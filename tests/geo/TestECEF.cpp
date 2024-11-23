#include <gtest/gtest.h>

#include <mcutils/geo/ECEF.h>

#include <mcutils/geo/Mars2015.h>
#include <mcutils/geo/WGS84.h>

// linear position tolerance (0.1 mm)
#define LINEAR_POSITION_TOLERANCE 1.0e-4
// latitude and longitude tolerance (10^-9 rad ~ ca. 6 mm)
#define LAT_LON_TOLERANCE 1.0e-9
// attitude tolerance (10^-6 rad ~ ca. 0.00005 deg)
#define ATTITUDE_TOLERANCE 1.0e-6

class TestECEF : public ::testing::Test
{
protected:
    TestECEF() {}
    virtual ~TestECEF() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestECEF, CanConstruct)
{
    mc::ECEF* ecef = nullptr;
    EXPECT_NO_THROW(ecef = new mc::ECEF(mc::WGS84::ellipsoid));
    delete ecef;
}

TEST_F(TestECEF, CanDestruct)
{
    mc::ECEF* ecef = new mc::ECEF(mc::WGS84::ellipsoid);
    EXPECT_NO_THROW(delete ecef);
}

TEST_F(TestECEF, CanInstantiate)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);

    EXPECT_NEAR(ecef.pos_cart().x(), mc::WGS84::ellipsoid.a(), LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(ecef.pos_cart().y(), 0.0, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(ecef.pos_cart().z(), 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanConvertFromCartToGeoAt0N0E0H)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 0N 0E
    pos_cart.x() = mc::WGS84::ellipsoid.a();
    pos_cart.y() = 0.0;
    pos_cart.z() = 0.0;

    ecef.ConvertCart2Geo(pos_cart, &pos_geo);
    EXPECT_NEAR(pos_geo.lat(), 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon(), 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt(), 0.0, LINEAR_POSITION_TOLERANCE);

    pos_geo = ecef.ConvertCart2Geo(pos_cart);
    EXPECT_NEAR(pos_geo.lat(), 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon(), 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt(), 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanConvertFromCartToGeoAt45N45E100H)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 45N 45E H=100m
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_cart.x() = 3194469.1450605746;
    pos_cart.y() = 3194469.145060574;
    pos_cart.z() = 4487419.119544039;

    ecef.ConvertCart2Geo(pos_cart, &pos_geo);
    EXPECT_NEAR(pos_geo.lat(), M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon(), M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt(), 100.0  , LINEAR_POSITION_TOLERANCE);

    pos_geo = ecef.ConvertCart2Geo(pos_cart);
    EXPECT_NEAR(pos_geo.lat(), M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon(), M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt(), 100.0  , LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanConvertFromGeoToCartAt0N0E0H)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 0N 0E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;

    ecef.ConvertGeo2Cart(pos_geo, &pos_cart);
    EXPECT_NEAR(pos_cart.x(), mc::WGS84::ellipsoid.a(), LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 0.0, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 0.0, LINEAR_POSITION_TOLERANCE);

    pos_cart = ecef.ConvertGeo2Cart(pos_geo);
    EXPECT_NEAR(pos_cart.x(), mc::WGS84::ellipsoid.a(), LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 0.0, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanConvertFromGeoToCartAt45N45E100H)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 45N 45E H=100m
    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_geo.lat = 45.0_deg;
    pos_geo.lon = 45.0_deg;
    pos_geo.alt = 100.0_m;

    ecef.ConvertGeo2Cart(pos_geo, &pos_cart);
    EXPECT_NEAR(pos_cart.x(), 3194469.1450605746 , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 3194469.145060574  , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 4487419.119544039  , LINEAR_POSITION_TOLERANCE);

    pos_cart = ecef.ConvertGeo2Cart(pos_geo);
    EXPECT_NEAR(pos_cart.x(), 3194469.1450605746 , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 3194469.145060574  , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 4487419.119544039  , LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanGetGeoOffsetHeading0)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);

    constexpr double nautical_mile = 1852.0;
    constexpr double arc_min = (1.0 / 60.0) * M_PI / 180.0;

    // as one nautical mile is equal to one arc minute only on the great circle
    // tolerance for those tests is higher than for typical lat/lon position
    constexpr double tolerance = 1.0e-5;

    mc::Geo pos_geo;
    mc::Geo pos_geo_off;

    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    // HDG = 0
    pos_geo_off = ecef.GetGeoOffset(0.0_deg, nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat() + arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon(), tolerance);

    pos_geo_off = ecef.GetGeoOffset(0.0_deg, -nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat() - arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon(), tolerance);

    pos_geo_off = ecef.GetGeoOffset(0.0_deg, 0.0, nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat(), tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon() + arc_min, tolerance);

    pos_geo_off = ecef.GetGeoOffset(0.0_deg, 0.0, -nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat(), tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon() - arc_min, tolerance);
}

TEST_F(TestECEF, CanGetGeoOffsetHeading90)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);

    constexpr double nautical_mile = 1852.0;
    constexpr double arc_min = (1.0 / 60.0) * M_PI / 180.0;

    // as one nautical mile is equal to one arc minute only on the great circle
    // tolerance for those tests is higher than for typical lat/lon position
    constexpr double tolerance = 1.0e-5;

    mc::Geo pos_geo;
    mc::Geo pos_geo_off;

    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    // HDG = 90
    pos_geo_off = ecef.GetGeoOffset(90.0_deg, nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat(), tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon() + arc_min, tolerance);

    pos_geo_off = ecef.GetGeoOffset(90.0_deg, -nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat(), tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon() - arc_min, tolerance);

    pos_geo_off = ecef.GetGeoOffset(90.0_deg, 0.0, nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat() - arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon(), tolerance);

    pos_geo_off = ecef.GetGeoOffset(90.0_deg, 0.0, -nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat() + arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon(), tolerance);
}

TEST_F(TestECEF, CanGetGeoOffsetHeadingMinus90)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);

    constexpr double nautical_mile = 1852.0;
    constexpr double arc_min = (1.0 / 60.0) * M_PI / 180.0;

    // as one nautical mile is equal to one arc minute only on the great circle
    // tolerance for those tests is higher than for typical lat/lon position
    constexpr double tolerance = 1.0e-5;

    mc::Geo pos_geo;
    mc::Geo pos_geo_off;

    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    // HDG = -90
    pos_geo_off = ecef.GetGeoOffset(-90.0_deg, nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat(), tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon() - arc_min, tolerance);

    pos_geo_off = ecef.GetGeoOffset(-90.0_deg, -nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat(), tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon() + arc_min, tolerance);

    pos_geo_off = ecef.GetGeoOffset(-90.0_deg, 0.0, nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat() + arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon(), tolerance);

    pos_geo_off = ecef.GetGeoOffset(-90.0_deg, 0.0, -nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat() - arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon(), tolerance);
}

TEST_F(TestECEF, CanGetGeoOffsetHeading180)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);

    constexpr double nautical_mile = 1852.0;
    constexpr double arc_min = (1.0 / 60.0) * M_PI / 180.0;

    // as one nautical mile is equal to one arc minute only on the great circle
    // tolerance for those tests is higher than for typical lat/lon position
    constexpr double tolerance = 1.0e-5;

    mc::Geo pos_geo;
    mc::Geo pos_geo_off;

    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    // HDG = 180
    pos_geo_off = ecef.GetGeoOffset(180.0_deg, nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat() - arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon(), tolerance);

    pos_geo_off = ecef.GetGeoOffset(180.0_deg, -nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat() + arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon(), tolerance);

    pos_geo_off = ecef.GetGeoOffset(180.0_deg, 0.0, nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat(), tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon() - arc_min, tolerance);

    pos_geo_off = ecef.GetGeoOffset(180.0_deg, 0.0, -nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat(), pos_geo.lat(), tolerance);
    EXPECT_NEAR(pos_geo_off.lon(), pos_geo.lon() + arc_min, tolerance);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesECEF2ENUAt0N0E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_enu;

    // 0N 0E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_enu = ecef.ConvertAttitudeECEF2ENU(angles_ecef);

    EXPECT_NEAR(angles_enu.phi()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_enu.tht()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_enu.psi()(), 0.0     , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesECEF2ENUAt0N90E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_enu;

    // 0N 90E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 90.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_enu = ecef.ConvertAttitudeECEF2ENU(angles_ecef);

    EXPECT_NEAR(angles_enu.phi()(), M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_enu.tht()(), 0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_enu.psi()(), M_PI   , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesECEF2ENUAt0N90W)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_enu;

    // 0N 90W
    pos_geo.lat =  0.0_deg;
    pos_geo.lon = -90.0_deg;
    pos_geo.alt =  0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_enu = ecef.ConvertAttitudeECEF2ENU(angles_ecef);

    EXPECT_NEAR(angles_enu.phi()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_enu.tht()(), 0.0     , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_enu.psi()(), 0.0     , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesECEF2ENUAt0N180E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_enu;

    // 0N 180E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 180.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_enu = ecef.ConvertAttitudeECEF2ENU(angles_ecef);

    EXPECT_NEAR(angles_enu.phi()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_enu.tht()(),  M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_enu.psi()(),     0.0 , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesENU2ECEFAt0N0E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_enu;

    // 0N 0E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_enu.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_ecef = ecef.ConvertAttitudeENU2ECEF(angles_ecef);

    EXPECT_NEAR(angles_ecef.phi()(), M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht()(),    0.0 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi()(), M_PI_2 , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesENU2ECEFAt0N90E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_enu;

    // 0N 90E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 90.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_enu.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_ecef = ecef.ConvertAttitudeENU2ECEF(angles_ecef);

    EXPECT_NEAR(angles_ecef.phi()(), M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht()(),    0.0 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi()(),   M_PI , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesENU2ECEFAt0N90W)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_enu;

    // 0N 90W
    pos_geo.lat =  0.0_deg;
    pos_geo.lon = -90.0_deg;
    pos_geo.alt =  0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_enu.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_ecef = ecef.ConvertAttitudeENU2ECEF(angles_ecef);

    EXPECT_NEAR(angles_ecef.phi()(), M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht()(),    0.0 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi()(),    0.0 , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesENU2ECEFAt0N180E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_enu;

    // 0N 180E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 180.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_enu.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_ecef = ecef.ConvertAttitudeENU2ECEF(angles_ecef);

    EXPECT_NEAR(angles_ecef.phi()(),  M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht()(),     0.0 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi()(), M_PI_2 + M_PI , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesECEF2NEDAt0N0E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 0E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_ned = ecef.ConvertAttitudeECEF2NED(angles_ecef);

    EXPECT_NEAR(angles_ned.phi()(), 0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht()(), M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi()(), 0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesECEF2NEDAt0N90E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 90E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 90.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_ned = ecef.ConvertAttitudeECEF2NED(angles_ecef);

    EXPECT_NEAR(angles_ned.phi()(), -M_PI_2    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht()(), 0.0        , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi()(), 1.5 * M_PI , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesECEF2NEDAt0N90W)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 90W
    pos_geo.lat =  0.0_deg;
    pos_geo.lon = -90.0_deg;
    pos_geo.alt =  0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_ned = ecef.ConvertAttitudeECEF2NED(angles_ecef);

    EXPECT_NEAR(angles_ned.phi()(), M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht()(), 0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi()(), M_PI_2 , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesECEF2NEDAt0N180E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 180E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 180.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_ned = ecef.ConvertAttitudeECEF2NED(angles_ecef);

    EXPECT_NEAR(angles_ned.phi()(),  M_PI   , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi()(),  0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesNED2ECEFAt0N0E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 0E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ned.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_ecef = ecef.ConvertAttitudeNED2ECEF(angles_ned);

    EXPECT_NEAR(angles_ecef.phi()(),  0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi()(),  0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesNED2ECEFAt0N90E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 90E
    pos_geo.lat =  0.0_deg;
    pos_geo.lon = 90.0_deg;
    pos_geo.alt =  0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ned.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_ecef = ecef.ConvertAttitudeNED2ECEF(angles_ned);

    EXPECT_NEAR(angles_ecef.psi()(),  0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.phi()(),  M_PI_2 , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesNED2ECEFAt0N90W)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 90W
    pos_geo.lat =   0.0_deg;
    pos_geo.lon = -90.0_deg;
    pos_geo.alt =   0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ned.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_ecef = ecef.ConvertAttitudeNED2ECEF(angles_ned);

    EXPECT_NEAR(angles_ecef.psi()(),  0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.phi()(), -M_PI_2 , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesNED2ECEFAt0N180E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 180E
    pos_geo.lat =   0.0_deg;
    pos_geo.lon = 180.0_deg;
    pos_geo.alt =   0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ned.Set(0.0_deg, 0.0_deg, 0.0_deg);
    angles_ecef = ecef.ConvertAttitudeNED2ECEF(angles_ned);

    EXPECT_NEAR(angles_ecef.psi()(),  0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.phi()(),  M_PI   , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsECEF2NEDAt0N0E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;
    mc::Quaternion ned2bas;

    // 0N 0E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.phi() =   0.0_deg;
    angles_ecef.tht() = -90.0_deg;
    angles_ecef.psi() =   0.0_deg;

    ned2bas = ecef.ConvertAttitudeECEF2NED(mc::Quaternion(angles_ecef));
    angles_ned = ned2bas.GetAngles();
    angles_ned.Normalize();

    EXPECT_NEAR(angles_ned.phi()(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht()(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi()(), 0.0, ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsECEF2NEDAt0N90E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;
    mc::Quaternion ned2bas;

    // 0N 90E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 90.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.phi() =   0.0_deg;
    angles_ecef.tht() = -90.0_deg;
    angles_ecef.psi() =  90.0_deg;

    ned2bas = ecef.ConvertAttitudeECEF2NED(mc::Quaternion(angles_ecef));
    angles_ned = ned2bas.GetAngles();
    angles_ned.Normalize();

    EXPECT_NEAR(angles_ned.phi()(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht()(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi()(), 0.0, ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsECEF2NEDAt0N90W)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;
    mc::Quaternion ned2bas;

    // 0N 90W
    pos_geo.lat =  0.0_deg;
    pos_geo.lon = -90.0_deg;
    pos_geo.alt =  0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.phi() =   0.0_deg;
    angles_ecef.tht() = -90.0_deg;
    angles_ecef.psi() = -90.0_deg;

    ned2bas = ecef.ConvertAttitudeECEF2NED(mc::Quaternion(angles_ecef));
    angles_ned = ned2bas.GetAngles();
    angles_ned.Normalize();

    EXPECT_NEAR(angles_ned.phi()(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht()(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi()(), 0.0, ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsECEF2NEDAt0N180E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;
    mc::Quaternion ned2bas;

    // 0N 180E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 180.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.phi() =   0.0_deg;
    angles_ecef.tht() = -90.0_deg;
    angles_ecef.psi() = 180.0_deg;

    ned2bas = ecef.ConvertAttitudeECEF2NED(mc::Quaternion(angles_ecef));
    angles_ned = ned2bas.GetAngles();
    angles_ned.Normalize();

    EXPECT_NEAR(angles_ned.phi()(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht()(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi()(), 0.0, ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsNED2ECEFAt0N0E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Quaternion ecef2bas;

    // 0N 0E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2bas = ecef.ConvertAttitudeNED2ECEF(mc::Quaternion());
    angles_ecef = ecef2bas.GetAngles();
    angles_ecef.Normalize();

    EXPECT_NEAR(angles_ecef.phi()(),  0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi()(),  0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsNED2ECEFAt0N90E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Quaternion ecef2bas;

    // 0N 90E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 90.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2bas = ecef.ConvertAttitudeNED2ECEF(mc::Quaternion());
    angles_ecef = ecef2bas.GetAngles();
    angles_ecef.Normalize();

    EXPECT_NEAR(angles_ecef.phi()(),  M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi()(),  0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsNED2ECEFAt0N90W)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Quaternion ecef2bas;

    // 0N 90W
    pos_geo.lat =  0.0_deg;
    pos_geo.lon = -90.0_deg;
    pos_geo.alt =  0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2bas = ecef.ConvertAttitudeNED2ECEF(mc::Quaternion());
    angles_ecef = ecef2bas.GetAngles();
    angles_ecef.Normalize();

    EXPECT_NEAR(angles_ecef.phi()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi()(),  0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsNED2ECEFAt0N180E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Quaternion ecef2bas;

    // 0N 180E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 180.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2bas = ecef.ConvertAttitudeNED2ECEF(mc::Quaternion());
    angles_ecef = ecef2bas.GetAngles();
    angles_ecef.Normalize();

    EXPECT_NEAR(angles_ecef.phi()(),  M_PI   , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht()(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi()(),  0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanUpdateAndGetPosGeoAt0N0E0H)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 0N 0E
    pos_cart.x() = mc::WGS84::ellipsoid.a();
    pos_cart.y() = 0.0;
    pos_cart.z() = 0.0;
    ecef.SetPositionFromCart(pos_cart);

    pos_geo = ecef.pos_geo();

    EXPECT_NEAR(pos_geo.lat(), 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon(), 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt(), 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanUpdateAndGetPosGeoAt45N45E100H)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 45N 45E H=100m
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_cart.x() = 3194469.1450605746;
    pos_cart.y() = 3194469.145060574;
    pos_cart.z() = 4487419.119544039;
    ecef.SetPositionFromCart(pos_cart);

    pos_geo = ecef.pos_geo();

    EXPECT_NEAR(pos_geo.lat(), M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon(), M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt(), 100.0  , LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanUpdateAndGetPosCartAt0N0E0H)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 0N 0E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;

    ecef.SetPositionFromGeo(pos_geo);
    pos_cart = ecef.pos_cart();
    EXPECT_NEAR(pos_cart.x(), mc::WGS84::ellipsoid.a(), LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 0.0, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanUpdateAndGetPosCartAt45N45E100H)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 45N 45E H=100m
    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_geo.lat = 45.0_deg;
    pos_geo.lon = 45.0_deg;
    pos_geo.alt = 100.0_m;

    ecef.SetPositionFromGeo(pos_geo);
    pos_cart = ecef.pos_cart();
    EXPECT_NEAR(pos_cart.x(), 3194469.1450605746 , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 3194469.145060574  , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 4487419.119544039  , LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanGetENU2NED)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Matrix3x3 enu2ned = ecef.enu2ned();

    const mc::Vector3 v_enu(1.0, 2.0, 3.0);
    mc::Vector3 v_ned = enu2ned * v_enu;

    EXPECT_DOUBLE_EQ(v_ned.x(),  2.0);
    EXPECT_DOUBLE_EQ(v_ned.y(),  1.0);
    EXPECT_DOUBLE_EQ(v_ned.z(), -3.0);
}

TEST_F(TestECEF, CanGetNED2ENU)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Matrix3x3 ned2enu = ecef.ned2enu();

    const mc::Vector3 v_ned(1.0, 2.0, 3.0);
    mc::Vector3 v_enu = ned2enu * v_ned;

    EXPECT_DOUBLE_EQ(v_enu.x(),  2.0);
    EXPECT_DOUBLE_EQ(v_enu.y(),  1.0);
    EXPECT_DOUBLE_EQ(v_enu.z(), -3.0);
}

TEST_F(TestECEF, CanGetENU2ECEFAt0N0E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 enu2ecef;

    const mc::Vector3 v_enu(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 0E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    enu2ecef = ecef.enu2ecef();
    v_ecef = enu2ecef * v_enu;

    EXPECT_DOUBLE_EQ(v_ecef.x(),  3.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(),  1.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  2.0);
}

TEST_F(TestECEF, CanGetENU2ECEFAt0N90E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 enu2ecef;

    const mc::Vector3 v_enu(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 90E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 90.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    enu2ecef = ecef.enu2ecef();
    v_ecef = enu2ecef * v_enu;

    EXPECT_DOUBLE_EQ(v_ecef.x(), -1.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(),  3.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  2.0);
}

TEST_F(TestECEF, CanGetENU2ECEFAt0N90W)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 enu2ecef;

    const mc::Vector3 v_enu(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 90W
    pos_geo.lat =  0.0_deg;
    pos_geo.lon = -90.0_deg;
    pos_geo.alt =  0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    enu2ecef = ecef.enu2ecef();
    v_ecef = enu2ecef * v_enu;

    EXPECT_DOUBLE_EQ(v_ecef.x(),  1.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(), -3.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  2.0);
}

TEST_F(TestECEF, CanGetENU2ECEFAt0N180E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 enu2ecef;

    const mc::Vector3 v_enu(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 180E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 180.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    enu2ecef = ecef.enu2ecef();
    v_ecef = enu2ecef * v_enu;

    EXPECT_DOUBLE_EQ(v_ecef.x(), -3.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(), -1.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  2.0);
}

TEST_F(TestECEF, CanGetNED2ECEFAt0N0E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 ned2ecef;

    const mc::Vector3 v_ned(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 0E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ned2ecef = ecef.ned2ecef();
    v_ecef = ned2ecef * v_ned;

    EXPECT_DOUBLE_EQ(v_ecef.x(), -3.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(),  2.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  1.0);
}

TEST_F(TestECEF, CanGetNED2ECEFAt0N90E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 ned2ecef;

    const mc::Vector3 v_ned(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 90E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 90.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ned2ecef = ecef.ned2ecef();
    v_ecef = ned2ecef * v_ned;

    EXPECT_DOUBLE_EQ(v_ecef.x(), -2.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(), -3.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  1.0);
}

TEST_F(TestECEF, CanGetNED2ECEFAt0N90W)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 ned2ecef;

    const mc::Vector3 v_ned(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 90W
    pos_geo.lat =  0.0_deg;
    pos_geo.lon = -90.0_deg;
    pos_geo.alt =  0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ned2ecef = ecef.ned2ecef();
    v_ecef = ned2ecef * v_ned;

    EXPECT_DOUBLE_EQ(v_ecef.x(),  2.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(),  3.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  1.0);
}

TEST_F(TestECEF, CanGetNED2ECEFAt0N180E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 ned2ecef;

    const mc::Vector3 v_ned(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 180E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 180.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ned2ecef = ecef.ned2ecef();
    v_ecef = ned2ecef * v_ned;

    EXPECT_DOUBLE_EQ(v_ecef.x(),  3.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(), -2.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  1.0);
}

TEST_F(TestECEF, CanGetECEF2ENUAt0N0E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2enu;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_enu;

    // 0N 0E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2enu = ecef.ecef2enu();
    v_enu = ecef2enu * v_ecef;

    EXPECT_DOUBLE_EQ(v_enu.x(),  2.0);
    EXPECT_DOUBLE_EQ(v_enu.y(),  3.0);
    EXPECT_DOUBLE_EQ(v_enu.z(),  1.0);
}

TEST_F(TestECEF, CanGetECEF2ENUAt0N90E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2enu;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_enu;

    // 0N 90E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 90.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2enu = ecef.ecef2enu();
    v_enu = ecef2enu * v_ecef;

    EXPECT_DOUBLE_EQ(v_enu.x(), -1.0);
    EXPECT_DOUBLE_EQ(v_enu.y(),  3.0);
    EXPECT_DOUBLE_EQ(v_enu.z(),  2.0);
}

TEST_F(TestECEF, CanGetECEF2ENUAt0N90W)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2enu;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_enu;

    // 0N 90W
    pos_geo.lat =  0.0_deg;
    pos_geo.lon = -90.0_deg;
    pos_geo.alt =  0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2enu = ecef.ecef2enu();
    v_enu = ecef2enu * v_ecef;

    EXPECT_DOUBLE_EQ(v_enu.x(),  1.0);
    EXPECT_DOUBLE_EQ(v_enu.y(),  3.0);
    EXPECT_DOUBLE_EQ(v_enu.z(), -2.0);
}

TEST_F(TestECEF, CanGetECEF2ENUAt0N180E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2enu;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_enu;

    // 0N 180E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 180.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2enu = ecef.ecef2enu();
    v_enu = ecef2enu * v_ecef;

    EXPECT_DOUBLE_EQ(v_enu.x(), -2.0);
    EXPECT_DOUBLE_EQ(v_enu.y(),  3.0);
    EXPECT_DOUBLE_EQ(v_enu.z(), -1.0);
}

TEST_F(TestECEF, CanGetECEF2NEDAt0N0E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2ned;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_ned;

    // 0N 0E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 0.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2ned = ecef.ecef2ned();
    v_ned = ecef2ned * v_ecef;

    EXPECT_DOUBLE_EQ(v_ned.x(),  3.0);
    EXPECT_DOUBLE_EQ(v_ned.y(),  2.0);
    EXPECT_DOUBLE_EQ(v_ned.z(), -1.0);
}

TEST_F(TestECEF, CanGetECEF2NEDAt0N90E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2ned;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_ned;

    // 0N 90E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 90.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2ned = ecef.ecef2ned();
    v_ned = ecef2ned * v_ecef;

    EXPECT_DOUBLE_EQ(v_ned.x(),  3.0);
    EXPECT_DOUBLE_EQ(v_ned.y(), -1.0);
    EXPECT_DOUBLE_EQ(v_ned.z(), -2.0);
}

TEST_F(TestECEF, CanGetECEF2NEDAt0N90W)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2ned;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_ned;

    // 0N 90W
    pos_geo.lat =  0.0_deg;
    pos_geo.lon = -90.0_deg;
    pos_geo.alt =  0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2ned = ecef.ecef2ned();
    v_ned = ecef2ned * v_ecef;

    EXPECT_DOUBLE_EQ(v_ned.x(),  3.0);
    EXPECT_DOUBLE_EQ(v_ned.y(),  1.0);
    EXPECT_DOUBLE_EQ(v_ned.z(),  2.0);
}

TEST_F(TestECEF, CanGetECEF2NEDAt0N180E)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2ned;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_ned;

    // 0N 180E
    pos_geo.lat = 0.0_deg;
    pos_geo.lon = 180.0_deg;
    pos_geo.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2ned = ecef.ecef2ned();
    v_ned = ecef2ned * v_ecef;

    EXPECT_DOUBLE_EQ(v_ned.x(),  3.0);
    EXPECT_DOUBLE_EQ(v_ned.y(), -2.0);
    EXPECT_DOUBLE_EQ(v_ned.z(),  1.0);
}

TEST_F(TestECEF, CanSetPositionFromGeoAt0N0E0H)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo_in;
    mc::Geo pos_geo;

    // 0N 0E
    pos_geo_in.lat = 0.0_deg;
    pos_geo_in.lon = 0.0_deg;
    pos_geo_in.alt = 0.0_m;
    ecef.SetPositionFromGeo(pos_geo_in);

    pos_geo = ecef.pos_geo();

    EXPECT_NEAR(pos_geo.lat(), 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon(), 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt(), 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanSetPositionFromGeoAt45N45E100H)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Geo pos_geo_in;
    mc::Geo pos_geo;

    // 45N 45E H=100m
    pos_geo_in.lat = 45.0_deg;
    pos_geo_in.lon = 45.0_deg;
    pos_geo_in.alt = 100.0_m;
    ecef.SetPositionFromGeo(pos_geo_in);

    pos_geo = ecef.pos_geo();

    EXPECT_NEAR(pos_geo.lat(), M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon(), M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt(), 100.0  , LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanSetPositionFromCartAt0N0E0H)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Vector3 pos_cart_in;
    mc::Vector3 pos_cart;

    // 0N 0E
    pos_cart_in.x() = mc::WGS84::ellipsoid.a();
    pos_cart_in.y() = 0.0;
    pos_cart_in.z() = 0.0;
    ecef.SetPositionFromCart(pos_cart_in);

    pos_cart = ecef.pos_cart();
    EXPECT_NEAR(pos_cart.x(), mc::WGS84::ellipsoid.a(), LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 0.0, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanSetPositionFromCartAt45N45E100H)
{
    mc::ECEF ecef(mc::WGS84::ellipsoid);
    mc::Vector3 pos_cart_in;
    mc::Vector3 pos_cart;

    // 45N 45E H=100m
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_cart_in.x() = 3194469.1450605746;
    pos_cart_in.y() = 3194469.145060574;
    pos_cart_in.z() = 4487419.119544039;
    ecef.SetPositionFromCart(pos_cart_in);

    pos_cart = ecef.pos_cart();
    EXPECT_NEAR(pos_cart.x(), 3194469.1450605746 , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 3194469.145060574  , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 4487419.119544039  , LINEAR_POSITION_TOLERANCE);
}
