#include "renderManager.hpp"
#include "cameraManager.hpp"
#include "gameManager.hpp"
#include "gameObjectManager.hpp"
#include "../engine_library_dir/shaderManager.hpp"
#include "../engine_library_dir/debug.hpp"

namespace game
{
    RenderManager *RenderManager::instance = nullptr;

    RenderManager::RenderManager(const int &windowWidth, const int &windowHeight) : _windowWidth(windowWidth),
                                                                                    _windowHeight(windowHeight),
                                                                                    _ssao(windowWidth, windowHeight, 0.1f),
                                                                                    _lightsUBO(std::make_unique<engine::LightsData>(
                                                                                        1,
                                                                                        std::vector<engine::LightData>{
                                                                                            engine::SunData(math::Vec3(1, 1, -1), math::Vec3::one, 0.5f, 0.7f, 0.7f)})),
                                                                                    _livesText(
                                                                                        ui::Transform(math::Vec2(_textOffset, 1 - _textOffset), math::Vec2(-1, 1), math::Vec2(1, _textHeight), true),
                                                                                        engine::TextureManager::instance->getTexture("lives.png"),
                                                                                        true),
                                                                                    _scoreText(
                                                                                        ui::Transform(math::Vec2(1 - _textOffset, 1 - _textOffset), math::Vec2(1, 1), math::Vec2(1, _textHeight), true),
                                                                                        engine::TextureManager::instance->getTexture("score.png"),
                                                                                        true),
                                                                                    _scoreNumber(math::Vec2(1 - _textOffset, 1 - (2 * _textOffset + _textHeight)), _textHeight, 10)
    {
        if (instance != nullptr)
            throw std::logic_error("Instance already exists.");
        instance = this;

        // create hearts
        engine::Texture heartTexture = engine::TextureManager::instance->getTexture("heart.png");
        for (int i = 0; i < 3; ++i)
            _livesSprites.emplace_back(
                ui::Transform(math::Vec2(_textOffset, 1 - (2 * _textOffset + _textHeight)), math::Vec2(-1.0f - 2.5f * i, 1), math::Vec2(1, _textHeight), true),
                heartTexture,
                true);

        // set texture properties
        _livesText.texture.setTextureParameters(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR);
        _scoreText.texture.setTextureParameters(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR);
        heartTexture.setTextureParameters(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR);

        prepareFramebuffers();
    }

    RenderManager::~RenderManager()
    {
        if (instance == this)
            instance = nullptr;

        glDeleteFramebuffers(1, &_ballMaskFbo);
        glDeleteTextures(1, &_ballMaskTexture);
    }

    void RenderManager::prepareFramebuffers()
    {
        glCreateFramebuffers(1, &_ballMaskFbo);
        GLenum colorAtachment = GL_COLOR_ATTACHMENT0;
        glNamedFramebufferDrawBuffers(_ballMaskFbo, 1, &colorAtachment);

        // Create and attach textures
        resizeFullscreenTextures();
    }

    void RenderManager::resizeFullscreenTextures()
    {
        // Remove previously allocated textures (if any)
        glDeleteTextures(1, &_ballMaskTexture);

        // Create new textures
        glCreateTextures(GL_TEXTURE_2D, 1, &_ballMaskTexture);

        // Initialize the immutable storage
        glTextureStorage2D(_ballMaskTexture, 1, GL_RG32F, _windowWidth, _windowHeight);

        // Set the texture parameters
        engine::Texture::setTextureParameters(_ballMaskTexture, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_NEAREST, GL_NEAREST);

        // Bind the textures to the buffers
        glNamedFramebufferTexture(_ballMaskFbo, GL_COLOR_ATTACHMENT0, _ballMaskTexture, 0);

        _ssao.resizeFullScreenTextures(_windowWidth, _windowHeight);
    }

#pragma region render
    void RenderManager::render() const
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        CameraManager::instance->bindCamera();

        // use mask if not TopDown camera
        bool useBallMask = !game::CameraManager::instance->currentCameraIsTopDown();
        if (useBallMask)
            renderAlphaMask();

        // SSAO
        _ssao.bindSceneFramebuffer(_windowWidth, _windowHeight);
        // Set min z for alpha mask
        glUniform1f(2, GameObjectManager::instance->ball()->transform.position.z());
        // do not bind default framebuffer - the ssao framebuffer is used
        // sort bricks if not TopDown camera
        renderScene(false, !game::CameraManager::instance->currentCameraIsTopDown(), useBallMask);
        _ssao.evaluateSSAO(_windowWidth, _windowHeight);

        // Render scene
        _lightsUBO.bind();
        // no need to sort bricks, already sorted in ssao pass if demanded
        // use mask if not TopDown camera
        renderScene(true, false, useBallMask);

        glDisable(GL_CULL_FACE);

        // Debug mode rendering
        if (game::GameManager::instance->debug())
        {
            glUseProgram(engine::ShaderManager::instance->unilitProgram());
            engine::Debug::drawAxis(); // render axis

            // render light positions
            for (int i = 0; i < _lightsUBO.data->size(); ++i)
            {
                engine::Debug::drawCross((math::Vec3)(*_lightsUBO.data)[i].position, 0.1f, math::Vec4::one);
            }

            // render ball collision normal
            gameObjects::Ball *b = game::GameObjectManager::instance->ball();
            engine::Debug::drawLine(b->lastContactPoint,
                                    b->lastContactPoint + b->lastCollisionNormal,
                                    math::Vec4(0, 1, 0, 1));
        }
    }

    void RenderManager::renderAlphaMask() const
    {
        glUseProgram(engine::ShaderManager::instance->maskProgram());

        // Bind mask mask framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, _ballMaskFbo);
        glViewport(0, 0, _windowWidth, _windowHeight);
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        game::GameObjectManager::instance->ball()->renderMask();
    }

    void RenderManager::renderScene(bool bindDefaultFramebuffer, bool sortBricks, bool useBallMask) const
    {
        if (bindDefaultFramebuffer)
        {
            glUseProgram(engine::ShaderManager::instance->litWithMaskProgram());

            // Bind default framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, _windowWidth, _windowHeight);
            glClearColor(0.6f, 0.7f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Bind occlusion texture and turn ssao on
            glBindTextureUnit(2, _ssao.occlusionTexture());
            glUniform1i(1, 1);

            // Set min z for alpha mask
            glUniform1f(2, GameObjectManager::instance->ball()->transform.position.z());
        }

        // Bind ball mask
        glBindTextureUnit(1, _ballMaskTexture);

        // Use depth test and blending
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Don't use mask for ground, ball and paddles
        // No need to bind materials if rendering into ssao (bindDefaultFramebuffer == false)
        glUniform1i(0, 0);
        game::GameObjectManager::instance->ground()->render(bindDefaultFramebuffer);
        game::GameObjectManager::instance->ball()->render(bindDefaultFramebuffer);
        game::GameObjectManager::instance->paddleController()->render(bindDefaultFramebuffer);

        // Use mask for bricks if demanded
        if (useBallMask)
            glUniform1i(0, 1);
        game::GameObjectManager::instance->brickController()->render(sortBricks, bindDefaultFramebuffer);

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
    }

    void RenderManager::renderTexture(GLuint texture) const
    {
        glUseProgram(engine::ShaderManager::instance->displayTextureProgram());

        // Bind default framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, _windowWidth, _windowHeight);

        glBindTextureUnit(0, texture);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
#pragma endregion render

#pragma region renderUI
    void RenderManager::renderUI() const
    {
        glUseProgram(engine::ShaderManager::instance->uiProgram());

        // Bind default framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, _windowWidth, _windowHeight);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Set window ratio
        glUniform1f(0, (float)_windowWidth / _windowHeight);

        // Render fulscreen texts
        if (game::GameManager::instance->paused())
            _fullscreenTexts.pause.render();

        if (game::GameManager::instance->gameState() == game::gameOver)
            _fullscreenTexts.gameOver.render();
        else if (game::GameManager::instance->gameState() == game::win)
            _fullscreenTexts.win.render();

        // Render lives and score
        _livesText.render();
        assert(game::GameManager::instance->lives() <= _livesSprites.size());
        for (int i = 0; i < (int)game::GameManager::instance->lives(); ++i)
            _livesSprites[i].render();
        _scoreText.render();
        _scoreNumber.render();

        glDisable(GL_BLEND);
    }
#pragma endregion renderUI
} // namespace game
