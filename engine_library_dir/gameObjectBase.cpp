#include "gameObjectBase.hpp"
#include "glad/glad.h"

namespace engine
{
    GameObjectBase::GameObjectBase() : GameObjectBase(engine::Transform::defaultTransform) {}
    GameObjectBase::GameObjectBase(const Transform &t) : GameObjectBase(t, nullptr, nullptr, Texture::Empty) {}
    GameObjectBase::GameObjectBase(const Geometry *geometry, const UBO<MaterialData> *material, Texture texture) : GameObjectBase(Transform::defaultTransform, geometry, material, texture) {}
    GameObjectBase::GameObjectBase(const Transform &t, const Geometry *geometry, const UBO<MaterialData> *material, Texture texture) : transform(t),
                                                                                                                                       geometry(geometry),
                                                                                                                                       material(material),
                                                                                                                                       texture(texture),
                                                                                                                                       modelData() {}

    void GameObjectBase::update(float timeDelta)
    {
    }

    void GameObjectBase::render(bool bindMaterial)
    {
        if (material != nullptr && geometry != nullptr)
        {
            if (bindMaterial)
            {
                material->bind();
                if (material->data->hasTexture)
                    texture.bind(0);
            }

            modelData.data->model = transform.modelMatrix();
            modelData.bind();

            geometry->draw();
        }
    }
} // namespace engine
