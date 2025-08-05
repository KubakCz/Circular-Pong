#pragma once

#include "../ui_library_dir/element.hpp"

namespace gameUI
{
    class FullscreenText
    {
        const ui::Element background = ui::Element(
            ui::Transform::getMidMid(math::Vec2(1, 1), false),
            math::Vec4(0, 0, 0, 0.5f));
        const ui::Element text;

    public:
        FullscreenText(engine::Texture textTexture);

        void render() const;
    };
} // namespace gameUI
