#include <gtest/gtest.h>

#include <mcutils/math/Vector6.h>

class TestVector6 : public ::testing::Test
{
protected:
    TestVector6() {}
    virtual ~TestVector6() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestVector6, CanInstantiate)
{
    mc::Vector6 v1;

    EXPECT_DOUBLE_EQ(v1(0), 0.0);
    EXPECT_DOUBLE_EQ(v1(1), 0.0);
    EXPECT_DOUBLE_EQ(v1(2), 0.0);
    EXPECT_DOUBLE_EQ(v1(3), 0.0);
    EXPECT_DOUBLE_EQ(v1(4), 0.0);
    EXPECT_DOUBLE_EQ(v1(5), 0.0);
}

TEST_F(TestVector6, CanGetNormalized)
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector6 v1;
    v1.SetFromArray(x1);
    mc::Vector6 v1_n = v1.GetNormalized();

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector6.m
    EXPECT_NEAR(v1_n(0), 0.104828, 1.0e-5);
    EXPECT_NEAR(v1_n(1), 0.209657, 1.0e-5);
    EXPECT_NEAR(v1_n(2), 0.314485, 1.0e-5);
    EXPECT_NEAR(v1_n(3), 0.419314, 1.0e-5);
    EXPECT_NEAR(v1_n(4), 0.524142, 1.0e-5);
    EXPECT_NEAR(v1_n(5), 0.628971, 1.0e-5);

    EXPECT_DOUBLE_EQ(v1_n.GetLength(), 1.0);
}

TEST_F(TestVector6, CanAssign)
{
    mc::Vector6 v;

    double x1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::Vector6 v1;
    v1.SetFromArray(x1);
    v = v1;
    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
    EXPECT_DOUBLE_EQ(v(3), 4.0);
    EXPECT_DOUBLE_EQ(v(4), 5.0);
    EXPECT_DOUBLE_EQ(v(5), 6.0);
}

TEST_F(TestVector6, CanAdd)
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    double x2[] = { 6.0, 5.0, 4.0, 3.0, 2.0, 1.0 };

    mc::Vector6 v1;
    mc::Vector6 v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    mc::Vector6 v12 = v1 + v2;

    EXPECT_DOUBLE_EQ(v12(0), 7.0);
    EXPECT_DOUBLE_EQ(v12(1), 7.0);
    EXPECT_DOUBLE_EQ(v12(2), 7.0);
    EXPECT_DOUBLE_EQ(v12(3), 7.0);
    EXPECT_DOUBLE_EQ(v12(4), 7.0);
    EXPECT_DOUBLE_EQ(v12(5), 7.0);
}

TEST_F(TestVector6, CanNegate)
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector6 v1;
    v1.SetFromArray(x1);
    mc::Vector6 v1n = -v1;
    EXPECT_DOUBLE_EQ(v1n(0), -1.0);
    EXPECT_DOUBLE_EQ(v1n(1), -2.0);
    EXPECT_DOUBLE_EQ(v1n(2), -3.0);
    EXPECT_DOUBLE_EQ(v1n(3), -4.0);
    EXPECT_DOUBLE_EQ(v1n(4), -5.0);
    EXPECT_DOUBLE_EQ(v1n(5), -6.0);
}

TEST_F(TestVector6, CanSubstract)
{
    double x1[] = { 6.0, 6.0, 6.0, 6.0, 6.0, 6.0 };
    double x2[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::Vector6 v1;
    mc::Vector6 v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    mc::Vector6 v = v1 - v2;

    EXPECT_DOUBLE_EQ(v(0), 5.0);
    EXPECT_DOUBLE_EQ(v(1), 4.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
    EXPECT_DOUBLE_EQ(v(3), 2.0);
    EXPECT_DOUBLE_EQ(v(4), 1.0);
    EXPECT_DOUBLE_EQ(v(5), 0.0);
}

TEST_F(TestVector6, CanMultiplyByScalar)
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::Vector6 v1;
    v1.SetFromArray(x1);

    mc::Vector6 v = v1 * 2.0;

    EXPECT_DOUBLE_EQ(v(0),  2.0);
    EXPECT_DOUBLE_EQ(v(1),  4.0);
    EXPECT_DOUBLE_EQ(v(2),  6.0);
    EXPECT_DOUBLE_EQ(v(3),  8.0);
    EXPECT_DOUBLE_EQ(v(4), 10.0);
    EXPECT_DOUBLE_EQ(v(5), 12.0);
}

TEST_F(TestVector6, CanDivideByScalar)
{
    double x1[] = { 2.0, 4.0, 6.0, 8.0, 10.0, 12.0 };

    mc::Vector6 v1;
    v1.SetFromArray(x1);

    mc::Vector6 v = v1 / 2.0;

    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
    EXPECT_DOUBLE_EQ(v(3), 4.0);
    EXPECT_DOUBLE_EQ(v(4), 5.0);
    EXPECT_DOUBLE_EQ(v(5), 6.0);
}

TEST_F(TestVector6, CanUnaryAdd)
{
    double x1[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double x2[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::Vector6 v1;
    mc::Vector6 v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    v1 += v2;

    EXPECT_DOUBLE_EQ(v1(0), 1.0);
    EXPECT_DOUBLE_EQ(v1(1), 2.0);
    EXPECT_DOUBLE_EQ(v1(2), 3.0);
    EXPECT_DOUBLE_EQ(v1(3), 4.0);
    EXPECT_DOUBLE_EQ(v1(4), 5.0);
    EXPECT_DOUBLE_EQ(v1(5), 6.0);
}

TEST_F(TestVector6, CanUnarySubstract)
{
    double x1[] = { 6.0, 6.0, 6.0, 6.0, 6.0, 6.0 };
    double x2[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::Vector6 v1;
    mc::Vector6 v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    v1 -= v2;

    EXPECT_DOUBLE_EQ(v1(0), 5.0);
    EXPECT_DOUBLE_EQ(v1(1), 4.0);
    EXPECT_DOUBLE_EQ(v1(2), 3.0);
    EXPECT_DOUBLE_EQ(v1(3), 2.0);
    EXPECT_DOUBLE_EQ(v1(4), 1.0);
    EXPECT_DOUBLE_EQ(v1(5), 0.0);
}

TEST_F(TestVector6, CanUnaryMultiplyByScalar)
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::Vector6 v1;
    v1.SetFromArray(x1);

    v1 *= 2.0;

    EXPECT_DOUBLE_EQ(v1(0),  2.0);
    EXPECT_DOUBLE_EQ(v1(1),  4.0);
    EXPECT_DOUBLE_EQ(v1(2),  6.0);
    EXPECT_DOUBLE_EQ(v1(3),  8.0);
    EXPECT_DOUBLE_EQ(v1(4), 10.0);
    EXPECT_DOUBLE_EQ(v1(5), 12.0);
}

TEST_F(TestVector6, CanUnaryDivideByScalar)
{
    double x1[] = { 2.0, 4.0, 6.0, 8.0, 10.0, 12.0 };

    mc::Vector6 v1;
    v1.SetFromArray(x1);

    v1 /= 2.0;

    EXPECT_DOUBLE_EQ(v1(0), 1.0);
    EXPECT_DOUBLE_EQ(v1(1), 2.0);
    EXPECT_DOUBLE_EQ(v1(2), 3.0);
    EXPECT_DOUBLE_EQ(v1(3), 4.0);
    EXPECT_DOUBLE_EQ(v1(4), 5.0);
    EXPECT_DOUBLE_EQ(v1(5), 6.0);
}
