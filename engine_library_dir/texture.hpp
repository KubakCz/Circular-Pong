#pragma once

#include "glad/glad.h"

namespace engine
{
    class Texture
    {
        GLuint _id;
        unsigned int _width;
        unsigned int _height;

    public:
        Texture() = default;
        Texture(GLuint id, unsigned int width, unsigned int height);

        GLuint id() { return _id; }
        unsigned int width() { return _width; }
        unsigned int height() { return _height; }

        void bind(GLuint unit) const
        {
            glBindTextureUnit(unit, _id);
        };

        void setTextureParameters(GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter) const;
        static void setTextureParameters(size_t n, Texture *textures, GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter);
        static void setTextureParameters(GLuint texture, GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter);
        static void setTextureParameters(size_t n, GLuint *textures, GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter);

        static const Texture Empty;
    };
} // namespace engine
