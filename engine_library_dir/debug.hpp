#pragma once

#include "glad/glad.h"
#include <memory>

#include "transform.hpp"
#include "geometry.hpp"
#include "uniforms.hpp"

namespace engine
{

    class Debug
    {
        static std::unique_ptr<UBO<ModelData>> modelUBO;
        static std::unique_ptr<UBO<MaterialData>> colorUBO;
        static void bindUBOs(math::Mat4 model, math::Vec4 col);

        static std::unique_ptr<Geometry> line_geometry;
        static const Geometry &get_line_geometry();

    public:
        Debug() = delete;

        static void drawLine(const math::Vec3 &a, const math::Vec3 &b, const math::Vec4 &col);
        static void drawLine(const math::Vec3 &a, const math::Vec3 &b, const math::Vec4 &col, const Transform &t);

        static void drawAxis();
        static void drawAxis(const Transform &t);

        static void drawCross(const math::Vec3 &pos, float size, const math::Vec4 &col);
    };
}