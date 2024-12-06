#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/astro/Utils.h>
#include <mcutils/misc/Units.h>

class TestRaDec2AzEl : public ::testing::Test
{
protected:
    TestRaDec2AzEl() {}
    virtual ~TestRaDec2AzEl() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestRaDec2AzEl, CanComputeAzElFromRaDecLatAndLST1)
{
    // expected values calculated with PyEphem
    // tests/astro/python/test_radec2azel.py

    mc::AzEl azel;
    mc::RaDec radec;

    radec.ra = 5.623280496934751_rad;
    radec.dec = -0.2513744984225895_rad;

    units::angle::radian_t lat = 52.2296756_deg;
    units::angle::radian_t lst = 5.956121595178459_rad;

    azel = mc::RaDec2AzEl(radec, lat, lst);

    EXPECT_NEAR(azel.az(), 3.4882750511169434, 1.0e-3);
    EXPECT_NEAR(azel.el(), 0.3733336627483368, 1.0e-3);
}
