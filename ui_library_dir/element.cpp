#include "element.hpp"
#include "../engine_library_dir/textureManager.hpp"

namespace ui
{
    Element::Element(const Transform &transform, const math::Vec4 &color) : Element(transform, engine::TextureManager::instance->getTexture("whitePixel.png"), false, color){};
    Element::Element(const Transform &transform, engine::Texture texture, bool keepAspect) : Element(transform, texture, keepAspect, math::Vec4::one){};
    Element::Element(const Transform &transform, engine::Texture texture, bool keepAspect, const math::Vec4 &color) : transformUBO(std::make_unique<Transform>(transform)),
                                                                                                                      color(color),
                                                                                                                      texture(texture)
    {
        if (keepAspect)
            this->transform.size.x() = (float)texture.width() / texture.height() * transform.size.y();
    };

    void Element::render() const
    {
        transformUBO.bind();
        subtextureUBO.bind(engine::UI_SUBTEXTURE_DEFAULT_BIND_INDEX);

        glUniform4f(1, color.x(), color.y(), color.z(), color.w()); // Set color
        texture.bind(0);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
} // namespace ui
