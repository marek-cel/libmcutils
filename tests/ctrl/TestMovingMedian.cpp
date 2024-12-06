#include <gtest/gtest.h>

#include <mcutils/ctrl/MovingMedian.h>
#include <mcutils/math/Random.h>

class TestMovingMedian : public ::testing::Test
{
protected:

    TestMovingMedian() {}
    virtual ~TestMovingMedian() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMovingMedian, CanInstantiate)
{
    mc::MovingMedian<double> mm;
    EXPECT_EQ(mm.length(), 1);
}

TEST_F(TestMovingMedian, CanInstantiateAndSetData)
{
    mc::MovingMedian<double> mm(5);
    EXPECT_EQ(mm.length(), 5);
}

TEST_F(TestMovingMedian, CanUpdate)
{
    mc::MovingMedian<units::length::meter_t> mm(5);

    units::length::meter_t u[] = { 44.0_m, 64.0_m, 18.0_m, 65.0_m, 81.0_m, 28.0_m, 1.0_m, 25.0_m, 41.0_m, 39.0_m };

    mm.Update(1.0_s, u[0]);
    // [44]
    EXPECT_DOUBLE_EQ(mm.value()(), 44.0);

    mm.Update(1.0_s, u[1]);
    // [44, 64]
    // ( 44 + 64 ) / 2 = 54
    EXPECT_DOUBLE_EQ(mm.value()(), 54.0);

    mm.Update(1.0_s, u[2]);
    // 18, [44], 64
    EXPECT_DOUBLE_EQ(mm.value()(), 44.0);

    mm.Update(1.0_s, u[3]);
    // 18, [44, 64], 65
    // ( 44 + 64 ) / 2 = 54
    EXPECT_DOUBLE_EQ(mm.value()(), 54.0);

    mm.Update(1.0_s, u[4]);
    // 18, 44, [64], 65, 81
    EXPECT_DOUBLE_EQ(mm.value()(), 64.0);

    mm.Update(1.0_s, u[5]);
    // 18, 28, [64], 65, 81
    EXPECT_DOUBLE_EQ(mm.value()(), 64.0);

    mm.Update(1.0_s, u[6]);
    // 1, 18, [28], 65, 81
    EXPECT_DOUBLE_EQ(mm.value()(), 28.0);

    mm.Update(1.0_s, u[7]);
    // 1, 25, [28], 65, 81
    EXPECT_DOUBLE_EQ(mm.value()(), 28.0);

    mm.Update(1.0_s, u[8]);
    // 1, 25, [28], 41, 81
    EXPECT_DOUBLE_EQ(mm.value()(), 28.0);

    mm.Update(1.0_s, u[9]);
    // 1, 25, [28], 39, 41
    EXPECT_DOUBLE_EQ(mm.value()(), 28.0);
}

TEST_F(TestMovingMedian, CanSetLenght)
{
    mc::MovingMedian<double> mm;
    EXPECT_NO_THROW(mm.set_length(5));
    EXPECT_EQ(mm.length(), 5);
}

TEST_F(TestMovingMedian, CanGetLenght)
{
    mc::MovingMedian<double> mm(7);
    EXPECT_EQ(mm.length(), 7);
}
