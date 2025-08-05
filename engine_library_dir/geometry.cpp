#include "geometry.hpp"

namespace engine
{
    Geometry::Geometry(GLenum mode, const std::vector<Geometry::Vertex> &data, const std::vector<uint32_t> &indices) : mode(mode),
                                                                                                                       elementCount((GLsizei)indices.size())
    {
        // create vao
        glCreateVertexArrays(1, &vao);

        // create vertex buffer
        glCreateBuffers(1, &vertex_vbo);
        glNamedBufferStorage(vertex_vbo, data.size() * sizeof(Vertex), data.data(), NULL);
        glVertexArrayVertexBuffer(vao, 0, vertex_vbo, 0, sizeof(Vertex));

        // position
        glEnableVertexArrayAttrib(vao, 0);
        glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vao, 0, 0);

        // normal
        glEnableVertexArrayAttrib(vao, 1);
        glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, sizeof(math::Vec3));
        glVertexArrayAttribBinding(vao, 1, 0);

        // tex_coord
        glEnableVertexArrayAttrib(vao, 2);
        glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(math::Vec3));
        glVertexArrayAttribBinding(vao, 2, 0);

        // indices buffer
        glCreateBuffers(1, &indices_vbo);
        glNamedBufferStorage(indices_vbo, indices.size() * sizeof(uint32_t), indices.data(), NULL);
        glVertexArrayElementBuffer(vao, indices_vbo);
    }

    Geometry::~Geometry()
    {
        glDeleteBuffers(1, &vertex_vbo);
        glDeleteBuffers(1, &indices_vbo);

        glDeleteVertexArrays(1, &vao);
    }

    void Geometry::draw() const
    {
        glBindVertexArray(vao);
        glDrawElements(mode, elementCount, GL_UNSIGNED_INT, 0);
    }

} // namespace engine
