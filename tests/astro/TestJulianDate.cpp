#include <gtest/gtest.h>

#include <mcutils/astro/JulianDate.h>

class TestJulianDate : public ::testing::Test
{
protected:
    TestJulianDate() {}
    virtual ~TestJulianDate() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestJulianDate, CanCalculateJulianDay)
{
    // expected values calculated with astropy
    // tests/astro/python/test_julian_date.py

    mc::DateTime dt;
    mc::JulianDate jd;

    dt.year   = 2000;
    dt.month  = 1;
    dt.day    = 1;
    dt.hour   = 0;
    dt.minute = 0;
    dt.second = 0;
    dt.msec   = 0;
    jd.SetFromGregorianDate(dt);
    EXPECT_DOUBLE_EQ(jd.jd(), 2451544.5);

    dt.year   = 2024;
    dt.month  = 4;
    dt.day    = 24;
    dt.hour   = 17;
    dt.minute = 15;
    dt.second = 30;
    dt.msec   = 0;
    jd.SetFromGregorianDate(dt);
    EXPECT_DOUBLE_EQ(jd.jd(), 2460425.219097222);
}
