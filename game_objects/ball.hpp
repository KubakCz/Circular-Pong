#pragma once

#include "../engine_library_dir/gameObjectBase.hpp"
#include "../game_data_files/geometries.hpp"
#include "paddleController.hpp"
#include "brickController.hpp"
#include "screenOrientedQuad.hpp"
#include <functional>

namespace gameObjects
{
    class Ball : public engine::GameObjectBase
    {
        std::unique_ptr<ScreenOrientedQuad> maskQuad;

        const float radius = gameData::EnvironmentProperties::ballRadius;
        const float initSpeed = 3.0f;
        const float maxSpeed = 15.0f;
        const float ballAcceleration = 0.01f;
        const float paddleTwistAngle = (float)M_PI / 60; // How much to rotate collision normal, when paddle hit and moving
        float currentBaseSpeed;
        math::Vec3 velocity;
        bool launched = false;

        // Debug
    public:
        math::Vec3 lastCollisionNormal;
        math::Vec3 lastContactPoint;

    private:
        void launch();
        void solveCollisions();
        bool collisionBroadPhase(const math::Polar &ballPos,
                                 const math::Polar &brickPos,
                                 const float brickAngleSize,
                                 const float brickWidth,
                                 bool isPaddle,
                                 math::Vec3 &collisionNormal);
        bool collisionNarrowPhase1(const math::Polar &ballPos,
                                   const math::Polar &brickPos,
                                   const float brickAngleSize,
                                   const float brickWidth,
                                   bool isPaddle,
                                   math::Vec3 &collisionNormal);
        bool collisionNarrowPhase2(const math::Polar &ballPos,
                                   const math::Polar &brickPos,
                                   const float brickAngleSize,
                                   const float brickWidth,
                                   bool isPaddle,
                                   math::Vec3 &collisionNormal);
        void collisionResponse(const math::Vec3 &collisionNormal);

    public:
        Ball();

        void update(float timeDelta) override;

        void renderMask();

        void reset();
    };
} // namespace game
