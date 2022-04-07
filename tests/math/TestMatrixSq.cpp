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
    mc::MatrixSq<3> *m = nullptr;
    EXPECT_NO_THROW( m = new mc::MatrixSq<3>() );
    delete m;
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
    mc::MatrixSq<3> m1;

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

TEST_F(TestMatrixSq, CanInstantiateAndCopy)
{
    mc::MatrixSq<3> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;
    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;
    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    mc::MatrixSq<3> m2( m1 );

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

TEST_F(TestMatrixSq, CanInstantiateAndSetDataFromArray)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixSq<3> m1( items1 );

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
