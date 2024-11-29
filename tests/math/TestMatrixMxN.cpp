#include <gtest/gtest.h>

#include <mcutils/math/Matrix.h>

class TestMatrixMxN : public ::testing::Test
{
protected:
    TestMatrixMxN() {}
    virtual ~TestMatrixMxN() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMatrixMxN, CanInstantiate)
{
    constexpr int size = 3;
    mc::MatrixMxN<double,size,size> m;
    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanFill)
{
    constexpr int rows = 3;
    constexpr int cols = 3;
    constexpr double val = 666.0;

    mc::MatrixMxN<double,rows,cols> mat;
    mat.Fill(val);

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mat(r,c), val) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanValidate)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    double x[] = { 1.0, 2.0, 3.0,
                   4.0, 5.0, 6.0,
                   7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,rows,cols> m1;
    EXPECT_TRUE(m1.IsValid());

    mc::MatrixMxN<double,rows,cols> m2;
    m2.SetFromArray(x);
    EXPECT_TRUE(m2.IsValid());

    mc::MatrixMxN<double,rows,cols> m3;
    m3.SetFromArray(x);
    m3(0,0) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(m3.IsValid());

    mc::MatrixMxN<double,rows,cols> m4;
    m4.SetFromArray(x);
    m4(1,1) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(m4.IsValid());

    mc::MatrixMxN<double,rows,cols> m5;
    m5.Fill(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(m5.IsValid());
}

TEST_F(TestMatrixMxN, CanPutIntoArray)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };
    double xx[rows * cols] = { 0.0 };

    mc::MatrixMxN<double,rows,cols> m;
    m.SetFromArray(x);
    m.PutIntoArray(xx);

    for ( int i = 0; i < rows * cols; ++i )
    {
        EXPECT_DOUBLE_EQ(xx[i], x[i]) << "Error at index " << i;
    }
}

TEST_F(TestMatrixMxN, CanSetFromArray)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    mc::MatrixMxN<double,rows,cols> m;

    double x[] = { 1.0, 2.0, 3.0,
                   4.0, 5.0, 6.0,
                   7.0, 8.0, 9.0 };

    m.SetFromArray(x);

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            int index = r * cols + c;
            EXPECT_DOUBLE_EQ(m(r,c), x[index]) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanSetFromString)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    char str[] =
    { R"##(
        1.0 2.0 3.0
        4.0 5.0 6.0
        7.0 8.0 9.0
    )##" };

    mc::MatrixMxN<double,rows,cols> m;
    m.SetFromString(str);

    EXPECT_DOUBLE_EQ(m(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m(0,1), 2.0);
    EXPECT_DOUBLE_EQ(m(0,2), 3.0);

    EXPECT_DOUBLE_EQ(m(1,0), 4.0);
    EXPECT_DOUBLE_EQ(m(1,1), 5.0);
    EXPECT_DOUBLE_EQ(m(1,2), 6.0);

    EXPECT_DOUBLE_EQ(m(2,0), 7.0);
    EXPECT_DOUBLE_EQ(m(2,1), 8.0);
    EXPECT_DOUBLE_EQ(m(2,2), 9.0);

    char str2[] = { "lorem ipsum" };
    mc::MatrixMxN<double,rows,cols> m2;
    m2.SetFromString(str2);
    EXPECT_FALSE(m2.IsValid());
}

TEST_F(TestMatrixMxN, CanSwapRows)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,rows,cols> m;
    m.SetFromArray(x);
    m.SwapRows(0, 1);

    EXPECT_DOUBLE_EQ(m(1,0), 1.0);
    EXPECT_DOUBLE_EQ(m(1,1), 2.0);
    EXPECT_DOUBLE_EQ(m(1,2), 3.0);

    EXPECT_DOUBLE_EQ(m(0,0), 4.0);
    EXPECT_DOUBLE_EQ(m(0,1), 5.0);
    EXPECT_DOUBLE_EQ(m(0,2), 6.0);

    EXPECT_DOUBLE_EQ(m(2,0), 7.0);
    EXPECT_DOUBLE_EQ(m(2,1), 8.0);
    EXPECT_DOUBLE_EQ(m(2,2), 9.0);
}

TEST_F(TestMatrixMxN, CanConvertToString)
{
    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,3,3> m;
    m.SetFromArray(x);
    EXPECT_STREQ(m.ToString().c_str(), "1\t2\t3\t\n4\t5\t6\t\n7\t8\t9");
}

TEST_F(TestMatrixMxN, CanAccessItem)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    mc::MatrixMxN<double,rows,cols> m;
    m(0,0) = 1.0;
    m(1,1) = 2.0;
    m(2,2) = 3.0;
    m(0,2) = 9.0;

    mc::MatrixMxN<double,rows,cols> mr(m);
    EXPECT_DOUBLE_EQ(mr(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mr(1,1), 2.0);
    EXPECT_DOUBLE_EQ(mr(2,2), 3.0);
    EXPECT_DOUBLE_EQ(mr(0,2), 9.0);
}

TEST_F(TestMatrixMxN, CanAdd)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,rows,cols> m1;
    mc::MatrixMxN<double,rows,cols> m2;
    mc::MatrixMxN<double,rows,cols> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 + m2;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] + val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanNegate)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,rows,cols> m1;
    mc::MatrixMxN<double,rows,cols> m2;
    mc::MatrixMxN<double,rows,cols> mr;
    m1.SetFromArray(x);
    m2.SetFromArray(x);
    mr = -m1;

        for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), -m2(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanSubstract)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,rows,cols> m1;
    mc::MatrixMxN<double,rows,cols> m2;
    mc::MatrixMxN<double,rows,cols> mr;
    m1.SetFromArray(x);
    m2.Fill(val);
    mr = m1 - m2;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] - val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanMultiplyByNumber)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,rows,cols> m1;
    mc::MatrixMxN<double,rows,cols> mr;
    m1.SetFromArray(x);
    mr = m1 * val;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] * val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanMultiplyIdentityMatrixByVector)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    mc::MatrixMxN<double,rows,cols> m;

    m(0,0) =  1.0;
    m(0,1) =  0.0;
    m(0,2) =  0.0;

    m(1,0) =  0.0;
    m(1,1) =  1.0;
    m(1,2) =  0.0;

    m(2,0) =  0.0;
    m(2,1) =  0.0;
    m(2,2) =  1.0;

    mc::VectorN<double,rows> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<double,rows> vr = m * v;
    EXPECT_DOUBLE_EQ(vr(0),  1.0);
    EXPECT_DOUBLE_EQ(vr(1),  2.0);
    EXPECT_DOUBLE_EQ(vr(2),  3.0);
}

TEST_F(TestMatrixMxN, CanMultiplyNegativeIdentityMatrixByVector)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    mc::MatrixMxN<double,rows,cols> m;

    m(0,0) = -1.0;
    m(0,1) =  0.0;
    m(0,2) =  0.0;

    m(1,0) =  0.0;
    m(1,1) = -1.0;
    m(1,2) =  0.0;

    m(2,0) =  0.0;
    m(2,1) =  0.0;
    m(2,2) = -1.0;

    mc::VectorN<double,rows> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<double,rows> vr = m * v;
    EXPECT_DOUBLE_EQ(vr(0), -1.0);
    EXPECT_DOUBLE_EQ(vr(1), -2.0);
    EXPECT_DOUBLE_EQ(vr(2), -3.0);
}

TEST_F(TestMatrixMxN, CanMultiplySkewXYMatrixByVector)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    mc::MatrixMxN<double,rows,cols> m;

    m(0,0) =  0.0;
    m(0,1) =  1.0;
    m(0,2) =  0.0;

    m(1,0) =  1.0;
    m(1,1) =  0.0;
    m(1,2) =  0.0;

    m(2,0) =  0.0;
    m(2,1) =  0.0;
    m(2,2) =  1.0;

    mc::VectorN<double,rows> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<double,rows> vr = m * v;
    EXPECT_DOUBLE_EQ(vr(0),  2.0);
    EXPECT_DOUBLE_EQ(vr(1),  1.0);
    EXPECT_DOUBLE_EQ(vr(2),  3.0);
}

TEST_F(TestMatrixMxN, CanMultiplyRandomMatrixByVector)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    mc::MatrixMxN<double,rows,cols> m3;


    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };
    mc::MatrixMxN<double,rows,cols> m;
    m.SetFromArray(x);

    mc::VectorN<double,rows> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<double,rows> vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0), 14.0);
    EXPECT_DOUBLE_EQ(vr(1), 32.0);
    EXPECT_DOUBLE_EQ(vr(2), 50.0);
}

TEST_F(TestMatrixMxN, CanDivideByNumber)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,rows,cols> m1;
    mc::MatrixMxN<double,rows,cols> mr;
    m1.SetFromArray(x);
    mr = m1 / val;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] / val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanUnaryAdd)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,rows,cols> m1;
    mc::MatrixMxN<double,rows,cols> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr += m1;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val + m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanUnarySubstract)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,rows,cols> m1;
    mc::MatrixMxN<double,rows,cols> mr;
    m1.SetFromArray(x);
    mr.Fill(val);
    mr -= m1;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val - m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanUnaryMultiplyByNumber)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,rows,cols> m;
    m.SetFromArray(x);
    m *= val;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] * val;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanUnaryDivideByNumber)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    constexpr double val = 2.0;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,rows,cols> m;
    m.SetFromArray(x);
    m /= val;

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] / val;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanCompare)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<double,rows,cols> m0;
    mc::MatrixMxN<double,rows,cols> m1;
    mc::MatrixMxN<double,rows,cols> m2;

    m1.SetFromArray(x);
    m2.SetFromArray(x);

    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m1 != m0);

    EXPECT_FALSE(m1 != m2);
    EXPECT_FALSE(m1 == m0);
}
