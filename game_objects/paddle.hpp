#pragma once

#include "brickBase.hpp"
#include "../game_data_files/geometries.hpp"

namespace gameObjects
{
    class Paddle : public BrickBase
    {
    public:
        Paddle(float initAnglePosition);

        void rotate(float deltaAngle);
        void setRotation(float angle);

        void render(bool b) override;
    };
} // namespace game
