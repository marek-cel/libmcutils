#include <gtest/gtest.h>

#include <mcutils/math/MatrixMxN.h>

////////////////////////////////////////////////////////////////////////////////

class TestMatrixMxN : public ::testing::Test
{
protected:
    TestMatrixMxN() {}
    virtual ~TestMatrixMxN() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanConstruct)
{
    mc::MatrixMxN<3,3> *m = nullptr;
    EXPECT_NO_THROW( ( m = new mc::MatrixMxN<3,3>() ) );
    delete m;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanDestruct)
{
    mc::MatrixMxN<3,3> *m3 = new mc::MatrixMxN<3,3>();
    EXPECT_NO_THROW( delete m3 );

    mc::MatrixMxN<4,4> *m4 = new mc::MatrixMxN<4,4>();
    EXPECT_NO_THROW( delete m4 );

    mc::MatrixMxN<6,6> *m6 = new mc::MatrixMxN<6,6>();
    EXPECT_NO_THROW( delete m6 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanInstantiate)
{
    mc::MatrixMxN<3,3> m1;

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

TEST_F(TestMatrixMxN, CanValidate3x3)
{
    mc::MatrixMxN<3,3> m3_1;
    mc::MatrixMxN<4,4> m4_1;
    mc::MatrixMxN<6,6> m6_1;

    EXPECT_TRUE( m3_1.IsValid() );
    EXPECT_TRUE( m4_1.IsValid() );
    EXPECT_TRUE( m6_1.IsValid() );

    mc::MatrixMxN<3,3> m3_2(m3_1);

    m3_2(0,0) = 1.0;
    m3_2(0,1) = 2.0;
    m3_2(0,2) = 3.0;
    m3_2(1,0) = 4.0;
    m3_2(1,1) = 5.0;
    m3_2(1,2) = 6.0;
    m3_2(2,0) = 7.0;
    m3_2(2,1) = 8.0;
    m3_2(2,2) = 9.0;

    EXPECT_TRUE( m3_2.IsValid() );

    mc::MatrixMxN<3,3> m3_3(m3_1);

    m3_3(0,0) = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE( m3_3.IsValid() );

    mc::MatrixMxN<3,3> m3_4(m3_1);

    m3_4(1,1) = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE( m3_4.IsValid() );

    mc::MatrixMxN<3,3> m3_5(m3_1);

    m3_5(0,0) = std::numeric_limits<double>::quiet_NaN();
    m3_5(0,1) = std::numeric_limits<double>::quiet_NaN();
    m3_5(0,2) = std::numeric_limits<double>::quiet_NaN();
    m3_5(1,0) = std::numeric_limits<double>::quiet_NaN();
    m3_5(1,1) = std::numeric_limits<double>::quiet_NaN();
    m3_5(1,2) = std::numeric_limits<double>::quiet_NaN();
    m3_5(2,0) = std::numeric_limits<double>::quiet_NaN();
    m3_5(2,1) = std::numeric_limits<double>::quiet_NaN();
    m3_5(2,2) = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE( m3_5.IsValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanGetElement)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> m3;
    mc::MatrixMxN<4,4> m4;
    mc::MatrixMxN<6,6> m6;

    m3.SetFromArray(x3);
    m4.SetFromArray(x4);
    m6.SetFromArray(x6);

    EXPECT_DOUBLE_EQ( m3.GetElement(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m3.GetElement(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m3.GetElement(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m3.GetElement(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m3.GetElement(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m3.GetElement(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m3.GetElement(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m3.GetElement(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m3.GetElement(2,2), 9.0 );

    double r23 = m3.GetElement(2,3);
    double r32 = m3.GetElement(3,2);

    EXPECT_FALSE( r23 == r23 ); // NaN
    EXPECT_FALSE( r32 == r32 ); // NaN

    EXPECT_DOUBLE_EQ( m4.GetElement(1,1), 6.0 );
    EXPECT_DOUBLE_EQ( m6.GetElement(1,1), 8.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanPutIntoArray)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> m3;
    mc::MatrixMxN<4,4> m4;
    mc::MatrixMxN<6,6> m6;

    m3.SetFromArray(x3);
    m4.SetFromArray(x4);
    m6.SetFromArray(x6);

    double xx3[9]  = { 0.0 };
    double xx4[16] = { 0.0 };
    double xx6[36] = { 0.0 };

    m3.PutIntoArray(xx3);
    m4.PutIntoArray(xx4);
    m6.PutIntoArray(xx6);

    EXPECT_DOUBLE_EQ( xx3[0], x3[0] );
    EXPECT_DOUBLE_EQ( xx3[1], x3[1] );
    EXPECT_DOUBLE_EQ( xx3[2], x3[2] );
    EXPECT_DOUBLE_EQ( xx3[3], x3[3] );
    EXPECT_DOUBLE_EQ( xx3[4], x3[4] );
    EXPECT_DOUBLE_EQ( xx3[5], x3[5] );
    EXPECT_DOUBLE_EQ( xx3[6], x3[6] );
    EXPECT_DOUBLE_EQ( xx3[7], x3[7] );
    EXPECT_DOUBLE_EQ( xx3[8], x3[8] );

    EXPECT_DOUBLE_EQ( xx4[0]  , x4[0]  );
    EXPECT_DOUBLE_EQ( xx4[1]  , x4[1]  );
    EXPECT_DOUBLE_EQ( xx4[2]  , x4[2]  );
    EXPECT_DOUBLE_EQ( xx4[3]  , x4[3]  );
    EXPECT_DOUBLE_EQ( xx4[4]  , x4[4]  );
    EXPECT_DOUBLE_EQ( xx4[5]  , x4[5]  );
    EXPECT_DOUBLE_EQ( xx4[6]  , x4[6]  );
    EXPECT_DOUBLE_EQ( xx4[7]  , x4[7]  );
    EXPECT_DOUBLE_EQ( xx4[8]  , x4[8]  );
    EXPECT_DOUBLE_EQ( xx4[9]  , x4[9]  );
    EXPECT_DOUBLE_EQ( xx4[10] , x4[10] );
    EXPECT_DOUBLE_EQ( xx4[11] , x4[11] );
    EXPECT_DOUBLE_EQ( xx4[12] , x4[12] );
    EXPECT_DOUBLE_EQ( xx4[13] , x4[13] );
    EXPECT_DOUBLE_EQ( xx4[14] , x4[14] );
    EXPECT_DOUBLE_EQ( xx4[15] , x4[15] );


    EXPECT_DOUBLE_EQ( xx6[0]  , x6[0]  );
    EXPECT_DOUBLE_EQ( xx6[1]  , x6[1]  );
    EXPECT_DOUBLE_EQ( xx6[2]  , x6[2]  );
    EXPECT_DOUBLE_EQ( xx6[3]  , x6[3]  );
    EXPECT_DOUBLE_EQ( xx6[4]  , x6[4]  );
    EXPECT_DOUBLE_EQ( xx6[5]  , x6[5]  );
    EXPECT_DOUBLE_EQ( xx6[6]  , x6[6]  );
    EXPECT_DOUBLE_EQ( xx6[7]  , x6[7]  );
    EXPECT_DOUBLE_EQ( xx6[8]  , x6[8]  );
    EXPECT_DOUBLE_EQ( xx6[9]  , x6[9]  );
    EXPECT_DOUBLE_EQ( xx6[10] , x6[10] );
    EXPECT_DOUBLE_EQ( xx6[11] , x6[11] );
    EXPECT_DOUBLE_EQ( xx6[12] , x6[12] );
    EXPECT_DOUBLE_EQ( xx6[13] , x6[13] );
    EXPECT_DOUBLE_EQ( xx6[14] , x6[14] );
    EXPECT_DOUBLE_EQ( xx6[15] , x6[15] );
    EXPECT_DOUBLE_EQ( xx6[16] , x6[16] );
    EXPECT_DOUBLE_EQ( xx6[17] , x6[17] );
    EXPECT_DOUBLE_EQ( xx6[18] , x6[18] );
    EXPECT_DOUBLE_EQ( xx6[19] , x6[19] );
    EXPECT_DOUBLE_EQ( xx6[20] , x6[20] );
    EXPECT_DOUBLE_EQ( xx6[21] , x6[21] );
    EXPECT_DOUBLE_EQ( xx6[22] , x6[22] );
    EXPECT_DOUBLE_EQ( xx6[23] , x6[23] );
    EXPECT_DOUBLE_EQ( xx6[24] , x6[24] );
    EXPECT_DOUBLE_EQ( xx6[25] , x6[25] );
    EXPECT_DOUBLE_EQ( xx6[26] , x6[26] );
    EXPECT_DOUBLE_EQ( xx6[27] , x6[27] );
    EXPECT_DOUBLE_EQ( xx6[28] , x6[28] );
    EXPECT_DOUBLE_EQ( xx6[29] , x6[29] );
    EXPECT_DOUBLE_EQ( xx6[30] , x6[30] );
    EXPECT_DOUBLE_EQ( xx6[31] , x6[31] );
    EXPECT_DOUBLE_EQ( xx6[32] , x6[32] );
    EXPECT_DOUBLE_EQ( xx6[33] , x6[33] );
    EXPECT_DOUBLE_EQ( xx6[34] , x6[34] );
    EXPECT_DOUBLE_EQ( xx6[35] , x6[35] );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSetElement)
{
    mc::MatrixMxN<3,3> m3;
    mc::MatrixMxN<4,4> m4;
    mc::MatrixMxN<6,6> m6;

    m3.SetElement(0, 0, 1.0);
    m3.SetElement(0, 1, 2.0);
    m3.SetElement(0, 2, 3.0);
    m3.SetElement(1, 0, 4.0);
    m3.SetElement(1, 1, 5.0);
    m3.SetElement(1, 2, 6.0);
    m3.SetElement(2, 0, 7.0);
    m3.SetElement(2, 1, 8.0);
    m3.SetElement(2, 2, 9.0);

    m4.SetElement(1, 1, 11.0);
    m6.SetElement(2, 2, 22.0);

    EXPECT_DOUBLE_EQ( m3(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m3(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m3(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m3(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m3(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m3(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m3(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m3(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m3(2,2), 9.0 );

    EXPECT_DOUBLE_EQ( m4(1,1), 11.0 );
    EXPECT_DOUBLE_EQ( m6(2,2), 22.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSetFromArray)
{
    mc::MatrixMxN<3,3> m1;

    double elements[] = { 1.0, 2.0, 3.0,
                          4.0, 5.0, 6.0,
                          7.0, 8.0, 9.0 };

    m1.SetFromArray(elements);

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

TEST_F(TestMatrixMxN, CanSetFromString)
{
    char str3[] =
    { R"##(
        1.0 2.0 3.0
        4.0 5.0 6.0
        7.0 8.0 9.0
    )##" };

    mc::MatrixMxN<3,3> m3;

    m3.SetFromString(str3);

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

    mc::MatrixMxN<4,4> m4;

    m4.SetFromString(str4);

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

    mc::MatrixMxN<6,6> m6;

    m6.SetFromString(str6);

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
    mc::MatrixMxN<3,3> m32;

    m32.SetFromString(str32);

    EXPECT_FALSE( m32.IsValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSwapRows)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> m3;
    mc::MatrixMxN<4,4> m4;
    mc::MatrixMxN<6,6> m6;

    m3.SetFromArray(x3);
    m4.SetFromArray(x4);
    m6.SetFromArray(x6);

    EXPECT_DOUBLE_EQ( m3(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m3(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m3(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m3(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m3(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m3(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m3(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m3(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m3(2,2), 9.0 );

    mc::MatrixMxN<3,3> m01(m3);
    m01.SwapRows(0, 1);
    EXPECT_DOUBLE_EQ( m01(1,0), 1.0 );
    EXPECT_DOUBLE_EQ( m01(1,1), 2.0 );
    EXPECT_DOUBLE_EQ( m01(1,2), 3.0 );
    EXPECT_DOUBLE_EQ( m01(0,0), 4.0 );
    EXPECT_DOUBLE_EQ( m01(0,1), 5.0 );
    EXPECT_DOUBLE_EQ( m01(0,2), 6.0 );
    EXPECT_DOUBLE_EQ( m01(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m01(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m01(2,2), 9.0 );

    mc::MatrixMxN<3,3> m02(m3);
    m02.SwapRows(0, 2);
    EXPECT_DOUBLE_EQ( m02(2,0), 1.0 );
    EXPECT_DOUBLE_EQ( m02(2,1), 2.0 );
    EXPECT_DOUBLE_EQ( m02(2,2), 3.0 );
    EXPECT_DOUBLE_EQ( m02(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m02(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m02(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m02(0,0), 7.0 );
    EXPECT_DOUBLE_EQ( m02(0,1), 8.0 );
    EXPECT_DOUBLE_EQ( m02(0,2), 9.0 );

    mc::MatrixMxN<3,3> m12(m3);
    m12.SwapRows(1, 2);
    EXPECT_DOUBLE_EQ( m12(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m12(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m12(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m12(2,0), 4.0 );
    EXPECT_DOUBLE_EQ( m12(2,1), 5.0 );
    EXPECT_DOUBLE_EQ( m12(2,2), 6.0 );
    EXPECT_DOUBLE_EQ( m12(1,0), 7.0 );
    EXPECT_DOUBLE_EQ( m12(1,1), 8.0 );
    EXPECT_DOUBLE_EQ( m12(1,2), 9.0 );

    m4.SwapRows(0,1);
    EXPECT_DOUBLE_EQ( m4(0,0),  5.0 );
    EXPECT_DOUBLE_EQ( m4(0,1),  6.0 );
    EXPECT_DOUBLE_EQ( m4(0,2),  7.0 );
    EXPECT_DOUBLE_EQ( m4(0,3),  8.0 );
    EXPECT_DOUBLE_EQ( m4(1,0),  1.0 );
    EXPECT_DOUBLE_EQ( m4(1,1),  2.0 );
    EXPECT_DOUBLE_EQ( m4(1,2),  3.0 );
    EXPECT_DOUBLE_EQ( m4(1,3),  4.0 );
    EXPECT_DOUBLE_EQ( m4(2,0),  9.0 );
    EXPECT_DOUBLE_EQ( m4(2,1), 10.0 );
    EXPECT_DOUBLE_EQ( m4(2,2), 11.0 );
    EXPECT_DOUBLE_EQ( m4(2,3), 12.0 );
    EXPECT_DOUBLE_EQ( m4(3,0), 13.0 );
    EXPECT_DOUBLE_EQ( m4(3,1), 14.0 );
    EXPECT_DOUBLE_EQ( m4(3,2), 15.0 );
    EXPECT_DOUBLE_EQ( m4(3,3), 16.0 );

    m6.SwapRows(0,1);
    EXPECT_DOUBLE_EQ( m6(0,0),  7.0 );
    EXPECT_DOUBLE_EQ( m6(0,1),  8.0 );
    EXPECT_DOUBLE_EQ( m6(0,2),  9.0 );
    EXPECT_DOUBLE_EQ( m6(0,3), 10.0 );
    EXPECT_DOUBLE_EQ( m6(0,4), 11.0 );
    EXPECT_DOUBLE_EQ( m6(0,5), 12.0 );
    EXPECT_DOUBLE_EQ( m6(1,0),  1.0 );
    EXPECT_DOUBLE_EQ( m6(1,1),  2.0 );
    EXPECT_DOUBLE_EQ( m6(1,2),  3.0 );
    EXPECT_DOUBLE_EQ( m6(1,3),  4.0 );
    EXPECT_DOUBLE_EQ( m6(1,4),  5.0 );
    EXPECT_DOUBLE_EQ( m6(1,5),  6.0 );
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
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanConvertToString)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> m3;
    mc::MatrixMxN<4,4> m4;
    mc::MatrixMxN<6,6> m6;

    m3.SetFromArray(x3);
    m4.SetFromArray(x4);
    m6.SetFromArray(x6);

    EXPECT_STREQ( m3.ToString().c_str(), "1\t2\t3\t\n4\t5\t6\t\n7\t8\t9" );
    EXPECT_STREQ( m4.ToString().c_str(), "1\t2\t3\t4\t\n5\t6\t7\t8\t\n9\t10\t11\t12\t\n13\t14\t15\t16" );
    EXPECT_STREQ( m6.ToString().c_str(), "1\t2\t3\t4\t5\t6\t\n7\t8\t9\t10\t11\t12\t\n13\t14\t15\t16\t17\t18\t\n19\t20\t21\t22\t23\t24\t\n25\t26\t27\t28\t29\t30\t\n31\t32\t33\t34\t35\t36" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanAccessItem)
{
    mc::MatrixMxN<3,3> m3;
    m3(0,0) = 1.0;
    m3(0,1) = 2.0;
    m3(0,2) = 3.0;
    m3(1,0) = 4.0;
    m3(1,1) = 5.0;
    m3(1,2) = 6.0;
    m3(2,0) = 7.0;
    m3(2,1) = 8.0;
    m3(2,2) = 9.0;
    const mc::MatrixMxN<3,3> mr3(m3);
    EXPECT_DOUBLE_EQ( mr3(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( mr3(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( mr3(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( mr3(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( mr3(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( mr3(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( mr3(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( mr3(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( mr3(2,2), 9.0 );


    mc::MatrixMxN<4,4> m4;
    m4(0,0) =  1.0;
    m4(0,1) =  2.0;
    m4(0,2) =  3.0;
    m4(0,3) =  4.0;
    m4(1,0) =  5.0;
    m4(1,1) =  6.0;
    m4(1,2) =  7.0;
    m4(1,3) =  8.0;
    m4(2,0) =  9.0;
    m4(2,1) = 10.0;
    m4(2,2) = 11.0;
    m4(2,3) = 12.0;
    m4(3,0) = 13.0;
    m4(3,1) = 14.0;
    m4(3,2) = 15.0;
    m4(3,3) = 16.0;
    const mc::MatrixMxN<4,4> mr4(m4);
    EXPECT_DOUBLE_EQ( mr4(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( mr4(0,1),  2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,2),  3.0 );
    EXPECT_DOUBLE_EQ( mr4(0,3),  4.0 );
    EXPECT_DOUBLE_EQ( mr4(1,0),  5.0 );
    EXPECT_DOUBLE_EQ( mr4(1,1),  6.0 );
    EXPECT_DOUBLE_EQ( mr4(1,2),  7.0 );
    EXPECT_DOUBLE_EQ( mr4(1,3),  8.0 );
    EXPECT_DOUBLE_EQ( mr4(2,0),  9.0 );
    EXPECT_DOUBLE_EQ( mr4(2,1), 10.0 );
    EXPECT_DOUBLE_EQ( mr4(2,2), 11.0 );
    EXPECT_DOUBLE_EQ( mr4(2,3), 12.0 );
    EXPECT_DOUBLE_EQ( mr4(3,0), 13.0 );
    EXPECT_DOUBLE_EQ( mr4(3,1), 14.0 );
    EXPECT_DOUBLE_EQ( mr4(3,2), 15.0 );
    EXPECT_DOUBLE_EQ( mr4(3,3), 16.0 );

    mc::MatrixMxN<6,6> m6;
    m6(0,0) =  1.0;
    m6(0,1) =  2.0;
    m6(0,2) =  3.0;
    m6(0,3) =  4.0;
    m6(0,4) =  5.0;
    m6(0,5) =  6.0;
    m6(1,0) =  7.0;
    m6(1,1) =  8.0;
    m6(1,2) =  9.0;
    m6(1,3) = 10.0;
    m6(1,4) = 11.0;
    m6(1,5) = 12.0;
    m6(2,0) = 13.0;
    m6(2,1) = 14.0;
    m6(2,2) = 15.0;
    m6(2,3) = 16.0;
    m6(2,4) = 17.0;
    m6(2,5) = 18.0;
    m6(3,0) = 19.0;
    m6(3,1) = 20.0;
    m6(3,2) = 21.0;
    m6(3,3) = 22.0;
    m6(3,4) = 23.0;
    m6(3,5) = 24.0;
    m6(4,0) = 25.0;
    m6(4,1) = 26.0;
    m6(4,2) = 27.0;
    m6(4,3) = 28.0;
    m6(4,4) = 29.0;
    m6(4,5) = 30.0;
    m6(5,0) = 31.0;
    m6(5,1) = 32.0;
    m6(5,2) = 33.0;
    m6(5,3) = 34.0;
    m6(5,4) = 35.0;
    m6(5,5) = 36.0;
    const mc::MatrixMxN<6,6> mr6(m6);
    EXPECT_DOUBLE_EQ( mr6(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( mr6(0,1),  2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,2),  3.0 );
    EXPECT_DOUBLE_EQ( mr6(0,3),  4.0 );
    EXPECT_DOUBLE_EQ( mr6(0,4),  5.0 );
    EXPECT_DOUBLE_EQ( mr6(0,5),  6.0 );
    EXPECT_DOUBLE_EQ( mr6(1,0),  7.0 );
    EXPECT_DOUBLE_EQ( mr6(1,1),  8.0 );
    EXPECT_DOUBLE_EQ( mr6(1,2),  9.0 );
    EXPECT_DOUBLE_EQ( mr6(1,3), 10.0 );
    EXPECT_DOUBLE_EQ( mr6(1,4), 11.0 );
    EXPECT_DOUBLE_EQ( mr6(1,5), 12.0 );
    EXPECT_DOUBLE_EQ( mr6(2,0), 13.0 );
    EXPECT_DOUBLE_EQ( mr6(2,1), 14.0 );
    EXPECT_DOUBLE_EQ( mr6(2,2), 15.0 );
    EXPECT_DOUBLE_EQ( mr6(2,3), 16.0 );
    EXPECT_DOUBLE_EQ( mr6(2,4), 17.0 );
    EXPECT_DOUBLE_EQ( mr6(2,5), 18.0 );
    EXPECT_DOUBLE_EQ( mr6(3,0), 19.0 );
    EXPECT_DOUBLE_EQ( mr6(3,1), 20.0 );
    EXPECT_DOUBLE_EQ( mr6(3,2), 21.0 );
    EXPECT_DOUBLE_EQ( mr6(3,3), 22.0 );
    EXPECT_DOUBLE_EQ( mr6(3,4), 23.0 );
    EXPECT_DOUBLE_EQ( mr6(3,5), 24.0 );
    EXPECT_DOUBLE_EQ( mr6(4,0), 25.0 );
    EXPECT_DOUBLE_EQ( mr6(4,1), 26.0 );
    EXPECT_DOUBLE_EQ( mr6(4,2), 27.0 );
    EXPECT_DOUBLE_EQ( mr6(4,3), 28.0 );
    EXPECT_DOUBLE_EQ( mr6(4,4), 29.0 );
    EXPECT_DOUBLE_EQ( mr6(4,5), 30.0 );
    EXPECT_DOUBLE_EQ( mr6(5,0), 31.0 );
    EXPECT_DOUBLE_EQ( mr6(5,1), 32.0 );
    EXPECT_DOUBLE_EQ( mr6(5,2), 33.0 );
    EXPECT_DOUBLE_EQ( mr6(5,3), 34.0 );
    EXPECT_DOUBLE_EQ( mr6(5,4), 35.0 );
    EXPECT_DOUBLE_EQ( mr6(5,5), 36.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanAdd)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> m3;
    mc::MatrixMxN<4,4> m4;
    mc::MatrixMxN<6,6> m6;

    m3.SetFromArray(x3);
    m4.SetFromArray(x4);
    m6.SetFromArray(x6);

    mc::MatrixMxN<3,3> m03;
    mc::MatrixMxN<4,4> m04;
    mc::MatrixMxN<6,6> m06;

    mc::MatrixMxN<3,3> mr3 = m03 + m3;
    mc::MatrixMxN<4,4> mr4 = m04 + m4;
    mc::MatrixMxN<6,6> mr6 = m06 + m6;

    EXPECT_DOUBLE_EQ( mr3(0,0), x3[0] );
    EXPECT_DOUBLE_EQ( mr3(0,1), x3[1] );
    EXPECT_DOUBLE_EQ( mr3(0,2), x3[2] );
    EXPECT_DOUBLE_EQ( mr3(1,0), x3[3] );
    EXPECT_DOUBLE_EQ( mr3(1,1), x3[4] );
    EXPECT_DOUBLE_EQ( mr3(1,2), x3[5] );
    EXPECT_DOUBLE_EQ( mr3(2,0), x3[6] );
    EXPECT_DOUBLE_EQ( mr3(2,1), x3[7] );
    EXPECT_DOUBLE_EQ( mr3(2,2), x3[8] );

    EXPECT_DOUBLE_EQ( mr4(0,0), x4[0]  );
    EXPECT_DOUBLE_EQ( mr4(0,1), x4[1]  );
    EXPECT_DOUBLE_EQ( mr4(0,2), x4[2]  );
    EXPECT_DOUBLE_EQ( mr4(0,3), x4[3]  );
    EXPECT_DOUBLE_EQ( mr4(1,0), x4[4]  );
    EXPECT_DOUBLE_EQ( mr4(1,1), x4[5]  );
    EXPECT_DOUBLE_EQ( mr4(1,2), x4[6]  );
    EXPECT_DOUBLE_EQ( mr4(1,3), x4[7]  );
    EXPECT_DOUBLE_EQ( mr4(2,0), x4[8]  );
    EXPECT_DOUBLE_EQ( mr4(2,1), x4[9]  );
    EXPECT_DOUBLE_EQ( mr4(2,2), x4[10] );
    EXPECT_DOUBLE_EQ( mr4(2,3), x4[11] );
    EXPECT_DOUBLE_EQ( mr4(3,0), x4[12] );
    EXPECT_DOUBLE_EQ( mr4(3,1), x4[13] );
    EXPECT_DOUBLE_EQ( mr4(3,2), x4[14] );
    EXPECT_DOUBLE_EQ( mr4(3,3), x4[15] );

    EXPECT_DOUBLE_EQ( mr6(0,0), x6[0]  );
    EXPECT_DOUBLE_EQ( mr6(0,1), x6[1]  );
    EXPECT_DOUBLE_EQ( mr6(0,2), x6[2]  );
    EXPECT_DOUBLE_EQ( mr6(0,3), x6[3]  );
    EXPECT_DOUBLE_EQ( mr6(0,4), x6[4]  );
    EXPECT_DOUBLE_EQ( mr6(0,5), x6[5]  );
    EXPECT_DOUBLE_EQ( mr6(1,0), x6[6]  );
    EXPECT_DOUBLE_EQ( mr6(1,1), x6[7]  );
    EXPECT_DOUBLE_EQ( mr6(1,2), x6[8]  );
    EXPECT_DOUBLE_EQ( mr6(1,3), x6[9]  );
    EXPECT_DOUBLE_EQ( mr6(1,4), x6[10] );
    EXPECT_DOUBLE_EQ( mr6(1,5), x6[11] );
    EXPECT_DOUBLE_EQ( mr6(2,0), x6[12] );
    EXPECT_DOUBLE_EQ( mr6(2,1), x6[13] );
    EXPECT_DOUBLE_EQ( mr6(2,2), x6[14] );
    EXPECT_DOUBLE_EQ( mr6(2,3), x6[15] );
    EXPECT_DOUBLE_EQ( mr6(2,4), x6[16] );
    EXPECT_DOUBLE_EQ( mr6(2,5), x6[17] );
    EXPECT_DOUBLE_EQ( mr6(3,0), x6[18] );
    EXPECT_DOUBLE_EQ( mr6(3,1), x6[19] );
    EXPECT_DOUBLE_EQ( mr6(3,2), x6[20] );
    EXPECT_DOUBLE_EQ( mr6(3,3), x6[21] );
    EXPECT_DOUBLE_EQ( mr6(3,4), x6[22] );
    EXPECT_DOUBLE_EQ( mr6(3,5), x6[23] );
    EXPECT_DOUBLE_EQ( mr6(4,0), x6[24] );
    EXPECT_DOUBLE_EQ( mr6(4,1), x6[25] );
    EXPECT_DOUBLE_EQ( mr6(4,2), x6[26] );
    EXPECT_DOUBLE_EQ( mr6(4,3), x6[27] );
    EXPECT_DOUBLE_EQ( mr6(4,4), x6[28] );
    EXPECT_DOUBLE_EQ( mr6(4,5), x6[29] );
    EXPECT_DOUBLE_EQ( mr6(5,0), x6[30] );
    EXPECT_DOUBLE_EQ( mr6(5,1), x6[31] );
    EXPECT_DOUBLE_EQ( mr6(5,2), x6[32] );
    EXPECT_DOUBLE_EQ( mr6(5,3), x6[33] );
    EXPECT_DOUBLE_EQ( mr6(5,4), x6[34] );
    EXPECT_DOUBLE_EQ( mr6(5,5), x6[35] );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanNegate)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> m3;
    mc::MatrixMxN<4,4> m4;
    mc::MatrixMxN<6,6> m6;

    m3.SetFromArray(x3);
    m4.SetFromArray(x4);
    m6.SetFromArray(x6);

    mc::MatrixMxN<3,3> mr3 = -m3;
    mc::MatrixMxN<4,4> mr4 = -m4;
    mc::MatrixMxN<6,6> mr6 = -m6;

    EXPECT_DOUBLE_EQ( mr3(0,0), -x3[0] );
    EXPECT_DOUBLE_EQ( mr3(0,1), -x3[1] );
    EXPECT_DOUBLE_EQ( mr3(0,2), -x3[2] );
    EXPECT_DOUBLE_EQ( mr3(1,0), -x3[3] );
    EXPECT_DOUBLE_EQ( mr3(1,1), -x3[4] );
    EXPECT_DOUBLE_EQ( mr3(1,2), -x3[5] );
    EXPECT_DOUBLE_EQ( mr3(2,0), -x3[6] );
    EXPECT_DOUBLE_EQ( mr3(2,1), -x3[7] );
    EXPECT_DOUBLE_EQ( mr3(2,2), -x3[8] );

    EXPECT_DOUBLE_EQ( mr4(0,0), -x4[0]  );
    EXPECT_DOUBLE_EQ( mr4(0,1), -x4[1]  );
    EXPECT_DOUBLE_EQ( mr4(0,2), -x4[2]  );
    EXPECT_DOUBLE_EQ( mr4(0,3), -x4[3]  );
    EXPECT_DOUBLE_EQ( mr4(1,0), -x4[4]  );
    EXPECT_DOUBLE_EQ( mr4(1,1), -x4[5]  );
    EXPECT_DOUBLE_EQ( mr4(1,2), -x4[6]  );
    EXPECT_DOUBLE_EQ( mr4(1,3), -x4[7]  );
    EXPECT_DOUBLE_EQ( mr4(2,0), -x4[8]  );
    EXPECT_DOUBLE_EQ( mr4(2,1), -x4[9]  );
    EXPECT_DOUBLE_EQ( mr4(2,2), -x4[10] );
    EXPECT_DOUBLE_EQ( mr4(2,3), -x4[11] );
    EXPECT_DOUBLE_EQ( mr4(3,0), -x4[12] );
    EXPECT_DOUBLE_EQ( mr4(3,1), -x4[13] );
    EXPECT_DOUBLE_EQ( mr4(3,2), -x4[14] );
    EXPECT_DOUBLE_EQ( mr4(3,3), -x4[15] );

    EXPECT_DOUBLE_EQ( mr6(0,0), -x6[0]  );
    EXPECT_DOUBLE_EQ( mr6(0,1), -x6[1]  );
    EXPECT_DOUBLE_EQ( mr6(0,2), -x6[2]  );
    EXPECT_DOUBLE_EQ( mr6(0,3), -x6[3]  );
    EXPECT_DOUBLE_EQ( mr6(0,4), -x6[4]  );
    EXPECT_DOUBLE_EQ( mr6(0,5), -x6[5]  );
    EXPECT_DOUBLE_EQ( mr6(1,0), -x6[6]  );
    EXPECT_DOUBLE_EQ( mr6(1,1), -x6[7]  );
    EXPECT_DOUBLE_EQ( mr6(1,2), -x6[8]  );
    EXPECT_DOUBLE_EQ( mr6(1,3), -x6[9]  );
    EXPECT_DOUBLE_EQ( mr6(1,4), -x6[10] );
    EXPECT_DOUBLE_EQ( mr6(1,5), -x6[11] );
    EXPECT_DOUBLE_EQ( mr6(2,0), -x6[12] );
    EXPECT_DOUBLE_EQ( mr6(2,1), -x6[13] );
    EXPECT_DOUBLE_EQ( mr6(2,2), -x6[14] );
    EXPECT_DOUBLE_EQ( mr6(2,3), -x6[15] );
    EXPECT_DOUBLE_EQ( mr6(2,4), -x6[16] );
    EXPECT_DOUBLE_EQ( mr6(2,5), -x6[17] );
    EXPECT_DOUBLE_EQ( mr6(3,0), -x6[18] );
    EXPECT_DOUBLE_EQ( mr6(3,1), -x6[19] );
    EXPECT_DOUBLE_EQ( mr6(3,2), -x6[20] );
    EXPECT_DOUBLE_EQ( mr6(3,3), -x6[21] );
    EXPECT_DOUBLE_EQ( mr6(3,4), -x6[22] );
    EXPECT_DOUBLE_EQ( mr6(3,5), -x6[23] );
    EXPECT_DOUBLE_EQ( mr6(4,0), -x6[24] );
    EXPECT_DOUBLE_EQ( mr6(4,1), -x6[25] );
    EXPECT_DOUBLE_EQ( mr6(4,2), -x6[26] );
    EXPECT_DOUBLE_EQ( mr6(4,3), -x6[27] );
    EXPECT_DOUBLE_EQ( mr6(4,4), -x6[28] );
    EXPECT_DOUBLE_EQ( mr6(4,5), -x6[29] );
    EXPECT_DOUBLE_EQ( mr6(5,0), -x6[30] );
    EXPECT_DOUBLE_EQ( mr6(5,1), -x6[31] );
    EXPECT_DOUBLE_EQ( mr6(5,2), -x6[32] );
    EXPECT_DOUBLE_EQ( mr6(5,3), -x6[33] );
    EXPECT_DOUBLE_EQ( mr6(5,4), -x6[34] );
    EXPECT_DOUBLE_EQ( mr6(5,5), -x6[35] );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSubstract)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> m3;
    mc::MatrixMxN<4,4> m4;
    mc::MatrixMxN<6,6> m6;

    m3.SetFromArray(x3);
    m4.SetFromArray(x4);
    m6.SetFromArray(x6);

    mc::MatrixMxN<3,3> m03;
    mc::MatrixMxN<4,4> m04;
    mc::MatrixMxN<6,6> m06;

    mc::MatrixMxN<3,3> mr3 = m03 - m3;
    mc::MatrixMxN<4,4> mr4 = m04 - m4;
    mc::MatrixMxN<6,6> mr6 = m06 - m6;

    EXPECT_DOUBLE_EQ( mr3(0,0), -x3[0] );
    EXPECT_DOUBLE_EQ( mr3(0,1), -x3[1] );
    EXPECT_DOUBLE_EQ( mr3(0,2), -x3[2] );
    EXPECT_DOUBLE_EQ( mr3(1,0), -x3[3] );
    EXPECT_DOUBLE_EQ( mr3(1,1), -x3[4] );
    EXPECT_DOUBLE_EQ( mr3(1,2), -x3[5] );
    EXPECT_DOUBLE_EQ( mr3(2,0), -x3[6] );
    EXPECT_DOUBLE_EQ( mr3(2,1), -x3[7] );
    EXPECT_DOUBLE_EQ( mr3(2,2), -x3[8] );

    EXPECT_DOUBLE_EQ( mr4(0,0), -x4[0]  );
    EXPECT_DOUBLE_EQ( mr4(0,1), -x4[1]  );
    EXPECT_DOUBLE_EQ( mr4(0,2), -x4[2]  );
    EXPECT_DOUBLE_EQ( mr4(0,3), -x4[3]  );
    EXPECT_DOUBLE_EQ( mr4(1,0), -x4[4]  );
    EXPECT_DOUBLE_EQ( mr4(1,1), -x4[5]  );
    EXPECT_DOUBLE_EQ( mr4(1,2), -x4[6]  );
    EXPECT_DOUBLE_EQ( mr4(1,3), -x4[7]  );
    EXPECT_DOUBLE_EQ( mr4(2,0), -x4[8]  );
    EXPECT_DOUBLE_EQ( mr4(2,1), -x4[9]  );
    EXPECT_DOUBLE_EQ( mr4(2,2), -x4[10] );
    EXPECT_DOUBLE_EQ( mr4(2,3), -x4[11] );
    EXPECT_DOUBLE_EQ( mr4(3,0), -x4[12] );
    EXPECT_DOUBLE_EQ( mr4(3,1), -x4[13] );
    EXPECT_DOUBLE_EQ( mr4(3,2), -x4[14] );
    EXPECT_DOUBLE_EQ( mr4(3,3), -x4[15] );

    EXPECT_DOUBLE_EQ( mr6(0,0), -x6[0]  );
    EXPECT_DOUBLE_EQ( mr6(0,1), -x6[1]  );
    EXPECT_DOUBLE_EQ( mr6(0,2), -x6[2]  );
    EXPECT_DOUBLE_EQ( mr6(0,3), -x6[3]  );
    EXPECT_DOUBLE_EQ( mr6(0,4), -x6[4]  );
    EXPECT_DOUBLE_EQ( mr6(0,5), -x6[5]  );
    EXPECT_DOUBLE_EQ( mr6(1,0), -x6[6]  );
    EXPECT_DOUBLE_EQ( mr6(1,1), -x6[7]  );
    EXPECT_DOUBLE_EQ( mr6(1,2), -x6[8]  );
    EXPECT_DOUBLE_EQ( mr6(1,3), -x6[9]  );
    EXPECT_DOUBLE_EQ( mr6(1,4), -x6[10] );
    EXPECT_DOUBLE_EQ( mr6(1,5), -x6[11] );
    EXPECT_DOUBLE_EQ( mr6(2,0), -x6[12] );
    EXPECT_DOUBLE_EQ( mr6(2,1), -x6[13] );
    EXPECT_DOUBLE_EQ( mr6(2,2), -x6[14] );
    EXPECT_DOUBLE_EQ( mr6(2,3), -x6[15] );
    EXPECT_DOUBLE_EQ( mr6(2,4), -x6[16] );
    EXPECT_DOUBLE_EQ( mr6(2,5), -x6[17] );
    EXPECT_DOUBLE_EQ( mr6(3,0), -x6[18] );
    EXPECT_DOUBLE_EQ( mr6(3,1), -x6[19] );
    EXPECT_DOUBLE_EQ( mr6(3,2), -x6[20] );
    EXPECT_DOUBLE_EQ( mr6(3,3), -x6[21] );
    EXPECT_DOUBLE_EQ( mr6(3,4), -x6[22] );
    EXPECT_DOUBLE_EQ( mr6(3,5), -x6[23] );
    EXPECT_DOUBLE_EQ( mr6(4,0), -x6[24] );
    EXPECT_DOUBLE_EQ( mr6(4,1), -x6[25] );
    EXPECT_DOUBLE_EQ( mr6(4,2), -x6[26] );
    EXPECT_DOUBLE_EQ( mr6(4,3), -x6[27] );
    EXPECT_DOUBLE_EQ( mr6(4,4), -x6[28] );
    EXPECT_DOUBLE_EQ( mr6(4,5), -x6[29] );
    EXPECT_DOUBLE_EQ( mr6(5,0), -x6[30] );
    EXPECT_DOUBLE_EQ( mr6(5,1), -x6[31] );
    EXPECT_DOUBLE_EQ( mr6(5,2), -x6[32] );
    EXPECT_DOUBLE_EQ( mr6(5,3), -x6[33] );
    EXPECT_DOUBLE_EQ( mr6(5,4), -x6[34] );
    EXPECT_DOUBLE_EQ( mr6(5,5), -x6[35] );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanMultiplyByScalar)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> m3;
    mc::MatrixMxN<4,4> m4;
    mc::MatrixMxN<6,6> m6;

    m3.SetFromArray(x3);
    m4.SetFromArray(x4);
    m6.SetFromArray(x6);

    mc::MatrixMxN<3,3> mr3 = m3 * 2.0;
    mc::MatrixMxN<4,4> mr4 = m4 * 2.0;
    mc::MatrixMxN<6,6> mr6 = m6 * 2.0;

    EXPECT_DOUBLE_EQ( mr3(0,0), x3[0] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(0,1), x3[1] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(0,2), x3[2] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(1,0), x3[3] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(1,1), x3[4] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(1,2), x3[5] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(2,0), x3[6] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(2,1), x3[7] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(2,2), x3[8] * 2.0 );

    EXPECT_DOUBLE_EQ( mr4(0,0), x4[0]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,1), x4[1]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,2), x4[2]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,3), x4[3]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,0), x4[4]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,1), x4[5]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,2), x4[6]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,3), x4[7]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,0), x4[8]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,1), x4[9]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,2), x4[10] * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,3), x4[11] * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,0), x4[12] * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,1), x4[13] * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,2), x4[14] * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,3), x4[15] * 2.0 );

    EXPECT_DOUBLE_EQ( mr6(0,0), x6[0]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,1), x6[1]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,2), x6[2]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,3), x6[3]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,4), x6[4]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,5), x6[5]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,0), x6[6]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,1), x6[7]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,2), x6[8]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,3), x6[9]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,4), x6[10] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,5), x6[11] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,0), x6[12] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,1), x6[13] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,2), x6[14] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,3), x6[15] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,4), x6[16] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,5), x6[17] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,0), x6[18] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,1), x6[19] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,2), x6[20] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,3), x6[21] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,4), x6[22] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,5), x6[23] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,0), x6[24] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,1), x6[25] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,2), x6[26] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,3), x6[27] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,4), x6[28] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,5), x6[29] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,0), x6[30] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,1), x6[31] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,2), x6[32] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,3), x6[33] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,4), x6[34] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,5), x6[35] * 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanMultiplyByVector)
{
    mc::MatrixMxN<3,3> m31;
    m31(0,0) =  1.0;
    m31(0,1) =  0.0;
    m31(0,2) =  0.0;
    m31(1,0) =  0.0;
    m31(1,1) =  1.0;
    m31(1,2) =  0.0;
    m31(2,0) =  0.0;
    m31(2,1) =  0.0;
    m31(2,2) =  1.0;

    mc::MatrixMxN<3,3> m32;
    m32(0,0) = -1.0;
    m32(0,1) =  0.0;
    m32(0,2) =  0.0;
    m32(1,0) =  0.0;
    m32(1,1) = -1.0;
    m32(1,2) =  0.0;
    m32(2,0) =  0.0;
    m32(2,1) =  0.0;
    m32(2,2) = -1.0;

    mc::MatrixMxN<3,3> m33;
    m33(0,0) =  0.0;
    m33(0,1) =  1.0;
    m33(0,2) =  0.0;
    m33(1,0) =  1.0;
    m33(1,1) =  0.0;
    m33(1,2) =  0.0;
    m33(2,0) =  0.0;
    m33(2,1) =  0.0;
    m33(2,2) =  1.0;

    mc::MatrixMxN<3,3> m34;
    m34(0,0) =  1.0;
    m34(0,1) =  0.0;
    m34(0,2) =  0.0;
    m34(1,0) =  0.0;
    m34(1,1) =  0.0;
    m34(1,2) = -1.0;
    m34(2,0) =  0.0;
    m34(2,1) = -1.0;
    m34(2,2) =  0.0;

    mc::VectorN<3> v3;
    v3(0) = 1.0;
    v3(1) = 2.0;
    v3(2) = 3.0;

    mc::VectorN<3> v31 = m31 * v3;
    EXPECT_DOUBLE_EQ( v31(0),  1.0 );
    EXPECT_DOUBLE_EQ( v31(1),  2.0 );
    EXPECT_DOUBLE_EQ( v31(2),  3.0 );

    mc::VectorN<3> v32 = m32 * v3;
    EXPECT_DOUBLE_EQ( v32(0), -1.0 );
    EXPECT_DOUBLE_EQ( v32(1), -2.0 );
    EXPECT_DOUBLE_EQ( v32(2), -3.0 );

    mc::VectorN<3> v33 = m33 * v3;
    EXPECT_DOUBLE_EQ( v33(0),  2.0 );
    EXPECT_DOUBLE_EQ( v33(1),  1.0 );
    EXPECT_DOUBLE_EQ( v33(2),  3.0 );

    mc::VectorN<3> v34 = m34 * v3;
    EXPECT_DOUBLE_EQ( v34(0),  1.0 );
    EXPECT_DOUBLE_EQ( v34(1), -3.0 );
    EXPECT_DOUBLE_EQ( v34(2), -2.0 );

    // Following tests uses expected values calculated with GNU Octave
    // tests/math/octave/test_matrix.m

    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };
    mc::MatrixMxN<3,3> m35;
    m35.SetFromArray(x3);

    mc::VectorN<3> v35 = m35 * v3;
    EXPECT_DOUBLE_EQ( v35(0), 14.0 );
    EXPECT_DOUBLE_EQ( v35(1), 32.0 );
    EXPECT_DOUBLE_EQ( v35(2), 50.0 );

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };
    mc::MatrixMxN<4,4> m41;
    m41.SetFromArray(x4);

    mc::VectorN<4> v4;
    v4(0) = 1.0;
    v4(1) = 2.0;
    v4(2) = 3.0;
    v4(3) = 4.0;

    mc::VectorN<4> v41 = m41 * v4;
    EXPECT_DOUBLE_EQ( v41(0),  30.0 );
    EXPECT_DOUBLE_EQ( v41(1),  70.0 );
    EXPECT_DOUBLE_EQ( v41(2), 110.0 );
    EXPECT_DOUBLE_EQ( v41(3), 150.0 );

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };
    mc::MatrixMxN<6,6> m61;
    m61.SetFromArray(x6);

    mc::VectorN<6> v6;
    v6(0) = 1.0;
    v6(1) = 2.0;
    v6(2) = 3.0;
    v6(3) = 4.0;
    v6(4) = 5.0;
    v6(5) = 6.0;

    mc::VectorN<6> v61 = m61 * v6;
    EXPECT_DOUBLE_EQ( v61(0),  91.0 );
    EXPECT_DOUBLE_EQ( v61(1), 217.0 );
    EXPECT_DOUBLE_EQ( v61(2), 343.0 );
    EXPECT_DOUBLE_EQ( v61(3), 469.0 );
    EXPECT_DOUBLE_EQ( v61(4), 595.0 );
    EXPECT_DOUBLE_EQ( v61(5), 721.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanDivideByScalar)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> m3;
    mc::MatrixMxN<4,4> m4;
    mc::MatrixMxN<6,6> m6;

    m3.SetFromArray(x3);
    m4.SetFromArray(x4);
    m6.SetFromArray(x6);

    mc::MatrixMxN<3,3> mr3 = m3 / 2.0;
    mc::MatrixMxN<4,4> mr4 = m4 / 2.0;
    mc::MatrixMxN<6,6> mr6 = m6 / 2.0;

    EXPECT_DOUBLE_EQ( mr3(0,0), x3[0] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(0,1), x3[1] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(0,2), x3[2] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(1,0), x3[3] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(1,1), x3[4] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(1,2), x3[5] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(2,0), x3[6] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(2,1), x3[7] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(2,2), x3[8] / 2.0 );

    EXPECT_DOUBLE_EQ( mr4(0,0), x4[0]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,1), x4[1]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,2), x4[2]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,3), x4[3]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,0), x4[4]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,1), x4[5]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,2), x4[6]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,3), x4[7]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,0), x4[8]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,1), x4[9]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,2), x4[10] / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,3), x4[11] / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,0), x4[12] / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,1), x4[13] / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,2), x4[14] / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,3), x4[15] / 2.0 );

    EXPECT_DOUBLE_EQ( mr6(0,0), x6[0]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,1), x6[1]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,2), x6[2]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,3), x6[3]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,4), x6[4]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,5), x6[5]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,0), x6[6]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,1), x6[7]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,2), x6[8]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,3), x6[9]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,4), x6[10] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,5), x6[11] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,0), x6[12] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,1), x6[13] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,2), x6[14] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,3), x6[15] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,4), x6[16] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,5), x6[17] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,0), x6[18] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,1), x6[19] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,2), x6[20] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,3), x6[21] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,4), x6[22] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,5), x6[23] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,0), x6[24] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,1), x6[25] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,2), x6[26] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,3), x6[27] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,4), x6[28] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,5), x6[29] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,0), x6[30] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,1), x6[31] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,2), x6[32] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,3), x6[33] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,4), x6[34] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,5), x6[35] / 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnaryAdd)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> m3;
    mc::MatrixMxN<4,4> m4;
    mc::MatrixMxN<6,6> m6;

    m3.SetFromArray(x3);
    m4.SetFromArray(x4);
    m6.SetFromArray(x6);

    mc::MatrixMxN<3,3> mr3;
    mc::MatrixMxN<4,4> mr4;
    mc::MatrixMxN<6,6> mr6;

    mr3 += m3;
    mr4 += m4;
    mr6 += m6;

    EXPECT_DOUBLE_EQ( mr3(0,0), x3[0] );
    EXPECT_DOUBLE_EQ( mr3(0,1), x3[1] );
    EXPECT_DOUBLE_EQ( mr3(0,2), x3[2] );
    EXPECT_DOUBLE_EQ( mr3(1,0), x3[3] );
    EXPECT_DOUBLE_EQ( mr3(1,1), x3[4] );
    EXPECT_DOUBLE_EQ( mr3(1,2), x3[5] );
    EXPECT_DOUBLE_EQ( mr3(2,0), x3[6] );
    EXPECT_DOUBLE_EQ( mr3(2,1), x3[7] );
    EXPECT_DOUBLE_EQ( mr3(2,2), x3[8] );

    EXPECT_DOUBLE_EQ( mr4(0,0), x4[0]  );
    EXPECT_DOUBLE_EQ( mr4(0,1), x4[1]  );
    EXPECT_DOUBLE_EQ( mr4(0,2), x4[2]  );
    EXPECT_DOUBLE_EQ( mr4(0,3), x4[3]  );
    EXPECT_DOUBLE_EQ( mr4(1,0), x4[4]  );
    EXPECT_DOUBLE_EQ( mr4(1,1), x4[5]  );
    EXPECT_DOUBLE_EQ( mr4(1,2), x4[6]  );
    EXPECT_DOUBLE_EQ( mr4(1,3), x4[7]  );
    EXPECT_DOUBLE_EQ( mr4(2,0), x4[8]  );
    EXPECT_DOUBLE_EQ( mr4(2,1), x4[9]  );
    EXPECT_DOUBLE_EQ( mr4(2,2), x4[10] );
    EXPECT_DOUBLE_EQ( mr4(2,3), x4[11] );
    EXPECT_DOUBLE_EQ( mr4(3,0), x4[12] );
    EXPECT_DOUBLE_EQ( mr4(3,1), x4[13] );
    EXPECT_DOUBLE_EQ( mr4(3,2), x4[14] );
    EXPECT_DOUBLE_EQ( mr4(3,3), x4[15] );

    EXPECT_DOUBLE_EQ( mr6(0,0), x6[0]  );
    EXPECT_DOUBLE_EQ( mr6(0,1), x6[1]  );
    EXPECT_DOUBLE_EQ( mr6(0,2), x6[2]  );
    EXPECT_DOUBLE_EQ( mr6(0,3), x6[3]  );
    EXPECT_DOUBLE_EQ( mr6(0,4), x6[4]  );
    EXPECT_DOUBLE_EQ( mr6(0,5), x6[5]  );
    EXPECT_DOUBLE_EQ( mr6(1,0), x6[6]  );
    EXPECT_DOUBLE_EQ( mr6(1,1), x6[7]  );
    EXPECT_DOUBLE_EQ( mr6(1,2), x6[8]  );
    EXPECT_DOUBLE_EQ( mr6(1,3), x6[9]  );
    EXPECT_DOUBLE_EQ( mr6(1,4), x6[10] );
    EXPECT_DOUBLE_EQ( mr6(1,5), x6[11] );
    EXPECT_DOUBLE_EQ( mr6(2,0), x6[12] );
    EXPECT_DOUBLE_EQ( mr6(2,1), x6[13] );
    EXPECT_DOUBLE_EQ( mr6(2,2), x6[14] );
    EXPECT_DOUBLE_EQ( mr6(2,3), x6[15] );
    EXPECT_DOUBLE_EQ( mr6(2,4), x6[16] );
    EXPECT_DOUBLE_EQ( mr6(2,5), x6[17] );
    EXPECT_DOUBLE_EQ( mr6(3,0), x6[18] );
    EXPECT_DOUBLE_EQ( mr6(3,1), x6[19] );
    EXPECT_DOUBLE_EQ( mr6(3,2), x6[20] );
    EXPECT_DOUBLE_EQ( mr6(3,3), x6[21] );
    EXPECT_DOUBLE_EQ( mr6(3,4), x6[22] );
    EXPECT_DOUBLE_EQ( mr6(3,5), x6[23] );
    EXPECT_DOUBLE_EQ( mr6(4,0), x6[24] );
    EXPECT_DOUBLE_EQ( mr6(4,1), x6[25] );
    EXPECT_DOUBLE_EQ( mr6(4,2), x6[26] );
    EXPECT_DOUBLE_EQ( mr6(4,3), x6[27] );
    EXPECT_DOUBLE_EQ( mr6(4,4), x6[28] );
    EXPECT_DOUBLE_EQ( mr6(4,5), x6[29] );
    EXPECT_DOUBLE_EQ( mr6(5,0), x6[30] );
    EXPECT_DOUBLE_EQ( mr6(5,1), x6[31] );
    EXPECT_DOUBLE_EQ( mr6(5,2), x6[32] );
    EXPECT_DOUBLE_EQ( mr6(5,3), x6[33] );
    EXPECT_DOUBLE_EQ( mr6(5,4), x6[34] );
    EXPECT_DOUBLE_EQ( mr6(5,5), x6[35] );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnarySubstract)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> m3;
    mc::MatrixMxN<4,4> m4;
    mc::MatrixMxN<6,6> m6;

    m3.SetFromArray(x3);
    m4.SetFromArray(x4);
    m6.SetFromArray(x6);

    mc::MatrixMxN<3,3> mr3;
    mc::MatrixMxN<4,4> mr4;
    mc::MatrixMxN<6,6> mr6;

    mr3 -= m3;
    mr4 -= m4;
    mr6 -= m6;

    EXPECT_DOUBLE_EQ( mr3(0,0), -x3[0] );
    EXPECT_DOUBLE_EQ( mr3(0,1), -x3[1] );
    EXPECT_DOUBLE_EQ( mr3(0,2), -x3[2] );
    EXPECT_DOUBLE_EQ( mr3(1,0), -x3[3] );
    EXPECT_DOUBLE_EQ( mr3(1,1), -x3[4] );
    EXPECT_DOUBLE_EQ( mr3(1,2), -x3[5] );
    EXPECT_DOUBLE_EQ( mr3(2,0), -x3[6] );
    EXPECT_DOUBLE_EQ( mr3(2,1), -x3[7] );
    EXPECT_DOUBLE_EQ( mr3(2,2), -x3[8] );

    EXPECT_DOUBLE_EQ( mr4(0,0), -x4[0]  );
    EXPECT_DOUBLE_EQ( mr4(0,1), -x4[1]  );
    EXPECT_DOUBLE_EQ( mr4(0,2), -x4[2]  );
    EXPECT_DOUBLE_EQ( mr4(0,3), -x4[3]  );
    EXPECT_DOUBLE_EQ( mr4(1,0), -x4[4]  );
    EXPECT_DOUBLE_EQ( mr4(1,1), -x4[5]  );
    EXPECT_DOUBLE_EQ( mr4(1,2), -x4[6]  );
    EXPECT_DOUBLE_EQ( mr4(1,3), -x4[7]  );
    EXPECT_DOUBLE_EQ( mr4(2,0), -x4[8]  );
    EXPECT_DOUBLE_EQ( mr4(2,1), -x4[9]  );
    EXPECT_DOUBLE_EQ( mr4(2,2), -x4[10] );
    EXPECT_DOUBLE_EQ( mr4(2,3), -x4[11] );
    EXPECT_DOUBLE_EQ( mr4(3,0), -x4[12] );
    EXPECT_DOUBLE_EQ( mr4(3,1), -x4[13] );
    EXPECT_DOUBLE_EQ( mr4(3,2), -x4[14] );
    EXPECT_DOUBLE_EQ( mr4(3,3), -x4[15] );

    EXPECT_DOUBLE_EQ( mr6(0,0), -x6[0]  );
    EXPECT_DOUBLE_EQ( mr6(0,1), -x6[1]  );
    EXPECT_DOUBLE_EQ( mr6(0,2), -x6[2]  );
    EXPECT_DOUBLE_EQ( mr6(0,3), -x6[3]  );
    EXPECT_DOUBLE_EQ( mr6(0,4), -x6[4]  );
    EXPECT_DOUBLE_EQ( mr6(0,5), -x6[5]  );
    EXPECT_DOUBLE_EQ( mr6(1,0), -x6[6]  );
    EXPECT_DOUBLE_EQ( mr6(1,1), -x6[7]  );
    EXPECT_DOUBLE_EQ( mr6(1,2), -x6[8]  );
    EXPECT_DOUBLE_EQ( mr6(1,3), -x6[9]  );
    EXPECT_DOUBLE_EQ( mr6(1,4), -x6[10] );
    EXPECT_DOUBLE_EQ( mr6(1,5), -x6[11] );
    EXPECT_DOUBLE_EQ( mr6(2,0), -x6[12] );
    EXPECT_DOUBLE_EQ( mr6(2,1), -x6[13] );
    EXPECT_DOUBLE_EQ( mr6(2,2), -x6[14] );
    EXPECT_DOUBLE_EQ( mr6(2,3), -x6[15] );
    EXPECT_DOUBLE_EQ( mr6(2,4), -x6[16] );
    EXPECT_DOUBLE_EQ( mr6(2,5), -x6[17] );
    EXPECT_DOUBLE_EQ( mr6(3,0), -x6[18] );
    EXPECT_DOUBLE_EQ( mr6(3,1), -x6[19] );
    EXPECT_DOUBLE_EQ( mr6(3,2), -x6[20] );
    EXPECT_DOUBLE_EQ( mr6(3,3), -x6[21] );
    EXPECT_DOUBLE_EQ( mr6(3,4), -x6[22] );
    EXPECT_DOUBLE_EQ( mr6(3,5), -x6[23] );
    EXPECT_DOUBLE_EQ( mr6(4,0), -x6[24] );
    EXPECT_DOUBLE_EQ( mr6(4,1), -x6[25] );
    EXPECT_DOUBLE_EQ( mr6(4,2), -x6[26] );
    EXPECT_DOUBLE_EQ( mr6(4,3), -x6[27] );
    EXPECT_DOUBLE_EQ( mr6(4,4), -x6[28] );
    EXPECT_DOUBLE_EQ( mr6(4,5), -x6[29] );
    EXPECT_DOUBLE_EQ( mr6(5,0), -x6[30] );
    EXPECT_DOUBLE_EQ( mr6(5,1), -x6[31] );
    EXPECT_DOUBLE_EQ( mr6(5,2), -x6[32] );
    EXPECT_DOUBLE_EQ( mr6(5,3), -x6[33] );
    EXPECT_DOUBLE_EQ( mr6(5,4), -x6[34] );
    EXPECT_DOUBLE_EQ( mr6(5,5), -x6[35] );
}


////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnaryMultiplyByScalar)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> mr3;
    mc::MatrixMxN<4,4> mr4;
    mc::MatrixMxN<6,6> mr6;

    mr3.SetFromArray(x3);
    mr4.SetFromArray(x4);
    mr6.SetFromArray(x6);

    mr3 *= 2.0;
    mr4 *= 2.0;
    mr6 *= 2.0;

    EXPECT_DOUBLE_EQ( mr3(0,0), x3[0] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(0,1), x3[1] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(0,2), x3[2] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(1,0), x3[3] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(1,1), x3[4] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(1,2), x3[5] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(2,0), x3[6] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(2,1), x3[7] * 2.0 );
    EXPECT_DOUBLE_EQ( mr3(2,2), x3[8] * 2.0 );

    EXPECT_DOUBLE_EQ( mr4(0,0), x4[0]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,1), x4[1]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,2), x4[2]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,3), x4[3]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,0), x4[4]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,1), x4[5]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,2), x4[6]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,3), x4[7]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,0), x4[8]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,1), x4[9]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,2), x4[10] * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,3), x4[11] * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,0), x4[12] * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,1), x4[13] * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,2), x4[14] * 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,3), x4[15] * 2.0 );

    EXPECT_DOUBLE_EQ( mr6(0,0), x6[0]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,1), x6[1]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,2), x6[2]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,3), x6[3]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,4), x6[4]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,5), x6[5]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,0), x6[6]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,1), x6[7]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,2), x6[8]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,3), x6[9]  * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,4), x6[10] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,5), x6[11] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,0), x6[12] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,1), x6[13] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,2), x6[14] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,3), x6[15] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,4), x6[16] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,5), x6[17] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,0), x6[18] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,1), x6[19] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,2), x6[20] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,3), x6[21] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,4), x6[22] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,5), x6[23] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,0), x6[24] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,1), x6[25] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,2), x6[26] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,3), x6[27] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,4), x6[28] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,5), x6[29] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,0), x6[30] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,1), x6[31] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,2), x6[32] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,3), x6[33] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,4), x6[34] * 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,5), x6[35] * 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnaryDivideByScalar)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> mr3;
    mc::MatrixMxN<4,4> mr4;
    mc::MatrixMxN<6,6> mr6;

    mr3.SetFromArray(x3);
    mr4.SetFromArray(x4);
    mr6.SetFromArray(x6);

    mr3 /= 2.0;
    mr4 /= 2.0;
    mr6 /= 2.0;

    EXPECT_DOUBLE_EQ( mr3(0,0), x3[0] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(0,1), x3[1] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(0,2), x3[2] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(1,0), x3[3] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(1,1), x3[4] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(1,2), x3[5] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(2,0), x3[6] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(2,1), x3[7] / 2.0 );
    EXPECT_DOUBLE_EQ( mr3(2,2), x3[8] / 2.0 );

    EXPECT_DOUBLE_EQ( mr4(0,0), x4[0]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,1), x4[1]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,2), x4[2]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(0,3), x4[3]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,0), x4[4]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,1), x4[5]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,2), x4[6]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(1,3), x4[7]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,0), x4[8]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,1), x4[9]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,2), x4[10] / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(2,3), x4[11] / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,0), x4[12] / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,1), x4[13] / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,2), x4[14] / 2.0 );
    EXPECT_DOUBLE_EQ( mr4(3,3), x4[15] / 2.0 );

    EXPECT_DOUBLE_EQ( mr6(0,0), x6[0]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,1), x6[1]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,2), x6[2]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,3), x6[3]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,4), x6[4]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(0,5), x6[5]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,0), x6[6]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,1), x6[7]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,2), x6[8]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,3), x6[9]  / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,4), x6[10] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(1,5), x6[11] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,0), x6[12] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,1), x6[13] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,2), x6[14] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,3), x6[15] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,4), x6[16] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(2,5), x6[17] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,0), x6[18] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,1), x6[19] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,2), x6[20] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,3), x6[21] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,4), x6[22] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(3,5), x6[23] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,0), x6[24] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,1), x6[25] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,2), x6[26] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,3), x6[27] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,4), x6[28] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(4,5), x6[29] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,0), x6[30] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,1), x6[31] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,2), x6[32] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,3), x6[33] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,4), x6[34] / 2.0 );
    EXPECT_DOUBLE_EQ( mr6(5,5), x6[35] / 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanCompare)
{
    double x3[] { 1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0 };

    double x4[] {  1.0,  2.0,  3.0,  4.0,
                   5.0,  6.0,  7.0,  8.0,
                   9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0 };

    double x6[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                   7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                  19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                  25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                  31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<3,3> m31;
    mc::MatrixMxN<4,4> m41;
    mc::MatrixMxN<6,6> m61;

    mc::MatrixMxN<3,3> m32;
    mc::MatrixMxN<4,4> m42;
    mc::MatrixMxN<6,6> m62;

    m61.SetFromArray(x6);
    m41.SetFromArray(x4);
    m31.SetFromArray(x3);

    m32.SetFromArray(x3);
    m42.SetFromArray(x4);
    m62.SetFromArray(x6);

    mc::MatrixMxN<3,3> m30;
    mc::MatrixMxN<4,4> m40;
    mc::MatrixMxN<6,6> m60;

    EXPECT_TRUE( m31 == m32 );
    EXPECT_TRUE( m41 == m42 );
    EXPECT_TRUE( m61 == m62 );

    EXPECT_FALSE( m31 != m32 );
    EXPECT_FALSE( m41 != m42 );
    EXPECT_FALSE( m61 != m62 );

    EXPECT_FALSE( m31 == m30 );
    EXPECT_FALSE( m41 == m40 );
    EXPECT_FALSE( m61 == m60 );

    EXPECT_TRUE( m31 != m30 );
    EXPECT_TRUE( m41 != m40 );
    EXPECT_TRUE( m61 != m60 );
}
