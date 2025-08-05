#include <gtest/gtest.h>
#include "../math_library_dir/vector.hpp"
#include <cstdio>

TEST(vector_test_suite, element_acces)
{
    math::Vector<2> v = math::Vector<2>();

    v[0] = 42;
    v[1] = v[0];

    EXPECT_EQ(v[0], v[1])
        << "42 == v[0] == v[1]";
}

TEST(vector_test_suite, copy_constructor_1)
{
    math::Vec2 u = math::Vec2();
    u[0] = 42;
    u[1] = -42;

    math::Vector<2> v = math::Vector<2>(u);
    EXPECT_EQ(u[0], v[0]) << "u[0] == v[0]";
    EXPECT_EQ(u[1], v[1]) << "u[1] == v[1]";
}
TEST(vector_test_suite, copy_constructor_2)
{
    math::Vector<2> u = math::Vector<2>();
    u[0] = 42;
    u[1] = -42;

    math::Vector<2> v = math::Vector<2>(u);
    v[0] = 0;
    v[1] = 1;

    EXPECT_NE(u[0], v[0]) << "u[0] != v[0]";
    EXPECT_NE(u[1], v[1]) << "u[1] != v[1]";
}

TEST(vector_test_suite, array_constructor)
{
    float data[4] = {42, 3, 2, 8};
    math::Vector<4> v = math::Vector<4>(data);

    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 2);
    EXPECT_EQ(v[3], 8);
}

TEST(vector_test_suite, assignment)
{
    math::Vector<2> u = math::Vector<2>();
    u[0] = 42;
    u[1] = -42;

    math::Vector<2> v = u;
    v[0] = 0;
    v[1] = 1;

    EXPECT_NE(u[0], v[0]) << "u[0] != v[0]";
    EXPECT_NE(u[1], v[1]) << "u[1] != v[1]";
}

TEST(vector_test_suite, dot_product)
{
    math::Vector<3> u = math::Vector<3>();
    math::Vector<3> v = math::Vector<3>();

    u[0] = 1;
    u[1] = 2;
    u[2] = 3;

    v[0] = -1;
    v[1] = 0;
    v[2] = 1;

    EXPECT_EQ(math::dot(u, v), 2) << "(1,2,3) . (-1,0,1) == 2";
}

TEST(vector_test_suite, magSquared)
{
    math::Vector<4> v = math::Vector<4>();
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;

    EXPECT_EQ(v.magSquared(), 30) << "||(1,2,3,4)||^2 == 30";
}

TEST(vector_test_suite, mag)
{
    math::Vector<5> v = math::Vector<5>();
    v[0] = 3;
    v[1] = 1;
    v[2] = 3;
    v[3] = 4;
    v[4] = 1;

    EXPECT_FLOAT_EQ(v.mag(), 6) << "||(3,1,3,4,1)|| == 6";
}

TEST(vector_test_suite, unit_vector_mag)
{
    math::Vector<3> v = math::Vector<3>();
    v[0] = 1;
    v[1] = 2;
    v[2] = 42;

    math::Vector<3> u = v.unit();

    EXPECT_FLOAT_EQ(u.mag(), 1) << "||unit vector|| == 1";
}

TEST(vector_test_suite, unit_vector_dir)
{
    math::Vector<3> v = math::Vector<3>();
    v[0] = 1;
    v[1] = 2;
    v[2] = 42;

    math::Vector<3> u = v.unit();

    EXPECT_FLOAT_EQ(u[0] / u[1], v[0] / v[1]) << "u[0] / u[1] == v[0] / v[1]";
    EXPECT_FLOAT_EQ(u[1] / u[2], v[1] / v[2]) << "u[1] / u[2] == v[1] / v[2]";
    EXPECT_FLOAT_EQ(u[0] / u[2], v[0] / v[2]) << "u[0] / u[2] == v[0] / v[2]";
}

TEST(vector_test_suite, normalize)
{
    math::Vector<3> v = math::Vector<3>();
    v[0] = 1;
    v[1] = 2;
    v[2] = 42;

    math::Vector<3> unit = v.unit();
    v.normalize();

    EXPECT_FLOAT_EQ(v[0], unit[0]) << "v[0] == unit[0]";
    EXPECT_FLOAT_EQ(v[1], unit[1]) << "v[1] == unit[1]";
    EXPECT_FLOAT_EQ(v[2], unit[2]) << "v[2] == unit[2]";
}

TEST(vector_test_suite, addition)
{
    math::Vector<2> u = math::Vector<2>();
    u[0] = -2;
    u[1] = 2;

    math::Vector<2> v = math::Vector<2>();
    v[0] = 42;
    v[1] = 42;

    math::Vector<2> res = u + v;

    EXPECT_FLOAT_EQ(res[0], 40) << "-2 + 42 == 40 == res[0]";
    EXPECT_FLOAT_EQ(res[1], 44) << "2 + 42 == 44 == res[1]";
}

TEST(vector_test_suite, subtraction)
{
    math::Vector<2> u = math::Vector<2>();
    u[0] = -2;
    u[1] = 2;

    math::Vector<2> v = math::Vector<2>();
    v[0] = 42;
    v[1] = 42;

    math::Vector<2> res = u - v;

    EXPECT_FLOAT_EQ(res[0], -44) << "-2 - 42 == -44 == res[0]";
    EXPECT_FLOAT_EQ(res[1], -40) << "2 - 42 == -40 == res[1]";
}

TEST(vector_test_suite, elementvise_multiplication)
{
    math::Vector<2> u = math::Vector<2>();
    u[0] = -2;
    u[1] = 2;

    math::Vector<2> v = math::Vector<2>();
    v[0] = 42;
    v[1] = 4;

    math::Vector<2> res = u * v;

    EXPECT_FLOAT_EQ(res[0], -84);
    EXPECT_FLOAT_EQ(res[1], 8);
}

TEST(vector_test_suite, elementvise_division)
{
    math::Vector<2> u = math::Vector<2>();
    u[0] = -2;
    u[1] = 2;

    math::Vector<2> v = math::Vector<2>();
    v[0] = 42;
    v[1] = 4;

    math::Vector<2> res = u / v;

    EXPECT_FLOAT_EQ(res[0], -2 / 42.0f);
    EXPECT_FLOAT_EQ(res[1], 2 / 4.0f);
}

TEST(vector_test_suite, multiplication_by_scalar)
{
    math::Vector<2> u = math::Vector<2>();
    u[0] = -2;
    u[1] = 42;

    auto v = 3.0f * u;

    EXPECT_FLOAT_EQ(v[0], -6);
    EXPECT_FLOAT_EQ(v[1], 42 * 3);
}

TEST(vector_test_suite, division_by_scalar)
{
    math::Vector<2> u = math::Vector<2>();
    u[0] = -2;
    u[1] = 42;

    auto v = u / 3;

    EXPECT_FLOAT_EQ(v[0], -2 / 3.0f);
    EXPECT_FLOAT_EQ(v[1], 42 / 3.0f);
}

TEST(vector_test_suite, cross)
{
    math::Vec3 u = math::Vec3(1, 2, 3);
    math::Vec3 v = math::Vec3(4, -10, 6);

    auto res = math::cross(u, v);

    EXPECT_FLOAT_EQ(res.x(), 42);
    EXPECT_FLOAT_EQ(res.y(), 6);
    EXPECT_FLOAT_EQ(res.z(), -18);
}

TEST(vector_test_suite, cast_down)
{
    math::Vec3 u = math::Vec3(1, 2, 3);

    math::Vector<1> v = (math::Vector<1>)u;

    EXPECT_FLOAT_EQ(v[0], u.x());
}

TEST(vector_test_suite, cast_up)
{
    math::Vec3 u = math::Vec3(1, 2, 3);

    math::Vector<5> v = (math::Vector<5>)u;

    EXPECT_FLOAT_EQ(v[0], u.x());
    EXPECT_FLOAT_EQ(v[1], u.y());
    EXPECT_FLOAT_EQ(v[2], u.z());
    EXPECT_FLOAT_EQ(v[3], 0);
    EXPECT_FLOAT_EQ(v[4], 0);
}
