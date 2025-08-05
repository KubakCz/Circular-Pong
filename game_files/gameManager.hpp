#pragma once

#include <functional>

namespace game
{
    enum GameState
    {
        game,
        gameOver,
        win
    };

    class GameManager
    {
        bool _debug = false;
        bool _paused = false;
        GameState _state = game;
        unsigned int _lives = 3;
        unsigned int _score = 0;

    public:
        static GameManager *instance;

        GameManager();
        GameManager(const GameManager &gm) = delete;
        GameManager(GameManager &&gm) = delete;
        ~GameManager();

#pragma region getters and setters
        bool debug() const
        {
            return _debug;
        }

        void paused(bool newValue);
        bool paused() const { return _paused; }

        void gameState(GameState newState);
        GameState gameState() const { return _state; }

        void increaseScore(unsigned int score);
        unsigned int score() const { return _score; }

        void decreaseLives();
        unsigned int lives() { return _lives; }
#pragma endregion getters and setters

        void update(float deltaSeconds);

    private:
        void pauseCheck();
        void waitForInput(std::function<void()> action);
        void gameUpdate(float deltaSeconds);
        void resetGame();
    };
} // namespace game
