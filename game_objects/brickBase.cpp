#include "brickBase.hpp"

namespace gameObjects
{
    BrickBase::BrickBase(const math::Polar &xzPosition, float yPosition, const engine::Geometry *geometry, const engine::UBO<engine::MaterialData> *material) : realXZPosition(xzPosition),
                                                                                                                                                                GameObjectBase(
                                                                                                                                                                    engine::Transform(
                                                                                                                                                                        math::Vec3(0, yPosition, 0),
                                                                                                                                                                        math::Quaternion::fromEulerAngles(0, -xzPosition.a(), 0)),
                                                                                                                                                                    geometry,
                                                                                                                                                                    material){};
} // namespace gameObjects