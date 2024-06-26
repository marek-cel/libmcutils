#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/math/Vector.h>

class TestVector : public ::testing::Test
{
protected:
    TestVector() {}
    virtual ~TestVector() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestVector, CanInstantiate)
{
    mc::Vector v1(3);

    EXPECT_EQ(v1.size(), 3);

    EXPECT_DOUBLE_EQ(v1(0), 0.0);
    EXPECT_DOUBLE_EQ(v1(1), 0.0);
    EXPECT_DOUBLE_EQ(v1(2), 0.0);
}

TEST_F(TestVector, CanInstantiateAndCopy)
{
    mc::Vector v1(3);

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;

    mc::Vector v2(v1);

    EXPECT_DOUBLE_EQ(v2(0), 1.0);
    EXPECT_DOUBLE_EQ(v2(1), 2.0);
    EXPECT_DOUBLE_EQ(v2(2), 3.0);

    EXPECT_EQ(v2.size(), 3);
}

TEST_F(TestVector, CanInstantiateAndMove)
{
    mc::Vector v1(3);

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;

    mc::Vector v2(std::move(v1));

    EXPECT_DOUBLE_EQ(v2(0), 1.0);
    EXPECT_DOUBLE_EQ(v2(1), 2.0);
    EXPECT_DOUBLE_EQ(v2(2), 3.0);

    EXPECT_EQ(v2.size(), 3);
}

TEST_F(TestVector, CanValidate)
{
    mc::Vector v1(3);

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;

    EXPECT_TRUE(v1.IsValid());

    v1(0) = std::numeric_limits<double>::quiet_NaN();
    v1(1) = 2.0;
    v1(2) = 3.0;

    EXPECT_FALSE(v1.IsValid());

    v1(0) = 1.0;
    v1(1) = std::numeric_limits<double>::quiet_NaN();
    v1(2) = 3.0;

    EXPECT_FALSE(v1.IsValid());

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE(v1.IsValid());

    v1(0) = std::numeric_limits<double>::quiet_NaN();
    v1(1) = std::numeric_limits<double>::quiet_NaN();
    v1(2) = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE(v1.IsValid());
}

TEST_F(TestVector, CanGetLength)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m

    mc::Vector v1(3);

    EXPECT_DOUBLE_EQ(v1.GetLength(), 0.0);

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;

    // sqrt( 1^2 + 2^2 + 3^2 ) = sqrt( 1 + 4 + 9 ) = sqrt( 14 )
    EXPECT_NEAR(v1.GetLength(), 3.741657, 1.0e-5);
}

TEST_F(TestVector, CanNormalize)
{
    mc::Vector v1(3);

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;

    v1.Normalize();

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector3.m
    EXPECT_NEAR(v1(0), 0.267261, 1.0e-5);
    EXPECT_NEAR(v1(1), 0.534522, 1.0e-5);
    EXPECT_NEAR(v1(2), 0.801784, 1.0e-5);

    EXPECT_DOUBLE_EQ(v1.GetLength(), 1.0);
}

TEST_F(TestVector, CanGetElement)
{
    mc::Vector v1(3);

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;

    EXPECT_DOUBLE_EQ(v1.GetElement(0), 1.0);
    EXPECT_DOUBLE_EQ(v1.GetElement(1), 2.0);
    EXPECT_DOUBLE_EQ(v1.GetElement(2), 3.0);
}

TEST_F(TestVector, CanPutIntoArray)
{
    mc::Vector v1(4);

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;
    v1(3) = 4.0;

    double x[4];

    v1.PutIntoArray(x);

    EXPECT_DOUBLE_EQ(x[0], 1.0);
    EXPECT_DOUBLE_EQ(x[1], 2.0);
    EXPECT_DOUBLE_EQ(x[2], 3.0);
    EXPECT_DOUBLE_EQ(x[3], 4.0);
}

TEST_F(TestVector, CanGetElementOutOfRange)
{
    mc::Vector v1(3);

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;

    EXPECT_TRUE(std::isnan(v1.GetElement(3)));
}

TEST_F(TestVector, CanSetElement)
{
    mc::Vector v1(3);

    v1.SetElement(0, 1.0);
    v1.SetElement(1, 2.0);
    v1.SetElement(2, 3.0);

    EXPECT_DOUBLE_EQ(v1(0), 1.0);
    EXPECT_DOUBLE_EQ(v1(1), 2.0);
    EXPECT_DOUBLE_EQ(v1(2), 3.0);
}

TEST_F(TestVector, CanSetFromArray)
{
    mc::Vector v1(3);

    double x[] = { 1.0, 2.0, 3.0 };

    v1.SetFromArray(x);

    EXPECT_DOUBLE_EQ(v1(0), 1.0);
    EXPECT_DOUBLE_EQ(v1(1), 2.0);
    EXPECT_DOUBLE_EQ(v1(2), 3.0);
}

TEST_F(TestVector, CanGetSize)
{
    mc::Vector v0(0);
    EXPECT_EQ(v0.size(), 0);

    mc::Vector v3(3);
    EXPECT_EQ(v3.size(), 3);
}

TEST_F(TestVector, CanConvertToString)
{
    mc::Vector v1(3);

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;

    EXPECT_STREQ(v1.ToString().c_str(), "1,2,3");
}

TEST_F(TestVector, CanResize)
{
    mc::Vector v(0);
    EXPECT_EQ(v.size(), 0);

    v.Resize(3);
    EXPECT_EQ(v.size(), 3);

    v.Resize(6);
    EXPECT_EQ(v.size(), 6);
}

TEST_F(TestVector, CanZeroize)
{
    mc::Vector v1(3);

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;

    v1.Zeroize();

    EXPECT_DOUBLE_EQ(v1(0), 0.0);
    EXPECT_DOUBLE_EQ(v1(1), 0.0);
    EXPECT_DOUBLE_EQ(v1(2), 0.0);
}

TEST_F(TestVector, CanAccessItemViaOperator)
{
    mc::Vector v1(4);

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;
    v1(3) = 4.0;

    EXPECT_DOUBLE_EQ(v1(0), 1.0);
    EXPECT_DOUBLE_EQ(v1(1), 2.0);
    EXPECT_DOUBLE_EQ(v1(2), 3.0);
    EXPECT_DOUBLE_EQ(v1(3), 4.0);
}

TEST_F(TestVector, CanAssign)
{
    mc::Vector v(3);
    double x1[] = { 1.0, 2.0, 3.0 };
    mc::Vector v1(3);
    v1.SetFromArray(x1);
    v = v1;
    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
}

TEST_F(TestVector, CanAssignAndMove)
{
    mc::Vector v(3);
    double x1[] = { 1.0, 2.0, 3.0 };
    mc::Vector v1(3);
    v1.SetFromArray(x1);
    v = std::move(v1);
    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
}

TEST_F(TestVector, CanAdd)
{
    double x1[] = { 1.0, 2.0, 3.0 };
    double x2[] = { 4.0, 5.0, 6.0 };
    
    mc::Vector v1(3);
    mc::Vector v2(3);

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    mc::Vector v12 = v1 + v2;

    EXPECT_DOUBLE_EQ(v12(0), 5.0);
    EXPECT_DOUBLE_EQ(v12(1), 7.0);
    EXPECT_DOUBLE_EQ(v12(2), 9.0);
}

TEST_F(TestVector, CanAddWrongSize)
{
    mc::Vector v1(3);
    mc::Vector v2(4);

    mc::Vector v12 = v1 + v2;

    EXPECT_TRUE(std::isnan(v12(0)));
    EXPECT_TRUE(std::isnan(v12(1)));
    EXPECT_TRUE(std::isnan(v12(2)));
}

TEST_F(TestVector, CanNegate)
{
    double x[] = { 1.0, 2.0, 3.0 };

    mc::Vector v1(3);
    v1.SetFromArray(x);

    mc::Vector v2 = -v1;

    EXPECT_DOUBLE_EQ(v2(0), -1.0);
    EXPECT_DOUBLE_EQ(v2(1), -2.0);
    EXPECT_DOUBLE_EQ(v2(2), -3.0);
}

TEST_F(TestVector, CanSubstract)
{
    double x1[] = { 3.0, 3.0, 3.0 };
    double x2[] = { 1.0, 2.0, 3.0 };

    mc::Vector v1(3);
    mc::Vector v2(3);

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    mc::Vector v = v1 - v2;

    EXPECT_DOUBLE_EQ(v(0), 2.0);
    EXPECT_DOUBLE_EQ(v(1), 1.0);
    EXPECT_DOUBLE_EQ(v(2), 0.0);
}

TEST_F(TestVector, CanSubstractWrongSize)
{
    mc::Vector v1(3);
    mc::Vector v2(4);

    mc::Vector v12 = v1 - v2;

    EXPECT_TRUE(std::isnan(v12(0)));
    EXPECT_TRUE(std::isnan(v12(1)));
    EXPECT_TRUE(std::isnan(v12(2)));
}

TEST_F(TestVector, CanMultiplyByScalar)
{
    double x[] = { 1.0, 2.0, 3.0 };

    mc::Vector v1(3);

    v1.SetFromArray(x);

    mc::Vector v2 = v1 * 2.0;

    EXPECT_DOUBLE_EQ(v2(0), 2.0);
    EXPECT_DOUBLE_EQ(v2(1), 4.0);
    EXPECT_DOUBLE_EQ(v2(2), 6.0);
}

TEST_F(TestVector, CandivideByScalar)
{
    double x[] = { 2.0, 4.0, 6.0 };

    mc::Vector v1(3);

    v1.SetFromArray(x);

    mc::Vector v2 = v1 / 2.0;

    EXPECT_DOUBLE_EQ(v2(0), 1.0);
    EXPECT_DOUBLE_EQ(v2(1), 2.0);
    EXPECT_DOUBLE_EQ(v2(2), 3.0);
}

TEST_F(TestVector, CanUnaryAdd)
{
    double x0[] = { 1.0, 2.0, 3.0 };
    double x1[] = { 3.0, 2.0, 1.0 };

    mc::Vector v0(3);
    mc::Vector v1(3);

    v0.SetFromArray(x0);
    v1.SetFromArray(x1);

    v0 += v1;

    EXPECT_DOUBLE_EQ(v0(0), 4.0);
    EXPECT_DOUBLE_EQ(v0(1), 4.0);
    EXPECT_DOUBLE_EQ(v0(2), 4.0);
}

TEST_F(TestVector, CanUnarySubstract)
{
    double x0[] = { 3.0, 3.0, 3.0 };
    double x1[] = { 1.0, 2.0, 3.0 };

    mc::Vector v0(3);
    mc::Vector v1(3);

    v0.SetFromArray(x0);
    v1.SetFromArray(x1);

    v0 -= v1;

    EXPECT_DOUBLE_EQ(v0(0), 2.0);
    EXPECT_DOUBLE_EQ(v0(1), 1.0);
    EXPECT_DOUBLE_EQ(v0(2), 0.0);
}

TEST_F(TestVector, CanUnaryMultiplyByScalar)
{
    double x0[] = { 1.0, 2.0, 3.0 };

    mc::Vector v0(3);

    v0.SetFromArray(x0);

    v0 *= 2.0;

    EXPECT_DOUBLE_EQ(v0(0), 2.0);
    EXPECT_DOUBLE_EQ(v0(1), 4.0);
    EXPECT_DOUBLE_EQ(v0(2), 6.0);
}

TEST_F(TestVector, CanUnaryDivideByScalar)
{
    double x0[] = { 2.0, 4.0, 6.0 };

    mc::Vector v0(3);

    v0.SetFromArray(x0);

    v0 /= 2.0;

    EXPECT_DOUBLE_EQ(v0(0), 1.0);
    EXPECT_DOUBLE_EQ(v0(1), 2.0);
    EXPECT_DOUBLE_EQ(v0(2), 3.0);
}
