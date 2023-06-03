#include <gtest/gtest.h>

#include <mcutils/math/MatrixNxN.h>

////////////////////////////////////////////////////////////////////////////////

class TestMatrixNxN : public ::testing::Test
{
protected:
    TestMatrixNxN() {}
    virtual ~TestMatrixNxN() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanConstruct)
{
    mc::MatrixNxN<3> *m3 = nullptr;
    EXPECT_NO_THROW( m3 = new mc::MatrixNxN<3>() );
    delete m3;

    mc::MatrixNxN<4> *m4 = nullptr;
    EXPECT_NO_THROW( m4 = new mc::MatrixNxN<4>() );
    delete m4;

    mc::MatrixNxN<6> *m6 = nullptr;
    EXPECT_NO_THROW( m6 = new mc::MatrixNxN<6>() );
    delete m6;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanDestruct)
{
    mc::MatrixNxN<3> *m3 = new mc::MatrixNxN<3>();
    EXPECT_NO_THROW( delete m3 );

    mc::MatrixNxN<4> *m4 = new mc::MatrixNxN<4>();
    EXPECT_NO_THROW( delete m4 );

    mc::MatrixNxN<6> *m6 = new mc::MatrixNxN<6>();
    EXPECT_NO_THROW( delete m6 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanInstantiate)
{
    mc::MatrixNxN<3> m3;
    mc::MatrixNxN<4> m4;
    mc::MatrixNxN<6> m6;

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

TEST_F(TestMatrixNxN, CanInstantiateAndCopy)
{
    mc::MatrixNxN<3> m31;
    mc::MatrixNxN<4> m41;
    mc::MatrixNxN<6> m61;

    m31(0,0) = 1.0;
    m31(0,1) = 2.0;
    m31(0,2) = 3.0;
    m31(1,0) = 4.0;
    m31(1,1) = 5.0;
    m31(1,2) = 6.0;
    m31(2,0) = 7.0;
    m31(2,1) = 8.0;
    m31(2,2) = 9.0;

    mc::MatrixNxN<3> m32( m31 );

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

    mc::MatrixNxN<4> m42( m41 );

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

    mc::MatrixNxN<6> m62( m61 );

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

TEST_F(TestMatrixNxN, CanTranspose)
{
    double items1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixNxN<3> m1;
    m1.setItems( items1 );

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

TEST_F(TestMatrixNxN, CanGetTransposed)
{
    double items3[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixNxN<3> m3;
    m3.setItems( items3 );

    mc::MatrixNxN<3> mt3 = m3.getTransposed();

    EXPECT_DOUBLE_EQ( m3(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( m3(0,1), 2.0 );
    EXPECT_DOUBLE_EQ( m3(0,2), 3.0 );
    EXPECT_DOUBLE_EQ( m3(1,0), 4.0 );
    EXPECT_DOUBLE_EQ( m3(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( m3(1,2), 6.0 );
    EXPECT_DOUBLE_EQ( m3(2,0), 7.0 );
    EXPECT_DOUBLE_EQ( m3(2,1), 8.0 );
    EXPECT_DOUBLE_EQ( m3(2,2), 9.0 );

    EXPECT_DOUBLE_EQ( mt3(0,0), 1.0 );
    EXPECT_DOUBLE_EQ( mt3(0,1), 4.0 );
    EXPECT_DOUBLE_EQ( mt3(0,2), 7.0 );
    EXPECT_DOUBLE_EQ( mt3(1,0), 2.0 );
    EXPECT_DOUBLE_EQ( mt3(1,1), 5.0 );
    EXPECT_DOUBLE_EQ( mt3(1,2), 8.0 );
    EXPECT_DOUBLE_EQ( mt3(2,0), 3.0 );
    EXPECT_DOUBLE_EQ( mt3(2,1), 6.0 );
    EXPECT_DOUBLE_EQ( mt3(2,2), 9.0 );

    double x4[] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };

    mc::MatrixNxN<4> m4;
    m4.setItems( x4 );

    mc::MatrixNxN<4> mt4 = m4.getTransposed();

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

    EXPECT_DOUBLE_EQ( mt4(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( mt4(0,1),  5.0 );
    EXPECT_DOUBLE_EQ( mt4(0,2),  9.0 );
    EXPECT_DOUBLE_EQ( mt4(0,3), 13.0 );
    EXPECT_DOUBLE_EQ( mt4(1,0),  2.0 );
    EXPECT_DOUBLE_EQ( mt4(1,1),  6.0 );
    EXPECT_DOUBLE_EQ( mt4(1,2), 10.0 );
    EXPECT_DOUBLE_EQ( mt4(1,3), 14.0 );
    EXPECT_DOUBLE_EQ( mt4(2,0),  3.0 );
    EXPECT_DOUBLE_EQ( mt4(2,1),  7.0 );
    EXPECT_DOUBLE_EQ( mt4(2,2), 11.0 );
    EXPECT_DOUBLE_EQ( mt4(2,3), 15.0 );
    EXPECT_DOUBLE_EQ( mt4(3,0),  4.0 );
    EXPECT_DOUBLE_EQ( mt4(3,1),  8.0 );
    EXPECT_DOUBLE_EQ( mt4(3,2), 12.0 );
    EXPECT_DOUBLE_EQ( mt4(3,3), 16.0 );

    double x6[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::MatrixNxN<6> m6;
    m6.setItems( x6 );

    mc::MatrixNxN<6> mt6 = m6.getTransposed();

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

    EXPECT_DOUBLE_EQ( mt6(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( mt6(0,1),  7.0 );
    EXPECT_DOUBLE_EQ( mt6(0,2), 13.0 );
    EXPECT_DOUBLE_EQ( mt6(0,3), 19.0 );
    EXPECT_DOUBLE_EQ( mt6(0,4), 25.0 );
    EXPECT_DOUBLE_EQ( mt6(0,5), 31.0 );
    EXPECT_DOUBLE_EQ( mt6(1,0),  2.0 );
    EXPECT_DOUBLE_EQ( mt6(1,1),  8.0 );
    EXPECT_DOUBLE_EQ( mt6(1,2), 14.0 );
    EXPECT_DOUBLE_EQ( mt6(1,3), 20.0 );
    EXPECT_DOUBLE_EQ( mt6(1,4), 26.0 );
    EXPECT_DOUBLE_EQ( mt6(1,5), 32.0 );
    EXPECT_DOUBLE_EQ( mt6(2,0),  3.0 );
    EXPECT_DOUBLE_EQ( mt6(2,1),  9.0 );
    EXPECT_DOUBLE_EQ( mt6(2,2), 15.0 );
    EXPECT_DOUBLE_EQ( mt6(2,3), 21.0 );
    EXPECT_DOUBLE_EQ( mt6(2,4), 27.0 );
    EXPECT_DOUBLE_EQ( mt6(2,5), 33.0 );
    EXPECT_DOUBLE_EQ( mt6(3,0),  4.0 );
    EXPECT_DOUBLE_EQ( mt6(3,1), 10.0 );
    EXPECT_DOUBLE_EQ( mt6(3,2), 16.0 );
    EXPECT_DOUBLE_EQ( mt6(3,3), 22.0 );
    EXPECT_DOUBLE_EQ( mt6(3,4), 28.0 );
    EXPECT_DOUBLE_EQ( mt6(3,5), 34.0 );
    EXPECT_DOUBLE_EQ( mt6(4,0),  5.0 );
    EXPECT_DOUBLE_EQ( mt6(4,1), 11.0 );
    EXPECT_DOUBLE_EQ( mt6(4,2), 17.0 );
    EXPECT_DOUBLE_EQ( mt6(4,3), 23.0 );
    EXPECT_DOUBLE_EQ( mt6(4,4), 29.0 );
    EXPECT_DOUBLE_EQ( mt6(4,5), 35.0 );
    EXPECT_DOUBLE_EQ( mt6(5,0),  6.0 );
    EXPECT_DOUBLE_EQ( mt6(5,1), 12.0 );
    EXPECT_DOUBLE_EQ( mt6(5,2), 18.0 );
    EXPECT_DOUBLE_EQ( mt6(5,3), 24.0 );
    EXPECT_DOUBLE_EQ( mt6(5,4), 30.0 );
    EXPECT_DOUBLE_EQ( mt6(5,5), 36.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanAssign)
{
    mc::MatrixNxN<3> m31;
    mc::MatrixNxN<4> m41;
    mc::MatrixNxN<6> m61;

    m31(0,0) = 1.0;
    m31(0,1) = 2.0;
    m31(0,2) = 3.0;
    m31(1,0) = 4.0;
    m31(1,1) = 5.0;
    m31(1,2) = 6.0;
    m31(2,0) = 7.0;
    m31(2,1) = 8.0;
    m31(2,2) = 9.0;

    mc::MatrixNxN<3> m32;
    m32 = m31;

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

    mc::MatrixNxN<4> m42;
    m42 = m41;

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

    mc::MatrixNxN<6> m62;
    m62 = m61;

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

TEST_F(TestMatrixNxN, CanAdd)
{
    mc::MatrixNxN<3> m31;
    mc::MatrixNxN<4> m41;
    mc::MatrixNxN<6> m61;

    m31(0,0) = 1.0;
    m31(0,1) = 2.0;
    m31(0,2) = 3.0;
    m31(1,0) = 4.0;
    m31(1,1) = 5.0;
    m31(1,2) = 6.0;
    m31(2,0) = 7.0;
    m31(2,1) = 8.0;
    m31(2,2) = 9.0;

    mc::MatrixNxN<3> m32;
    m32 = m32 + m31;

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

    mc::MatrixNxN<4> m42;
    m42 = m42 + m41;

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

    mc::MatrixNxN<6> m62;
    m62 = m62 + m61;

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

TEST_F(TestMatrixNxN, CanNegate)
{
    mc::MatrixNxN<3> m31;
    mc::MatrixNxN<4> m41;
    mc::MatrixNxN<6> m61;

    m31(0,0) = 1.0;
    m31(0,1) = 2.0;
    m31(0,2) = 3.0;
    m31(1,0) = 4.0;
    m31(1,1) = 5.0;
    m31(1,2) = 6.0;
    m31(2,0) = 7.0;
    m31(2,1) = 8.0;
    m31(2,2) = 9.0;

    mc::MatrixNxN<3> m32;
    m32 = -m31;

    EXPECT_DOUBLE_EQ( m32(0,0), -1.0 );
    EXPECT_DOUBLE_EQ( m32(0,1), -2.0 );
    EXPECT_DOUBLE_EQ( m32(0,2), -3.0 );
    EXPECT_DOUBLE_EQ( m32(1,0), -4.0 );
    EXPECT_DOUBLE_EQ( m32(1,1), -5.0 );
    EXPECT_DOUBLE_EQ( m32(1,2), -6.0 );
    EXPECT_DOUBLE_EQ( m32(2,0), -7.0 );
    EXPECT_DOUBLE_EQ( m32(2,1), -8.0 );
    EXPECT_DOUBLE_EQ( m32(2,2), -9.0 );

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

    mc::MatrixNxN<4> m42;
    m42 = -m41;

    EXPECT_DOUBLE_EQ( m42(0,0),  -1.0 );
    EXPECT_DOUBLE_EQ( m42(0,1),  -2.0 );
    EXPECT_DOUBLE_EQ( m42(0,2),  -3.0 );
    EXPECT_DOUBLE_EQ( m42(0,3),  -4.0 );
    EXPECT_DOUBLE_EQ( m42(1,0),  -5.0 );
    EXPECT_DOUBLE_EQ( m42(1,1),  -6.0 );
    EXPECT_DOUBLE_EQ( m42(1,2),  -7.0 );
    EXPECT_DOUBLE_EQ( m42(1,3),  -8.0 );
    EXPECT_DOUBLE_EQ( m42(2,0), -11.0 );
    EXPECT_DOUBLE_EQ( m42(2,1), -12.0 );
    EXPECT_DOUBLE_EQ( m42(2,2), -13.0 );
    EXPECT_DOUBLE_EQ( m42(2,3), -14.0 );
    EXPECT_DOUBLE_EQ( m42(3,0), -15.0 );
    EXPECT_DOUBLE_EQ( m42(3,1), -16.0 );
    EXPECT_DOUBLE_EQ( m42(3,2), -17.0 );
    EXPECT_DOUBLE_EQ( m42(3,3), -18.0 );

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

    mc::MatrixNxN<6> m62;
    m62 = -m61;

    EXPECT_DOUBLE_EQ( m62(0,0),  -1.0 );
    EXPECT_DOUBLE_EQ( m62(0,1),  -2.0 );
    EXPECT_DOUBLE_EQ( m62(0,2),  -3.0 );
    EXPECT_DOUBLE_EQ( m62(0,3),  -4.0 );
    EXPECT_DOUBLE_EQ( m62(0,4),  -5.0 );
    EXPECT_DOUBLE_EQ( m62(0,5),  -6.0 );
    EXPECT_DOUBLE_EQ( m62(1,0), -11.0 );
    EXPECT_DOUBLE_EQ( m62(1,1), -12.0 );
    EXPECT_DOUBLE_EQ( m62(1,2), -13.0 );
    EXPECT_DOUBLE_EQ( m62(1,3), -14.0 );
    EXPECT_DOUBLE_EQ( m62(1,4), -15.0 );
    EXPECT_DOUBLE_EQ( m62(1,5), -16.0 );
    EXPECT_DOUBLE_EQ( m62(2,0), -21.0 );
    EXPECT_DOUBLE_EQ( m62(2,1), -22.0 );
    EXPECT_DOUBLE_EQ( m62(2,2), -23.0 );
    EXPECT_DOUBLE_EQ( m62(2,3), -24.0 );
    EXPECT_DOUBLE_EQ( m62(2,4), -25.0 );
    EXPECT_DOUBLE_EQ( m62(2,5), -26.0 );
    EXPECT_DOUBLE_EQ( m62(3,0), -31.0 );
    EXPECT_DOUBLE_EQ( m62(3,1), -32.0 );
    EXPECT_DOUBLE_EQ( m62(3,2), -33.0 );
    EXPECT_DOUBLE_EQ( m62(3,3), -34.0 );
    EXPECT_DOUBLE_EQ( m62(3,4), -35.0 );
    EXPECT_DOUBLE_EQ( m62(3,5), -36.0 );
    EXPECT_DOUBLE_EQ( m62(4,0), -41.0 );
    EXPECT_DOUBLE_EQ( m62(4,1), -42.0 );
    EXPECT_DOUBLE_EQ( m62(4,2), -43.0 );
    EXPECT_DOUBLE_EQ( m62(4,3), -44.0 );
    EXPECT_DOUBLE_EQ( m62(4,4), -45.0 );
    EXPECT_DOUBLE_EQ( m62(4,5), -46.0 );
    EXPECT_DOUBLE_EQ( m62(5,0), -51.0 );
    EXPECT_DOUBLE_EQ( m62(5,1), -52.0 );
    EXPECT_DOUBLE_EQ( m62(5,2), -53.0 );
    EXPECT_DOUBLE_EQ( m62(5,3), -54.0 );
    EXPECT_DOUBLE_EQ( m62(5,4), -55.0 );
    EXPECT_DOUBLE_EQ( m62(5,5), -56.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanSubstract)
{
    mc::MatrixNxN<3> m31;
    mc::MatrixNxN<4> m41;
    mc::MatrixNxN<6> m61;

    m31(0,0) = 1.0;
    m31(0,1) = 2.0;
    m31(0,2) = 3.0;
    m31(1,0) = 4.0;
    m31(1,1) = 5.0;
    m31(1,2) = 6.0;
    m31(2,0) = 7.0;
    m31(2,1) = 8.0;
    m31(2,2) = 9.0;

    mc::MatrixNxN<3> m32;
    m32 = m32 - m31;

    EXPECT_DOUBLE_EQ( m32(0,0), -1.0 );
    EXPECT_DOUBLE_EQ( m32(0,1), -2.0 );
    EXPECT_DOUBLE_EQ( m32(0,2), -3.0 );
    EXPECT_DOUBLE_EQ( m32(1,0), -4.0 );
    EXPECT_DOUBLE_EQ( m32(1,1), -5.0 );
    EXPECT_DOUBLE_EQ( m32(1,2), -6.0 );
    EXPECT_DOUBLE_EQ( m32(2,0), -7.0 );
    EXPECT_DOUBLE_EQ( m32(2,1), -8.0 );
    EXPECT_DOUBLE_EQ( m32(2,2), -9.0 );

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

    mc::MatrixNxN<4> m42;
    m42 = m42 - m41;

    EXPECT_DOUBLE_EQ( m42(0,0),  -1.0 );
    EXPECT_DOUBLE_EQ( m42(0,1),  -2.0 );
    EXPECT_DOUBLE_EQ( m42(0,2),  -3.0 );
    EXPECT_DOUBLE_EQ( m42(0,3),  -4.0 );
    EXPECT_DOUBLE_EQ( m42(1,0),  -5.0 );
    EXPECT_DOUBLE_EQ( m42(1,1),  -6.0 );
    EXPECT_DOUBLE_EQ( m42(1,2),  -7.0 );
    EXPECT_DOUBLE_EQ( m42(1,3),  -8.0 );
    EXPECT_DOUBLE_EQ( m42(2,0), -11.0 );
    EXPECT_DOUBLE_EQ( m42(2,1), -12.0 );
    EXPECT_DOUBLE_EQ( m42(2,2), -13.0 );
    EXPECT_DOUBLE_EQ( m42(2,3), -14.0 );
    EXPECT_DOUBLE_EQ( m42(3,0), -15.0 );
    EXPECT_DOUBLE_EQ( m42(3,1), -16.0 );
    EXPECT_DOUBLE_EQ( m42(3,2), -17.0 );
    EXPECT_DOUBLE_EQ( m42(3,3), -18.0 );

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

    mc::MatrixNxN<6> m62;
    m62 = m62 - m61;

    EXPECT_DOUBLE_EQ( m62(0,0),  -1.0 );
    EXPECT_DOUBLE_EQ( m62(0,1),  -2.0 );
    EXPECT_DOUBLE_EQ( m62(0,2),  -3.0 );
    EXPECT_DOUBLE_EQ( m62(0,3),  -4.0 );
    EXPECT_DOUBLE_EQ( m62(0,4),  -5.0 );
    EXPECT_DOUBLE_EQ( m62(0,5),  -6.0 );
    EXPECT_DOUBLE_EQ( m62(1,0), -11.0 );
    EXPECT_DOUBLE_EQ( m62(1,1), -12.0 );
    EXPECT_DOUBLE_EQ( m62(1,2), -13.0 );
    EXPECT_DOUBLE_EQ( m62(1,3), -14.0 );
    EXPECT_DOUBLE_EQ( m62(1,4), -15.0 );
    EXPECT_DOUBLE_EQ( m62(1,5), -16.0 );
    EXPECT_DOUBLE_EQ( m62(2,0), -21.0 );
    EXPECT_DOUBLE_EQ( m62(2,1), -22.0 );
    EXPECT_DOUBLE_EQ( m62(2,2), -23.0 );
    EXPECT_DOUBLE_EQ( m62(2,3), -24.0 );
    EXPECT_DOUBLE_EQ( m62(2,4), -25.0 );
    EXPECT_DOUBLE_EQ( m62(2,5), -26.0 );
    EXPECT_DOUBLE_EQ( m62(3,0), -31.0 );
    EXPECT_DOUBLE_EQ( m62(3,1), -32.0 );
    EXPECT_DOUBLE_EQ( m62(3,2), -33.0 );
    EXPECT_DOUBLE_EQ( m62(3,3), -34.0 );
    EXPECT_DOUBLE_EQ( m62(3,4), -35.0 );
    EXPECT_DOUBLE_EQ( m62(3,5), -36.0 );
    EXPECT_DOUBLE_EQ( m62(4,0), -41.0 );
    EXPECT_DOUBLE_EQ( m62(4,1), -42.0 );
    EXPECT_DOUBLE_EQ( m62(4,2), -43.0 );
    EXPECT_DOUBLE_EQ( m62(4,3), -44.0 );
    EXPECT_DOUBLE_EQ( m62(4,4), -45.0 );
    EXPECT_DOUBLE_EQ( m62(4,5), -46.0 );
    EXPECT_DOUBLE_EQ( m62(5,0), -51.0 );
    EXPECT_DOUBLE_EQ( m62(5,1), -52.0 );
    EXPECT_DOUBLE_EQ( m62(5,2), -53.0 );
    EXPECT_DOUBLE_EQ( m62(5,3), -54.0 );
    EXPECT_DOUBLE_EQ( m62(5,4), -55.0 );
    EXPECT_DOUBLE_EQ( m62(5,5), -56.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanMultiplyByScalar)
{
    mc::MatrixNxN<3> m31;
    mc::MatrixNxN<4> m41;
    mc::MatrixNxN<6> m61;

    m31(0,0) = 1.0;
    m31(0,1) = 2.0;
    m31(0,2) = 3.0;
    m31(1,0) = 4.0;
    m31(1,1) = 5.0;
    m31(1,2) = 6.0;
    m31(2,0) = 7.0;
    m31(2,1) = 8.0;
    m31(2,2) = 9.0;

    mc::MatrixNxN<3> m32;
    m32 = m31 * 2.0;

    EXPECT_DOUBLE_EQ( m32(0,0), 1.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m32(0,1), 2.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m32(0,2), 3.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m32(1,0), 4.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m32(1,1), 5.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m32(1,2), 6.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m32(2,0), 7.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m32(2,1), 8.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m32(2,2), 9.0 * 2.0 );

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

    mc::MatrixNxN<4> m42;
    m42 = m41 * 2.0;

    EXPECT_DOUBLE_EQ( m42(0,0),  1.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(0,1),  2.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(0,2),  3.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(0,3),  4.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(1,0),  5.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(1,1),  6.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(1,2),  7.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(1,3),  8.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(2,0), 11.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(2,1), 12.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(2,2), 13.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(2,3), 14.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(3,0), 15.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(3,1), 16.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(3,2), 17.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m42(3,3), 18.0 * 2.0 );

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

    mc::MatrixNxN<6> m62;
    m62 = m61 * 2.0;

    EXPECT_DOUBLE_EQ( m62(0,0),  1.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(0,1),  2.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(0,2),  3.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(0,3),  4.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(0,4),  5.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(0,5),  6.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(1,0), 11.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(1,1), 12.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(1,2), 13.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(1,3), 14.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(1,4), 15.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(1,5), 16.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(2,0), 21.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(2,1), 22.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(2,2), 23.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(2,3), 24.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(2,4), 25.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(2,5), 26.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(3,0), 31.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(3,1), 32.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(3,2), 33.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(3,3), 34.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(3,4), 35.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(3,5), 36.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(4,0), 41.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(4,1), 42.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(4,2), 43.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(4,3), 44.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(4,4), 45.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(4,5), 46.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(5,0), 51.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(5,1), 52.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(5,2), 53.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(5,3), 54.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(5,4), 55.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m62(5,5), 56.0 * 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanMultiplyByMatrix)
{
    double x30[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixNxN<3> m30;
    m30.setItems( x30 );

    double x31[] { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    mc::MatrixNxN<3> m31;
    m31.setItems( x31 );

    mc::MatrixNxN<3> m3 = m30 * m31;

    EXPECT_NEAR( m3(0,0),  33.0, 1.0e-9 );
    EXPECT_NEAR( m3(0,1),  39.6, 1.0e-9 );
    EXPECT_NEAR( m3(0,2),  46.2, 1.0e-9 );
    EXPECT_NEAR( m3(1,0),  72.6, 1.0e-9 );
    EXPECT_NEAR( m3(1,1),  89.1, 1.0e-9 );
    EXPECT_NEAR( m3(1,2), 105.6, 1.0e-9 );
    EXPECT_NEAR( m3(2,0), 112.2, 1.0e-9 );
    EXPECT_NEAR( m3(2,1), 138.6, 1.0e-9 );
    EXPECT_NEAR( m3(2,2), 165.0, 1.0e-9 );

    double x41[] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };

    double x42[] = {
        2.0,  3.0,  4.0,  5.0,
        6.0,  7.0,  8.0,  9.0,
       10.0, 11.0, 12.0, 13.0,
       14.0, 15.0, 16.0, 17.0
    };

    mc::MatrixNxN<4> m41;
    mc::MatrixNxN<4> m42;

    m41.setItems( x41 );
    m42.setItems( x42 );

    mc::MatrixNxN<4> m4 = m41 * m42;

    EXPECT_DOUBLE_EQ( m4(0,0), 100.0 );
    EXPECT_DOUBLE_EQ( m4(0,1), 110.0 );
    EXPECT_DOUBLE_EQ( m4(0,2), 120.0 );
    EXPECT_DOUBLE_EQ( m4(0,3), 130.0 );
    EXPECT_DOUBLE_EQ( m4(1,0), 228.0 );
    EXPECT_DOUBLE_EQ( m4(1,1), 254.0 );
    EXPECT_DOUBLE_EQ( m4(1,2), 280.0 );
    EXPECT_DOUBLE_EQ( m4(1,3), 306.0 );
    EXPECT_DOUBLE_EQ( m4(2,0), 356.0 );
    EXPECT_DOUBLE_EQ( m4(2,1), 398.0 );
    EXPECT_DOUBLE_EQ( m4(2,2), 440.0 );
    EXPECT_DOUBLE_EQ( m4(2,3), 482.0 );
    EXPECT_DOUBLE_EQ( m4(3,0), 484.0 );
    EXPECT_DOUBLE_EQ( m4(3,1), 542.0 );
    EXPECT_DOUBLE_EQ( m4(3,2), 600.0 );
    EXPECT_DOUBLE_EQ( m4(3,3), 658.0 );

    double x60[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    double x61[] = {
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0
    };

    mc::MatrixNxN<6> m60;
    mc::MatrixNxN<6> m61;

    m60.setItems( x60 );
    m61.setItems( x61 );

    mc::MatrixNxN<6> m6 = m60 * m61;

    EXPECT_DOUBLE_EQ( m6(0,0),  231.0 );
    EXPECT_DOUBLE_EQ( m6(0,1),  252.0 );
    EXPECT_DOUBLE_EQ( m6(0,2),  273.0 );
    EXPECT_DOUBLE_EQ( m6(0,3),  294.0 );
    EXPECT_DOUBLE_EQ( m6(0,4),  315.0 );
    EXPECT_DOUBLE_EQ( m6(0,5),  336.0 );

    EXPECT_DOUBLE_EQ( m6(1,0),  807.0 );
    EXPECT_DOUBLE_EQ( m6(1,1),  864.0 );
    EXPECT_DOUBLE_EQ( m6(1,2),  921.0 );
    EXPECT_DOUBLE_EQ( m6(1,3),  978.0 );
    EXPECT_DOUBLE_EQ( m6(1,4), 1035.0 );
    EXPECT_DOUBLE_EQ( m6(1,5), 1092.0 );

    EXPECT_DOUBLE_EQ( m6(2,0), 1383.0 );
    EXPECT_DOUBLE_EQ( m6(2,1), 1476.0 );
    EXPECT_DOUBLE_EQ( m6(2,2), 1569.0 );
    EXPECT_DOUBLE_EQ( m6(2,3), 1662.0 );
    EXPECT_DOUBLE_EQ( m6(2,4), 1755.0 );
    EXPECT_DOUBLE_EQ( m6(2,5), 1848.0 );

    EXPECT_DOUBLE_EQ( m6(3,0), 1959.0 );
    EXPECT_DOUBLE_EQ( m6(3,1), 2088.0 );
    EXPECT_DOUBLE_EQ( m6(3,2), 2217.0 );
    EXPECT_DOUBLE_EQ( m6(3,3), 2346.0 );
    EXPECT_DOUBLE_EQ( m6(3,4), 2475.0 );
    EXPECT_DOUBLE_EQ( m6(3,5), 2604.0 );

    EXPECT_DOUBLE_EQ( m6(4,0), 2535.0 );
    EXPECT_DOUBLE_EQ( m6(4,1), 2700.0 );
    EXPECT_DOUBLE_EQ( m6(4,2), 2865.0 );
    EXPECT_DOUBLE_EQ( m6(4,3), 3030.0 );
    EXPECT_DOUBLE_EQ( m6(4,4), 3195.0 );
    EXPECT_DOUBLE_EQ( m6(4,5), 3360.0 );

    EXPECT_DOUBLE_EQ( m6(5,0), 3111.0 );
    EXPECT_DOUBLE_EQ( m6(5,1), 3312.0 );
    EXPECT_DOUBLE_EQ( m6(5,2), 3513.0 );
    EXPECT_DOUBLE_EQ( m6(5,3), 3714.0 );
    EXPECT_DOUBLE_EQ( m6(5,4), 3915.0 );
    EXPECT_DOUBLE_EQ( m6(5,5), 4116.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanDivideByScalar)
{
    mc::MatrixNxN<3> m31;
    mc::MatrixNxN<4> m41;
    mc::MatrixNxN<6> m61;

    m31(0,0) = 1.0;
    m31(0,1) = 2.0;
    m31(0,2) = 3.0;
    m31(1,0) = 4.0;
    m31(1,1) = 5.0;
    m31(1,2) = 6.0;
    m31(2,0) = 7.0;
    m31(2,1) = 8.0;
    m31(2,2) = 9.0;

    mc::MatrixNxN<3> m32;
    m32 = m31 / 2.0;

    EXPECT_DOUBLE_EQ( m32(0,0), 1.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m32(0,1), 2.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m32(0,2), 3.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m32(1,0), 4.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m32(1,1), 5.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m32(1,2), 6.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m32(2,0), 7.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m32(2,1), 8.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m32(2,2), 9.0 / 2.0 );

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

    mc::MatrixNxN<4> m42;
    m42 = m41 / 2.0;

    EXPECT_DOUBLE_EQ( m42(0,0),  1.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(0,1),  2.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(0,2),  3.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(0,3),  4.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(1,0),  5.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(1,1),  6.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(1,2),  7.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(1,3),  8.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(2,0), 11.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(2,1), 12.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(2,2), 13.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(2,3), 14.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(3,0), 15.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(3,1), 16.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(3,2), 17.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m42(3,3), 18.0 / 2.0 );

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

    mc::MatrixNxN<6> m62;
    m62 = m61 / 2.0;

    EXPECT_DOUBLE_EQ( m62(0,0),  1.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(0,1),  2.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(0,2),  3.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(0,3),  4.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(0,4),  5.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(0,5),  6.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(1,0), 11.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(1,1), 12.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(1,2), 13.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(1,3), 14.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(1,4), 15.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(1,5), 16.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(2,0), 21.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(2,1), 22.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(2,2), 23.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(2,3), 24.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(2,4), 25.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(2,5), 26.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(3,0), 31.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(3,1), 32.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(3,2), 33.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(3,3), 34.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(3,4), 35.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(3,5), 36.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(4,0), 41.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(4,1), 42.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(4,2), 43.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(4,3), 44.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(4,4), 45.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(4,5), 46.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(5,0), 51.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(5,1), 52.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(5,2), 53.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(5,3), 54.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(5,4), 55.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m62(5,5), 56.0 / 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnaryAdd)
{
    mc::MatrixNxN<3> m31;
    mc::MatrixNxN<4> m41;
    mc::MatrixNxN<6> m61;

    m31(0,0) = 1.0;
    m31(0,1) = 2.0;
    m31(0,2) = 3.0;
    m31(1,0) = 4.0;
    m31(1,1) = 5.0;
    m31(1,2) = 6.0;
    m31(2,0) = 7.0;
    m31(2,1) = 8.0;
    m31(2,2) = 9.0;

    mc::MatrixNxN<3> m32;
    m32 += m31;

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

    mc::MatrixNxN<4> m42;
    m42 += m41;

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

    mc::MatrixNxN<6> m62;
    m62 += m61;

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

TEST_F(TestMatrixNxN, CanUnarySubstract)
{
    mc::MatrixNxN<3> m31;
    mc::MatrixNxN<4> m41;
    mc::MatrixNxN<6> m61;

    m31(0,0) = 1.0;
    m31(0,1) = 2.0;
    m31(0,2) = 3.0;
    m31(1,0) = 4.0;
    m31(1,1) = 5.0;
    m31(1,2) = 6.0;
    m31(2,0) = 7.0;
    m31(2,1) = 8.0;
    m31(2,2) = 9.0;

    mc::MatrixNxN<3> m32;
    m32 -= m31;

    EXPECT_DOUBLE_EQ( m32(0,0), -1.0 );
    EXPECT_DOUBLE_EQ( m32(0,1), -2.0 );
    EXPECT_DOUBLE_EQ( m32(0,2), -3.0 );
    EXPECT_DOUBLE_EQ( m32(1,0), -4.0 );
    EXPECT_DOUBLE_EQ( m32(1,1), -5.0 );
    EXPECT_DOUBLE_EQ( m32(1,2), -6.0 );
    EXPECT_DOUBLE_EQ( m32(2,0), -7.0 );
    EXPECT_DOUBLE_EQ( m32(2,1), -8.0 );
    EXPECT_DOUBLE_EQ( m32(2,2), -9.0 );

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

    mc::MatrixNxN<4> m42;
    m42 -= m41;

    EXPECT_DOUBLE_EQ( m42(0,0),  -1.0 );
    EXPECT_DOUBLE_EQ( m42(0,1),  -2.0 );
    EXPECT_DOUBLE_EQ( m42(0,2),  -3.0 );
    EXPECT_DOUBLE_EQ( m42(0,3),  -4.0 );
    EXPECT_DOUBLE_EQ( m42(1,0),  -5.0 );
    EXPECT_DOUBLE_EQ( m42(1,1),  -6.0 );
    EXPECT_DOUBLE_EQ( m42(1,2),  -7.0 );
    EXPECT_DOUBLE_EQ( m42(1,3),  -8.0 );
    EXPECT_DOUBLE_EQ( m42(2,0), -11.0 );
    EXPECT_DOUBLE_EQ( m42(2,1), -12.0 );
    EXPECT_DOUBLE_EQ( m42(2,2), -13.0 );
    EXPECT_DOUBLE_EQ( m42(2,3), -14.0 );
    EXPECT_DOUBLE_EQ( m42(3,0), -15.0 );
    EXPECT_DOUBLE_EQ( m42(3,1), -16.0 );
    EXPECT_DOUBLE_EQ( m42(3,2), -17.0 );
    EXPECT_DOUBLE_EQ( m42(3,3), -18.0 );

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

    mc::MatrixNxN<6> m62;
    m62 -= m61;

    EXPECT_DOUBLE_EQ( m62(0,0),  -1.0 );
    EXPECT_DOUBLE_EQ( m62(0,1),  -2.0 );
    EXPECT_DOUBLE_EQ( m62(0,2),  -3.0 );
    EXPECT_DOUBLE_EQ( m62(0,3),  -4.0 );
    EXPECT_DOUBLE_EQ( m62(0,4),  -5.0 );
    EXPECT_DOUBLE_EQ( m62(0,5),  -6.0 );
    EXPECT_DOUBLE_EQ( m62(1,0), -11.0 );
    EXPECT_DOUBLE_EQ( m62(1,1), -12.0 );
    EXPECT_DOUBLE_EQ( m62(1,2), -13.0 );
    EXPECT_DOUBLE_EQ( m62(1,3), -14.0 );
    EXPECT_DOUBLE_EQ( m62(1,4), -15.0 );
    EXPECT_DOUBLE_EQ( m62(1,5), -16.0 );
    EXPECT_DOUBLE_EQ( m62(2,0), -21.0 );
    EXPECT_DOUBLE_EQ( m62(2,1), -22.0 );
    EXPECT_DOUBLE_EQ( m62(2,2), -23.0 );
    EXPECT_DOUBLE_EQ( m62(2,3), -24.0 );
    EXPECT_DOUBLE_EQ( m62(2,4), -25.0 );
    EXPECT_DOUBLE_EQ( m62(2,5), -26.0 );
    EXPECT_DOUBLE_EQ( m62(3,0), -31.0 );
    EXPECT_DOUBLE_EQ( m62(3,1), -32.0 );
    EXPECT_DOUBLE_EQ( m62(3,2), -33.0 );
    EXPECT_DOUBLE_EQ( m62(3,3), -34.0 );
    EXPECT_DOUBLE_EQ( m62(3,4), -35.0 );
    EXPECT_DOUBLE_EQ( m62(3,5), -36.0 );
    EXPECT_DOUBLE_EQ( m62(4,0), -41.0 );
    EXPECT_DOUBLE_EQ( m62(4,1), -42.0 );
    EXPECT_DOUBLE_EQ( m62(4,2), -43.0 );
    EXPECT_DOUBLE_EQ( m62(4,3), -44.0 );
    EXPECT_DOUBLE_EQ( m62(4,4), -45.0 );
    EXPECT_DOUBLE_EQ( m62(4,5), -46.0 );
    EXPECT_DOUBLE_EQ( m62(5,0), -51.0 );
    EXPECT_DOUBLE_EQ( m62(5,1), -52.0 );
    EXPECT_DOUBLE_EQ( m62(5,2), -53.0 );
    EXPECT_DOUBLE_EQ( m62(5,3), -54.0 );
    EXPECT_DOUBLE_EQ( m62(5,4), -55.0 );
    EXPECT_DOUBLE_EQ( m62(5,5), -56.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnaryMultiplyByScalar)
{
    mc::MatrixNxN<3> m31;
    mc::MatrixNxN<4> m41;
    mc::MatrixNxN<6> m61;

    m31(0,0) = 1.0;
    m31(0,1) = 2.0;
    m31(0,2) = 3.0;
    m31(1,0) = 4.0;
    m31(1,1) = 5.0;
    m31(1,2) = 6.0;
    m31(2,0) = 7.0;
    m31(2,1) = 8.0;
    m31(2,2) = 9.0;

    m31 *= 2.0;

    EXPECT_DOUBLE_EQ( m31(0,0), 1.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m31(0,1), 2.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m31(0,2), 3.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m31(1,0), 4.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m31(1,1), 5.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m31(1,2), 6.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m31(2,0), 7.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m31(2,1), 8.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m31(2,2), 9.0 * 2.0 );

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

    m41 *= 2.0;

    EXPECT_DOUBLE_EQ( m41(0,0),  1.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(0,1),  2.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(0,2),  3.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(0,3),  4.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(1,0),  5.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(1,1),  6.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(1,2),  7.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(1,3),  8.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(2,0), 11.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(2,1), 12.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(2,2), 13.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(2,3), 14.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(3,0), 15.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(3,1), 16.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(3,2), 17.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m41(3,3), 18.0 * 2.0 );

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

    m61 *= 2.0;

    EXPECT_DOUBLE_EQ( m61(0,0),  1.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(0,1),  2.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(0,2),  3.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(0,3),  4.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(0,4),  5.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(0,5),  6.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(1,0), 11.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(1,1), 12.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(1,2), 13.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(1,3), 14.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(1,4), 15.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(1,5), 16.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(2,0), 21.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(2,1), 22.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(2,2), 23.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(2,3), 24.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(2,4), 25.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(2,5), 26.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(3,0), 31.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(3,1), 32.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(3,2), 33.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(3,3), 34.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(3,4), 35.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(3,5), 36.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(4,0), 41.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(4,1), 42.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(4,2), 43.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(4,3), 44.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(4,4), 45.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(4,5), 46.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(5,0), 51.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(5,1), 52.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(5,2), 53.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(5,3), 54.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(5,4), 55.0 * 2.0 );
    EXPECT_DOUBLE_EQ( m61(5,5), 56.0 * 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnaryDivideByScalar)
{
    mc::MatrixNxN<3> m31;
    mc::MatrixNxN<4> m41;
    mc::MatrixNxN<6> m61;

    m31(0,0) = 1.0;
    m31(0,1) = 2.0;
    m31(0,2) = 3.0;
    m31(1,0) = 4.0;
    m31(1,1) = 5.0;
    m31(1,2) = 6.0;
    m31(2,0) = 7.0;
    m31(2,1) = 8.0;
    m31(2,2) = 9.0;

    m31 /= 2.0;

    EXPECT_DOUBLE_EQ( m31(0,0), 1.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m31(0,1), 2.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m31(0,2), 3.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m31(1,0), 4.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m31(1,1), 5.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m31(1,2), 6.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m31(2,0), 7.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m31(2,1), 8.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m31(2,2), 9.0 / 2.0 );

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

    m41 /= 2.0;

    EXPECT_DOUBLE_EQ( m41(0,0),  1.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(0,1),  2.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(0,2),  3.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(0,3),  4.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(1,0),  5.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(1,1),  6.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(1,2),  7.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(1,3),  8.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(2,0), 11.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(2,1), 12.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(2,2), 13.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(2,3), 14.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(3,0), 15.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(3,1), 16.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(3,2), 17.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m41(3,3), 18.0 / 2.0 );

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

    m61 /= 2.0;

    EXPECT_DOUBLE_EQ( m61(0,0),  1.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(0,1),  2.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(0,2),  3.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(0,3),  4.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(0,4),  5.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(0,5),  6.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(1,0), 11.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(1,1), 12.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(1,2), 13.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(1,3), 14.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(1,4), 15.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(1,5), 16.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(2,0), 21.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(2,1), 22.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(2,2), 23.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(2,3), 24.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(2,4), 25.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(2,5), 26.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(3,0), 31.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(3,1), 32.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(3,2), 33.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(3,3), 34.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(3,4), 35.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(3,5), 36.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(4,0), 41.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(4,1), 42.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(4,2), 43.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(4,3), 44.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(4,4), 45.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(4,5), 46.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(5,0), 51.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(5,1), 52.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(5,2), 53.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(5,3), 54.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(5,4), 55.0 / 2.0 );
    EXPECT_DOUBLE_EQ( m61(5,5), 56.0 / 2.0 );
}
