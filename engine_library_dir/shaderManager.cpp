#include "shaderManager.hpp"
#include <cassert>
#include <fstream>
#include <stdexcept>

namespace engine
{
    ShaderManager *ShaderManager::instance = nullptr;

    GLuint loadShader(std::filesystem::path const &path, GLenum const shader_type)
    {
        std::filesystem::path const current = std::filesystem::current_path();
        GLuint const shader = glCreateShader(shader_type);
        assert(glGetError() == 0U && shader != 0);
        std::ifstream ifs(path);
        assert(ifs.is_open());
        std::string const str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        char const *code = str.c_str();
        glShaderSource(shader, 1, &code, nullptr);
        assert(glGetError() == 0U);
        glCompileShader(shader);
        assert(glGetError() == 0U);
        return shader;
    }

    GLuint createShaderProgram(GLuint vertex_shader, GLuint fragment_shader)
    {
        GLuint program = glCreateProgram();
        assert(glGetError() == 0U && program != 0);
        glAttachShader(program, vertex_shader);
        assert(glGetError() == 0U);
        glAttachShader(program, fragment_shader);
        assert(glGetError() == 0U);
        glLinkProgram(program);
        assert(glGetError() == 0U);
        glDetachShader(program, vertex_shader);
        assert(glGetError() == 0U);
        glDetachShader(program, fragment_shader);
        assert(glGetError() == 0U);
        return program;
    }

    ShaderManager::ShaderManager(const std::filesystem::path &shaderDir)
    {
        if (instance != nullptr)
            throw std::logic_error("Instance already exists.");
        instance = this;

        GLuint object_vert = loadShader(shaderDir / "object.vert", GL_VERTEX_SHADER);
        GLuint full_screen_quad_vert = loadShader(shaderDir / "full_screen_quad.vert", GL_VERTEX_SHADER);

        GLuint normal_frag = loadShader(shaderDir / "normal.frag", GL_FRAGMENT_SHADER);

        GLuint unlit_frag = loadShader(shaderDir / "unlit.frag", GL_FRAGMENT_SHADER);
        GLuint lit_with_mask_frag = loadShader(shaderDir / "lit_with_mask.frag", GL_FRAGMENT_SHADER);

        GLuint positions_and_normal_frag = loadShader(shaderDir / "positions_and_normals.frag", GL_FRAGMENT_SHADER);
        GLuint evaluate_ssao_frag = loadShader(shaderDir / "evaluate_ssao.frag", GL_FRAGMENT_SHADER);
        GLuint blur_ssao_texture_frag = loadShader(shaderDir / "blur_ssao_texture.frag", GL_FRAGMENT_SHADER);

        GLuint alpha_mask_frag = loadShader(shaderDir / "alpha_mask.frag", GL_FRAGMENT_SHADER);
        GLuint display_textrure_frag = loadShader(shaderDir / "display_texture.frag", GL_FRAGMENT_SHADER);

        GLuint ui_vert = loadShader(shaderDir / "ui.vert", GL_VERTEX_SHADER);
        GLuint ui_frag = loadShader(shaderDir / "ui.frag", GL_FRAGMENT_SHADER);

        _normalProgram = createShaderProgram(object_vert, normal_frag);

        _unlitProgram = createShaderProgram(object_vert, unlit_frag);
        _litWithMaskProgram = createShaderProgram(object_vert, lit_with_mask_frag);

        _positionsAndNormalsProgram = createShaderProgram(object_vert, positions_and_normal_frag);
        _evaluateSSAOProgram = createShaderProgram(full_screen_quad_vert, evaluate_ssao_frag);
        _blurSSAOProgram = createShaderProgram(full_screen_quad_vert, blur_ssao_texture_frag);

        _maskProgram = createShaderProgram(object_vert, alpha_mask_frag);
        _displayTextureProgram = createShaderProgram(full_screen_quad_vert, display_textrure_frag);

        _uiProgram = createShaderProgram(ui_vert, ui_frag);

        glDeleteShader(object_vert);
        glDeleteShader(full_screen_quad_vert);

        glDeleteShader(normal_frag);

        glDeleteShader(unlit_frag);
        glDeleteShader(lit_with_mask_frag);

        glDeleteShader(positions_and_normal_frag);
        glDeleteShader(evaluate_ssao_frag);
        glDeleteShader(blur_ssao_texture_frag);

        glDeleteShader(alpha_mask_frag);
        glDeleteShader(display_textrure_frag);

        glDeleteShader(ui_vert);
        glDeleteShader(ui_frag);
    }

    ShaderManager::~ShaderManager()
    {
        if (instance == this)
            instance = nullptr;

        glDeleteProgram(_normalProgram);

        glDeleteProgram(_unlitProgram);
        glDeleteProgram(_litWithMaskProgram);

        glDeleteProgram(_positionsAndNormalsProgram);
        glDeleteProgram(_evaluateSSAOProgram);
        glDeleteProgram(_blurSSAOProgram);

        glDeleteProgram(_maskProgram);
        glDeleteProgram(_displayTextureProgram);

        glDeleteProgram(_uiProgram);
    }
} // namespace engine