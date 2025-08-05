#pragma once

#include "glad/glad.h"
#include "lodepng.h"
#include "texture.hpp"
#include <filesystem>
#include <iostream>
#include <vector>
#include <map>

namespace engine
{
    class TextureManager
    {
        /// @brief Stores loaded textures. Key: fileName, Value: textureID
        std::map<std::filesystem::path, Texture> textures;

        std::filesystem::path textureDir;

    public:
        static TextureManager *instance;

        /// @brief Create new texture manager.
        /// @param textureDir Path to the directory with textures.
        TextureManager(const std::filesystem::path &textureDir);

        /// @brief Create new texture manager and load textures.
        /// @param textureDir Path to the directory with textures.
        /// @param textureNames Vector of paths to the textures from texture directory.
        TextureManager(const std::filesystem::path &textureDir, const std::vector<std::filesystem::path> &paths);

        TextureManager(const TextureManager &tm) = delete;
        TextureManager(TextureManager &&tm) = delete;

        ~TextureManager();

        /// @brief Get textureID. The texture will be loaded, if it is not already.
        /// @param textuerName Path to the texture from texture directory.
        /// @return TextureID
        Texture getTexture(const std::filesystem::path &textuerName);

        /// @brief Unloads the texture.
        void unloadTexture(const std::filesystem::path &textuerName);

        /// @brief True, if the texture is already loaded.
        bool isLoaded(const std::filesystem::path &textuerName);
    };
} // namespace engine