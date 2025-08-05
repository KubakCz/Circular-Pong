#include "fullscreenText.hpp"

namespace gameUI
{
    FullscreenText::FullscreenText(engine::Texture textTexture) : text(ui::Transform::getMidMid(math::Vec2(1, 0.1f)), textTexture, true){};

    void FullscreenText::render() const
    {
        background.render();
        text.render();
    }
} // namespace gameUI
