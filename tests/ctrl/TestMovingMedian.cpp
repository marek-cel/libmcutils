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
    mc::MovingMedian mm;
    EXPECT_EQ(mm.length(), 1);
}

TEST_F(TestMovingMedian, CanInstantiateAndSetData)
{
    mc::MovingMedian mm(5);
    EXPECT_EQ(mm.length(), 5);
}

TEST_F(TestMovingMedian, CanUpdate)
{
    mc::MovingMedian mm(5);

    double u[] = { 44.0, 64.0, 18.0, 65.0, 81.0, 28.0, 1.0, 25.0, 41.0, 39.0 };

    mm.Update(1.0, u[0]);
    // [44]
    EXPECT_DOUBLE_EQ(mm.value(), 44.0);

    mm.Update(1.0, u[1]);
    // [44, 64]
    // ( 44 + 64 ) / 2 = 54
    EXPECT_DOUBLE_EQ(mm.value(), 54.0);

    mm.Update(1.0, u[2]);
    // 18, [44], 64
    EXPECT_DOUBLE_EQ(mm.value(), 44.0);

    mm.Update(1.0, u[3]);
    // 18, [44, 64], 65
    // ( 44 + 64 ) / 2 = 54
    EXPECT_DOUBLE_EQ(mm.value(), 54.0);

    mm.Update(1.0, u[4]);
    // 18, 44, [64], 65, 81
    EXPECT_DOUBLE_EQ(mm.value(), 64.0);

    mm.Update(1.0, u[5]);
    // 18, 28, [64], 65, 81
    EXPECT_DOUBLE_EQ(mm.value(), 64.0);

    mm.Update(1.0, u[6]);
    // 1, 18, [28], 65, 81
    EXPECT_DOUBLE_EQ(mm.value(), 28.0);

    mm.Update(1.0, u[7]);
    // 1, 25, [28], 65, 81
    EXPECT_DOUBLE_EQ(mm.value(), 28.0);

    mm.Update(1.0, u[8]);
    // 1, 25, [28], 41, 81
    EXPECT_DOUBLE_EQ(mm.value(), 28.0);

    mm.Update(1.0, u[9]);
    // 1, 25, [28], 39, 41
    EXPECT_DOUBLE_EQ(mm.value(), 28.0);
}

TEST_F(TestMovingMedian, CanSetLenght)
{
    mc::MovingMedian mm;
    EXPECT_NO_THROW(mm.set_length(5));
    EXPECT_EQ(mm.length(), 5);
}

TEST_F(TestMovingMedian, CanGetLenght)
{
    mc::MovingMedian mm(7);
    EXPECT_EQ(mm.length(), 7);
}
