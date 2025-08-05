#pragma once

#include "glad/glad.h"
#include "../engine_library_dir/uniforms.hpp"
#include "../engine_library_dir/ssao.hpp"
#include "../game_ui/fullscreenTexts.hpp"
#include "../ui_library_dir/number.hpp"
#include <vector>

namespace game
{
    class RenderManager
    {
        const int &_windowWidth;
        const int &_windowHeight;

        engine::SSAO _ssao;
        engine::UBO<engine::LightsData> _lightsUBO;

        gameUI::FullscreenTexts _fullscreenTexts;

        /** Framebuffer for rendering transparency mask around the ball. */
        GLuint _ballMaskFbo;
        GLuint _ballMaskTexture; // alpha in r, depth (ndc) in g

        const float _textHeight = 0.03f;
        const float _textOffset = 0.01f;
        ui::Element _livesText;
        std::vector<ui::Element> _livesSprites;
        ui::Element _scoreText;
        ui::Number _scoreNumber;

    public:
        static RenderManager *instance;

        RenderManager(const int &windowWidth, const int &windowHeight);
        RenderManager(const RenderManager &rm) = delete;
        RenderManager(RenderManager &&rm) = delete;
        ~RenderManager();

        void render() const;
        void renderUI() const;

        void resizeFullscreenTextures();

        void updateScoreNumber(unsigned int score) { _scoreNumber.value(score); };

    private:
        void renderAlphaMask() const;
        void renderScene(bool bindDefaultFramebuffer, bool sortBricks, bool useBallMask) const;
        void renderTexture(GLuint texture) const;

        void prepareFramebuffers();
    };
} // namespace game
