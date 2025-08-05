#include "mat4.hpp"

#include <algorithm>
#include <iterator>

namespace math
{
    Mat4::Mat4(float data[16], bool dataByRows)
    {
        if (dataByRows)
        {
            // transpose
            for (int i = 0; i < 16; ++i)
                get(i / 4, i % 4) = data[i];
        }
        else
        {
            std::copy(data, data + 16, _data);
        }
    }

    float &Mat4::get(int row, int col)
    {
        assert(row >= 0 && row < 4);
        assert(col >= 0 && col < 4);
        return _data[col * 4 + row];
    }
    float Mat4::get(int row, int col) const
    {
        assert(row >= 0 && row < 4);
        assert(col >= 0 && col < 4);
        return _data[col * 4 + row];
    }

    Mat4 Mat4::transposed() const
    {
        Mat4 transposed = Mat4();
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; j++)
            {
                transposed.get(i, j) = this->get(j, i);
            }
        }
        return transposed;
    }

    void Mat4::transpose()
    {
        std::swap(_data[1], _data[4]);
        std::swap(_data[2], _data[8]);
        std::swap(_data[3], _data[12]);
        std::swap(_data[6], _data[9]);
        std::swap(_data[7], _data[13]);
        std::swap(_data[11], _data[14]);
    }

    void Mat4::operator*=(float f)
    {
        for (float &val : _data)
        {
            val *= f;
        }
    }

    void Mat4::operator/=(float f)
    {
        for (float &val : _data)
        {
            val /= f;
        }
    }

    Mat4 operator*(Mat4 lhs, float rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    Mat4 operator*(float lhs, Mat4 rhs)
    {
        rhs *= lhs;
        return rhs;
    }
    Mat4 operator/(Mat4 lhs, float rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    Mat4 operator*(const Mat4 &lhs, const Mat4 &rhs)
    {
        Mat4 res;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                for (int k = 0; k < 4; ++k)
                {
                    res.get(i, j) += lhs.get(i, k) * rhs.get(k, j);
                }
            }
        }
        return res;
    }

    Vec4 operator*(const Mat4 &lhs, const Vec4 &rhs)
    {
        Vec4 res;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                res[i] += lhs.get(i, j) * rhs[j];
            }
        }
        return res;
    }

    bool Mat4::isRotationMatrix()
    {
        return _data[3] == 0 &&
               _data[7] == 0 &&
               _data[11] == 0 &&
               _data[12] == 0 &&
               _data[13] == 0 &&
               _data[14] == 0 &&
               _data[15] == 1;
    }

    Mat4::Mat4(const Vec3 &x, const Vec3 &y, const Vec3 &z)
    {
        _data[0] = x.x();
        _data[1] = x.y();
        _data[2] = x.z();
        _data[3] = 0;

        _data[4] = y.x();
        _data[5] = y.y();
        _data[6] = y.z();
        _data[7] = 0;

        _data[8] = z.x();
        _data[9] = z.y();
        _data[10] = z.z();
        _data[11] = 0;

        _data[12] = 0;
        _data[13] = 0;
        _data[14] = 0;
        _data[15] = 1;
    }

    void Mat4::toBasisVectors(Vec3 &x, Vec3 &y, Vec3 &z)
    {
        x[0] = _data[0];
        x[1] = _data[1];
        x[2] = _data[2];

        y[0] = _data[4];
        y[1] = _data[5];
        y[2] = _data[6];

        z[0] = _data[8];
        z[1] = _data[9];
        z[2] = _data[10];
    }
}