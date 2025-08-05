#include "polar.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

namespace math
{
    Polar::Polar(const Vec2 &vec) : _angle(std::atan2f(vec[1], vec[0])),
                                    _radius(vec.mag())
    {
        normalize();
    }

    Polar::Polar(float a, float r) : _angle(a), _radius(r)
    {
        normalize();
    }

    float Polar::a() const
    {
        return _angle;
    }

    void Polar::a(float angle)
    {
        _angle = angle;
        normalize();
    }

    float Polar::r() const
    {
        return _radius;
    }

    void Polar::r(float radius)
    {
        _radius = radius;
    }

    void Polar::normalize()
    {
        _angle -= (float)(std::floor(_angle / (2 * M_PI)) * 2 * M_PI);
    }

    const Vec2 Polar::toCartesian() const
    {
        return Vec2(std::cosf(_angle) * _radius, std::sinf(_angle) * _radius);
    }

    float Polar::signedAngleDifference(Polar a, Polar b)
    {
        float bAngle = b.a();
        if (a.a() > b.a())
            bAngle += (float)(2 * M_PI);

        float diff = bAngle - a.a();
        if (diff > M_PI)
            diff = -(float)(2 * M_PI - diff);

        return diff;
    }

    float Polar::angleDifference(Polar a, Polar b)
    {
        return std::abs(signedAngleDifference(a, b));
    }

    bool Polar::isInTheLeftHalfPlane(Polar vector, Polar point)
    {
        return signedAngleDifference(vector, point) > 0;
    }

}