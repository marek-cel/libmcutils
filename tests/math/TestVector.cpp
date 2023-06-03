#include <gtest/gtest.h>

#include <mcutils/math/Vector.h>

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
    mc::Vector<3> *v3 = new mc::Vector<3>();
    EXPECT_NO_THROW( delete v3 );

    mc::Vector<4> *v4 = new mc::Vector<4>();
    EXPECT_NO_THROW( delete v4 );

    mc::Vector<6> *v6 = new mc::Vector<6>();
    EXPECT_NO_THROW( delete v6 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanInstantiate)
{
    mc::Vector<3> v3;

    EXPECT_DOUBLE_EQ( v3( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v3( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v3( 2 ), 0.0 );

    mc::Vector<4> v4;

    EXPECT_DOUBLE_EQ( v4( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v4( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v4( 2 ), 0.0 );
    EXPECT_DOUBLE_EQ( v4( 3 ), 0.0 );

    mc::Vector<6> v6;

    EXPECT_DOUBLE_EQ( v6( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v6( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v6( 2 ), 0.0 );
    EXPECT_DOUBLE_EQ( v6( 3 ), 0.0 );
    EXPECT_DOUBLE_EQ( v6( 4 ), 0.0 );
    EXPECT_DOUBLE_EQ( v6( 5 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanInstantiateAndCopy)
{
    const double d3[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v3;
    v3.setItems( d3 );

    mc::Vector<3> v32( v3 );

    EXPECT_DOUBLE_EQ( v32( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v32( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v32( 2 ), 3.0 );

    const double d4[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v4;
    v4.setItems( d4 );

    mc::Vector<4> v42( v4 );

    EXPECT_DOUBLE_EQ( v42( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v42( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v42( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v42( 3 ), 4.0 );

    const double d6[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v6;
    v6.setItems( d6 );

    mc::Vector<6> v62( v6 );

    EXPECT_DOUBLE_EQ( v62( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v62( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v62( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v62( 3 ), 4.0 );
    EXPECT_DOUBLE_EQ( v62( 4 ), 5.0 );
    EXPECT_DOUBLE_EQ( v62( 5 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanInstantiateAndSetData)
{
    const double d3[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v3;
    v3.setItems( d3 );

    EXPECT_DOUBLE_EQ( v3( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v3( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v3( 2 ), 3.0 );

    const double d4[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v4;
    v4.setItems( d4 );

    EXPECT_DOUBLE_EQ( v4( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v4( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v4( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v4( 3 ), 4.0 );

    const double d6[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v6;
    v6.setItems( d6 );

    EXPECT_DOUBLE_EQ( v6( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v6( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v6( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v6( 3 ), 4.0 );
    EXPECT_DOUBLE_EQ( v6( 4 ), 5.0 );
    EXPECT_DOUBLE_EQ( v6( 5 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanInstantiateAndSetDataFromString)
{
    char str3[] = { " 1.0  2.0  3.0 " };
    mc::Vector<3> v3;
    v3.setFromString( str3 );

    EXPECT_DOUBLE_EQ( v3( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v3( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v3( 2 ), 3.0 );

    char str4[] = { " 1.0 2.0 3.0 4.0 " };
    mc::Vector<4> v4;
    v4.setFromString( str4 );

    EXPECT_DOUBLE_EQ( v4( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v4( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v4( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v4( 3 ), 4.0 );

    char str6[] = { "1.0  2.0  3.0  4.0  5.0  6.0" };
    mc::Vector<6> v6;
    v6.setFromString( str6 );

    EXPECT_DOUBLE_EQ( v6( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v6( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v6( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v6( 3 ), 4.0 );
    EXPECT_DOUBLE_EQ( v6( 4 ), 5.0 );
    EXPECT_DOUBLE_EQ( v6( 5 ), 6.0 );

    char str62[] = { "lorem ipsum" };
    mc::Vector<6> v62;
    v62.setFromString( str62 );
    EXPECT_FALSE( v62.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanValidate)
{
    const double d3[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v3;
    v3.setItems( d3 );
    EXPECT_TRUE( v3.isValid() );

    const double d4[] { std::numeric_limits<double>::quiet_NaN(), 2.0, 3.0, 4.0 };
    mc::Vector<4> v4;
    v4.setItems( d4 );
    EXPECT_FALSE( v4.isValid() );

    const double d6[] { 1.0, std::numeric_limits<double>::quiet_NaN(), 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v6;
    v6.setItems( d6 );
    EXPECT_FALSE( v6.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanGetLength2)
{
    mc::Vector<3> v3;

    v3( 0 ) = 1.0;
    v3( 1 ) = 2.0;
    v3( 2 ) = 3.0;

    // 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
    EXPECT_DOUBLE_EQ( v3.getLength2(), 14.0 );

    mc::Vector<4> v4;
    EXPECT_DOUBLE_EQ( v4.getLength2(), 0.0 );

    mc::Vector<6> v6;
    EXPECT_DOUBLE_EQ( v6.getLength2(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanGetLength)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m

    mc::Vector<3> v3;

    v3( 0 ) = 1.0;
    v3( 1 ) = 2.0;
    v3( 2 ) = 3.0;

    // sqrt( 1^2 + 2^2 + 3^2 ) = sqrt( 1 + 4 + 9 ) = sqrt( 14 )
    EXPECT_NEAR( v3.getLength(), 3.741657, 1.0e-5 );

    mc::Vector<4> v4;
    EXPECT_DOUBLE_EQ( v4.getLength(), 0.0 );

    mc::Vector<6> v6;
    EXPECT_DOUBLE_EQ( v6.getLength(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanNormalize)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m

    const double d3[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v3;
    v3.setItems( d3 );

    v3.normalize();

    EXPECT_NEAR( v3(0), 0.267261, 1.0e-5 );
    EXPECT_NEAR( v3(1), 0.534522, 1.0e-5 );
    EXPECT_NEAR( v3(2), 0.801784, 1.0e-5 );

    EXPECT_DOUBLE_EQ( v3.getLength(), 1.0 );

    const double d4[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v4;
    v4.setItems( d4 );

    v4.normalize();

    EXPECT_NEAR( v4( 0 ), 0.182574, 1.0e-5 );
    EXPECT_NEAR( v4( 1 ), 0.365148, 1.0e-5 );
    EXPECT_NEAR( v4( 2 ), 0.547723, 1.0e-5 );
    EXPECT_NEAR( v4( 3 ), 0.730297, 1.0e-5 );

    EXPECT_DOUBLE_EQ( v4.getLength(), 1.0 );

    double x6[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v6;
    v6.setItems( x6 );

    v6.normalize();

    EXPECT_NEAR( v6( 0 ), 0.104828, 1.0e-5 );
    EXPECT_NEAR( v6( 1 ), 0.209657, 1.0e-5 );
    EXPECT_NEAR( v6( 2 ), 0.314485, 1.0e-5 );
    EXPECT_NEAR( v6( 3 ), 0.419314, 1.0e-5 );
    EXPECT_NEAR( v6( 4 ), 0.524142, 1.0e-5 );
    EXPECT_NEAR( v6( 5 ), 0.628971, 1.0e-5 );

    EXPECT_DOUBLE_EQ( v6.getLength(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanGetArray)
{
    const double d31[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v3;
    v3.setItems( d31 );

    double d32[3];
    v3.getItems( d32 );

    EXPECT_DOUBLE_EQ( d32[ 0 ], d31[ 0 ] );
    EXPECT_DOUBLE_EQ( d32[ 1 ], d31[ 1 ] );
    EXPECT_DOUBLE_EQ( d32[ 2 ], d31[ 2 ] );

    const double d41[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v4;
    v4.setItems( d41 );

    double d42[4];
    v4.getItems( d42 );

    EXPECT_DOUBLE_EQ( d42[ 0 ], d41[ 0 ] );
    EXPECT_DOUBLE_EQ( d42[ 1 ], d41[ 1 ] );
    EXPECT_DOUBLE_EQ( d42[ 2 ], d41[ 2 ] );
    EXPECT_DOUBLE_EQ( d42[ 3 ], d41[ 3 ] );

    const double d61[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v6;
    v6.setItems( d61 );

    double d62[6];
    v6.getItems( d62 );

    EXPECT_DOUBLE_EQ( d62[ 0 ], d61[ 0 ] );
    EXPECT_DOUBLE_EQ( d62[ 1 ], d61[ 1 ] );
    EXPECT_DOUBLE_EQ( d62[ 2 ], d61[ 2 ] );
    EXPECT_DOUBLE_EQ( d62[ 3 ], d61[ 3 ] );
    EXPECT_DOUBLE_EQ( d62[ 4 ], d61[ 4 ] );
    EXPECT_DOUBLE_EQ( d62[ 5 ], d61[ 5 ] );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanGetItem)
{
    const double d31[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v3;
    v3.setItems( d31 );

    EXPECT_DOUBLE_EQ( v3.getItem( 0 ), d31[ 0 ] );
    EXPECT_DOUBLE_EQ( v3.getItem( 1 ), d31[ 1 ] );
    EXPECT_DOUBLE_EQ( v3.getItem( 2 ), d31[ 2 ] );

    EXPECT_TRUE( v3.getItem( 666 ) != v3.getItem( 666 ) );

    const double d41[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v4;
    v4.setItems( d41 );

    EXPECT_DOUBLE_EQ( v4.getItem( 0 ), d41[ 0 ] );
    EXPECT_DOUBLE_EQ( v4.getItem( 1 ), d41[ 1 ] );
    EXPECT_DOUBLE_EQ( v4.getItem( 2 ), d41[ 2 ] );
    EXPECT_DOUBLE_EQ( v4.getItem( 3 ), d41[ 3 ] );

    EXPECT_TRUE( v4.getItem( 666 ) != v3.getItem( 666 ) );

    const double d61[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v6;
    v6.setItems( d61 );

    EXPECT_DOUBLE_EQ( v6.getItem( 0 ), d61[ 0 ] );
    EXPECT_DOUBLE_EQ( v6.getItem( 1 ), d61[ 1 ] );
    EXPECT_DOUBLE_EQ( v6.getItem( 2 ), d61[ 2 ] );
    EXPECT_DOUBLE_EQ( v6.getItem( 3 ), d61[ 3 ] );
    EXPECT_DOUBLE_EQ( v6.getItem( 4 ), d61[ 4 ] );
    EXPECT_DOUBLE_EQ( v6.getItem( 5 ), d61[ 5 ] );

    EXPECT_TRUE( v6.getItem( 666 ) != v3.getItem( 666 ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanSetArray)
{
    const double d31[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v3;
    v3.setItems( d31 );

    double d32[3];
    v3.getItems( d32 );

    EXPECT_DOUBLE_EQ( d32[ 0 ], d31[ 0 ] );
    EXPECT_DOUBLE_EQ( d32[ 1 ], d31[ 1 ] );
    EXPECT_DOUBLE_EQ( d32[ 2 ], d31[ 2 ] );

    const double d41[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v4;
    v4.setItems( d41 );

    double d42[4];
    v4.getItems( d42 );

    EXPECT_DOUBLE_EQ( d42[ 0 ], d41[ 0 ] );
    EXPECT_DOUBLE_EQ( d42[ 1 ], d41[ 1 ] );
    EXPECT_DOUBLE_EQ( d42[ 2 ], d41[ 2 ] );
    EXPECT_DOUBLE_EQ( d42[ 3 ], d41[ 3 ] );

    const double d61[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v6;
    v6.setItems( d61 );

    double d62[6];
    v6.getItems( d62 );

    EXPECT_DOUBLE_EQ( d62[ 0 ], d61[ 0 ] );
    EXPECT_DOUBLE_EQ( d62[ 1 ], d61[ 1 ] );
    EXPECT_DOUBLE_EQ( d62[ 2 ], d61[ 2 ] );
    EXPECT_DOUBLE_EQ( d62[ 3 ], d61[ 3 ] );
    EXPECT_DOUBLE_EQ( d62[ 4 ], d61[ 4 ] );
    EXPECT_DOUBLE_EQ( d62[ 5 ], d61[ 5 ] );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanSetItem)
{
    mc::Vector<3> v3;

    v3.setItem( 0, 1.0 );
    v3.setItem( 1, 2.0 );
    v3.setItem( 2, 3.0 );

    EXPECT_DOUBLE_EQ( v3( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v3( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v3( 2 ), 3.0 );

    mc::Vector<4> v4;

    v4.setItem( 0, 1.0 );
    v4.setItem( 1, 2.0 );
    v4.setItem( 2, 3.0 );
    v4.setItem( 3, 4.0 );

    EXPECT_DOUBLE_EQ( v4( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v4( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v4( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v4( 3 ), 4.0 );

    mc::Vector<6> v6;

    v6.setItem( 0, 1.0 );
    v6.setItem( 1, 2.0 );
    v6.setItem( 2, 3.0 );
    v6.setItem( 3, 4.0 );
    v6.setItem( 4, 5.0 );
    v6.setItem( 5, 6.0 );

    EXPECT_DOUBLE_EQ( v6( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v6( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v6( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v6( 3 ), 4.0 );
    EXPECT_DOUBLE_EQ( v6( 4 ), 5.0 );
    EXPECT_DOUBLE_EQ( v6( 5 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanSwapRows)
{
    const double d3[] { 1.0, 2.0, 3.0 };

    mc::Vector<3> v31;
    v31.setItems( d3 );
    v31.swapRows( 0, 1 );
    EXPECT_DOUBLE_EQ( v31( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v31( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v31( 2 ), 3.0 );

    const double d4[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v4;
    v4.setItems( d4 );
    v4.swapRows( 0, 1 );
    EXPECT_DOUBLE_EQ( v4( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v4( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v4( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v4( 3 ), 4.0 );

    const double d6[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v6;
    v6.setItems( d6 );
    v6.swapRows( 0, 1 );
    EXPECT_DOUBLE_EQ( v6( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v6( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v6( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v6( 3 ), 4.0 );
    EXPECT_DOUBLE_EQ( v6( 4 ), 5.0 );
    EXPECT_DOUBLE_EQ( v6( 5 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanConvertToString)
{
    const double d3[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v3;
    v3.setItems( d3 );
    EXPECT_STREQ( v3.toString().c_str(), "1,2,3" );

    const double d4[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v4;
    v4.setItems( d4 );
    EXPECT_STREQ( v4.toString().c_str(), "1,2,3,4" );

    const double d6[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v6;
    v6.setItems( d6 );
    EXPECT_STREQ( v6.toString().c_str(), "1,2,3,4,5,6" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanZeroize)
{
    const double d3[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v3;
    v3.setItems( d3 );
    v3.zeroize();
    EXPECT_DOUBLE_EQ( v3( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v3( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v3( 2 ), 0.0 );

    const double d4[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v4;
    v4.setItems( d4 );
    v4.zeroize();
    EXPECT_DOUBLE_EQ( v4( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v4( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v4( 2 ), 0.0 );
    EXPECT_DOUBLE_EQ( v4( 3 ), 0.0 );

    const double d6[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v6;
    v6.setItems( d6 );
    v6.zeroize();
    EXPECT_DOUBLE_EQ( v6( 0 ), 0.0 );
    EXPECT_DOUBLE_EQ( v6( 1 ), 0.0 );
    EXPECT_DOUBLE_EQ( v6( 2 ), 0.0 );
    EXPECT_DOUBLE_EQ( v6( 3 ), 0.0 );
    EXPECT_DOUBLE_EQ( v6( 4 ), 0.0 );
    EXPECT_DOUBLE_EQ( v6( 5 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanAccessItemViaOperator)
{
    const double d3[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v3;
    v3.setItems( d3 );

    EXPECT_DOUBLE_EQ( v3( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v3( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v3( 2 ), 3.0 );

    const double d4[] { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v4;
    v4.setItems( d4 );
    EXPECT_DOUBLE_EQ( v4( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v4( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v4( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v4( 3 ), 4.0 );

    const double d6[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v6;
    v6.setItems( d6 );
    EXPECT_DOUBLE_EQ( v6( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v6( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v6( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v6( 3 ), 4.0 );
    EXPECT_DOUBLE_EQ( v6( 4 ), 5.0 );
    EXPECT_DOUBLE_EQ( v6( 5 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanAssign)
{
    mc::Vector<3> v3;
    double x31[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v31;
    v31.setItems( x31 );
    v3 = v31;
    EXPECT_DOUBLE_EQ( v3( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v3( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v3( 2 ), 3.0 );

    mc::Vector<4> v4;
    double x41[] = { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v41;
    v41.setItems( x41 );
    v4 = v41;
    EXPECT_DOUBLE_EQ( v4( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v4( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v4( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v4( 3 ), 4.0 );

    mc::Vector<6> v6;

    double x61[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::Vector<6> v61;
    v61.setItems( x61 );

    v6 = v61;
    EXPECT_DOUBLE_EQ( v6( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v6( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v6( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v6( 3 ), 4.0 );
    EXPECT_DOUBLE_EQ( v6( 4 ), 5.0 );
    EXPECT_DOUBLE_EQ( v6( 5 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanAdd)
{
    double x1[] { 1.0, 2.0, 3.0 };
    double x2[] { 3.0, 2.0, 1.0 };
    double x3[] { 0.0, 0.0, 0.0 };
    double x4[] { 1.0, 2.0, 3.0 };

    mc::Vector<3> v1;
    mc::Vector<3> v2;
    mc::Vector<3> v3;
    mc::Vector<3> v4;

    v1.setItems( x1 );
    v2.setItems( x2 );
    v3.setItems( x3 );
    v4.setItems( x4 );

    mc::Vector<3> v12 = v1 + v2;
    mc::Vector<3> v34 = v3 + v4;

    EXPECT_DOUBLE_EQ( v12( 0 ), 4.0 );
    EXPECT_DOUBLE_EQ( v12( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v12( 2 ), 4.0 );

    EXPECT_DOUBLE_EQ( v34( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v34( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v34( 2 ), 3.0 );

    double x41[] = { 0.0, 0.0, 0.0, 0.0 };
    double x42[] = { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v41;
    mc::Vector<4> v42;
    v41.setItems( x41 );
    v42.setItems( x42 );
    mc::Vector<4> v412 = v41 + v42;
    EXPECT_DOUBLE_EQ( v412( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v412( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v412( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v412( 3 ), 4.0 );

    double x61[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double x62[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v61;
    mc::Vector<6> v62;
    v61.setItems( x61 );
    v62.setItems( x62 );
    mc::Vector<6> v612 = v61 + v62;
    EXPECT_DOUBLE_EQ( v612( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v612( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v612( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v612( 3 ), 4.0 );
    EXPECT_DOUBLE_EQ( v612( 4 ), 5.0 );
    EXPECT_DOUBLE_EQ( v612( 5 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanNegate)
{
    double x[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1;
    v1.setItems( x );

    mc::Vector<3> v2 = -v1;

    EXPECT_DOUBLE_EQ( v2( 0 ), -1.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), -2.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), -3.0 );

    double x4[] = { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v4;
    v4.setItems( x4 );
    mc::Vector<4> v4n = -v4;

    EXPECT_DOUBLE_EQ( v4n( 0 ), -1.0 );
    EXPECT_DOUBLE_EQ( v4n( 1 ), -2.0 );
    EXPECT_DOUBLE_EQ( v4n( 2 ), -3.0 );
    EXPECT_DOUBLE_EQ( v4n( 3 ), -4.0 );

    double x6[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v6;
    v6.setItems( x6 );
    mc::Vector<6> v6n = -v6;

    EXPECT_DOUBLE_EQ( v6n( 0 ), -1.0 );
    EXPECT_DOUBLE_EQ( v6n( 1 ), -2.0 );
    EXPECT_DOUBLE_EQ( v6n( 2 ), -3.0 );
    EXPECT_DOUBLE_EQ( v6n( 3 ), -4.0 );
    EXPECT_DOUBLE_EQ( v6n( 4 ), -5.0 );
    EXPECT_DOUBLE_EQ( v6n( 5 ), -6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanSubstract)
{
    double x1[] = { 3.0, 3.0, 3.0 };
    double x2[] = { 1.0, 2.0, 3.0 };

    mc::Vector<3> v1;
    mc::Vector<3> v2;

    v1.setItems( x1 );
    v2.setItems( x2 );

    mc::Vector<3> v = v1 - v2;

    EXPECT_DOUBLE_EQ( v( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v( 2 ), 0.0 );

    double x41[] = { 4.0, 4.0, 4.0, 4.0 };
    double x42[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector<4> v41;
    mc::Vector<4> v42;

    v41.setItems( x41 );
    v42.setItems( x42 );

    mc::Vector<4> v4 = v41 - v42;

    EXPECT_DOUBLE_EQ( v4( 0 ), 3.0 );
    EXPECT_DOUBLE_EQ( v4( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v4( 2 ), 1.0 );
    EXPECT_DOUBLE_EQ( v4( 3 ), 0.0 );

    double x61[] = { 6.0, 6.0, 6.0, 6.0, 6.0, 6.0 };
    double x62[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    mc::Vector<6> v61;
    mc::Vector<6> v62;

    v61.setItems( x61 );
    v62.setItems( x62 );

    mc::Vector<6> v6 = v61 - v62;

    EXPECT_DOUBLE_EQ( v6( 0 ), 5.0 );
    EXPECT_DOUBLE_EQ( v6( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v6( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v6( 3 ), 2.0 );
    EXPECT_DOUBLE_EQ( v6( 4 ), 1.0 );
    EXPECT_DOUBLE_EQ( v6( 5 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanMultiplyByScalar)
{
    double x[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v1;
    v1.setItems( x );
    mc::Vector<3> v2 = v1 * 2.0;
    EXPECT_DOUBLE_EQ( v2( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), 6.0 );

    double x41[] = { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v41;
    v41.setItems( x41 );
    mc::Vector<4> v4 = v41 * 2.0;
    EXPECT_DOUBLE_EQ( v4( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v4( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v4( 2 ), 6.0 );
    EXPECT_DOUBLE_EQ( v4( 3 ), 8.0 );

    double x61[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v61;
    v61.setItems( x61 );
    mc::Vector<6> v6 = v61 * 2.0;
    EXPECT_DOUBLE_EQ( v6( 0 ),  2.0 );
    EXPECT_DOUBLE_EQ( v6( 1 ),  4.0 );
    EXPECT_DOUBLE_EQ( v6( 2 ),  6.0 );
    EXPECT_DOUBLE_EQ( v6( 3 ),  8.0 );
    EXPECT_DOUBLE_EQ( v6( 4 ), 10.0 );
    EXPECT_DOUBLE_EQ( v6( 5 ), 12.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanCalculateDotProduct)
{
    double x31[] = { 1.0, 0.0, 0.0 };
    double x32[] = { 0.0, 1.0, 0.0 };
    double x33[] = { 0.0, 0.0, 1.0 };
    double x34[] = { 1.0, 2.0, 3.0 };

    mc::Vector<3> v31;
    mc::Vector<3> v32;
    mc::Vector<3> v33;
    mc::Vector<3> v34;

    v31.setItems( x31 );
    v32.setItems( x32 );
    v33.setItems( x33 );
    v34.setItems( x34 );

    double s41 = v34 * v31;
    double s42 = v34 * v32;
    double s43 = v34 * v33;
    double s44 = v34 * v34;

    EXPECT_DOUBLE_EQ( s41,  1.0 );
    EXPECT_DOUBLE_EQ( s42,  2.0 );
    EXPECT_DOUBLE_EQ( s43,  3.0 );
    EXPECT_DOUBLE_EQ( s44, 14.0 );

    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector.m

    double x1[] = { 1.0, 0.0, 0.0, 0.0 };
    double x2[] = { 0.0, 1.0, 0.0, 0.0 };
    double x3[] = { 0.0, 0.0, 1.0, 0.0 };
    double x4[] = { 0.0, 0.0, 0.0, 1.0 };
    double x5[] = { 1.0, 2.0, 3.0, 4.0 };

    mc::Vector<4> v1;
    mc::Vector<4> v2;
    mc::Vector<4> v3;
    mc::Vector<4> v4;
    mc::Vector<4> v5;

    v1.setItems( x1 );
    v2.setItems( x2 );
    v3.setItems( x3 );
    v4.setItems( x4 );
    v5.setItems( x5 );

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
    mc::Vector<3> v1;
    v1.setItems( x );
    mc::Vector<3> v2 = v1 / 2.0;
    EXPECT_DOUBLE_EQ( v2( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), 3.0 );

    double x41[] = { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v41;
    v41.setItems( x41 );
    mc::Vector<4> v4 = v41 / 2.0;
    EXPECT_DOUBLE_EQ( v4( 0 ), 1.0 / 2.0 );
    EXPECT_DOUBLE_EQ( v4( 1 ), 2.0 / 2.0 );
    EXPECT_DOUBLE_EQ( v4( 2 ), 3.0 / 2.0 );
    EXPECT_DOUBLE_EQ( v4( 3 ), 4.0 / 2.0 );

    double x61[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v61;
    v61.setItems( x61 );
    mc::Vector<6> v6 = v61 / 2.0;
    EXPECT_DOUBLE_EQ( v6( 0 ), 1.0 / 2.0 );
    EXPECT_DOUBLE_EQ( v6( 1 ), 2.0 / 2.0 );
    EXPECT_DOUBLE_EQ( v6( 2 ), 3.0 / 2.0 );
    EXPECT_DOUBLE_EQ( v6( 3 ), 4.0 / 2.0 );
    EXPECT_DOUBLE_EQ( v6( 4 ), 5.0 / 2.0 );
    EXPECT_DOUBLE_EQ( v6( 5 ), 6.0 / 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanUnaryAdd)
{
    double x0[] { 1.0, 2.0, 3.0 };
    double x1[] { 2.0, 3.0, 4.0 };
    mc::Vector<3> v0;
    mc::Vector<3> v1;
    v0.setItems( x0 );
    v1.setItems( x1 );
    v0 += v1;
    EXPECT_DOUBLE_EQ( v0( 0 ), 3.0 );
    EXPECT_DOUBLE_EQ( v0( 1 ), 5.0 );
    EXPECT_DOUBLE_EQ( v0( 2 ), 7.0 );

    double x41[] = { 0.0, 0.0, 0.0, 0.0 };
    double x42[] = { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v41;
    mc::Vector<4> v42;
    v41.setItems( x41 );
    v42.setItems( x42 );
    v41 += v42;
    EXPECT_DOUBLE_EQ( v41( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v41( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v41( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v41( 3 ), 4.0 );

    double x61[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double x62[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v61;
    mc::Vector<6> v62;
    v61.setItems( x61 );
    v62.setItems( x62 );
    v61 += v62;
    EXPECT_DOUBLE_EQ( v61( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v61( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v61( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v61( 3 ), 4.0 );
    EXPECT_DOUBLE_EQ( v61( 4 ), 5.0 );
    EXPECT_DOUBLE_EQ( v61( 5 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanUnarySubstract)
{
    double x0[] { 3.0, 3.0, 3.0 };
    double x1[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v0;
    mc::Vector<3> v1;
    v0.setItems( x0 );
    v1.setItems( x1 );
    v0 -= v1;
    EXPECT_DOUBLE_EQ( v0( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v0( 1 ), 1.0 );
    EXPECT_DOUBLE_EQ( v0( 2 ), 0.0 );

    double x41[] = { 4.0, 4.0, 4.0, 4.0 };
    double x42[] = { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v41;
    mc::Vector<4> v42;
    v41.setItems( x41 );
    v42.setItems( x42 );
    v41 -= v42;
    EXPECT_DOUBLE_EQ( v41( 0 ), 3.0 );
    EXPECT_DOUBLE_EQ( v41( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v41( 2 ), 1.0 );
    EXPECT_DOUBLE_EQ( v41( 3 ), 0.0 );

    double x61[] = { 6.0, 6.0, 6.0, 6.0, 6.0, 6.0 };
    double x62[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v61;
    mc::Vector<6> v62;
    v61.setItems( x61 );
    v62.setItems( x62 );
    v61 -= v62;
    EXPECT_DOUBLE_EQ( v61( 0 ), 5.0 );
    EXPECT_DOUBLE_EQ( v61( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v61( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v61( 3 ), 2.0 );
    EXPECT_DOUBLE_EQ( v61( 4 ), 1.0 );
    EXPECT_DOUBLE_EQ( v61( 5 ), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanUnaryMultiplyByScalar)
{
    double x0[] { 1.0, 2.0, 3.0 };
    mc::Vector<3> v0;
    v0.setItems( x0 );
    v0 *= 2.0;
    EXPECT_DOUBLE_EQ( v0( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v0( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v0( 2 ), 6.0 );

    double x41[] = { 1.0, 2.0, 3.0, 4.0 };
    mc::Vector<4> v41;
    v41.setItems( x41 );
    v41 *= 2.0;
    EXPECT_DOUBLE_EQ( v41( 0 ), 2.0 );
    EXPECT_DOUBLE_EQ( v41( 1 ), 4.0 );
    EXPECT_DOUBLE_EQ( v41( 2 ), 6.0 );
    EXPECT_DOUBLE_EQ( v41( 3 ), 8.0 );

    double x61[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    mc::Vector<6> v61;
    v61.setItems( x61 );
    v61 *= 2.0;
    EXPECT_DOUBLE_EQ( v61( 0 ),  2.0 );
    EXPECT_DOUBLE_EQ( v61( 1 ),  4.0 );
    EXPECT_DOUBLE_EQ( v61( 2 ),  6.0 );
    EXPECT_DOUBLE_EQ( v61( 3 ),  8.0 );
    EXPECT_DOUBLE_EQ( v61( 4 ), 10.0 );
    EXPECT_DOUBLE_EQ( v61( 5 ), 12.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanUnaryDivideByScalar)
{
    double x0[] { 2.0, 4.0, 6.0 };
    mc::Vector<3> v0;
    v0.setItems( x0 );
    v0 /= 2.0;
    EXPECT_DOUBLE_EQ( v0( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v0( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v0( 2 ), 3.0 );

    double x41[] = { 2.0, 4.0, 6.0, 8.0 };
    mc::Vector<4> v41;
    v41.setItems( x41 );
    v41 /= 2.0;
    EXPECT_DOUBLE_EQ( v41( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v41( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v41( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v41( 3 ), 4.0 );

    double x61[] = { 2.0, 4.0, 6.0, 8.0, 10.0, 12.0 };
    mc::Vector<6> v61;
    v61.setItems( x61 );
    v61 /= 2.0;
    EXPECT_DOUBLE_EQ( v61( 0 ), 1.0 );
    EXPECT_DOUBLE_EQ( v61( 1 ), 2.0 );
    EXPECT_DOUBLE_EQ( v61( 2 ), 3.0 );
    EXPECT_DOUBLE_EQ( v61( 3 ), 4.0 );
    EXPECT_DOUBLE_EQ( v61( 4 ), 5.0 );
    EXPECT_DOUBLE_EQ( v61( 5 ), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector, CanComparer)
{
    double x30[] = { 2.0, 4.0, 6.0 };
    double x31[] = { 1.0, 2.0, 3.0 };

    mc::Vector<3> v30;
    mc::Vector<3> v31;
    mc::Vector<3> v32;

    v30.setItems( x30 );
    v31.setItems( x31 );
    v32.setItems( x30 );

    EXPECT_FALSE( v30 == v31 );
    EXPECT_FALSE( v32 == v31 );
    EXPECT_FALSE( v32 != v30 );

    EXPECT_TRUE( v30 != v31 );
    EXPECT_TRUE( v32 != v31 );
    EXPECT_TRUE( v32 == v30 );

    double x40[] = { 2.0, 4.0, 6.0, 8.0 };
    double x41[] = { 3.0, 5.0, 7.0, 9.0 };

    mc::Vector<4> v40;
    mc::Vector<4> v41;
    mc::Vector<4> v42;

    v40.setItems( x40 );
    v41.setItems( x41 );
    v42.setItems( x40 );

    EXPECT_FALSE( v40 == v41 );
    EXPECT_FALSE( v42 == v41 );
    EXPECT_FALSE( v42 != v40 );

    EXPECT_TRUE( v40 != v41 );
    EXPECT_TRUE( v42 != v41 );
    EXPECT_TRUE( v42 == v40 );

    double x60[] = { 2.0, 4.0, 6.0, 8.0, 10.0, 12.0 };
    double x61[] = { 1.0, 3.0, 5.0, 7.0,  9.0, 11.0 };

    mc::Vector<4> v60;
    mc::Vector<4> v61;
    mc::Vector<4> v62;

    v60.setItems( x60 );
    v61.setItems( x61 );
    v62.setItems( x60 );

    EXPECT_FALSE( v60 == v61 );
    EXPECT_FALSE( v62 == v61 );
    EXPECT_FALSE( v62 != v60 );

    EXPECT_TRUE( v60 != v61 );
    EXPECT_TRUE( v62 != v61 );
    EXPECT_TRUE( v62 == v60 );
}
