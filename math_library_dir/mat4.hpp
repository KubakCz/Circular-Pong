#pragma once

#include "vector.hpp"

namespace math
{
    class Mat4
    {
        float _data[16] = {};

    public:
        Mat4() = default;
        Mat4(const Mat4 &mat) = default;
        Mat4(Mat4 &&mat) = default;

        /// @brief Initialize matrix by rows.
        Mat4(float data[16], bool dataByRows = true);

        /// @brief Create transform matrix from basis vectors.
        Mat4(const Vec3 &x, const Vec3 &y, const Vec3 &z);

        Mat4 &operator=(const Mat4 &m) = default;

        float &get(int row, int col);
        float get(int row, int col) const;

        /// @brief Get transposed matrix.
        Mat4 transposed() const;
        /// @brief Transpose this matrix.
        void transpose();

        void operator*=(float f);
        void operator/=(float f);

        friend Mat4 operator*(Mat4 lhs, float rhs);
        friend Mat4 operator*(float lhs, Mat4 rhs);
        friend Mat4 operator/(Mat4 lhs, float rhs);

        friend Mat4 operator*(const Mat4 &lhs, const Mat4 &rhs);
        friend Vec4 operator*(const Mat4 &lhs, const Vec4 &rhs);

        /// @brief Return true, if matrix is rotation matrix.
        bool isRotationMatrix();

        /// @brief Get basis vectors from matrix. If the matrix is not rotation matrix, behaviour is undefined.
        /// @param x First base vector.
        /// @param y Second base vector.
        /// @param z Third base vector.
        void toBasisVectors(Vec3 &x, Vec3 &y, Vec3 &z);
    };
}