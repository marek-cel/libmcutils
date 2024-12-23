#include <gtest/gtest.h>

#include <mcutils/ctrl/MovingAverage.h>
#include <mcutils/math/Random.h>

class TestMovingAverage : public ::testing::Test
{
protected:

    TestMovingAverage() {}
    virtual ~TestMovingAverage() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMovingAverage, CanInstantiate)
{
    mc::MovingAverage<double> ma;
    EXPECT_EQ(ma.length(), 1);
    EXPECT_NEAR(ma.value(), 0.0, 1.0e-9);
}

TEST_F(TestMovingAverage, CanInstantiateAndSetData)
{
    mc::MovingAverage<double> ma(5, 1.0);
    EXPECT_EQ(ma.length(), 5);
    EXPECT_NEAR(ma.value(), 1.0, 1.0e-9);
}

TEST_F(TestMovingAverage, CanUpdate)
{
    mc::MovingAverage<units::length::meter_t> ma(5);

    units::length::meter_t u[] = { 44.0_m, 64.0_m, 18.0_m, 65.0_m, 81.0_m, 28.0_m, 1.0_m, 25.0_m, 41.0_m, 39.0_m };

    ma.Update(1.0_s, u[0]);
    // 44
    EXPECT_DOUBLE_EQ(ma.value()(), 44.0);

    ma.Update(1.0_s, u[1]);
    // ( 44 + 64 ) / 2 = 54
    EXPECT_DOUBLE_EQ(ma.value()(), 54.0);

    ma.Update(1.0_s, u[2]);
    // ( 44 + 64 + 18 ) / 3 = 42
    EXPECT_DOUBLE_EQ(ma.value()(), 42.0);

    ma.Update(1.0_s, u[3]);
    // ( 44 + 64 + 18 + 65 ) / 4 = 47.75
    EXPECT_DOUBLE_EQ(ma.value()(), 47.75);

    ma.Update(1.0_s, u[4]);
    // ( 44 + 64 + 18 + 65 + 81 ) / 5 = 54.4
    EXPECT_DOUBLE_EQ(ma.value()(), 54.4);

    ma.Update(1.0_s, u[5]);
    // ( 64 + 18 + 65 + 81 + 28 ) / 5 = 51.2
    EXPECT_DOUBLE_EQ(ma.value()(), 51.2);

    ma.Update(1.0_s, u[6]);
    // ( 18 + 65 + 81 + 28 + 1 ) / 5 = 38.6
    EXPECT_DOUBLE_EQ(ma.value()(), 38.6);

    ma.Update(1.0_s, u[7]);
    // ( 65 + 81 + 28 + 1 + 25 ) / 5 = 40
    EXPECT_DOUBLE_EQ(ma.value()(), 40.0);

    ma.Update(1.0_s, u[8]);
    // ( 81 + 28 + 1 + 25 + 41 ) / 5 = 35.2
    EXPECT_DOUBLE_EQ(ma.value()(), 35.2);

    ma.Update(1.0_s, u[9]);
    // ( 28 + 1 + 25 + 41 + 39 ) / 5 = 26.8
    EXPECT_DOUBLE_EQ(ma.value()(), 26.8);
}

TEST_F(TestMovingAverage, CanSetLenght)
{
    mc::MovingAverage<double> ma;
    EXPECT_NO_THROW(ma.set_length(5));
    EXPECT_EQ(ma.length(), 5);
}

TEST_F(TestMovingAverage, CanGetLenght)
{
    mc::MovingAverage<double> ma(7);
    EXPECT_EQ(ma.length(), 7);
}
