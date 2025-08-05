#pragma once

#include <vector>
#include "../engine_library_dir/gameObjectBase.hpp"
#include "paddle.hpp"

namespace gameObjects
{
    class PaddleController : public engine::GameObjectBase
    {
        std::vector<Paddle> paddles;
        float currentAngularVelocity;

    public:
        const int paddleCount = 3;
        const float angularVelocity = 1;

    public:
        PaddleController();

        void update(float deltaTime) override;
        void render(bool bindMaterial = true) override;

        void reset();

        const Paddle *getClosestPaddle(math::Polar p) const;

        float getCurrentAngularVelocity() const { return currentAngularVelocity; }
    };
} // namespace gameObjects
