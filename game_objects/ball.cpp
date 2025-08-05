#include "ball.hpp"

#include "../math_library_dir/polar.hpp"
#include "../math_library_dir/cartesian.hpp"
#include "../engine_library_dir/input.hpp"
#include "../engine_library_dir/debug.hpp"
#include "../engine_library_dir/textureManager.hpp"
#include "../game_data_files/geometries.hpp"
#include "../game_data_files/materials.hpp"
#include "../game_files/cameraManager.hpp"
#include "../game_files/gameManager.hpp"
#include "../game_files/gameObjectManager.hpp"

#include <iostream>

namespace gameObjects
{
    Ball::Ball() : maskQuad(std::make_unique<ScreenOrientedQuad>(&gameData::Materials::instance->whiteTextured, engine::TextureManager::instance->getTexture("ballMask.png"))),
                   GameObjectBase(&gameData::Geometries::instance->ball, &gameData::Materials::instance->ball)
    {
        reset();
    }

    void Ball::solveCollisions()
    {
        math::Polar ballPos(math::Vec2(transform.position.x(), transform.position.z()));

        // Game over
        if (ballPos.r() - radius > gameData::EnvironmentProperties::groundRadius)
        {
            game::GameManager::instance->decreaseLives();
            reset();
            return;
        }

        // Find potential collision
        const BrickBase *brick = nullptr;
        bool isPaddle;

        if (ballPos.r() + radius >= gameData::EnvironmentProperties::brickInnerRadius &&
            ballPos.r() - radius <= gameData::EnvironmentProperties::brickInnerRadius + gameData::EnvironmentProperties::brickWidth)
        {
            // Potential collision with bricks
            brick = game::GameObjectManager::instance->brickController()->getClosestBrick(ballPos);
            isPaddle = false;
        }
        else if (ballPos.r() + radius >= gameData::EnvironmentProperties::paddleInnerRadius &&
                 ballPos.r() - radius <= gameData::EnvironmentProperties::paddleInnerRadius + gameData::EnvironmentProperties::paddleWidth)
        {
            // Potential collision with paddle
            brick = game::GameObjectManager::instance->paddleController()->getClosestPaddle(ballPos);
            isPaddle = true;
        }
        else
        {
            // No potential collision
            return;
        }

        // Solve collision
        math::Vec3 collisionNormal;
        bool collision = collisionBroadPhase(
            ballPos,
            brick->getRealXZPosition(),
            isPaddle ? gameData::EnvironmentProperties::paddleSize : gameData::EnvironmentProperties::brickSize,
            isPaddle ? gameData::EnvironmentProperties::paddleWidth : gameData::EnvironmentProperties::brickWidth,
            isPaddle,
            collisionNormal);

        // if (collision)
        //     std::cout << (math::dot(velocity, collisionNormal) < 0 ? " Y" : " N") << "\n";
        // Aply the collision only if the velocity of the ball points inside of the object
        if (collision && math::dot(velocity, collisionNormal) < 0)
        {
            if (!isPaddle) // Break brick
                game::GameObjectManager::instance->brickController()->breakBrick((Brick *)brick);
            collisionResponse(collisionNormal);
            // std::cout << "Velocity:: x: " << velocity.x() << " | y: " << velocity.y() << " | z: " << velocity.z() << std::endl;
        }
    }

    bool Ball::collisionBroadPhase(const math::Polar &ballPos,
                                   const math::Polar &brickPos,
                                   const float brickAngleSize,
                                   const float brickWidth,
                                   bool isPaddle,
                                   math::Vec3 &collisionNormal)
    {
        if (math::Polar::angleDifference(ballPos, brickPos) <= brickAngleSize / 2)
            return collisionNarrowPhase1(ballPos, brickPos, brickAngleSize, brickWidth, isPaddle, collisionNormal);
        return collisionNarrowPhase2(ballPos, brickPos, brickAngleSize, brickWidth, isPaddle, collisionNormal);
    }

    bool Ball::collisionNarrowPhase1(const math::Polar &ballPos,
                                     const math::Polar &brickPos,
                                     const float brickAngleSize,
                                     const float brickWidth,
                                     bool isPaddle,
                                     math::Vec3 &collisionNormal)
    {
        assert(ballPos.r() + radius >= brickPos.r() - brickWidth / 2 && ballPos.r() - radius <= brickPos.r() + brickWidth / 2);
        assert(math::Polar::angleDifference(ballPos, brickPos) <= brickAngleSize / 2);

        // Compute collision normal
        collisionNormal = transform.position;
        collisionNormal.y() = 0;
        collisionNormal.normalize();
        if (ballPos.r() < brickPos.r())
            collisionNormal *= -1;

        // Rotate collision normal if paddle moving
        if (isPaddle && std::abs(game::GameObjectManager::instance->paddleController()->getCurrentAngularVelocity()) > 1e-5f)
        {
            // Rotate the normal slightly
            float twistAngle = game::GameObjectManager::instance->paddleController()->getCurrentAngularVelocity() > 0 ? paddleTwistAngle : -paddleTwistAngle;
            math::Quaternion r = math::Quaternion::fromEulerAngles(0, twistAngle, 0);
            collisionNormal = (r * math::Quaternion(0, collisionNormal) * r.conjugated()).u();
            // std::cout << "Twist angle: " << twistAngle << std::endl;
        }

        // Debug
        // std::cout << "Narrow1 " << (isPaddle ? "Paddle" : "Brick");
        // std::cout << "Normal:: x: " << collisionNormal.x() << " | y: " << collisionNormal.y() << " | z: " << collisionNormal.z() << std::endl;
        lastCollisionNormal = collisionNormal;
        lastContactPoint = transform.position;
        lastContactPoint.y() = 0;
        lastContactPoint.normalize();
        lastContactPoint *= brickPos.r() + (ballPos.r() < brickPos.r() ? -brickWidth / 2 : brickWidth / 2);
        lastContactPoint.y() = radius;

        return true;
    }

    bool Ball::collisionNarrowPhase2(const math::Polar &ballPos,
                                     const math::Polar &brickPos,
                                     const float brickAngleSize,
                                     const float brickWidth,
                                     bool isPaddle,
                                     math::Vec3 &collisionNormal)
    {
        assert(ballPos.r() + radius >= brickPos.r() - brickWidth / 2 && ballPos.r() - radius <= brickPos.r() + brickWidth / 2);
        assert(math::Polar::angleDifference(ballPos, brickPos) > brickAngleSize / 2);

        // Find edge of the brick
        float edgeAngle = brickPos.a() + (math::Polar::isInTheLeftHalfPlane(brickPos, ballPos) ? brickAngleSize / 2 : -brickAngleSize / 2);
        math::Vec3 direction = math::Vec3(std::cos(edgeAngle), 0, std::sin(edgeAngle));
        math::Vec3 a = direction * (brickPos.r() - brickWidth / 2);
        a.y() = radius;
        math::Vec3 b = direction * (brickPos.r() + brickWidth / 2);
        b.y() = radius;

        // Find closest point
        math::Vec3 q = math::Cartesian::closestPointOnLine(a, b, transform.position);

        math::Vec3 pointToBall = transform.position - q;

        if (pointToBall.magSquared() > radius * radius) // Closest point is outside of the ball
            return false;

        // Compute the normal
        collisionNormal = pointToBall.unit();

        // Debug
        // std::cout << "Narrow2 " << (isPaddle ? "Paddle" : "Brick");
        lastCollisionNormal = collisionNormal;
        lastContactPoint = q;

        return true;
    }

    void Ball::collisionResponse(const math::Vec3 &collisionNormal)
    {
        assert(std::abs(1 - collisionNormal.mag()) < 1e-6f);
        assert(std::abs(collisionNormal.y()) < 1e-6f);

        velocity -= 2 * math::dot(velocity, collisionNormal) * collisionNormal;
    }

    void Ball::update(float timeDelta)
    {
        if (!launched)
        {
            launch();
            return;
        }

        solveCollisions();

        // Move
        transform.position += velocity * timeDelta;
        // Update mask position
        maskQuad->transform.position = transform.position;

        // Compute target speed
        currentBaseSpeed = std::min(currentBaseSpeed + ballAcceleration * timeDelta, maxSpeed);
        float targetSpeed = currentBaseSpeed;
        if (transform.position.magSquared() < gameData::EnvironmentProperties::brickInnerRadius * gameData::EnvironmentProperties::brickInnerRadius)
            targetSpeed *= 1.5f;

        // Compute acceleration to reach target speed
        float acceleration = (targetSpeed - velocity.mag()) / timeDelta;
        float maxAcceleration = 2 * currentBaseSpeed;
        if (std::abs(acceleration) > maxAcceleration)
        {
            if (std::signbit(acceleration))
                acceleration = -maxAcceleration;
            else
                acceleration = maxAcceleration;
        }

        // Update velocity
        velocity += velocity.unit() * acceleration * timeDelta;
    }

    void Ball::renderMask()
    {
        maskQuad->render();
    }

    void Ball::launch()
    {
        if (engine::Input::keyDown(GLFW_KEY_SPACE))
        {
            launched = true;
            float angle = (float)M_PI / 2.0f - gameData::EnvironmentProperties::maxBallLaunchAngle + std::rand() / (float)RAND_MAX * gameData::EnvironmentProperties::maxBallLaunchAngle * 2;
            // angle = (float)M_PI / 2.0f;
            velocity.x() = std::cosf(angle);
            velocity.z() = std::sinf(angle);
            currentBaseSpeed = initSpeed;
            velocity *= currentBaseSpeed;
            // std::cout << "Init Velocity:: x: " << velocity.x() << " | y: " << velocity.y() << " | z: " << velocity.z() << std::endl;
        }
    }

    void Ball::reset()
    {
        transform.position = gameData::EnvironmentProperties::initBallPosition;
        // Update mask position
        maskQuad->transform.position = transform.position;

        currentBaseSpeed = 0;
        launched = false;
    }
} // namespace gameObjects
