#pragma once

#include <memory>

#include "../game_objects/ball.hpp"
#include "../game_objects/ground.hpp"
#include "../game_objects/paddleController.hpp"
#include "../game_objects/brickController.hpp"

namespace game
{
    class GameObjectManager
    {
        std::unique_ptr<gameObjects::BrickController> _brickController;
        std::unique_ptr<gameObjects::PaddleController> _paddleController;
        std::unique_ptr<gameObjects::Ball> _ball;
        std::unique_ptr<gameObjects::Ground> _ground;

    public:
        static GameObjectManager *instance;

        GameObjectManager();
        GameObjectManager(const GameObjectManager &gom) = delete;
        GameObjectManager(GameObjectManager &&gom) = delete;
        ~GameObjectManager();

#pragma region getters and setters
        gameObjects::BrickController *brickController() const
        {
            return _brickController.get();
        }
        gameObjects::PaddleController *paddleController() const
        {
            return _paddleController.get();
        }
        gameObjects::Ball *ball() const
        {
            return _ball.get();
        }
        gameObjects::Ground *ground() const
        {
            return _ground.get();
        }
#pragma endregion getters and setters

        void update(float deltaSeconds);
    };
} // namespace game
