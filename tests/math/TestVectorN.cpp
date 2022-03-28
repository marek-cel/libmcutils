#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/math/VectorN.h>

////////////////////////////////////////////////////////////////////////////////

class TestVectorN : public ::testing::Test
{
protected:
    TestVectorN() {}
    virtual ~TestVectorN() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanConstruct)
{
    mc::VectorN *v = nullptr;
    EXPECT_NO_THROW( v = new mc::VectorN() );
    delete v;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanDestruct)
{
    mc::VectorN *v = new mc::VectorN();
    EXPECT_NO_THROW( delete v );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanInstantiate)
{
    mc::VectorN v1( 3 );

    EXPECT_EQ( v1.getSize(), 3 );

    EXPECT_DOUBLE_EQ( v1( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanInstantiateAndCopy)
{
    mc::VectorN v1( 3 );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;

    mc::VectorN v2( v1 );

    EXPECT_DOUBLE_EQ( v2( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), 3.0 );

    EXPECT_EQ( v2.getSize(), 3 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanValidate)
{
    mc::VectorN v1( 3 );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;

    EXPECT_TRUE( v1.isValid() );

    v1( 0 ) = std::numeric_limits<double>::quiet_NaN();
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;

    EXPECT_FALSE( v1.isValid() );

    v1( 0 ) = 1.0;
    v1( 1 ) = std::numeric_limits<double>::quiet_NaN();
    v1( 2 ) = 3.0;

    EXPECT_FALSE( v1.isValid() );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE( v1.isValid() );

    v1( 0 ) = std::numeric_limits<double>::quiet_NaN();
    v1( 1 ) = std::numeric_limits<double>::quiet_NaN();
    v1( 2 ) = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE( v1.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanGetLength)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m

    mc::VectorN v1( 3 );

    EXPECT_DOUBLE_EQ( v1.getLength(), 0.0 );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;

    // sqrt( 1^2 + 2^2 + 3^2 ) = sqrt( 1 + 4 + 9 ) = sqrt( 14 )
    EXPECT_NEAR( v1.getLength(), 3.741657, 1.0e-5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanNormalize)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector3.m
    // tests/math/octave/test_vector4.m

    mc::VectorN v1( 3 );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;

    v1.normalize();

    EXPECT_NEAR( v1( 0 ), 0.267261, 1.0e-5 );
    EXPECT_NEAR( v1( 1 ), 0.534522, 1.0e-5 );
    EXPECT_NEAR( v1( 2 ), 0.801784, 1.0e-5 );

    EXPECT_DOUBLE_EQ( v1.getLength(), 1.0 );

    mc::VectorN v2( 4 );

    v2( 0 ) = 1.0;
    v2( 1 ) = 2.0;
    v2( 2 ) = 3.0;
    v2( 3 ) = 4.0;

    v2.normalize();

    EXPECT_NEAR( v2( 0 ), 0.182574, 1.0e-5 );
    EXPECT_NEAR( v2( 1 ), 0.365148, 1.0e-5 );
    EXPECT_NEAR( v2( 2 ), 0.547723, 1.0e-5 );
    EXPECT_NEAR( v2( 3 ), 0.730297, 1.0e-5 );

    EXPECT_DOUBLE_EQ( v2.getLength(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanGetArray)
{
    mc::VectorN v1( 4 );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;
    v1( 3 ) = 4.0;

    double x[4];

    v1.getArray( x );

    EXPECT_DOUBLE_EQ( x[ 0 ], 1.0 );
    EXPECT_DOUBLE_EQ( x[ 1 ], 2.0 );
    EXPECT_DOUBLE_EQ( x[ 2 ], 3.0 );
    EXPECT_DOUBLE_EQ( x[ 3 ], 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanGetItem)
{
    mc::VectorN v1( 3 );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;

    EXPECT_DOUBLE_EQ( v1.getItem( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1.getItem( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1.getItem( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanGetItemOutOfRange)
{
    mc::VectorN v1( 3 );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;

    EXPECT_TRUE( std::isnan( v1.getItem( 3 ) ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanSetArray)
{
    mc::VectorN v1( 3 );

    double x[] = { 1.0, 2.0, 3.0 };

    v1.setArray( x );

    EXPECT_DOUBLE_EQ( v1( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanSetItem)
{
    mc::VectorN v1( 3 );

    v1.setItem( 0, 1.0 );
    v1.setItem( 1, 2.0 );
    v1.setItem( 2, 3.0 );

    EXPECT_DOUBLE_EQ( v1( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanSetValue)
{
    mc::VectorN v1( 3 );

    v1.setValue( 1.0 );

    EXPECT_DOUBLE_EQ( v1( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanGetSize)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanConvertToString)
{
    mc::VectorN v1( 3 );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;

    EXPECT_STREQ( v1.toString().c_str(), "1,2,3" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanResize)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanZeroize)
{
    mc::VectorN v1( 3 );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;

    v1.zeroize();

    EXPECT_DOUBLE_EQ( v1( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanAccessItemViaOperator)
{
    mc::VectorN v1( 4 );

    v1( 0 ) = 1.0;
    v1( 1 ) = 2.0;
    v1( 2 ) = 3.0;
    v1( 3 ) = 4.0;

    EXPECT_DOUBLE_EQ( v1( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v1( 3 ), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanAssign)
{
    mc::VectorN v( 3 );

    double x1[] = { 1.0, 0.0, 0.0 };
    double x2[] = { 0.0, 1.0, 0.0 };
    double x3[] = { 0.0, 0.0, 1.0 };
    double x4[] = { 1.0, 2.0, 3.0 };

    mc::VectorN v1( 3 );
    mc::VectorN v2( 3 );
    mc::VectorN v3( 3 );
    mc::VectorN v4( 3 );

    v1.setArray( x1 );
    v2.setArray( x2 );
    v3.setArray( x3 );
    v4.setArray( x4 );

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

TEST_F(TestVectorN, CanAdd)
{
    double x1[] = { 1.0, 2.0, 3.0 };
    double x2[] = { 3.0, 2.0, 1.0 };
    double x3[] = { 0.0, 0.0, 0.0 };
    double x4[] = { 1.0, 2.0, 3.0 };

    mc::VectorN v1( 3 );
    mc::VectorN v2( 3 );
    mc::VectorN v3( 3 );
    mc::VectorN v4( 3 );

    v1.setArray( x1 );
    v2.setArray( x2 );
    v3.setArray( x3 );
    v4.setArray( x4 );

    mc::VectorN v12 = v1 + v2;
    mc::VectorN v34 = v3 + v4;

    EXPECT_DOUBLE_EQ( v12( 0 ), 4.0 );
    EXPECT_DOUBLE_EQ( v12( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v12( 2 ), 4.0 );

    EXPECT_DOUBLE_EQ( v34( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v34( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v34( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanAddWrongSize)
{
    mc::VectorN v1( 3 );
    mc::VectorN v2( 4 );

    mc::VectorN v12 = v1 + v2;

    EXPECT_TRUE( std::isnan( v12( 0 ) ) );
    EXPECT_TRUE( std::isnan( v12( 1 ) ) );
    EXPECT_TRUE( std::isnan( v12( 2 ) ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanNegate)
{
    double x[] = { 1.0, 2.0, 3.0 };

    mc::VectorN v1( 3 );
    v1.setArray( x );

    mc::VectorN v2 = -v1;

    EXPECT_DOUBLE_EQ( v2( 0 ), -1.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), -2.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), -3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanSubstract)
{
    double x1[] = { 3.0, 3.0, 3.0 };
    double x2[] = { 1.0, 2.0, 3.0 };

    mc::VectorN v1( 3 );
    mc::VectorN v2( 3 );

    v1.setArray( x1 );
    v2.setArray( x2 );

    mc::VectorN v = v1 - v2;

    EXPECT_DOUBLE_EQ( v( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanSubstractWrongSize)
{
    mc::VectorN v1( 3 );
    mc::VectorN v2( 4 );

    mc::VectorN v12 = v1 - v2;

    EXPECT_TRUE( std::isnan( v12( 0 ) ) );
    EXPECT_TRUE( std::isnan( v12( 1 ) ) );
    EXPECT_TRUE( std::isnan( v12( 2 ) ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanMultiplyByScalar)
{
    double x[] = { 1.0, 2.0, 3.0 };

    mc::VectorN v1( 3 );

    v1.setArray( x );

    mc::VectorN v2 = v1 * 2.0;

    EXPECT_DOUBLE_EQ( v2( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CandivideByScalar)
{
    double x[] = { 2.0, 4.0, 6.0 };

    mc::VectorN v1( 3 );

    v1.setArray( x );

    mc::VectorN v2 = v1 / 2.0;

    EXPECT_DOUBLE_EQ( v2( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanUnaryAdd)
{
    double x0[] = { 1.0, 2.0, 3.0 };
    double x1[] = { 3.0, 2.0, 1.0 };

    mc::VectorN v0( 3 );
    mc::VectorN v1( 3 );

    v0.setArray( x0 );
    v1.setArray( x1 );

    v0 += v1;

    EXPECT_DOUBLE_EQ( v0( 0 ), 4.0 );
    EXPECT_DOUBLE_EQ( v0( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v0( 2 ), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanUnarySubstract)
{
    double x0[] = { 3.0, 3.0, 3.0 };
    double x1[] = { 1.0, 2.0, 3.0 };

    mc::VectorN v0( 3 );
    mc::VectorN v1( 3 );

    v0.setArray( x0 );
    v1.setArray( x1 );

    v0 -= v1;

    EXPECT_DOUBLE_EQ( v0( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v0( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v0( 2 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanUnaryMultiplyByScalar)
{
    double x0[] = { 1.0, 2.0, 3.0 };

    mc::VectorN v0( 3 );

    v0.setArray( x0 );

    v0 *= 2.0;

    EXPECT_DOUBLE_EQ( v0( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v0( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v0( 2 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVectorN, CanUnaryDivideByScalar)
{
    double x0[] = { 2.0, 4.0, 6.0 };

    mc::VectorN v0( 3 );

    v0.setArray( x0 );

    v0 /= 2.0;

    EXPECT_DOUBLE_EQ( v0( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v0( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v0( 2 ), 3.0 );
}
