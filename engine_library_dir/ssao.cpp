#include "ssao.hpp"
#include "../math_library_dir/vector.hpp"
#include "textureManager.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

namespace engine
{
    SSAO::SSAO(GLsizei width, GLsizei height, float ssaoRadius) : ssaoRadius(ssaoRadius)
    {
        prepareFramebuffers(width, height);
        computeRandomTangents();
        computeRandomSamples();
    }

    SSAO::~SSAO()
    {
        glDeleteBuffers(1, &ssaoSamplesUBO);
        glDeleteTextures(1, &randomTangentVsTexture);

        glDeleteFramebuffers((GLsizei)fbos.size(), fbos.data());
        glDeleteTextures((GLsizei)fullScreenTextures.size(), fullScreenTextures.data());
    }

    void SSAO::prepareFramebuffers(GLsizei width, GLsizei height)
    {
        const GLenum attachments[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};

        glCreateFramebuffers((GLsizei)fbos.size(), fbos.data());

        glNamedFramebufferDrawBuffers(sceneFbo, 2, attachments);
        glNamedFramebufferDrawBuffers(ssaoFbo, 1, attachments);
        glNamedFramebufferDrawBuffers(blurFbo, 1, attachments);
    }

    void SSAO::computeRandomTangents()
    {
        // Based on PV227 lecture 04
        const GLint textureSize = 4;
        std::vector<math::Vec3> SSAORandomTangent(textureSize * textureSize);
        for (int i = 0; i < SSAORandomTangent.size(); i++)
        {
            // Generates the tangents as random directions in xy plane.
            const float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f * static_cast<float>(M_PI);
            SSAORandomTangent[i] = math::Vec3(sinf(angle), cosf(angle), 0.0f);
        }
        // Creates a 4x4 texture for these random directions.
        glCreateTextures(GL_TEXTURE_2D, 1, &randomTangentVsTexture);
        glTextureStorage2D(randomTangentVsTexture, 1, GL_RGBA32F, textureSize, textureSize);
        glTextureSubImage2D(randomTangentVsTexture, 0, 0, 0, textureSize, textureSize, GL_RGB, GL_FLOAT, SSAORandomTangent.data());
        Texture::setTextureParameters(randomTangentVsTexture, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
    }

    void SSAO::computeRandomSamples()
    {
        // Based on PV227 lecture 04
        std::vector<math::Vec4> ssao_samples(NUMBER_OF_SSAO_SAMPLES);
        for (size_t i = 0; i < ssao_samples.size(); i++)
        {
            // Create a uniform point on a hemisphere (unit sphere, cut by xy plane, hemisphere in +z direction)
            const float alpha = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f * static_cast<float>(M_PI);
            const float beta = asinf(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
            math::Vec3 point_on_hemisphere = math::Vec3(cosf(alpha) * cosf(beta), sinf(alpha) * cosf(beta), sinf(beta));

            // Place the point on the hemisphere inside the hemisphere, so that the points in the hemisphere were uniformly
            // distributed in the hemisphere. This is true when the distance of the points from the center of the hemisphere
            // is the cube root of a uniformly distributed random number from interval [0,1].
            const float radius = powf(static_cast<float>(rand()) / static_cast<float>(RAND_MAX), 1.0f / 3.0f);
            math::Vec3 point_in_hemisphere = point_on_hemisphere * radius;

            ssao_samples[i] = (math::Vec4)point_in_hemisphere;
        }

        // Creates a buffer for storing the random positions.
        glCreateBuffers(1, &ssaoSamplesUBO);
        glNamedBufferStorage(ssaoSamplesUBO, sizeof(float) * 4 * ssao_samples.size(), ssao_samples.data(), 0 /* no updates needed*/);
    }

    void SSAO::resizeFullScreenTextures(GLsizei width, GLsizei height)
    {
        glDeleteTextures((GLsizei)fullScreenTextures.size(), fullScreenTextures.data());
        glCreateTextures(GL_TEXTURE_2D, (GLsizei)fullScreenTextures.size(), fullScreenTextures.data());

        glTextureStorage2D(scenePositionVSTexture, 1, GL_RGBA16F, width, height);
        glTextureStorage2D(sceneNormalVSTexture, 1, GL_RGBA16F, width, height);
        glTextureStorage2D(sceneDepthTexture, 1, GL_DEPTH_COMPONENT24, width, height);
        glTextureStorage2D(ssaoOcclusionTexture, 1, GL_R16F, width, height);
        glTextureStorage2D(blurOcclusionTexture, 1, GL_R16F, width, height);

        Texture::setTextureParameters(fullScreenTextures.size(), fullScreenTextures.data(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_NEAREST, GL_NEAREST);

        glNamedFramebufferTexture(sceneFbo, GL_COLOR_ATTACHMENT0, scenePositionVSTexture, 0);
        glNamedFramebufferTexture(sceneFbo, GL_COLOR_ATTACHMENT1, sceneNormalVSTexture, 0);
        glNamedFramebufferTexture(sceneFbo, GL_DEPTH_ATTACHMENT, sceneDepthTexture, 0);

        glNamedFramebufferTexture(ssaoFbo, GL_COLOR_ATTACHMENT0, ssaoOcclusionTexture, 0);

        glNamedFramebufferTexture(blurFbo, GL_COLOR_ATTACHMENT0, blurOcclusionTexture, 0);
    }

    void SSAO::bindSceneFramebuffer(GLsizei width, GLsizei height) const
    {
        glUseProgram(engine::ShaderManager::instance->positionsAndNormalsProgram());

        // Bind ssao framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, sceneFbo);
        glViewport(0, 0, width, height);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void SSAO::evaluateSSAO(GLsizei width, GLsizei height) const
    {
        eval(width, height);
        blur(width, height);
    }

    void SSAO::eval(GLsizei width, GLsizei height) const
    {
        glUseProgram(engine::ShaderManager::instance->evaluateSSAOProgram());

        // Bind ssao framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, ssaoFbo);
        glViewport(0, 0, width, height);

        // Bind textures
        glBindTextureUnit(0, scenePositionVSTexture);
        glBindTextureUnit(1, sceneNormalVSTexture);
        glBindTextureUnit(2, randomTangentVsTexture);

        // Set ssao radius
        glUniform1f(0, ssaoRadius);

        // Bind buffer with ssao samples
        glBindBufferBase(GL_UNIFORM_BUFFER, 1, ssaoSamplesUBO);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void SSAO::blur(GLsizei width, GLsizei height) const
    {
        glUseProgram(engine::ShaderManager::instance->blurSSAOProgram());

        // Bind ssao framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, blurFbo);
        glViewport(0, 0, width, height);

        // Bind textures
        glBindTextureUnit(0, ssaoOcclusionTexture);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

} // namespace engine
