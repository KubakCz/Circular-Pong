#pragma once

#include "../math_library_dir/vector.hpp"

namespace ui
{
    class Transform
    {
    public:
        /** Pivot position on the screen. 0 => left/top, 1 => right/bottom. */
        math::Vec2 pivot;
        /** Pivot offset inside the element. -1 => pivot is in the left bottom corner, 0 => pivot is in the center, 1 => pivot is in the right top corner .*/
        math::Vec2 pivotOffset;
        /** Size. y=1 => whole hight of the window. */
        math::Vec2 size;
        /** Bool. If true, size.x is relative to size.y else it is relative to screen. */
        int xRelativeToY;

    private:
        int pad1;

    public:
        Transform();
        Transform(const math::Vec2 &pivot, const math::Vec2 &pivotOffset, const math::Vec2 &size, bool xRelativeToY);

        static Transform getMidMid(const math::Vec2 &size, bool xRelativeToY = true);
    };
} // namespace ui
