#include "uniforms.hpp"
#include <vector>

namespace engine
{
#pragma region cameraData
    CameraData::CameraData(math::Mat4 projection, math::Mat4 model, math::Vec3 eyePosition) : projection(projection),
                                                                                              model(model),
                                                                                              eyePosition(eyePosition){};

    template <>
    void UBO<CameraData>::bind() const
    {
        bind(CAMERA_DEFAULT_BIND_INDEX);
    }
#pragma endregion cameraData

#pragma region modelData
    ModelData::ModelData(math::Mat4 model) : model(model){};

    template <>
    void UBO<ModelData>::bind() const
    {
        bind(MODEL_DEFAULT_BIND_INDEX);
    }
#pragma endregion modelData

#pragma region materialData
    MaterialData::MaterialData(math::Vec4 color) : MaterialData((math::Vec3)color, math::Vec3::zero, 0, color.w(), false){};
    MaterialData::MaterialData(math::Vec3 diffuse, math::Vec3 specular, float shininess, bool hasTexture) : MaterialData(diffuse, specular, shininess, 1.0f, hasTexture) {}
    MaterialData::MaterialData(math::Vec3 diffuse, math::Vec3 specular, float shininess, float alpha, bool hasTexture) : MaterialData(diffuse, diffuse, specular, shininess, alpha, hasTexture) {}
    MaterialData::MaterialData(math::Vec3 ambient, math::Vec3 diffuse, math::Vec3 specular, float shininess, float alpha, bool hasTexture) : ambient(ambient),
                                                                                                                                             diffuse(diffuse),
                                                                                                                                             specular(specular),
                                                                                                                                             shininess(shininess),
                                                                                                                                             alpha(alpha),
                                                                                                                                             hasTexture(hasTexture) {}

    void MaterialData::Color(math::Vec4 col)
    {
        ambient = (math::Vec3)col;
        diffuse = ambient;
        alpha = col.w();
    }

    template <>
    void UBO<MaterialData>::bind() const
    {
        bind(MATERIAL_DEFAULT_BIND_INDEX);
    }
#pragma endregion materialData

#pragma region lightData
    LightData::LightData(const math::Vec3 &position, const math::Vec3 col, float ambientStrength, float diffuseStrength, float specularStrength) : LightData(position,
                                                                                                                                                             col * ambientStrength,
                                                                                                                                                             col * diffuseStrength,
                                                                                                                                                             col * specularStrength)
    {
    }
    LightData::LightData(const math::Vec3 &position, const math::Vec3 &ambient, const math::Vec3 &diffuse, const math::Vec3 &specular) : position(position.x(), position.y(), position.z(), 1),
                                                                                                                                         ambient(ambient),
                                                                                                                                         diffuse(diffuse),
                                                                                                                                         specular(specular)
    {
    }

    SunData::SunData(const math::Vec3 &direction, const math::Vec3 col, float ambientStrength, float diffuseStrength, float specularStrength) : SunData(direction,
                                                                                                                                                        col * ambientStrength,
                                                                                                                                                        col * diffuseStrength,
                                                                                                                                                        col * specularStrength)
    {
    }
    SunData::SunData(const math::Vec3 &direction, const math::Vec3 &ambient, const math::Vec3 &diffuse, const math::Vec3 &specular) : LightData(direction,
                                                                                                                                                ambient,
                                                                                                                                                diffuse,
                                                                                                                                                specular)
    {
        position.w() = 0;
    }
#pragma endregion lightData

#pragma region lightsData
    LightsData::LightsData(int maxLights) : _maxSize(maxLights)
    {
    }
    LightsData::LightsData(int maxLights, const std::vector<LightData> &lights) : _maxSize(maxLights), data(lights)
    {
    }
    LightsData::LightsData(int maxLights, std::vector<LightData> &&lights) : _maxSize(maxLights), data(lights)
    {
    }

    void LightsData::pushBack(const LightData &light)
    {
        assert(_maxSize > data.size());
        data.push_back(light);
    }

    void LightsData::erase(int i)
    {
        data.erase(data.begin() + i);
    }

    template <>
    void UBO<LightsData>::bind(GLuint index) const
    {
        int size = data->size();
        glNamedBufferSubData(buffer, 0, sizeof(int), &size);
        glNamedBufferSubData(buffer, sizeof(int) * 4, sizeof(LightData) * data->data.size(), data->data.data());

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, buffer);
    }

    template <>
    void UBO<LightsData>::bind() const
    {
        bind(LIGHTS_DEFAULT_BIND_INDEX);
    }

    template <>
    UBO<LightsData>::UBO() = delete;

    template <>
    UBO<LightsData>::UBO(std::unique_ptr<LightsData> ubo, GLbitfield namedBufferStorageFlags) : data(move(ubo)), namedBufferStorageFlags(namedBufferStorageFlags)
    {
        glCreateBuffers(1, &buffer);
        assert(buffer != 0);
        glNamedBufferStorage(buffer, sizeof(int) * 4 + sizeof(LightData) * data->maxSize(), nullptr, namedBufferStorageFlags);

        int size = data->size();
        glNamedBufferSubData(buffer, 0, sizeof(int), &size);
        glNamedBufferSubData(buffer, sizeof(int) * 4, sizeof(LightData) * data->data.size(), data->data.data());
    }
#pragma endregion lightsData
} // namespace engine