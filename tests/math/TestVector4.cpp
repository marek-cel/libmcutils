#include <gtest/gtest.h>

#include <mcutils/math/Vector4.h>

////////////////////////////////////////////////////////////////////////////////

class TestVector4 : public ::testing::Test
{
protected:
    TestVector4() {}
    virtual ~TestVector4() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanConstruct)
{
    mc::Vector4 *v = nullptr;
    EXPECT_NO_THROW( v = new mc::Vector4() );
    delete v;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanDestruct)
{
    mc::Vector4 *v = new mc::Vector4();
    EXPECT_NO_THROW( delete v );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanInstantiate)
{
    mc::Vector4 v1;

    EXPECT_DOUBLE_EQ( v1( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 0.0 );
    EXPECT_DOUBLE_EQ( v1( 3 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanInstantiateAndCopy)
{
    const double d1[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector4 v1( d1 );

    mc::Vector4 v2( v1 );

    EXPECT_DOUBLE_EQ( v2( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v2( 3 ), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanInstantiateAndSetData)
{
    const double d1[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector4 v1( d1 );

    EXPECT_DOUBLE_EQ( v1( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v1( 3 ), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanInstantiateAndSetDataFromString)
{
    char str[] = { " 1.0 2.0 3.0 4.0 " };
    mc::Vector4 v1( str );

    EXPECT_DOUBLE_EQ( v1( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v1( 3 ), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanGetNormalized)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector4.m

    const double d1[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector4 v1( d1 );
    mc::Vector4 v1_n = v1.getNormalized();

    EXPECT_NEAR( v1_n( 0 ), 0.182574, 1.0e-5 );
    EXPECT_NEAR( v1_n( 1 ), 0.365148, 1.0e-5 );
    EXPECT_NEAR( v1_n( 2 ), 0.547723, 1.0e-5 );
    EXPECT_NEAR( v1_n( 3 ), 0.730297, 1.0e-5 );

    EXPECT_DOUBLE_EQ( v1_n.getLength(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanAssign)
{
    mc::Vector4 v;

    double x1[] = { 1.0, 0.0, 0.0, 0.0 };
    double x2[] = { 0.0, 1.0, 0.0, 0.0 };
    double x3[] = { 0.0, 0.0, 1.0, 0.0 };
    double x4[] = { 0.0, 0.0, 0.0, 1.0 };
    double x5[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector4 v1( x1 );
    mc::Vector4 v2( x2 );
    mc::Vector4 v3( x3 );
    mc::Vector4 v4( x4 );
    mc::Vector4 v5( x5 );

    v = v1;
    EXPECT_DOUBLE_EQ( v( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 3 ), 0.0 );

    v = v2;
    EXPECT_DOUBLE_EQ( v( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 3 ), 0.0 );

    v = v3;
    EXPECT_DOUBLE_EQ( v( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 1.0 );
    EXPECT_DOUBLE_EQ( v( 3 ), 0.0 );

    v = v4;
    EXPECT_DOUBLE_EQ( v( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 0.0 );
    EXPECT_DOUBLE_EQ( v( 3 ), 1.0 );

    v = v5;
    EXPECT_DOUBLE_EQ( v( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v( 3 ), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanAdd)
{
    double x1[] = { 0.0, 0.0, 0.0, 0.0 };
    double x2[] = { 1.0, 2.0, 3.0, 4.0 };
    double x3[] = { 1.0, 2.0, 3.0, 4.0 };
    double x4[] = { 4.0, 3.0, 2.0, 1.0 };

    mc::Vector4 v1( x1 );
    mc::Vector4 v2( x2 );
    mc::Vector4 v3( x3 );
    mc::Vector4 v4( x4 );

    mc::Vector4 v12 = v1 + v2;
    mc::Vector4 v34 = v3 + v4;

    EXPECT_DOUBLE_EQ( v12( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v12( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v12( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v12( 3 ), 4.0 );

    EXPECT_DOUBLE_EQ( v34( 0 ), 5.0 );
    EXPECT_DOUBLE_EQ( v34( 1 ), 5.0 );
    EXPECT_DOUBLE_EQ( v34( 2 ), 5.0 );
    EXPECT_DOUBLE_EQ( v34( 3 ), 5.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanNegate)
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0 };
    double x2[] = { 4.0, 3.0, 2.0, 1.0 };

    mc::Vector4 v1( x1 );
    mc::Vector4 v2( x2 );

    mc::Vector4 v1n = -v1;
    mc::Vector4 v2n = -v2;

    EXPECT_DOUBLE_EQ( v1n( 0 ), -1.0 );
    EXPECT_DOUBLE_EQ( v1n( 1 ), -2.0 );
    EXPECT_DOUBLE_EQ( v1n( 2 ), -3.0 );
    EXPECT_DOUBLE_EQ( v1n( 3 ), -4.0 );

    EXPECT_DOUBLE_EQ( v2n( 0 ), -4.0 );
    EXPECT_DOUBLE_EQ( v2n( 1 ), -3.0 );
    EXPECT_DOUBLE_EQ( v2n( 2 ), -2.0 );
    EXPECT_DOUBLE_EQ( v2n( 3 ), -1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanSubstract)
{
    double x1[] = { 4.0, 4.0, 4.0, 4.0 };
    double x2[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector4 v1( x1 );
    mc::Vector4 v2( x2 );

    mc::Vector4 v = v1 - v2;

    EXPECT_DOUBLE_EQ( v( 0 ), 3.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 1.0 );
    EXPECT_DOUBLE_EQ( v( 3 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanMultiplyByScalar)
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector4 v1( x1 );

    mc::Vector4 v = v1 * 2.0;

    EXPECT_DOUBLE_EQ( v( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 6.0 );
    EXPECT_DOUBLE_EQ( v( 3 ), 8.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanDivideByScalar)
{
    double x1[] = { 2.0, 4.0, 6.0, 8.0 };

    mc::Vector4 v1( x1 );

    mc::Vector4 v = v1 / 2.0;

    EXPECT_DOUBLE_EQ( v( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v( 3 ), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanUnaryAdd)
{
    double x1[] = { 0.0, 0.0, 0.0, 0.0 };
    double x2[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector4 v1( x1 );
    mc::Vector4 v2( x2 );

    v1 += v2;

    EXPECT_DOUBLE_EQ( v1( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v1( 3 ), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanUnarySubstract)
{
    double x1[] = { 4.0, 4.0, 4.0, 4.0 };
    double x2[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector4 v1( x1 );
    mc::Vector4 v2( x2 );

    v1 -= v2;

    EXPECT_DOUBLE_EQ( v1( 0 ), 3.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 3 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanUnaryMultiplyByScalar)
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector4 v1( x1 );

    v1 *= 2.0;

    EXPECT_DOUBLE_EQ( v1( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 6.0 );
    EXPECT_DOUBLE_EQ( v1( 3 ), 8.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector4, CanUnaryDivideByScalar)
{
    double x1[] = { 2.0, 4.0, 6.0, 8.0 };

    mc::Vector4 v1( x1 );

    v1 /= 2.0;

    EXPECT_DOUBLE_EQ( v1( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v1( 3 ), 4.0 );
}
