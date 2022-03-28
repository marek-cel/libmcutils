#include <gtest/gtest.h>

#include <mcutil/math/Vector.h>

////////////////////////////////////////////////////////////////////////////////

class TestVector : public ::testing::Test
{
protected:
    TestVector() {}
    virtual ~TestVector() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanConstruct)
{
    mc::Vector<3> *v = nullptr;
    EXPECT_NO_THROW( ( v = new mc::Vector<3>() ) );
    delete v;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanDestruct)
{
    mc::Vector<3> *v = new mc::Vector<3>();
    EXPECT_NO_THROW( delete v );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanInstantiate)
{
    mc::Vector<3> v1;

    EXPECT_DOUBLE_EQ( v1( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanInstantiateAndCopy)
{
    const double d1[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1( d1 );

    mc::Vector<3> v2( v1 );

    EXPECT_DOUBLE_EQ( v2( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanInstantiateAndSetData)
{
    const double d1[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1( d1 );

    EXPECT_DOUBLE_EQ( v1( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanValidate)
{
    const double d1[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1( d1 );
    EXPECT_TRUE( v1.isValid() );

    const double d2[] { std::numeric_limits<double>::quiet_NaN(), 2.0, 3.0 };
    mc::Vector<3> v2( d2 );
    EXPECT_FALSE( v2.isValid() );

    const double d3[] { 1.0, std::numeric_limits<double>::quiet_NaN(), 3.0 };
    mc::Vector<3> v3( d3 );
    EXPECT_FALSE( v3.isValid() );

    const double d4[] { 1.0, 2.0, std::numeric_limits<double>::quiet_NaN() };
    mc::Vector<3> v4( d4 );
    EXPECT_FALSE( v4.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanGetLength2)
{
    mc::Vector<3> v1;

    EXPECT_DOUBLE_EQ( v1.getLength2(), 0.0 );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;

    // 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
    EXPECT_DOUBLE_EQ( v1.getLength2(), 14.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanGetLength)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m

    mc::Vector<3> v1;

    EXPECT_DOUBLE_EQ( v1.getLength(), 0.0 );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;

    // sqrt( 1^2 + 2^2 + 3^2 ) = sqrt( 1 + 4 + 9 ) = sqrt( 14 )
    EXPECT_NEAR( v1.getLength(), 3.741657, 1.0e-5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanNormalize)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m

    const double d1[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1( d1 );

    v1.normalize();

    EXPECT_NEAR( v1(0), 0.267261, 1.0e-5 );
    EXPECT_NEAR( v1(1), 0.534522, 1.0e-5 );
    EXPECT_NEAR( v1(2), 0.801784, 1.0e-5 );

    EXPECT_DOUBLE_EQ( v1.getLength(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanGetArray)
{
    const double d1[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1( d1 );

    double d2[3];
    v1.getArray( d2 );

    EXPECT_DOUBLE_EQ( d2[ 0 ], d1[ 0 ] );
    EXPECT_DOUBLE_EQ( d2[ 1 ], d1[ 1 ] );
    EXPECT_DOUBLE_EQ( d2[ 2 ], d1[ 2 ] );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanGetItem)
{
    const double d1[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1( d1 );

    EXPECT_DOUBLE_EQ( v1.getItem( 0 ), d1[ 0 ] );
    EXPECT_DOUBLE_EQ( v1.getItem( 1 ), d1[ 1 ] );
    EXPECT_DOUBLE_EQ( v1.getItem( 2 ), d1[ 2 ] );

    double r3 = v1.getItem(3);

    EXPECT_FALSE( r3 == 23 ); // NaN
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanSetArray)
{
    mc::Vector<3> v1;

    const double d1[] { 1.0, 2.0, 3.0 };

    v1.setArray( d1 );

    EXPECT_DOUBLE_EQ( v1( 0 ), d1[ 0 ] );
    EXPECT_DOUBLE_EQ( v1( 1 ), d1[ 1 ] );
    EXPECT_DOUBLE_EQ( v1( 2 ), d1[ 2 ] );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanSetItem)
{
    mc::Vector<3> v1;

    v1.setItem( 0, 1.0 );
    v1.setItem( 1, 2.0 );
    v1.setItem( 2, 3.0 );

    EXPECT_DOUBLE_EQ( v1( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanSwapRows)
{
    const double d1[] { 1.0, 2.0, 3.0 };

    mc::Vector<3> v1( d1 );
    v1.swapRows( 0, 1 );
    EXPECT_DOUBLE_EQ( v1( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 3.0 );

    mc::Vector< 3 > v2( d1 );
    v2.swapRows( 1, 2 );
    EXPECT_DOUBLE_EQ( v2( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), 3.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), 2.0 );

    mc::Vector< 3 > v3( d1 );
    v3.swapRows( 0, 2 );
    EXPECT_DOUBLE_EQ( v3( 0 ), 3.0 );
    EXPECT_DOUBLE_EQ( v3( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v3( 2 ), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanConvertToString)
{
    const double d1[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1( d1 );

    EXPECT_STREQ( v1.toString().c_str(), "1,2,3" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanZeroize)
{
    const double d1[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1( d1 );

    v1.zeroize();

    EXPECT_DOUBLE_EQ( v1( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanAccessItemViaOperator)
{
    const double d1[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1( d1 );

    EXPECT_DOUBLE_EQ( v1( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanAssign)
{
    mc::Vector<3> v;

    double x1[] { 1.0, 0.0, 0.0 };
    double x2[] { 0.0, 1.0, 0.0 };
    double x3[] { 0.0, 0.0, 1.0 };
    double x4[] { 1.0, 2.0, 3.0 };

    mc::Vector<3> v1( x1 );
    mc::Vector<3> v2( x2 );
    mc::Vector<3> v3( x3 );
    mc::Vector<3> v4( x4 );

    v = v1;
    EXPECT_DOUBLE_EQ( v( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 0.0 );

    v = v2;
    EXPECT_DOUBLE_EQ( v( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 0.0 );

    v = v3;
    EXPECT_DOUBLE_EQ( v( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 1.0 );

    v = v4;
    EXPECT_DOUBLE_EQ( v( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanAdd)
{
    double x1[] { 1.0, 2.0, 3.0 };
    double x2[] { 3.0, 2.0, 1.0 };
    double x3[] { 0.0, 0.0, 0.0 };
    double x4[] { 1.0, 2.0, 3.0 };

    mc::Vector<3> v1( x1 );
    mc::Vector<3> v2( x2 );
    mc::Vector<3> v3( x3 );
    mc::Vector<3> v4( x4 );

    mc::Vector<3> v12 = v1 + v2;
    mc::Vector<3> v34 = v3 + v4;

    EXPECT_DOUBLE_EQ( v12( 0 ), 4.0 );
    EXPECT_DOUBLE_EQ( v12( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v12( 2 ), 4.0 );

    EXPECT_DOUBLE_EQ( v34( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v34( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v34( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanNegate)
{
    double x[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1( x );

    mc::Vector<3> v2 = -v1;

    EXPECT_DOUBLE_EQ( v2( 0 ), -1.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), -2.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), -3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanSubstract)
{
    double x1[] = { 3.0, 3.0, 3.0 };
    double x2[] = { 1.0, 2.0, 3.0 };

    mc::Vector<3> v1( x1 );
    mc::Vector<3> v2( x2 );

    mc::Vector<3> v = v1 - v2;

    EXPECT_DOUBLE_EQ( v( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanMultiplyByScalar)
{
    double x[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1( x );

    mc::Vector<3> v2 = v1 * 2.0;

    EXPECT_DOUBLE_EQ( v2( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanCalculateDotProduct)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m

    double x1[] = { 1.0, 0.0, 0.0, 0.0 };
    double x2[] = { 0.0, 1.0, 0.0, 0.0 };
    double x3[] = { 0.0, 0.0, 1.0, 0.0 };
    double x4[] = { 0.0, 0.0, 0.0, 1.0 };
    double x5[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector<4> v1( x1 );
    mc::Vector<4> v2( x2 );
    mc::Vector<4> v3( x3 );
    mc::Vector<4> v4( x4 );
    mc::Vector<4> v5( x5 );

    double s51 = v5 * v1;
    double s52 = v5 * v2;
    double s53 = v5 * v3;
    double s54 = v5 * v4;
    double s55 = v5 * v5;

    EXPECT_DOUBLE_EQ( s51,  1.0 );
    EXPECT_DOUBLE_EQ( s52,  2.0 );
    EXPECT_DOUBLE_EQ( s53,  3.0 );
    EXPECT_DOUBLE_EQ( s54,  4.0 );
    EXPECT_DOUBLE_EQ( s55, 30.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanSivideByScalar)
{
    double x[] { 2.0, 4.0, 6.0 };
    mc::Vector<3> v1( x );

    mc::Vector<3> v2 = v1 / 2.0;

    EXPECT_DOUBLE_EQ( v2( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanUnaryAdd)
{
    double x0[] { 1.0, 2.0, 3.0 };
    double x1[] { 2.0, 3.0, 4.0 };

    mc::Vector<3> v0( x0 );
    mc::Vector<3> v1( x1 );

    v0 += v1;

    EXPECT_DOUBLE_EQ( v0( 0 ), 3.0 );
    EXPECT_DOUBLE_EQ( v0( 1 ), 5.0 );
    EXPECT_DOUBLE_EQ( v0( 2 ), 7.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanUnarySubstract)
{
    double x0[] { 3.0, 3.0, 3.0 };
    double x1[] { 1.0, 2.0, 3.0 };

    mc::Vector<3> v0( x0 );
    mc::Vector<3> v1( x1 );

    v0 -= v1;

    EXPECT_DOUBLE_EQ( v0( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v0( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v0( 2 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanUnaryMultiplyByScalar)
{
    double x0[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v0( x0 );

    v0 *= 2.0;

    EXPECT_DOUBLE_EQ( v0( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v0( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v0( 2 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanUnaryDivideByScalar)
{
    double x0[] { 2.0, 4.0, 6.0 };
    mc::Vector<3> v0( x0 );

    v0 /= 2.0;

    EXPECT_DOUBLE_EQ( v0( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v0( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v0( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanComparer)
{
    double x0[] = { 2.0, 4.0, 6.0 };
    double x1[] = { 1.0, 2.0, 3.0 };

    mc::Vector<3> v0( x0 );
    mc::Vector<3> v1( x1 );
    mc::Vector<3> v2( x0 );

    EXPECT_FALSE( v0 == v1 );
    EXPECT_FALSE( v2 == v1 );
    EXPECT_FALSE( v2 != v0 );

    EXPECT_TRUE( v0 != v1 );
    EXPECT_TRUE( v2 != v1 );
    EXPECT_TRUE( v2 == v0 );
}
