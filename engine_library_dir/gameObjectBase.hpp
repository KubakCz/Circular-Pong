#pragma once

#include "uniforms.hpp"
#include "geometry.hpp"
#include "transform.hpp"
#include "texture.hpp"
#include <memory>

namespace engine
{
    class GameObjectBase
    {
    protected:
        UBO<ModelData> modelData;

    public:
        const Geometry *geometry;
        const UBO<MaterialData> *material;
        Texture texture;
        Transform transform;

    public:
        GameObjectBase();
        GameObjectBase(const Transform &t);
        GameObjectBase(const Geometry *geometry, const UBO<MaterialData> *material, Texture texture = Texture::Empty);
        GameObjectBase(const Transform &t, const Geometry *geometry, const UBO<MaterialData> *material, Texture texture = Texture::Empty);

        virtual ~GameObjectBase() = default;

        virtual void update(float timeDelta);
        virtual void render(bool bindMaterial = true);
    };
} // namespace engine
