#pragma once

#include "../engine_library_dir/gameObjectBase.hpp"
#include "../engine_library_dir/camera.hpp"

namespace gameObjects
{
    class ScreenOrientedQuad : public engine::GameObjectBase
    {
    public:
        ScreenOrientedQuad(const engine::UBO<engine::MaterialData> *material, engine::Texture texture = engine::Texture::Empty);
        ScreenOrientedQuad(const engine::Transform &t, const engine::UBO<engine::MaterialData> *material, engine::Texture texture = engine::Texture::Empty);

        void render(bool bindMaterial = true) override;
    };
} // namespace gameObjects
