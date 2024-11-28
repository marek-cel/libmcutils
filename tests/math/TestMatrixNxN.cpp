#include <gtest/gtest.h>

#include <mcutils/math/Matrix.h>

class TestMatrixNxN : public ::testing::Test
{
protected:
    TestMatrixNxN() {}
    virtual ~TestMatrixNxN() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMatrixNxN, CanInstantiate)
{
    constexpr int size = 3;
    mc::MatrixNxN<double,size> m;
    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanInstantiateAndCopy)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m0;
    m0.SetFromArray(x);

    mc::MatrixNxN<double,size> m1(m0);

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanTranspose)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m;
    m.SetFromArray(x);

    m.Transpose();

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            int index = r * size + c;
            // matrix 'm' transposed (row and col inverted)
            EXPECT_DOUBLE_EQ(m(c,r), x[index]) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanGetTransposed)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m0;
    m0.SetFromArray(x);

    mc::MatrixNxN<double,size> m1(m0);
    mc::MatrixNxN<double,size> mt = m1.GetTransposed();

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
            EXPECT_DOUBLE_EQ(mt(r,c), m0(c,r)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanAssign)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m0;
    mc::MatrixNxN<double,size> m1;
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

TEST_F(TestMatrixNxN, CanAdd)
{
    constexpr int size = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m1;
    mc::MatrixNxN<double,size> m2;
    mc::MatrixNxN<double,size> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 + m2;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] + val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanNegate)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m1;
    mc::MatrixNxN<double,size> m2;
    mc::MatrixNxN<double,size> mr;
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

TEST_F(TestMatrixNxN, CanSubstract)
{
    constexpr int size = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m1;
    mc::MatrixNxN<double,size> m2;
    mc::MatrixNxN<double,size> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 - m2;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] - val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanMultiplyByScalar)
{
    constexpr int size = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m1;
    mc::MatrixNxN<double,size> mr;
    m1.SetFromArray(x);
    mr = m1 * scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] * scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanMultiplyByMatrix)
{
    constexpr int size = 3;

    double x1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixNxN<double,size> m1;
    m1.SetFromArray(x1);

    double x2[] { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    mc::MatrixNxN<double,size> m2;
    m2.SetFromArray(x2);

    mc::MatrixNxN<double,size> mr = m1 * m2;

    EXPECT_NEAR(mr(0,0),  33.0, 1.0e-9);
    EXPECT_NEAR(mr(0,1),  39.6, 1.0e-9);
    EXPECT_NEAR(mr(0,2),  46.2, 1.0e-9);

    EXPECT_NEAR(mr(1,0),  72.6, 1.0e-9);
    EXPECT_NEAR(mr(1,1),  89.1, 1.0e-9);
    EXPECT_NEAR(mr(1,2), 105.6, 1.0e-9);

    EXPECT_NEAR(mr(2,0), 112.2, 1.0e-9);
    EXPECT_NEAR(mr(2,1), 138.6, 1.0e-9);
    EXPECT_NEAR(mr(2,2), 165.0, 1.0e-9);
}

TEST_F(TestMatrixNxN, CanDivideByScalar)
{
    constexpr int size = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m1;
    mc::MatrixNxN<double,size> mr;
    m1.SetFromArray(x);
    mr = m1 / scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] / scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanUnaryAdd)
{
    constexpr int size = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m1;
    mc::MatrixNxN<double,size> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr += m1;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val + m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanUnarySubstract)
{
    constexpr int size = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m1;
    mc::MatrixNxN<double,size> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr -= m1;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val - m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanUnaryMultiplyByScalar)
{
    constexpr int size = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m;
    m.SetFromArray(x);
    m *= scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] * scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanUnaryDivideByScalar)
{
    constexpr int size = 3;

    constexpr double scalar = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixNxN<double,size> m;
    m.SetFromArray(x);
    m /= scalar;

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            double ref_value = x[r*size + c] / scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}
