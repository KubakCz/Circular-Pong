#include "gameObjectManager.hpp"
#include <stdexcept>
#include "cameraManager.hpp"
#include "../engine_library_dir/textureManager.hpp"

namespace game
{
    GameObjectManager *GameObjectManager::instance = nullptr;

    GameObjectManager::GameObjectManager() : _brickController(std::make_unique<gameObjects::BrickController>()),
                                             _paddleController(std::make_unique<gameObjects::PaddleController>()),
                                             _ball(std::make_unique<gameObjects::Ball>()),
                                             _ground(std::make_unique<gameObjects::Ground>())
    {
        if (instance == nullptr)
            instance = this;
        else
            throw std::logic_error("Instance already exists.");
    }

    GameObjectManager::~GameObjectManager()
    {
        if (instance == this)
            instance = nullptr;
    }

    void GameObjectManager::update(float deltaSeconds)
    {
        _brickController->update(deltaSeconds);
        _paddleController->update(deltaSeconds);
        _ball->update(deltaSeconds);
        _ground->update(deltaSeconds);
    }
} // namespace game
