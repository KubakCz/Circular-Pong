#pragma once

#include "../engine_library_dir/camera.hpp"

namespace gameData
{
    class EnvironmentProperties
    {
    public:
        EnvironmentProperties() = delete;

        // ball
        static const float ballRadius;
        static const math::Vec3 initBallPosition;
        static const float maxBallLaunchAngle;

        // bricks
        static const float brickInnerRadius;
        static const float brickWidth;
        static const float brickHeight;
        static const int bricksInCircle;
        static const int bricksInStack;
        static const float brickSize;

        // paddle
        static const float paddleInnerRadius;
        static const float paddleWidth;
        static const float paddleHeight;
        static const float paddleSize;

        // ground
        static const float groundRadius;
    };
} // namespace gameData