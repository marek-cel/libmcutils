#include <gtest/gtest.h>

#include <mcutils/physics/ParallelAxis.h>

class TestParallelAxis : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP     { 0.1 };
    static constexpr double TIME_CONSTANT { 2.0 };

    TestParallelAxis() {}
    virtual ~TestParallelAxis() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestParallelAxis, CanComputeParallelAxisInertia)
{
    // https://en.wikipedia.org/wiki/List_of_moments_of_inertia

    constexpr double l = 1.0;
    constexpr double m = 1.0;

    // Slender rod along y-axis of length l and mass m about center
    mc::Matrix3x3 m1(m*l*l / 12.0, 0.0, 0.0,
                     0.0, 0.0, 0.0,
                     0.0, 0.0, m*l*l / 12.0);

    // Slender rod along y-axis of length l and mass m about end
    mc::Matrix3x3 m2(m*l*l / 3.0, 0.0, 0.0,
                     0.0, 0.0, 0.0,
                     0.0, 0.0, m*l*l / 3.0);

    mc::Vector3 r(0.0, l / 2.0, 0.0);

    mc::Matrix3x3 m3 = mc::ParallelAxisInertia(m, m1, r);

    EXPECT_NEAR(m3(0,0), m2(0,0), 1.0e-12);
    EXPECT_NEAR(m3(0,1), m2(0,1), 1.0e-12);
    EXPECT_NEAR(m3(0,2), m2(0,2), 1.0e-12);

    EXPECT_NEAR(m3(1,0), m2(1,0), 1.0e-12);
    EXPECT_NEAR(m3(1,1), m2(1,1), 1.0e-12);
    EXPECT_NEAR(m3(1,2), m2(1,2), 1.0e-12);

    EXPECT_NEAR(m3(2,0), m2(2,0), 1.0e-12);
    EXPECT_NEAR(m3(2,1), m2(2,1), 1.0e-12);
    EXPECT_NEAR(m3(2,2), m2(2,2), 1.0e-12);
}
