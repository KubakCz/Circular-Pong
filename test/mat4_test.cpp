#include <gtest/gtest.h>
#include "../math_library_dir/vector.hpp"
#include "../math_library_dir/mat4.hpp"
#include <cstdio>

TEST(mat4_test_suite, array_constructor)
{
    float data[16] = {
        0, 3, 6, 9,
        2, 5, 8, 11,
        4, 7, 10, 13,
        6, 9, 12, 15};
    math::Mat4 m = math::Mat4(data);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            EXPECT_EQ(m.get(i, j), 2 * i + 3 * j);
        }
    }
}

TEST(mat4_test_suite, transposed)
{
    float data[16] = {
        0, 3, 6, 9,
        2, 5, 8, 11,
        4, 7, 10, 13,
        6, 9, 12, 15};
    math::Mat4 m = math::Mat4(data);
    math::Mat4 t = m.transposed();

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            EXPECT_EQ(t.get(i, j), 3 * i + 2 * j);
        }
    }
}

TEST(mat4_test_suite, transpose)
{
    float data[16] = {
        6, 55, 22, 32,
        61, 34, 102, 5,
        250, 33, 7, 36,
        24, 1000, 1001, 6};

    math::Mat4 m = math::Mat4(data);
    math::Mat4 n = m.transposed();

    m.transpose();

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            EXPECT_EQ(m.get(i, j), n.get(i, j));
        }
    }
}

TEST(mat4_test_suite, mat_mat_mul)
{
    float data_m[16] = {
        0, 3, 6, 9,
        2, 5, 8, 0,
        4, 0, 10, 0,
        6, 0, 0, 1};
    math::Mat4 m = math::Mat4(data_m);
    float data_n[16] = {
        0, 1, 2, 3,
        1, 2, 3, 0,
        4, 0, 0, 10,
        0, 1, 2, 1};
    math::Mat4 n = math::Mat4(data_n);

    math::Mat4 r = m * n;

    EXPECT_FLOAT_EQ(r.get(0, 0), 27);
    EXPECT_FLOAT_EQ(r.get(0, 1), 15);
    EXPECT_FLOAT_EQ(r.get(0, 2), 27);
    EXPECT_FLOAT_EQ(r.get(0, 3), 69);

    EXPECT_FLOAT_EQ(r.get(1, 0), 37);
    EXPECT_FLOAT_EQ(r.get(1, 1), 12);
    EXPECT_FLOAT_EQ(r.get(1, 2), 19);
    EXPECT_FLOAT_EQ(r.get(1, 3), 86);

    EXPECT_FLOAT_EQ(r.get(2, 0), 40);
    EXPECT_FLOAT_EQ(r.get(2, 1), 4);
    EXPECT_FLOAT_EQ(r.get(2, 2), 8);
    EXPECT_FLOAT_EQ(r.get(2, 3), 112);

    EXPECT_FLOAT_EQ(r.get(3, 0), 0);
    EXPECT_FLOAT_EQ(r.get(3, 1), 7);
    EXPECT_FLOAT_EQ(r.get(3, 2), 14);
    EXPECT_FLOAT_EQ(r.get(3, 3), 19);
}

TEST(mat4_test_suite, mat_vec_mul)
{
    float data[16] = {
        0, 3, 6, 9,
        2, 5, 8, 0,
        4, 0, 10, 0,
        6, 0, 0, 1};
    math::Mat4 m = math::Mat4(data);
    float data_v[4] = {0, 1, 2, 3};
    math::Vector<4> v = math::Vector<4>(data_v);

    math::Vector<4> r = m * v;

    EXPECT_FLOAT_EQ(r[0], 3 + 12 + 27);
    EXPECT_FLOAT_EQ(r[1], 5 + 16);
    EXPECT_FLOAT_EQ(r[2], 20);
    EXPECT_FLOAT_EQ(r[3], 3);
}

TEST(mat4_test_suite, is_rotation_matrix_1)
{
    float data[16] = {
        1, 2, 3, 0,
        4, 5, 6, 0,
        7, 8, 9, 0,
        0, 0, 0, 1};
    math::Mat4 m = math::Mat4(data);

    EXPECT_TRUE(m.isRotationMatrix());
}

TEST(mat4_test_suite, is_rotation_matrix_2)
{
    float data[16] = {
        1, 2, 3, 0,
        4, 5, 6, 0,
        7, 8, 9, 0,
        0, 0, 0, 1};
    math::Mat4 m = math::Mat4(data);

    EXPECT_TRUE(m.isRotationMatrix());
}

TEST(mat4_test_suite, to_orthonormal)
{
    float data[16] = {
        -1, 1, 0, 0,
        1, 1, 0, 0,
        0, 0, -1, 0,
        0, 0, 0, 1};
    math::Mat4 m = math::Mat4(data);

    math::Vec3 x = math::Vec3();
    math::Vec3 y = math::Vec3();
    math::Vec3 z = math::Vec3();

    m.toBasisVectors(x, y, z);

    EXPECT_EQ(x.x(), data[0]);
    EXPECT_EQ(x.y(), data[4]);
    EXPECT_EQ(x.z(), data[8]);

    EXPECT_EQ(y.x(), data[1]);
    EXPECT_EQ(y.y(), data[5]);
    EXPECT_EQ(y.z(), data[9]);

    EXPECT_EQ(z.x(), data[2]);
    EXPECT_EQ(z.y(), data[6]);
    EXPECT_EQ(z.z(), data[10]);
}

TEST(mat4_test_suite, from_orthonormal)
{
    math::Vec3 x = math::Vec3(-1, 1, 0);
    math::Vec3 y = math::Vec3(1, 1, 0);
    math::Vec3 z = math::Vec3(0, 0, -1);

    math::Mat4 m = math::Mat4(x, y, z);

    float data[16] = {
        -1, 1, 0, 0,
        1, 1, 0, 0,
        0, 0, -1, 0,
        0, 0, 0, 1};

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            EXPECT_EQ(m.get(i, j), data[i + j * 4]);
        }
    }
}

TEST(mat4_test_suite, times_scalar)
{
    float data[16] = {
        1, 2, -4, 1,
        4, 9, 8, -1,
        3, 4, -1, 0,
        -1, 8, 9, 1};
    math::Mat4 m = math::Mat4(data);

    const float multiplier = 2.2f;

    math::Mat4 mm = multiplier * m;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            EXPECT_FLOAT_EQ(mm.get(i, j), m.get(i, j) * multiplier);
        }
    }
}

TEST(mat4_test_suite, div_by_scalar)
{
    float data[16] = {
        1, 2, -4, 1,
        4, 9, 8, -1,
        3, 4, -1, 0,
        -1, 8, 9, 1};
    math::Mat4 m = math::Mat4(data);

    const float divider = 2.2f;

    math::Mat4 mm = m / divider;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            EXPECT_FLOAT_EQ(mm.get(i, j), m.get(i, j) / divider);
        }
    }
}