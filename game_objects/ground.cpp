#include "ground.hpp"

#include "../game_data_files/geometries.hpp"
#include "../game_data_files/materials.hpp"
#include "../engine_library_dir/textureManager.hpp"

namespace gameObjects
{
    Ground::Ground() : GameObjectBase(&gameData::Geometries::instance->ground, &gameData::Materials::instance->ground, engine::TextureManager::instance->getTexture("ground.png")) {}
} // namespace gameObjects
