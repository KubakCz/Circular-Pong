#include "environmentProperties.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

namespace gameData
{
    // ball
    const float EnvironmentProperties::ballRadius = 0.1f;

    // bricks
    const float EnvironmentProperties::brickInnerRadius = 1.0f;
    const float EnvironmentProperties::brickWidth = EnvironmentProperties::ballRadius * 2.0f;
    const float EnvironmentProperties::brickHeight = EnvironmentProperties::brickWidth;
    const int EnvironmentProperties::bricksInCircle = 12; // should be even because of colors
    const int EnvironmentProperties::bricksInStack = 5;
    const float EnvironmentProperties::brickSize = 2 * (float)M_PI / EnvironmentProperties::bricksInCircle;

    // paddle
    const float EnvironmentProperties::paddleInnerRadius = EnvironmentProperties::brickInnerRadius * 5;
    const float EnvironmentProperties::paddleWidth = EnvironmentProperties::brickWidth;
    const float EnvironmentProperties::paddleHeight = EnvironmentProperties::brickHeight;
    const float EnvironmentProperties::paddleSize = (float)(2 * M_PI / (3 * 3));

    // ground
    const float EnvironmentProperties::groundRadius = EnvironmentProperties::paddleInnerRadius + EnvironmentProperties::paddleWidth * 2.0f;

    // ball
    const math::Vec3 EnvironmentProperties::initBallPosition = math::Vec3(0, ballRadius, -EnvironmentProperties::paddleInnerRadius + 1);
    const float EnvironmentProperties::maxBallLaunchAngle = std::atan2f(EnvironmentProperties::brickInnerRadius + EnvironmentProperties::brickWidth, -EnvironmentProperties::initBallPosition.z());
} // namespace gameData
