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

TEST_F(TestMatrix, CanGetItems)
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

    double items[9] = { 0.0 };

    m1.getItems( items );

    EXPECT_DOUBLE_EQ( items[0], 1.0 );
    EXPECT_DOUBLE_EQ( items[1], 2.0 );
    EXPECT_DOUBLE_EQ( items[2], 3.0 );
    EXPECT_DOUBLE_EQ( items[3], 4.0 );
    EXPECT_DOUBLE_EQ( items[4], 5.0 );
    EXPECT_DOUBLE_EQ( items[5], 6.0 );
    EXPECT_DOUBLE_EQ( items[6], 7.0 );
    EXPECT_DOUBLE_EQ( items[7], 8.0 );
    EXPECT_DOUBLE_EQ( items[8], 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix, CanSetFromString)
{
    char str3[] =
    { R"##(
        1.0 2.0 3.0
        4.0 5.0 6.0
        7.0 8.0 9.0
    )##" };
    mc::Matrix<3,3> m3;

    m3.setFromString( str3 );

    EXPECT_DOUBLE_EQ( m3(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m3(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m3(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m3(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m3(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m3(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m3(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m3(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m3(2,2), 9.0 );

    char str4[] =
    { R"##(
      1.0   2.0   3.0   4.0
      5.0   6.0   7.0   8.0
      9.0  10.0  11.0  12.0
     13.0  14.0  15.0  16.0
    )##" };

    mc::Matrix<4,4> m4;

    m4.setFromString( str4 );

    EXPECT_DOUBLE_EQ( m4(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( m4(0,1),  2.0 );
    EXPECT_DOUBLE_EQ( m4(0,2),  3.0 );
    EXPECT_DOUBLE_EQ( m4(0,3),  4.0 );
    EXPECT_DOUBLE_EQ( m4(1,0),  5.0 );
    EXPECT_DOUBLE_EQ( m4(1,1),  6.0 );
    EXPECT_DOUBLE_EQ( m4(1,2),  7.0 );
    EXPECT_DOUBLE_EQ( m4(1,3),  8.0 );
    EXPECT_DOUBLE_EQ( m4(2,0),  9.0 );
    EXPECT_DOUBLE_EQ( m4(2,1), 10.0 );
    EXPECT_DOUBLE_EQ( m4(2,2), 11.0 );
    EXPECT_DOUBLE_EQ( m4(2,3), 12.0 );
    EXPECT_DOUBLE_EQ( m4(3,0), 13.0 );
    EXPECT_DOUBLE_EQ( m4(3,1), 14.0 );
    EXPECT_DOUBLE_EQ( m4(3,2), 15.0 );
    EXPECT_DOUBLE_EQ( m4(3,3), 16.0 );

    char str6[] =
    { R"##(
      1.0   2.0   3.0   4.0   5.0   6.0
      7.0   8.0   9.0  10.0  11.0  12.0
     13.0  14.0  15.0  16.0  17.0  18.0
     19.0  20.0  21.0  22.0  23.0  24.0
     25.0  26.0  27.0  28.0  29.0  30.0
     31.0  32.0  33.0  34.0  35.0  36.0
    )##" };

    mc::Matrix<6,6> m6;

    m6.setFromString( str6 );

    EXPECT_DOUBLE_EQ( m6(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( m6(0,1),  2.0 );
    EXPECT_DOUBLE_EQ( m6(0,2),  3.0 );
    EXPECT_DOUBLE_EQ( m6(0,3),  4.0 );
    EXPECT_DOUBLE_EQ( m6(0,4),  5.0 );
    EXPECT_DOUBLE_EQ( m6(0,5),  6.0 );
    EXPECT_DOUBLE_EQ( m6(1,0),  7.0 );
    EXPECT_DOUBLE_EQ( m6(1,1),  8.0 );
    EXPECT_DOUBLE_EQ( m6(1,2),  9.0 );
    EXPECT_DOUBLE_EQ( m6(1,3), 10.0 );
    EXPECT_DOUBLE_EQ( m6(1,4), 11.0 );
    EXPECT_DOUBLE_EQ( m6(1,5), 12.0 );
    EXPECT_DOUBLE_EQ( m6(2,0), 13.0 );
    EXPECT_DOUBLE_EQ( m6(2,1), 14.0 );
    EXPECT_DOUBLE_EQ( m6(2,2), 15.0 );
    EXPECT_DOUBLE_EQ( m6(2,3), 16.0 );
    EXPECT_DOUBLE_EQ( m6(2,4), 17.0 );
    EXPECT_DOUBLE_EQ( m6(2,5), 18.0 );
    EXPECT_DOUBLE_EQ( m6(3,0), 19.0 );
    EXPECT_DOUBLE_EQ( m6(3,1), 20.0 );
    EXPECT_DOUBLE_EQ( m6(3,2), 21.0 );
    EXPECT_DOUBLE_EQ( m6(3,3), 22.0 );
    EXPECT_DOUBLE_EQ( m6(3,4), 23.0 );
    EXPECT_DOUBLE_EQ( m6(3,5), 24.0 );
    EXPECT_DOUBLE_EQ( m6(4,0), 25.0 );
    EXPECT_DOUBLE_EQ( m6(4,1), 26.0 );
    EXPECT_DOUBLE_EQ( m6(4,2), 27.0 );
    EXPECT_DOUBLE_EQ( m6(4,3), 28.0 );
    EXPECT_DOUBLE_EQ( m6(4,4), 29.0 );
    EXPECT_DOUBLE_EQ( m6(4,5), 30.0 );
    EXPECT_DOUBLE_EQ( m6(5,0), 31.0 );
    EXPECT_DOUBLE_EQ( m6(5,1), 32.0 );
    EXPECT_DOUBLE_EQ( m6(5,2), 33.0 );
    EXPECT_DOUBLE_EQ( m6(5,3), 34.0 );
    EXPECT_DOUBLE_EQ( m6(5,4), 35.0 );
    EXPECT_DOUBLE_EQ( m6(5,5), 36.0 );

    char str32[] = { "lorem ipsum" };
    mc::Matrix<3,3> m32;

    m32.setFromString( str32 );

    EXPECT_FALSE( m32.isValid() );
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

TEST_F(TestMatrix, CanSetItems)
{
    mc::Matrix<3,3> m1;

    double items[] = { 1.0, 2.0, 3.0,
                       4.0, 5.0, 6.0,
                       7.0, 8.0, 9.0 };

    m1.setItems( items );

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

    EXPECT_STREQ( m0.toString().c_str(), "1\t2\t3\t\n4\t5\t6\t\n7\t8\t9" );
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
    mc::Matrix<3,3> m1;
    m1(0,0) =  1.0;
    m1(0,1) =  0.0;
    m1(0,2) =  0.0;
    m1(1,0) =  0.0;
    m1(1,1) =  1.0;
    m1(1,2) =  0.0;
    m1(2,0) =  0.0;
    m1(2,1) =  0.0;
    m1(2,2) =  1.0;

    mc::Matrix<3,3> m2;
    m2(0,0) = -1.0;
    m2(0,1) =  0.0;
    m2(0,2) =  0.0;
    m2(1,0) =  0.0;
    m2(1,1) = -1.0;
    m2(1,2) =  0.0;
    m2(2,0) =  0.0;
    m2(2,1) =  0.0;
    m2(2,2) = -1.0;

    mc::Matrix<3,3> m3;
    m3(0,0) =  0.0;
    m3(0,1) =  1.0;
    m3(0,2) =  0.0;
    m3(1,0) =  1.0;
    m3(1,1) =  0.0;
    m3(1,2) =  0.0;
    m3(2,0) =  0.0;
    m3(2,1) =  0.0;
    m3(2,2) =  1.0;

    mc::Matrix<3,3> m4;
    m4(0,0) =  1.0;
    m4(0,1) =  0.0;
    m4(0,2) =  0.0;
    m4(1,0) =  0.0;
    m4(1,1) =  0.0;
    m4(1,2) = -1.0;
    m4(2,0) =  0.0;
    m4(2,1) = -1.0;
    m4(2,2) =  0.0;

    mc::Vector<3> v;
    v( 0 ) = 1.0;
    v( 1 ) = 2.0;
    v( 2 ) = 3.0;

    mc::Vector<3> v1 = m1 * v;
    EXPECT_DOUBLE_EQ( v1( 0 ),  1.0 );
    EXPECT_DOUBLE_EQ( v1( 1 ),  2.0 );
    EXPECT_DOUBLE_EQ( v1( 2 ),  3.0 );

    mc::Vector<3> v2 = m2 * v;
    EXPECT_DOUBLE_EQ( v2( 0 ), -1.0 );
    EXPECT_DOUBLE_EQ( v2( 1 ), -2.0 );
    EXPECT_DOUBLE_EQ( v2( 2 ), -3.0 );

    mc::Vector<3> v3 = m3 * v;
    EXPECT_DOUBLE_EQ( v3( 0 ),  2.0 );
    EXPECT_DOUBLE_EQ( v3( 1 ),  1.0 );
    EXPECT_DOUBLE_EQ( v3( 2 ),  3.0 );

    mc::Vector<3> v4 = m4 * v;
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
