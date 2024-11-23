#include <gtest/gtest.h>

#include <mcutils/astro/Ephemeris.h>
#include <mcutils/misc/Units.h>

class TestEphemeris : public ::testing::Test
{
protected:
    TestEphemeris() {}
    virtual ~TestEphemeris() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestEphemeris, CanComputeSun)
{
    // expected values calculated with PyEphem
    // tests/astro/python/test_ephemeris.py

    mc::DateTime dt;
    mc::Ephemeris ephem;

    double tol_rad = mc::Units::deg2rad(0.01);

    dt.year   = 2000;
    dt.month  = 1;
    dt.day    = 1;
    dt.hour   = 0;
    dt.minute = 0;
    dt.second = 0;
    dt.msec   = 0;
    ephem.Update(dt, 0.0, 0.0);
    EXPECT_NEAR(ephem.sun().ra_dec.ra(), 4.899595716773554, tol_rad);
    EXPECT_NEAR(ephem.sun().ra_dec.dec(), -0.40266683881073745, tol_rad);

    dt.year   = 2024;
    dt.month  = 4;
    dt.day    = 24;
    dt.hour   = 17;
    dt.minute = 15;
    dt.second = 30;
    dt.msec   = 0;
    ephem.Update(dt, 0.0, 0.0);
    EXPECT_NEAR(ephem.sun().ra_dec.ra(), 0.571160439394054, tol_rad);
    EXPECT_NEAR(ephem.sun().ra_dec.dec(), 0.23021727848778714, tol_rad);
}

TEST_F(TestEphemeris, CanComputeMoon)
{
    // expected values calculated with PyEphem
    // tests/astro/python/test_ephemeris.py

    mc::DateTime dt;
    mc::Ephemeris ephem;

    double tol_rad = mc::Units::deg2rad(0.1);

    dt.year   = 2000;
    dt.month  = 1;
    dt.day    = 1;
    dt.hour   = 0;
    dt.minute = 0;
    dt.second = 0;
    dt.msec   = 0;
    ephem.Update(dt, 0.0, 0.0);
    EXPECT_NEAR(ephem.moon().ra_dec.ra(), 3.7815961040162467, tol_rad);
    EXPECT_NEAR(ephem.moon().ra_dec.dec(), -0.1569823363895957, tol_rad);

    dt.year   = 2024;
    dt.month  = 4;
    dt.day    = 24;
    dt.hour   = 17;
    dt.minute = 15;
    dt.second = 30;
    dt.msec   = 0;
    ephem.Update(dt, 0.0, 0.0);
    EXPECT_NEAR(ephem.moon().ra_dec.ra(), 3.839393709858737, tol_rad);
    EXPECT_NEAR(ephem.moon().ra_dec.dec(), -0.31637240994389354, tol_rad);
}
