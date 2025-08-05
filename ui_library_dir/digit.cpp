#include "digit.hpp"
#include "../engine_library_dir/textureManager.hpp"
#include <cassert>

namespace ui
{
    Digit::Digit(const Transform &transform, const math::Vec4 &color, int initDigit) : Element(transform,
                                                                                               engine::TextureManager::instance->getTexture("digits.png"),
                                                                                               false,
                                                                                               color)
    {
        this->transform.size.x() = (float)texture.width() / (texture.height() * 11) * transform.size.y();
        SetDigit(initDigit);
    }

    void Digit::SetDigit(unsigned int digit)
    {
        assert(digit >= 0);
        assert(digit < 10);

        subtexture.minCorner.x() = digit / 11.0f;
        subtexture.maxCorner.x() = (digit + 1) / 11.0f;
    }
} // namespace ui
