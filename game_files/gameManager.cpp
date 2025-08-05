#include "gameManager.hpp"
#include <stdexcept>
#include "../engine_library_dir/input.hpp"
#include "gameObjectManager.hpp"
#include "renderManager.hpp"

namespace game
{
    GameManager *GameManager::instance = nullptr;

    GameManager::GameManager()
    {
        if (instance == nullptr)
            instance = this;
        else
            throw std::logic_error("Instance already exists.");
    }

    GameManager::~GameManager()
    {
        if (instance == this)
            instance = nullptr;
    }

#pragma region getters and setters
    void GameManager::paused(bool newValue)
    {
        _paused = newValue;
    }

    void GameManager::gameState(GameState newState)
    {
        if (newState == game)
            resetGame();
        _state = newState;
    }

    void GameManager::decreaseLives()
    {
        --_lives;
        if (_lives == 0)
            gameState(gameOver);
    }

    void GameManager::increaseScore(unsigned int score)
    {
        _score += score;
        RenderManager::instance->updateScoreNumber(_score);
    }
#pragma endregion getters and setters

    void GameManager::update(float deltaSeconds)
    {
        // Debug switch
        if (engine::Input::keyDown(GLFW_KEY_BACKSLASH))
            _debug = true;

        // Pause switch
        if (engine::Input::keyDown(GLFW_KEY_P))
            paused(!paused());

        switch (_state)
        {
        case game:
            gameUpdate(deltaSeconds);
            break;
        case gameOver:
        case win:
            waitForInput([&]()
                         { gameState(game); });
            break;
        default:
            throw std::logic_error("Undefined game state.");
        }
    }

    void GameManager::pauseCheck()
    {
        if (engine::Input::keyDown(GLFW_KEY_P))
            paused(!paused());
    }

    void GameManager::waitForInput(std::function<void()> action)
    {
        if (engine::Input::keyDown())
            action();
    }

    void GameManager::gameUpdate(float deltaSeconds)
    {
        if (paused())
            return;

        GameObjectManager::instance->update(deltaSeconds);
    }

    void GameManager::resetGame()
    {
        GameObjectManager::instance->ball()->reset();
        GameObjectManager::instance->paddleController()->reset();
        GameObjectManager::instance->brickController()->reset();
        _lives = 3;
        _score = 0;
        RenderManager::instance->updateScoreNumber(_score);
    }
} // namespace game
