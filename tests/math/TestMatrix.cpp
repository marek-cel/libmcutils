#include <gtest/gtest.h>

#include <mcutils/math/Matrix.h>

////////////////////////////////////////////////////////////////////////////////

class TestMatrix : public ::testing::Test
{
protected:
    TestMatrix() {}
    virtual ~TestMatrix() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanConstruct)
{
    mc::Matrix<3,3> *m = nullptr;
    EXPECT_NO_THROW( ( m = new mc::Matrix<3,3>() ) );
    delete m;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanDestruct)
{
    mc::Matrix<3,3> *m3 = new mc::Matrix<3,3>();
    EXPECT_NO_THROW( delete m3 );

    mc::Matrix<4,4> *m4 = new mc::Matrix<4,4>();
    EXPECT_NO_THROW( delete m4 );

    mc::Matrix<6,6> *m6 = new mc::Matrix<6,6>();
    EXPECT_NO_THROW( delete m6 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanInstantiate)
{
    mc::Matrix<3,3> m1;

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

TEST_F(TestMatrix, CanInstantiateAndCopy)
{
    mc::Matrix<3,3> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    mc::Matrix<3,3> m2( m1 );

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

TEST_F(TestMatrix, CanInstantiateAndSetData)
{
    double items[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::Matrix<3,3> m1( items );

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

TEST_F(TestMatrix, CanValidate)
{
    mc::Matrix<3,3> m1;

    EXPECT_TRUE( m1.isValid() );

    mc::Matrix<3,3> m2( m1 );

    m2(0,0) = 1.0;
    m2(0,1) = 2.0;
    m2(0,2) = 3.0;
    m2(1,0) = 4.0;
    m2(1,1) = 5.0;
    m2(1,2) = 6.0;
    m2(2,0) = 7.0;
    m2(2,1) = 8.0;
    m2(2,2) = 9.0;

    EXPECT_TRUE( m2.isValid() );

    mc::Matrix<3,3> m3( m1 );

    m3(0,0) = std::numeric_limits<double>::quiet_NaN();
    m3(0,1) = 2.0;
    m3(0,2) = 3.0;
    m3(1,0) = 4.0;
    m3(1,1) = 5.0;
    m3(1,2) = 6.0;
    m3(2,0) = 7.0;
    m3(2,1) = 8.0;
    m3(2,2) = 9.0;

    EXPECT_FALSE( m3.isValid() );

    mc::Matrix<3,3> m4( m1 );

    m4(0,0) = 1.0;
    m4(0,1) = 2.0;
    m4(0,2) = 3.0;
    m4(1,0) = 4.0;
    m4(1,1) = std::numeric_limits<double>::quiet_NaN();
    m4(1,2) = 6.0;
    m4(2,0) = 7.0;
    m4(2,1) = 8.0;
    m4(2,2) = 9.0;

    EXPECT_FALSE( m4.isValid() );

    mc::Matrix<3,3> m5( m1 );

    m5(0,0) = std::numeric_limits<double>::quiet_NaN();
    m5(0,1) = std::numeric_limits<double>::quiet_NaN();
    m5(0,2) = std::numeric_limits<double>::quiet_NaN();
    m5(1,0) = std::numeric_limits<double>::quiet_NaN();
    m5(1,1) = std::numeric_limits<double>::quiet_NaN();
    m5(1,2) = std::numeric_limits<double>::quiet_NaN();
    m5(2,0) = std::numeric_limits<double>::quiet_NaN();
    m5(2,1) = std::numeric_limits<double>::quiet_NaN();
    m5(2,2) = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE( m4.isValid() );
}


////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanCopyToArray)
{
    mc::Matrix<3,3> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    double x[ 9 ];

    m1.getArray( x );

    EXPECT_DOUBLE_EQ( x[ 0 ], 1.0 );
    EXPECT_DOUBLE_EQ( x[ 1 ], 2.0 );
    EXPECT_DOUBLE_EQ( x[ 2 ], 3.0 );
    EXPECT_DOUBLE_EQ( x[ 3 ], 4.0 );
    EXPECT_DOUBLE_EQ( x[ 4 ], 5.0 );
    EXPECT_DOUBLE_EQ( x[ 5 ], 6.0 );
    EXPECT_DOUBLE_EQ( x[ 6 ], 7.0 );
    EXPECT_DOUBLE_EQ( x[ 7 ], 8.0 );
    EXPECT_DOUBLE_EQ( x[ 8 ], 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanGetItem)
{
    mc::Matrix<3,3> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    EXPECT_DOUBLE_EQ( m1.getItem(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m1.getItem(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m1.getItem(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m1.getItem(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m1.getItem(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m1.getItem(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m1.getItem(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m1.getItem(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m1.getItem(2,2), 9.0 );

    double r23 = m1.getItem(2,3);
    double r32 = m1.getItem(3,2);

    EXPECT_FALSE( r23 == r23 ); // NaN
    EXPECT_FALSE( r32 == r32 ); // NaN
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanAssignDataFromArray)
{
    double items[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::Matrix<3,3> m1;

    m1.setArray( items );

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

TEST_F(TestMatrix, CanSetItem)
{
    mc::Matrix<3,3> m1;

    m1.setItem( 0,0, 1.0 );
    m1.setItem( 0,1, 2.0 );
    m1.setItem( 0,2, 3.0 );
    m1.setItem( 1,0, 4.0 );
    m1.setItem( 1,1, 5.0 );
    m1.setItem( 1,2, 6.0 );
    m1.setItem( 2,0, 7.0 );
    m1.setItem( 2,1, 8.0 );
    m1.setItem( 2,2, 9.0 );

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

TEST_F(TestMatrix, CanSwapRows)
{
    mc::Matrix<3,3> m0;

    m0(0,0) = 1.0;
    m0(0,1) = 2.0;
    m0(0,2) = 3.0;
    m0(1,0) = 4.0;
    m0(1,1) = 5.0;
    m0(1,2) = 6.0;
    m0(2,0) = 7.0;
    m0(2,1) = 8.0;
    m0(2,2) = 9.0;

    EXPECT_DOUBLE_EQ( m0.getItem(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m0.getItem(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m0.getItem(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m0.getItem(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m0.getItem(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m0.getItem(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m0.getItem(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m0.getItem(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m0.getItem(2,2), 9.0 );

    mc::Matrix<3,3> m01( m0 );

    m01.swapRows(0,1);

    EXPECT_DOUBLE_EQ( m01.getItem(1,0), 1.0 );
    EXPECT_DOUBLE_EQ( m01.getItem(1,1), 2.0 );
    EXPECT_DOUBLE_EQ( m01.getItem(1,2), 3.0 );
    EXPECT_DOUBLE_EQ( m01.getItem(0,0), 4.0 );
    EXPECT_DOUBLE_EQ( m01.getItem(0,1), 5.0 );
    EXPECT_DOUBLE_EQ( m01.getItem(0,2), 6.0 );
    EXPECT_DOUBLE_EQ( m01.getItem(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m01.getItem(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m01.getItem(2,2), 9.0 );

    mc::Matrix<3,3> m02( m0 );

    m02.swapRows(0,2);

    EXPECT_DOUBLE_EQ( m02.getItem(2,0), 1.0 );
    EXPECT_DOUBLE_EQ( m02.getItem(2,1), 2.0 );
    EXPECT_DOUBLE_EQ( m02.getItem(2,2), 3.0 );
    EXPECT_DOUBLE_EQ( m02.getItem(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m02.getItem(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m02.getItem(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m02.getItem(0,0), 7.0 );
    EXPECT_DOUBLE_EQ( m02.getItem(0,1), 8.0 );
    EXPECT_DOUBLE_EQ( m02.getItem(0,2), 9.0 );

    mc::Matrix<3,3> m12( m0 );

    m12.swapRows(1,2);

    EXPECT_DOUBLE_EQ( m12.getItem(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m12.getItem(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m12.getItem(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m12.getItem(2,0), 4.0 );
    EXPECT_DOUBLE_EQ( m12.getItem(2,1), 5.0 );
    EXPECT_DOUBLE_EQ( m12.getItem(2,2), 6.0 );
    EXPECT_DOUBLE_EQ( m12.getItem(1,0), 7.0 );
    EXPECT_DOUBLE_EQ( m12.getItem(1,1), 8.0 );
    EXPECT_DOUBLE_EQ( m12.getItem(1,2), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanConvertToString)
{
    mc::Matrix<3,3> m0;

    m0(0,0) = 1.0;
    m0(0,1) = 2.0;
    m0(0,2) = 3.0;
    m0(1,0) = 4.0;
    m0(1,1) = 5.0;
    m0(1,2) = 6.0;
    m0(2,0) = 7.0;
    m0(2,1) = 8.0;
    m0(2,2) = 9.0;

    EXPECT_STREQ( m0.toString().c_str(), "1,2,3,\n4,5,6,\n7,8,9" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanAccessItem)
{
    mc::Matrix<3,3> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

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

TEST_F(TestMatrix, CanAssign)
{
    double items[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };

    mc::Matrix<3,3> m1( items );
    mc::Matrix<3,3> m2;

    m2 = m1;

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

TEST_F(TestMatrix, CanAdd)
{
    mc::Matrix<3,3> m1;
    mc::Matrix<3,3> m2;

    m1(0,0) =  2.0;
    m1(0,1) =  4.0;
    m1(0,2) =  6.0;
    m1(1,0) =  8.0;
    m1(1,1) = 10.0;
    m1(1,2) = 12.0;
    m1(2,0) = 14.0;
    m1(2,1) = 16.0;
    m1(2,2) = 18.0;

    m2(0,0) = 1.0;
    m2(0,1) = 2.0;
    m2(0,2) = 3.0;
    m2(1,0) = 4.0;
    m2(1,1) = 5.0;
    m2(1,2) = 6.0;
    m2(2,0) = 7.0;
    m2(2,1) = 8.0;
    m2(2,2) = 9.0;

    mc::Matrix<3,3> m3 = m1 + m2;

    EXPECT_DOUBLE_EQ( m3(0,0),  3.0 );
    EXPECT_DOUBLE_EQ( m3(0,1),  6.0 );
    EXPECT_DOUBLE_EQ( m3(0,2),  9.0 );
    EXPECT_DOUBLE_EQ( m3(1,0), 12.0 );
    EXPECT_DOUBLE_EQ( m3(1,1), 15.0 );
    EXPECT_DOUBLE_EQ( m3(1,2), 18.0 );
    EXPECT_DOUBLE_EQ( m3(2,0), 21.0 );
    EXPECT_DOUBLE_EQ( m3(2,1), 24.0 );
    EXPECT_DOUBLE_EQ( m3(2,2), 27.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanNegate)
{
    mc::Matrix<3,3> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    mc::Matrix<3,3> m2 = -m1;

    EXPECT_DOUBLE_EQ( m2(0,0), -1.0 );
    EXPECT_DOUBLE_EQ( m2(0,1), -2.0 );
    EXPECT_DOUBLE_EQ( m2(0,2), -3.0 );
    EXPECT_DOUBLE_EQ( m2(1,0), -4.0 );
    EXPECT_DOUBLE_EQ( m2(1,1), -5.0 );
    EXPECT_DOUBLE_EQ( m2(1,2), -6.0 );
    EXPECT_DOUBLE_EQ( m2(2,0), -7.0 );
    EXPECT_DOUBLE_EQ( m2(2,1), -8.0 );
    EXPECT_DOUBLE_EQ( m2(2,2), -9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanSubstract)
{
    mc::Matrix<3,3> m1;
    mc::Matrix<3,3> m2;

    m1(0,0) =  2.0;
    m1(0,1) =  4.0;
    m1(0,2) =  6.0;
    m1(1,0) =  8.0;
    m1(1,1) = 10.0;
    m1(1,2) = 12.0;
    m1(2,0) = 14.0;
    m1(2,1) = 16.0;
    m1(2,2) = 18.0;

    m2(0,0) = 1.0;
    m2(0,1) = 2.0;
    m2(0,2) = 3.0;
    m2(1,0) = 4.0;
    m2(1,1) = 5.0;
    m2(1,2) = 6.0;
    m2(2,0) = 7.0;
    m2(2,1) = 8.0;
    m2(2,2) = 9.0;

    mc::Matrix<3,3> m3 = m1 - m2;

    EXPECT_DOUBLE_EQ( m3(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m3(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m3(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m3(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m3(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m3(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m3(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m3(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m3(2,2), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanMultiplyByScalar)
{
    mc::Matrix<3,3> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    mc::Matrix<3,3> m2 = m1 * 2.0;

    EXPECT_DOUBLE_EQ( m2(0,0),  2.0 );
    EXPECT_DOUBLE_EQ( m2(0,1),  4.0 );
    EXPECT_DOUBLE_EQ( m2(0,2),  6.0 );
    EXPECT_DOUBLE_EQ( m2(1,0),  8.0 );
    EXPECT_DOUBLE_EQ( m2(1,1), 10.0 );
    EXPECT_DOUBLE_EQ( m2(1,2), 12.0 );
    EXPECT_DOUBLE_EQ( m2(2,0), 14.0 );
    EXPECT_DOUBLE_EQ( m2(2,1), 16.0 );
    EXPECT_DOUBLE_EQ( m2(2,2), 18.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanMultiplyByVector)
{
    double x1[] = {  1.0,  0.0,  0.0,
                     0.0,  1.0,  0.0,
                     0.0,  0.0,  1.0 };

    double x2[] = { -1.0,  0.0,  0.0,
                     0.0, -1.0,  0.0,
                     0.0,  0.0, -1.0 };

    double x3[] = {  0.0,  1.0,  0.0,
                     1.0,  0.0,  0.0,
                     0.0,  0.0,  1.0 };

    double x4[] = {  1.0,  0.0,  0.0,
                     0.0,  0.0, -1.0,
                     0.0, -1.0,  0.0 };

    double va[] = { 1.0, 2.0, 3.0 };

    mc::Matrix<3,3> m1( x1 );
    mc::Matrix<3,3> m2( x2 );
    mc::Matrix<3,3> m3( x3 );
    mc::Matrix<3,3> m4( x4 );

    mc::Vector< 3 > v( va );

    mc::Vector< 3 > v1 = m1 * v;
    EXPECT_DOUBLE_EQ( v1( 0 ),  1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ),  2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ),  3.0 );

    mc::Vector< 3 > v2 = m2 * v;
    EXPECT_DOUBLE_EQ( v2( 0 ), -1.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), -2.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), -3.0 );

    mc::Vector< 3 > v3 = m3 * v;
    EXPECT_DOUBLE_EQ( v3( 0 ),  2.0 );
    EXPECT_DOUBLE_EQ( v3( 1 ),  1.0 );
    EXPECT_DOUBLE_EQ( v3( 2 ),  3.0 );

    mc::Vector< 3 > v4 = m4 * v;
    EXPECT_DOUBLE_EQ( v4( 0 ),  1.0 );
    EXPECT_DOUBLE_EQ( v4( 1 ), -3.0 );
    EXPECT_DOUBLE_EQ( v4( 2 ), -2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanDivideByScalar)
{
    mc::Matrix<3,3> m1;

    m1(0,0) =  2.0;
    m1(0,1) =  4.0;
    m1(0,2) =  6.0;
    m1(1,0) =  8.0;
    m1(1,1) = 10.0;
    m1(1,2) = 12.0;
    m1(2,0) = 14.0;
    m1(2,1) = 16.0;
    m1(2,2) = 18.0;

    mc::Matrix<3,3> m2 = m1 / 2.0;

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

TEST_F(TestMatrix, CanUnaryAdd)
{
    mc::Matrix<3,3> m1;
    mc::Matrix<3,3> m2;

    m2(0,0) = 1.0;
    m2(0,1) = 2.0;
    m2(0,2) = 3.0;
    m2(1,0) = 4.0;
    m2(1,1) = 5.0;
    m2(1,2) = 6.0;
    m2(2,0) = 7.0;
    m2(2,1) = 8.0;
    m2(2,2) = 9.0;

    m1 += m2;

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

TEST_F(TestMatrix, CanUnarySubstract)
{
    mc::Matrix<3,3> m1;
    mc::Matrix<3,3> m2;

    m1(0,0) = 1.0;
    m1(0,1) = 1.0;
    m1(0,2) = 1.0;
    m1(1,0) = 1.0;
    m1(1,1) = 1.0;
    m1(1,2) = 1.0;
    m1(2,0) = 1.0;
    m1(2,1) = 1.0;
    m1(2,2) = 1.0;

    m2(0,0) = 1.0;
    m2(0,1) = 2.0;
    m2(0,2) = 3.0;
    m2(1,0) = 4.0;
    m2(1,1) = 5.0;
    m2(1,2) = 6.0;
    m2(2,0) = 7.0;
    m2(2,1) = 8.0;
    m2(2,2) = 9.0;

    m2 -= m1;

    EXPECT_DOUBLE_EQ( m2(0,0), 0.0 );
    EXPECT_DOUBLE_EQ( m2(0,1), 1.0 );
    EXPECT_DOUBLE_EQ( m2(0,2), 2.0 );
    EXPECT_DOUBLE_EQ( m2(1,0), 3.0 );
    EXPECT_DOUBLE_EQ( m2(1,1), 4.0 );
    EXPECT_DOUBLE_EQ( m2(1,2), 5.0 );
    EXPECT_DOUBLE_EQ( m2(2,0), 6.0 );
    EXPECT_DOUBLE_EQ( m2(2,1), 7.0 );
    EXPECT_DOUBLE_EQ( m2(2,2), 8.0 );
}


////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanUnaryMultiplyByScalar)
{
    mc::Matrix<3,3> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    m1 *= 2.0;

    EXPECT_DOUBLE_EQ( m1(0,0),  2.0 );
    EXPECT_DOUBLE_EQ( m1(0,1),  4.0 );
    EXPECT_DOUBLE_EQ( m1(0,2),  6.0 );
    EXPECT_DOUBLE_EQ( m1(1,0),  8.0 );
    EXPECT_DOUBLE_EQ( m1(1,1), 10.0 );
    EXPECT_DOUBLE_EQ( m1(1,2), 12.0 );
    EXPECT_DOUBLE_EQ( m1(2,0), 14.0 );
    EXPECT_DOUBLE_EQ( m1(2,1), 16.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 18.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanUnaryDivideByScalar)
{
    mc::Matrix<3,3> m1;

    m1(0,0) =  2.0;
    m1(0,1) =  4.0;
    m1(0,2) =  6.0;
    m1(1,0) =  8.0;
    m1(1,1) = 10.0;
    m1(1,2) = 12.0;
    m1(2,0) = 14.0;
    m1(2,1) = 16.0;
    m1(2,2) = 18.0;

    m1 /= 2.0;

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

TEST_F(TestMatrix, CanCompare)
{
    mc::Matrix<3,3> m1;
    mc::Matrix<3,3> m2;

    EXPECT_TRUE( m1 == m2 );
    EXPECT_FALSE( m1 != m2 );

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    EXPECT_FALSE( m1 == m2 );
    EXPECT_TRUE( m1 != m2 );

    m2 = m1;

    EXPECT_TRUE( m1 == m2 );
    EXPECT_FALSE( m1 != m2 );
}
