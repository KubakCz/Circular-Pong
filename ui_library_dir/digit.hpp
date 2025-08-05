#pragma once

#include "element.hpp"
#include "rectangle.hpp"

namespace ui
{
    class Digit : public Element
    {
    public:
        Digit(const Transform &transform, const math::Vec4 &color, int initDigit);

        void SetDigit(unsigned int digit);
    };
} // namespace ui
