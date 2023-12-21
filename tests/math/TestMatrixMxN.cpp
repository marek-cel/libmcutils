#include <gtest/gtest.h>

#ifdef TEST_USING_ARMADILLO
#   include <armadillo>
#endif // TEST_USING_ARMADILLO

#include <mcutils/math/MatrixMxN.h>

#include <TestingUtils.h>

////////////////////////////////////////////////////////////////////////////////

// To achieve full test coverage of MatrixMxN template class tests have to be
// done for 3x3, 4x4 and 6x6 matrices, as template class MatrixMxN has derived 
// classes which are not templates.

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
    mc::MatrixMxN<3,3>* m = nullptr;
    EXPECT_NO_THROW((m = new mc::MatrixMxN<3,3>()));
    delete m;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanDestruct)
{
    mc::MatrixMxN<3,3>* m3 = new mc::MatrixMxN<3,3>();
    EXPECT_NO_THROW(delete m3);

    mc::MatrixMxN<4,4>* m4 = new mc::MatrixMxN<4,4>();
    EXPECT_NO_THROW(delete m4);

    mc::MatrixMxN<6,6>* m6 = new mc::MatrixMxN<6,6>();
    EXPECT_NO_THROW(delete m6);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanInstantiate3x3)
{
    mc::MatrixMxN<3,3> m1;

    EXPECT_DOUBLE_EQ(m1(0,0), 0.0);
    EXPECT_DOUBLE_EQ(m1(0,1), 0.0);
    EXPECT_DOUBLE_EQ(m1(0,2), 0.0);

    EXPECT_DOUBLE_EQ(m1(1,0), 0.0);
    EXPECT_DOUBLE_EQ(m1(1,1), 0.0);
    EXPECT_DOUBLE_EQ(m1(1,2), 0.0);

    EXPECT_DOUBLE_EQ(m1(2,0), 0.0);
    EXPECT_DOUBLE_EQ(m1(2,1), 0.0);
    EXPECT_DOUBLE_EQ(m1(2,2), 0.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanFill3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;
    constexpr double val = 666.0;

    mc::MatrixMxN<rows,cols> mat;
    mat.Fill(val);

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mat(r,c), val);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanFill4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;
    constexpr double val = 666.0;

    mc::MatrixMxN<rows,cols> mat;
    mat.Fill(val);

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mat(r,c), val);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanFill6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;
    constexpr double val = 666.0;

    mc::MatrixMxN<rows,cols> mat;
    mat.Fill(val);

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mat(r,c), val);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanValidate3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;
    
    double x[] = { 1.0, 2.0, 3.0,
                   4.0, 5.0, 6.0,
                   7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m1;
    EXPECT_TRUE(m1.IsValid());

    mc::MatrixMxN<rows,cols> m2;
    m2.SetFromArray(x);
    EXPECT_TRUE(m2.IsValid());

    mc::MatrixMxN<rows,cols> m3;
    m3.SetFromArray(x);
    m3(0,0) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(m3.IsValid());

    mc::MatrixMxN<rows,cols> m4;
    m4.SetFromArray(x);
    m4(1,1) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(m4.IsValid());

    mc::MatrixMxN<rows,cols> m5;
    m5.Fill(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(m5.IsValid());
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanValidate4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m1;
    EXPECT_TRUE(m1.IsValid());

    mc::MatrixMxN<rows,cols> m2;
    m2.SetFromArray(x);
    EXPECT_TRUE(m2.IsValid());

    mc::MatrixMxN<rows,cols> m3;
    m3.SetFromArray(x);
    m3(0,0) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(m3.IsValid());

    mc::MatrixMxN<rows,cols> m4;
    m4.SetFromArray(x);
    m4(1,1) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(m4.IsValid());

    mc::MatrixMxN<rows,cols> m5;
    m5.Fill(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(m5.IsValid());
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanValidate6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixMxN<rows,cols> m1;
    EXPECT_TRUE(m1.IsValid());

    mc::MatrixMxN<rows,cols> m2;
    m2.SetFromArray(x);
    EXPECT_TRUE(m2.IsValid());

    mc::MatrixMxN<rows,cols> m3;
    m3.SetFromArray(x);
    m3(0,0) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(m3.IsValid());

    mc::MatrixMxN<rows,cols> m4;
    m4.SetFromArray(x);
    m4(1,1) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(m4.IsValid());

    mc::MatrixMxN<rows,cols> m5;
    m5.Fill(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(m5.IsValid());
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanGetElement3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    double x[] = { 1.0, 2.0, 3.0,
                   4.0, 5.0, 6.0,
                   7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);

    EXPECT_DOUBLE_EQ(m.GetElement(0,0), x[0]);
    EXPECT_DOUBLE_EQ(m.GetElement(0,1), x[1]);
    EXPECT_DOUBLE_EQ(m.GetElement(0,2), x[2]);

    EXPECT_DOUBLE_EQ(m.GetElement(1,0), x[3]);
    EXPECT_DOUBLE_EQ(m.GetElement(1,1), x[4]);
    EXPECT_DOUBLE_EQ(m.GetElement(1,2), x[5]);
    
    EXPECT_DOUBLE_EQ(m.GetElement(2,0), x[6]);
    EXPECT_DOUBLE_EQ(m.GetElement(2,1), x[7]);
    EXPECT_DOUBLE_EQ(m.GetElement(2,2), x[8]);

    double r23 = m.GetElement(2,3);
    double r32 = m.GetElement(3,2);

    EXPECT_FALSE(r23 == r23); // NaN
    EXPECT_FALSE(r32 == r32); // NaN
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanGetElement4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);

    EXPECT_DOUBLE_EQ(m.GetElement(0,0), x[0]);
    EXPECT_DOUBLE_EQ(m.GetElement(0,1), x[1]);
    EXPECT_DOUBLE_EQ(m.GetElement(0,2), x[2]);
    EXPECT_DOUBLE_EQ(m.GetElement(0,3), x[3]);

    EXPECT_DOUBLE_EQ(m.GetElement(1,0), x[4]);
    EXPECT_DOUBLE_EQ(m.GetElement(1,1), x[5]);
    EXPECT_DOUBLE_EQ(m.GetElement(1,2), x[6]);
    EXPECT_DOUBLE_EQ(m.GetElement(1,3), x[7]);
    
    EXPECT_DOUBLE_EQ(m.GetElement(2,0), x[8]);
    EXPECT_DOUBLE_EQ(m.GetElement(2,1), x[9]);
    EXPECT_DOUBLE_EQ(m.GetElement(2,2), x[10]);
    EXPECT_DOUBLE_EQ(m.GetElement(2,3), x[11]);
    
    EXPECT_DOUBLE_EQ(m.GetElement(3,0), x[12]);
    EXPECT_DOUBLE_EQ(m.GetElement(3,1), x[13]);
    EXPECT_DOUBLE_EQ(m.GetElement(3,2), x[14]);
    EXPECT_DOUBLE_EQ(m.GetElement(3,3), x[15]);

    double r24 = m.GetElement(2,4);
    double r42 = m.GetElement(4,2);

    EXPECT_FALSE(r24 == r24); // NaN
    EXPECT_FALSE(r42 == r42); // NaN
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanGetElement6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);

    // only diagonal
    EXPECT_DOUBLE_EQ(m.GetElement(0,0), x[0]);
    EXPECT_DOUBLE_EQ(m.GetElement(1,1), x[7]);
    EXPECT_DOUBLE_EQ(m.GetElement(2,2), x[14]);
    EXPECT_DOUBLE_EQ(m.GetElement(3,3), x[21]);
    EXPECT_DOUBLE_EQ(m.GetElement(4,4), x[28]);
    EXPECT_DOUBLE_EQ(m.GetElement(5,5), x[35]);

    double r26 = m.GetElement(2,6);
    double r62 = m.GetElement(6,2);

    EXPECT_FALSE(r26 == r26); // NaN
    EXPECT_FALSE(r62 == r62); // NaN
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanPutIntoArray3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };
    double xx[rows * cols] = { 0.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);
    m.PutIntoArray(xx);

    for ( int i = 0; i < rows * cols; ++i )
    {
        EXPECT_DOUBLE_EQ(xx[i], x[i]) << "Error at index " << i;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanPutIntoArray4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };
    double xx[rows * cols] = { 0.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);
    m.PutIntoArray(xx);

    for ( int i = 0; i < rows * cols; ++i )
    {
        EXPECT_DOUBLE_EQ(xx[i], x[i]) << "Error at index " << i;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanPutIntoArray6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };
    double xx[rows * cols] = { 0.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);
    m.PutIntoArray(xx);

    for ( int i = 0; i < rows * cols; ++i )
    {
        EXPECT_DOUBLE_EQ(xx[i], x[i]) << "Error at index " << i;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSetElement3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    mc::MatrixMxN<rows,cols> m;

    m.SetElement(0, 0, 1.0);
    m.SetElement(1, 1, 2.0);
    m.SetElement(2, 2, 3.0);
    m.SetElement(0, 2, 9.0);

    EXPECT_DOUBLE_EQ(m(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m(1,1), 2.0);
    EXPECT_DOUBLE_EQ(m(2,2), 3.0);
    EXPECT_DOUBLE_EQ(m(0,2), 9.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSetElement4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    mc::MatrixMxN<rows,cols> m;

    m.SetElement(0, 0, 1.0);
    m.SetElement(1, 1, 2.0);
    m.SetElement(2, 2, 3.0);
    m.SetElement(3, 3, 4.0);
    m.SetElement(0, 3, 9.0);

    EXPECT_DOUBLE_EQ(m(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m(1,1), 2.0);
    EXPECT_DOUBLE_EQ(m(2,2), 3.0);
    EXPECT_DOUBLE_EQ(m(3,3), 4.0);
    EXPECT_DOUBLE_EQ(m(0,3), 9.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSetElement6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    mc::MatrixMxN<rows,cols> m;

    m.SetElement(0, 0, 1.0);
    m.SetElement(1, 1, 2.0);
    m.SetElement(2, 2, 3.0);
    m.SetElement(3, 3, 4.0);
    m.SetElement(4, 4, 5.0);
    m.SetElement(5, 5, 6.0);
    m.SetElement(0, 5, 9.0);

    EXPECT_DOUBLE_EQ(m(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m(1,1), 2.0);
    EXPECT_DOUBLE_EQ(m(2,2), 3.0);
    EXPECT_DOUBLE_EQ(m(3,3), 4.0);
    EXPECT_DOUBLE_EQ(m(4,4), 5.0);
    EXPECT_DOUBLE_EQ(m(5,5), 6.0);
    EXPECT_DOUBLE_EQ(m(0,5), 9.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSetFromArray)
{
    mc::MatrixMxN<3,3> m1;

    double elements[] = { 1.0, 2.0, 3.0,
                          4.0, 5.0, 6.0,
                          7.0, 8.0, 9.0 };

    m1.SetFromArray(elements);

    EXPECT_DOUBLE_EQ(m1(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m1(0,1), 2.0);
    EXPECT_DOUBLE_EQ(m1(0,2), 3.0);
    
    EXPECT_DOUBLE_EQ(m1(1,0), 4.0);
    EXPECT_DOUBLE_EQ(m1(1,1), 5.0);
    EXPECT_DOUBLE_EQ(m1(1,2), 6.0);
    
    EXPECT_DOUBLE_EQ(m1(2,0), 7.0);
    EXPECT_DOUBLE_EQ(m1(2,1), 8.0);
    EXPECT_DOUBLE_EQ(m1(2,2), 9.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSetFromString3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    char str[] =
    { R"##(
        1.0 2.0 3.0
        4.0 5.0 6.0
        7.0 8.0 9.0
    )##" };

    mc::MatrixMxN<rows,cols> m;
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
    mc::MatrixMxN<rows,cols> m2;
    m2.SetFromString(str2);
    EXPECT_FALSE(m2.IsValid());
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSetFromString4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    char str[] =
    { R"##(
     11.0  12.0  13.0  14.0
     21.0  22.0  23.0  24.0
     31.0  32.0  33.0  34.0
     41.0  42.0  43.0  44.0
    )##" };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromString(str);

    EXPECT_DOUBLE_EQ(m(0,0),  11.0);
    EXPECT_DOUBLE_EQ(m(0,1),  12.0);
    EXPECT_DOUBLE_EQ(m(0,2),  13.0);
    EXPECT_DOUBLE_EQ(m(0,3),  14.0);

    EXPECT_DOUBLE_EQ(m(1,0),  21.0);
    EXPECT_DOUBLE_EQ(m(1,1),  22.0);
    EXPECT_DOUBLE_EQ(m(1,2),  23.0);
    EXPECT_DOUBLE_EQ(m(1,3),  24.0);

    EXPECT_DOUBLE_EQ(m(2,0),  31.0);
    EXPECT_DOUBLE_EQ(m(2,1),  32.0);
    EXPECT_DOUBLE_EQ(m(2,2),  33.0);
    EXPECT_DOUBLE_EQ(m(2,3),  34.0);

    EXPECT_DOUBLE_EQ(m(3,0),  41.0);
    EXPECT_DOUBLE_EQ(m(3,1),  42.0);
    EXPECT_DOUBLE_EQ(m(3,2),  43.0);
    EXPECT_DOUBLE_EQ(m(3,3),  44.0);

    char str2[] = { "lorem ipsum" };
    mc::MatrixMxN<rows,cols> m2;
    m2.SetFromString(str2);
    EXPECT_FALSE(m2.IsValid());
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSetFromString6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    char str[] =
    { R"##(
     11.0  12.0  13.0  14.0  15.0  16.0
     21.0  22.0  23.0  24.0  25.0  26.0
     31.0  32.0  33.0  34.0  35.0  36.0
     41.0  42.0  43.0  44.0  45.0  46.0
     51.0  52.0  53.0  54.0  55.0  56.0
     61.0  62.0  63.0  64.0  65.0  66.0
    )##" };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromString(str);

    EXPECT_DOUBLE_EQ(m(0,0), 11.0);
    EXPECT_DOUBLE_EQ(m(0,1), 12.0);
    EXPECT_DOUBLE_EQ(m(0,2), 13.0);
    EXPECT_DOUBLE_EQ(m(0,3), 14.0);
    EXPECT_DOUBLE_EQ(m(0,4), 15.0);
    EXPECT_DOUBLE_EQ(m(0,5), 16.0);

    EXPECT_DOUBLE_EQ(m(1,0), 21.0);
    EXPECT_DOUBLE_EQ(m(1,1), 22.0);
    EXPECT_DOUBLE_EQ(m(1,2), 23.0);
    EXPECT_DOUBLE_EQ(m(1,3), 24.0);
    EXPECT_DOUBLE_EQ(m(1,4), 25.0);
    EXPECT_DOUBLE_EQ(m(1,5), 26.0);

    EXPECT_DOUBLE_EQ(m(2,0), 31.0);
    EXPECT_DOUBLE_EQ(m(2,1), 32.0);
    EXPECT_DOUBLE_EQ(m(2,2), 33.0);
    EXPECT_DOUBLE_EQ(m(2,3), 34.0);
    EXPECT_DOUBLE_EQ(m(2,4), 35.0);
    EXPECT_DOUBLE_EQ(m(2,5), 36.0);

    EXPECT_DOUBLE_EQ(m(3,0), 41.0);
    EXPECT_DOUBLE_EQ(m(3,1), 42.0);
    EXPECT_DOUBLE_EQ(m(3,2), 43.0);
    EXPECT_DOUBLE_EQ(m(3,3), 44.0);
    EXPECT_DOUBLE_EQ(m(3,4), 45.0);
    EXPECT_DOUBLE_EQ(m(3,5), 46.0);

    EXPECT_DOUBLE_EQ(m(4,0), 51.0);
    EXPECT_DOUBLE_EQ(m(4,1), 52.0);
    EXPECT_DOUBLE_EQ(m(4,2), 53.0);
    EXPECT_DOUBLE_EQ(m(4,3), 54.0);
    EXPECT_DOUBLE_EQ(m(4,4), 55.0);
    EXPECT_DOUBLE_EQ(m(4,5), 56.0);

    EXPECT_DOUBLE_EQ(m(5,0), 61.0);
    EXPECT_DOUBLE_EQ(m(5,1), 62.0);
    EXPECT_DOUBLE_EQ(m(5,2), 63.0);
    EXPECT_DOUBLE_EQ(m(5,3), 64.0);
    EXPECT_DOUBLE_EQ(m(5,4), 65.0);
    EXPECT_DOUBLE_EQ(m(5,5), 66.0);

    char str2[] = { "lorem ipsum" };
    mc::MatrixMxN<rows,cols> m2;
    m2.SetFromString(str2);
    EXPECT_FALSE(m2.IsValid());
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSwapRows3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);

    EXPECT_DOUBLE_EQ(m(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m(0,1), 2.0);
    EXPECT_DOUBLE_EQ(m(0,2), 3.0);

    EXPECT_DOUBLE_EQ(m(1,0), 4.0);
    EXPECT_DOUBLE_EQ(m(1,1), 5.0);
    EXPECT_DOUBLE_EQ(m(1,2), 6.0);
    
    EXPECT_DOUBLE_EQ(m(2,0), 7.0);
    EXPECT_DOUBLE_EQ(m(2,1), 8.0);
    EXPECT_DOUBLE_EQ(m(2,2), 9.0);

    mc::MatrixMxN<rows,cols> m01(m);
    m01.SwapRows(0, 1);

    EXPECT_DOUBLE_EQ(m01(1,0), 1.0);
    EXPECT_DOUBLE_EQ(m01(1,1), 2.0);
    EXPECT_DOUBLE_EQ(m01(1,2), 3.0);

    EXPECT_DOUBLE_EQ(m01(0,0), 4.0);
    EXPECT_DOUBLE_EQ(m01(0,1), 5.0);
    EXPECT_DOUBLE_EQ(m01(0,2), 6.0);
    
    EXPECT_DOUBLE_EQ(m01(2,0), 7.0);
    EXPECT_DOUBLE_EQ(m01(2,1), 8.0);
    EXPECT_DOUBLE_EQ(m01(2,2), 9.0);

    mc::MatrixMxN<rows,cols> m02(m);
    m02.SwapRows(0, 2);

    EXPECT_DOUBLE_EQ(m02(2,0), 1.0);
    EXPECT_DOUBLE_EQ(m02(2,1), 2.0);
    EXPECT_DOUBLE_EQ(m02(2,2), 3.0);

    EXPECT_DOUBLE_EQ(m02(1,0), 4.0);
    EXPECT_DOUBLE_EQ(m02(1,1), 5.0);
    EXPECT_DOUBLE_EQ(m02(1,2), 6.0);
    
    EXPECT_DOUBLE_EQ(m02(0,0), 7.0);
    EXPECT_DOUBLE_EQ(m02(0,1), 8.0);
    EXPECT_DOUBLE_EQ(m02(0,2), 9.0);

    mc::MatrixMxN<rows,cols> m12(m);
    m12.SwapRows(1, 2);

    EXPECT_DOUBLE_EQ(m12(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m12(0,1), 2.0);
    EXPECT_DOUBLE_EQ(m12(0,2), 3.0);

    EXPECT_DOUBLE_EQ(m12(2,0), 4.0);
    EXPECT_DOUBLE_EQ(m12(2,1), 5.0);
    EXPECT_DOUBLE_EQ(m12(2,2), 6.0);
    
    EXPECT_DOUBLE_EQ(m12(1,0), 7.0);
    EXPECT_DOUBLE_EQ(m12(1,1), 8.0);
    EXPECT_DOUBLE_EQ(m12(1,2), 9.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSwapRows4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);
    m.SwapRows(0,1);

    EXPECT_DOUBLE_EQ(m(0,0), 21.0);
    EXPECT_DOUBLE_EQ(m(0,1), 22.0);
    EXPECT_DOUBLE_EQ(m(0,2), 23.0);
    EXPECT_DOUBLE_EQ(m(0,3), 24.0);

    EXPECT_DOUBLE_EQ(m(1,0), 11.0);
    EXPECT_DOUBLE_EQ(m(1,1), 12.0);
    EXPECT_DOUBLE_EQ(m(1,2), 13.0);
    EXPECT_DOUBLE_EQ(m(1,3), 14.0);

    EXPECT_DOUBLE_EQ(m(2,0), 31.0);
    EXPECT_DOUBLE_EQ(m(2,1), 32.0);
    EXPECT_DOUBLE_EQ(m(2,2), 33.0);
    EXPECT_DOUBLE_EQ(m(2,3), 34.0);

    EXPECT_DOUBLE_EQ(m(3,0), 41.0);
    EXPECT_DOUBLE_EQ(m(3,1), 42.0);
    EXPECT_DOUBLE_EQ(m(3,2), 43.0);
    EXPECT_DOUBLE_EQ(m(3,3), 44.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSwapRows6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixMxN<rows,cols> m;
    m.SetFromArray(x);
    m.SwapRows(0,1);

    EXPECT_DOUBLE_EQ(m(0,0), 21.0);
    EXPECT_DOUBLE_EQ(m(0,1), 22.0);
    EXPECT_DOUBLE_EQ(m(0,2), 23.0);
    EXPECT_DOUBLE_EQ(m(0,3), 24.0);
    EXPECT_DOUBLE_EQ(m(0,4), 25.0);
    EXPECT_DOUBLE_EQ(m(0,5), 26.0);

    EXPECT_DOUBLE_EQ(m(1,0), 11.0);
    EXPECT_DOUBLE_EQ(m(1,1), 12.0);
    EXPECT_DOUBLE_EQ(m(1,2), 13.0);
    EXPECT_DOUBLE_EQ(m(1,3), 14.0);
    EXPECT_DOUBLE_EQ(m(1,4), 15.0);
    EXPECT_DOUBLE_EQ(m(1,5), 16.0);

    EXPECT_DOUBLE_EQ(m(2,0), 31.0);
    EXPECT_DOUBLE_EQ(m(2,1), 32.0);
    EXPECT_DOUBLE_EQ(m(2,2), 33.0);
    EXPECT_DOUBLE_EQ(m(2,3), 34.0);
    EXPECT_DOUBLE_EQ(m(2,4), 35.0);
    EXPECT_DOUBLE_EQ(m(2,5), 36.0);

    EXPECT_DOUBLE_EQ(m(3,0), 41.0);
    EXPECT_DOUBLE_EQ(m(3,1), 42.0);
    EXPECT_DOUBLE_EQ(m(3,2), 43.0);
    EXPECT_DOUBLE_EQ(m(3,3), 44.0);
    EXPECT_DOUBLE_EQ(m(3,4), 45.0);
    EXPECT_DOUBLE_EQ(m(3,5), 46.0);

    EXPECT_DOUBLE_EQ(m(4,0), 51.0);
    EXPECT_DOUBLE_EQ(m(4,1), 52.0);
    EXPECT_DOUBLE_EQ(m(4,2), 53.0);
    EXPECT_DOUBLE_EQ(m(4,3), 54.0);
    EXPECT_DOUBLE_EQ(m(4,4), 55.0);
    EXPECT_DOUBLE_EQ(m(4,5), 56.0);

    EXPECT_DOUBLE_EQ(m(5,0), 61.0);
    EXPECT_DOUBLE_EQ(m(5,1), 62.0);
    EXPECT_DOUBLE_EQ(m(5,2), 63.0);
    EXPECT_DOUBLE_EQ(m(5,3), 64.0);
    EXPECT_DOUBLE_EQ(m(5,4), 65.0);
    EXPECT_DOUBLE_EQ(m(5,5), 66.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanConvertToString3x3)
{
    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<3,3> m;
    m.SetFromArray(x);
    EXPECT_STREQ(m.ToString().c_str(), "1\t2\t3\t\n4\t5\t6\t\n7\t8\t9");
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanConvertToString4x4)
{
    double x[] {  1.0,  2.0,  3.0,  4.0,
                  5.0,  6.0,  7.0,  8.0,
                  9.0, 10.0, 11.0, 12.0,
                 13.0, 14.0, 15.0, 16.0 };

    mc::MatrixMxN<4,4> m;
    m.SetFromArray(x);
    EXPECT_STREQ(m.ToString().c_str(), "1\t2\t3\t4\t\n5\t6\t7\t8\t\n9\t10\t11\t12\t\n13\t14\t15\t16");
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanConvertToString6x6)
{
    double x[] {  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
                  7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
                 13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                 19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
                 31.0, 32.0, 33.0, 34.0, 35.0, 36.0 };

    mc::MatrixMxN<6,6> m;
    m.SetFromArray(x);
    EXPECT_STREQ(m.ToString().c_str(), "1\t2\t3\t4\t5\t6\t\n7\t8\t9\t10\t11\t12\t\n13\t14\t15\t16\t17\t18\t\n19\t20\t21\t22\t23\t24\t\n25\t26\t27\t28\t29\t30\t\n31\t32\t33\t34\t35\t36");
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanAccessItem3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    mc::MatrixMxN<rows,cols> m;
    m(0,0) = 1.0;
    m(1,1) = 2.0;
    m(2,2) = 3.0;
    m(0,2) = 9.0;

    mc::MatrixMxN<rows,cols> mr(m);
    EXPECT_DOUBLE_EQ(mr(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mr(1,1), 2.0);
    EXPECT_DOUBLE_EQ(mr(2,2), 3.0);
    EXPECT_DOUBLE_EQ(mr(0,2), 9.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanAccessItem4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    mc::MatrixMxN<rows,cols> m;
    m(0,0) = 1.0;
    m(1,1) = 2.0;
    m(2,2) = 3.0;
    m(3,3) = 4.0;
    m(0,3) = 9.0;

    mc::MatrixMxN<rows,cols> mr(m);
    EXPECT_DOUBLE_EQ(mr(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mr(1,1), 2.0);
    EXPECT_DOUBLE_EQ(mr(2,2), 3.0);
    EXPECT_DOUBLE_EQ(mr(3,3), 4.0);
    EXPECT_DOUBLE_EQ(mr(0,3), 9.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanAccessItem6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    mc::MatrixMxN<rows,cols> m;
    m(0,0) = 1.0;
    m(1,1) = 2.0;
    m(2,2) = 3.0;
    m(3,3) = 4.0;
    m(4,4) = 5.0;
    m(5,5) = 6.0;
    m(0,5) = 9.0;

    mc::MatrixMxN<rows,cols> mr(m);
    EXPECT_DOUBLE_EQ(mr(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mr(1,1), 2.0);
    EXPECT_DOUBLE_EQ(mr(2,2), 3.0);
    EXPECT_DOUBLE_EQ(mr(3,3), 4.0);
    EXPECT_DOUBLE_EQ(mr(4,4), 5.0);
    EXPECT_DOUBLE_EQ(mr(5,5), 6.0);
    EXPECT_DOUBLE_EQ(mr(0,5), 9.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanAdd3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat ma2(rows, cols);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 + ma2;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] + val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanAdd4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat ma2(rows, cols);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 + ma2;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] + val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanAdd6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat ma2(rows, cols);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 + ma2;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] + val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanNegate3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> m2;
    mc::MatrixMxN<rows,cols> mr;
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

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanNegate4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> m2;
    mc::MatrixMxN<rows,cols> mr;
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

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanNegate6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

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

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSubstract3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat ma2(rows, cols);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 - ma2;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] - val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSubstract4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat ma2(rows, cols);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 - ma2;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] - val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanSubstract6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat ma2(rows, cols);
    arma::mat mar;
    ma2.fill(val);
    mar = ma1 - ma2;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] - val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanMultiplyByScalar3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar;
    mar = ma1 * scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] * scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanMultiplyByScalar4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar;
    mar = ma1 * scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] * scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanMultiplyByScalar6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar;
    mar = ma1 * scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] * scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanMultiplyByVector3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    mc::MatrixMxN<rows,cols> m1;

    m1(0,0) =  1.0;
    m1(0,1) =  0.0;
    m1(0,2) =  0.0;

    m1(1,0) =  0.0;
    m1(1,1) =  1.0;
    m1(1,2) =  0.0;

    m1(2,0) =  0.0;
    m1(2,1) =  0.0;
    m1(2,2) =  1.0;

    mc::MatrixMxN<rows,cols> m2;

    m2(0,0) = -1.0;
    m2(0,1) =  0.0;
    m2(0,2) =  0.0;

    m2(1,0) =  0.0;
    m2(1,1) = -1.0;
    m2(1,2) =  0.0;

    m2(2,0) =  0.0;
    m2(2,1) =  0.0;
    m2(2,2) = -1.0;

    mc::MatrixMxN<rows,cols> m3;

    m3(0,0) =  0.0;
    m3(0,1) =  1.0;
    m3(0,2) =  0.0;

    m3(1,0) =  1.0;
    m3(1,1) =  0.0;
    m3(1,2) =  0.0;

    m3(2,0) =  0.0;
    m3(2,1) =  0.0;
    m3(2,2) =  1.0;

    mc::MatrixMxN<rows,cols> m4;

    m4(0,0) =  1.0;
    m4(0,1) =  0.0;
    m4(0,2) =  0.0;

    m4(1,0) =  0.0;
    m4(1,1) =  0.0;
    m4(1,2) = -1.0;

    m4(2,0) =  0.0;
    m4(2,1) = -1.0;
    m4(2,2) =  0.0;

    mc::VectorN<rows> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<rows> vr1 = m1 * v;
    EXPECT_DOUBLE_EQ(vr1(0),  1.0);
    EXPECT_DOUBLE_EQ(vr1(1),  2.0);
    EXPECT_DOUBLE_EQ(vr1(2),  3.0);

    mc::VectorN<rows> vr2 = m2 * v;
    EXPECT_DOUBLE_EQ(vr2(0), -1.0);
    EXPECT_DOUBLE_EQ(vr2(1), -2.0);
    EXPECT_DOUBLE_EQ(vr2(2), -3.0);

    mc::VectorN<rows> vr3 = m3 * v;
    EXPECT_DOUBLE_EQ(vr3(0),  2.0);
    EXPECT_DOUBLE_EQ(vr3(1),  1.0);
    EXPECT_DOUBLE_EQ(vr3(2),  3.0);

    mc::VectorN<rows> vr4 = m4 * v;
    EXPECT_DOUBLE_EQ(vr4(0),  1.0);
    EXPECT_DOUBLE_EQ(vr4(1), -3.0);
    EXPECT_DOUBLE_EQ(vr4(2), -2.0);

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };
    mc::MatrixMxN<rows,cols> m5;
    m5.SetFromArray(x);

    mc::VectorN<rows> vr5 = m5 * v;

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::vec va;
    va << 1.0 << arma::endr
       << 2.0 << arma::endr
       << 3.0 << arma::endr;
    arma::vec var;
    var = ma1 * va;

    for ( int r = 0; r < rows; ++r )
    {
        EXPECT_DOUBLE_EQ(vr5(r), var(r)) << "Error at row " << r;
    }
#   endif // TEST_USING_ARMADILLO

    // Following tests uses expected values calculated with GNU Octave
    // tests/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr5(0), 14.0);
    EXPECT_DOUBLE_EQ(vr5(1), 32.0);
    EXPECT_DOUBLE_EQ(vr5(2), 50.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanMultiplyByVector4)
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

#   ifdef TEST_USING_ARMADILLO
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
#   endif // TEST_USING_ARMADILLO

    // Following tests uses expected values calculated with GNU Octave
    // tests/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0),  30.0);
    EXPECT_DOUBLE_EQ(vr(1),  70.0);
    EXPECT_DOUBLE_EQ(vr(2), 110.0);
    EXPECT_DOUBLE_EQ(vr(3), 150.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanMultiplyByVector6)
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

#   ifdef TEST_USING_ARMADILLO
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
#   endif // TEST_USING_ARMADILLO

    // Following tests uses expected values calculated with GNU Octave
    // tests/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0),  91.0);
    EXPECT_DOUBLE_EQ(vr(1), 217.0);
    EXPECT_DOUBLE_EQ(vr(2), 343.0);
    EXPECT_DOUBLE_EQ(vr(3), 469.0);
    EXPECT_DOUBLE_EQ(vr(4), 595.0);
    EXPECT_DOUBLE_EQ(vr(5), 721.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanDivideByScalar3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar;
    mar = ma1 / scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] / scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanDivideByScalar4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar;
    mar = ma1 / scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] / scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanDivideByScalar6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar;
    mar = ma1 / scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] / scalar;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnaryAdd3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar(rows, cols, arma::fill::zeros);
    mar.fill(val);
    mar += ma1;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val + m1(r,c)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnaryAdd4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar(rows, cols, arma::fill::zeros);
    mar.fill(val);
    mar += ma1;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val + m1(r,c)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnaryAdd6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar(rows, cols, arma::fill::zeros);
    mar.fill(val);
    mar += ma1;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val + m1(r,c)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnarySubstract3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar(rows, cols, arma::fill::zeros);
    mar.fill(val);
    mar -= ma1;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val - m1(r,c)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnarySubstract4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar(rows, cols, arma::fill::zeros);
    mar.fill(val);
    mar -= ma1;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val - m1(r,c)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnarySubstract6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma1 = SetArmaMatFromArray(x, rows, cols);
    arma::mat mar(rows, cols, arma::fill::zeros);
    mar.fill(val);
    mar -= ma1;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val - m1(r,c)) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(mr(r,c), mar(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnaryMultiplyByScalar3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    ma *= scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] * scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnaryMultiplyByScalar4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    ma *= scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] * scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnaryMultiplyByScalar6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    ma *= scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] * scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnaryDivideByScalar3x3)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    ma /= scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] / scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnaryDivideByScalar4x4)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    ma /= scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] / scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanUnaryDivideByScalar6x6)
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

#   ifdef TEST_USING_ARMADILLO
    arma::mat ma = SetArmaMatFromArray(x, rows, cols);
    ma /= scalar;
#   endif // TEST_USING_ARMADILLO

    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            double ref_value = x[r*cols + c] / scalar;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
#           ifdef TEST_USING_ARMADILLO
            EXPECT_DOUBLE_EQ(m(r,c), ma(r,c)) << "Error at row " << r << " and col " << c;
#           endif // TEST_USING_ARMADILLO
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanCompare3x3)
{
    constexpr int rows = 3;
    constexpr int cols = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::MatrixMxN<rows,cols> m0;
    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> m2;

    m1.SetFromArray(x);
    m2.SetFromArray(x);

    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m1 != m0);
    
    EXPECT_FALSE(m1 != m2);
    EXPECT_FALSE(m1 == m0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanCompare4x4)
{
    constexpr int rows = 4;
    constexpr int cols = 4;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::MatrixMxN<rows,cols> m0;
    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> m2;

    m1.SetFromArray(x);
    m2.SetFromArray(x);

    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m1 != m0);
    
    EXPECT_FALSE(m1 != m2);
    EXPECT_FALSE(m1 == m0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrixMxN, CanCompare6x6)
{
    constexpr int rows = 6;
    constexpr int cols = 6;

    double x[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                   21.0, 22.0, 23.0, 24.0, 25.0, 26.0,
                   31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
                   41.0, 42.0, 43.0, 44.0, 45.0, 46.0,
                   51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                   61.0, 62.0, 63.0, 64.0, 65.0, 66.0 };

    mc::MatrixMxN<rows,cols> m0;
    mc::MatrixMxN<rows,cols> m1;
    mc::MatrixMxN<rows,cols> m2;

    m1.SetFromArray(x);
    m2.SetFromArray(x);

    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m1 != m0);
    
    EXPECT_FALSE(m1 != m2);
    EXPECT_FALSE(m1 == m0);
}
