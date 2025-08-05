#pragma once

#include "vector.hpp"

namespace math
{
    class Cartesian
    {
    public:
        /// @brief Compute and return closes point on line ab from point p.
        /// @param a Starting point of the line
        /// @param b Ending point of the line
        /// @param p Point to which is the closest point computed
        /// @param clamp If true, only the points on segment ab are considered. If false, the point may lie outside the interval.
        /// @return Closest point on the line
        static Vec3 closestPointOnLine(Vec3 a, Vec3 b, Vec3 p, bool clamp = true);
    };
} // namespace math
