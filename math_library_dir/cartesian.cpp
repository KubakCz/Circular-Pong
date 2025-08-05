#include "cartesian.hpp"

namespace math
{
    Vec3 Cartesian::closestPointOnLine(Vec3 a, Vec3 b, Vec3 p, bool clamp)
    {
        Vec3 ab = b - a;
        Vec3 dir = ab.unit();
        float lineCoord = dot(dir, p - a);

        // If clamped, chack that the point is not outside the ab range
        if (clamp)
        {
            if (lineCoord < 0)
                return a;
            else if (lineCoord > ab.mag())
                return b;
        }

        return a + dir * lineCoord;
    }
} // namespace math
