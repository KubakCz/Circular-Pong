#include "texture.hpp"

namespace engine
{
    const Texture Texture::Empty = Texture();

    Texture::Texture(GLuint id, unsigned int width, unsigned int height) : _id(id),
                                                                           _width(width),
                                                                           _height(height){};

    void Texture::setTextureParameters(GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter) const
    {
        setTextureParameters(_id, wrap_s, wrap_t, min_filter, mag_filter);
    }

    void Texture::setTextureParameters(size_t n, Texture *textures, GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter)
    {
        for (int i = 0; i < n; ++i)
        {
            setTextureParameters(textures->_id, wrap_s, wrap_t, min_filter, mag_filter);
        }
    }

    void Texture::setTextureParameters(GLuint texture, GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter)
    {
        // Based on PV227 lecture 04
        glTextureParameteri(texture, GL_TEXTURE_WRAP_S, wrap_s);
        glTextureParameteri(texture, GL_TEXTURE_WRAP_T, wrap_t);
        glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, min_filter);
        glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, mag_filter);
    }

    void Texture::setTextureParameters(size_t n, GLuint *textures, GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter)
    {
        for (int i = 0; i < n; ++i)
        {
            setTextureParameters(*textures, wrap_s, wrap_t, min_filter, mag_filter);
            ++textures;
        }
    }
} // namespace engine
