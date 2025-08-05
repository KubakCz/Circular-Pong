#pragma once

#include "shaderManager.hpp"
#include "glad/glad.h"
#include <array>

// The number of the samples.
// This number must be same as in the shader.
#define NUMBER_OF_SSAO_SAMPLES 128

namespace engine
{
    class SSAO
    {
        float ssaoRadius;

        std::array<GLuint, 3> fbos;
        std::array<GLuint, 5> fullScreenTextures;

        GLuint ssaoSamplesUBO;
        GLuint randomTangentVsTexture;

        GLuint &sceneFbo = fbos[0];
        GLuint &scenePositionVSTexture = fullScreenTextures[0]; // positions in view space
        GLuint &sceneNormalVSTexture = fullScreenTextures[1];   // normals in view space
        GLuint &sceneDepthTexture = fullScreenTextures[2];

        GLuint &ssaoFbo = fbos[1];
        GLuint &ssaoOcclusionTexture = fullScreenTextures[3];

        GLuint &blurFbo = fbos[2];
        GLuint &blurOcclusionTexture = fullScreenTextures[4];

        // preparation methods
        void prepareFramebuffers(GLsizei width, GLsizei height);
        void computeRandomTangents();
        void computeRandomSamples();

        /** Evaluate the occlusion. */
        void eval(GLsizei width, GLsizei height) const;

        /** Blur the occlusion texture to remove artefacts. */
        void blur(GLsizei width, GLsizei height) const;

    public:
        /// @brief Create new instance of ssao utils.
        /// @param width initial window width
        /// @param height initial window height
        /// @param ssaoRadius
        SSAO(GLsizei width, GLsizei height, float ssaoRadius);

        ~SSAO();

        /** Call this on window resize. */
        void resizeFullScreenTextures(GLsizei width, GLsizei height);

        /// @brief Binds the scene framebuffer and sets the positionsAndNoramls shader program. Render the scene into this buffer to evaluate positions and normals textures for ssao.
        /// @param width window width
        /// @param height window height
        void bindSceneFramebuffer(GLsizei width, GLsizei height) const;

        /// @brief Evaluate ssao. Before evaluation, render the scene with scene framebuffer.
        void evaluateSSAO(GLsizei width, GLsizei height) const;

        /** Get the final occlusion texture. */
        GLuint occlusionTexture() const { return blurOcclusionTexture; }
    };
} // namespace engine
