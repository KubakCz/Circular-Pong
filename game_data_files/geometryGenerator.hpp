#pragma once

#include "../engine_library_dir/geometry.hpp"

namespace gameData
{
    class GeometryGenerator
    {
    public:
        GeometryGenerator() = delete;

        static engine::Geometry Circle(float radius, int segments);
        static engine::Geometry Sphere(float radius, int segments, int rings);
        static engine::Geometry Cube(float size);
        static engine::Geometry Brick(float innerRadius, float angle, float width, float height, int segments);
        static engine::Geometry Quad(float size);
    };
} // namespace gameData
