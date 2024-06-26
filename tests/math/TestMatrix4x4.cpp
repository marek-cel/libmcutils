#include <gtest/gtest.h>

#include <mcutils/math/Matrix4x4.h>

class TestMatrix4x4 : public ::testing::Test
{
protected:
    constexpr static int size = 4;
    TestMatrix4x4() {}
    virtual ~TestMatrix4x4() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMatrix4x4, CanInstantiate)
{
    mc::Matrix4x4 m;
    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix4x4, CanInstantiateAndCopy)
{
    constexpr int size = 4;

    double x[] = { 11.0, 12.0, 13.0, 14.0,
                   21.0, 22.0, 23.0, 24.0,
                   31.0, 32.0, 33.0, 34.0,
                   41.0, 42.0, 43.0, 44.0 };

    mc::Matrix4x4 m0;
    m0.SetFromArray(x);

    mc::Matrix4x4 m1(m0);

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix4x4, CanGetTransposed)
{
    constexpr int size = 4;

    double x[] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };

    mc::Matrix4x4 m0;
    m0.SetFromArray(x);

    mc::Matrix4x4 m1(m0);
    mc::Matrix4x4 mt = m1.GetTransposed();

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
            EXPECT_DOUBLE_EQ(mt(r,c), m0(c,r)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix4x4, CanAdd)
{
    double elements[] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };

    mc::Matrix4x4 m0;
    mc::Matrix4x4 m1;
    m1.SetFromArray(elements);

    mc::Matrix4x4 m2 = m0 + m1;

    EXPECT_DOUBLE_EQ(m2(0,0),  1.0);
    EXPECT_DOUBLE_EQ(m2(0,1),  2.0);
    EXPECT_DOUBLE_EQ(m2(0,2),  3.0);
    EXPECT_DOUBLE_EQ(m2(0,3),  4.0);
    EXPECT_DOUBLE_EQ(m2(1,0),  5.0);
    EXPECT_DOUBLE_EQ(m2(1,1),  6.0);
    EXPECT_DOUBLE_EQ(m2(1,2),  7.0);
    EXPECT_DOUBLE_EQ(m2(1,3),  8.0);
    EXPECT_DOUBLE_EQ(m2(2,0),  9.0);
    EXPECT_DOUBLE_EQ(m2(2,1), 10.0);
    EXPECT_DOUBLE_EQ(m2(2,2), 11.0);
    EXPECT_DOUBLE_EQ(m2(2,3), 12.0);
    EXPECT_DOUBLE_EQ(m2(3,0), 13.0);
    EXPECT_DOUBLE_EQ(m2(3,1), 14.0);
    EXPECT_DOUBLE_EQ(m2(3,2), 15.0);
    EXPECT_DOUBLE_EQ(m2(3,3), 16.0);
}

TEST_F(TestMatrix4x4, CanNegate)
{
    double elements[] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };

    mc::Matrix4x4 m1;
    m1.SetFromArray(elements);

    mc::Matrix4x4 m2 = -m1;

    EXPECT_DOUBLE_EQ(m2(0,0),  -1.0);
    EXPECT_DOUBLE_EQ(m2(0,1),  -2.0);
    EXPECT_DOUBLE_EQ(m2(0,2),  -3.0);
    EXPECT_DOUBLE_EQ(m2(0,3),  -4.0);
    EXPECT_DOUBLE_EQ(m2(1,0),  -5.0);
    EXPECT_DOUBLE_EQ(m2(1,1),  -6.0);
    EXPECT_DOUBLE_EQ(m2(1,2),  -7.0);
    EXPECT_DOUBLE_EQ(m2(1,3),  -8.0);
    EXPECT_DOUBLE_EQ(m2(2,0),  -9.0);
    EXPECT_DOUBLE_EQ(m2(2,1), -10.0);
    EXPECT_DOUBLE_EQ(m2(2,2), -11.0);
    EXPECT_DOUBLE_EQ(m2(2,3), -12.0);
    EXPECT_DOUBLE_EQ(m2(3,0), -13.0);
    EXPECT_DOUBLE_EQ(m2(3,1), -14.0);
    EXPECT_DOUBLE_EQ(m2(3,2), -15.0);
    EXPECT_DOUBLE_EQ(m2(3,3), -16.0);
}

TEST_F(TestMatrix4x4, CanSubstract)
{
    double elements[] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };

    mc::Matrix4x4 m0;
    mc::Matrix4x4 m1;
    m1.SetFromArray(elements);

    mc::Matrix4x4 m2 = m0 - m1;

    EXPECT_DOUBLE_EQ(m2(0,0), -  1.0);
    EXPECT_DOUBLE_EQ(m2(0,1), -  2.0);
    EXPECT_DOUBLE_EQ(m2(0,2), -  3.0);
    EXPECT_DOUBLE_EQ(m2(0,3), -  4.0);
    EXPECT_DOUBLE_EQ(m2(1,0), -  5.0);
    EXPECT_DOUBLE_EQ(m2(1,1), -  6.0);
    EXPECT_DOUBLE_EQ(m2(1,2), -  7.0);
    EXPECT_DOUBLE_EQ(m2(1,3), -  8.0);
    EXPECT_DOUBLE_EQ(m2(2,0), -  9.0);
    EXPECT_DOUBLE_EQ(m2(2,1), - 10.0);
    EXPECT_DOUBLE_EQ(m2(2,2), - 11.0);
    EXPECT_DOUBLE_EQ(m2(2,3), - 12.0);
    EXPECT_DOUBLE_EQ(m2(3,0), - 13.0);
    EXPECT_DOUBLE_EQ(m2(3,1), - 14.0);
    EXPECT_DOUBLE_EQ(m2(3,2), - 15.0);
    EXPECT_DOUBLE_EQ(m2(3,3), - 16.0);
}

TEST_F(TestMatrix4x4, CanMultiplyByScalar)
{
    double elements[] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };

    mc::Matrix4x4 m1;
    m1.SetFromArray(elements);

    mc::Matrix4x4 m = m1 * 2.0;

    EXPECT_DOUBLE_EQ(m(0,0),  2.0);
    EXPECT_DOUBLE_EQ(m(0,1),  4.0);
    EXPECT_DOUBLE_EQ(m(0,2),  6.0);
    EXPECT_DOUBLE_EQ(m(0,3),  8.0);
    EXPECT_DOUBLE_EQ(m(1,0), 10.0);
    EXPECT_DOUBLE_EQ(m(1,1), 12.0);
    EXPECT_DOUBLE_EQ(m(1,2), 14.0);
    EXPECT_DOUBLE_EQ(m(1,3), 16.0);
    EXPECT_DOUBLE_EQ(m(2,0), 18.0);
    EXPECT_DOUBLE_EQ(m(2,1), 20.0);
    EXPECT_DOUBLE_EQ(m(2,2), 22.0);
    EXPECT_DOUBLE_EQ(m(2,3), 24.0);
    EXPECT_DOUBLE_EQ(m(3,0), 26.0);
    EXPECT_DOUBLE_EQ(m(3,1), 28.0);
    EXPECT_DOUBLE_EQ(m(3,2), 30.0);
    EXPECT_DOUBLE_EQ(m(3,3), 32.0);
}

TEST_F(TestMatrix4x4, CanMultiplyByMatrix)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix4x4.m

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

    mc::Matrix4x4 m1;
    mc::Matrix4x4 m2;

    m1.SetFromArray(x1);
    m2.SetFromArray(x2);

    mc::Matrix4x4 m = m1 * m2;

    EXPECT_DOUBLE_EQ(m(0,0), 100.0);
    EXPECT_DOUBLE_EQ(m(0,1), 110.0);
    EXPECT_DOUBLE_EQ(m(0,2), 120.0);
    EXPECT_DOUBLE_EQ(m(0,3), 130.0);
    EXPECT_DOUBLE_EQ(m(1,0), 228.0);
    EXPECT_DOUBLE_EQ(m(1,1), 254.0);
    EXPECT_DOUBLE_EQ(m(1,2), 280.0);
    EXPECT_DOUBLE_EQ(m(1,3), 306.0);
    EXPECT_DOUBLE_EQ(m(2,0), 356.0);
    EXPECT_DOUBLE_EQ(m(2,1), 398.0);
    EXPECT_DOUBLE_EQ(m(2,2), 440.0);
    EXPECT_DOUBLE_EQ(m(2,3), 482.0);
    EXPECT_DOUBLE_EQ(m(3,0), 484.0);
    EXPECT_DOUBLE_EQ(m(3,1), 542.0);
    EXPECT_DOUBLE_EQ(m(3,2), 600.0);
    EXPECT_DOUBLE_EQ(m(3,3), 658.0);
}

TEST_F(TestMatrix4x4, CanMultiplyByVector)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix4x4.m

    double x1[] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };

    double x2[] = {
         1.0,  2.0,  3.0,  4.0
    };

    mc::Matrix4x4 m1;
    m1.SetFromArray(x1);

    mc::Vector4 v2;
    v2.SetFromArray(x2);

    mc::Vector4 v = m1 * v2;

    EXPECT_DOUBLE_EQ(v(0),  30.0);
    EXPECT_DOUBLE_EQ(v(1),  70.0);
    EXPECT_DOUBLE_EQ(v(2), 110.0);
    EXPECT_DOUBLE_EQ(v(3), 150.0);
}

TEST_F(TestMatrix4x4, CanDivideByScalar)
{
    double x1[] = {
        2.0,  4.0,  6.0,  8.0,
       10.0, 12.0, 14.0, 16.0,
       18.0, 20.0, 22.0, 24.0,
       26.0, 28.0, 30.0, 32.0
    };

    mc::Matrix4x4 m1;
    m1.SetFromArray(x1);
    mc::Matrix4x4 m2 = m1 / 2.0;

    EXPECT_DOUBLE_EQ(m2(0,0),  1.0);
    EXPECT_DOUBLE_EQ(m2(0,1),  2.0);
    EXPECT_DOUBLE_EQ(m2(0,2),  3.0);
    EXPECT_DOUBLE_EQ(m2(0,3),  4.0);
    EXPECT_DOUBLE_EQ(m2(1,0),  5.0);
    EXPECT_DOUBLE_EQ(m2(1,1),  6.0);
    EXPECT_DOUBLE_EQ(m2(1,2),  7.0);
    EXPECT_DOUBLE_EQ(m2(1,3),  8.0);
    EXPECT_DOUBLE_EQ(m2(2,0),  9.0);
    EXPECT_DOUBLE_EQ(m2(2,1), 10.0);
    EXPECT_DOUBLE_EQ(m2(2,2), 11.0);
    EXPECT_DOUBLE_EQ(m2(2,3), 12.0);
    EXPECT_DOUBLE_EQ(m2(3,0), 13.0);
    EXPECT_DOUBLE_EQ(m2(3,1), 14.0);
    EXPECT_DOUBLE_EQ(m2(3,2), 15.0);
    EXPECT_DOUBLE_EQ(m2(3,3), 16.0);
}

TEST_F(TestMatrix4x4, CanUnaryAdd)
{
    double x1[] = {
        1.0,  2.0,  3.0,  4.0,
        5.0,  6.0,  7.0,  8.0,
        9.0, 10.0, 11.0, 12.0,
       13.0, 14.0, 15.0, 16.0
    };

    mc::Matrix4x4 m1;
    mc::Matrix4x4 m2;
    m2.SetFromArray(x1);

    m1 += m2;

    EXPECT_DOUBLE_EQ(m1(0,0),  1.0);
    EXPECT_DOUBLE_EQ(m1(0,1),  2.0);
    EXPECT_DOUBLE_EQ(m1(0,2),  3.0);
    EXPECT_DOUBLE_EQ(m1(0,3),  4.0);
    EXPECT_DOUBLE_EQ(m1(1,0),  5.0);
    EXPECT_DOUBLE_EQ(m1(1,1),  6.0);
    EXPECT_DOUBLE_EQ(m1(1,2),  7.0);
    EXPECT_DOUBLE_EQ(m1(1,3),  8.0);
    EXPECT_DOUBLE_EQ(m1(2,0),  9.0);
    EXPECT_DOUBLE_EQ(m1(2,1), 10.0);
    EXPECT_DOUBLE_EQ(m1(2,2), 11.0);
    EXPECT_DOUBLE_EQ(m1(2,3), 12.0);
    EXPECT_DOUBLE_EQ(m1(3,0), 13.0);
    EXPECT_DOUBLE_EQ(m1(3,1), 14.0);
    EXPECT_DOUBLE_EQ(m1(3,2), 15.0);
    EXPECT_DOUBLE_EQ(m1(3,3), 16.0);
}

TEST_F(TestMatrix4x4, CanUnarySubstract)
{
    double x1[] = {
        1.0,  2.0,  3.0,  4.0,
        5.0,  6.0,  7.0,  8.0,
        9.0, 10.0, 11.0, 12.0,
       13.0, 14.0, 15.0, 16.0
    };

    mc::Matrix4x4 m1;
    mc::Matrix4x4 m2;
    m2.SetFromArray(x1);

    m1 -= m2;

    EXPECT_DOUBLE_EQ(m1(0,0), -  1.0);
    EXPECT_DOUBLE_EQ(m1(0,1), -  2.0);
    EXPECT_DOUBLE_EQ(m1(0,2), -  3.0);
    EXPECT_DOUBLE_EQ(m1(0,3), -  4.0);
    EXPECT_DOUBLE_EQ(m1(1,0), -  5.0);
    EXPECT_DOUBLE_EQ(m1(1,1), -  6.0);
    EXPECT_DOUBLE_EQ(m1(1,2), -  7.0);
    EXPECT_DOUBLE_EQ(m1(1,3), -  8.0);
    EXPECT_DOUBLE_EQ(m1(2,0), -  9.0);
    EXPECT_DOUBLE_EQ(m1(2,1), - 10.0);
    EXPECT_DOUBLE_EQ(m1(2,2), - 11.0);
    EXPECT_DOUBLE_EQ(m1(2,3), - 12.0);
    EXPECT_DOUBLE_EQ(m1(3,0), - 13.0);
    EXPECT_DOUBLE_EQ(m1(3,1), - 14.0);
    EXPECT_DOUBLE_EQ(m1(3,2), - 15.0);
    EXPECT_DOUBLE_EQ(m1(3,3), - 16.0);
}

TEST_F(TestMatrix4x4, CanUnaryMultiplyByScalar)
{
    double elements[] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };

    mc::Matrix4x4 m1;
    m1.SetFromArray(elements);

    m1 *= 2.0;

    EXPECT_DOUBLE_EQ(m1(0,0),  2.0);
    EXPECT_DOUBLE_EQ(m1(0,1),  4.0);
    EXPECT_DOUBLE_EQ(m1(0,2),  6.0);
    EXPECT_DOUBLE_EQ(m1(0,3),  8.0);
    EXPECT_DOUBLE_EQ(m1(1,0), 10.0);
    EXPECT_DOUBLE_EQ(m1(1,1), 12.0);
    EXPECT_DOUBLE_EQ(m1(1,2), 14.0);
    EXPECT_DOUBLE_EQ(m1(1,3), 16.0);
    EXPECT_DOUBLE_EQ(m1(2,0), 18.0);
    EXPECT_DOUBLE_EQ(m1(2,1), 20.0);
    EXPECT_DOUBLE_EQ(m1(2,2), 22.0);
    EXPECT_DOUBLE_EQ(m1(2,3), 24.0);
    EXPECT_DOUBLE_EQ(m1(3,0), 26.0);
    EXPECT_DOUBLE_EQ(m1(3,1), 28.0);
    EXPECT_DOUBLE_EQ(m1(3,2), 30.0);
    EXPECT_DOUBLE_EQ(m1(3,3), 32.0);
}

TEST_F(TestMatrix4x4, CanUnaryDivideByScalar)
{
    double elements[] = {
        2.0,  4.0,  6.0,  8.0,
       10.0, 12.0, 14.0, 16.0,
       18.0, 20.0, 22.0, 24.0,
       26.0, 28.0, 30.0, 32.0
    };

    mc::Matrix4x4 m1;
    m1.SetFromArray(elements);

    m1 /= 2.0;

    EXPECT_DOUBLE_EQ(m1(0,0),  1.0);
    EXPECT_DOUBLE_EQ(m1(0,1),  2.0);
    EXPECT_DOUBLE_EQ(m1(0,2),  3.0);
    EXPECT_DOUBLE_EQ(m1(0,3),  4.0);
    EXPECT_DOUBLE_EQ(m1(1,0),  5.0);
    EXPECT_DOUBLE_EQ(m1(1,1),  6.0);
    EXPECT_DOUBLE_EQ(m1(1,2),  7.0);
    EXPECT_DOUBLE_EQ(m1(1,3),  8.0);
    EXPECT_DOUBLE_EQ(m1(2,0),  9.0);
    EXPECT_DOUBLE_EQ(m1(2,1), 10.0);
    EXPECT_DOUBLE_EQ(m1(2,2), 11.0);
    EXPECT_DOUBLE_EQ(m1(2,3), 12.0);
    EXPECT_DOUBLE_EQ(m1(3,0), 13.0);
    EXPECT_DOUBLE_EQ(m1(3,1), 14.0);
    EXPECT_DOUBLE_EQ(m1(3,2), 15.0);
    EXPECT_DOUBLE_EQ(m1(3,3), 16.0);
}
