#pragma once

#include "glad/glad.h"
#include "../math_library_dir/vector.hpp"

namespace ui
{
    struct Rectangle
    {
        math::Vec2 minCorner;
        math::Vec2 maxCorner;

        Rectangle();
        Rectangle(const math::Vec2 &minCorner, const math::Vec2 &maxCorner);

        float width() const { return maxCorner.x() - minCorner.x(); }
        float height() const { return maxCorner.y() - minCorner.y(); }
        math::Vec2 size() const { return maxCorner - minCorner; }
    };
} // namespace ui
