#pragma once

#include "glad/glad.h"
#include "../math_library_dir/vector.hpp"
#include <vector>

namespace engine
{
    class Geometry
    {
        GLenum mode;          // drawing mode
        GLsizei elementCount; // number of elements to be drawn (number of indices)
        GLuint vertex_vbo;    // buffer with vertex data
        GLuint indices_vbo;   // buffer with indices
        GLuint vao;           // vertex array object

    public:
        struct Vertex
        {
            math::Vec3 position;
            math::Vec3 normal;
            math::Vec2 tex_coord;

            Vertex(const math::Vec3 &position, const math::Vec3 &normal) : Vertex(position, normal, math::Vec2::zero){};
            Vertex(const math::Vec3 &position, const math::Vec3 &normal, const math::Vec2 &tex_coord) : position(position),
                                                                                                        normal(normal),
                                                                                                        tex_coord(tex_coord){};
        };

        /// @param mode drawing mode
        /// @param data vetor of vertices
        /// @param indices  vector of indices
        Geometry(GLenum mode, const std::vector<Geometry::Vertex> &data, const std::vector<uint32_t> &indices);

        ~Geometry();

        /// @brief Draw the geometry.
        void draw() const;
    };
} // namespace engine
