#ifdef TEST_USING_ARMADILLO

#include <gtest/gtest.h>
#include <armadillo>

#include <mcutils/math/MatrixMxN.h>

#include <TestingUtils.h>

// To achieve full test coverage of MatrixNxN template class some tests have
// to be done for 3x3, 4x4 and 6x6 matrices, as template class MatrixMxN has 
// derived classes which are not templates. (e.g. all operators)

class TestMatrixMxN_Armadillo : public ::testing::Test
{
protected:
    TestMatrixMxN_Armadillo() {}
    virtual ~TestMatrixMxN_Armadillo() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMatrixMxN_Armadillo, CanAdd3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> m2;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 + m2;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat ma2(rows, cols);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 + ma2;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanAdd4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> m2;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 + m2;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat ma2(rows, cols);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 + ma2;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanAdd6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> m2;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 + m2;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat ma2(rows, cols);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 + ma2;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanSubstract3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> m2;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 - m2;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat ma2(rows, cols);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 - ma2;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanSubstract4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> m2;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 - m2;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat ma2(rows, cols);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 - ma2;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanSubstract6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> m2;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 - m2;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat ma2(rows, cols);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 - ma2;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanMultiplyByScalar3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    mr = m1 * scalar;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar;
    mar = ma1 * scalar;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanMultiplyByScalar4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    mr = m1 * scalar;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar;
    mar = ma1 * scalar;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanMultiplyByScalar6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    mr = m1 * scalar;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar;
    mar = ma1 * scalar;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanMultiplyRandomMatrixByVector3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    mc::MatrixMxN<rows,cols> m3;


    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };
    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);

    mc::VectorN<rows> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<rows> vr = m * v;

    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    arma::vec va;
    va << 1.0 << arma::endr
       << 2.0 << arma::endr
       << 3.0 << arma::endr;
    arma::vec var;
    var = ma * va;

    for ( int r = 0; r < rows; ++r )
    {
        EXPECT_DOUBLE_EQ(vr(r), var(r)) << "Error at row " << r;
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanMultiplyByVector4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    double x[] {  1.0,  2.0,  3.0,  4.0,
                  5.0,  6.0,  7.0,  8.0,
                  9.0, 10.0, 11.0, 12.0,
                 13.0, 14.0, 15.0, 16.0 };
    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);

    mc::VectorN<rows> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;
    v(3) = 4.0;

    mc::VectorN<rows> vr = m * v;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::vec va;
    va << 1.0 << arma::endr
       << 2.0 << arma::endr
       << 3.0 << arma::endr
       << 4.0 << arma::endr;
    arma::vec var;
    var = ma1 * va;

    for ( int r = 0; r < rows; ++r )
    {
        EXPECT_DOUBLE_EQ(vr(r), var(r)) << "Error at row " << r;
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanMultiplyByVector6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    double x[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                  7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                 13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                 19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                 31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };
    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);

    mc::VectorN<rows> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;
    v(3) = 4.0;
    v(4) = 5.0;
    v(5) = 6.0;

    mc::VectorN<rows> vr = m * v;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::vec va;
    va << 1.0 << arma::endr
       << 2.0 << arma::endr
       << 3.0 << arma::endr
       << 4.0 << arma::endr
       << 5.0 << arma::endr
       << 6.0 << arma::endr;
    arma::vec var;
    var = ma1 * va;

    for ( int r = 0; r < rows; ++r )
    {
        EXPECT_DOUBLE_EQ(vr(r), var(r)) << "Error at row " << r;
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanDivideByScalar3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    mr = m1 / scalar;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar;
    mar = ma1 / scalar;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanDivideByScalar4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    mr = m1 / scalar;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar;
    mar = ma1 / scalar;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanDivideByScalar6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    mr = m1 / scalar;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar;
    mar = ma1 / scalar;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanUnaryAdd3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr += m1;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar(rows, cols, arma::fill::zeros);
    mar.fill(val);
    mar += ma1;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanUnaryAdd4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr += m1;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar(rows, cols, arma::fill::zeros);
    mar.fill(val);
    mar += ma1;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanUnaryAdd6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr += m1;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar(rows, cols, arma::fill::zeros);
    mar.fill(val);
    mar += ma1;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanUnarySubstract3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr -= m1;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar(rows, cols, arma::fill::zeros);
    mar.fill(val);
    mar -= ma1;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanUnarySubstract4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr -= m1;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar(rows, cols, arma::fill::zeros);
    mar.fill(val);
    mar -= ma1;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanUnarySubstract6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    constexpr double val = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr -= m1;

    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar(rows, cols, arma::fill::zeros);
    mar.fill(val);
    mar -= ma1;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanUnaryMultiplyByScalar3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);
    m *= scalar;

    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    ma *= scalar;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanUnaryMultiplyByScalar4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);
    m *= scalar;

    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    ma *= scalar;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanUnaryMultiplyByScalar6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);
    m *= scalar;

    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    ma *= scalar;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanUnaryDivideByScalar3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);
    m /= scalar;

    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    ma /= scalar;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanUnaryDivideByScalar4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);
    m /= scalar;

    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    ma /= scalar;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN_Armadillo, CanUnaryDivideByScalar6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    constexpr double scalar = 2.0;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);
    m /= scalar;

    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    ma /= scalar;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

#endif // TEST_USING_ARMADILLO