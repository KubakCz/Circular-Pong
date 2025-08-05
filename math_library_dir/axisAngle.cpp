#include "axisAngle.hpp"
#include "quaternion.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

namespace math
{
    AxisAngle::AxisAngle(const Vec3 &axis, float angle) : _axis(axis), _angle(angle)
    {
        normalize();
    }

    void AxisAngle::normalize()
    {
        _axis.normalize();
        _angle -= (float)(std::floor(_angle / (2 * M_PI)) * 2 * M_PI);
    }

    void AxisAngle::angle(float angle)
    {
        _angle = angle;
        normalize();
    }

    void AxisAngle::axis(const Vec3 &axis)
    {
        _axis = axis;
        normalize();
    }

    Quaternion AxisAngle::toQuaternion() const
    {
        return Quaternion::fromAxisAngle(*this);
    }
} // namespace math
