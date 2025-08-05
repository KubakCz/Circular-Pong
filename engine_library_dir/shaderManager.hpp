#pragma once

#include "glad/glad.h"
#include <filesystem>

namespace engine
{
    class ShaderManager
    {
        // Debug programs
        GLuint _normalProgram;

        // Lighting programs
        GLuint _unlitProgram;
        GLuint _litWithMaskProgram;

        // SSAO programs
        GLuint _positionsAndNormalsProgram;
        GLuint _evaluateSSAOProgram;
        GLuint _blurSSAOProgram;

        // Other
        GLuint _maskProgram;
        GLuint _displayTextureProgram;

        // UI
        GLuint _uiProgram;

    public:
        static ShaderManager *instance;

        ShaderManager(const std::filesystem::path &shaderDir);
        ShaderManager(const ShaderManager &sm) = delete;
        ShaderManager(ShaderManager &&sm) = delete;
        ~ShaderManager();

        GLuint normalProgram() const { return _normalProgram; }

        GLuint unilitProgram() const { return _unlitProgram; }
        GLuint litWithMaskProgram() const { return _litWithMaskProgram; }

        GLuint positionsAndNormalsProgram() const { return _positionsAndNormalsProgram; }
        GLuint evaluateSSAOProgram() const { return _evaluateSSAOProgram; }
        GLuint blurSSAOProgram() const { return _blurSSAOProgram; }

        GLuint maskProgram() const { return _maskProgram; }
        GLuint displayTextureProgram() const { return _displayTextureProgram; }

        GLuint uiProgram() const { return _uiProgram; }
    };
} // namespace engine