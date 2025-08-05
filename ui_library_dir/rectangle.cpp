#include "rectangle.hpp"
#include "../engine_library_dir/uniforms.hpp"

namespace ui
{
    Rectangle::Rectangle() : minCorner(math::Vec2::zero),
                             maxCorner(math::Vec2::one){};

    Rectangle::Rectangle(const math::Vec2 &minCorner, const math::Vec2 &maxCorner) : minCorner(minCorner),
                                                                                     maxCorner(maxCorner){};
} // namespace ui
