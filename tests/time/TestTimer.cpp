#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/time/Timer.h>

void dummyTimeConsumingOperations()
{
    double y = 0.0;
    for (int i = 0; i < 10000; ++i)
    {
        double x = pow(sin(i), 2.0) + pow(cos(i), 2.0);
        y += x;
    }
}

class TestTimer : public ::testing::Test
{
protected:
    TestTimer() {}
    virtual ~TestTimer() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestTimer, CanWaitForTimeout)
{
    constexpr double time_step = 0.01;
    constexpr double precision = 0.001;
    mc::Timer timer;
    timer.Start(std::chrono::milliseconds(static_cast<unsigned int>(time_step * 1000)));
    for ( int i = 0; i < 10; ++i )
    {
        std::chrono::microseconds step_us = timer.WaitForTimeout();
        double step_sec = static_cast<double>(step_us.count()) / 1.0e6;
        dummyTimeConsumingOperations();
        EXPECT_NEAR(time_step, step_sec, precision);
    }
}
