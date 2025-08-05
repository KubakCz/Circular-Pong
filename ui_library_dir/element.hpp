#pragma once

#include "glad/glad.h"
#include "transform.hpp"
#include "rectangle.hpp"
#include "../engine_library_dir/uniforms.hpp"
#include "../engine_library_dir/texture.hpp"

namespace ui
{
    class Element
    {
        engine::UBO<Transform> transformUBO;
        engine::UBO<Rectangle> subtextureUBO;

    public:
        math::Vec4 color;
        engine::Texture texture;
        Transform &transform = *(transformUBO.data.get());
        Rectangle &subtexture = *(subtextureUBO.data.get());

        Element(const Transform &transform, const math::Vec4 &color);
        Element(const Transform &transform, engine::Texture texture, bool keepAspect);
        Element(const Transform &transform, engine::Texture texture, bool keepAspect, const math::Vec4 &color);

        void render() const;
    };
} // namespace ui
