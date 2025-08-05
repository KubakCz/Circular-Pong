#pragma once

#include "vector.hpp"
#include "mat4.hpp"
#include "axisAngle.hpp"

namespace math
{
    class Quaternion
    {
    private:
        float _s = 1;
        Vec3 _u = Vec3(0, 0, 0);

    public:
        Quaternion() = default;
        Quaternion(const Quaternion &q) = default;
        Quaternion(Quaternion &&q) = default;

        Quaternion(float s, Vec3 u);
        Quaternion(float s, float x, float y, float z);

        Quaternion &operator=(const Quaternion &rhs) = default;

        float s() const { return _s; }
        const Vec3 &u() const { return _u; }
        float x() const { return _u.x(); }
        float y() const { return _u.y(); }
        float z() const { return _u.z(); }

        Quaternion unit() const;
        void normalize();

        float mag() const;
        float magSquared() const;

        Quaternion conjugated() const;
        void conjugate();

        Quaternion inversed() const;
        void inverse();

        void operator+=(const Quaternion &rhs);
        void operator-=(const Quaternion &rhs);
        void operator*=(const Quaternion &rhs);
        void operator*=(float rhs);
        void operator/=(float rhs);

        friend Quaternion operator+(Quaternion lhs, const Quaternion &rhs);
        friend Quaternion operator-(Quaternion lhs, const Quaternion &rhs);
        friend Quaternion operator*(Quaternion lhs, const Quaternion &rhs);
        friend Quaternion operator*(float lhs, Quaternion rhs);
        friend Quaternion operator*(Quaternion lhs, float rhs);
        friend Quaternion operator/(Quaternion lhs, float rhs);

        friend float dot(const Quaternion &p, const Quaternion &q);
        friend Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t);

        /// @brief Transform quaternion to angle axis representation.
        /// @param axis Resulting unit axis of rotation
        /// @param angle Resulting rotation angle in radians
        AxisAngle toAxisAngle();

        /// @brief Create quaternion from axis angle representation.
        /// @param axis Axis of rotation (no need to normalize)
        /// @param angle Angle of rotation in radians
        static Quaternion fromAxisAngle(const Vec3 &axis, float angle);

        /// @brief Create quaternion from axis angle representation.
        static Quaternion fromAxisAngle(const AxisAngle &aa);

        /// @brief Create rotation matrix for homogenous coordinates.
        Mat4 toRotMatrix() const;

        /// @brief Create quaternion from rotation matrix. If the matrix is not rotation matrix, behaviour is undefined.
        static Quaternion fromRotMatrix(const Mat4 &rm);

        /// @brief Create quaternion representing rotation from Euler angles in Y-X-Z sequence (Yaw-Pitch-Roll).
        static Quaternion fromEulerAngles(float x, float y, float z);
    };

    /// @brief Dot product of two quaternions.
    float dot(const Quaternion &p, const Quaternion &q);

    /// @brief Get spherical linear interpolation between quaternions q0 and q1.
    Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t);
}
