#include <gtest/gtest.h>

#include <mcutils/math/Matrix3x3.h>

////////////////////////////////////////////////////////////////////////////////

class TestMatrix3x3 : public ::testing::Test
{
protected:
    TestMatrix3x3() {}
    virtual ~TestMatrix3x3() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanCreateIdentityMatrix)
{
    mc::Matrix3x3 m = mc::Matrix3x3::identityMatrix();

    EXPECT_DOUBLE_EQ( m(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m(0,1), 0.0 );
    EXPECT_DOUBLE_EQ( m(0,2), 0.0 );

    EXPECT_DOUBLE_EQ( m(1,0), 0.0 );
    EXPECT_DOUBLE_EQ( m(1,1), 1.0 );
    EXPECT_DOUBLE_EQ( m(1,2), 0.0 );

    EXPECT_DOUBLE_EQ( m(2,0), 0.0 );
    EXPECT_DOUBLE_EQ( m(2,1), 0.0 );
    EXPECT_DOUBLE_EQ( m(2,2), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanConstruct)
{
    mc::Matrix3x3 *m = nullptr;
    EXPECT_NO_THROW( m = new mc::Matrix3x3() );
    delete m;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanDestruct)
{
    mc::Matrix3x3 *m = new mc::Matrix3x3();
    EXPECT_NO_THROW( delete m );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanInstantiate)
{
    mc::Matrix3x3 m1;

    EXPECT_DOUBLE_EQ( m1(0,0), 0.0 );
    EXPECT_DOUBLE_EQ( m1(0,1), 0.0 );
    EXPECT_DOUBLE_EQ( m1(0,2), 0.0 );
    EXPECT_DOUBLE_EQ( m1(1,0), 0.0 );
    EXPECT_DOUBLE_EQ( m1(1,1), 0.0 );
    EXPECT_DOUBLE_EQ( m1(1,2), 0.0 );
    EXPECT_DOUBLE_EQ( m1(2,0), 0.0 );
    EXPECT_DOUBLE_EQ( m1(2,1), 0.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanInstantiateAndCopy)
{
    mc::Matrix3x3 m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    mc::Matrix3x3 m2( m1 );

    EXPECT_DOUBLE_EQ( m2(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m2(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m2(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m2(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m2(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m2(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m2(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m2(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m2(2,2), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanInstantiateAndSetData)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 );

    EXPECT_DOUBLE_EQ( m1(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m1(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m1(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m1(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m1(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m1(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m1(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m1(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromArray)
{
    double items[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::Matrix3x3 m1( items );

    EXPECT_DOUBLE_EQ( m1(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m1(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m1(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m1(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m1(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m1(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m1(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m1(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromAngles)
{
    mc::Angles a0( 0.0, 0.0, 0.0 );
    mc::Angles a1( M_PI, 0.0, 0.0 );
    mc::Angles a2( 0.0, M_PI, 0.0 );
    mc::Angles a3( 0.0, 0.0, M_PI );
    mc::Angles a4( M_PI_2, M_PI_2, M_PI_2 );
    mc::Angles a5( M_PI_4, M_PI_4, M_PI_4 );
    mc::Angles a6( -M_PI_4,  M_PI_4,  M_PI_4 );
    mc::Angles a7(  M_PI_4, -M_PI_4,  M_PI_4 );
    mc::Angles a8(  M_PI_4,  M_PI_4, -M_PI_4 );

    mc::Matrix3x3 ma0( a0 );
    EXPECT_NEAR( ma0.xx(), 1.0, 1.0e-9 );
    EXPECT_NEAR( ma0.xy(), 0.0, 1.0e-9 );
    EXPECT_NEAR( ma0.xz(), 0.0, 1.0e-9 );
    EXPECT_NEAR( ma0.yx(), 0.0, 1.0e-9 );
    EXPECT_NEAR( ma0.yy(), 1.0, 1.0e-9 );
    EXPECT_NEAR( ma0.yz(), 0.0, 1.0e-9 );
    EXPECT_NEAR( ma0.zx(), 0.0, 1.0e-9 );
    EXPECT_NEAR( ma0.zy(), 0.0, 1.0e-9 );
    EXPECT_NEAR( ma0.zz(), 1.0, 1.0e-9 );

    mc::Matrix3x3 ma1( a1 );
    EXPECT_NEAR( ma1.xx(),  1.0, 1.0e-9 );
    EXPECT_NEAR( ma1.xy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma1.xz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma1.yx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma1.yy(), -1.0, 1.0e-9 );
    EXPECT_NEAR( ma1.yz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma1.zx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma1.zy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma1.zz(), -1.0, 1.0e-9 );

    mc::Matrix3x3 ma2( a2 );
    EXPECT_NEAR( ma2.xx(), -1.0, 1.0e-9 );
    EXPECT_NEAR( ma2.xy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma2.xz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma2.yx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma2.yy(),  1.0, 1.0e-9 );
    EXPECT_NEAR( ma2.yz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma2.zx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma2.zy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma2.zz(), -1.0, 1.0e-9 );

    mc::Matrix3x3 ma3( a3 );
    EXPECT_NEAR( ma3.xx(), -1.0, 1.0e-9 );
    EXPECT_NEAR( ma3.xy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma3.xz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma3.yx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma3.yy(), -1.0, 1.0e-9 );
    EXPECT_NEAR( ma3.yz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma3.zx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma3.zy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma3.zz(),  1.0, 1.0e-9 );

    mc::Matrix3x3 ma4( a4 );
    EXPECT_NEAR( ma4.xx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma4.xy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma4.xz(), -1.0, 1.0e-9 );
    EXPECT_NEAR( ma4.yx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma4.yy(),  1.0, 1.0e-9 );
    EXPECT_NEAR( ma4.yz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma4.zx(),  1.0, 1.0e-9 );
    EXPECT_NEAR( ma4.zy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( ma4.zz(),  0.0, 1.0e-9 );

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 ma5( a5 );
    EXPECT_NEAR( ma5.xx(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( ma5.xy(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( ma5.xz(), -0.7071, 1.0e-3 );
    EXPECT_NEAR( ma5.yx(), -0.1464, 1.0e-3 );
    EXPECT_NEAR( ma5.yy(),  0.8536, 1.0e-3 );
    EXPECT_NEAR( ma5.yz(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( ma5.zx(),  0.8536, 1.0e-3 );
    EXPECT_NEAR( ma5.zy(), -0.1464, 1.0e-3 );
    EXPECT_NEAR( ma5.zz(),  0.5000, 1.0e-3 );

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 ma6( a6 );
    EXPECT_NEAR( ma6.xx(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( ma6.xy(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( ma6.xz(), -0.7071, 1.0e-3 );
    EXPECT_NEAR( ma6.yx(), -0.8536, 1.0e-3 );
    EXPECT_NEAR( ma6.yy(),  0.1464, 1.0e-3 );
    EXPECT_NEAR( ma6.yz(), -0.5000, 1.0e-3 );
    EXPECT_NEAR( ma6.zx(), -0.1464, 1.0e-3 );
    EXPECT_NEAR( ma6.zy(),  0.8536, 1.0e-3 );
    EXPECT_NEAR( ma6.zz(),  0.5000, 1.0e-3 );

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 ma7( a7 );
    EXPECT_NEAR( ma7.xx(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( ma7.xy(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( ma7.xz(),  0.7071, 1.0e-3 );
    EXPECT_NEAR( ma7.yx(), -0.8536, 1.0e-3 );
    EXPECT_NEAR( ma7.yy(),  0.1464, 1.0e-3 );
    EXPECT_NEAR( ma7.yz(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( ma7.zx(),  0.1464, 1.0e-3 );
    EXPECT_NEAR( ma7.zy(), -0.8536, 1.0e-3 );
    EXPECT_NEAR( ma7.zz(),  0.5000, 1.0e-3 );

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 ma8( a8 );
    EXPECT_NEAR( ma8.xx(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( ma8.xy(), -0.5000, 1.0e-3 );
    EXPECT_NEAR( ma8.xz(), -0.7071, 1.0e-3 );
    EXPECT_NEAR( ma8.yx(),  0.8536, 1.0e-3 );
    EXPECT_NEAR( ma8.yy(),  0.1464, 1.0e-3 );
    EXPECT_NEAR( ma8.yz(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( ma8.zx(), -0.1464, 1.0e-3 );
    EXPECT_NEAR( ma8.zy(), -0.8536, 1.0e-3 );
    EXPECT_NEAR( ma8.zz(),  0.5000, 1.0e-3 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromQuaternion)
{
    mc::Angles a0( 0.0, 0.0, 0.0 );
    mc::Angles a1( M_PI, 0.0, 0.0 );
    mc::Angles a2( 0.0, M_PI, 0.0 );
    mc::Angles a3( 0.0, 0.0, M_PI );
    mc::Angles a4( M_PI_2, M_PI_2, M_PI_2 );
    mc::Angles a5( M_PI_4, M_PI_4, M_PI_4 );
    mc::Angles a6( -M_PI_4,  M_PI_4,  M_PI_4 );
    mc::Angles a7(  M_PI_4, -M_PI_4,  M_PI_4 );
    mc::Angles a8(  M_PI_4,  M_PI_4, -M_PI_4 );

    mc::Quaternion q0( a0 );
    mc::Quaternion q1( a1 );
    mc::Quaternion q2( a2 );
    mc::Quaternion q3( a3 );
    mc::Quaternion q4( a4 );
    mc::Quaternion q5( a5 );
    mc::Quaternion q6( a6 );
    mc::Quaternion q7( a7 );
    mc::Quaternion q8( a8 );

    mc::Matrix3x3 mq0( q0 );
    EXPECT_NEAR( mq0.xx(), 1.0, 1.0e-9 );
    EXPECT_NEAR( mq0.xy(), 0.0, 1.0e-9 );
    EXPECT_NEAR( mq0.xz(), 0.0, 1.0e-9 );
    EXPECT_NEAR( mq0.yx(), 0.0, 1.0e-9 );
    EXPECT_NEAR( mq0.yy(), 1.0, 1.0e-9 );
    EXPECT_NEAR( mq0.yz(), 0.0, 1.0e-9 );
    EXPECT_NEAR( mq0.zx(), 0.0, 1.0e-9 );
    EXPECT_NEAR( mq0.zy(), 0.0, 1.0e-9 );
    EXPECT_NEAR( mq0.zz(), 1.0, 1.0e-9 );

    mc::Matrix3x3 mq1( q1 );
    EXPECT_NEAR( mq1.xx(),  1.0, 1.0e-9 );
    EXPECT_NEAR( mq1.xy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq1.xz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq1.yx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq1.yy(), -1.0, 1.0e-9 );
    EXPECT_NEAR( mq1.yz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq1.zx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq1.zy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq1.zz(), -1.0, 1.0e-9 );

    mc::Matrix3x3 mq2( q2 );
    EXPECT_NEAR( mq2.xx(), -1.0, 1.0e-9 );
    EXPECT_NEAR( mq2.xy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq2.xz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq2.yx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq2.yy(),  1.0, 1.0e-9 );
    EXPECT_NEAR( mq2.yz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq2.zx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq2.zy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq2.zz(), -1.0, 1.0e-9 );

    mc::Matrix3x3 mq3( q3 );
    EXPECT_NEAR( mq3.xx(), -1.0, 1.0e-9 );
    EXPECT_NEAR( mq3.xy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq3.xz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq3.yx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq3.yy(), -1.0, 1.0e-9 );
    EXPECT_NEAR( mq3.yz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq3.zx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq3.zy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq3.zz(),  1.0, 1.0e-9 );

    mc::Matrix3x3 mq4( q4 );
    EXPECT_NEAR( mq4.xx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq4.xy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq4.xz(), -1.0, 1.0e-9 );
    EXPECT_NEAR( mq4.yx(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq4.yy(),  1.0, 1.0e-9 );
    EXPECT_NEAR( mq4.yz(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq4.zx(),  1.0, 1.0e-9 );
    EXPECT_NEAR( mq4.zy(),  0.0, 1.0e-9 );
    EXPECT_NEAR( mq4.zz(),  0.0, 1.0e-9 );

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 mq5( q5 );
    EXPECT_NEAR( mq5.xx(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( mq5.xy(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( mq5.xz(), -0.7071, 1.0e-3 );
    EXPECT_NEAR( mq5.yx(), -0.1464, 1.0e-3 );
    EXPECT_NEAR( mq5.yy(),  0.8536, 1.0e-3 );
    EXPECT_NEAR( mq5.yz(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( mq5.zx(),  0.8536, 1.0e-3 );
    EXPECT_NEAR( mq5.zy(), -0.1464, 1.0e-3 );
    EXPECT_NEAR( mq5.zz(),  0.5000, 1.0e-3 );

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 mq6( q6 );
    EXPECT_NEAR( mq6.xx(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( mq6.xy(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( mq6.xz(), -0.7071, 1.0e-3 );
    EXPECT_NEAR( mq6.yx(), -0.8536, 1.0e-3 );
    EXPECT_NEAR( mq6.yy(),  0.1464, 1.0e-3 );
    EXPECT_NEAR( mq6.yz(), -0.5000, 1.0e-3 );
    EXPECT_NEAR( mq6.zx(), -0.1464, 1.0e-3 );
    EXPECT_NEAR( mq6.zy(),  0.8536, 1.0e-3 );
    EXPECT_NEAR( mq6.zz(),  0.5000, 1.0e-3 );

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 mq7( q7 );
    EXPECT_NEAR( mq7.xx(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( mq7.xy(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( mq7.xz(),  0.7071, 1.0e-3 );
    EXPECT_NEAR( mq7.yx(), -0.8536, 1.0e-3 );
    EXPECT_NEAR( mq7.yy(),  0.1464, 1.0e-3 );
    EXPECT_NEAR( mq7.yz(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( mq7.zx(),  0.1464, 1.0e-3 );
    EXPECT_NEAR( mq7.zy(), -0.8536, 1.0e-3 );
    EXPECT_NEAR( mq7.zz(),  0.5000, 1.0e-3 );

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 mq8( q8 );
    EXPECT_NEAR( mq8.xx(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( mq8.xy(), -0.5000, 1.0e-3 );
    EXPECT_NEAR( mq8.xz(), -0.7071, 1.0e-3 );
    EXPECT_NEAR( mq8.yx(),  0.8536, 1.0e-3 );
    EXPECT_NEAR( mq8.yy(),  0.1464, 1.0e-3 );
    EXPECT_NEAR( mq8.yz(),  0.5000, 1.0e-3 );
    EXPECT_NEAR( mq8.zx(), -0.1464, 1.0e-3 );
    EXPECT_NEAR( mq8.zy(), -0.8536, 1.0e-3 );
    EXPECT_NEAR( mq8.zz(),  0.5000, 1.0e-3 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromString)
{
    char str[] =
    { R"##(
        1.0 2.0 3.0
        4.0 5.0 6.0
        7.0 8.0 9.0
    )##" };
    mc::Matrix3x3 m1( str );

    EXPECT_DOUBLE_EQ( m1(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m1(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m1(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m1(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m1(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m1(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m1(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m1(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanAccessXX)
{
    mc::Matrix3x3 m0;

    m0.xx() = 1.0;

    EXPECT_DOUBLE_EQ( m0.xx(), 1.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanAccessXY)
{
    mc::Matrix3x3 m0;

    m0.xy() = 1.0;

    EXPECT_DOUBLE_EQ( m0.xx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), 1.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanAccessXZ)
{
    mc::Matrix3x3 m0;

    m0.xz() = 1.0;

    EXPECT_DOUBLE_EQ( m0.xx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 1.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanAccessYX)
{
    mc::Matrix3x3 m0;

    m0.yx() = 1.0;

    EXPECT_DOUBLE_EQ( m0.xx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), 1.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanAccessYY)
{
    mc::Matrix3x3 m0;

    m0.yy() = 1.0;

    EXPECT_DOUBLE_EQ( m0.xx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 1.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanAccessYZ)
{
    mc::Matrix3x3 m0;

    m0.yz() = 1.0;

    EXPECT_DOUBLE_EQ( m0.xx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), 1.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanAccessZX)
{
    mc::Matrix3x3 m0;

    m0.zx() = 1.0;

    EXPECT_DOUBLE_EQ( m0.xx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 1.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanAccessZY)
{
    mc::Matrix3x3 m0;

    m0.zy() = 1.0;

    EXPECT_DOUBLE_EQ( m0.xx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), 1.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanAccessZZ)
{
    mc::Matrix3x3 m0;

    m0.zz() = 1.0;

    EXPECT_DOUBLE_EQ( m0.xx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanSetDat)
{
    mc::Matrix3x3 m0;

    m0.set( 11.0, 12.0, 13.0,
            21.0, 22.0, 23.0,
            31.0, 32.0, 33.0 );

    EXPECT_DOUBLE_EQ( m0.xx(), 11.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), 12.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 13.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), 21.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 22.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), 23.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 31.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), 32.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 33.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanTranspose)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    m1.transpose();

    EXPECT_DOUBLE_EQ( m1.xx(), 1.0 );
    EXPECT_DOUBLE_EQ( m1.xy(), 4.0 );
    EXPECT_DOUBLE_EQ( m1.xz(), 7.0 );
    EXPECT_DOUBLE_EQ( m1.yx(), 2.0 );
    EXPECT_DOUBLE_EQ( m1.yy(), 5.0 );
    EXPECT_DOUBLE_EQ( m1.yz(), 8.0 );
    EXPECT_DOUBLE_EQ( m1.zx(), 3.0 );
    EXPECT_DOUBLE_EQ( m1.zy(), 6.0 );
    EXPECT_DOUBLE_EQ( m1.zz(), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanGetAngles)
{
    mc::Matrix3x3 ma0( mc::Angles( 0.0, 0.0, 0.0 ) );
    mc::Matrix3x3 ma1( mc::Angles( M_PI, 0.0, 0.0 ) );
    mc::Matrix3x3 ma3( mc::Angles( 0.0, 0.0, M_PI ) );

    mc::Angles a0 =  ma0.getAngles();
    mc::Angles a1 =  ma1.getAngles();
    mc::Angles a3 =  ma3.getAngles();

    EXPECT_NEAR( a0.phi(), 0.0  , 1.0e-9 );
    EXPECT_NEAR( a0.tht(), 0.0  , 1.0e-9 );
    EXPECT_NEAR( a0.psi(), 0.0  , 1.0e-9 );

    EXPECT_NEAR( a1.phi(), M_PI , 1.0e-9 );
    EXPECT_NEAR( a1.tht(), 0.0  , 1.0e-9 );
    EXPECT_NEAR( a1.psi(), 0.0  , 1.0e-9 );

    EXPECT_NEAR( a3.phi(), 0.0  , 1.0e-9 );
    EXPECT_NEAR( a3.tht(), 0.0  , 1.0e-9 );
    EXPECT_NEAR( a3.psi(), M_PI , 1.0e-9 );

    // singularity - gimbal lock
    mc::Matrix3x3 mas1( mc::Angles(    0.0, M_PI_2,    0.0 ) );
    mc::Matrix3x3 mas2( mc::Angles( M_PI_4, M_PI_2,    0.0 ) );
    mc::Matrix3x3 mas3( mc::Angles( M_PI_2, M_PI_2,    0.0 ) );
    mc::Matrix3x3 mas4( mc::Angles(   M_PI, M_PI_2,    0.0 ) );
    mc::Matrix3x3 mas5( mc::Angles(    0.0, M_PI_2, M_PI_2 ) );

    mc::Angles as1 = mas1.getAngles();
    mc::Angles as2 = mas2.getAngles();
    mc::Angles as3 = mas3.getAngles();
    mc::Angles as4 = mas4.getAngles();
    mc::Angles as5 = mas5.getAngles();

    EXPECT_NEAR( as1.phi(),     0.0, 1.0e-9 );
    EXPECT_NEAR( as1.tht(),  M_PI_2, 1.0e-9 );
    EXPECT_NEAR( as1.psi(),     0.0, 1.0e-9 );

    EXPECT_NEAR( as2.phi(),  M_PI_4, 1.0e-9 );
    EXPECT_NEAR( as2.tht(),  M_PI_2, 1.0e-9 );
    EXPECT_NEAR( as2.psi(),     0.0, 1.0e-9 );

    EXPECT_NEAR( as3.phi(),  M_PI_2, 1.0e-9 );
    EXPECT_NEAR( as3.tht(),  M_PI_2, 1.0e-9 );
    EXPECT_NEAR( as3.psi(),     0.0, 1.0e-9 );

    EXPECT_NEAR( as4.phi(),    M_PI, 1.0e-9 );
    EXPECT_NEAR( as4.tht(),  M_PI_2, 1.0e-9 );
    EXPECT_NEAR( as4.psi(),     0.0, 1.0e-9 );

    EXPECT_NEAR( as5.phi(), -M_PI_2, 1.0e-9 );
    EXPECT_NEAR( as5.tht(),  M_PI_2, 1.0e-9 );
    EXPECT_NEAR( as5.psi(),     0.0, 1.0e-9 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanGetQuaternion)
{
    mc::Matrix3x3 mq0( mc::Quaternion::zeroRotationQuaternion() );
    mc::Matrix3x3 mq1( mc::Quaternion( 0.6, 0.0, 0.0, 0.8 ) );

    mc::Quaternion q0 = mq0.getQuaternion();
    mc::Quaternion q1 = mq1.getQuaternion();

    EXPECT_NEAR( q0.e0(), 1.0, 1.0e-9 );
    EXPECT_NEAR( q0.ex(), 0.0, 1.0e-9 );
    EXPECT_NEAR( q0.ey(), 0.0, 1.0e-9 );
    EXPECT_NEAR( q0.ez(), 0.0, 1.0e-9 );

    EXPECT_NEAR( q1.e0(), 0.6, 1.0e-9 );
    EXPECT_NEAR( q1.ex(), 0.0, 1.0e-9 );
    EXPECT_NEAR( q1.ey(), 0.0, 1.0e-9 );
    EXPECT_NEAR( q1.ez(), 0.8, 1.0e-9 );

    mc::Matrix3x3 m1(  1.0,  0.0,  0.0,
                       0.0,  1.0,  0.0,
                       0.0,  0.0,  1.0 );
    mc::Matrix3x3 m2( -1.0,  0.0,  0.0,
                       0.0, -1.0,  0.0,
                       0.0,  0.0,  1.0 );
    mc::Matrix3x3 m3( -1.0,  0.0,  0.0,
                       0.0,  1.0,  0.0,
                       0.0,  0.0, -1.0 );
    mc::Matrix3x3 m4(  1.0,  0.0,  0.0,
                       0.0, -1.0,  0.0,
                       0.0,  0.0, -1.0 );

    mc::Angles a1 = m1.getAngles();
    mc::Angles a2 = m2.getAngles();
    mc::Angles a3 = m3.getAngles();
    mc::Angles a4 = m4.getAngles();

    mc::Quaternion qa1( a1 );
    mc::Quaternion qa2( a2 );
    mc::Quaternion qa3( a3 );
    mc::Quaternion qa4( a4 );

    mc::Quaternion qm1 = m1.getQuaternion();
    mc::Quaternion qm2 = m2.getQuaternion();
    mc::Quaternion qm3 = m3.getQuaternion();
    mc::Quaternion qm4 = m4.getQuaternion();

    EXPECT_NEAR( qa1.e0(), qm1.e0(), 1.0e-9 );
    EXPECT_NEAR( qa1.ex(), qm1.ex(), 1.0e-9 );
    EXPECT_NEAR( qa1.ey(), qm1.ey(), 1.0e-9 );
    EXPECT_NEAR( qa1.ez(), qm1.ez(), 1.0e-9 );

    EXPECT_NEAR( qa2.e0(), qm2.e0(), 1.0e-9 );
    EXPECT_NEAR( qa2.ex(), qm2.ex(), 1.0e-9 );
    EXPECT_NEAR( qa2.ey(), qm2.ey(), 1.0e-9 );
    EXPECT_NEAR( qa2.ez(), qm2.ez(), 1.0e-9 );

    EXPECT_NEAR( qa3.e0(), qm3.e0(), 1.0e-9 );
    EXPECT_NEAR( qa3.ex(), qm3.ex(), 1.0e-9 );
    EXPECT_NEAR( qa3.ey(), qm3.ey(), 1.0e-9 );
    EXPECT_NEAR( qa3.ez(), qm3.ez(), 1.0e-9 );

    EXPECT_NEAR( qa4.e0(), qm4.e0(), 1.0e-9 );
    EXPECT_NEAR( qa4.ex(), qm4.ex(), 1.0e-9 );
    EXPECT_NEAR( qa4.ey(), qm4.ey(), 1.0e-9 );
    EXPECT_NEAR( qa4.ez(), qm4.ez(), 1.0e-9 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanGetTransposed)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 mt = m1.getTransposed();

    EXPECT_DOUBLE_EQ( m1(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m1(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m1(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m1(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m1(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m1(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m1(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m1(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 9.0 );

    EXPECT_DOUBLE_EQ( mt.xx(), 1.0 );
    EXPECT_DOUBLE_EQ( mt.xy(), 4.0 );
    EXPECT_DOUBLE_EQ( mt.xz(), 7.0 );
    EXPECT_DOUBLE_EQ( mt.yx(), 2.0 );
    EXPECT_DOUBLE_EQ( mt.yy(), 5.0 );
    EXPECT_DOUBLE_EQ( mt.yz(), 8.0 );
    EXPECT_DOUBLE_EQ( mt.zx(), 3.0 );
    EXPECT_DOUBLE_EQ( mt.zy(), 6.0 );
    EXPECT_DOUBLE_EQ( mt.zz(), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanAssign)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m0;
    m0 = m1;

    EXPECT_DOUBLE_EQ( m0.xx(), 1.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), 2.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 3.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), 4.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 5.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), 6.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 7.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), 8.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanAdd)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m2( 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0 );

    mc::Matrix3x3 m0 = m1 + m2;

    EXPECT_DOUBLE_EQ( m0.xx(),  2.0 );
    EXPECT_DOUBLE_EQ( m0.xy(),  3.0 );
    EXPECT_DOUBLE_EQ( m0.xz(),  4.0 );
    EXPECT_DOUBLE_EQ( m0.yx(),  5.0 );
    EXPECT_DOUBLE_EQ( m0.yy(),  6.0 );
    EXPECT_DOUBLE_EQ( m0.yz(),  7.0 );
    EXPECT_DOUBLE_EQ( m0.zx(),  8.0 );
    EXPECT_DOUBLE_EQ( m0.zy(),  9.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 10.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanNegate)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m0 = -m1;

    EXPECT_DOUBLE_EQ( m0.xx(), -1.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), -2.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), -3.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), -4.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), -5.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), -6.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), -7.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), -8.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), -9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanSubstract)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m2( 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0 );

    mc::Matrix3x3 m0 = m1 - m2;

    EXPECT_DOUBLE_EQ( m0.xx(), 0.0 );
    EXPECT_DOUBLE_EQ( m0.xy(), 1.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 2.0 );
    EXPECT_DOUBLE_EQ( m0.yx(), 3.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 4.0 );
    EXPECT_DOUBLE_EQ( m0.yz(), 5.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 6.0 );
    EXPECT_DOUBLE_EQ( m0.zy(), 7.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 8.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanMultiplyByScalar)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m0 = m1 * 0.5;

    EXPECT_DOUBLE_EQ( m0.xx(), 0.5 );
    EXPECT_DOUBLE_EQ( m0.xy(), 1.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 1.5 );
    EXPECT_DOUBLE_EQ( m0.yx(), 2.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 2.5 );
    EXPECT_DOUBLE_EQ( m0.yz(), 3.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 3.5 );
    EXPECT_DOUBLE_EQ( m0.zy(), 4.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 4.5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanMultiplyByMatrix)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m2( 1.1, 2.2, 3.3,
                      4.4, 5.5, 6.6,
                      7.7, 8.8, 9.9 );

    mc::Matrix3x3 m0 = m1 * m2;

    EXPECT_NEAR( m0.xx(),  33.0, 1.0e-9 );
    EXPECT_NEAR( m0.xy(),  39.6, 1.0e-9 );
    EXPECT_NEAR( m0.xz(),  46.2, 1.0e-9 );
    EXPECT_NEAR( m0.yx(),  72.6, 1.0e-9 );
    EXPECT_NEAR( m0.yy(),  89.1, 1.0e-9 );
    EXPECT_NEAR( m0.yz(), 105.6, 1.0e-9 );
    EXPECT_NEAR( m0.zx(), 112.2, 1.0e-9 );
    EXPECT_NEAR( m0.zy(), 138.6, 1.0e-9 );
    EXPECT_NEAR( m0.zz(), 165.0, 1.0e-9 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanMultiplyByVector)
{
    mc::Matrix3x3 m1( 1.0, 0.0, 0.0,
                      0.0, 1.0, 0.0,
                      0.0, 0.0, 1.0 );

    mc::Matrix3x3 m2( -1.0,  0.0,  0.0,
                       0.0, -1.0,  0.0,
                       0.0,  0.0, -1.0 );

    mc::Matrix3x3 m3( 0.0, 1.0, 0.0,
                      1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0 );

    mc::Matrix3x3 m4( 1.0,  0.0,  0.0,
                      0.0,  0.0, -1.0,
                      0.0, -1.0,  0.0 );

    mc::Vector3 v( 1.0, 2.0, 3.0 );

    mc::Vector3 v1 = m1 * v;
    EXPECT_NEAR( v1.x(),  1.0, 1.0e-9 );
    EXPECT_NEAR( v1.y(),  2.0, 1.0e-9 );
    EXPECT_NEAR( v1.z(),  3.0, 1.0e-9 );

    mc::Vector3 v2 = m2 * v;
    EXPECT_NEAR( v2.x(), -1.0, 1.0e-9 );
    EXPECT_NEAR( v2.y(), -2.0, 1.0e-9 );
    EXPECT_NEAR( v2.z(), -3.0, 1.0e-9 );

    mc::Vector3 v3 = m3 * v;
    EXPECT_NEAR( v3.x(),  2.0, 1.0e-9 );
    EXPECT_NEAR( v3.y(),  1.0, 1.0e-9 );
    EXPECT_NEAR( v3.z(),  3.0, 1.0e-9 );

    mc::Vector3 v4 = m4 * v;
    EXPECT_NEAR( v4.x(),  1.0, 1.0e-9 );
    EXPECT_NEAR( v4.y(), -3.0, 1.0e-9 );
    EXPECT_NEAR( v4.z(), -2.0, 1.0e-9 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanDivideByScalar)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );
    mc::Matrix3x3 m0 = m1 / 2.0;

    EXPECT_DOUBLE_EQ( m0.xx(), 0.5 );
    EXPECT_DOUBLE_EQ( m0.xy(), 1.0 );
    EXPECT_DOUBLE_EQ( m0.xz(), 1.5 );
    EXPECT_DOUBLE_EQ( m0.yx(), 2.0 );
    EXPECT_DOUBLE_EQ( m0.yy(), 2.5 );
    EXPECT_DOUBLE_EQ( m0.yz(), 3.0 );
    EXPECT_DOUBLE_EQ( m0.zx(), 3.5 );
    EXPECT_DOUBLE_EQ( m0.zy(), 4.0 );
    EXPECT_DOUBLE_EQ( m0.zz(), 4.5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanUnaryAdd)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m2( 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0 );

    m1 += m2;

    EXPECT_DOUBLE_EQ( m1.xx(),  2.0 );
    EXPECT_DOUBLE_EQ( m1.xy(),  3.0 );
    EXPECT_DOUBLE_EQ( m1.xz(),  4.0 );
    EXPECT_DOUBLE_EQ( m1.yx(),  5.0 );
    EXPECT_DOUBLE_EQ( m1.yy(),  6.0 );
    EXPECT_DOUBLE_EQ( m1.yz(),  7.0 );
    EXPECT_DOUBLE_EQ( m1.zx(),  8.0 );
    EXPECT_DOUBLE_EQ( m1.zy(),  9.0 );
    EXPECT_DOUBLE_EQ( m1.zz(), 10.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanUnarySubstract)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m2( 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0 );

    m1 -= m2;

    EXPECT_DOUBLE_EQ( m1.xx(), 0.0 );
    EXPECT_DOUBLE_EQ( m1.xy(), 1.0 );
    EXPECT_DOUBLE_EQ( m1.xz(), 2.0 );
    EXPECT_DOUBLE_EQ( m1.yx(), 3.0 );
    EXPECT_DOUBLE_EQ( m1.yy(), 4.0 );
    EXPECT_DOUBLE_EQ( m1.yz(), 5.0 );
    EXPECT_DOUBLE_EQ( m1.zx(), 6.0 );
    EXPECT_DOUBLE_EQ( m1.zy(), 7.0 );
    EXPECT_DOUBLE_EQ( m1.zz(), 8.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanUnaryMultiplyByScalar)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    m1 *= 0.5;

    EXPECT_DOUBLE_EQ( m1.xx(), 0.5 );
    EXPECT_DOUBLE_EQ( m1.xy(), 1.0 );
    EXPECT_DOUBLE_EQ( m1.xz(), 1.5 );
    EXPECT_DOUBLE_EQ( m1.yx(), 2.0 );
    EXPECT_DOUBLE_EQ( m1.yy(), 2.5 );
    EXPECT_DOUBLE_EQ( m1.yz(), 3.0 );
    EXPECT_DOUBLE_EQ( m1.zx(), 3.5 );
    EXPECT_DOUBLE_EQ( m1.zy(), 4.0 );
    EXPECT_DOUBLE_EQ( m1.zz(), 4.5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix3x3, CanUnaryDivideByScalar)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    m1 /= 2.0;

    EXPECT_DOUBLE_EQ( m1.xx(), 0.5 );
    EXPECT_DOUBLE_EQ( m1.xy(), 1.0 );
    EXPECT_DOUBLE_EQ( m1.xz(), 1.5 );
    EXPECT_DOUBLE_EQ( m1.yx(), 2.0 );
    EXPECT_DOUBLE_EQ( m1.yy(), 2.5 );
    EXPECT_DOUBLE_EQ( m1.yz(), 3.0 );
    EXPECT_DOUBLE_EQ( m1.zx(), 3.5 );
    EXPECT_DOUBLE_EQ( m1.zy(), 4.0 );
    EXPECT_DOUBLE_EQ( m1.zz(), 4.5 );
}
