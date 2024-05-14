#ifdef TEST_USING_ARMADILLO

#include <gtest/gtest.h>
#include <armadillo>

#include <mcutils/math/Matrix3x3.h>

#include <TestingUtils.h>

class TestMatrix3x3_Armadillo : public ::testing::Test
{
protected:
    constexpr static int size = 3;
    TestMatrix3x3_Armadillo() {}
    virtual ~TestMatrix3x3_Armadillo() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMatrix3x3_Armadillo, CanGetTransposed)
{
    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::Matrix3x3 m0;
    m0.SetFromArray(x);

    mc::Matrix3x3 m1(m0);
    mc::Matrix3x3 mt = m1.GetTransposed();

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