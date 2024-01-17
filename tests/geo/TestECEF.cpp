#include <gtest/gtest.h>

#include <mcutils/geo/ECEF.h>

#include <mcutils/geo/DataMars.h>
#include <mcutils/geo/DataWGS84.h>

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
    EXPECT_NO_THROW(ecef = new mc::ECEF());
    delete ecef;
}

TEST_F(TestECEF, CanDestruct)
{
    mc::ECEF* ecef = new mc::ECEF();
    EXPECT_NO_THROW(delete ecef);
}

TEST_F(TestECEF, CanInstantiate)
{
    mc::ECEF ecef;

    EXPECT_DOUBLE_EQ(ecef.a()  , 0.0);
    EXPECT_DOUBLE_EQ(ecef.f()  , 0.0);
    EXPECT_DOUBLE_EQ(ecef.b()  , 0.0);
    EXPECT_DOUBLE_EQ(ecef.r1() , 0.0);
    EXPECT_DOUBLE_EQ(ecef.a2() , 0.0);
    EXPECT_DOUBLE_EQ(ecef.b2() , 0.0);

    double e2  = ecef.e2();
    double e   = ecef.e();
    double ep2 = ecef.ep2();
    double ep  = ecef.ep();

    EXPECT_FALSE(e2  == e2 ); // NaN
    EXPECT_FALSE(e   == e  ); // NaN
    EXPECT_FALSE(ep2 == ep2); // NaN
    EXPECT_FALSE(ep  == ep ); // NaN
}

TEST_F(TestECEF, CanInstantiateAndCopy)
{
    mc::ECEF ecef0(mc::DataMars::a, mc::DataMars::f);

    mc::ECEF ecef(ecef0);

    EXPECT_NEAR(ecef.a()   , mc::DataMars::a   , 1.0e-9);
    EXPECT_NEAR(ecef.f()   , mc::DataMars::f   , 1.0e-9);
    EXPECT_NEAR(ecef.b()   , mc::DataMars::b   , 1.0e-4);
    EXPECT_NEAR(ecef.r1()  , mc::DataMars::r1  , 1.0e-4);
    EXPECT_NEAR(ecef.a2()  , mc::DataMars::a2  , 1.0e3 ); // sic!
    EXPECT_NEAR(ecef.b2()  , mc::DataMars::b2  , 1.0e3 ); // sic!
    EXPECT_NEAR(ecef.e2()  , mc::DataMars::e2  , 1.0e-4);
    EXPECT_NEAR(ecef.e()   , mc::DataMars::e   , 1.0e-4);
    EXPECT_NEAR(ecef.ep2() , mc::DataMars::ep2 , 1.0e-4);
    EXPECT_NEAR(ecef.ep()  , mc::DataMars::ep  , 1.0e-4);
}

TEST_F(TestECEF, CanInstantiateAndMove)
{
    mc::ECEF ecef( std::move(mc::ECEF(mc::DataMars::a, mc::DataMars::f)) );

    EXPECT_NEAR(ecef.a()   , mc::DataMars::a   , 1.0e-9);
    EXPECT_NEAR(ecef.f()   , mc::DataMars::f   , 1.0e-9);
    EXPECT_NEAR(ecef.b()   , mc::DataMars::b   , 1.0e-4);
    EXPECT_NEAR(ecef.r1()  , mc::DataMars::r1  , 1.0e-4);
    EXPECT_NEAR(ecef.a2()  , mc::DataMars::a2  , 1.0e3 ); // sic!
    EXPECT_NEAR(ecef.b2()  , mc::DataMars::b2  , 1.0e3 ); // sic!
    EXPECT_NEAR(ecef.e2()  , mc::DataMars::e2  , 1.0e-4);
    EXPECT_NEAR(ecef.e()   , mc::DataMars::e   , 1.0e-4);
    EXPECT_NEAR(ecef.ep2() , mc::DataMars::ep2 , 1.0e-4);
    EXPECT_NEAR(ecef.ep()  , mc::DataMars::ep  , 1.0e-4);
}

TEST_F(TestECEF, CanInstantiateAndSetData)
{
    mc::ECEF ecef(mc::DataMars::a, mc::DataMars::f);

    EXPECT_NEAR(ecef.a()   , mc::DataMars::a   , 1.0e-9);
    EXPECT_NEAR(ecef.f()   , mc::DataMars::f   , 1.0e-9);
    EXPECT_NEAR(ecef.b()   , mc::DataMars::b   , 1.0e-4);
    EXPECT_NEAR(ecef.r1()  , mc::DataMars::r1  , 1.0e-4);
    EXPECT_NEAR(ecef.a2()  , mc::DataMars::a2  , 1.0e3 ); // sic!
    EXPECT_NEAR(ecef.b2()  , mc::DataMars::b2  , 1.0e3 ); // sic!
    EXPECT_NEAR(ecef.e2()  , mc::DataMars::e2  , 1.0e-4);
    EXPECT_NEAR(ecef.e()   , mc::DataMars::e   , 1.0e-4);
    EXPECT_NEAR(ecef.ep2() , mc::DataMars::ep2 , 1.0e-4);
    EXPECT_NEAR(ecef.ep()  , mc::DataMars::ep  , 1.0e-4);
}

TEST_F(TestECEF, CanConvertFromCartToGeoAt0N0E0H)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 0N 0E
    pos_cart.x() = mc::DataWGS84::a;
    pos_cart.y() = 0.0;
    pos_cart.z() = 0.0;

    ecef.ConvertCart2Geo(pos_cart, &pos_geo);
    EXPECT_NEAR(pos_geo.lat, 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon, 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt, 0.0, LINEAR_POSITION_TOLERANCE);

    pos_geo = ecef.ConvertCart2Geo(pos_cart);
    EXPECT_NEAR(pos_geo.lat, 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon, 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt, 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanConvertFromCartToGeoAt45N45E100H)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 45N 45E H=100m
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_cart.x() = 3194469.1450605746;
    pos_cart.y() = 3194469.145060574;
    pos_cart.z() = 4487419.119544039;

    ecef.ConvertCart2Geo(pos_cart, &pos_geo);
    EXPECT_NEAR(pos_geo.lat, M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon, M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt, 100.0  , LINEAR_POSITION_TOLERANCE);

    pos_geo = ecef.ConvertCart2Geo(pos_cart);
    EXPECT_NEAR(pos_geo.lat, M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon, M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt, 100.0  , LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanConvertFromGeoToCartAt0N0E0H)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;

    ecef.ConvertGeo2Cart(pos_geo, &pos_cart);
    EXPECT_NEAR(pos_cart.x(), mc::DataWGS84::a, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 0.0, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 0.0, LINEAR_POSITION_TOLERANCE);

    pos_cart = ecef.ConvertGeo2Cart(pos_geo);
    EXPECT_NEAR(pos_cart.x(), mc::DataWGS84::a, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 0.0, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanConvertFromGeoToCartAt45N45E100H)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 45N 45E H=100m
    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_geo.lat = M_PI_4;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 100.0;

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
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);

    constexpr double nautical_mile = 1852.0;
    constexpr double arc_min = (1.0 / 60.0) * M_PI / 180.0;

    // as one nautical mile is equal to one arc minute only on the great circle
    // tolerance for those tests is higher than for typical lat/lon position
    constexpr double tolerance = 1.0e-5;

    mc::Geo pos_geo;
    mc::Geo pos_geo_off;

    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    // HDG = 0
    pos_geo_off = ecef.GetGeoOffset(0.0, nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat + arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon, tolerance);

    pos_geo_off = ecef.GetGeoOffset(0.0, -nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat - arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon, tolerance);

    pos_geo_off = ecef.GetGeoOffset(0.0, 0.0, nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon + arc_min, tolerance);

    pos_geo_off = ecef.GetGeoOffset(0.0, 0.0, -nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon - arc_min, tolerance);
}

TEST_F(TestECEF, CanGetGeoOffsetHeading90)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);

    constexpr double nautical_mile = 1852.0;
    constexpr double arc_min = (1.0 / 60.0) * M_PI / 180.0;

    // as one nautical mile is equal to one arc minute only on the great circle
    // tolerance for those tests is higher than for typical lat/lon position
    constexpr double tolerance = 1.0e-5;

    mc::Geo pos_geo;
    mc::Geo pos_geo_off;

    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    // HDG = 90
    pos_geo_off = ecef.GetGeoOffset(M_PI_2, nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon + arc_min, tolerance);

    pos_geo_off = ecef.GetGeoOffset(M_PI_2, -nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon - arc_min, tolerance);

    pos_geo_off = ecef.GetGeoOffset(M_PI_2, 0.0, nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat - arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon, tolerance);

    pos_geo_off = ecef.GetGeoOffset(M_PI_2, 0.0, -nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat + arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon, tolerance);
}

TEST_F(TestECEF, CanGetGeoOffsetHeadingMinus90)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);

    constexpr double nautical_mile = 1852.0;
    constexpr double arc_min = (1.0 / 60.0) * M_PI / 180.0;

    // as one nautical mile is equal to one arc minute only on the great circle
    // tolerance for those tests is higher than for typical lat/lon position
    constexpr double tolerance = 1.0e-5;

    mc::Geo pos_geo;
    mc::Geo pos_geo_off;

    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    // HDG = -90
    pos_geo_off = ecef.GetGeoOffset(-M_PI_2, nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon - arc_min, tolerance);

    pos_geo_off = ecef.GetGeoOffset(-M_PI_2, -nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon + arc_min, tolerance);

    pos_geo_off = ecef.GetGeoOffset(-M_PI_2, 0.0, nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat + arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon, tolerance);

    pos_geo_off = ecef.GetGeoOffset(-M_PI_2, 0.0, -nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat - arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon, tolerance);
}

TEST_F(TestECEF, CanGetGeoOffsetHeading180)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);

    constexpr double nautical_mile = 1852.0;
    constexpr double arc_min = (1.0 / 60.0) * M_PI / 180.0;

    // as one nautical mile is equal to one arc minute only on the great circle
    // tolerance for those tests is higher than for typical lat/lon position
    constexpr double tolerance = 1.0e-5;

    mc::Geo pos_geo;
    mc::Geo pos_geo_off;

    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    // HDG = 180
    pos_geo_off = ecef.GetGeoOffset(M_PI, nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat - arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon, tolerance);

    pos_geo_off = ecef.GetGeoOffset(M_PI, -nautical_mile, 0.0);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat + arc_min, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon, tolerance);

    pos_geo_off = ecef.GetGeoOffset(M_PI, 0.0, nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon - arc_min, tolerance);

    pos_geo_off = ecef.GetGeoOffset(M_PI, 0.0, -nautical_mile);
    EXPECT_NEAR(pos_geo_off.lat, pos_geo.lat, tolerance);
    EXPECT_NEAR(pos_geo_off.lon, pos_geo.lon + arc_min, tolerance);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesECEF2NEDAt0N0E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.Set(0.0, 0.0, 0.0);
    angles_ned = ecef.ConvertAttitudeECEF2NED(angles_ecef);

    EXPECT_NEAR(angles_ned.phi(), 0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht(), M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi(), 0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesECEF2NEDAt0N90E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.Set(0.0, 0.0, 0.0);
    angles_ned = ecef.ConvertAttitudeECEF2NED(angles_ecef);

    EXPECT_NEAR(angles_ned.phi(), -M_PI_2    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht(), 0.0        , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi(), 1.5 * M_PI , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesECEF2NEDAt0N90W)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.Set(0.0, 0.0, 0.0);
    angles_ned = ecef.ConvertAttitudeECEF2NED(angles_ecef);

    EXPECT_NEAR(angles_ned.phi(), M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht(), 0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi(), M_PI_2 , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesECEF2NEDAt0N180E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.Set(0.0, 0.0, 0.0);
    angles_ned = ecef.ConvertAttitudeECEF2NED(angles_ecef);

    EXPECT_NEAR(angles_ned.phi(),  M_PI   , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi(),  0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesNED2ECEFAt0N0E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ned.Set(0.0, 0.0, 0.0);
    angles_ecef = ecef.ConvertAttitudeNED2ECEF(angles_ned);

    EXPECT_NEAR(angles_ecef.phi(),  0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi(),  0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesNED2ECEFAt0N90E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ned.Set(0.0, 0.0, 0.0);
    angles_ecef = ecef.ConvertAttitudeNED2ECEF(angles_ned);

    EXPECT_NEAR(angles_ecef.psi(),  0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.phi(),  M_PI_2 , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesNED2ECEFAt0N90W)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ned.Set(0.0, 0.0, 0.0);
    angles_ecef = ecef.ConvertAttitudeNED2ECEF(angles_ned);

    EXPECT_NEAR(angles_ecef.psi(),  0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.phi(), -M_PI_2 , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeAnglesNED2ECEFAt0N180E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ned.Set(0.0, 0.0, 0.0);
    angles_ecef = ecef.ConvertAttitudeNED2ECEF(angles_ned);

    EXPECT_NEAR(angles_ecef.psi(),  0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.phi(),  M_PI   , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsECEF2NEDAt0N0E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;
    mc::Quaternion ned2bas;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.phi() =  0.0;
    angles_ecef.tht() = -M_PI_2;
    angles_ecef.psi() =  0.0;

    ned2bas = ecef.ConvertAttitudeECEF2NED(mc::Quaternion(angles_ecef));
    angles_ned = ned2bas.GetAngles();
    angles_ned.Normalize();

    EXPECT_NEAR(angles_ned.phi(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi(), 0.0, ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsECEF2NEDAt0N90E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;
    mc::Quaternion ned2bas;

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.phi() =  0.0;
    angles_ecef.tht() = -M_PI_2;
    angles_ecef.psi() =  M_PI_2;

    ned2bas = ecef.ConvertAttitudeECEF2NED(mc::Quaternion(angles_ecef));
    angles_ned = ned2bas.GetAngles();
    angles_ned.Normalize();

    EXPECT_NEAR(angles_ned.phi(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi(), 0.0, ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsECEF2NEDAt0N90W)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;
    mc::Quaternion ned2bas;

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.phi() =  0.0;
    angles_ecef.tht() = -M_PI_2;
    angles_ecef.psi() = -M_PI_2;

    ned2bas = ecef.ConvertAttitudeECEF2NED(mc::Quaternion(angles_ecef));
    angles_ned = ned2bas.GetAngles();
    angles_ned.Normalize();

    EXPECT_NEAR(angles_ned.phi(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi(), 0.0, ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsECEF2NEDAt0N180E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Angles angles_ned;
    mc::Quaternion ned2bas;

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    angles_ecef.phi() =  0.0;
    angles_ecef.tht() = -M_PI_2;
    angles_ecef.psi() =  M_PI;

    ned2bas = ecef.ConvertAttitudeECEF2NED(mc::Quaternion(angles_ecef));
    angles_ned = ned2bas.GetAngles();
    angles_ned.Normalize();

    EXPECT_NEAR(angles_ned.phi(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.tht(), 0.0, ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ned.psi(), 0.0, ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsNED2ECEFAt0N0E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Quaternion ecef2bas;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo( pos_geo );

    ecef2bas = ecef.ConvertAttitudeNED2ECEF(mc::Quaternion());
    angles_ecef = ecef2bas.GetAngles();
    angles_ecef.Normalize();

    EXPECT_NEAR(angles_ecef.phi(),  0.0    , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi(),  0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsNED2ECEFAt0N90E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Quaternion ecef2bas;

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo( pos_geo );

    ecef2bas = ecef.ConvertAttitudeNED2ECEF(mc::Quaternion());
    angles_ecef = ecef2bas.GetAngles();
    angles_ecef.Normalize();

    EXPECT_NEAR(angles_ecef.phi(),  M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi(),  0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsNED2ECEFAt0N90W)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Quaternion ecef2bas;

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo( pos_geo );

    ecef2bas = ecef.ConvertAttitudeNED2ECEF(mc::Quaternion());
    angles_ecef = ecef2bas.GetAngles();
    angles_ecef.Normalize();

    EXPECT_NEAR(angles_ecef.phi(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi(),  0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanConvertAttitudeQuaternionsNED2ECEFAt0N180E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Quaternion ecef2bas;

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo( pos_geo );

    ecef2bas = ecef.ConvertAttitudeNED2ECEF(mc::Quaternion());
    angles_ecef = ecef2bas.GetAngles();
    angles_ecef.Normalize();

    EXPECT_NEAR(angles_ecef.phi(),  M_PI   , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.tht(), -M_PI_2 , ATTITUDE_TOLERANCE);
    EXPECT_NEAR(angles_ecef.psi(),  0.0    , ATTITUDE_TOLERANCE);
}

TEST_F(TestECEF, CanUpdateAndGetPosGeoAt0N0E0H)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 0N 0E
    pos_cart.x() = mc::DataWGS84::a;
    pos_cart.y() = 0.0;
    pos_cart.z() = 0.0;
    ecef.SetPositionFromCart(pos_cart);

    pos_geo = ecef.pos_geo();

    EXPECT_NEAR(pos_geo.lat, 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon, 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt, 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanUpdateAndGetPosGeoAt45N45E100H)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
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

    EXPECT_NEAR(pos_geo.lat, M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon, M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt, 100.0  , LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanUpdateAndGetPosCartAt0N0E0H)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;

    ecef.SetPositionFromGeo(pos_geo);
    pos_cart = ecef.pos_cart();
    EXPECT_NEAR(pos_cart.x(), mc::DataWGS84::a, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 0.0, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanUpdateAndGetPosCartAt45N45E100H)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Vector3 pos_cart;

    // 45N 45E H=100m
    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_geo.lat = M_PI_4;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 100.0;

    ecef.SetPositionFromGeo(pos_geo);
    pos_cart = ecef.pos_cart();
    EXPECT_NEAR(pos_cart.x(), 3194469.1450605746 , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 3194469.145060574  , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 4487419.119544039  , LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanGetENU2NED)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Matrix3x3 enu2ned = ecef.enu2ned();

    const mc::Vector3 v_enu(1.0, 2.0, 3.0);
    mc::Vector3 v_ned = enu2ned * v_enu;

    EXPECT_DOUBLE_EQ(v_ned.x(),  2.0);
    EXPECT_DOUBLE_EQ(v_ned.y(),  1.0);
    EXPECT_DOUBLE_EQ(v_ned.z(), -3.0);
}

TEST_F(TestECEF, CanGetNED2ENU)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Matrix3x3 ned2enu = ecef.ned2enu();

    const mc::Vector3 v_ned(1.0, 2.0, 3.0);
    mc::Vector3 v_enu = ned2enu * v_ned;

    EXPECT_DOUBLE_EQ(v_enu.x(),  2.0);
    EXPECT_DOUBLE_EQ(v_enu.y(),  1.0);
    EXPECT_DOUBLE_EQ(v_enu.z(), -3.0);
}

TEST_F(TestECEF, CanGetENU2ECEFAt0N0E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 enu2ecef;

    const mc::Vector3 v_enu(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    enu2ecef = ecef.enu2ecef();
    v_ecef = enu2ecef * v_enu;

    EXPECT_DOUBLE_EQ(v_ecef.x(),  3.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(),  1.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  2.0);
}

TEST_F(TestECEF, CanGetENU2ECEFAt0N90E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 enu2ecef;

    const mc::Vector3 v_enu(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    enu2ecef = ecef.enu2ecef();
    v_ecef = enu2ecef * v_enu;

    EXPECT_DOUBLE_EQ(v_ecef.x(), -1.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(),  3.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  2.0);
}

TEST_F(TestECEF, CanGetENU2ECEFAt0N90W)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 enu2ecef;

    const mc::Vector3 v_enu(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    enu2ecef = ecef.enu2ecef();
    v_ecef = enu2ecef * v_enu;

    EXPECT_DOUBLE_EQ(v_ecef.x(),  1.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(), -3.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  2.0);
}

TEST_F(TestECEF, CanGetENU2ECEFAt0N180E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 enu2ecef;

    const mc::Vector3 v_enu(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    enu2ecef = ecef.enu2ecef();
    v_ecef = enu2ecef * v_enu;

    EXPECT_DOUBLE_EQ(v_ecef.x(), -3.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(), -1.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  2.0);
}

TEST_F(TestECEF, CanGetNED2ECEFAt0N0E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 ned2ecef;

    const mc::Vector3 v_ned(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    ned2ecef = ecef.ned2ecef();
    v_ecef = ned2ecef * v_ned;

    EXPECT_DOUBLE_EQ(v_ecef.x(), -3.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(),  2.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  1.0);
}

TEST_F(TestECEF, CanGetNED2ECEFAt0N90E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 ned2ecef;

    const mc::Vector3 v_ned(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    ned2ecef = ecef.ned2ecef();
    v_ecef = ned2ecef * v_ned;

    EXPECT_DOUBLE_EQ(v_ecef.x(), -2.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(), -3.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  1.0);
}

TEST_F(TestECEF, CanGetNED2ECEFAt0N90W)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 ned2ecef;

    const mc::Vector3 v_ned(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    ned2ecef = ecef.ned2ecef();
    v_ecef = ned2ecef * v_ned;

    EXPECT_DOUBLE_EQ(v_ecef.x(),  2.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(),  3.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  1.0);
}

TEST_F(TestECEF, CanGetNED2ECEFAt0N180E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 ned2ecef;

    const mc::Vector3 v_ned(1.0, 2.0, 3.0);
    mc::Vector3 v_ecef;

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    ned2ecef = ecef.ned2ecef();
    v_ecef = ned2ecef * v_ned;

    EXPECT_DOUBLE_EQ(v_ecef.x(),  3.0);
    EXPECT_DOUBLE_EQ(v_ecef.y(), -2.0);
    EXPECT_DOUBLE_EQ(v_ecef.z(),  1.0);
}

TEST_F(TestECEF, CanGetECEF2ENUAt0N0E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2enu;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_enu;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2enu = ecef.ecef2enu();
    v_enu = ecef2enu * v_ecef;

    EXPECT_DOUBLE_EQ(v_enu.x(),  2.0);
    EXPECT_DOUBLE_EQ(v_enu.y(),  3.0);
    EXPECT_DOUBLE_EQ(v_enu.z(),  1.0);
}

TEST_F(TestECEF, CanGetECEF2ENUAt0N90E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2enu;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_enu;

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2enu = ecef.ecef2enu();
    v_enu = ecef2enu * v_ecef;

    EXPECT_DOUBLE_EQ(v_enu.x(), -1.0);
    EXPECT_DOUBLE_EQ(v_enu.y(),  3.0);
    EXPECT_DOUBLE_EQ(v_enu.z(),  2.0);
}

TEST_F(TestECEF, CanGetECEF2ENUAt0N90W)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2enu;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_enu;

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2enu = ecef.ecef2enu();
    v_enu = ecef2enu * v_ecef;

    EXPECT_DOUBLE_EQ(v_enu.x(),  1.0);
    EXPECT_DOUBLE_EQ(v_enu.y(),  3.0);
    EXPECT_DOUBLE_EQ(v_enu.z(), -2.0);
}

TEST_F(TestECEF, CanGetECEF2ENUAt0N180E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2enu;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_enu;

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2enu = ecef.ecef2enu();
    v_enu = ecef2enu * v_ecef;

    EXPECT_DOUBLE_EQ(v_enu.x(), -2.0);
    EXPECT_DOUBLE_EQ(v_enu.y(),  3.0);
    EXPECT_DOUBLE_EQ(v_enu.z(), -1.0);
}

TEST_F(TestECEF, CanGetECEF2NEDAt0N0E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2ned;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_ned;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2ned = ecef.ecef2ned();
    v_ned = ecef2ned * v_ecef;

    EXPECT_DOUBLE_EQ(v_ned.x(),  3.0);
    EXPECT_DOUBLE_EQ(v_ned.y(),  2.0);
    EXPECT_DOUBLE_EQ(v_ned.z(), -1.0);
}

TEST_F(TestECEF, CanGetECEF2NEDAt0N90E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2ned;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_ned;

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2ned = ecef.ecef2ned();
    v_ned = ecef2ned * v_ecef;

    EXPECT_DOUBLE_EQ(v_ned.x(),  3.0);
    EXPECT_DOUBLE_EQ(v_ned.y(), -1.0);
    EXPECT_DOUBLE_EQ(v_ned.z(), -2.0);
}

TEST_F(TestECEF, CanGetECEF2NEDAt0N90W)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2ned;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_ned;

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2ned = ecef.ecef2ned();
    v_ned = ecef2ned * v_ecef;

    EXPECT_DOUBLE_EQ(v_ned.x(),  3.0);
    EXPECT_DOUBLE_EQ(v_ned.y(),  1.0);
    EXPECT_DOUBLE_EQ(v_ned.z(),  2.0);
}

TEST_F(TestECEF, CanGetECEF2NEDAt0N180E)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo;
    mc::Matrix3x3 ecef2ned;

    const mc::Vector3 v_ecef(1.0, 2.0, 3.0);
    mc::Vector3 v_ned;

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo);

    ecef2ned = ecef.ecef2ned();
    v_ned = ecef2ned * v_ecef;

    EXPECT_DOUBLE_EQ(v_ned.x(),  3.0);
    EXPECT_DOUBLE_EQ(v_ned.y(), -2.0);
    EXPECT_DOUBLE_EQ(v_ned.z(),  1.0);
}

TEST_F(TestECEF, CanSetPositionFromGeoAt0N0E0H)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo_in;
    mc::Geo pos_geo;

    // 0N 0E
    pos_geo_in.lat = 0.0;
    pos_geo_in.lon = 0.0;
    pos_geo_in.alt = 0.0;
    ecef.SetPositionFromGeo(pos_geo_in);

    pos_geo = ecef.pos_geo();

    EXPECT_NEAR(pos_geo.lat, 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon, 0.0, LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt, 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanSetPositionFromGeoAt45N45E100H)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Geo pos_geo_in;
    mc::Geo pos_geo;

    // 45N 45E H=100m
    pos_geo_in.lat =  M_PI_4;
    pos_geo_in.lon =  M_PI_4;
    pos_geo_in.alt =  100.0;
    ecef.SetPositionFromGeo(pos_geo_in);

    pos_geo = ecef.pos_geo();

    EXPECT_NEAR(pos_geo.lat, M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.lon, M_PI_4 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(pos_geo.alt, 100.0  , LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanSetPositionFromCartAt0N0E0H)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
    mc::Vector3 pos_cart_in;
    mc::Vector3 pos_cart;

    // 0N 0E
    pos_cart_in.x() = mc::DataWGS84::a;
    pos_cart_in.y() = 0.0;
    pos_cart_in.z() = 0.0;
    ecef.SetPositionFromCart(pos_cart_in);

    pos_cart = ecef.pos_cart();
    EXPECT_NEAR(pos_cart.x(), mc::DataWGS84::a, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.y(), 0.0, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(pos_cart.z(), 0.0, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestECEF, CanSetPositionFromCartAt45N45E100H)
{
    mc::ECEF ecef(mc::DataWGS84::a, mc::DataWGS84::f);
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

TEST_F(TestECEF, CanAssign)
{
    mc::ECEF ecef;

    mc::ECEF ecef0(mc::DataMars::a, mc::DataMars::f);

    ecef = ecef0;

    EXPECT_NEAR(ecef.a()   , mc::DataMars::a   , 1.0e-9);
    EXPECT_NEAR(ecef.f()   , mc::DataMars::f   , 1.0e-9);
    EXPECT_NEAR(ecef.b()   , mc::DataMars::b   , 1.0e-4);
    EXPECT_NEAR(ecef.r1()  , mc::DataMars::r1  , 1.0e-4);
    EXPECT_NEAR(ecef.a2()  , mc::DataMars::a2  , 1.0e3 ); // sic!
    EXPECT_NEAR(ecef.b2()  , mc::DataMars::b2  , 1.0e3 ); // sic!
    EXPECT_NEAR(ecef.e2()  , mc::DataMars::e2  , 1.0e-4);
    EXPECT_NEAR(ecef.e()   , mc::DataMars::e   , 1.0e-4);
    EXPECT_NEAR(ecef.ep2() , mc::DataMars::ep2 , 1.0e-4);
    EXPECT_NEAR(ecef.ep()  , mc::DataMars::ep  , 1.0e-4);
}

TEST_F(TestECEF, CanAssignMove)
{
    mc::ECEF ecef;

    ecef = std::move( mc::ECEF( mc::DataMars::a, mc::DataMars::f ) );

    EXPECT_NEAR(ecef.a()   , mc::DataMars::a   , 1.0e-9);
    EXPECT_NEAR(ecef.f()   , mc::DataMars::f   , 1.0e-9);
    EXPECT_NEAR(ecef.b()   , mc::DataMars::b   , 1.0e-4);
    EXPECT_NEAR(ecef.r1()  , mc::DataMars::r1  , 1.0e-4);
    EXPECT_NEAR(ecef.a2()  , mc::DataMars::a2  , 1.0e3 ); // sic!
    EXPECT_NEAR(ecef.b2()  , mc::DataMars::b2  , 1.0e3 ); // sic!
    EXPECT_NEAR(ecef.e2()  , mc::DataMars::e2  , 1.0e-4);
    EXPECT_NEAR(ecef.e()   , mc::DataMars::e   , 1.0e-4);
    EXPECT_NEAR(ecef.ep2() , mc::DataMars::ep2 , 1.0e-4);
    EXPECT_NEAR(ecef.ep()  , mc::DataMars::ep  , 1.0e-4);
}
