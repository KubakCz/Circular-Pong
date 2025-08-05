#pragma once

#include "brickBase.hpp"
#include "../game_data_files/geometries.hpp"

namespace gameObjects
{
    class Brick : public BrickBase
    {
        float targetHeight = INFINITY; // update position only if current height > target height (only fall down)
        float verticalSpeed = 0;
        unsigned int _points = 1;
        int _lives = 1;

    public:
        Brick(float orientation, int level, int lives);

        void update(float deltaTime) override;

        void triggerFall(float targetHeight);

        unsigned int points() const { return _points; }
        int lives() const { return _lives; }
        void decreaseLives();
    };
} // namespace game
