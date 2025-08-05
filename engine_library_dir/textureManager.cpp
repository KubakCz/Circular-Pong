#include "textureManager.hpp"

#include <cassert>
#include <stdexcept>

namespace engine
{
    TextureManager *TextureManager::instance = nullptr;

    Texture loadTexture(std::filesystem::path const &path)
    {
        std::vector<unsigned char> texels;
        unsigned int width, height;
        unsigned int error_code = lodepng::decode(texels, width, height, path.string(), LCT_RGBA);
        assert(error_code == 0);

        // flip the image vertically
        for (unsigned int lo = 0, hi = height - 1; lo < hi; ++lo, --hi)
            for (unsigned int *lo_ptr = (unsigned int *)texels.data() + lo * width,
                              *lo_end = lo_ptr + width,
                              *hi_ptr = (unsigned int *)texels.data() + hi * width;
                 lo_ptr != lo_end; ++lo_ptr, ++hi_ptr)
                std::swap(*lo_ptr, *hi_ptr);

        GLuint texture;
        glGenTextures(1, &texture);
        assert(glGetError() == 0U);
        glBindTexture(GL_TEXTURE_2D, texture);
        assert(glGetError() == 0U);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *)texels.data());
        assert(glGetError() == 0U);
        glGenerateMipmap(GL_TEXTURE_2D);
        assert(glGetError() == 0U);

        Texture t = Texture(texture, width, height);
        t.setTextureParameters(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
        return t;
    }

    TextureManager::TextureManager(const std::filesystem::path &textureDir) : textureDir(textureDir)
    {
        if (instance == nullptr)
            instance = this;
        else
            throw std::logic_error("Instance already exists.");
    }

    TextureManager::TextureManager(const std::filesystem::path &textureDir, const std::vector<std::filesystem::path> &paths) : textureDir(textureDir)
    {
        for (const auto t : paths)
        {
            textures[t] = loadTexture(textureDir / t);
        }

        instance = this;
    }

    TextureManager::~TextureManager()
    {
        for (auto it = textures.begin(); it != textures.end(); ++it)
        {
            GLuint texture = it->second.id();
            glDeleteTextures(1, &texture);
        }

        if (instance == this)
            instance = nullptr;
    }

    Texture TextureManager::getTexture(const std::filesystem::path &textureName)
    {
        auto it = textures.find(textureName);
        if (it == textures.end()) // need to be loaded
        {
            Texture t = loadTexture(textureDir / textureName);
            textures[textureName] = t;
            return t;
        }
        else
        {
            return it->second;
        }
    }

    void TextureManager::unloadTexture(const std::filesystem::path &textuerName)
    {
        assert(textures.contains(textuerName));

        GLuint t = textures[textuerName].id();
        glDeleteTextures(1, &t);
        textures.erase(textuerName);
    }

    bool TextureManager::isLoaded(const std::filesystem::path &textuerName)
    {
        return textures.contains(textuerName);
    }
} // namespace engine