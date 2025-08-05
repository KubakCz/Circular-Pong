#include <gtest/gtest.h>
#include "../math_library_dir/vector.hpp"
#include "../math_library_dir/mat4.hpp"
#include "../math_library_dir/quaternion.hpp"
#include <cstdio>
#define _USE_MATH_DEFINES
#include <math.h>

// Note: quaternions were chosen randomly and correct results were usually computed by wolfram alpha

TEST(quaternion_test_suite, unit)
{
    math::Quaternion q = math::Quaternion(5, 4, 9, 101);

    math::Quaternion uq = q.unit();

    const float sqrt = std::sqrtf(1147);

    EXPECT_FLOAT_EQ(uq.s(), 5 / (3 * sqrt));
    EXPECT_FLOAT_EQ(uq.u().x(), 4 / (3 * sqrt));
    EXPECT_FLOAT_EQ(uq.u().y(), 9 / (3 * sqrt));
    EXPECT_FLOAT_EQ(uq.u().z(), 101 / (3 * sqrt));
}

TEST(quaternion_test_suite, normalize)
{
    math::Quaternion q = math::Quaternion(7, 9, 11, 38);

    q.normalize();

    const float sqrt = std::sqrtf(1695);

    EXPECT_FLOAT_EQ(q.s(), 7 / sqrt);
    EXPECT_FLOAT_EQ(q.u().x(), 9 / sqrt);
    EXPECT_FLOAT_EQ(q.u().y(), 11 / sqrt);
    EXPECT_FLOAT_EQ(q.u().z(), 38 / sqrt);
}

TEST(quaternion_test_suite, mag)
{
    math::Quaternion q = math::Quaternion(21, 7, 8, 1);

    EXPECT_FLOAT_EQ(q.mag(), std::sqrtf(555));
}

TEST(quaternion_test_suite, magSquared)
{
    math::Quaternion q = math::Quaternion(42, 9, 9, 99);

    EXPECT_FLOAT_EQ(q.magSquared(), 9 * 1303);
}

TEST(quaternion_test_suite, conjugated)
{
    math::Quaternion q = math::Quaternion(5, 7, -85, -4);

    math::Quaternion cq = q.conjugated();

    EXPECT_FLOAT_EQ(cq.s(), 5);
    EXPECT_FLOAT_EQ(cq.u().x(), -7);
    EXPECT_FLOAT_EQ(cq.u().y(), 85);
    EXPECT_FLOAT_EQ(cq.u().z(), 4);
}

TEST(quaternion_test_suite, conjugate)
{
    math::Quaternion q = math::Quaternion(-8, 7, 0, -1);

    q.conjugate();

    EXPECT_FLOAT_EQ(q.s(), -8);
    EXPECT_FLOAT_EQ(q.u().x(), -7);
    EXPECT_FLOAT_EQ(q.u().y(), 0);
    EXPECT_FLOAT_EQ(q.u().z(), 1);
}

TEST(quaternion_test_suite, inversed)
{
    math::Quaternion q = math::Quaternion(5, 7, -85, -4);

    math::Quaternion cq = q.inversed();

    EXPECT_FLOAT_EQ(cq.s(), 1 / 1463.0f);
    EXPECT_FLOAT_EQ(cq.u().x(), -1 / 1045.0f);
    EXPECT_FLOAT_EQ(cq.u().y(), 17 / 1463.0f);
    EXPECT_FLOAT_EQ(cq.u().z(), 4 / 7315.0f);
}

TEST(quaternion_test_suite, inverse)
{
    math::Quaternion q = math::Quaternion(-8, 7, 0, -1);

    q.inverse();

    EXPECT_FLOAT_EQ(q.s(), -8 / 114.0f);
    EXPECT_FLOAT_EQ(q.u().x(), -7 / 114.0f);
    EXPECT_FLOAT_EQ(q.u().y(), 0 / 114.0f);
    EXPECT_FLOAT_EQ(q.u().z(), 1 / 114.0f);
}

TEST(quaternion_test_suite, plus)
{
    math::Quaternion lhs = math::Quaternion(1, 2, -3, -4);
    math::Quaternion rhs = math::Quaternion(-1, 5, -3, 0);

    math::Quaternion res = lhs + rhs;

    EXPECT_FLOAT_EQ(res.s(), 0);
    EXPECT_FLOAT_EQ(res.u().x(), 7);
    EXPECT_FLOAT_EQ(res.u().y(), -6);
    EXPECT_FLOAT_EQ(res.u().z(), -4);
}

TEST(quaternion_test_suite, minus)
{
    math::Quaternion lhs = math::Quaternion(1, 2, -3, -4);
    math::Quaternion rhs = math::Quaternion(-1, 5, -3, 0);

    math::Quaternion res = lhs - rhs;

    EXPECT_FLOAT_EQ(res.s(), 2);
    EXPECT_FLOAT_EQ(res.u().x(), -3);
    EXPECT_FLOAT_EQ(res.u().y(), 0);
    EXPECT_FLOAT_EQ(res.u().z(), -4);
}

TEST(quaternion_test_suite, q_times_q)
{
    math::Quaternion lhs = math::Quaternion(1, 3, -3, 1);
    math::Quaternion rhs = math::Quaternion(-1, 47, -42, 1);

    math::Quaternion res = lhs * rhs;

    EXPECT_FLOAT_EQ(res.s(), -269);
    EXPECT_FLOAT_EQ(res.u().x(), 83);
    EXPECT_FLOAT_EQ(res.u().y(), 5);
    EXPECT_FLOAT_EQ(res.u().z(), 15);
}

TEST(quaternion_test_suite, f_times_q)
{
    float f = 2;
    math::Quaternion q = math::Quaternion(-1, 47, -42, 1);

    math::Quaternion res = f * q;

    EXPECT_FLOAT_EQ(res.s(), -2);
    EXPECT_FLOAT_EQ(res.u().x(), 94);
    EXPECT_FLOAT_EQ(res.u().y(), -84);
    EXPECT_FLOAT_EQ(res.u().z(), 2);
}

TEST(quaternion_test_suite, q_times_f)
{
    float f = 2;
    math::Quaternion q = math::Quaternion(-1, 47, -42, 1);

    math::Quaternion res = q * f;

    EXPECT_FLOAT_EQ(res.s(), -2);
    EXPECT_FLOAT_EQ(res.u().x(), 94);
    EXPECT_FLOAT_EQ(res.u().y(), -84);
    EXPECT_FLOAT_EQ(res.u().z(), 2);
}

TEST(quaternion_test_suite, q_div_f)
{
    float f = 2;
    math::Quaternion q = math::Quaternion(-1, 47, -42, 1);

    math::Quaternion res = q / f;

    EXPECT_FLOAT_EQ(res.s(), -1 / 2.0f);
    EXPECT_FLOAT_EQ(res.u().x(), 47 / 2.0f);
    EXPECT_FLOAT_EQ(res.u().y(), -42 / 2.0f);
    EXPECT_FLOAT_EQ(res.u().z(), 1 / 2.0f);
}

TEST(quaternion_test_suite, dot)
{
    math::Quaternion p = math::Quaternion(1, 0, 0, 3);
    math::Quaternion q = math::Quaternion(-1, 3, 3, -2);

    EXPECT_FLOAT_EQ(math::dot(p, q), -1 - 6);
}

TEST(quaternion_test_suite, slerp)
{
    math::Quaternion q0 = math::Quaternion(.5f, .5f, .5f, .5f);
    math::Quaternion q1 = math::Quaternion(.6f, 0, .8f, 0);

    math::Quaternion res = math::slerp(q0, q1, 0);
    EXPECT_FLOAT_EQ(res.s(), q0.s());
    EXPECT_FLOAT_EQ(res.u().x(), q0.u().x());
    EXPECT_FLOAT_EQ(res.u().y(), q0.u().y());
    EXPECT_FLOAT_EQ(res.u().z(), q0.u().z());

    res = math::slerp(q0, q1, 1);
    EXPECT_FLOAT_EQ(res.s(), q1.s());
    EXPECT_FLOAT_EQ(res.u().x(), q1.u().x());
    EXPECT_FLOAT_EQ(res.u().y(), q1.u().y());
    EXPECT_FLOAT_EQ(res.u().z(), q1.u().z());

    // calculator https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
    res = math::slerp(q0, q1, .3f);
    EXPECT_FLOAT_EQ(res.s(), 0.5685756960725247f);
    EXPECT_FLOAT_EQ(res.u().x(), 0.3699922203957914f);
    EXPECT_FLOAT_EQ(res.u().y(), 0.6347701879647691f);
    EXPECT_FLOAT_EQ(res.u().z(), 0.3699922203957914f);
}

TEST(quaternion_test_suite, to_rot_matrix)
{
    // test result by comparing transformation by computed rotation matrix and by precomputed rotation matrix
    // computed rotation matrix will be different, but must perform the same transformation

    math::Quaternion q = math::Quaternion(2, -1, -2, 3); // tested quaternion
    math::Vec4 p = math::Vec4(4, 3, 2, 1);               // point to be transformed

    math::Mat4 qm = q.toRotMatrix(); // tested rotation matrix
    float correctMatData[16] = {
        -4 / 9.0f, -4 / 9.0f, -7 / 9.0f, 0,
        8 / 9.0f, -1 / 9.0f, -4 / 9.0f, 0,
        1 / 9.0f, -8 / 9.0f, 4 / 9.0f, 0,
        0, 0, 0, 1};
    math::Mat4 correctRM = math::Mat4(correctMatData); // correct rotation matrix

    math::Vec4 cT = correctRM * p; // correct transform
    math::Vec4 tT = qm * p;        // tested transform

    EXPECT_NEAR(tT.x() / tT.w(), cT.x() / cT.w(), 1e-6);
    EXPECT_NEAR(tT.y() / tT.w(), cT.y() / cT.w(), 1e-6);
    EXPECT_NEAR(tT.z() / tT.w(), cT.z() / cT.w(), 1e-6);
}

TEST(quaternion_test_suite, to_axis_angle)
{
    math::Quaternion q = math::Quaternion(8, -2, 3, 1);

    math::AxisAngle aa = q.toAxisAngle();

    EXPECT_NEAR(aa.axis().x(), -std::sqrtf(2 / 7.0f), 1e-6);
    EXPECT_NEAR(aa.axis().y(), 3 * std::sqrtf(1 / 14.0f), 1e-6);
    EXPECT_NEAR(aa.axis().z(), std::sqrtf(1 / 14.0f), 1e-6);
    EXPECT_NEAR(aa.angle(), 2 * std::acosf(4 * std::sqrtf(2 / 39.0f)), 1e-6);
}

TEST(quaternion_test_suite, from_axis_angle)
{
    float origAngle = 1.23f;
    math::Vec3 origAxis = math::Vec3(3, -1, 2);

    math::Quaternion q = math::Quaternion::fromAxisAngle(math::Vec3(3, -1, 2), 1.23f); // testing

    EXPECT_FLOAT_EQ(q.magSquared(), 1);

    math::AxisAngle aa = q.toAxisAngle(); // already tested

    origAxis.normalize();

    EXPECT_NEAR(aa.axis().x(), origAxis.x(), 1e-6);
    EXPECT_NEAR(aa.axis().y(), origAxis.y(), 1e-6);
    EXPECT_NEAR(aa.axis().z(), origAxis.z(), 1e-6);
    EXPECT_NEAR(aa.angle(), origAngle, 1e-6);
}

TEST(quaternion_test_suite, euler_angles_01)
{
    math::Quaternion q = math::Quaternion::fromEulerAngles((float)(-M_PI / 4), (float)M_PI, 0.0f);
    math::Vec3 cx = math::Vec3(-1, 0, 0).unit();
    math::Vec3 cy = math::Vec3(0, 1, 1).unit();
    math::Vec3 cz = math::Vec3(0, 1, -1).unit();

    math::Mat4 m = q.toRotMatrix();

    math::Vec3 tx = math::Vec3(m.get(0, 0), m.get(1, 0), m.get(2, 0)).unit();
    math::Vec3 ty = math::Vec3(m.get(0, 1), m.get(1, 1), m.get(2, 1)).unit();
    math::Vec3 tz = math::Vec3(m.get(0, 2), m.get(1, 2), m.get(2, 2)).unit();

    EXPECT_NEAR(tx.x(), cx.x(), 1e-6);
    EXPECT_NEAR(tx.y(), cx.y(), 1e-6);
    EXPECT_NEAR(tx.z(), cx.z(), 1e-6);

    EXPECT_NEAR(ty.x(), cy.x(), 1e-6);
    EXPECT_NEAR(ty.y(), cy.y(), 1e-6);
    EXPECT_NEAR(ty.z(), cy.z(), 1e-6);

    EXPECT_NEAR(tz.x(), cz.x(), 1e-6);
    EXPECT_NEAR(tz.y(), cz.y(), 1e-6);
    EXPECT_NEAR(tz.z(), cz.z(), 1e-6);
}

TEST(quaternion_test_suite, euler_angles_02)
{
    // tested agains https://www.andre-gaschler.com/rotationconverter/
    math::Quaternion q = math::Quaternion::fromEulerAngles(1.2f, 2, 2.1f); // testing

    EXPECT_NEAR(q.x(), 0.7542197f, 1e-6);
    EXPECT_NEAR(q.y(), 0.0809297f, 1e-6);
    EXPECT_NEAR(q.z(), 0.1503996f, 1e-6);
    EXPECT_NEAR(q.s(), 0.6340212f, 1e-6);
}

TEST(quaternion_test_suite, from_rot_matrix_01)
{
    // rot around x by pi/2
    math::Vec3 x = math::Vec3::right;
    math::Vec3 y = math::Vec3::forward;
    math::Vec3 z = math::Vec3::down;

    float data[16] = {
        x.x(), y.x(), z.x(), 0,
        x.y(), y.y(), z.y(), 0,
        x.z(), y.z(), z.z(), 0,
        0, 0, 0, 1};
    math::Mat4 crm = math::Mat4(data);

    math::Quaternion q = math::Quaternion::fromRotMatrix(crm);

    math::Mat4 rm = q.toRotMatrix();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            EXPECT_NEAR(rm.get(i, j), crm.get(i, j), 1e-6) << "i: " << i << ", j: " << j;
        }
    }
}

TEST(quaternion_test_suite, from_rot_matrix_02)
{
    math::Vec3 x = math::Vec3::forward;
    math::Vec3 y = math::Vec3::right;
    math::Vec3 z = math::Vec3::up;

    float data[16] = {
        x.x(), y.x(), z.x(), 0,
        x.y(), y.y(), z.y(), 0,
        x.z(), y.z(), z.z(), 0,
        0, 0, 0, 1};
    math::Mat4 crm = math::Mat4(data);

    math::Quaternion q = math::Quaternion::fromRotMatrix(crm);

    math::Mat4 rm = q.toRotMatrix();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            EXPECT_NEAR(rm.get(i, j), crm.get(i, j), 1e-6) << "i: " << i << ", j: " << j;
        }
    }
}

TEST(quaternion_test_suite, from_rot_matrix_03)
{
    math::Vec3 x = math::Vec3(1, -8, 3).unit();
    math::Vec3 y = math::cross(x, math::Vec3::one).unit();
    math::Vec3 z = math::cross(x, y).unit();

    EXPECT_NEAR(math::dot(x, y), 0, 1e-6);
    EXPECT_NEAR(math::dot(x, z), 0, 1e-6);
    EXPECT_NEAR(math::dot(y, z), 0, 1e-6);

    float data[16] = {
        x.x(), y.x(), z.x(), 0,
        x.y(), y.y(), z.y(), 0,
        x.z(), y.z(), z.z(), 0,
        0, 0, 0, 1};
    math::Mat4 crm = math::Mat4(data);

    math::Quaternion q = math::Quaternion::fromRotMatrix(crm);
    q.normalize();
    EXPECT_NEAR(q.magSquared(), 1, 1e-6);

    math::Mat4 rm = q.toRotMatrix();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            EXPECT_NEAR(rm.get(i, j), crm.get(i, j), 1e-6) << "i: " << i << ", j: " << j;
        }
    }
}
