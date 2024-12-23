#include <gtest/gtest.h>

#include <mcutils/math/Vector.h>

class TestVectorN : public ::testing::Test
{
protected:
    TestVectorN() {}
    virtual ~TestVectorN() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestVectorN, CanInstantiate)
{
    constexpr int size = 3;
    mc::VectorN<double,size> v;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), 0.0) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanValidate)
{
    constexpr int size = 3;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    mc::VectorN<double,size> v;
    v.SetFromVector(x);
    EXPECT_TRUE(v.IsValid());
    v(0) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(v.IsValid());
}

TEST_F(TestVectorN, CanGetHalfLength)
{
    constexpr int size = 3;
    mc::VectorN<double,size> v;

    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    // 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
    EXPECT_DOUBLE_EQ(v.GetLength2(), 14.0);
}

TEST_F(TestVectorN, CanGetLength)
{
    constexpr int size = 3;
    mc::VectorN<double,size> v;

    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m
    // sqrt( 1^2 + 2^2 + 3^2 ) = sqrt( 1 + 4 + 9 ) = sqrt( 14 )
    EXPECT_NEAR(v.GetLength(), 3.741657, 1.0e-5);
}

TEST_F(TestVectorN, CanNormalize)
{
    constexpr int size = 3;
    mc::VectorN<double,size> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.SetFromVector(x);

    v.Normalize();

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m
    EXPECT_NEAR(v(0), 0.267261, 1.0e-5);
    EXPECT_NEAR(v(1), 0.534522, 1.0e-5);
    EXPECT_NEAR(v(2), 0.801784, 1.0e-5);

    EXPECT_DOUBLE_EQ(v.GetLength(), 1.0);
}

TEST_F(TestVectorN, CanPutIntoArray)
{
    constexpr int size = 3;
    mc::VectorN<double,size> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.SetFromVector(x);
    std::vector<double> result;
    result = v.GetVector();

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(result[i], x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSetFromArray)
{
    constexpr int size = 3;
    mc::VectorN<double,size> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.SetFromVector(x);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSetFromString)
{
    constexpr int size = 3;
    char str[] = { " 1.0  2.0  3.0 " };
    mc::VectorN<double,size> v;
    v.SetFromString(str);

    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
}

TEST_F(TestVectorN, CanSetFromInvalidString)
{
    constexpr int size = 3;
    char str[] = { "lorem ipsum" };
    mc::VectorN<double,size> v;
    v.SetFromString(str);
    EXPECT_FALSE(v.IsValid());
}

TEST_F(TestVectorN, CanSwapRows)
{
    constexpr int size = 3;
    mc::VectorN<double,size> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.SetFromVector(x);

    v.SwapRows(0, 1);
    EXPECT_DOUBLE_EQ(v(0), 2.0);
    EXPECT_DOUBLE_EQ(v(1), 1.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
}

TEST_F(TestVectorN, CanConvertToString)
{
    constexpr int size = 3;
    mc::VectorN<double,size> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.SetFromVector(x);
    EXPECT_STREQ(v.ToString().c_str(), "1,2,3");
}

TEST_F(TestVectorN, CanZeroize)
{
    constexpr int size = 3;
    mc::VectorN<double,size> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.SetFromVector(x);
    v.Zeroize();

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), 0.0) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanAccessItemViaOperator)
{
    constexpr int size = 3;
    mc::VectorN<double,size> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.SetFromVector(x);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanAdd)
{
    constexpr int size = 3;

    std::vector<double> x1 { 1.0, 2.0, 3.0 };
    std::vector<double> x2 { 4.0, 5.0, 6.0 };

    mc::VectorN<double,size> v1;
    mc::VectorN<double,size> v2;

    v1.SetFromVector(x1);
    v2.SetFromVector(x2);

    mc::VectorN<double,size> vr = v1 + v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x1[i] + x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanNegate)
{
    constexpr int size = 3;
    mc::VectorN<double,size> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.SetFromVector(x);

    mc::VectorN<double,size> vr = -v;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), -x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSubstract)
{
    constexpr int size = 3;

    std::vector<double> x1 { 1.0, 2.0, 3.0 };
    std::vector<double> x2 { 4.0, 5.0, 6.0 };

    mc::VectorN<double,size> v1;
    mc::VectorN<double,size> v2;

    v1.SetFromVector(x1);
    v2.SetFromVector(x2);

    mc::VectorN<double,size> vr = v1 - v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x1[i] - x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanMultiplyByNumber)
{
    constexpr int size = 3;

    std::vector<double> x { 1.0, 2.0, 3.0 };
    mc::VectorN<double,size> v;
    v.SetFromVector(x);

    constexpr double val = 2.0;
    mc::VectorN<double,size> vr = v * val;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x[i] * val) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanCalculateDotProduct)
{
    constexpr int size = 3;

    std::vector<double> x1 { 1.0, 0.0, 0.0 };
    std::vector<double> x2 { 0.0, 1.0, 0.0 };
    std::vector<double> x3 { 0.0, 0.0, 1.0 };
    std::vector<double> x4 { 1.0, 2.0, 3.0 };

    mc::VectorN<double,size> v1;
    mc::VectorN<double,size> v2;
    mc::VectorN<double,size> v3;
    mc::VectorN<double,size> v4;

    v1.SetFromVector(x1);
    v2.SetFromVector(x2);
    v3.SetFromVector(x3);
    v4.SetFromVector(x4);

    double s1 = v4 * v1;
    double s2 = v4 * v2;
    double s3 = v4 * v3;
    double s4 = v4 * v4;

    EXPECT_DOUBLE_EQ(s1,  1.0);
    EXPECT_DOUBLE_EQ(s2,  2.0);
    EXPECT_DOUBLE_EQ(s3,  3.0);
    EXPECT_DOUBLE_EQ(s4, 14.0);
}

TEST_F(TestVectorN, CanDivideByNumber)
{
    constexpr int size = 3;

    std::vector<double> x { 1.0, 2.0, 3.0 };
    mc::VectorN<double,size> v;
    v.SetFromVector(x);

    constexpr double val = 2.0;
    mc::VectorN<double,size> vr = v / val;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x[i] / val) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryAdd)
{
    constexpr int size = 3;

    std::vector<double> x1 { 1.0, 2.0, 3.0 };
    std::vector<double> x2 { 4.0, 5.0, 6.0 };

    mc::VectorN<double,size> v1;
    mc::VectorN<double,size> v2;

    v1.SetFromVector(x1);
    v2.SetFromVector(x2);

    v1 += v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v1(i), x1[i] + x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnarySubstract)
{
    constexpr int size = 3;

    std::vector<double> x1 { 1.0, 2.0, 3.0 };
    std::vector<double> x2 { 4.0, 5.0, 6.0 };

    mc::VectorN<double,size> v1;
    mc::VectorN<double,size> v2;

    v1.SetFromVector(x1);
    v2.SetFromVector(x2);

    v1 -= v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v1(i), x1[i] - x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryMultiplyByNumber)
{
    constexpr int size = 3;

    std::vector<double> x { 1.0, 2.0, 3.0 };
    mc::VectorN<double,size> v;
    v.SetFromVector(x);

    constexpr double val = 2.0;
    v *= val;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i] * val) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryDivideByNumber)
{
    constexpr int size = 3;

    std::vector<double> x { 1.0, 2.0, 3.0 };
    mc::VectorN<double,size> v;
    v.SetFromVector(x);

    constexpr double val = 2.0;
    v /= val;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i] / val) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanCompare)
{
    constexpr int size = 3;

    std::vector<double> x1 { 2.0, 4.0, 6.0 };
    std::vector<double> x2 { 1.0, 2.0, 3.0 };
    mc::VectorN<double,size> v1;
    mc::VectorN<double,size> v2;
    mc::VectorN<double,size> v3;
    v1.SetFromVector(x1);
    v2.SetFromVector(x2);
    v3.SetFromVector(x1);

    EXPECT_FALSE(v1 == v2);
    EXPECT_FALSE(v3 == v2);
    EXPECT_FALSE(v3 != v1);

    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v3 != v2);
    EXPECT_TRUE(v3 == v1);
}
