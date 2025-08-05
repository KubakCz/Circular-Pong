#include "transform.hpp"
#include "../engine_library_dir/uniforms.hpp"

namespace ui
{
    Transform::Transform() : pivot(0, 0), size(1, 1){};
    Transform::Transform(const math::Vec2 &pivot, const math::Vec2 &pivotOffset, const math::Vec2 &size, bool xRelativeToY) : pivot(pivot),
                                                                                                                              pivotOffset(pivotOffset),
                                                                                                                              size(size),
                                                                                                                              xRelativeToY(xRelativeToY){};

    Transform Transform::getMidMid(const math::Vec2 &size, bool xRelativeToY)
    {
        return Transform(math::Vec2::one * 0.5, math::Vec2::zero, size, xRelativeToY);
    }
} // namespace ui

namespace engine
{
    template <>
    void UBO<ui::Transform>::bind() const
    {
        bind(engine::UI_TRANSFORM_DEFAULT_BIND_INDEX);
    }
} // namespace engine
