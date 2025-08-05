#include "quaternion.hpp"

namespace math
{
#pragma region constructors
    Quaternion::Quaternion(float s, Vec3 u) : _s(s), _u(u)
    {
    }

    Quaternion::Quaternion(float s, float x, float y, float z) : _s(s), _u(Vec3(x, y, z))
    {
    }

#pragma endregion constructors

#pragma region unit
    Quaternion Quaternion::unit() const
    {
        Quaternion q = *this;
        q.normalize();
        return q;
    }
    void Quaternion::normalize()
    {
        *this /= mag();
    }
#pragma endregion unit

#pragma region mag
    float Quaternion::mag() const
    {
        return std::sqrt(magSquared());
    }
    float Quaternion::magSquared() const
    {
        return dot(*this, *this);
    }
#pragma endregion mag

#pragma region conjugation
    Quaternion Quaternion::conjugated() const
    {
        Quaternion q = *this;
        q.conjugate();
        return q;
    }
    void Quaternion::conjugate()
    {
        _u = -_u;
    }
#pragma endregion conjugation

#pragma region inverse
    Quaternion Quaternion::inversed() const
    {
        Quaternion q = *this;
        q.inverse();
        return q;
    }
    void Quaternion::inverse()
    {
        _u = -_u;
        *this /= magSquared();
    }
#pragma endregion inverse

#pragma region operators
    void Quaternion::operator+=(const Quaternion &rhs)
    {
        _s += rhs._s;
        _u += rhs._u;
    }
    void Quaternion::operator-=(const Quaternion &rhs)
    {
        _s -= rhs._s;
        _u -= rhs._u;
    }
    void Quaternion::operator*=(const Quaternion &rhs)
    {
        float newS = _s * rhs._s - dot(_u, rhs._u);
        _u = _s * rhs._u + rhs._s * _u + cross(_u, rhs._u);
        _s = newS;
    }
    void Quaternion::operator*=(float rhs)
    {
        _s *= rhs;
        _u *= rhs;
    }
    void Quaternion::operator/=(float rhs)
    {
        _s /= rhs;
        _u /= rhs;
    }

    Quaternion operator+(Quaternion lhs, const Quaternion &rhs)
    {
        lhs += rhs;
        return lhs;
    }
    Quaternion operator-(Quaternion lhs, const Quaternion &rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    Quaternion operator*(Quaternion lhs, const Quaternion &rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    Quaternion operator*(float lhs, Quaternion rhs)
    {
        rhs *= lhs;
        return rhs;
    }
    Quaternion operator*(Quaternion lhs, float rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    Quaternion operator/(Quaternion lhs, float rhs)
    {
        lhs /= rhs;
        return lhs;
    }
#pragma endregion operators

    float dot(const Quaternion &p, const Quaternion &q)
    {
        return p._s * q._s + dot(p._u, q._u);
    }

    Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t)
    {
        float alpha = std::acosf(dot(q0, q1));
        Vec3 a = (q0._s * q1._u - q1._s * q0._u + cross(q0._u, q1._u)) / std::sinf(alpha);
        return Quaternion(std::cosf(t * alpha), std::sinf(t * alpha) * a) * q0;
    }

#pragma region conversions
    AxisAngle Quaternion::toAxisAngle()
    {
        normalize();

        // https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Recovering_the_axis-angle_representation
        float uMag = _u.mag(); // prevent computing root several times

        return AxisAngle(_u / uMag, 2 * std::atan2f(uMag, _s));
    }

    Quaternion Quaternion::fromAxisAngle(const Vec3 &axis, float angle)
    {
        return Quaternion(std::cosf(angle / 2), axis.unit() * std::sinf(angle / 2));
    }

    Quaternion Quaternion::fromAxisAngle(const AxisAngle &aa)
    {
        return fromAxisAngle(aa.axis(), aa.angle());
    }

    Mat4 Quaternion::toRotMatrix() const
    {
        // https://stackoverflow.com/questions/11667783/quaternion-and-normalization
        float data[16] = {
            s() * s() + x() * x() - y() * y() - z() * z(),
            2 * (-s() * z() + x() * y()),
            2 * (s() * y() + x() * z()),
            0,

            2 * (s() * z() + x() * y()),
            s() * s() - x() * x() + y() * y() - z() * z(),
            2 * (-s() * x() + y() * z()),
            0,

            2 * (-s() * y() + x() * z()),
            2 * (s() * x() + y() * z()),
            s() * s() - x() * x() - y() * y() + z() * z(),
            0,

            0,
            0,
            0,
            s() * s() + x() * x() + y() * y() + z() * z(),
        };
        return Mat4(data);
    }

    Quaternion Quaternion::fromEulerAngles(float x, float y, float z)
    {
        // https://ntrs.nasa.gov/citations/19770024290
        float sx = std::sinf(x / 2);
        float cx = std::cosf(x / 2);
        float sy = std::sinf(y / 2);
        float cy = std::cosf(y / 2);
        float sz = std::sinf(z / 2);
        float cz = std::cosf(z / 2);

        return Quaternion(
            sy * sx * sz + cy * cx * cz,
            sy * cx * sz + cy * sx * cz,
            sy * cx * cz - cy * sx * sz,
            -sy * sx * cz + cy * cx * sz);
    }

    Quaternion Quaternion::fromRotMatrix(const Mat4 &rm)
    {
        // Accurate Computation of Quaternions from Rotation Matrices
        // Soheil Sarabandi and Federico Thomas
        // http://www.iri.upc.edu/files/scidoc/2068-Accurate-Computation-of-Quaternions-from-Rotation-Matrices.pdf
        float treshold = 0;
        float q1, q2, q3, q4;

        float q1sum = rm.get(0, 0) + rm.get(1, 1) + rm.get(2, 2);
        if (q1sum > treshold)
        {
            q1 = 0.5f * std::sqrtf(1 + q1sum);
        }
        else
        {
            float s1 = rm.get(2, 1) - rm.get(1, 2);
            float s2 = rm.get(0, 2) - rm.get(2, 0);
            float s3 = rm.get(1, 0) - rm.get(0, 1);

            q1 = 0.5f * std::sqrtf((s1 * s1 + s2 * s2 + s3 * s3) / (3 - q1sum));
        }

        float q2sum = rm.get(0, 0) - rm.get(1, 1) - rm.get(2, 2);
        if (q2sum > treshold)
        {
            q2 = 0.5f * std::sqrtf(1 + q2sum);
        }
        else
        {
            float s1 = rm.get(2, 1) - rm.get(1, 2);
            float s2 = rm.get(0, 1) + rm.get(1, 0);
            float s3 = rm.get(2, 0) + rm.get(0, 2);

            q2 = 0.5f * std::sqrtf((s1 * s1 + s2 * s2 + s3 * s3) / (3 - q2sum));
        }
        if (rm.get(2, 1) - rm.get(1, 2) < 0)
            q2 = -q2;

        float q3sum = -rm.get(0, 0) + rm.get(1, 1) - rm.get(2, 2);
        if (q3sum > treshold)
        {
            q3 = 0.5f * std::sqrtf(1 + q3sum);
        }
        else
        {
            float s1 = rm.get(0, 2) - rm.get(2, 0);
            float s2 = rm.get(0, 1) + rm.get(1, 0);
            float s3 = rm.get(1, 2) + rm.get(2, 1);

            q3 = 0.5f * std::sqrtf((s1 * s1 + s2 * s2 + s3 * s3) / (3 - q3sum));
        }
        if (rm.get(0, 2) - rm.get(2, 0) < 0)
            q3 = -q3;

        float q4sum = -rm.get(0, 0) - rm.get(1, 1) + rm.get(2, 2);
        if (q4sum > treshold)
        {
            q4 = 0.5f * std::sqrtf(1 + q4sum);
        }
        else
        {
            float s1 = rm.get(1, 0) - rm.get(0, 1);
            float s2 = rm.get(2, 0) + rm.get(0, 2);
            float s3 = rm.get(2, 1) + rm.get(1, 2);

            q4 = 0.5f * std::sqrtf((s1 * s1 + s2 * s2 + s3 * s3) / (3 - q4sum));
        }
        if (rm.get(1, 0) - rm.get(0, 1) < 0)
            q4 = -q4;

        return Quaternion(q1, q2, q3, q4);
    }

#pragma endregion conversions
}