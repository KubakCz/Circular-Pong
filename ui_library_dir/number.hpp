#pragma once

#include "digit.hpp"

namespace ui
{
    class Number
    {
        const float digitWidth = 0.85f;

        unsigned int _value;
        int digitCount;
        int maxDigitCount;

        std::vector<Digit> digits;

    public:
        Number(const math::Vec2 &rightTopCorner, float height, int maxDigits);

        int value() const { return _value; }
        void value(unsigned int i);

        void render() const;
    };
} // namespace ui
