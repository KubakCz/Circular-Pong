#include "mat4.hpp"

#include <algorithm>
#include <iterator>

namespace math
{
#pragma region constants
    template <>
    const Vec2 Vec2::zero = Vec2();
    template <>
    const Vec2 Vec2::one = Vec2(1, 1);
    template <>
    const Vec2 Vec2::right = Vec2(1, 0);
    template <>
    const Vec2 Vec2::left = Vec2(-1, 0);
    template <>
    const Vec2 Vec2::up = Vec2(0, 1);
    template <>
    const Vec2 Vec2::down = Vec2(0, -1);

    template <>
    const Vec3 Vec3::zero = Vec3();
    template <>
    const Vec3 Vec3::one = Vec3(1, 1, 1);
    template <>
    const Vec3 Vec3::right = Vec3(1, 0, 0);
    template <>
    const Vec3 Vec3::left = Vec3(-1, 0, 0);
    template <>
    const Vec3 Vec3::up = Vec3(0, 1, 0);
    template <>
    const Vec3 Vec3::down = Vec3(0, -1, 0);
    template <>
    const Vec3 Vec3::forward = Vec3(0, 0, 1);
    template <>
    const Vec3 Vec3::back = Vec3(0, 0, -1);

    template <>
    const Vec4 Vec4::zero = Vec4();
    template <>
    const Vec4 Vec4::one = Vec4(1, 1, 1, 1);
    template <>
    const Vec4 Vec4::right = Vec4(1, 0, 0, 0);
    template <>
    const Vec4 Vec4::left = Vec4(-1, 0, 0, 0);
    template <>
    const Vec4 Vec4::up = Vec4(0, 1, 0, 0);
    template <>
    const Vec4 Vec4::down = Vec4(0, -1, 0, 0);
    template <>
    const Vec4 Vec4::forward = Vec4(0, 0, 1, 0);
    template <>
    const Vec4 Vec4::back = Vec4(0, 0, -1, 0);
#pragma endregion constants

    template <>
    Vector<2>::Vector(float x, float y)
    {
        _data[0] = x;
        _data[1] = y;
    };

    template <>
    Vector<3>::Vector(float x, float y, float z)
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
    };

    template <>
    Vector<4>::Vector(float x, float y, float z, float w)
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
        _data[3] = w;
    };

    Vec3 cross(const Vec3 &a, const Vec3 &b)
    {
        return Vec3(
            a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]);
    };
}