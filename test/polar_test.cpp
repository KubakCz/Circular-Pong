#include <gtest/gtest.h>
#include "../math_library_dir/vector.hpp"
#include "../math_library_dir/polar.hpp"
#include <cstdio>
#define _USE_MATH_DEFINES
#include <math.h>

TEST(polar_test_suite, normalization_0)
{
    math::Polar p = math::Polar(0, 1);

    EXPECT_FLOAT_EQ(p.a(), 0);
    EXPECT_FLOAT_EQ(p.r(), 1);
}

TEST(polar_test_suite, normalization_1)
{
    math::Polar p = math::Polar(5.5f, 5.5f);

    EXPECT_FLOAT_EQ(p.a(), 5.5f);
    EXPECT_FLOAT_EQ(p.r(), 5.5f);
}

TEST(polar_test_suite, normalization_2)
{
    math::Polar p = math::Polar(1.45f + 4 * (float)M_PI, 5.5f);

    EXPECT_FLOAT_EQ(p.a(), 1.45f);
    EXPECT_FLOAT_EQ(p.r(), 5.5f);
}

TEST(polar_test_suite, normalization_3)
{
    math::Polar p = math::Polar(-0.45f * (float)M_PI, 5.5f);

    EXPECT_FLOAT_EQ(p.a(), (float)((2 - 0.45) * M_PI));
    EXPECT_FLOAT_EQ(p.r(), 5.5);
}

TEST(polar_test_suite, from_cartesian_1)
{
    float data[2] = {1, 1};
    math::Polar p = math::Polar(math::Vector<2>(data));

    EXPECT_FLOAT_EQ(p.a(), 0.25f * (float)M_PI);
    EXPECT_FLOAT_EQ(p.r(), std::sqrtf(2));
}

TEST(polar_test_suite, from_cartesian_2)
{
    float data[2] = {-2, 2};
    math::Polar p = math::Polar(math::Vector<2>(data));

    EXPECT_FLOAT_EQ(p.a(), 0.75f * (float)M_PI);
    EXPECT_FLOAT_EQ(p.r(), std::sqrtf(8));
}

TEST(polar_test_suite, from_cartesian_3)
{
    float data[2] = {-3, -3};
    math::Polar p = math::Polar(math::Vector<2>(data));

    EXPECT_FLOAT_EQ(p.a(), 1.25f * (float)M_PI);
    EXPECT_FLOAT_EQ(p.r(), std::sqrtf(18));
}

TEST(polar_test_suite, from_cartesian_4)
{
    math::Polar p = math::Polar(math::Vec2(0, -3));

    EXPECT_FLOAT_EQ(p.a(), 1.5f * (float)M_PI);
    EXPECT_FLOAT_EQ(p.r(), 3);
}

TEST(polar_test_suite, to_cartesian_1)
{
    math::Polar p = math::Polar(0.25f * (float)M_PI, 2.0f);

    math::Vector<2> v = p.toCartesian();

    EXPECT_FLOAT_EQ(v[0], std::sqrtf(2));
    EXPECT_FLOAT_EQ(v[1], std::sqrtf(2));
}

TEST(polar_test_suite, to_cartesian_2)
{
    math::Polar p = math::Polar(1.5f * (float)M_PI, 5.5f);

    math::Vector<2> v = p.toCartesian();

    EXPECT_NEAR(v[0], 0, 1e-6);
    EXPECT_FLOAT_EQ(v[1], -5.5f);
}

TEST(polar_test_suite, signedAngleDifference_mPI2)
{
    math::Polar a((float)M_PI, 1);
    math::Polar b((float)M_PI_2, 1);

    EXPECT_FLOAT_EQ(math::Polar::signedAngleDifference(a, b), -(float)M_PI_2);
}

TEST(polar_test_suite, signedAngleDifference_0)
{
    math::Polar a((float)M_PI, 1);
    math::Polar b((float)M_PI, 1);

    EXPECT_FLOAT_EQ(math::Polar::signedAngleDifference(a, b), 0);
}

TEST(polar_test_suite, signedAngleDifference_PI2)
{
    math::Polar a((float)(15 * M_PI / 8), 1);
    math::Polar b((float)(float)(19 * M_PI / 8), 1);

    EXPECT_FLOAT_EQ(math::Polar::signedAngleDifference(a, b), (float)M_PI_2);
}

TEST(polar_test_suite, signedAngleDifference_PI)
{
    math::Polar a((float)(M_PI / 2), 1);
    math::Polar b((float)(float)(-M_PI / 2), 1);

    EXPECT_FLOAT_EQ(math::Polar::signedAngleDifference(a, b), (float)M_PI);
}

TEST(polar_test_suite, angleDifference_mPI2)
{
    math::Polar a((float)M_PI, 1);
    math::Polar b((float)M_PI_2, 1);

    EXPECT_FLOAT_EQ(math::Polar::angleDifference(a, b), (float)M_PI_2);
}

TEST(polar_test_suite, angleDifference_0)
{
    math::Polar a((float)M_PI, 1);
    math::Polar b((float)M_PI, 1);

    EXPECT_FLOAT_EQ(math::Polar::angleDifference(a, b), 0);
}

TEST(polar_test_suite, angleDifference_PI2)
{
    math::Polar a((float)(15 * M_PI / 8), 1);
    math::Polar b((float)(float)(19 * M_PI / 8), 1);

    EXPECT_FLOAT_EQ(math::Polar::angleDifference(a, b), (float)M_PI_2);
}

TEST(polar_test_suite, angleDifference_PI)
{
    math::Polar a((float)(M_PI / 2), 1);
    math::Polar b((float)(float)(-M_PI / 2), 1);

    EXPECT_FLOAT_EQ(math::Polar::angleDifference(a, b), (float)M_PI);
}

TEST(polar_test_suite, isInTheLeftHalfPlane_mPI2)
{
    math::Polar a((float)M_PI, 1);
    math::Polar b((float)M_PI_2, 1);

    EXPECT_FALSE(math::Polar::isInTheLeftHalfPlane(a, b));
}

TEST(polar_test_suite, isInTheLeftHalfPlane_0)
{
    math::Polar a((float)M_PI, 1);
    math::Polar b((float)M_PI, 1);

    EXPECT_FALSE(math::Polar::isInTheLeftHalfPlane(a, b));
}

TEST(polar_test_suite, isInTheLeftHalfPlane_PI2)
{
    math::Polar a((float)(15 * M_PI / 8), 1);
    math::Polar b((float)(float)(19 * M_PI / 8), 1);

    EXPECT_TRUE(math::Polar::isInTheLeftHalfPlane(a, b));
}

TEST(polar_test_suite, isInTheLeftHalfPlane_PI)
{
    math::Polar a((float)(M_PI / 2), 1);
    math::Polar b((float)(float)(-M_PI / 2), 1);

    EXPECT_TRUE(math::Polar::isInTheLeftHalfPlane(a, b));
}
