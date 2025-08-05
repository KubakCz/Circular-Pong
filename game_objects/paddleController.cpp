#include "paddleController.hpp"
#include "../engine_library_dir/input.hpp"
#include "glad/glad.h"

namespace gameObjects
{
    PaddleController::PaddleController() : engine::GameObjectBase()
    {
        paddles.reserve(paddleCount);
        float theta = -(float)M_PI / 2;
        for (int i = 0; i < paddleCount; ++i)
        {
            paddles.emplace_back(theta);
            theta += 2 * (float)M_PI / paddleCount;
        }
    }

    void PaddleController::update(float deltaTime)
    {
        currentAngularVelocity = 0;
        if (engine::Input::keyPressed(GLFW_KEY_LEFT) || engine::Input::keyPressed(GLFW_KEY_A))
            currentAngularVelocity += angularVelocity;
        if (engine::Input::keyPressed(GLFW_KEY_RIGHT) || engine::Input::keyPressed(GLFW_KEY_D))
            currentAngularVelocity -= angularVelocity;

        if (currentAngularVelocity != 0)
        {
            for (auto it = paddles.begin(); it != paddles.end(); ++it)
            {
                it->rotate(currentAngularVelocity * deltaTime);
            }
        }
    }

    void PaddleController::render(bool bindMaterial)
    {
        for (auto it = paddles.begin(); it != paddles.end(); ++it)
            it->render(bindMaterial);
    }

    void PaddleController::reset()
    {
        float theta = -(float)M_PI / 2;
        for (int i = 0; i < paddleCount; ++i)
        {
            paddles[i].setRotation(theta);
            theta += 2 * (float)M_PI / paddleCount;
        }
    }

    const Paddle *PaddleController::getClosestPaddle(math::Polar p) const
    {
        const Paddle *paddle = nullptr;
        float minAngle = INFINITY;

        for (int i = 0; i < paddles.size(); ++i)
        {
            float angle = math::Polar::angleDifference(p, paddles[i].getRealXZPosition());
            if (angle < minAngle)
            {
                minAngle = angle;
                paddle = &paddles[i];
            }
        }

        return paddle;
    }
} // namespace gameObjects
