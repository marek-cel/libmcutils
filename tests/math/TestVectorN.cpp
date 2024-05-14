#include <gtest/gtest.h>

#include <mcutils/math/VectorN.h>

// To achieve full test coverage of VectorN template class some tests have
// to be done for 3, 4, and 6 elements vectors, as template class VectorN has 
// derived classes which are not templates. (e.g. all operators)

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
    mc::VectorN<size> v;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), 0.0) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanValidate3)
{
    constexpr int size = 3;
    const double x[] { 1.0, 2.0, 3.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);
    EXPECT_TRUE(v.IsValid());
    v(0) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(v.IsValid());
}

TEST_F(TestVectorN, CanValidate4)
{
    constexpr int size = 4;
    const double x[] { 1.0, 2.0, 3.0, 4.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);
    EXPECT_TRUE(v.IsValid());
    v(0) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(v.IsValid());
}

TEST_F(TestVectorN, CanValidate6)
{
    constexpr int size = 6;
    const double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);
    EXPECT_TRUE(v.IsValid());
    v(0) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(v.IsValid());
}

TEST_F(TestVectorN, CanGetHalfLength3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;

    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    // 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
    EXPECT_DOUBLE_EQ(v.GetLength2(), 14.0);
}

TEST_F(TestVectorN, CanGetHalfLength4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;

    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;
    v(3) = 0.0;

    // 1^2 + 2^2 + 3^2 + 0^2 = 1 + 4 + 9 + 0 = 14
    EXPECT_DOUBLE_EQ(v.GetLength2(), 14.0);
}

TEST_F(TestVectorN, CanGetHalfLength6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;

    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;
    v(3) = 0.0;
    v(4) = 0.0;
    v(5) = 0.0;

    // 1^2 + 2^2 + 3^2 + 0^2 + 0^2 + 0^2 = 1 + 4 + 9 + 0 + 0 + 0 = 14
    EXPECT_DOUBLE_EQ(v.GetLength2(), 14.0);
}

TEST_F(TestVectorN, CanGetLength3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;

    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m
    // sqrt( 1^2 + 2^2 + 3^2 ) = sqrt( 1 + 4 + 9 ) = sqrt( 14 )
    EXPECT_NEAR(v.GetLength(), 3.741657, 1.0e-5);
}

TEST_F(TestVectorN, CanGetLength4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;

    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;
    v(3) = 0.0;

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m
    // sqrt( 1^2 + 2^2 + 3^2 ) = sqrt( 1 + 4 + 9 ) = sqrt( 14 )
    EXPECT_NEAR(v.GetLength(), 3.741657, 1.0e-5);
}

TEST_F(TestVectorN, CanGetLength6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;

    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;
    v(3) = 0.0;
    v(4) = 0.0;
    v(5) = 0.0;

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m
    // sqrt( 1^2 + 2^2 + 3^2 ) = sqrt( 1 + 4 + 9 ) = sqrt( 14 )
    EXPECT_NEAR(v.GetLength(), 3.741657, 1.0e-5);
}

TEST_F(TestVectorN, CanNormalize3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0 };
    v.SetFromArray(x);

    v.Normalize();

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m
    EXPECT_NEAR(v(0), 0.267261, 1.0e-5);
    EXPECT_NEAR(v(1), 0.534522, 1.0e-5);
    EXPECT_NEAR(v(2), 0.801784, 1.0e-5);

    EXPECT_DOUBLE_EQ(v.GetLength(), 1.0);
}

TEST_F(TestVectorN, CanNormalize4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0 };
    v.SetFromArray(x);

    v.Normalize();

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m
    EXPECT_NEAR(v(0), 0.182574, 1.0e-5);
    EXPECT_NEAR(v(1), 0.365148, 1.0e-5);
    EXPECT_NEAR(v(2), 0.547723, 1.0e-5);
    EXPECT_NEAR(v(3), 0.730297, 1.0e-5);

    EXPECT_DOUBLE_EQ(v.GetLength(), 1.0);
}

TEST_F(TestVectorN, CanNormalize6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    v.SetFromArray(x);

    v.Normalize();

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m
    EXPECT_NEAR(v(0), 0.104828, 1.0e-5);
    EXPECT_NEAR(v(1), 0.209657, 1.0e-5);
    EXPECT_NEAR(v(2), 0.314485, 1.0e-5);
    EXPECT_NEAR(v(3), 0.419314, 1.0e-5);
    EXPECT_NEAR(v(4), 0.524142, 1.0e-5);
    EXPECT_NEAR(v(5), 0.628971, 1.0e-5);

    EXPECT_DOUBLE_EQ(v.GetLength(), 1.0);
}

TEST_F(TestVectorN, CanGetElement3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0 };
    v.SetFromArray(x);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v.GetElement(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanGetElement4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0 };
    v.SetFromArray(x);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v.GetElement(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanGetElement6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    v.SetFromArray(x);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v.GetElement(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanGetElementWithInvalidIndex3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;
    double x = v.GetElement(size);
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestVectorN, CanGetElementWithInvalidIndex4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;
    double x = v.GetElement(size);
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestVectorN, CanGetElementWithInvalidIndex6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;
    double x = v.GetElement(size);
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestVectorN, CanPutIntoArray3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0 };
    v.SetFromArray(x);
    double result[size];
    v.PutIntoArray(result);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(result[i], x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanPutIntoArray4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0 };
    v.SetFromArray(x);
    double result[size];
    v.PutIntoArray(result);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(result[i], x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanPutIntoArray6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    v.SetFromArray(x);
    double result[size];
    v.PutIntoArray(result);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(result[i], x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSetElement3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;

    v.SetElement(0, 1.0);
    v.SetElement(1, 2.0);
    v.SetElement(2, 3.0);

    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
}

TEST_F(TestVectorN, CanSetElement4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;

    v.SetElement(0, 1.0);
    v.SetElement(1, 2.0);
    v.SetElement(2, 3.0);
    v.SetElement(3, 4.0);

    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
    EXPECT_DOUBLE_EQ(v(3), 4.0);
}

TEST_F(TestVectorN, CanSetElement6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;

    v.SetElement(0, 1.0);
    v.SetElement(1, 2.0);
    v.SetElement(2, 3.0);
    v.SetElement(3, 4.0);
    v.SetElement(4, 5.0);
    v.SetElement(5, 6.0);

    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
    EXPECT_DOUBLE_EQ(v(3), 4.0);
    EXPECT_DOUBLE_EQ(v(4), 5.0);
    EXPECT_DOUBLE_EQ(v(5), 6.0);
}

TEST_F(TestVectorN, CanSetFromArray3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0 };
    v.SetFromArray(x);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSetFromArray4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0 };
    v.SetFromArray(x);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSetFromArray6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    v.SetFromArray(x);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSetFromString3)
{
    constexpr int size = 3;
    char str[] = { " 1.0  2.0  3.0 " };
    mc::VectorN<size> v;
    v.SetFromString(str);

    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
}

TEST_F(TestVectorN, CanSetFromString4)
{
    constexpr int size = 4;
    char str[] = { " 1.0 2.0 3.0 4.0 " };
    mc::VectorN<size> v;
    v.SetFromString(str);

    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
    EXPECT_DOUBLE_EQ(v(3), 4.0);
}

TEST_F(TestVectorN, CanSetFromString6)
{
    constexpr int size = 6;
    char str[] = { "1.0  2.0  3.0  4.0  5.0  6.0" };
    mc::VectorN<size> v;
    v.SetFromString(str);

    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
    EXPECT_DOUBLE_EQ(v(3), 4.0);
    EXPECT_DOUBLE_EQ(v(4), 5.0);
    EXPECT_DOUBLE_EQ(v(5), 6.0);
}

TEST_F(TestVectorN, CanSetFromInvalidString3)
{
    constexpr int size = 3;
    char str[] = { "lorem ipsum" };
    mc::VectorN<size> v;
    v.SetFromString(str);
    EXPECT_FALSE(v.IsValid());
}

TEST_F(TestVectorN, CanSetFromInvalidString4)
{
    constexpr int size = 4;
    char str[] = { "lorem ipsum" };
    mc::VectorN<size> v;
    v.SetFromString(str);
    EXPECT_FALSE(v.IsValid());
}

TEST_F(TestVectorN, CanSetFromInvalidString6)
{
    constexpr int size = 6;
    char str[] = { "lorem ipsum" };
    mc::VectorN<size> v;
    v.SetFromString(str);
    EXPECT_FALSE(v.IsValid());
}

TEST_F(TestVectorN, CanSwapRows3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0 };
    v.SetFromArray(x);
    
    v.SwapRows(0, 1);
    EXPECT_DOUBLE_EQ(v(0), 2.0);
    EXPECT_DOUBLE_EQ(v(1), 1.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
}

TEST_F(TestVectorN, CanSwapRows4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0 };
    v.SetFromArray(x);
    
    v.SwapRows(0, 1);
    EXPECT_DOUBLE_EQ(v(0), 2.0);
    EXPECT_DOUBLE_EQ(v(1), 1.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
    EXPECT_DOUBLE_EQ(v(3), 4.0);
}

TEST_F(TestVectorN, CanSwapRows6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    v.SetFromArray(x);
    
    v.SwapRows(0, 1);
    EXPECT_DOUBLE_EQ(v(0), 2.0);
    EXPECT_DOUBLE_EQ(v(1), 1.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
    EXPECT_DOUBLE_EQ(v(3), 4.0);
    EXPECT_DOUBLE_EQ(v(4), 5.0);
    EXPECT_DOUBLE_EQ(v(5), 6.0);
}

TEST_F(TestVectorN, CanConvertToString3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0 };
    v.SetFromArray(x);
    EXPECT_STREQ(v.ToString().c_str(), "1,2,3");
}

TEST_F(TestVectorN, CanConvertToString4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0 };
    v.SetFromArray(x);
    EXPECT_STREQ(v.ToString().c_str(), "1,2,3,4");
}

TEST_F(TestVectorN, CanConvertToString6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    v.SetFromArray(x);
    EXPECT_STREQ(v.ToString().c_str(), "1,2,3,4,5,6");
}

TEST_F(TestVectorN, CanZeroize3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0 };
    v.SetFromArray(x);
    v.Zeroize();

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), 0.0) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanZeroize4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0 };
    v.SetFromArray(x);
    v.Zeroize();

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), 0.0) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanZeroize6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    v.SetFromArray(x);
    v.Zeroize();

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), 0.0) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanAccessItemViaOperator3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0 };
    v.SetFromArray(x);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanAccessItemViaOperator4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0 };
    v.SetFromArray(x);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanAccessItemViaOperator6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    v.SetFromArray(x);

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanAdd3)
{
    constexpr int size = 3;

    double x1[] { 1.0, 2.0, 3.0 };
    double x2[] { 4.0, 5.0, 6.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    mc::VectorN<size> vr = v1 + v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x1[i] + x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanAdd4)
{
    constexpr int size = 4;

    double x1[] { 1.0, 2.0, 3.0, 4.0 };
    double x2[] { 5.0, 6.0, 7.0, 8.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    mc::VectorN<size> vr = v1 + v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x1[i] + x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanAdd6)
{
    constexpr int size = 6;

    double x1[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double x2[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    mc::VectorN<size> vr = v1 + v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x1[i] + x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanNegate3)
{
    constexpr int size = 3;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0 };
    v.SetFromArray(x);

    mc::VectorN<size> vr = -v;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), -x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanNegate4)
{
    constexpr int size = 4;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0 };
    v.SetFromArray(x);

    mc::VectorN<size> vr = -v;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), -x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanNegate6)
{
    constexpr int size = 6;
    mc::VectorN<size> v;
    const double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    v.SetFromArray(x);

    mc::VectorN<size> vr = -v;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), -x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSubstract3)
{
    constexpr int size = 3;

    double x1[] { 1.0, 2.0, 3.0 };
    double x2[] { 4.0, 5.0, 6.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    mc::VectorN<size> vr = v1 - v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x1[i] - x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSubstract4)
{
    constexpr int size = 4;

    double x1[] { 1.0, 2.0, 3.0, 4.0 };
    double x2[] { 5.0, 6.0, 7.0, 8.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    mc::VectorN<size> vr = v1 - v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x1[i] - x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSubstract6)
{
    constexpr int size = 6;

    double x1[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double x2[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    mc::VectorN<size> vr = v1 - v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x1[i] - x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanMultiplyByScalar3)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);

    constexpr double scalar = 2.0;
    mc::VectorN<size> vr = v * scalar;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x[i] * scalar) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanMultiplyByScalar4)
{
    constexpr int size = 4;

    double x[] { 1.0, 2.0, 3.0, 4.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);

    constexpr double scalar = 2.0;
    mc::VectorN<size> vr = v * scalar;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x[i] * scalar) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanMultiplyByScalar6)
{
    constexpr int size = 6;

    double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);

    constexpr double scalar = 2.0;
    mc::VectorN<size> vr = v * scalar;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x[i] * scalar) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanCalculateDotProduct3)
{
    constexpr int size = 3;

    double x1[] = { 1.0, 0.0, 0.0 };
    double x2[] = { 0.0, 1.0, 0.0 };
    double x3[] = { 0.0, 0.0, 1.0 };
    double x4[] = { 1.0, 2.0, 3.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;
    mc::VectorN<size> v3;
    mc::VectorN<size> v4;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);
    v3.SetFromArray(x3);
    v4.SetFromArray(x4);

    double s1 = v4 * v1;
    double s2 = v4 * v2;
    double s3 = v4 * v3;
    double s4 = v4 * v4;

    EXPECT_DOUBLE_EQ(s1,  1.0);
    EXPECT_DOUBLE_EQ(s2,  2.0);
    EXPECT_DOUBLE_EQ(s3,  3.0);
    EXPECT_DOUBLE_EQ(s4, 14.0);
}

TEST_F(TestVectorN, CanCalculateDotProduct4)
{
    constexpr int size = 4;

    double x1[] = { 1.0, 0.0, 0.0, 0.0 };
    double x2[] = { 0.0, 1.0, 0.0, 0.0 };
    double x3[] = { 0.0, 0.0, 1.0, 0.0 };
    double x4[] = { 0.0, 0.0, 0.0, 1.0 };
    double x5[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;
    mc::VectorN<size> v3;
    mc::VectorN<size> v4;
    mc::VectorN<size> v5;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);
    v3.SetFromArray(x3);
    v4.SetFromArray(x4);
    v5.SetFromArray(x5);

    double s1 = v5 * v1;
    double s2 = v5 * v2;
    double s3 = v5 * v3;
    double s4 = v5 * v4;
    double s5 = v5 * v5;

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m
    EXPECT_DOUBLE_EQ(s1,  1.0);
    EXPECT_DOUBLE_EQ(s2,  2.0);
    EXPECT_DOUBLE_EQ(s3,  3.0);
    EXPECT_DOUBLE_EQ(s4,  4.0);
    EXPECT_DOUBLE_EQ(s5, 30.0);
}

TEST_F(TestVectorN, CanCalculateDotProduct6)
{
    constexpr int size = 6;

    double x1[] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double x2[] = { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
    double x3[] = { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 };
    double x4[] = { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
    double x5[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;
    mc::VectorN<size> v3;
    mc::VectorN<size> v4;
    mc::VectorN<size> v5;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);
    v3.SetFromArray(x3);
    v4.SetFromArray(x4);
    v5.SetFromArray(x5);

    double s1 = v5 * v1;
    double s2 = v5 * v2;
    double s3 = v5 * v3;
    double s4 = v5 * v4;
    double s5 = v5 * v5;

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m
    EXPECT_DOUBLE_EQ(s1,  1.0);
    EXPECT_DOUBLE_EQ(s2,  2.0);
    EXPECT_DOUBLE_EQ(s3,  3.0);
    EXPECT_DOUBLE_EQ(s4,  4.0);
    EXPECT_DOUBLE_EQ(s5, 91.0);
}

TEST_F(TestVectorN, CanDivideByScalar3)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);

    constexpr double scalar = 2.0;
    mc::VectorN<size> vr = v / scalar;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x[i] / scalar) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanDivideByScalar4)
{
    constexpr int size = 4;

    double x[] { 1.0, 2.0, 3.0, 4.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);

    constexpr double scalar = 2.0;
    mc::VectorN<size> vr = v / scalar;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x[i] / scalar) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanDivideByScalar6)
{
    constexpr int size = 6;

    double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);

    constexpr double scalar = 2.0;
    mc::VectorN<size> vr = v / scalar;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x[i] / scalar) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryAdd3)
{
    constexpr int size = 3;

    double x1[] { 1.0, 2.0, 3.0 };
    double x2[] { 4.0, 5.0, 6.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    v1 += v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v1(i), x1[i] + x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryAdd4)
{
    constexpr int size = 4;

    double x1[] { 1.0, 2.0, 3.0, 4.0 };
    double x2[] { 5.0, 6.0, 7.0, 8.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    v1 += v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v1(i), x1[i] + x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryAdd6)
{
    constexpr int size = 6;

    double x1[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double x2[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    v1 += v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v1(i), x1[i] + x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnarySubstract3)
{
    constexpr int size = 3;

    double x1[] { 1.0, 2.0, 3.0 };
    double x2[] { 4.0, 5.0, 6.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    v1 -= v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v1(i), x1[i] - x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnarySubstract4)
{
    constexpr int size = 4;

    double x1[] { 1.0, 2.0, 3.0, 4.0 };
    double x2[] { 5.0, 6.0, 7.0, 8.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    v1 -= v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v1(i), x1[i] - x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnarySubstract6)
{
    constexpr int size = 6;

    double x1[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double x2[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::VectorN<size> v1;
    mc::VectorN<size> v2;

    v1.SetFromArray(x1);
    v2.SetFromArray(x2);

    v1 -= v2;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v1(i), x1[i] - x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryMultiplyByScalar3)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);

    constexpr double scalar = 2.0;
    v *= scalar;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i] * scalar) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryMultiplyByScalar4)
{
    constexpr int size = 4;

    double x[] { 1.0, 2.0, 3.0, 4.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);

    constexpr double scalar = 2.0;
    v *= scalar;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i] * scalar) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryMultiplyByScalar6)
{
    constexpr int size = 6;

    double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);

    constexpr double scalar = 2.0;
    v *= scalar;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i] * scalar) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryDivideByScalar3)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);

    constexpr double scalar = 2.0;
    v /= scalar;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i] / scalar) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryDivideByScalar4)
{
    constexpr int size = 4;

    double x[] { 1.0, 2.0, 3.0, 4.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);

    constexpr double scalar = 2.0;
    v /= scalar;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i] / scalar) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryDivideByScalar6)
{
    constexpr int size = 6;

    double x[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::VectorN<size> v;
    v.SetFromArray(x);

    constexpr double scalar = 2.0;
    v /= scalar;

    for ( int i = 0; i < size; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i] / scalar) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanCompare3)
{
    constexpr int size = 3;

    double x1[] = { 2.0, 4.0, 6.0 };
    double x2[] = { 1.0, 2.0, 3.0 };
    mc::VectorN<size> v1;
    mc::VectorN<size> v2;
    mc::VectorN<size> v3;
    v1.SetFromArray(x1);
    v2.SetFromArray(x2);
    v3.SetFromArray(x1);

    EXPECT_FALSE(v1 == v2);
    EXPECT_FALSE(v3 == v2);
    EXPECT_FALSE(v3 != v1);

    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v3 != v2);
    EXPECT_TRUE(v3 == v1);
}

TEST_F(TestVectorN, CanCompare4)
{
    constexpr int size = 4;

    double x1[] = { 2.0, 4.0, 6.0, 8.0 };
    double x2[] = { 3.0, 5.0, 7.0, 9.0 };
    mc::VectorN<size> v1;
    mc::VectorN<size> v2;
    mc::VectorN<size> v3;
    v1.SetFromArray(x1);
    v2.SetFromArray(x2);
    v3.SetFromArray(x1);

    EXPECT_FALSE(v1 == v2);
    EXPECT_FALSE(v3 == v2);
    EXPECT_FALSE(v3 != v1);

    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v3 != v2);
    EXPECT_TRUE(v3 == v1);
}

TEST_F(TestVectorN, CanCompare6)
{
    constexpr int size = 6;

    double x1[] = { 2.0, 4.0, 6.0, 8.0, 10.0, 12.0 };
    double x2[] = { 1.0, 3.0, 5.0, 7.0,  9.0, 11.0 };
    mc::VectorN<size> v1;
    mc::VectorN<size> v2;
    mc::VectorN<size> v3;
    v1.SetFromArray(x1);
    v2.SetFromArray(x2);
    v3.SetFromArray(x1);

    EXPECT_FALSE(v1 == v2);
    EXPECT_FALSE(v3 == v2);
    EXPECT_FALSE(v3 != v1);

    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v3 != v2);
    EXPECT_TRUE(v3 == v1);
}
