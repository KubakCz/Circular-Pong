#include "paddle.hpp"

#include "../game_data_files/geometries.hpp"
#include "../game_data_files/materials.hpp"
#include "../engine_library_dir/debug.hpp"

namespace gameObjects
{
    Paddle::Paddle(float initAnglePosition) : BrickBase(
                                                  math::Polar(initAnglePosition, gameData::EnvironmentProperties::paddleInnerRadius + gameData::EnvironmentProperties::paddleWidth * 0.5f),
                                                  gameData::EnvironmentProperties::paddleHeight / 2,
                                                  &gameData::Geometries::instance->paddle,
                                                  &gameData::Materials::instance->paddle) {}

    void Paddle::rotate(float deltaAngle)
    {
        realXZPosition.a(realXZPosition.a() + deltaAngle);
        transform.rotation = math::Quaternion::fromEulerAngles(0, -realXZPosition.a(), 0);
    }

    void Paddle::setRotation(float angle)
    {
        realXZPosition.a(angle);
        transform.rotation = math::Quaternion::fromEulerAngles(0, -realXZPosition.a(), 0);
    }

    void Paddle::render(bool mat)
    {
        BrickBase::render(mat);

        // glDisable(GL_DEPTH_TEST);
        // math::Vec2 p = realXZPosition.toCartesian();
        // engine::Debug::drawCross(math::Vec3(p.x(), 0, p.y()), 0.4f, math::Vec4(1, 0, 0, 1));
        // float sideAngle = realXZPosition.a() + gameData::EnvironmentProperties::paddleSize / 2;
        // math::Vec2 a = math::Polar(sideAngle, gameData::EnvironmentProperties::paddleInnerRadius).toCartesian();
        // engine::Debug::drawCross(math::Vec3(a.x(), 0, a.y()), 0.4f, math::Vec4(0, 1, 0, 1));
        // math::Vec2 b = math::Polar(sideAngle, gameData::EnvironmentProperties::paddleInnerRadius + gameData::EnvironmentProperties::paddleWidth).toCartesian();
        // engine::Debug::drawCross(math::Vec3(b.x(), 0, b.y()), 0.4f, math::Vec4(0, 0, 1, 1));
        // glEnable(GL_DEPTH_TEST);
    }
} // namespace gameObjects
