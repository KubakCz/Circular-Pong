#include "brick.hpp"

#include "../game_data_files/geometries.hpp"
#include "../game_data_files/materials.hpp"

namespace gameObjects
{
    Brick::Brick(float orientation, int level, int lives) : _lives(lives),
                                                            _points((unsigned int)lives),
                                                            BrickBase(
                                                                math::Polar(orientation, gameData::EnvironmentProperties::brickInnerRadius + gameData::EnvironmentProperties::brickWidth * 0.5f),
                                                                gameData::EnvironmentProperties::brickHeight * (level + 0.5f),
                                                                &gameData::Geometries::instance->brick,
                                                                &gameData::Materials::instance->brick[lives - 1]){};

    void Brick::update(float deltaTime)
    {
        if (targetHeight < transform.position.y())
        {
            // update speed and compute new position
            verticalSpeed += -9.8f * deltaTime;
            float newYpos = transform.position.y() + verticalSpeed * deltaTime;

            // stop fall
            if (newYpos < targetHeight)
            {
                newYpos = targetHeight;
                verticalSpeed = 0;
                targetHeight = INFINITY;
            }

            // aply position
            transform.position.y() = newYpos;
        }
    }

    void Brick::triggerFall(float targetHeight)
    {
        Brick::targetHeight = targetHeight;
    }

    void Brick::decreaseLives()
    {
        --_lives;
        assert(_lives >= 0 && _lives < gameData::Materials::instance->brick.size());
        if (_lives > 0)
            material = &gameData::Materials::instance->brick[_lives - 1];
    }
} // namespace gameObjects
