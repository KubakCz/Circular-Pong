#pragma once

#include "fullscreenText.hpp"
#include "../engine_library_dir/textureManager.hpp"

namespace gameUI
{
    class FullscreenTexts
    {
    public:
        const FullscreenText pause = FullscreenText(engine::TextureManager::instance->getTexture("pause.png"));
        const FullscreenText win = FullscreenText(engine::TextureManager::instance->getTexture("you_win.png"));
        const FullscreenText gameOver = FullscreenText(engine::TextureManager::instance->getTexture("game_over.png"));
    };
} // namespace gameUI
