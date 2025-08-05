#include "geometryGenerator.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

namespace gameData
{
    engine::Geometry GeometryGenerator::Circle(float radius, int segments)
    {
        assert(segments >= 3);

        std::vector<engine::Geometry::Vertex> vertices;
        vertices.reserve(segments + 1);
        std::vector<uint32_t> indices;
        indices.reserve(segments + 2);

        // mid vertex
        vertices.push_back(
            engine::Geometry::Vertex(
                math::Vec3::zero,
                math::Vec3::up,
                math::Vec2::one / 2));
        indices.push_back(0);

        for (int i = 0; i < segments; ++i)
        {
            float theta = (float)(i * 2 * M_PI / segments);
            float x = std::cosf(theta);
            float z = std::sinf(theta);
            vertices.push_back(
                engine::Geometry::Vertex(
                    math::Vec3(x * radius, 0, z * radius),
                    math::Vec3::up,
                    math::Vec2((x + 1) / 2, (z + 1) / 2)) // remap [-1;1] -> [0;1]
            );
            indices.push_back(i + 1);
        }

        // enclose circle
        indices.push_back(1);

        assert(vertices.size() == segments + 1);
        assert(indices.size() == segments + 2);
        return engine::Geometry(GL_TRIANGLE_FAN, vertices, indices);
    }

    engine::Geometry GeometryGenerator::Sphere(float radius, int segments, int rings)
    {
        assert(segments >= 3);
        assert(rings >= 1);

        std::vector<engine::Geometry::Vertex> vertices;
        vertices.reserve(2 + rings * segments);
        std::vector<uint32_t> indices;
        indices.reserve((segments - 1) * 2 + 2 * segments + 5 + (2 * segments + 4) * (rings - 1));

        // up cap
        vertices.push_back(
            engine::Geometry::Vertex(
                math::Vec3::up * radius,
                math::Vec3::up));
        float theta = (float)M_PI / (rings + 1);
        float thetaSinRad = std::sinf(theta) * radius;
        float y = std::cosf(theta) * radius;
        for (int i = 0; i < segments; ++i)
        {
            float phi = 2 * (float)M_PI * i / segments;
            auto pos = math::Vec3(std::cosf(phi) * thetaSinRad, y, std::sinf(phi) * thetaSinRad);
            vertices.push_back(
                engine::Geometry::Vertex(
                    pos,
                    pos.unit()));
            indices.push_back(0);
            indices.push_back(i + 1);
        }
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(1);

        // strips
        for (int ring = 2; ring <= rings; ++ring)
        {
            theta = ring * (float)M_PI / (rings + 1);
            thetaSinRad = std::sinf(theta) * radius;
            y = std::cosf(theta) * radius;
            for (int i = 0; i < segments; ++i)
            {
                float phi = 2 * (float)M_PI * i / segments;
                auto pos = math::Vec3(std::cosf(phi) * thetaSinRad, y, std::sinf(phi) * thetaSinRad);
                vertices.push_back(
                    engine::Geometry::Vertex(
                        pos,
                        pos.unit()));
                indices.push_back((int)vertices.size() - 1);
                indices.push_back((int)vertices.size() - segments - 1);
            }
            indices.push_back((int)vertices.size() - segments);
            indices.push_back((int)vertices.size() - 2 * segments);
            indices.push_back((int)vertices.size() - segments);
            indices.push_back((int)vertices.size() - segments);
        }

        // bottom cap
        vertices.push_back(
            engine::Geometry::Vertex(
                math::Vec3::down * radius,
                math::Vec3::down));
        for (int i = 0; i < segments - 1; ++i)
        {
            indices.push_back((int)vertices.size() - 1);
            indices.push_back((int)vertices.size() - segments + i);
        }
        indices.push_back((int)vertices.size() - 1);
        indices.push_back((int)vertices.size() - segments - 1);

        assert(vertices.size() == 2 + rings * segments);
        assert(indices.size() == (segments - 1) * 2 + 2 * segments + 5 + (2 * segments + 4) * (rings - 1));
        return engine::Geometry(GL_TRIANGLE_STRIP, vertices, indices);
    }

    /// @brief Create quad from two trinagles. Points are sharing one normal and are given in counter-clockwise order.
    void AddQuad(std::vector<engine::Geometry::Vertex> &vertices,
                 std::vector<uint32_t> &indices,
                 math::Vec3 normal,
                 math::Vec3 positions[4])
    {
        int offset = (int)vertices.size();

        for (int i = 0; i < 4; i++)
        {
            vertices.push_back(
                engine::Geometry::Vertex(
                    positions[i],
                    normal));
        }

        indices.push_back(0 + offset);
        indices.push_back(1 + offset);
        indices.push_back(2 + offset);
        indices.push_back(2 + offset);
        indices.push_back(3 + offset);
        indices.push_back(0 + offset);
    }

    engine::Geometry GeometryGenerator::Cube(float size)
    {
        float size_2 = size / 2;
        std::vector<engine::Geometry::Vertex> vertices;
        vertices.reserve(6 * 4);
        std::vector<uint32_t> indices;
        vertices.reserve(6 * 6);

        math::Vec3 positions[4] = {
            math::Vec3(-1, -1, -1) * size_2,
            math::Vec3(1, -1, -1) * size_2,
            math::Vec3(1, 1, -1) * size_2,
            math::Vec3(-1, 1, -1) * size_2,
        };
        AddQuad(vertices, indices, math::Vec3::back, positions);

        positions[0] = math::Vec3(-1, 1, 1) * size_2;
        positions[1] = math::Vec3(1, 1, 1) * size_2;
        positions[2] = math::Vec3(1, -1, 1) * size_2;
        positions[3] = math::Vec3(-1, -1, 1) * size_2;
        AddQuad(vertices, indices, math::Vec3::forward, positions);

        positions[0] = math::Vec3(1, -1, 1) * size_2;
        positions[1] = math::Vec3(1, 1, 1) * size_2;
        positions[2] = math::Vec3(1, 1, -1) * size_2;
        positions[3] = math::Vec3(1, -1, -1) * size_2;
        AddQuad(vertices, indices, math::Vec3::right, positions);

        positions[0] = math::Vec3(-1, -1, -1) * size_2;
        positions[1] = math::Vec3(-1, 1, -1) * size_2;
        positions[2] = math::Vec3(-1, 1, 1) * size_2;
        positions[3] = math::Vec3(-1, -1, 1) * size_2;
        AddQuad(vertices, indices, math::Vec3::left, positions);

        positions[0] = math::Vec3(-1, 1, -1) * size_2;
        positions[1] = math::Vec3(1, 1, -1) * size_2;
        positions[2] = math::Vec3(1, 1, 1) * size_2;
        positions[3] = math::Vec3(-1, 1, 1) * size_2;
        AddQuad(vertices, indices, math::Vec3::up, positions);

        positions[0] = math::Vec3(-1, -1, 1) * size_2;
        positions[1] = math::Vec3(1, -1, 1) * size_2;
        positions[2] = math::Vec3(1, -1, -1) * size_2;
        positions[3] = math::Vec3(-1, -1, -1) * size_2;
        AddQuad(vertices, indices, math::Vec3::down, positions);

        assert(vertices.size() == 6 * 4);
        assert(indices.size() == 6 * 6);
        return engine::Geometry(GL_TRIANGLES, vertices, indices);
    }

    void BrickTopFace(std::vector<engine::Geometry::Vertex> &vertices,
                      std::vector<uint32_t> &indices,
                      math::Vec3 normal,
                      float yOffset,
                      float angle,
                      float innerRadius,
                      float outerRadius,
                      int segments)
    {
        for (int i = 0; i <= segments; ++i)
        {
            float phi = angle * i / segments - angle / 2;
            float x = std::cosf(phi);
            float z = std::sinf(phi);
            vertices.push_back(
                engine::Geometry::Vertex(
                    math::Vec3(x * innerRadius, yOffset, z * innerRadius),
                    normal));
            vertices.push_back(
                engine::Geometry::Vertex(
                    math::Vec3(x * outerRadius, yOffset, z * outerRadius),
                    normal));
            indices.push_back((uint32_t)vertices.size() - 2);
            indices.push_back((uint32_t)vertices.size() - 1);
        }
    }

    /// @brief Create quad from two trinagles in GL_TRIANGLE_STRIP mode. Points are sharing one normal and are given in counter-clockwise order.
    void AddQuadStrip(std::vector<engine::Geometry::Vertex> &vertices,
                      std::vector<uint32_t> &indices,
                      math::Vec3 normal,
                      math::Vec3 positions[4])
    {
        int offset = (int)vertices.size();

        for (int i = 0; i < 4; i++)
        {
            vertices.push_back(
                engine::Geometry::Vertex(
                    positions[i],
                    normal));
        }
        indices.push_back(0 + offset);
        indices.push_back(1 + offset);
        indices.push_back(3 + offset);
        indices.push_back(2 + offset);
    }

    /// @brief Generation of curved strip for brick inner and outer faces.
    void CurvedStrip(std::vector<engine::Geometry::Vertex> &vertices,
                     std::vector<uint32_t> &indices,
                     bool normalToCenter,
                     float angle,
                     float radius,
                     float height,
                     int segments)
    {
        float height_2 = height / 2;
        float normalMult = normalToCenter ? -1.0f : 1.0f;
        for (int i = 0; i <= segments; ++i)
        {
            float phi = angle * i / segments - angle / 2;
            float x = std::cosf(phi);
            float z = std::sinf(phi);
            auto pos = math::Vec3(x * radius, height_2, z * radius);
            auto n = math::Vec3(x, 0, z) * normalMult;
            vertices.push_back(engine::Geometry::Vertex(pos, n));
            pos.y() = -height_2;
            vertices.push_back(engine::Geometry::Vertex(pos, n));
            indices.push_back((int)vertices.size() - 2);
            indices.push_back((int)vertices.size() - 1);
        }
    }

    engine::Geometry GeometryGenerator::Brick(float innerRadius, float angle, float width, float height, int segments)
    {
        float height_2 = height / 2;
        float outerRadius = innerRadius + width;

        std::vector<engine::Geometry::Vertex> vertices;
        // vertices.reserve(6 * 4);
        std::vector<uint32_t> indices;
        // vertices.reserve(6 * 6);

        // top face
        BrickTopFace(vertices, indices, math::Vec3::up, height_2, angle, innerRadius, outerRadius, segments);

        // left faces
        float phi = angle / 2;
        float x = std::cosf(phi);
        float z = std::sinf(phi);
        math::Vec3 positions[4] = {
            math::Vec3(x * outerRadius, height_2, z * outerRadius),
            math::Vec3(x * outerRadius, -height_2, z * outerRadius),
            math::Vec3(x * innerRadius, -height_2, z * innerRadius),
            math::Vec3(x * innerRadius, height_2, z * innerRadius),
        };
        AddQuadStrip(vertices, indices, math::Vec3(-z, 0, x), positions);

        // inner face
        CurvedStrip(vertices, indices, true, -angle, innerRadius, height, segments);

        // right face
        positions[0] = math::Vec3(x * innerRadius, -height_2, -z * innerRadius);
        positions[1] = math::Vec3(x * outerRadius, -height_2, -z * outerRadius);
        positions[2] = math::Vec3(x * outerRadius, height_2, -z * outerRadius);
        positions[3] = math::Vec3(x * innerRadius, height_2, -z * innerRadius);
        AddQuadStrip(vertices, indices, math::Vec3(-z, 0, -x), positions);

        // outer face
        CurvedStrip(vertices, indices, false, angle, outerRadius, height, segments);

        // bottom face
        indices.push_back((int32_t)indices.size() - 1);
        indices.push_back((int32_t)indices.size() - 1); // invert winding order
        BrickTopFace(vertices, indices, math::Vec3::down, -height_2, -angle, innerRadius, outerRadius, segments);

        return engine::Geometry(GL_TRIANGLE_STRIP, vertices, indices);
    }

    engine::Geometry GeometryGenerator::Quad(float size)
    {
        float s_2 = size / 2;

        std::vector<engine::Geometry::Vertex> vertices = {
            engine::Geometry::Vertex(
                math::Vec3(-s_2, 0, -s_2),
                math::Vec3::up,
                math::Vec2(0, 0)),
            engine::Geometry::Vertex(
                math::Vec3(s_2, 0, -s_2),
                math::Vec3::up,
                math::Vec2(1, 0)),
            engine::Geometry::Vertex(
                math::Vec3(s_2, 0, s_2),
                math::Vec3::up,
                math::Vec2(1, 1)),
            engine::Geometry::Vertex(
                math::Vec3(-s_2, 0, s_2),
                math::Vec3::up,
                math::Vec2(0, 1))};

        std::vector<uint32_t> indices = {0, 1, 3, 2};

        assert(vertices.size() == 4);
        assert(indices.size() == 4);

        return engine::Geometry(GL_TRIANGLE_STRIP, vertices, indices);
    }
} // namespace gameData
