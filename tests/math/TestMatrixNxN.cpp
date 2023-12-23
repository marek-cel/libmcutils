#include <gtest/gtest.h>

#ifdef TEST_USING_ARMADILLO
#   include <armadillo>
#endif // TEST_USING_ARMADILLO

#include <mcutils/math/MatrixNxN.h>

#include <TestingUtils.h>

////////////////////////////////////////////////////////////////////////////////

// To achieve full test coverage of MatrixNxN template class tests have to be
// done for 3x3, 4x4 and 6x6 matrices, as template class MatrixNxN has derived 
// classes which are not templates.

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
    mc::MatrixNxN<3>* m3 = nullptr;
    EXPECT_NO_THROW(m3 = new mc::MatrixNxN<3>());
    delete m3;

    mc::MatrixNxN<4>* m4 = nullptr;
    EXPECT_NO_THROW(m4 = new mc::MatrixNxN<4>());
    delete m4;

    mc::MatrixNxN<6>* m6 = nullptr;
    EXPECT_NO_THROW(m6 = new mc::MatrixNxN<6>());
    delete m6;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanDestruct)
{
    mc::MatrixNxN<3>* m3 = new mc::MatrixNxN<3>();
    EXPECT_NO_THROW(delete m3);

    mc::MatrixNxN<4>* m4 = new mc::MatrixNxN<4>();
    EXPECT_NO_THROW(delete m4);

    mc::MatrixNxN<6>* m6 = new mc::MatrixNxN<6>();
    EXPECT_NO_THROW(delete m6);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanInstantiate3x3)
{
    constexpr int size = 3;

    mc::MatrixNxN<size> m;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanInstantiate4x4)
{
    constexpr int size = 4;

    mc::MatrixNxN<size> m;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanInstantiate6x6)
{
    constexpr int size = 6;

    mc::MatrixNxN<size> m;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanInstantiateAndCopy3x3)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m0;
    m0.SetFromArray(x);

    mc::MatrixNxN<size> m1(m0);

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanInstantiateAndCopy4x4)
{
    constexpr int size = 4;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixNxN<size> m0;
    m0.SetFromArray(x);

    mc::MatrixNxN<size> m1(m0);

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanInstantiateAndCopy6x6)
{
    constexpr int size = 6;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixNxN<size> m0;
    m0.SetFromArray(x);

    mc::MatrixNxN<size> m1(m0);

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanTranspose)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m1;
    m1.SetFromArray(x);

    m1.Transpose();

    EXPECT_DOUBLE_EQ(m1(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m1(0,1), 4.0);
    EXPECT_DOUBLE_EQ(m1(0,2), 7.0);
    EXPECT_DOUBLE_EQ(m1(1,0), 2.0);
    EXPECT_DOUBLE_EQ(m1(1,1), 5.0);
    EXPECT_DOUBLE_EQ(m1(1,2), 8.0);
    EXPECT_DOUBLE_EQ(m1(2,0), 3.0);
    EXPECT_DOUBLE_EQ(m1(2,1), 6.0);
    EXPECT_DOUBLE_EQ(m1(2,2), 9.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanGetTransposed3x3)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m0;
    m0.SetFromArray(x);

    mc::MatrixNxN<size> m1(m0);
    mc::MatrixNxN<size> mt = m1.GetTransposed();

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mat = ma1.t();
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
            EXPECT_DOUBLE_EQ(mt(r,c), m0(c,r)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mt(r,c), mat(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanGetTransposed4x4)
{
    constexpr int size = 4;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixNxN<size> m0;
    m0.SetFromArray(x);

    mc::MatrixNxN<size> m1(m0);
    mc::MatrixNxN<size> mt = m1.GetTransposed();

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mat = ma1.t();
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
            EXPECT_DOUBLE_EQ(mt(r,c), m0(c,r)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mt(r,c), mat(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanGetTransposed6x6)
{
    constexpr int size = 6;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixNxN<size> m0;
    m0.SetFromArray(x);

    mc::MatrixNxN<size> m1(m0);
    mc::MatrixNxN<size> mt = m1.GetTransposed();

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mat = ma1.t();
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
            EXPECT_DOUBLE_EQ(mt(r,c), m0(c,r)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mt(r,c), mat(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanAssign3x3)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m0;
    mc::MatrixNxN<size> m1;
    m0.SetFromArray(x);
    m1 = m0;

        for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanAssign4x4)
{
    constexpr int size = 4;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixNxN<size> m0;
    mc::MatrixNxN<size> m1;
    m0.SetFromArray(x);
    m1 = m0;

        for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanAssign6x6)
{
    constexpr int size = 6;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixNxN<size> m0;
    mc::MatrixNxN<size> m1;
    m0.SetFromArray(x);
    m1 = m0;

        for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanAdd3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat ma2(size, size);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 + ma2;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] + val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanAdd4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat ma2(size, size);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 + ma2;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] + val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanAdd6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat ma2(size, size);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 + ma2;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] + val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanNegate3x3)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> m2;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    m2.SetFromArray(x);
    mr = -m1;

        for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), -m2(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanNegate4x4)
{
    constexpr int size = 4;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixNxN<size> m1;
    mc::MatrixNxN<size> m2;
    mc::MatrixNxN<size> mr;
    m1.SetFromArray(x);
    m2.SetFromArray(x);
    mr = -m1;

        for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), -m2(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanNegate6x6)
{
    constexpr int size = 6;

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
    m2.SetFromArray(x);
    mr = -m1;

        for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), -m2(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanSubstract3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat ma2(size, size);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 - ma2;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] - val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanSubstract4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat ma2(size, size);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 - ma2;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] - val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanSubstract6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat ma2(size, size);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 - ma2;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] - val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanMultiplyByScalar3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar = ma1 * scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] * scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanMultiplyByScalar4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar = ma1 * scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] * scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanMultiplyByScalar6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar = ma1 * scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] * scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanMultiplyByMatrix3x3)
{
    constexpr int size = 3;

    double x1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixNxN<size> m1;
    m1.SetFromArray(x1);

    double x2[] { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    mc::MatrixNxN<size> m2;
    m2.SetFromArray(x2);

    mc::MatrixNxN<size> mr = m1 * m2;

    EXPECT_NEAR(mr(0,0),  33.0, 1.0e-9);
    EXPECT_NEAR(mr(0,1),  39.6, 1.0e-9);
    EXPECT_NEAR(mr(0,2),  46.2, 1.0e-9);
    
    EXPECT_NEAR(mr(1,0),  72.6, 1.0e-9);
    EXPECT_NEAR(mr(1,1),  89.1, 1.0e-9);
    EXPECT_NEAR(mr(1,2), 105.6, 1.0e-9);
    
    EXPECT_NEAR(mr(2,0), 112.2, 1.0e-9);
    EXPECT_NEAR(mr(2,1), 138.6, 1.0e-9);
    EXPECT_NEAR(mr(2,2), 165.0, 1.0e-9);

#   ifdef TEST_USING_ARMADILLO
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
#   endif // TEST_USING_ARMADILLO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanMultiplyByMatrix4x4)
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

    EXPECT_DOUBLE_EQ(mr(0,0), 100.0);
    EXPECT_DOUBLE_EQ(mr(0,1), 110.0);
    EXPECT_DOUBLE_EQ(mr(0,2), 120.0);
    EXPECT_DOUBLE_EQ(mr(0,3), 130.0);

    EXPECT_DOUBLE_EQ(mr(1,0), 228.0);
    EXPECT_DOUBLE_EQ(mr(1,1), 254.0);
    EXPECT_DOUBLE_EQ(mr(1,2), 280.0);
    EXPECT_DOUBLE_EQ(mr(1,3), 306.0);
    
    EXPECT_DOUBLE_EQ(mr(2,0), 356.0);
    EXPECT_DOUBLE_EQ(mr(2,1), 398.0);
    EXPECT_DOUBLE_EQ(mr(2,2), 440.0);
    EXPECT_DOUBLE_EQ(mr(2,3), 482.0);
    
    EXPECT_DOUBLE_EQ(mr(3,0), 484.0);
    EXPECT_DOUBLE_EQ(mr(3,1), 542.0);
    EXPECT_DOUBLE_EQ(mr(3,2), 600.0);
    EXPECT_DOUBLE_EQ(mr(3,3), 658.0);

#   ifdef TEST_USING_ARMADILLO
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
#   endif // TEST_USING_ARMADILLO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanMultiplyByMatrix6x6)
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

    EXPECT_DOUBLE_EQ(mr(0,0),  231.0);
    EXPECT_DOUBLE_EQ(mr(0,1),  252.0);
    EXPECT_DOUBLE_EQ(mr(0,2),  273.0);
    EXPECT_DOUBLE_EQ(mr(0,3),  294.0);
    EXPECT_DOUBLE_EQ(mr(0,4),  315.0);
    EXPECT_DOUBLE_EQ(mr(0,5),  336.0);

    EXPECT_DOUBLE_EQ(mr(1,0),  807.0);
    EXPECT_DOUBLE_EQ(mr(1,1),  864.0);
    EXPECT_DOUBLE_EQ(mr(1,2),  921.0);
    EXPECT_DOUBLE_EQ(mr(1,3),  978.0);
    EXPECT_DOUBLE_EQ(mr(1,4), 1035.0);
    EXPECT_DOUBLE_EQ(mr(1,5), 1092.0);

    EXPECT_DOUBLE_EQ(mr(2,0), 1383.0);
    EXPECT_DOUBLE_EQ(mr(2,1), 1476.0);
    EXPECT_DOUBLE_EQ(mr(2,2), 1569.0);
    EXPECT_DOUBLE_EQ(mr(2,3), 1662.0);
    EXPECT_DOUBLE_EQ(mr(2,4), 1755.0);
    EXPECT_DOUBLE_EQ(mr(2,5), 1848.0);

    EXPECT_DOUBLE_EQ(mr(3,0), 1959.0);
    EXPECT_DOUBLE_EQ(mr(3,1), 2088.0);
    EXPECT_DOUBLE_EQ(mr(3,2), 2217.0);
    EXPECT_DOUBLE_EQ(mr(3,3), 2346.0);
    EXPECT_DOUBLE_EQ(mr(3,4), 2475.0);
    EXPECT_DOUBLE_EQ(mr(3,5), 2604.0);

    EXPECT_DOUBLE_EQ(mr(4,0), 2535.0);
    EXPECT_DOUBLE_EQ(mr(4,1), 2700.0);
    EXPECT_DOUBLE_EQ(mr(4,2), 2865.0);
    EXPECT_DOUBLE_EQ(mr(4,3), 3030.0);
    EXPECT_DOUBLE_EQ(mr(4,4), 3195.0);
    EXPECT_DOUBLE_EQ(mr(4,5), 3360.0);

    EXPECT_DOUBLE_EQ(mr(5,0), 3111.0);
    EXPECT_DOUBLE_EQ(mr(5,1), 3312.0);
    EXPECT_DOUBLE_EQ(mr(5,2), 3513.0);
    EXPECT_DOUBLE_EQ(mr(5,3), 3714.0);
    EXPECT_DOUBLE_EQ(mr(5,4), 3915.0);
    EXPECT_DOUBLE_EQ(mr(5,5), 4116.0);

#   ifdef TEST_USING_ARMADILLO
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
#   endif // TEST_USING_ARMADILLO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanDivideByScalar3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar;
    mar = ma1 / scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] / scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanDivideByScalar4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar;
    mar = ma1 / scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] / scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanDivideByScalar6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar;
    mar = ma1 / scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] / scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnaryAdd3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar(size, size, arma::fill::zeros);
    mar.fill(val);
    mar += ma1;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val + m1(r,c)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnaryAdd4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar(size, size, arma::fill::zeros);
    mar.fill(val);
    mar += ma1;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val + m1(r,c)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnaryAdd6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar(size, size, arma::fill::zeros);
    mar.fill(val);
    mar += ma1;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val + m1(r,c)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnarySubstract3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar(size, size, arma::fill::zeros);
    mar.fill(val);
    mar -= ma1;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val - m1(r,c)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnarySubstract4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar(size, size, arma::fill::zeros);
    mar.fill(val);
    mar -= ma1;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val - m1(r,c)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnarySubstract6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, size, size);
    arma::mat mar(size, size, arma::fill::zeros);
    mar.fill(val);
    mar -= ma1;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val - m1(r,c)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnaryMultiplyByScalar3x3)
{
    constexpr int size = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m;
    m.SetFromArray(x);
    m *= scalar;

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma = SetArmaMatFromArray(x, size, size);
    ma *= scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] * scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnaryMultiplyByScalar4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma = SetArmaMatFromArray(x, size, size);
    ma *= scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] * scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnaryMultiplyByScalar6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma = SetArmaMatFromArray(x, size, size);
    ma *= scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] * scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnaryDivideByScalar3x3)
{
    constexpr int size = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<size> m;
    m.SetFromArray(x);
    m /= scalar;

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma = SetArmaMatFromArray(x, size, size);
    ma /= scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] / scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnaryDivideByScalar4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma = SetArmaMatFromArray(x, size, size);
    ma /= scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] / scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixNxN, CanUnaryDivideByScalar6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma = SetArmaMatFromArray(x, size, size);
    ma /= scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] / scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}
