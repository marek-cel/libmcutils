#include <gtest/gtest.h>

#include <mcutils/math/Matrix6x6.h>

////////////////////////////////////////////////////////////////////////////////

class TestMatrix6x6 : public ::testing::Test
{
protected:
    TestMatrix6x6() {}
    virtual ~TestMatrix6x6() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanConstruct)
{
    mc::Matrix6x6 *m = nullptr;
    EXPECT_NO_THROW( m = new mc::Matrix6x6() );
    delete m;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanDestruct)
{
    mc::Matrix6x6 *m = new mc::Matrix6x6();
    EXPECT_NO_THROW( delete m );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanInstantiate)
{
    mc::Matrix6x6 m;

    EXPECT_DOUBLE_EQ( m(0,0), 0.0 );
    EXPECT_DOUBLE_EQ( m(0,1), 0.0 );
    EXPECT_DOUBLE_EQ( m(0,2), 0.0 );
    EXPECT_DOUBLE_EQ( m(0,3), 0.0 );
    EXPECT_DOUBLE_EQ( m(0,4), 0.0 );
    EXPECT_DOUBLE_EQ( m(0,5), 0.0 );
    EXPECT_DOUBLE_EQ( m(1,0), 0.0 );
    EXPECT_DOUBLE_EQ( m(1,1), 0.0 );
    EXPECT_DOUBLE_EQ( m(1,2), 0.0 );
    EXPECT_DOUBLE_EQ( m(1,3), 0.0 );
    EXPECT_DOUBLE_EQ( m(1,4), 0.0 );
    EXPECT_DOUBLE_EQ( m(1,5), 0.0 );
    EXPECT_DOUBLE_EQ( m(2,0), 0.0 );
    EXPECT_DOUBLE_EQ( m(2,1), 0.0 );
    EXPECT_DOUBLE_EQ( m(2,2), 0.0 );
    EXPECT_DOUBLE_EQ( m(2,3), 0.0 );
    EXPECT_DOUBLE_EQ( m(2,4), 0.0 );
    EXPECT_DOUBLE_EQ( m(2,5), 0.0 );
    EXPECT_DOUBLE_EQ( m(3,0), 0.0 );
    EXPECT_DOUBLE_EQ( m(3,1), 0.0 );
    EXPECT_DOUBLE_EQ( m(3,2), 0.0 );
    EXPECT_DOUBLE_EQ( m(3,3), 0.0 );
    EXPECT_DOUBLE_EQ( m(3,4), 0.0 );
    EXPECT_DOUBLE_EQ( m(3,5), 0.0 );
    EXPECT_DOUBLE_EQ( m(4,0), 0.0 );
    EXPECT_DOUBLE_EQ( m(4,1), 0.0 );
    EXPECT_DOUBLE_EQ( m(4,2), 0.0 );
    EXPECT_DOUBLE_EQ( m(4,3), 0.0 );
    EXPECT_DOUBLE_EQ( m(4,4), 0.0 );
    EXPECT_DOUBLE_EQ( m(4,5), 0.0 );
    EXPECT_DOUBLE_EQ( m(5,0), 0.0 );
    EXPECT_DOUBLE_EQ( m(5,1), 0.0 );
    EXPECT_DOUBLE_EQ( m(5,2), 0.0 );
    EXPECT_DOUBLE_EQ( m(5,3), 0.0 );
    EXPECT_DOUBLE_EQ( m(5,4), 0.0 );
    EXPECT_DOUBLE_EQ( m(5,5), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanTranspose)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix6x6.m

    double x[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::Matrix6x6 m;
    m.SetFromArray(x);

    m.Transpose();

    EXPECT_DOUBLE_EQ( m(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( m(0,1),  7.0 );
    EXPECT_DOUBLE_EQ( m(0,2), 13.0 );
    EXPECT_DOUBLE_EQ( m(0,3), 19.0 );
    EXPECT_DOUBLE_EQ( m(0,4), 25.0 );
    EXPECT_DOUBLE_EQ( m(0,5), 31.0 );
    EXPECT_DOUBLE_EQ( m(1,0),  2.0 );
    EXPECT_DOUBLE_EQ( m(1,1),  8.0 );
    EXPECT_DOUBLE_EQ( m(1,2), 14.0 );
    EXPECT_DOUBLE_EQ( m(1,3), 20.0 );
    EXPECT_DOUBLE_EQ( m(1,4), 26.0 );
    EXPECT_DOUBLE_EQ( m(1,5), 32.0 );
    EXPECT_DOUBLE_EQ( m(2,0),  3.0 );
    EXPECT_DOUBLE_EQ( m(2,1),  9.0 );
    EXPECT_DOUBLE_EQ( m(2,2), 15.0 );
    EXPECT_DOUBLE_EQ( m(2,3), 21.0 );
    EXPECT_DOUBLE_EQ( m(2,4), 27.0 );
    EXPECT_DOUBLE_EQ( m(2,5), 33.0 );
    EXPECT_DOUBLE_EQ( m(3,0),  4.0 );
    EXPECT_DOUBLE_EQ( m(3,1), 10.0 );
    EXPECT_DOUBLE_EQ( m(3,2), 16.0 );
    EXPECT_DOUBLE_EQ( m(3,3), 22.0 );
    EXPECT_DOUBLE_EQ( m(3,4), 28.0 );
    EXPECT_DOUBLE_EQ( m(3,5), 34.0 );
    EXPECT_DOUBLE_EQ( m(4,0),  5.0 );
    EXPECT_DOUBLE_EQ( m(4,1), 11.0 );
    EXPECT_DOUBLE_EQ( m(4,2), 17.0 );
    EXPECT_DOUBLE_EQ( m(4,3), 23.0 );
    EXPECT_DOUBLE_EQ( m(4,4), 29.0 );
    EXPECT_DOUBLE_EQ( m(4,5), 35.0 );
    EXPECT_DOUBLE_EQ( m(5,0),  6.0 );
    EXPECT_DOUBLE_EQ( m(5,1), 12.0 );
    EXPECT_DOUBLE_EQ( m(5,2), 18.0 );
    EXPECT_DOUBLE_EQ( m(5,3), 24.0 );
    EXPECT_DOUBLE_EQ( m(5,4), 30.0 );
    EXPECT_DOUBLE_EQ( m(5,5), 36.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanGetTransposed)
{
    double x[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::Matrix6x6 m;
    m.SetFromArray(x);

    mc::Matrix6x6 m1 = m.GetTransposed();

    EXPECT_DOUBLE_EQ( m(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( m(0,1),  2.0 );
    EXPECT_DOUBLE_EQ( m(0,2),  3.0 );
    EXPECT_DOUBLE_EQ( m(0,3),  4.0 );
    EXPECT_DOUBLE_EQ( m(0,4),  5.0 );
    EXPECT_DOUBLE_EQ( m(0,5),  6.0 );
    EXPECT_DOUBLE_EQ( m(1,0),  7.0 );
    EXPECT_DOUBLE_EQ( m(1,1),  8.0 );
    EXPECT_DOUBLE_EQ( m(1,2),  9.0 );
    EXPECT_DOUBLE_EQ( m(1,3), 10.0 );
    EXPECT_DOUBLE_EQ( m(1,4), 11.0 );
    EXPECT_DOUBLE_EQ( m(1,5), 12.0 );
    EXPECT_DOUBLE_EQ( m(2,0), 13.0 );
    EXPECT_DOUBLE_EQ( m(2,1), 14.0 );
    EXPECT_DOUBLE_EQ( m(2,2), 15.0 );
    EXPECT_DOUBLE_EQ( m(2,3), 16.0 );
    EXPECT_DOUBLE_EQ( m(2,4), 17.0 );
    EXPECT_DOUBLE_EQ( m(2,5), 18.0 );
    EXPECT_DOUBLE_EQ( m(3,0), 19.0 );
    EXPECT_DOUBLE_EQ( m(3,1), 20.0 );
    EXPECT_DOUBLE_EQ( m(3,2), 21.0 );
    EXPECT_DOUBLE_EQ( m(3,3), 22.0 );
    EXPECT_DOUBLE_EQ( m(3,4), 23.0 );
    EXPECT_DOUBLE_EQ( m(3,5), 24.0 );
    EXPECT_DOUBLE_EQ( m(4,0), 25.0 );
    EXPECT_DOUBLE_EQ( m(4,1), 26.0 );
    EXPECT_DOUBLE_EQ( m(4,2), 27.0 );
    EXPECT_DOUBLE_EQ( m(4,3), 28.0 );
    EXPECT_DOUBLE_EQ( m(4,4), 29.0 );
    EXPECT_DOUBLE_EQ( m(4,5), 30.0 );
    EXPECT_DOUBLE_EQ( m(5,0), 31.0 );
    EXPECT_DOUBLE_EQ( m(5,1), 32.0 );
    EXPECT_DOUBLE_EQ( m(5,2), 33.0 );
    EXPECT_DOUBLE_EQ( m(5,3), 34.0 );
    EXPECT_DOUBLE_EQ( m(5,4), 35.0 );
    EXPECT_DOUBLE_EQ( m(5,5), 36.0 );

    EXPECT_DOUBLE_EQ( m1(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( m1(0,1),  7.0 );
    EXPECT_DOUBLE_EQ( m1(0,2), 13.0 );
    EXPECT_DOUBLE_EQ( m1(0,3), 19.0 );
    EXPECT_DOUBLE_EQ( m1(0,4), 25.0 );
    EXPECT_DOUBLE_EQ( m1(0,5), 31.0 );
    EXPECT_DOUBLE_EQ( m1(1,0),  2.0 );
    EXPECT_DOUBLE_EQ( m1(1,1),  8.0 );
    EXPECT_DOUBLE_EQ( m1(1,2), 14.0 );
    EXPECT_DOUBLE_EQ( m1(1,3), 20.0 );
    EXPECT_DOUBLE_EQ( m1(1,4), 26.0 );
    EXPECT_DOUBLE_EQ( m1(1,5), 32.0 );
    EXPECT_DOUBLE_EQ( m1(2,0),  3.0 );
    EXPECT_DOUBLE_EQ( m1(2,1),  9.0 );
    EXPECT_DOUBLE_EQ( m1(2,2), 15.0 );
    EXPECT_DOUBLE_EQ( m1(2,3), 21.0 );
    EXPECT_DOUBLE_EQ( m1(2,4), 27.0 );
    EXPECT_DOUBLE_EQ( m1(2,5), 33.0 );
    EXPECT_DOUBLE_EQ( m1(3,0),  4.0 );
    EXPECT_DOUBLE_EQ( m1(3,1), 10.0 );
    EXPECT_DOUBLE_EQ( m1(3,2), 16.0 );
    EXPECT_DOUBLE_EQ( m1(3,3), 22.0 );
    EXPECT_DOUBLE_EQ( m1(3,4), 28.0 );
    EXPECT_DOUBLE_EQ( m1(3,5), 34.0 );
    EXPECT_DOUBLE_EQ( m1(4,0),  5.0 );
    EXPECT_DOUBLE_EQ( m1(4,1), 11.0 );
    EXPECT_DOUBLE_EQ( m1(4,2), 17.0 );
    EXPECT_DOUBLE_EQ( m1(4,3), 23.0 );
    EXPECT_DOUBLE_EQ( m1(4,4), 29.0 );
    EXPECT_DOUBLE_EQ( m1(4,5), 35.0 );
    EXPECT_DOUBLE_EQ( m1(5,0),  6.0 );
    EXPECT_DOUBLE_EQ( m1(5,1), 12.0 );
    EXPECT_DOUBLE_EQ( m1(5,2), 18.0 );
    EXPECT_DOUBLE_EQ( m1(5,3), 24.0 );
    EXPECT_DOUBLE_EQ( m1(5,4), 30.0 );
    EXPECT_DOUBLE_EQ( m1(5,5), 36.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanAdd)
{
    double x[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::Matrix6x6 m0;
    mc::Matrix6x6 m1;
    m1.SetFromArray(x);

    mc::Matrix6x6 m = m0 + m1;

    EXPECT_DOUBLE_EQ( m(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( m(0,1),  2.0 );
    EXPECT_DOUBLE_EQ( m(0,2),  3.0 );
    EXPECT_DOUBLE_EQ( m(0,3),  4.0 );
    EXPECT_DOUBLE_EQ( m(0,4),  5.0 );
    EXPECT_DOUBLE_EQ( m(0,5),  6.0 );
    EXPECT_DOUBLE_EQ( m(1,0),  7.0 );
    EXPECT_DOUBLE_EQ( m(1,1),  8.0 );
    EXPECT_DOUBLE_EQ( m(1,2),  9.0 );
    EXPECT_DOUBLE_EQ( m(1,3), 10.0 );
    EXPECT_DOUBLE_EQ( m(1,4), 11.0 );
    EXPECT_DOUBLE_EQ( m(1,5), 12.0 );
    EXPECT_DOUBLE_EQ( m(2,0), 13.0 );
    EXPECT_DOUBLE_EQ( m(2,1), 14.0 );
    EXPECT_DOUBLE_EQ( m(2,2), 15.0 );
    EXPECT_DOUBLE_EQ( m(2,3), 16.0 );
    EXPECT_DOUBLE_EQ( m(2,4), 17.0 );
    EXPECT_DOUBLE_EQ( m(2,5), 18.0 );
    EXPECT_DOUBLE_EQ( m(3,0), 19.0 );
    EXPECT_DOUBLE_EQ( m(3,1), 20.0 );
    EXPECT_DOUBLE_EQ( m(3,2), 21.0 );
    EXPECT_DOUBLE_EQ( m(3,3), 22.0 );
    EXPECT_DOUBLE_EQ( m(3,4), 23.0 );
    EXPECT_DOUBLE_EQ( m(3,5), 24.0 );
    EXPECT_DOUBLE_EQ( m(4,0), 25.0 );
    EXPECT_DOUBLE_EQ( m(4,1), 26.0 );
    EXPECT_DOUBLE_EQ( m(4,2), 27.0 );
    EXPECT_DOUBLE_EQ( m(4,3), 28.0 );
    EXPECT_DOUBLE_EQ( m(4,4), 29.0 );
    EXPECT_DOUBLE_EQ( m(4,5), 30.0 );
    EXPECT_DOUBLE_EQ( m(5,0), 31.0 );
    EXPECT_DOUBLE_EQ( m(5,1), 32.0 );
    EXPECT_DOUBLE_EQ( m(5,2), 33.0 );
    EXPECT_DOUBLE_EQ( m(5,3), 34.0 );
    EXPECT_DOUBLE_EQ( m(5,4), 35.0 );
    EXPECT_DOUBLE_EQ( m(5,5), 36.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanNegate)
{
    double x[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::Matrix6x6 m1;
    m1.SetFromArray(x);

    mc::Matrix6x6 m = -m1;

    EXPECT_DOUBLE_EQ( m(0,0),  -1.0 );
    EXPECT_DOUBLE_EQ( m(0,1),  -2.0 );
    EXPECT_DOUBLE_EQ( m(0,2),  -3.0 );
    EXPECT_DOUBLE_EQ( m(0,3),  -4.0 );
    EXPECT_DOUBLE_EQ( m(0,4),  -5.0 );
    EXPECT_DOUBLE_EQ( m(0,5),  -6.0 );
    EXPECT_DOUBLE_EQ( m(1,0),  -7.0 );
    EXPECT_DOUBLE_EQ( m(1,1),  -8.0 );
    EXPECT_DOUBLE_EQ( m(1,2),  -9.0 );
    EXPECT_DOUBLE_EQ( m(1,3), -10.0 );
    EXPECT_DOUBLE_EQ( m(1,4), -11.0 );
    EXPECT_DOUBLE_EQ( m(1,5), -12.0 );
    EXPECT_DOUBLE_EQ( m(2,0), -13.0 );
    EXPECT_DOUBLE_EQ( m(2,1), -14.0 );
    EXPECT_DOUBLE_EQ( m(2,2), -15.0 );
    EXPECT_DOUBLE_EQ( m(2,3), -16.0 );
    EXPECT_DOUBLE_EQ( m(2,4), -17.0 );
    EXPECT_DOUBLE_EQ( m(2,5), -18.0 );
    EXPECT_DOUBLE_EQ( m(3,0), -19.0 );
    EXPECT_DOUBLE_EQ( m(3,1), -20.0 );
    EXPECT_DOUBLE_EQ( m(3,2), -21.0 );
    EXPECT_DOUBLE_EQ( m(3,3), -22.0 );
    EXPECT_DOUBLE_EQ( m(3,4), -23.0 );
    EXPECT_DOUBLE_EQ( m(3,5), -24.0 );
    EXPECT_DOUBLE_EQ( m(4,0), -25.0 );
    EXPECT_DOUBLE_EQ( m(4,1), -26.0 );
    EXPECT_DOUBLE_EQ( m(4,2), -27.0 );
    EXPECT_DOUBLE_EQ( m(4,3), -28.0 );
    EXPECT_DOUBLE_EQ( m(4,4), -29.0 );
    EXPECT_DOUBLE_EQ( m(4,5), -30.0 );
    EXPECT_DOUBLE_EQ( m(5,0), -31.0 );
    EXPECT_DOUBLE_EQ( m(5,1), -32.0 );
    EXPECT_DOUBLE_EQ( m(5,2), -33.0 );
    EXPECT_DOUBLE_EQ( m(5,3), -34.0 );
    EXPECT_DOUBLE_EQ( m(5,4), -35.0 );
    EXPECT_DOUBLE_EQ( m(5,5), -36.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanSubstract)
{
    double x[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::Matrix6x6 m0;
    mc::Matrix6x6 m1;
    m1.SetFromArray(x);

    mc::Matrix6x6 m = m0 - m1;

    EXPECT_DOUBLE_EQ( m(0,0), -  1.0 );
    EXPECT_DOUBLE_EQ( m(0,1), -  2.0 );
    EXPECT_DOUBLE_EQ( m(0,2), -  3.0 );
    EXPECT_DOUBLE_EQ( m(0,3), -  4.0 );
    EXPECT_DOUBLE_EQ( m(0,4), -  5.0 );
    EXPECT_DOUBLE_EQ( m(0,5), -  6.0 );
    EXPECT_DOUBLE_EQ( m(1,0), -  7.0 );
    EXPECT_DOUBLE_EQ( m(1,1), -  8.0 );
    EXPECT_DOUBLE_EQ( m(1,2), -  9.0 );
    EXPECT_DOUBLE_EQ( m(1,3), - 10.0 );
    EXPECT_DOUBLE_EQ( m(1,4), - 11.0 );
    EXPECT_DOUBLE_EQ( m(1,5), - 12.0 );
    EXPECT_DOUBLE_EQ( m(2,0), - 13.0 );
    EXPECT_DOUBLE_EQ( m(2,1), - 14.0 );
    EXPECT_DOUBLE_EQ( m(2,2), - 15.0 );
    EXPECT_DOUBLE_EQ( m(2,3), - 16.0 );
    EXPECT_DOUBLE_EQ( m(2,4), - 17.0 );
    EXPECT_DOUBLE_EQ( m(2,5), - 18.0 );
    EXPECT_DOUBLE_EQ( m(3,0), - 19.0 );
    EXPECT_DOUBLE_EQ( m(3,1), - 20.0 );
    EXPECT_DOUBLE_EQ( m(3,2), - 21.0 );
    EXPECT_DOUBLE_EQ( m(3,3), - 22.0 );
    EXPECT_DOUBLE_EQ( m(3,4), - 23.0 );
    EXPECT_DOUBLE_EQ( m(3,5), - 24.0 );
    EXPECT_DOUBLE_EQ( m(4,0), - 25.0 );
    EXPECT_DOUBLE_EQ( m(4,1), - 26.0 );
    EXPECT_DOUBLE_EQ( m(4,2), - 27.0 );
    EXPECT_DOUBLE_EQ( m(4,3), - 28.0 );
    EXPECT_DOUBLE_EQ( m(4,4), - 29.0 );
    EXPECT_DOUBLE_EQ( m(4,5), - 30.0 );
    EXPECT_DOUBLE_EQ( m(5,0), - 31.0 );
    EXPECT_DOUBLE_EQ( m(5,1), - 32.0 );
    EXPECT_DOUBLE_EQ( m(5,2), - 33.0 );
    EXPECT_DOUBLE_EQ( m(5,3), - 34.0 );
    EXPECT_DOUBLE_EQ( m(5,4), - 35.0 );
    EXPECT_DOUBLE_EQ( m(5,5), - 36.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanMultiplyByScalar)
{
    double x[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::Matrix6x6 m1;
    m1.SetFromArray(x);

    mc::Matrix6x6 m = m1 * 0.5;

    EXPECT_DOUBLE_EQ( m(0,0),  0.5 );
    EXPECT_DOUBLE_EQ( m(0,1),  1.0 );
    EXPECT_DOUBLE_EQ( m(0,2),  1.5 );
    EXPECT_DOUBLE_EQ( m(0,3),  2.0 );
    EXPECT_DOUBLE_EQ( m(0,4),  2.5 );
    EXPECT_DOUBLE_EQ( m(0,5),  3.0 );
    EXPECT_DOUBLE_EQ( m(1,0),  3.5 );
    EXPECT_DOUBLE_EQ( m(1,1),  4.0 );
    EXPECT_DOUBLE_EQ( m(1,2),  4.5 );
    EXPECT_DOUBLE_EQ( m(1,3),  5.0 );
    EXPECT_DOUBLE_EQ( m(1,4),  5.5 );
    EXPECT_DOUBLE_EQ( m(1,5),  6.0 );
    EXPECT_DOUBLE_EQ( m(2,0),  6.5 );
    EXPECT_DOUBLE_EQ( m(2,1),  7.0 );
    EXPECT_DOUBLE_EQ( m(2,2),  7.5 );
    EXPECT_DOUBLE_EQ( m(2,3),  8.0 );
    EXPECT_DOUBLE_EQ( m(2,4),  8.5 );
    EXPECT_DOUBLE_EQ( m(2,5),  9.0 );
    EXPECT_DOUBLE_EQ( m(3,0),  9.5 );
    EXPECT_DOUBLE_EQ( m(3,1), 10.0 );
    EXPECT_DOUBLE_EQ( m(3,2), 10.5 );
    EXPECT_DOUBLE_EQ( m(3,3), 11.0 );
    EXPECT_DOUBLE_EQ( m(3,4), 11.5 );
    EXPECT_DOUBLE_EQ( m(3,5), 12.0 );
    EXPECT_DOUBLE_EQ( m(4,0), 12.5 );
    EXPECT_DOUBLE_EQ( m(4,1), 13.0 );
    EXPECT_DOUBLE_EQ( m(4,2), 13.5 );
    EXPECT_DOUBLE_EQ( m(4,3), 14.0 );
    EXPECT_DOUBLE_EQ( m(4,4), 14.5 );
    EXPECT_DOUBLE_EQ( m(4,5), 15.0 );
    EXPECT_DOUBLE_EQ( m(5,0), 15.5 );
    EXPECT_DOUBLE_EQ( m(5,1), 16.0 );
    EXPECT_DOUBLE_EQ( m(5,2), 16.5 );
    EXPECT_DOUBLE_EQ( m(5,3), 17.0 );
    EXPECT_DOUBLE_EQ( m(5,4), 17.5 );
    EXPECT_DOUBLE_EQ( m(5,5), 18.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanMultiplyByMatrix)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix6x6.m

    double x0[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    double x1[] = {
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0
    };

    mc::Matrix6x6 m0;
    mc::Matrix6x6 m1;

    m0.SetFromArray(x0);
    m1.SetFromArray(x1);

    mc::Matrix6x6 m = m0 * m1;

    EXPECT_DOUBLE_EQ( m(0,0),  231.0 );
    EXPECT_DOUBLE_EQ( m(0,1),  252.0 );
    EXPECT_DOUBLE_EQ( m(0,2),  273.0 );
    EXPECT_DOUBLE_EQ( m(0,3),  294.0 );
    EXPECT_DOUBLE_EQ( m(0,4),  315.0 );
    EXPECT_DOUBLE_EQ( m(0,5),  336.0 );

    EXPECT_DOUBLE_EQ( m(1,0),  807.0 );
    EXPECT_DOUBLE_EQ( m(1,1),  864.0 );
    EXPECT_DOUBLE_EQ( m(1,2),  921.0 );
    EXPECT_DOUBLE_EQ( m(1,3),  978.0 );
    EXPECT_DOUBLE_EQ( m(1,4), 1035.0 );
    EXPECT_DOUBLE_EQ( m(1,5), 1092.0 );

    EXPECT_DOUBLE_EQ( m(2,0), 1383.0 );
    EXPECT_DOUBLE_EQ( m(2,1), 1476.0 );
    EXPECT_DOUBLE_EQ( m(2,2), 1569.0 );
    EXPECT_DOUBLE_EQ( m(2,3), 1662.0 );
    EXPECT_DOUBLE_EQ( m(2,4), 1755.0 );
    EXPECT_DOUBLE_EQ( m(2,5), 1848.0 );

    EXPECT_DOUBLE_EQ( m(3,0), 1959.0 );
    EXPECT_DOUBLE_EQ( m(3,1), 2088.0 );
    EXPECT_DOUBLE_EQ( m(3,2), 2217.0 );
    EXPECT_DOUBLE_EQ( m(3,3), 2346.0 );
    EXPECT_DOUBLE_EQ( m(3,4), 2475.0 );
    EXPECT_DOUBLE_EQ( m(3,5), 2604.0 );

    EXPECT_DOUBLE_EQ( m(4,0), 2535.0 );
    EXPECT_DOUBLE_EQ( m(4,1), 2700.0 );
    EXPECT_DOUBLE_EQ( m(4,2), 2865.0 );
    EXPECT_DOUBLE_EQ( m(4,3), 3030.0 );
    EXPECT_DOUBLE_EQ( m(4,4), 3195.0 );
    EXPECT_DOUBLE_EQ( m(4,5), 3360.0 );

    EXPECT_DOUBLE_EQ( m(5,0), 3111.0 );
    EXPECT_DOUBLE_EQ( m(5,1), 3312.0 );
    EXPECT_DOUBLE_EQ( m(5,2), 3513.0 );
    EXPECT_DOUBLE_EQ( m(5,3), 3714.0 );
    EXPECT_DOUBLE_EQ( m(5,4), 3915.0 );
    EXPECT_DOUBLE_EQ( m(5,5), 4116.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanMultiplyByVector)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix6x6.m

    double x0[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    double x1[] = { 1.0,  2.0,  3.0,  4.0,  5.0,  6.0 };

    mc::Matrix6x6 m0;
    m0.SetFromArray(x0);

    mc::Vector6 v1;
    v1.SetFromArray(x1);

    mc::Vector6 v = m0 * v1;

    EXPECT_DOUBLE_EQ( v(0),  91.0 );
    EXPECT_DOUBLE_EQ( v(1), 217.0 );
    EXPECT_DOUBLE_EQ( v(2), 343.0 );
    EXPECT_DOUBLE_EQ( v(3), 469.0 );
    EXPECT_DOUBLE_EQ( v(4), 595.0 );
    EXPECT_DOUBLE_EQ( v(5), 721.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanDivideByScalar)
{
    double x[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::Matrix6x6 m1;
    m1.SetFromArray(x);

    mc::Matrix6x6 m = m1 / 2.0;

    EXPECT_DOUBLE_EQ( m(0,0),  0.5 );
    EXPECT_DOUBLE_EQ( m(0,1),  1.0 );
    EXPECT_DOUBLE_EQ( m(0,2),  1.5 );
    EXPECT_DOUBLE_EQ( m(0,3),  2.0 );
    EXPECT_DOUBLE_EQ( m(0,4),  2.5 );
    EXPECT_DOUBLE_EQ( m(0,5),  3.0 );
    EXPECT_DOUBLE_EQ( m(1,0),  3.5 );
    EXPECT_DOUBLE_EQ( m(1,1),  4.0 );
    EXPECT_DOUBLE_EQ( m(1,2),  4.5 );
    EXPECT_DOUBLE_EQ( m(1,3),  5.0 );
    EXPECT_DOUBLE_EQ( m(1,4),  5.5 );
    EXPECT_DOUBLE_EQ( m(1,5),  6.0 );
    EXPECT_DOUBLE_EQ( m(2,0),  6.5 );
    EXPECT_DOUBLE_EQ( m(2,1),  7.0 );
    EXPECT_DOUBLE_EQ( m(2,2),  7.5 );
    EXPECT_DOUBLE_EQ( m(2,3),  8.0 );
    EXPECT_DOUBLE_EQ( m(2,4),  8.5 );
    EXPECT_DOUBLE_EQ( m(2,5),  9.0 );
    EXPECT_DOUBLE_EQ( m(3,0),  9.5 );
    EXPECT_DOUBLE_EQ( m(3,1), 10.0 );
    EXPECT_DOUBLE_EQ( m(3,2), 10.5 );
    EXPECT_DOUBLE_EQ( m(3,3), 11.0 );
    EXPECT_DOUBLE_EQ( m(3,4), 11.5 );
    EXPECT_DOUBLE_EQ( m(3,5), 12.0 );
    EXPECT_DOUBLE_EQ( m(4,0), 12.5 );
    EXPECT_DOUBLE_EQ( m(4,1), 13.0 );
    EXPECT_DOUBLE_EQ( m(4,2), 13.5 );
    EXPECT_DOUBLE_EQ( m(4,3), 14.0 );
    EXPECT_DOUBLE_EQ( m(4,4), 14.5 );
    EXPECT_DOUBLE_EQ( m(4,5), 15.0 );
    EXPECT_DOUBLE_EQ( m(5,0), 15.5 );
    EXPECT_DOUBLE_EQ( m(5,1), 16.0 );
    EXPECT_DOUBLE_EQ( m(5,2), 16.5 );
    EXPECT_DOUBLE_EQ( m(5,3), 17.0 );
    EXPECT_DOUBLE_EQ( m(5,4), 17.5 );
    EXPECT_DOUBLE_EQ( m(5,5), 18.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanUnaryAdd)
{
    double x[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::Matrix6x6 m;
    mc::Matrix6x6 m1;
    m1.SetFromArray(x);

    m += m1;

    EXPECT_DOUBLE_EQ( m(0,0),  1.0 );
    EXPECT_DOUBLE_EQ( m(0,1),  2.0 );
    EXPECT_DOUBLE_EQ( m(0,2),  3.0 );
    EXPECT_DOUBLE_EQ( m(0,3),  4.0 );
    EXPECT_DOUBLE_EQ( m(0,4),  5.0 );
    EXPECT_DOUBLE_EQ( m(0,5),  6.0 );
    EXPECT_DOUBLE_EQ( m(1,0),  7.0 );
    EXPECT_DOUBLE_EQ( m(1,1),  8.0 );
    EXPECT_DOUBLE_EQ( m(1,2),  9.0 );
    EXPECT_DOUBLE_EQ( m(1,3), 10.0 );
    EXPECT_DOUBLE_EQ( m(1,4), 11.0 );
    EXPECT_DOUBLE_EQ( m(1,5), 12.0 );
    EXPECT_DOUBLE_EQ( m(2,0), 13.0 );
    EXPECT_DOUBLE_EQ( m(2,1), 14.0 );
    EXPECT_DOUBLE_EQ( m(2,2), 15.0 );
    EXPECT_DOUBLE_EQ( m(2,3), 16.0 );
    EXPECT_DOUBLE_EQ( m(2,4), 17.0 );
    EXPECT_DOUBLE_EQ( m(2,5), 18.0 );
    EXPECT_DOUBLE_EQ( m(3,0), 19.0 );
    EXPECT_DOUBLE_EQ( m(3,1), 20.0 );
    EXPECT_DOUBLE_EQ( m(3,2), 21.0 );
    EXPECT_DOUBLE_EQ( m(3,3), 22.0 );
    EXPECT_DOUBLE_EQ( m(3,4), 23.0 );
    EXPECT_DOUBLE_EQ( m(3,5), 24.0 );
    EXPECT_DOUBLE_EQ( m(4,0), 25.0 );
    EXPECT_DOUBLE_EQ( m(4,1), 26.0 );
    EXPECT_DOUBLE_EQ( m(4,2), 27.0 );
    EXPECT_DOUBLE_EQ( m(4,3), 28.0 );
    EXPECT_DOUBLE_EQ( m(4,4), 29.0 );
    EXPECT_DOUBLE_EQ( m(4,5), 30.0 );
    EXPECT_DOUBLE_EQ( m(5,0), 31.0 );
    EXPECT_DOUBLE_EQ( m(5,1), 32.0 );
    EXPECT_DOUBLE_EQ( m(5,2), 33.0 );
    EXPECT_DOUBLE_EQ( m(5,3), 34.0 );
    EXPECT_DOUBLE_EQ( m(5,4), 35.0 );
    EXPECT_DOUBLE_EQ( m(5,5), 36.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanUnarySubstract)
{
    double x[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::Matrix6x6 m;
    mc::Matrix6x6 m1;
    m1.SetFromArray(x);

    m -= m1;

    EXPECT_DOUBLE_EQ( m(0,0), -  1.0 );
    EXPECT_DOUBLE_EQ( m(0,1), -  2.0 );
    EXPECT_DOUBLE_EQ( m(0,2), -  3.0 );
    EXPECT_DOUBLE_EQ( m(0,3), -  4.0 );
    EXPECT_DOUBLE_EQ( m(0,4), -  5.0 );
    EXPECT_DOUBLE_EQ( m(0,5), -  6.0 );
    EXPECT_DOUBLE_EQ( m(1,0), -  7.0 );
    EXPECT_DOUBLE_EQ( m(1,1), -  8.0 );
    EXPECT_DOUBLE_EQ( m(1,2), -  9.0 );
    EXPECT_DOUBLE_EQ( m(1,3), - 10.0 );
    EXPECT_DOUBLE_EQ( m(1,4), - 11.0 );
    EXPECT_DOUBLE_EQ( m(1,5), - 12.0 );
    EXPECT_DOUBLE_EQ( m(2,0), - 13.0 );
    EXPECT_DOUBLE_EQ( m(2,1), - 14.0 );
    EXPECT_DOUBLE_EQ( m(2,2), - 15.0 );
    EXPECT_DOUBLE_EQ( m(2,3), - 16.0 );
    EXPECT_DOUBLE_EQ( m(2,4), - 17.0 );
    EXPECT_DOUBLE_EQ( m(2,5), - 18.0 );
    EXPECT_DOUBLE_EQ( m(3,0), - 19.0 );
    EXPECT_DOUBLE_EQ( m(3,1), - 20.0 );
    EXPECT_DOUBLE_EQ( m(3,2), - 21.0 );
    EXPECT_DOUBLE_EQ( m(3,3), - 22.0 );
    EXPECT_DOUBLE_EQ( m(3,4), - 23.0 );
    EXPECT_DOUBLE_EQ( m(3,5), - 24.0 );
    EXPECT_DOUBLE_EQ( m(4,0), - 25.0 );
    EXPECT_DOUBLE_EQ( m(4,1), - 26.0 );
    EXPECT_DOUBLE_EQ( m(4,2), - 27.0 );
    EXPECT_DOUBLE_EQ( m(4,3), - 28.0 );
    EXPECT_DOUBLE_EQ( m(4,4), - 29.0 );
    EXPECT_DOUBLE_EQ( m(4,5), - 30.0 );
    EXPECT_DOUBLE_EQ( m(5,0), - 31.0 );
    EXPECT_DOUBLE_EQ( m(5,1), - 32.0 );
    EXPECT_DOUBLE_EQ( m(5,2), - 33.0 );
    EXPECT_DOUBLE_EQ( m(5,3), - 34.0 );
    EXPECT_DOUBLE_EQ( m(5,4), - 35.0 );
    EXPECT_DOUBLE_EQ( m(5,5), - 36.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanUnaryMultiplyByScalar)
{
    double x[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::Matrix6x6 m;
    m.SetFromArray(x);

    m *= 0.5;

    EXPECT_DOUBLE_EQ( m(0,0),  0.5 );
    EXPECT_DOUBLE_EQ( m(0,1),  1.0 );
    EXPECT_DOUBLE_EQ( m(0,2),  1.5 );
    EXPECT_DOUBLE_EQ( m(0,3),  2.0 );
    EXPECT_DOUBLE_EQ( m(0,4),  2.5 );
    EXPECT_DOUBLE_EQ( m(0,5),  3.0 );
    EXPECT_DOUBLE_EQ( m(1,0),  3.5 );
    EXPECT_DOUBLE_EQ( m(1,1),  4.0 );
    EXPECT_DOUBLE_EQ( m(1,2),  4.5 );
    EXPECT_DOUBLE_EQ( m(1,3),  5.0 );
    EXPECT_DOUBLE_EQ( m(1,4),  5.5 );
    EXPECT_DOUBLE_EQ( m(1,5),  6.0 );
    EXPECT_DOUBLE_EQ( m(2,0),  6.5 );
    EXPECT_DOUBLE_EQ( m(2,1),  7.0 );
    EXPECT_DOUBLE_EQ( m(2,2),  7.5 );
    EXPECT_DOUBLE_EQ( m(2,3),  8.0 );
    EXPECT_DOUBLE_EQ( m(2,4),  8.5 );
    EXPECT_DOUBLE_EQ( m(2,5),  9.0 );
    EXPECT_DOUBLE_EQ( m(3,0),  9.5 );
    EXPECT_DOUBLE_EQ( m(3,1), 10.0 );
    EXPECT_DOUBLE_EQ( m(3,2), 10.5 );
    EXPECT_DOUBLE_EQ( m(3,3), 11.0 );
    EXPECT_DOUBLE_EQ( m(3,4), 11.5 );
    EXPECT_DOUBLE_EQ( m(3,5), 12.0 );
    EXPECT_DOUBLE_EQ( m(4,0), 12.5 );
    EXPECT_DOUBLE_EQ( m(4,1), 13.0 );
    EXPECT_DOUBLE_EQ( m(4,2), 13.5 );
    EXPECT_DOUBLE_EQ( m(4,3), 14.0 );
    EXPECT_DOUBLE_EQ( m(4,4), 14.5 );
    EXPECT_DOUBLE_EQ( m(4,5), 15.0 );
    EXPECT_DOUBLE_EQ( m(5,0), 15.5 );
    EXPECT_DOUBLE_EQ( m(5,1), 16.0 );
    EXPECT_DOUBLE_EQ( m(5,2), 16.5 );
    EXPECT_DOUBLE_EQ( m(5,3), 17.0 );
    EXPECT_DOUBLE_EQ( m(5,4), 17.5 );
    EXPECT_DOUBLE_EQ( m(5,5), 18.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMatrix6x6, CanUnaryDivideByScalar)
{
    double x[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,  6.0,
         7.0,  8.0,  9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
        31.0, 32.0, 33.0, 34.0, 35.0, 36.0
    };

    mc::Matrix6x6 m;
    m.SetFromArray(x);

    m /= 2.0;

    EXPECT_DOUBLE_EQ( m(0,0),  0.5 );
    EXPECT_DOUBLE_EQ( m(0,1),  1.0 );
    EXPECT_DOUBLE_EQ( m(0,2),  1.5 );
    EXPECT_DOUBLE_EQ( m(0,3),  2.0 );
    EXPECT_DOUBLE_EQ( m(0,4),  2.5 );
    EXPECT_DOUBLE_EQ( m(0,5),  3.0 );
    EXPECT_DOUBLE_EQ( m(1,0),  3.5 );
    EXPECT_DOUBLE_EQ( m(1,1),  4.0 );
    EXPECT_DOUBLE_EQ( m(1,2),  4.5 );
    EXPECT_DOUBLE_EQ( m(1,3),  5.0 );
    EXPECT_DOUBLE_EQ( m(1,4),  5.5 );
    EXPECT_DOUBLE_EQ( m(1,5),  6.0 );
    EXPECT_DOUBLE_EQ( m(2,0),  6.5 );
    EXPECT_DOUBLE_EQ( m(2,1),  7.0 );
    EXPECT_DOUBLE_EQ( m(2,2),  7.5 );
    EXPECT_DOUBLE_EQ( m(2,3),  8.0 );
    EXPECT_DOUBLE_EQ( m(2,4),  8.5 );
    EXPECT_DOUBLE_EQ( m(2,5),  9.0 );
    EXPECT_DOUBLE_EQ( m(3,0),  9.5 );
    EXPECT_DOUBLE_EQ( m(3,1), 10.0 );
    EXPECT_DOUBLE_EQ( m(3,2), 10.5 );
    EXPECT_DOUBLE_EQ( m(3,3), 11.0 );
    EXPECT_DOUBLE_EQ( m(3,4), 11.5 );
    EXPECT_DOUBLE_EQ( m(3,5), 12.0 );
    EXPECT_DOUBLE_EQ( m(4,0), 12.5 );
    EXPECT_DOUBLE_EQ( m(4,1), 13.0 );
    EXPECT_DOUBLE_EQ( m(4,2), 13.5 );
    EXPECT_DOUBLE_EQ( m(4,3), 14.0 );
    EXPECT_DOUBLE_EQ( m(4,4), 14.5 );
    EXPECT_DOUBLE_EQ( m(4,5), 15.0 );
    EXPECT_DOUBLE_EQ( m(5,0), 15.5 );
    EXPECT_DOUBLE_EQ( m(5,1), 16.0 );
    EXPECT_DOUBLE_EQ( m(5,2), 16.5 );
    EXPECT_DOUBLE_EQ( m(5,3), 17.0 );
    EXPECT_DOUBLE_EQ( m(5,4), 17.5 );
    EXPECT_DOUBLE_EQ( m(5,5), 18.0 );
}
