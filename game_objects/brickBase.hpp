#pragma once

#include "../engine_library_dir/gameObjectBase.hpp"
#include "../math_library_dir/polar.hpp"

namespace gameObjects
{
    class BrickBase : public engine::GameObjectBase
    {
    protected:
        math::Polar realXZPosition;

    public:
        BrickBase(const math::Polar &xyPosition, float yPosition, const engine::Geometry *geometry, const engine::UBO<engine::MaterialData> *material);

        math::Polar getRealXZPosition() const { return realXZPosition; }
    };
} // namespace gameObjects
