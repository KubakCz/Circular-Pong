#pragma once

#include <cassert>
#include <algorithm>
#include <iterator>
#include <cmath>

namespace math
{
    template <int N>
    class Vector
    {
        float _data[N] = {};

    public:
        Vector() = default;
        Vector(const Vector<N> &vec) = default;
        Vector(Vector<N> &&vec) = default;
        Vector(float data[N]);

        Vector(float x, float y);
        Vector(float x, float y, float z);
        Vector(float x, float y, float z, float w);

        Vector<N> &operator=(const Vector<N> &rhs) = default;

        float &x();
        float x() const;
        float &y();
        float y() const;
        float &z();
        float z() const;
        float &w();
        float w() const;

        float &operator[](int x);
        float operator[](int x) const;

        Vector<N> unit() const;
        void normalize();

        float mag() const;
        float magSquared() const;

        void operator+=(const Vector<N> &rhs);
        void operator-=(const Vector<N> &rhs);
        void operator*=(float rhs);
        void operator*=(const Vector<N> &rhs);
        void operator/=(float rhs);
        void operator/=(const Vector<N> &rhs);

        Vector<N> operator-() const;

        template <int N>
        friend Vector<N> operator+(Vector<N> lhs, const Vector<N> &rhs);
        template <int N>
        friend Vector<N> operator-(Vector<N> lhs, const Vector<N> &rhs);
        template <int N>
        friend Vector<N> operator*(Vector<N> lhs, float rhs);
        template <int N>
        friend Vector<N> operator*(float lhs, Vector<N> rhs);
        template <int N>
        friend Vector<N> operator*(Vector<N> lhs, const Vector<N> &rhs);
        template <int N>
        friend Vector<N> operator/(Vector<N> lhs, float rhs);
        template <int N>
        friend Vector<N> operator/(Vector<N> lhs, const Vector<N> &rhs);

        template <int N>
        friend float dot(const Vector<N> &a, const Vector<N> &b);

        template <int M>
        explicit operator Vector<M>() const
        {
            float new_data[M];
            std::copy(_data, _data + std::min(N, M), new_data);
            if (M > N)
                std::memset(new_data + N, 0, sizeof(float) * (M - N));
            return Vector<M>(new_data);
        };

        static const Vector<N> zero;
        static const Vector<N> one;
        static const Vector<N> right;
        static const Vector<N> left;
        static const Vector<N> forward;
        static const Vector<N> back;
        static const Vector<N> down;
        static const Vector<N> up;
    };

    typedef Vector<2> Vec2;
    typedef Vector<3> Vec3;
    typedef Vector<4> Vec4;

#pragma region constructors
    template <int N>
    Vector<N>::Vector(float data[N])
    {
        std::copy(data, data + N, _data);
    };
#pragma endregion constructors

#pragma region getters
    template <int N>
    float &Vector<N>::x()
    {
        assert(N > 0);
        return _data[0];
    };
    template <int N>
    float Vector<N>::x() const
    {
        assert(N > 0);
        return _data[0];
    };
    template <int N>
    float &Vector<N>::y()
    {
        assert(N > 1);
        return _data[1];
    };
    template <int N>
    float Vector<N>::y() const
    {
        assert(N > 1);
        return _data[1];
    };
    template <int N>
    float &Vector<N>::z()
    {
        assert(N > 2);
        return _data[2];
    };
    template <int N>
    float Vector<N>::z() const
    {
        assert(N > 2);
        return _data[2];
    };
    template <int N>
    float &Vector<N>::w()
    {
        assert(N > 3);
        return _data[3];
    };
    template <int N>
    float Vector<N>::w() const
    {
        assert(N > 3);
        return _data[3];
    };
#pragma endregion getters

#pragma region unit_vector
    template <int N>
    Vector<N> Vector<N>::unit() const
    {
        return *this / mag();
    };
    template <int N>
    void Vector<N>::normalize()
    {
        *this /= mag();
    };
#pragma endregion unit_vector

#pragma region mag
    template <int N>
    float Vector<N>::mag() const
    {
        return std::sqrtf(magSquared());
    };
    template <int N>
    float Vector<N>::magSquared() const
    {
        return dot(*this, *this);
    };
#pragma endregion

#pragma region access_operators
    template <int N>
    float &Vector<N>::operator[](int x)
    {
        assert(x >= 0 && x < N);
        return _data[x];
    };
    template <int N>
    float Vector<N>::operator[](int x) const
    {
        assert(x >= 0 && x < N);
        return _data[x];
    };
#pragma endregion access_operators

#pragma region assign_operators
    template <int N>
    void Vector<N>::operator+=(const Vector<N> &rhs)
    {
        for (int i = 0; i < N; ++i)
            _data[i] += rhs[i];
    };
    template <int N>
    void Vector<N>::operator-=(const Vector<N> &rhs)
    {
        for (int i = 0; i < N; ++i)
            _data[i] -= rhs[i];
    };
    template <int N>
    void Vector<N>::operator*=(float rhs)
    {
        for (int i = 0; i < N; ++i)
            _data[i] *= rhs;
    };
    template <int N>
    void Vector<N>::operator*=(const Vector<N> &rhs)
    {
        for (int i = 0; i < N; ++i)
            _data[i] *= rhs[i];
    };
    template <int N>
    void Vector<N>::operator/=(float rhs)
    {
        for (int i = 0; i < N; ++i)
            _data[i] /= rhs;
    };
    template <int N>
    void Vector<N>::operator/=(const Vector<N> &rhs)
    {
        for (int i = 0; i < N; ++i)
            _data[i] /= rhs[i];
    };
#pragma endregion assign_operators

#pragma region unary_operators
    template <int N>
    Vector<N> Vector<N>::operator-() const
    {
        Vector<N> v = Vector<N>();
        for (int i = 0; i < N; ++i)
            v._data[i] = -_data[i];
        return v;
    };
#pragma endregion unary_operators

#pragma region binary_operators
    template <int N>
    Vector<N> operator+(Vector<N> lhs, const Vector<N> &rhs)
    {
        lhs += rhs;
        return lhs;
    };
    template <int N>
    Vector<N> operator-(Vector<N> lhs, const Vector<N> &rhs)
    {
        lhs -= rhs;
        return lhs;
    };
    template <int N>
    Vector<N> operator*(Vector<N> lhs, float rhs)
    {
        lhs *= rhs;
        return lhs;
    };
    template <int N>
    Vector<N> operator*(float lhs, Vector<N> rhs)
    {
        rhs *= lhs;
        return rhs;
    };
    template <int N>
    Vector<N> operator*(Vector<N> lhs, const Vector<N> &rhs)
    {
        lhs *= rhs;
        return lhs;
    };
    template <int N>
    Vector<N> operator/(Vector<N> lhs, float rhs)
    {
        lhs /= rhs;
        return lhs;
    };
    template <int N>
    Vector<N> operator/(Vector<N> lhs, const Vector<N> &rhs)
    {
        lhs /= rhs;
        return lhs;
    };
#pragma endregion binary_operators

#pragma region dot
    template <int N>
    struct Dot
    {
        static inline float result(const float *a, const float *b)
        {
            return (*a) * (*b) + Dot<N - 1>::result(a + 1, b + 1);
        }
    };

    template <>
    struct Dot<1>
    {
        static inline float result(const float *a, const float *b)
        {
            return (*a) * (*b);
        }
    };

    template <int N>
    float dot(const Vector<N> &a, const Vector<N> &b)
    {
        return Dot<N>::result(&a._data[0], &b._data[0]);
    };
#pragma endregion dot

#pragma region cross
    Vec3 cross(const Vec3 &a, const Vec3 &b);
#pragma endregion cross
}