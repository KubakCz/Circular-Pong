#include "number.hpp"

namespace ui
{
    Number::Number(const math::Vec2 &rightTopCorner, float height, int maxDigits) : maxDigitCount(maxDigits)
    {
        digits.reserve(maxDigitCount);
        for (int i = 0; i < maxDigits; ++i)
        {
            digits.emplace_back(
                Transform(rightTopCorner,
                          math::Vec2(1.0f + 2 * i, 1),
                          math::Vec2(1, height),
                          true),
                math::Vec4::one,
                0);
        }
        value(0);
    };

    void Number::value(unsigned int i)
    {
        _value = i;
        digitCount = 0;
        while (i > 0 && digitCount < maxDigitCount)
        {
            digits[digitCount].SetDigit(i % 10);
            i /= 10;
            ++digitCount;
        }

        if (digitCount == 0) // value == 0
        {
            digits[0].SetDigit(0);
            digitCount = 1;
        }
    }

    void Number::render() const
    {
        for (int i = 0; i < digitCount; ++i)
        {
            digits[i].render();
        }
    }
} // namespace ui
