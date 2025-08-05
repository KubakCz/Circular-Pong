#pragma once

#include "glad/glad.h"
#include "../math_library_dir/mat4.hpp"
#include "../math_library_dir/vector.hpp"
#include <memory>
#include <vector>

namespace engine
{
    template <class ubo_t>
    class UBO
    {
        GLbitfield namedBufferStorageFlags;
        GLuint buffer;

    public:
        std::unique_ptr<ubo_t> data;

        UBO();
        UBO(std::unique_ptr<ubo_t> ubo);
        UBO(GLbitfield namedBufferStorageFlags);
        UBO(std::unique_ptr<ubo_t> ubo, GLbitfield namedBufferStorageFlags);

        /// @brief Create new buffer object with the same data as ubo.
        UBO(const UBO<ubo_t> &ubo);

        ~UBO();

        void bind() const;
        void bind(GLuint index) const;
    };

    const GLuint CAMERA_DEFAULT_BIND_INDEX = 0;
    const GLuint MODEL_DEFAULT_BIND_INDEX = 1;
    const GLuint MATERIAL_DEFAULT_BIND_INDEX = 2;
    const GLuint LIGHTS_DEFAULT_BIND_INDEX = 3;
    const GLuint UI_TRANSFORM_DEFAULT_BIND_INDEX = 0;
    const GLuint UI_SUBTEXTURE_DEFAULT_BIND_INDEX = 1;

#pragma region UBO

    template <class ubo_t>
    UBO<ubo_t>::UBO() : UBO(std::make_unique<ubo_t>(), GL_DYNAMIC_STORAGE_BIT)
    {
    }

    template <class ubo_t>
    UBO<ubo_t>::UBO(std::unique_ptr<ubo_t> ubo) : UBO(move(ubo), GL_DYNAMIC_STORAGE_BIT) {}

    template <class ubo_t>
    UBO<ubo_t>::UBO(GLbitfield namedBufferStorageFlags) : UBO(std::make_unique<ubo_t>(), namedBufferStorageFlags) {}

    template <class ubo_t>
    UBO<ubo_t>::UBO(std::unique_ptr<ubo_t> ubo, GLbitfield namedBufferStorageFlags) : data(move(ubo)), namedBufferStorageFlags(namedBufferStorageFlags)
    {
        glCreateBuffers(1, &buffer);
        assert(buffer != 0);
        glNamedBufferStorage(buffer, sizeof(ubo_t), data.get(), namedBufferStorageFlags);
    }

    template <class ubo_t>
    UBO<ubo_t>::UBO(const UBO<ubo_t> &ubo) : UBO(std::make_unique<ubo_t>(*(ubo.data.get())), ubo.namedBufferStorageFlags) {}

    template <class ubo_t>
    UBO<ubo_t>::~UBO()
    {
        glDeleteBuffers(1, &buffer);
    }

    template <class ubo_t>
    void UBO<ubo_t>::bind(GLuint index) const
    {
        glNamedBufferSubData(buffer, 0, sizeof(ubo_t), data.get());
        glBindBufferBase(GL_UNIFORM_BUFFER, index, buffer);
    }

#pragma endregion UBO

    struct CameraData
    {
        math::Mat4 projection;
        math::Mat4 model;
        math::Vec3 eyePosition;
        float _pad1;

        CameraData() = default;
        CameraData(const CameraData &ubo) = default;
        CameraData(math::Mat4 projection, math::Mat4 model, math::Vec3 eyePosition);
    };

    struct ModelData
    {
        math::Mat4 model;

        ModelData() = default;
        ModelData(const ModelData &ubo) = default;
        ModelData(math::Mat4 model);
    };

    struct MaterialData
    {
        math::Vec3 ambient;
        int hasTexture;
        math::Vec3 diffuse;
        float alpha = 1;
        math::Vec3 specular;
        float shininess;

        MaterialData() = default;
        MaterialData(const MaterialData &ubo) = default;
        /// @brief Create material with the same ambient and diffuse color and no shininess. Last component of color is used as alpha.
        /// @param color RGBA [0-1]
        MaterialData(math::Vec4 color);
        /// @brief Create material with the same ambient and diffuse color (diffuse parameter) and separate specular color.
        /// @param diffuse RGB [0-1]
        /// @param specular RGB [0-1]
        /// @param shininess
        /// @param hasTexture
        MaterialData(math::Vec3 diffuse, math::Vec3 specular, float shininess, bool hasTexture);
        /// @brief Create material with the same ambient and diffuse color (diffuse parameter) and separate specular color.
        /// @param diffuse RGB [0-1]
        /// @param specular RGB [0-1]
        /// @param shininess
        /// @param alpha [0-1]
        /// @param hasTexture
        MaterialData(math::Vec3 diffuse, math::Vec3 specular, float shininess, float alpha, bool hasTexture);
        /// @brief Create material with different ambient, diffuse and specular components.
        /// @param ambient RGB [0-1]
        /// @param diffuse RGB [0-1]
        /// @param specular RGB [0-1]
        /// @param shininess
        /// @param alpha [0-1]
        /// @param hasTexture
        MaterialData(math::Vec3 ambient, math::Vec3 diffuse, math::Vec3 specular, float shininess, float alpha, bool hasTexture);

        /// @brief Set ambient and diffuse color and alpha.
        /// @param col RGBA [0-1]
        void Color(math::Vec4 col);
    };

    struct LightData
    {
        math::Vec4 position;
        math::Vec3 ambient;
        float _pad1;
        math::Vec3 diffuse;
        float _pad2;
        math::Vec3 specular;
        float _pad3;

        LightData() = default;
        LightData(const LightData &ubo) = default;
        LightData(const math::Vec3 &position, const math::Vec3 col, float ambientStrength, float diffuseStrength, float specularStrength);
        LightData(const math::Vec3 &position, const math::Vec3 &ambient, const math::Vec3 &diffuse, const math::Vec3 &specular);
    };

    struct SunData : public LightData
    {
        SunData() = default;
        SunData(const SunData &ubo) = default;
        SunData(const math::Vec3 &direction, const math::Vec3 col, float ambientStrength, float diffuseStrength, float specularStrength);
        SunData(const math::Vec3 &direction, const math::Vec3 &ambient, const math::Vec3 &diffuse, const math::Vec3 &specular);
    };

    class LightsData
    {
        friend class UBO<LightsData>;

        int _maxSize;
        std::vector<LightData> data;

    public:
        LightsData(const LightsData &lightsData) = default;
        LightsData(int maxLights);
        LightsData(int maxLights, const std::vector<LightData> &lights);
        LightsData(int maxLights, std::vector<LightData> &&lights);

        int size() { return (int)data.size(); }
        int maxSize() { return _maxSize; }

        void pushBack(const LightData &light);
        void erase(int i);

        LightData &operator[](int i) { return data[i]; }
    };

    template <>
    UBO<LightsData>::UBO();

    template <>
    UBO<LightsData>::UBO(std::unique_ptr<LightsData> ubo, GLbitfield namedBufferStorageFlags);
} // namespace engine
