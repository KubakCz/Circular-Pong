#include <gtest/gtest.h>
#include "../engine_library_dir/ode.hpp"
#include <cstdio>

TEST(ode_test_suite, euler_forward)
{
    std::vector<float> y0 = {1, 2, 3, 4, 5, 6};
    std::vector<engine::F_y_t> fyt = {
        [](const std::vector<float> &y, float t)
        { return y[3]; },
        [](const std::vector<float> &y, float t)
        { return y[4]; },
        [](const std::vector<float> &y, float t)
        { return y[5]; },
        [](const std::vector<float> &y, float t)
        { return 1; },
        [](const std::vector<float> &y, float t)
        { return 0; },
        [](const std::vector<float> &y, float t)
        { return -1; }};
    float t0 = 0;
    float dt = 0.1f;
    std::vector<float> y(6);

    engine::ODE::eulerForward(y0, fyt, t0, dt, y);

    EXPECT_FLOAT_EQ(y[0], 1.4f);
    EXPECT_FLOAT_EQ(y[1], 2.5f);
    EXPECT_FLOAT_EQ(y[2], 3.6f);
    EXPECT_FLOAT_EQ(y[3], 4.1f);
    EXPECT_FLOAT_EQ(y[4], 5.0f);
    EXPECT_FLOAT_EQ(y[5], 5.9f);
}

TEST(ode_test_suite, midpoint)
{
    std::vector<float> y0 = {1, 2, 3, 4, 5, 6};
    std::vector<engine::F_y_t> fyt = {
        [](const std::vector<float> &y, float t)
        { return y[3]; },
        [](const std::vector<float> &y, float t)
        { return y[4]; },
        [](const std::vector<float> &y, float t)
        { return y[5]; },
        [](const std::vector<float> &y, float t)
        { return 1; },
        [](const std::vector<float> &y, float t)
        { return 0; },
        [](const std::vector<float> &y, float t)
        { return -1; }};
    float t0 = 0;
    float dt = 0.2f;
    std::vector<float> y(6);

    engine::ODE::midpoint(y0, fyt, t0, dt, y);

    EXPECT_FLOAT_EQ(y[0], 1.82f);
    EXPECT_FLOAT_EQ(y[1], 3.0f);
    EXPECT_FLOAT_EQ(y[2], 4.18f);
    EXPECT_FLOAT_EQ(y[3], 4.2f);
    EXPECT_FLOAT_EQ(y[4], 5.0f);
    EXPECT_FLOAT_EQ(y[5], 5.8f);
}