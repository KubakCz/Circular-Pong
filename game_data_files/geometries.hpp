#pragma once

#include "geometryGenerator.hpp"
#include "environmentProperties.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>

namespace gameData
{
    class Geometries
    {
    public:
        static Geometries *instance;

        Geometries()
        {
            if (instance == nullptr)
                instance = this;
        }

        const engine::Geometry ball = GeometryGenerator::Sphere(
            EnvironmentProperties::ballRadius,
            16,
            8);

        const engine::Geometry brick = GeometryGenerator::Brick(
            EnvironmentProperties::brickInnerRadius,
            EnvironmentProperties::brickSize,
            EnvironmentProperties::brickWidth,
            EnvironmentProperties::brickHeight,
            16);

        const engine::Geometry paddle = GeometryGenerator::Brick(
            EnvironmentProperties::paddleInnerRadius,
            EnvironmentProperties::paddleSize,
            EnvironmentProperties::paddleWidth,
            EnvironmentProperties::paddleHeight,
            32);

        const engine::Geometry ground = GeometryGenerator::Circle(
            EnvironmentProperties::groundRadius,
            64);

        const engine::Geometry ballMaskQuad = GeometryGenerator::Quad(
            1);
    };
} // namespace gameData
