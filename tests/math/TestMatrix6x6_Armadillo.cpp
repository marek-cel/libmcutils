#ifdef TEST_USING_ARMADILLO

#include <gtest/gtest.h>
#include <armadillo>

#include <mcutils/math/Matrix6x6.h>

#include <TestingUtils.h>

class TestMatrix6x6_Armadillo : public ::testing::Test
{
protected:
    constexpr static int size = 6;
    TestMatrix6x6_Armadillo() {}
    virtual ~TestMatrix6x6_Armadillo() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMatrix6x6_Armadillo, CanGetTransposed)
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

    mc::Matrix6x6 m0;
    m0.SetFromArray(x);

    mc::Matrix6x6 m1(m0);
    mc::Matrix6x6 mt = m1.GetTransposed();

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

#endif // TEST_USING_ARMADILLO