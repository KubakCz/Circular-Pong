#include "screenOrientedQuad.hpp"
#include "../game_data_files/geometries.hpp"
#include "../game_files/cameraManager.hpp"

namespace gameObjects
{
    ScreenOrientedQuad::ScreenOrientedQuad(const engine::UBO<engine::MaterialData> *material, engine::Texture texture) : ScreenOrientedQuad(engine::Transform::defaultTransform, material, texture) {}
    ScreenOrientedQuad::ScreenOrientedQuad(const engine::Transform &t, const engine::UBO<engine::MaterialData> *material, engine::Texture texture) : GameObjectBase(t, &gameData::Geometries::instance->ballMaskQuad, material, texture) {}

    void ScreenOrientedQuad::render(bool bindMaterial)
    {
        math::Vec3 cPos = game::CameraManager::instance->currentCamera()->transform.position;
        math::Vec3 y = (cPos - transform.position).unit();
        math::Vec3 x = math::cross(y, math::Vec3::up).unit();
        math::Vec3 z = math::cross(x, y).unit();
        transform.rotation = math::Quaternion::fromRotMatrix(math::Mat4(x, y, z));

        GameObjectBase::render(bindMaterial);
    }
}