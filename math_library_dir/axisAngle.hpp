#pragma once

#include "vector.hpp"

namespace math
{
    class Quaternion;

    class AxisAngle
    {
        Vec3 _axis;
        float _angle;

        void normalize();

    public:
        AxisAngle() = default;
        AxisAngle(const AxisAngle &aa) = default;
        AxisAngle(AxisAngle &&aa) = default;

        AxisAngle(const Vec3 &axis, float angle);

        AxisAngle &operator=(const AxisAngle &rhs) = default;

        float angle() const { return _angle; }
        void angle(float angle);

        Vec3 axis() const { return _axis; }
        void axis(const Vec3 &axis);

        Quaternion toQuaternion() const;
    };
} // namespace math
