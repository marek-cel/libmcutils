#ifdef TEST_USING_ARMADILLO

#include <gtest/gtest.h>
#include <armadillo>


#include <mcutils/math/MatrixNxN.h>

#include <TestingUtils.h>

// To achieve full test coverage of MatrixNxN template class some tests have
// to be done for 3x3, 4x4 and 6x6 matrices, as template class MatrixNxN has 
// derived classes which are not templates. (e.g. all operators)

class TestMatrixNxN_Armadillo : public ::testing::Test
{
protected:
    TestMatrixNxN_Armadillo() {}
    virtual ~TestMatrixNxN_Armadillo() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMatrixNxN_Armadillo, CanGetTransposed3x3)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m0;
    m0.SetFromArray(x);

    mc::MatrixNxN<size> m1(m0);
    mc::MatrixNxN<size> mt = m1.GetTransposed();

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mat = ma1.t();

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
            EXPECT_DOUBLE_EQ(mt(r,c), mat(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanGetTransposed4x4)
{
    constexpr int size = 4;

    double x[] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };

    mc::MatrixNxN<size> m0;
    m0.SetFromArray(x);

    mc::MatrixNxN<size> m1(m0);
    mc::MatrixNxN<size> mt = m1.GetTransposed();

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mat = ma1.t();

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
            EXPECT_DOUBLE_EQ(mt(r,c), mat(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanGetTransposed6x6)
{
    constexpr int size = 6;

    double x[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::MatrixNxN<size> m0;
    m0.SetFromArray(x);

    mc::MatrixNxN<size> m1(m0);
    mc::MatrixNxN<size> mt = m1.GetTransposed();

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mat = ma1.t();

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
            EXPECT_DOUBLE_EQ(mt(r,c), mat(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}



TEST_F(TestMatrixNxN_Armadillo, CanAdd3x3)
{
    constexpr int size = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> m2;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 + m2;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat ma2(size, size);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 + ma2;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanAdd4x4)
{
    constexpr int size = 4;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> m2;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 + m2;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat ma2(size, size);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 + ma2;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanAdd6x6)
{
    constexpr int size = 6;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> m2;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 + m2;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat ma2(size, size);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 + ma2;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanSubstract3x3)
{
    constexpr int size = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> m2;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 - m2;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat ma2(size, size);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 - ma2;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanSubstract4x4)
{
    constexpr int size = 4;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> m2;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 - m2;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat ma2(size, size);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 - ma2;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanSubstract6x6)
{
    constexpr int size = 6;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> m2;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 - m2;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat ma2(size, size);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 - ma2;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanMultiplyByScalar3x3)
{
    constexpr int size = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    mr = m1 * scalar;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar = ma1 * scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanMultiplyByScalar4x4)
{
    constexpr int size = 4;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    mr = m1 * scalar;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar = ma1 * scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanMultiplyByScalar6x6)
{
    constexpr int size = 6;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    mr = m1 * scalar;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar = ma1 * scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanMultiplyByMatrix3x3)
{
    constexpr int size = 3;

    double x1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixNxN<size> m1;
    m1.SetFromArray(x1);

    double x2[] { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    mc::MatrixNxN<size> m2;
    m2.SetFromArray(x2);

    mc::MatrixNxN<size> mr = m1 * m2;

    arma::mat ma1 = SetArmaMatFromArray(x1, size, size);
    arma::mat ma2 = SetArmaMatFromArray(x2, size, size);
    arma::mat mar = ma1 * ma2;
    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanMultiplyByMatrix4x4)
{
    constexpr int size = 4;

    double x1[] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };

    double x2[] = {
        2.0,  3.0,  4.0,  5.0,
        6.0,  7.0,  8.0,  9.0,
       10.0, 11.0, 12.0, 13.0,
       14.0, 15.0, 16.0, 17.0
    };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> m2;

    m1.SetFromArray(x1);
    m2.SetFromArray(x2);

    mc::MatrixNxN<size> mr = m1 * m2;

    arma::mat ma1 = SetArmaMatFromArray(x1, size, size);
    arma::mat ma2 = SetArmaMatFromArray(x2, size, size);
    arma::mat mar = ma1 * ma2;
    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanMultiplyByMatrix6x6)
{
    constexpr int size = 6;

    double x1[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    double x2[] = {
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0
    };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> m2;

    m1.SetFromArray(x1);
    m2.SetFromArray(x2);

    mc::MatrixNxN<size> mr = m1 * m2;

    arma::mat ma1 = SetArmaMatFromArray(x1, size, size);
    arma::mat ma2 = SetArmaMatFromArray(x2, size, size);
    arma::mat mar = ma1 * ma2;
    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanDivideByScalar3x3)
{
    constexpr int size = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    mr = m1 / scalar;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar;
    mar = ma1 / scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanDivideByScalar4x4)
{
    constexpr int size = 4;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    mr = m1 / scalar;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar;
    mar = ma1 / scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanDivideByScalar6x6)
{
    constexpr int size = 6;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    mr = m1 / scalar;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar;
    mar = ma1 / scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanUnaryAdd3x3)
{
    constexpr int size = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr += m1;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar(size, size, arma::fill::zeros);
    mar.fill(val);
    mar += ma1;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanUnaryAdd4x4)
{
    constexpr int size = 4;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr += m1;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar(size, size, arma::fill::zeros);
    mar.fill(val);
    mar += ma1;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanUnaryAdd6x6)
{
    constexpr int size = 6;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr += m1;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar(size, size, arma::fill::zeros);
    mar.fill(val);
    mar += ma1;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanUnarySubstract3x3)
{
    constexpr int size = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr -= m1;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar(size, size, arma::fill::zeros);
    mar.fill(val);
    mar -= ma1;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanUnarySubstract4x4)
{
    constexpr int size = 4;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr -= m1;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar(size, size, arma::fill::zeros);
    mar.fill(val);
    mar -= ma1;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanUnarySubstract6x6)
{
    constexpr int size = 6;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr -= m1;

    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar(size, size, arma::fill::zeros);
    mar.fill(val);
    mar -= ma1;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanUnaryMultiplyByScalar3x3)
{
    constexpr int size = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m;
    m.SetFromArray(x);
    m *= scalar;

    arma::mat ma = SetArmaMatFromArray(x, size, size);
    ma *= scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanUnaryMultiplyByScalar4x4)
{
    constexpr int size = 4;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixNxN<size> m;
    m.SetFromArray(x);
    m *= scalar;

    arma::mat ma = SetArmaMatFromArray(x, size, size);
    ma *= scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanUnaryMultiplyByScalar6x6)
{
    constexpr int size = 6;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixNxN<size> m;
    m.SetFromArray(x);
    m *= scalar;

    arma::mat ma = SetArmaMatFromArray(x, size, size);
    ma *= scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanUnaryDivideByScalar3x3)
{
    constexpr int size = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m;
    m.SetFromArray(x);
    m /= scalar;

    arma::mat ma = SetArmaMatFromArray(x, size, size);
    ma /= scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanUnaryDivideByScalar4x4)
{
    constexpr int size = 4;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixNxN<size> m;
    m.SetFromArray(x);
    m /= scalar;

    arma::mat ma = SetArmaMatFromArray(x, size, size);
    ma /= scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN_Armadillo, CanUnaryDivideByScalar6x6)
{
    constexpr int size = 6;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixNxN<size> m;
    m.SetFromArray(x);
    m /= scalar;

    arma::mat ma = SetArmaMatFromArray(x, size, size);
    ma /= scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

#endif // TEST_USING_ARMADILLO