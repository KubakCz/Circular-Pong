#pragma once

#include "../engine_library_dir/uniforms.hpp"

namespace gameData
{
    class Materials
    {
    public:
        static Materials *instance;

        Materials()
        {
            if (instance == nullptr)
                instance = this;
        }

        const engine::UBO<engine::MaterialData> white = engine::UBO<engine::MaterialData>(
            std::make_unique<engine::MaterialData>(
                math::Vec3::one, math::Vec3::one, 16.0f, false));

        const engine::UBO<engine::MaterialData> whiteTextured = engine::UBO<engine::MaterialData>(
            std::make_unique<engine::MaterialData>(
                math::Vec3::one, math::Vec3::one, 16.0f, true));

        const engine::UBO<engine::MaterialData> ball = engine::UBO<engine::MaterialData>(
            std::make_unique<engine::MaterialData>(
                math::Vec3::one * 0.7f, math::Vec3::one, 128.0f, false));

        const engine::UBO<engine::MaterialData> paddle = engine::UBO<engine::MaterialData>(
            std::make_unique<engine::MaterialData>(
                math::Vec3(25.0f / 255, 83.0f / 255, 95.0f / 255), math::Vec3::one, 32.0f, false));

        const std::vector<engine::UBO<engine::MaterialData>> brick = {
            engine::UBO<engine::MaterialData>(
                std::make_unique<engine::MaterialData>(
                    math::Vec3(249.0f / 255, 160.0f / 255, 63.0f / 255), math::Vec3::one, 32.0f, false)),
            engine::UBO<engine::MaterialData>(
                std::make_unique<engine::MaterialData>(
                    math::Vec3(212.0f / 255, 81.0f / 255, 19.0f / 255), math::Vec3::one, 32.0f, false)),
            engine::UBO<engine::MaterialData>(
                std::make_unique<engine::MaterialData>(
                    math::Vec3(129.0f / 255, 52.0f / 255, 5.0f / 255), math::Vec3::one, 32.0f, false))};

        const engine::UBO<engine::MaterialData> ground = engine::UBO<engine::MaterialData>(
            std::make_unique<engine::MaterialData>(
                math::Vec3(1.1f, 1.3f, 1.1f), math::Vec3::one, 16.0f, true));
    };
} // namespace gameData
