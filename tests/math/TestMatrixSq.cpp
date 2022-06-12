#include <gtest/gtest.h>

#include <mcutils/math/MatrixSq.h>

////////////////////////////////////////////////////////////////////////////////

class TestMatrixSq : public ::testing::Test
{
protected:
    TestMatrixSq() {}
    virtual ~TestMatrixSq() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanConstruct)
{
    mc::MatrixSq<3> *m3 = nullptr;
    EXPECT_NO_THROW( m3 = new mc::MatrixSq<3>() );
    delete m3;

    mc::MatrixSq<4> *m4 = nullptr;
    EXPECT_NO_THROW( m4 = new mc::MatrixSq<4>() );
    delete m4;

    mc::MatrixSq<6> *m6 = nullptr;
    EXPECT_NO_THROW( m6 = new mc::MatrixSq<6>() );
    delete m6;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanDestruct)
{
    mc::MatrixSq<3> *m3 = new mc::MatrixSq<3>();
    EXPECT_NO_THROW( delete m3 );

    mc::MatrixSq<4> *m4 = new mc::MatrixSq<4>();
    EXPECT_NO_THROW( delete m4 );

    mc::MatrixSq<6> *m6 = new mc::MatrixSq<6>();
    EXPECT_NO_THROW( delete m6 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanInstantiate)
{
    mc::MatrixSq<3> m3;
    mc::MatrixSq<4> m4;
    mc::MatrixSq<6> m6;

    EXPECT_DOUBLE_EQ( m3(0,0), 0.0 );
    EXPECT_DOUBLE_EQ( m3(0,1), 0.0 );
    EXPECT_DOUBLE_EQ( m3(0,2), 0.0 );
    EXPECT_DOUBLE_EQ( m3(1,0), 0.0 );
    EXPECT_DOUBLE_EQ( m3(1,1), 0.0 );
    EXPECT_DOUBLE_EQ( m3(1,2), 0.0 );
    EXPECT_DOUBLE_EQ( m3(2,0), 0.0 );
    EXPECT_DOUBLE_EQ( m3(2,1), 0.0 );
    EXPECT_DOUBLE_EQ( m3(2,2), 0.0 );

    EXPECT_DOUBLE_EQ( m4(0,0), 0.0 );
    EXPECT_DOUBLE_EQ( m4(0,1), 0.0 );
    EXPECT_DOUBLE_EQ( m4(0,2), 0.0 );
    EXPECT_DOUBLE_EQ( m4(0,3), 0.0 );
    EXPECT_DOUBLE_EQ( m4(1,0), 0.0 );
    EXPECT_DOUBLE_EQ( m4(1,1), 0.0 );
    EXPECT_DOUBLE_EQ( m4(1,2), 0.0 );
    EXPECT_DOUBLE_EQ( m4(1,3), 0.0 );
    EXPECT_DOUBLE_EQ( m4(2,0), 0.0 );
    EXPECT_DOUBLE_EQ( m4(2,1), 0.0 );
    EXPECT_DOUBLE_EQ( m4(2,2), 0.0 );
    EXPECT_DOUBLE_EQ( m4(2,3), 0.0 );
    EXPECT_DOUBLE_EQ( m4(3,0), 0.0 );
    EXPECT_DOUBLE_EQ( m4(3,1), 0.0 );
    EXPECT_DOUBLE_EQ( m4(3,2), 0.0 );
    EXPECT_DOUBLE_EQ( m4(3,3), 0.0 );

    EXPECT_DOUBLE_EQ( m6(0,0), 0.0 );
    EXPECT_DOUBLE_EQ( m6(0,1), 0.0 );
    EXPECT_DOUBLE_EQ( m6(0,2), 0.0 );
    EXPECT_DOUBLE_EQ( m6(0,3), 0.0 );
    EXPECT_DOUBLE_EQ( m6(0,4), 0.0 );
    EXPECT_DOUBLE_EQ( m6(0,5), 0.0 );
    EXPECT_DOUBLE_EQ( m6(1,0), 0.0 );
    EXPECT_DOUBLE_EQ( m6(1,1), 0.0 );
    EXPECT_DOUBLE_EQ( m6(1,2), 0.0 );
    EXPECT_DOUBLE_EQ( m6(1,3), 0.0 );
    EXPECT_DOUBLE_EQ( m6(1,4), 0.0 );
    EXPECT_DOUBLE_EQ( m6(1,5), 0.0 );
    EXPECT_DOUBLE_EQ( m6(2,0), 0.0 );
    EXPECT_DOUBLE_EQ( m6(2,1), 0.0 );
    EXPECT_DOUBLE_EQ( m6(2,2), 0.0 );
    EXPECT_DOUBLE_EQ( m6(2,3), 0.0 );
    EXPECT_DOUBLE_EQ( m6(2,4), 0.0 );
    EXPECT_DOUBLE_EQ( m6(2,5), 0.0 );
    EXPECT_DOUBLE_EQ( m6(3,0), 0.0 );
    EXPECT_DOUBLE_EQ( m6(3,1), 0.0 );
    EXPECT_DOUBLE_EQ( m6(3,2), 0.0 );
    EXPECT_DOUBLE_EQ( m6(3,3), 0.0 );
    EXPECT_DOUBLE_EQ( m6(3,4), 0.0 );
    EXPECT_DOUBLE_EQ( m6(3,5), 0.0 );
    EXPECT_DOUBLE_EQ( m6(4,0), 0.0 );
    EXPECT_DOUBLE_EQ( m6(4,1), 0.0 );
    EXPECT_DOUBLE_EQ( m6(4,2), 0.0 );
    EXPECT_DOUBLE_EQ( m6(4,3), 0.0 );
    EXPECT_DOUBLE_EQ( m6(4,4), 0.0 );
    EXPECT_DOUBLE_EQ( m6(4,5), 0.0 );
    EXPECT_DOUBLE_EQ( m6(5,0), 0.0 );
    EXPECT_DOUBLE_EQ( m6(5,1), 0.0 );
    EXPECT_DOUBLE_EQ( m6(5,2), 0.0 );
    EXPECT_DOUBLE_EQ( m6(5,3), 0.0 );
    EXPECT_DOUBLE_EQ( m6(5,4), 0.0 );
    EXPECT_DOUBLE_EQ( m6(5,5), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanInstantiateAndCopy)
{
    mc::MatrixSq<3> m31;
    mc::MatrixSq<4> m41;
    mc::MatrixSq<6> m61;

    m31(0,0) = 1.0;
    m31(0,1) = 2.0;
    m31(0,2) = 3.0;
    m31(1,0) = 4.0;
    m31(1,1) = 5.0;
    m31(1,2) = 6.0;
    m31(2,0) = 7.0;
    m31(2,1) = 8.0;
    m31(2,2) = 9.0;

    mc::MatrixSq<3> m32( m31 );

    EXPECT_DOUBLE_EQ( m32(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m32(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m32(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m32(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m32(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m32(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m32(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m32(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m32(2,2), 9.0 );

    m41(0,0) =  1.0;
    m41(0,1) =  2.0;
    m41(0,2) =  3.0;
    m41(0,3) =  4.0;
    m41(1,0) =  5.0;
    m41(1,1) =  6.0;
    m41(1,2) =  7.0;
    m41(1,3) =  8.0;
    m41(2,0) = 11.0;
    m41(2,1) = 12.0;
    m41(2,2) = 13.0;
    m41(2,3) = 14.0;
    m41(3,0) = 15.0;
    m41(3,1) = 16.0;
    m41(3,2) = 17.0;
    m41(3,3) = 18.0;

    mc::MatrixSq<4> m42( m41 );

    EXPECT_DOUBLE_EQ( m42(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( m42(0,1),  2.0 );
    EXPECT_DOUBLE_EQ( m42(0,2),  3.0 );
    EXPECT_DOUBLE_EQ( m42(0,3),  4.0 );
    EXPECT_DOUBLE_EQ( m42(1,0),  5.0 );
    EXPECT_DOUBLE_EQ( m42(1,1),  6.0 );
    EXPECT_DOUBLE_EQ( m42(1,2),  7.0 );
    EXPECT_DOUBLE_EQ( m42(1,3),  8.0 );
    EXPECT_DOUBLE_EQ( m42(2,0), 11.0 );
    EXPECT_DOUBLE_EQ( m42(2,1), 12.0 );
    EXPECT_DOUBLE_EQ( m42(2,2), 13.0 );
    EXPECT_DOUBLE_EQ( m42(2,3), 14.0 );
    EXPECT_DOUBLE_EQ( m42(3,0), 15.0 );
    EXPECT_DOUBLE_EQ( m42(3,1), 16.0 );
    EXPECT_DOUBLE_EQ( m42(3,2), 17.0 );
    EXPECT_DOUBLE_EQ( m42(3,3), 18.0 );

    m61(0,0) =  1.0;
    m61(0,1) =  2.0;
    m61(0,2) =  3.0;
    m61(0,3) =  4.0;
    m61(0,4) =  5.0;
    m61(0,5) =  6.0;
    m61(1,0) = 11.0;
    m61(1,1) = 12.0;
    m61(1,2) = 13.0;
    m61(1,3) = 14.0;
    m61(1,4) = 15.0;
    m61(1,5) = 16.0;
    m61(2,0) = 21.0;
    m61(2,1) = 22.0;
    m61(2,2) = 23.0;
    m61(2,3) = 24.0;
    m61(2,4) = 25.0;
    m61(2,5) = 26.0;
    m61(3,0) = 31.0;
    m61(3,1) = 32.0;
    m61(3,2) = 33.0;
    m61(3,3) = 34.0;
    m61(3,4) = 35.0;
    m61(3,5) = 36.0;
    m61(4,0) = 41.0;
    m61(4,1) = 42.0;
    m61(4,2) = 43.0;
    m61(4,3) = 44.0;
    m61(4,4) = 45.0;
    m61(4,5) = 46.0;
    m61(5,0) = 51.0;
    m61(5,1) = 52.0;
    m61(5,2) = 53.0;
    m61(5,3) = 54.0;
    m61(5,4) = 55.0;
    m61(5,5) = 56.0;

    mc::MatrixSq<6> m62( m61 );

    EXPECT_DOUBLE_EQ( m62(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( m62(0,1),  2.0 );
    EXPECT_DOUBLE_EQ( m62(0,2),  3.0 );
    EXPECT_DOUBLE_EQ( m62(0,3),  4.0 );
    EXPECT_DOUBLE_EQ( m62(0,4),  5.0 );
    EXPECT_DOUBLE_EQ( m62(0,5),  6.0 );
    EXPECT_DOUBLE_EQ( m62(1,0), 11.0 );
    EXPECT_DOUBLE_EQ( m62(1,1), 12.0 );
    EXPECT_DOUBLE_EQ( m62(1,2), 13.0 );
    EXPECT_DOUBLE_EQ( m62(1,3), 14.0 );
    EXPECT_DOUBLE_EQ( m62(1,4), 15.0 );
    EXPECT_DOUBLE_EQ( m62(1,5), 16.0 );
    EXPECT_DOUBLE_EQ( m62(2,0), 21.0 );
    EXPECT_DOUBLE_EQ( m62(2,1), 22.0 );
    EXPECT_DOUBLE_EQ( m62(2,2), 23.0 );
    EXPECT_DOUBLE_EQ( m62(2,3), 24.0 );
    EXPECT_DOUBLE_EQ( m62(2,4), 25.0 );
    EXPECT_DOUBLE_EQ( m62(2,5), 26.0 );
    EXPECT_DOUBLE_EQ( m62(3,0), 31.0 );
    EXPECT_DOUBLE_EQ( m62(3,1), 32.0 );
    EXPECT_DOUBLE_EQ( m62(3,2), 33.0 );
    EXPECT_DOUBLE_EQ( m62(3,3), 34.0 );
    EXPECT_DOUBLE_EQ( m62(3,4), 35.0 );
    EXPECT_DOUBLE_EQ( m62(3,5), 36.0 );
    EXPECT_DOUBLE_EQ( m62(4,0), 41.0 );
    EXPECT_DOUBLE_EQ( m62(4,1), 42.0 );
    EXPECT_DOUBLE_EQ( m62(4,2), 43.0 );
    EXPECT_DOUBLE_EQ( m62(4,3), 44.0 );
    EXPECT_DOUBLE_EQ( m62(4,4), 45.0 );
    EXPECT_DOUBLE_EQ( m62(4,5), 46.0 );
    EXPECT_DOUBLE_EQ( m62(5,0), 51.0 );
    EXPECT_DOUBLE_EQ( m62(5,1), 52.0 );
    EXPECT_DOUBLE_EQ( m62(5,2), 53.0 );
    EXPECT_DOUBLE_EQ( m62(5,3), 54.0 );
    EXPECT_DOUBLE_EQ( m62(5,4), 55.0 );
    EXPECT_DOUBLE_EQ( m62(5,5), 56.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanInstantiateAndSetDataFromArray)
{
    double items3[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m3( items3 );

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

TEST_F(TestMatrixSq, CanTranspose)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    m1.transpose();

    EXPECT_DOUBLE_EQ( m1(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m1(0,1), 4.0 );
    EXPECT_DOUBLE_EQ( m1(0,2), 7.0 );
    EXPECT_DOUBLE_EQ( m1(1,0), 2.0 );
    EXPECT_DOUBLE_EQ( m1(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m1(1,2), 8.0 );
    EXPECT_DOUBLE_EQ( m1(2,0), 3.0 );
    EXPECT_DOUBLE_EQ( m1(2,1), 6.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanGetTransposed)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    mc::MatrixSq<3> mt = m1.getTransposed();

    EXPECT_DOUBLE_EQ( m1(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m1(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m1(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m1(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m1(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m1(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m1(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m1(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 9.0 );

    EXPECT_DOUBLE_EQ( mt(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( mt(0,1), 4.0 );
    EXPECT_DOUBLE_EQ( mt(0,2), 7.0 );
    EXPECT_DOUBLE_EQ( mt(1,0), 2.0 );
    EXPECT_DOUBLE_EQ( mt(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( mt(1,2), 8.0 );
    EXPECT_DOUBLE_EQ( mt(2,0), 3.0 );
    EXPECT_DOUBLE_EQ( mt(2,1), 6.0 );
    EXPECT_DOUBLE_EQ( mt(2,2), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanAssign)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    mc::MatrixSq<3> m0;
    m0 = m1;

    EXPECT_DOUBLE_EQ( m0(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m0(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m0(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m0(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m0(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m0(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m0(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m0(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m0(2,2), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanAdd)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    double items2[] { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
    mc::MatrixSq<3> m2( items2 );

    mc::MatrixSq<3> m0 = m1 + m2;

    EXPECT_DOUBLE_EQ( m0(0,0),  2.0 );
    EXPECT_DOUBLE_EQ( m0(0,1),  3.0 );
    EXPECT_DOUBLE_EQ( m0(0,2),  4.0 );
    EXPECT_DOUBLE_EQ( m0(1,0),  5.0 );
    EXPECT_DOUBLE_EQ( m0(1,1),  6.0 );
    EXPECT_DOUBLE_EQ( m0(1,2),  7.0 );
    EXPECT_DOUBLE_EQ( m0(2,0),  8.0 );
    EXPECT_DOUBLE_EQ( m0(2,1),  9.0 );
    EXPECT_DOUBLE_EQ( m0(2,2), 10.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanNegate)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    mc::MatrixSq<3> m0 = -m1;

    EXPECT_DOUBLE_EQ( m0(0,0), -1.0 );
    EXPECT_DOUBLE_EQ( m0(0,1), -2.0 );
    EXPECT_DOUBLE_EQ( m0(0,2), -3.0 );
    EXPECT_DOUBLE_EQ( m0(1,0), -4.0 );
    EXPECT_DOUBLE_EQ( m0(1,1), -5.0 );
    EXPECT_DOUBLE_EQ( m0(1,2), -6.0 );
    EXPECT_DOUBLE_EQ( m0(2,0), -7.0 );
    EXPECT_DOUBLE_EQ( m0(2,1), -8.0 );
    EXPECT_DOUBLE_EQ( m0(2,2), -9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanSubstract)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    double items2[] { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
    mc::MatrixSq<3> m2( items2 );

    mc::MatrixSq<3> m0 = m1 - m2;

    EXPECT_DOUBLE_EQ( m0(0,0), 0.0 );
    EXPECT_DOUBLE_EQ( m0(0,1), 1.0 );
    EXPECT_DOUBLE_EQ( m0(0,2), 2.0 );
    EXPECT_DOUBLE_EQ( m0(1,0), 3.0 );
    EXPECT_DOUBLE_EQ( m0(1,1), 4.0 );
    EXPECT_DOUBLE_EQ( m0(1,2), 5.0 );
    EXPECT_DOUBLE_EQ( m0(2,0), 6.0 );
    EXPECT_DOUBLE_EQ( m0(2,1), 7.0 );
    EXPECT_DOUBLE_EQ( m0(2,2), 8.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanMultiplyByScalar)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    mc::MatrixSq<3> m0 = m1 * 0.5;

    EXPECT_DOUBLE_EQ( m0(0,0), 0.5 );
    EXPECT_DOUBLE_EQ( m0(0,1), 1.0 );
    EXPECT_DOUBLE_EQ( m0(0,2), 1.5 );
    EXPECT_DOUBLE_EQ( m0(1,0), 2.0 );
    EXPECT_DOUBLE_EQ( m0(1,1), 2.5 );
    EXPECT_DOUBLE_EQ( m0(1,2), 3.0 );
    EXPECT_DOUBLE_EQ( m0(2,0), 3.5 );
    EXPECT_DOUBLE_EQ( m0(2,1), 4.0 );
    EXPECT_DOUBLE_EQ( m0(2,2), 4.5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanMultiplyByMatrix)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    double items2[] { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    mc::MatrixSq<3> m2( items2 );

    mc::MatrixSq<3> m0 = m1 * m2;

    EXPECT_NEAR( m0(0,0),  33.0, 1.0e-9 );
    EXPECT_NEAR( m0(0,1),  39.6, 1.0e-9 );
    EXPECT_NEAR( m0(0,2),  46.2, 1.0e-9 );
    EXPECT_NEAR( m0(1,0),  72.6, 1.0e-9 );
    EXPECT_NEAR( m0(1,1),  89.1, 1.0e-9 );
    EXPECT_NEAR( m0(1,2), 105.6, 1.0e-9 );
    EXPECT_NEAR( m0(2,0), 112.2, 1.0e-9 );
    EXPECT_NEAR( m0(2,1), 138.6, 1.0e-9 );
    EXPECT_NEAR( m0(2,2), 165.0, 1.0e-9 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanDivideByScalar)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    mc::MatrixSq<3> m0 = m1 / 2.0;

    EXPECT_DOUBLE_EQ( m0(0,0), 0.5 );
    EXPECT_DOUBLE_EQ( m0(0,1), 1.0 );
    EXPECT_DOUBLE_EQ( m0(0,2), 1.5 );
    EXPECT_DOUBLE_EQ( m0(1,0), 2.0 );
    EXPECT_DOUBLE_EQ( m0(1,1), 2.5 );
    EXPECT_DOUBLE_EQ( m0(1,2), 3.0 );
    EXPECT_DOUBLE_EQ( m0(2,0), 3.5 );
    EXPECT_DOUBLE_EQ( m0(2,1), 4.0 );
    EXPECT_DOUBLE_EQ( m0(2,2), 4.5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanUnaryAdd)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    double items2[] { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
    mc::MatrixSq<3> m2( items2 );

    m1 += m2;

    EXPECT_DOUBLE_EQ( m1(0,0),  2.0 );
    EXPECT_DOUBLE_EQ( m1(0,1),  3.0 );
    EXPECT_DOUBLE_EQ( m1(0,2),  4.0 );
    EXPECT_DOUBLE_EQ( m1(1,0),  5.0 );
    EXPECT_DOUBLE_EQ( m1(1,1),  6.0 );
    EXPECT_DOUBLE_EQ( m1(1,2),  7.0 );
    EXPECT_DOUBLE_EQ( m1(2,0),  8.0 );
    EXPECT_DOUBLE_EQ( m1(2,1),  9.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 10.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanUnarySubstract)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    double items2[] { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
    mc::MatrixSq<3> m2( items2 );

    m1 -= m2;

    EXPECT_DOUBLE_EQ( m1(0,0), 0.0 );
    EXPECT_DOUBLE_EQ( m1(0,1), 1.0 );
    EXPECT_DOUBLE_EQ( m1(0,2), 2.0 );
    EXPECT_DOUBLE_EQ( m1(1,0), 3.0 );
    EXPECT_DOUBLE_EQ( m1(1,1), 4.0 );
    EXPECT_DOUBLE_EQ( m1(1,2), 5.0 );
    EXPECT_DOUBLE_EQ( m1(2,0), 6.0 );
    EXPECT_DOUBLE_EQ( m1(2,1), 7.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 8.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanUnaryMultiplyByScalar)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    m1 *= 0.5;

    EXPECT_DOUBLE_EQ( m1(0,0), 0.5 );
    EXPECT_DOUBLE_EQ( m1(0,1), 1.0 );
    EXPECT_DOUBLE_EQ( m1(0,2), 1.5 );
    EXPECT_DOUBLE_EQ( m1(1,0), 2.0 );
    EXPECT_DOUBLE_EQ( m1(1,1), 2.5 );
    EXPECT_DOUBLE_EQ( m1(1,2), 3.0 );
    EXPECT_DOUBLE_EQ( m1(2,0), 3.5 );
    EXPECT_DOUBLE_EQ( m1(2,1), 4.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 4.5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixSq, CanUnaryDivideByScalar)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

    m1 /= 2.0;

    EXPECT_DOUBLE_EQ( m1(0,0), 0.5 );
    EXPECT_DOUBLE_EQ( m1(0,1), 1.0 );
    EXPECT_DOUBLE_EQ( m1(0,2), 1.5 );
    EXPECT_DOUBLE_EQ( m1(1,0), 2.0 );
    EXPECT_DOUBLE_EQ( m1(1,1), 2.5 );
    EXPECT_DOUBLE_EQ( m1(1,2), 3.0 );
    EXPECT_DOUBLE_EQ( m1(2,0), 3.5 );
    EXPECT_DOUBLE_EQ( m1(2,1), 4.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 4.5 );
}
