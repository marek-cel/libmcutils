#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/astro/GregorianCal.h>

class TestGregorianCal : public ::testing::Test
{
protected:
    TestGregorianCal() {}
    virtual ~TestGregorianCal() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestGregorianCal, CanDetermineLeapYear)
{
    EXPECT_TRUE(mc::GregorianCal::IsLeapYear(1600));
    EXPECT_TRUE(mc::GregorianCal::IsLeapYear(2000));
    EXPECT_TRUE(mc::GregorianCal::IsLeapYear(2004));
    EXPECT_TRUE(mc::GregorianCal::IsLeapYear(2024));
    EXPECT_TRUE(mc::GregorianCal::IsLeapYear(2400));

    EXPECT_FALSE(mc::GregorianCal::IsLeapYear(1900));
    EXPECT_FALSE(mc::GregorianCal::IsLeapYear(2001));
    EXPECT_FALSE(mc::GregorianCal::IsLeapYear(2025));
    EXPECT_FALSE(mc::GregorianCal::IsLeapYear(2100));
}

TEST_F(TestGregorianCal, CanGetDaysInYear)
{
    EXPECT_EQ(mc::GregorianCal::GetDaysInYear(1600), 366);
    EXPECT_EQ(mc::GregorianCal::GetDaysInYear(1900), 365);
    EXPECT_EQ(mc::GregorianCal::GetDaysInYear(2000), 366);
    EXPECT_EQ(mc::GregorianCal::GetDaysInYear(2001), 365);
    EXPECT_EQ(mc::GregorianCal::GetDaysInYear(2024), 366);
    EXPECT_EQ(mc::GregorianCal::GetDaysInYear(2100), 365);
}

TEST_F(TestGregorianCal, CanGetDayOfYear)
{
    mc::DateTime dt;

    dt.year   = 2000;
    dt.month  = 1;
    dt.day    = 1;
    dt.hour   = 0;
    dt.minute = 0;
    dt.second = 0;
    dt.msec   = 0;
    EXPECT_DOUBLE_EQ(mc::GregorianCal::GetDayOfYear(dt), 0.0);

    dt.year   = 2000;
    dt.month  = 1;
    dt.day    = 1;
    dt.hour   = 12;
    dt.minute = 0;
    dt.second = 0;
    dt.msec   = 0;
    EXPECT_DOUBLE_EQ(mc::GregorianCal::GetDayOfYear(dt), 0.5);

    dt.year   = 2000;
    dt.month  = 3;
    dt.day    = 1;
    dt.hour   = 0;
    dt.minute = 0;
    dt.second = 0;
    dt.msec   = 0;
    EXPECT_DOUBLE_EQ(mc::GregorianCal::GetDayOfYear(dt), 60.0);

    dt.year   = 2024;
    dt.month  = 5;
    dt.day    = 14;
    dt.hour   = 12;
    dt.minute = 54;
    dt.second = 0;
    dt.msec   = 0;
    EXPECT_DOUBLE_EQ(mc::GregorianCal::GetDayOfYear(dt), 134.5375);
}
