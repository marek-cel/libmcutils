#include <gtest/gtest.h>

#include <mcutils/math/Vector4.h>

class TestVector4 : public ::testing::Test
{
protected:
    TestVector4() {}
    virtual ~TestVector4() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestVector4, CanInstantiate)
{
    mc::Vector4 v1;

    EXPECT_DOUBLE_EQ(v1(0), 0.0);
    EXPECT_DOUBLE_EQ(v1(1), 0.0);
    EXPECT_DOUBLE_EQ(v1(2), 0.0);
    EXPECT_DOUBLE_EQ(v1(3), 0.0);
}

TEST_F(TestVector4, CanGetNormalized)
{
    const double d1[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector4 v1;
    v1.SetFromArray(d1);
    mc::Vector4 v1_n = v1.GetNormalized();

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector4.m
    EXPECT_NEAR(v1_n(0), 0.182574, 1.0e-5);
    EXPECT_NEAR(v1_n(1), 0.365148, 1.0e-5);
    EXPECT_NEAR(v1_n(2), 0.547723, 1.0e-5);
    EXPECT_NEAR(v1_n(3), 0.730297, 1.0e-5);

    EXPECT_DOUBLE_EQ(v1_n.GetLength(), 1.0);
}

TEST_F(TestVector4, CanAssign)
{
    mc::Vector4 v;
    double x1[] = { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector4 v1;
    v1.SetFromArray(x1);
    v = v1;
    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
    EXPECT_DOUBLE_EQ(v(3), 4.0);
}

TEST_F(TestVector4, CanAdd)
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0 };
    double x2[] = { 4.0, 3.0, 2.0, 1.0 };

    mc::Vector4 v1;
    mc::Vector4 v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    mc::Vector4 v12 = v1 + v2;

    EXPECT_DOUBLE_EQ(v12(0), 5.0);
    EXPECT_DOUBLE_EQ(v12(1), 5.0);
    EXPECT_DOUBLE_EQ(v12(2), 5.0);
    EXPECT_DOUBLE_EQ(v12(3), 5.0);
}

TEST_F(TestVector4, CanNegate)
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector4 v1;
    v1.SetFromArray(x1);
    mc::Vector4 v1n = -v1;
    EXPECT_DOUBLE_EQ(v1n(0), -1.0);
    EXPECT_DOUBLE_EQ(v1n(1), -2.0);
    EXPECT_DOUBLE_EQ(v1n(2), -3.0);
    EXPECT_DOUBLE_EQ(v1n(3), -4.0);
}

TEST_F(TestVector4, CanSubstract)
{
    double x1[] = { 4.0, 4.0, 4.0, 4.0 };
    double x2[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector4 v1;
    mc::Vector4 v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    mc::Vector4 v = v1 - v2;

    EXPECT_DOUBLE_EQ(v(0), 3.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 1.0);
    EXPECT_DOUBLE_EQ(v(3), 0.0);
}

TEST_F(TestVector4, CanMultiplyByScalar)
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector4 v1;
    v1.SetFromArray(x1);

    mc::Vector4 v = v1 * 2.0;

    EXPECT_DOUBLE_EQ(v(0), 2.0);
    EXPECT_DOUBLE_EQ(v(1), 4.0);
    EXPECT_DOUBLE_EQ(v(2), 6.0);
    EXPECT_DOUBLE_EQ(v(3), 8.0);
}

TEST_F(TestVector4, CanDivideByScalar)
{
    double x1[] = { 2.0, 4.0, 6.0, 8.0 };

    mc::Vector4 v1;
    v1.SetFromArray(x1);

    mc::Vector4 v = v1 / 2.0;

    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
    EXPECT_DOUBLE_EQ(v(3), 4.0);
}

TEST_F(TestVector4, CanUnaryAdd)
{
    double x1[] = { 0.0, 0.0, 0.0, 0.0 };
    double x2[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector4 v1;
    mc::Vector4 v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    v1 += v2;

    EXPECT_DOUBLE_EQ(v1(0), 1.0);
    EXPECT_DOUBLE_EQ(v1(1), 2.0);
    EXPECT_DOUBLE_EQ(v1(2), 3.0);
    EXPECT_DOUBLE_EQ(v1(3), 4.0);
}

TEST_F(TestVector4, CanUnarySubstract)
{
    double x1[] = { 4.0, 4.0, 4.0, 4.0 };
    double x2[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector4 v1;
    mc::Vector4 v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    v1 -= v2;

    EXPECT_DOUBLE_EQ(v1(0), 3.0);
    EXPECT_DOUBLE_EQ(v1(1), 2.0);
    EXPECT_DOUBLE_EQ(v1(2), 1.0);
    EXPECT_DOUBLE_EQ(v1(3), 0.0);
}

TEST_F(TestVector4, CanUnaryMultiplyByScalar)
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector4 v1;
    v1.SetFromArray(x1);

    v1 *= 2.0;

    EXPECT_DOUBLE_EQ(v1(0), 2.0);
    EXPECT_DOUBLE_EQ(v1(1), 4.0);
    EXPECT_DOUBLE_EQ(v1(2), 6.0);
    EXPECT_DOUBLE_EQ(v1(3), 8.0);
}

TEST_F(TestVector4, CanUnaryDivideByScalar)
{
    double x1[] = { 2.0, 4.0, 6.0, 8.0 };

    mc::Vector4 v1;
    v1.SetFromArray(x1);

    v1 /= 2.0;

    EXPECT_DOUBLE_EQ(v1(0), 1.0);
    EXPECT_DOUBLE_EQ(v1(1), 2.0);
    EXPECT_DOUBLE_EQ(v1(2), 3.0);
    EXPECT_DOUBLE_EQ(v1(3), 4.0);
}
