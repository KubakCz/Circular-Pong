#pragma once

#include "vector.hpp"

namespace math
{
    class Polar
    {
        float _angle;
        float _radius;

        /// @brief Clip angle to the [0,2PI) range.
        void normalize();

    public:
        Polar() = default;
        Polar(const Polar &p) = default;
        Polar(Polar &&p) = default;

        /// @brief Create polar coordinates from 2D cartesian.
        /// @param vec 2D cartesian coordinates
        Polar(const Vector<2> &vec);

        Polar(float a, float r);

        const Vec2 toCartesian() const;

        /// @brief Angle coordinate
        float a() const;
        /// @brief Angle coordinate
        void a(float angle);

        /// @brief Radius coordinate
        float r() const;
        /// @brief Radius coordinate
        void r(float radius);

        /// @brief Return angle between point a and b. Angle is in interval (-pi, pi].
        static float signedAngleDifference(Polar a, Polar b);

        /// @brief Return angle between point a and b. Angle is in interval [0, pi].
        static float angleDifference(Polar a, Polar b);

        /// @brief Decide, if the point is in the left half plane given by point [0,0] and vector. Point with 0 angle will be considered as false and point with PI angle will be considered as true.
        static bool isInTheLeftHalfPlane(Polar vector, Polar point);
    };
}