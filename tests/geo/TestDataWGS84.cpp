#include <gtest/gtest.h>

#include <mcutils/geo/DataWGS84.h>

////////////////////////////////////////////////////////////////////////////////

class TestDataWGS84 : public ::testing::Test
{
protected:
    TestDataWGS84() {}
    virtual ~TestDataWGS84() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsEquatorialRadiusCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-2
    EXPECT_NEAR(mc::DataWGS84::a, 6378137.0, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsPolarRadiusCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-7
    EXPECT_NEAR(mc::DataWGS84::b, 6356752.3142, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsEllipsoidFlatteningCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-2
    EXPECT_NEAR(mc::DataWGS84::f, 0.0033528106718309896, 1.0e-9);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsMeanRadiusCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-7
    EXPECT_NEAR(mc::DataWGS84::r1, 6371008.7714, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsEquatorialRadiusSquaredCorrect)
{
    // calculated with GNU Octave
    // tests/geo/python/test_geo_data_wgs84.py
    EXPECT_NEAR(mc::DataWGS84::a2, 40680631590769.0, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsPolarRadiusSquaredCorrect)
{
    // calculated with GNU Octave
    // tests/geo/python/test_geo_data_wgs84.py
    EXPECT_NEAR(mc::DataWGS84::b2, 40408299984087.055, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsEllipsoidFirstEccentricitySquaredCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-7
    EXPECT_NEAR(mc::DataWGS84::e2, 6.69437999014e-3, 1.0e-12);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsEllipsoidFirstEccentricityCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-7
    EXPECT_NEAR(mc::DataWGS84::e, 8.1819190842622e-2, 1.0e-12);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsEllipsoidSecondEccentricitySquaredCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-7
    EXPECT_NEAR(mc::DataWGS84::ep2, 6.73949674228e-3, 1.0e-12);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsEllipsoidSecondEccentricityCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-7
    EXPECT_NEAR(mc::DataWGS84::ep, 8.2094437949696e-2, 1.0e-12);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsMassOfEarthCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-7
    EXPECT_NEAR(mc::DataWGS84::me, 5.9733328e24, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsEarthGravitationalConstantCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-5
    EXPECT_NEAR(mc::DataWGS84::gm, 3986004.418e8, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsEarthAngularVelocityCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-5
    EXPECT_NEAR(mc::DataWGS84::omega, 7292115.0e-11, 1.0e-9);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsNormalGravityMeanValueCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.37
    EXPECT_NEAR(mc::DataWGS84::gamma, 9.7976432222, 1.0e-9);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsNormalGravityAtEquatorCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-7
    EXPECT_NEAR(mc::DataWGS84::gamma_e, 9.7803253359, 1.0e-9);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsNormalGravityAtPoleCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-7
    EXPECT_NEAR(mc::DataWGS84::gamma_p, 9.8321849378, 1.0e-9);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsTheoreticalGravityConstantCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-7
    EXPECT_NEAR(mc::DataWGS84::k, 0.00193185265241, 1.0e-12);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataWGS84, IsMConstantCorrect)
{
    // Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000, p.3-7
    EXPECT_NEAR(mc::DataWGS84::m, 0.00344978650684, 1.0e-12);
}
