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

TEST_F(TestMatrixMxN, CanValidate)
{
    mc::MatrixMxN<3,3> m1;

    EXPECT_TRUE( m1.IsValid() );

    mc::MatrixMxN<3,3> m2(m1);

    m2(0,0) = 1.0;
    m2(0,1) = 2.0;
    m2(0,2) = 3.0;
    m2(1,0) = 4.0;
    m2(1,1) = 5.0;
    m2(1,2) = 6.0;
    m2(2,0) = 7.0;
    m2(2,1) = 8.0;
    m2(2,2) = 9.0;

    EXPECT_TRUE( m2.IsValid() );

    mc::MatrixMxN<3,3> m3(m1);

    m3(0,0) = std::numeric_limits<double>::quiet_NaN();
    m3(0,1) = 2.0;
    m3(0,2) = 3.0;
    m3(1,0) = 4.0;
    m3(1,1) = 5.0;
    m3(1,2) = 6.0;
    m3(2,0) = 7.0;
    m3(2,1) = 8.0;
    m3(2,2) = 9.0;

    EXPECT_FALSE( m3.IsValid() );

    mc::MatrixMxN<3,3> m4(m1);

    m4(0,0) = 1.0;
    m4(0,1) = 2.0;
    m4(0,2) = 3.0;
    m4(1,0) = 4.0;
    m4(1,1) = std::numeric_limits<double>::quiet_NaN();
    m4(1,2) = 6.0;
    m4(2,0) = 7.0;
    m4(2,1) = 8.0;
    m4(2,2) = 9.0;

    EXPECT_FALSE( m4.IsValid() );

    mc::MatrixMxN<3,3> m5(m1);

    m5(0,0) = std::numeric_limits<double>::quiet_NaN();
    m5(0,1) = std::numeric_limits<double>::quiet_NaN();
    m5(0,2) = std::numeric_limits<double>::quiet_NaN();
    m5(1,0) = std::numeric_limits<double>::quiet_NaN();
    m5(1,1) = std::numeric_limits<double>::quiet_NaN();
    m5(1,2) = std::numeric_limits<double>::quiet_NaN();
    m5(2,0) = std::numeric_limits<double>::quiet_NaN();
    m5(2,1) = std::numeric_limits<double>::quiet_NaN();
    m5(2,2) = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE( m4.IsValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanGetElement)
{
    mc::MatrixMxN<3,3> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    EXPECT_DOUBLE_EQ( m1.GetElement(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m1.GetElement(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m1.GetElement(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m1.GetElement(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m1.GetElement(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m1.GetElement(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m1.GetElement(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m1.GetElement(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m1.GetElement(2,2), 9.0 );

    double r23 = m1.GetElement(2,3);
    double r32 = m1.GetElement(3,2);

    EXPECT_FALSE( r23 == r23 ); // NaN
    EXPECT_FALSE( r32 == r32 ); // NaN
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanGetElements)
{
    mc::MatrixMxN<3,3> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    double elements[9] = { 0.0 };

    m1.GetElements(elements);

    EXPECT_DOUBLE_EQ( elements[0], 1.0 );
    EXPECT_DOUBLE_EQ( elements[1], 2.0 );
    EXPECT_DOUBLE_EQ( elements[2], 3.0 );
    EXPECT_DOUBLE_EQ( elements[3], 4.0 );
    EXPECT_DOUBLE_EQ( elements[4], 5.0 );
    EXPECT_DOUBLE_EQ( elements[5], 6.0 );
    EXPECT_DOUBLE_EQ( elements[6], 7.0 );
    EXPECT_DOUBLE_EQ( elements[7], 8.0 );
    EXPECT_DOUBLE_EQ( elements[8], 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSetElement)
{
    mc::MatrixMxN<3,3> m1;

    m1.SetElement(0, 0, 1.0);
    m1.SetElement(0, 1, 2.0);
    m1.SetElement(0, 2, 3.0);
    m1.SetElement(1, 0, 4.0);
    m1.SetElement(1, 1, 5.0);
    m1.SetElement(1, 2, 6.0);
    m1.SetElement(2, 0, 7.0);
    m1.SetElement(2, 1, 8.0);
    m1.SetElement(2, 2, 9.0);

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

TEST_F(TestMatrixMxN, CanSetElements)
{
    mc::MatrixMxN<3,3> m1;

    double elements[] = { 1.0, 2.0, 3.0,
                          4.0, 5.0, 6.0,
                          7.0, 8.0, 9.0 };

    m1.SetElements(elements);

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
    mc::MatrixMxN<3,3> m0;

    m0(0,0) = 1.0;
    m0(0,1) = 2.0;
    m0(0,2) = 3.0;
    m0(1,0) = 4.0;
    m0(1,1) = 5.0;
    m0(1,2) = 6.0;
    m0(2,0) = 7.0;
    m0(2,1) = 8.0;
    m0(2,2) = 9.0;

    EXPECT_DOUBLE_EQ( m0(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m0(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m0(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m0(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m0(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m0(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m0(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m0(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m0(2,2), 9.0 );

    mc::MatrixMxN<3,3> m01(m0);

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

    mc::MatrixMxN<3,3> m02(m0);

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

    mc::MatrixMxN<3,3> m12(m0);

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
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanConvertToString)
{
    mc::MatrixMxN<3,3> m0;

    m0(0,0) = 1.0;
    m0(0,1) = 2.0;
    m0(0,2) = 3.0;
    m0(1,0) = 4.0;
    m0(1,1) = 5.0;
    m0(1,2) = 6.0;
    m0(2,0) = 7.0;
    m0(2,1) = 8.0;
    m0(2,2) = 9.0;

    EXPECT_STREQ( m0.ToString().c_str(), "1\t2\t3\t\n4\t5\t6\t\n7\t8\t9" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanAccessItem)
{
    mc::MatrixMxN<3,3> m1;

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

TEST_F(TestMatrixMxN, CanAdd)
{
    mc::MatrixMxN<3,3> m1;
    mc::MatrixMxN<3,3> m2;

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

    mc::MatrixMxN<3,3> m3 = m1 + m2;

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

TEST_F(TestMatrixMxN, CanNegate)
{
    mc::MatrixMxN<3,3> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    mc::MatrixMxN<3,3> m2 = -m1;

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

TEST_F(TestMatrixMxN, CanSubstract)
{
    mc::MatrixMxN<3,3> m1;
    mc::MatrixMxN<3,3> m2;

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

    mc::MatrixMxN<3,3> m3 = m1 - m2;

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

TEST_F(TestMatrixMxN, CanMultiplyByScalar)
{
    mc::MatrixMxN<3,3> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    mc::MatrixMxN<3,3> m2 = m1 * 2.0;

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

TEST_F(TestMatrixMxN, CanMultiplyByVector)
{
    mc::MatrixMxN<3,3> m1;
    m1(0,0) =  1.0;
    m1(0,1) =  0.0;
    m1(0,2) =  0.0;
    m1(1,0) =  0.0;
    m1(1,1) =  1.0;
    m1(1,2) =  0.0;
    m1(2,0) =  0.0;
    m1(2,1) =  0.0;
    m1(2,2) =  1.0;

    mc::MatrixMxN<3,3> m2;
    m2(0,0) = -1.0;
    m2(0,1) =  0.0;
    m2(0,2) =  0.0;
    m2(1,0) =  0.0;
    m2(1,1) = -1.0;
    m2(1,2) =  0.0;
    m2(2,0) =  0.0;
    m2(2,1) =  0.0;
    m2(2,2) = -1.0;

    mc::MatrixMxN<3,3> m3;
    m3(0,0) =  0.0;
    m3(0,1) =  1.0;
    m3(0,2) =  0.0;
    m3(1,0) =  1.0;
    m3(1,1) =  0.0;
    m3(1,2) =  0.0;
    m3(2,0) =  0.0;
    m3(2,1) =  0.0;
    m3(2,2) =  1.0;

    mc::MatrixMxN<3,3> m4;
    m4(0,0) =  1.0;
    m4(0,1) =  0.0;
    m4(0,2) =  0.0;
    m4(1,0) =  0.0;
    m4(1,1) =  0.0;
    m4(1,2) = -1.0;
    m4(2,0) =  0.0;
    m4(2,1) = -1.0;
    m4(2,2) =  0.0;

    mc::VectorN<3> v;
    v( 0 ) = 1.0;
    v( 1 ) = 2.0;
    v( 2 ) = 3.0;

    mc::VectorN<3> v1 = m1 * v;
    EXPECT_DOUBLE_EQ( v1(0),  1.0 );
    EXPECT_DOUBLE_EQ( v1(1),  2.0 );
    EXPECT_DOUBLE_EQ( v1(2),  3.0 );

    mc::VectorN<3> v2 = m2 * v;
    EXPECT_DOUBLE_EQ( v2(0), -1.0 );
    EXPECT_DOUBLE_EQ( v2(1), -2.0 );
    EXPECT_DOUBLE_EQ( v2(2), -3.0 );

    mc::VectorN<3> v3 = m3 * v;
    EXPECT_DOUBLE_EQ( v3(0),  2.0 );
    EXPECT_DOUBLE_EQ( v3(1),  1.0 );
    EXPECT_DOUBLE_EQ( v3(2),  3.0 );

    mc::VectorN<3> v4 = m4 * v;
    EXPECT_DOUBLE_EQ( v4(0),  1.0 );
    EXPECT_DOUBLE_EQ( v4(1), -3.0 );
    EXPECT_DOUBLE_EQ( v4(2), -2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanDivideByScalar)
{
    mc::MatrixMxN<3,3> m1;

    m1(0,0) =  2.0;
    m1(0,1) =  4.0;
    m1(0,2) =  6.0;
    m1(1,0) =  8.0;
    m1(1,1) = 10.0;
    m1(1,2) = 12.0;
    m1(2,0) = 14.0;
    m1(2,1) = 16.0;
    m1(2,2) = 18.0;

    mc::MatrixMxN<3,3> m2 = m1 / 2.0;

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

TEST_F(TestMatrixMxN, CanUnaryAdd)
{
    mc::MatrixMxN<3,3> m1;
    mc::MatrixMxN<3,3> m2;

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

TEST_F(TestMatrixMxN, CanUnarySubstract)
{
    mc::MatrixMxN<3,3> m1;
    mc::MatrixMxN<3,3> m2;

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

TEST_F(TestMatrixMxN, CanUnaryMultiplyByScalar)
{
    mc::MatrixMxN<3,3> m1;

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

TEST_F(TestMatrixMxN, CanUnaryDivideByScalar)
{
    mc::MatrixMxN<3,3> m1;

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

TEST_F(TestMatrixMxN, CanCompare)
{
    mc::MatrixMxN<3,3> m1;
    mc::MatrixMxN<3,3> m2;

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
