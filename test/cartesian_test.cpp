#include <gtest/gtest.h>
#include "../math_library_dir/cartesian.hpp"
#include <cstdio>

TEST(cartesian_test_suite, closestPointOnLine_onLine)
{
    math::Vec3 a(0, 0, 0);
    math::Vec3 b(2, 2, 0);
    math::Vec3 p(2, 0, 0);

    math::Vec3 x = math::Cartesian::closestPointOnLine(a, b, p);

    EXPECT_FLOAT_EQ(x.x(), 1);
    EXPECT_FLOAT_EQ(x.y(), 1);
    EXPECT_FLOAT_EQ(x.z(), 0);
}

TEST(cartesian_test_suite, closestPointOnLine_belowClamped)
{
    math::Vec3 a(0, 0, 0);
    math::Vec3 b(2, 2, 0);
    math::Vec3 p(-2, 0, 0);

    math::Vec3 x = math::Cartesian::closestPointOnLine(a, b, p);

    EXPECT_FLOAT_EQ(x.x(), a.x());
    EXPECT_FLOAT_EQ(x.y(), a.y());
    EXPECT_FLOAT_EQ(x.z(), a.z());
}

TEST(cartesian_test_suite, closestPointOnLine_belowUnclamped)
{
    math::Vec3 a(0, 0, 0);
    math::Vec3 b(2, 2, 0);
    math::Vec3 p(-2, 0, 0);

    math::Vec3 x = math::Cartesian::closestPointOnLine(a, b, p, false);

    EXPECT_FLOAT_EQ(x.x(), -1);
    EXPECT_FLOAT_EQ(x.y(), -1);
    EXPECT_FLOAT_EQ(x.z(), 0);
}

TEST(cartesian_test_suite, closestPointOnLine_aboveClamped)
{
    math::Vec3 a(0, 0, 0);
    math::Vec3 b(2, 2, 0);
    math::Vec3 p(2, 4, 0);

    math::Vec3 x = math::Cartesian::closestPointOnLine(a, b, p);

    EXPECT_FLOAT_EQ(x.x(), b.x());
    EXPECT_FLOAT_EQ(x.y(), b.y());
    EXPECT_FLOAT_EQ(x.z(), b.z());
}