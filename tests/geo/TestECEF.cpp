#include <gtest/gtest.h>

#include <mcutils/geo/ECEF.h>

#include <mcutils/geo/DataMars.h>
#include <mcutils/geo/DataWGS84.h>

////////////////////////////////////////////////////////////////////////////////

class TestECEF : public ::testing::Test
{
protected:
    TestECEF() {}
    virtual ~TestECEF() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanConstruct)
{
    mc::ECEF *ecef = nullptr;
    EXPECT_NO_THROW( ecef = new mc::ECEF() );
    delete ecef;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanDestruct)
{
    mc::ECEF *ecef = new mc::ECEF();
    EXPECT_NO_THROW( delete ecef );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanInstantiate)
{
    mc::ECEF ecef;

    EXPECT_DOUBLE_EQ( ecef.getA   (), 0.0 );
    EXPECT_DOUBLE_EQ( ecef.getF   (), 0.0 );
    EXPECT_DOUBLE_EQ( ecef.getB   (), 0.0 );
    EXPECT_DOUBLE_EQ( ecef.getR1  (), 0.0 );
    EXPECT_DOUBLE_EQ( ecef.getA2  (), 0.0 );
    EXPECT_DOUBLE_EQ( ecef.getB2  (), 0.0 );

    double e2  = ecef.getE2  ();
    double e   = ecef.getE   ();
    double ep2 = ecef.getEp2 ();
    double ep  = ecef.getEp  ();

    EXPECT_FALSE( e2  == e2  ); // NaN
    EXPECT_FALSE( e   == e   ); // NaN
    EXPECT_FALSE( ep2 == ep2 ); // NaN
    EXPECT_FALSE( ep  == ep  ); // NaN
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanInstantiateAndSetData)
{
    mc::ECEF ecef( mc::DataMars::a, mc::DataMars::f );

    EXPECT_NEAR( ecef.getA   (), mc::DataMars::a   , 1.0e-9 );
    EXPECT_NEAR( ecef.getF   (), mc::DataMars::f   , 1.0e-9 );
    EXPECT_NEAR( ecef.getB   (), mc::DataMars::b   , 1.0e-3 );
    EXPECT_NEAR( ecef.getR1  (), mc::DataMars::r1  , 1.0e-3 );
    EXPECT_NEAR( ecef.getA2  (), mc::DataMars::a2  , 1.0e3  ); // sic!
    EXPECT_NEAR( ecef.getB2  (), mc::DataMars::b2  , 1.0e3  ); // sic!
    EXPECT_NEAR( ecef.getE2  (), mc::DataMars::e2  , 1.0e-3 );
    EXPECT_NEAR( ecef.getE   (), mc::DataMars::e   , 1.0e-3 );
    EXPECT_NEAR( ecef.getEp2 (), mc::DataMars::ep2 , 1.0e-3 );
    EXPECT_NEAR( ecef.getEp  (), mc::DataMars::ep  , 1.0e-3 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanConvertFromEcefToGeo)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;
    mc::Vector3 pos_ecef;

    // 0N 0E
    pos_ecef.x() = mc::DataWGS84::a;
    pos_ecef.y() = 0.0;
    pos_ecef.z() = 0.0;

    pos_geo = ecef.ecef2geo( pos_ecef );

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-5 );
    EXPECT_NEAR( pos_geo.lon, 0.0, 1.0e-5 );
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 90E
    pos_ecef.x() = 0.0;
    pos_ecef.y() = mc::DataWGS84::a;
    pos_ecef.z() = 0.0;

    pos_geo = ecef.ecef2geo( pos_ecef );

    EXPECT_NEAR( pos_geo.lat, 0.0    , 1.0e-5 );
    EXPECT_NEAR( pos_geo.lon, M_PI_2 , 1.0e-5 );
    EXPECT_NEAR( pos_geo.alt, 0.0    , 1.0e-4 );

    // 0N -90E
    pos_ecef.x() = 0.0;
    pos_ecef.y() = -mc::DataWGS84::a;
    pos_ecef.z() = 0.0;

    pos_geo = ecef.ecef2geo( pos_ecef );

    EXPECT_NEAR( pos_geo.lat,  0.0    , 1.0e-5 );
    EXPECT_NEAR( pos_geo.lon, -M_PI_2 , 1.0e-5 );
    EXPECT_NEAR( pos_geo.alt,  0.0    , 1.0e-4 );

    // 0N 180E
    pos_ecef.x() = -mc::DataWGS84::a;
    pos_ecef.y() = 0.0;
    pos_ecef.z() = 0.0;

    pos_geo = ecef.ecef2geo( pos_ecef );

    EXPECT_NEAR( pos_geo.lat, 0.0  , 1.0e-5 );
    EXPECT_NEAR( pos_geo.lon, M_PI , 1.0e-5 );
    EXPECT_NEAR( pos_geo.alt, 0.0  , 1.0e-4 );

    // 0N 90W
    pos_ecef.x() = 0.0;
    pos_ecef.y() = -mc::DataWGS84::a;
    pos_ecef.z() = 0.0;

    pos_geo = ecef.ecef2geo( pos_ecef );

    EXPECT_NEAR( pos_geo.lat,  0.0    , 1.0e-5 );
    EXPECT_NEAR( pos_geo.lon, -M_PI_2 , 1.0e-5 );
    EXPECT_NEAR( pos_geo.alt,  0.0    , 1.0e-4 );

    // 90N 0E
    pos_ecef.x() = 0.0;
    pos_ecef.y() = 0.0;
    pos_ecef.z() = mc::DataWGS84::b;

    pos_geo = ecef.ecef2geo( pos_ecef );

    EXPECT_NEAR( pos_geo.lat, M_PI_2 , 1.0e-5 );
    EXPECT_NEAR( pos_geo.lon, 0.0    , 1.0e-5 );
    EXPECT_NEAR( pos_geo.alt, 0.0    , 1.0e-4 );

    // 90S 0E
    pos_ecef.x() = 0.0;
    pos_ecef.y() = 0.0;
    pos_ecef.z() = -mc::DataWGS84::b;

    pos_geo = ecef.ecef2geo( pos_ecef );

    EXPECT_NEAR( pos_geo.lat, -M_PI_2 , 1.0e-5 );
    EXPECT_NEAR( pos_geo.lon,  0.0    , 1.0e-5 );
    EXPECT_NEAR( pos_geo.alt,  0.0    , 1.0e-4 );

    // 0N 30E
    pos_ecef.x() = cos( M_PI * 30.0 / 180.0 ) * mc::DataWGS84::a;
    pos_ecef.y() = sin( M_PI * 30.0 / 180.0 ) * mc::DataWGS84::a;
    pos_ecef.z() = 0.0;

    pos_geo = ecef.ecef2geo( pos_ecef );

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-5 );
    EXPECT_NEAR( pos_geo.lon, M_PI * 30.0 / 180.0, 1.0e-5 );
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 45E
    pos_ecef.x() = cos( M_PI_4 ) * mc::DataWGS84::a;
    pos_ecef.y() = sin( M_PI_4 ) * mc::DataWGS84::a;
    pos_ecef.z() = 0.0;

    pos_geo = ecef.ecef2geo( pos_ecef );

    EXPECT_NEAR( pos_geo.lat,    0.0 , 1.0e-5 );
    EXPECT_NEAR( pos_geo.lon, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo.alt,    0.0 , 1.0e-4 );

    // 0N 60E
    pos_ecef.x() = cos( M_PI * 60.0 / 180.0 ) * mc::DataWGS84::a;
    pos_ecef.y() = sin( M_PI * 60.0 / 180.0 ) * mc::DataWGS84::a;
    pos_ecef.z() = 0.0;

    pos_geo = ecef.ecef2geo( pos_ecef );

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-5 );
    EXPECT_NEAR( pos_geo.lon, M_PI * 60.0 / 180.0, 1.0e-5 );
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 45N 45E
    pos_ecef.x() = 3194419.145061;
    pos_ecef.y() = 3194419.145061;
    pos_ecef.z() = 4487348.408802;

    pos_geo = ecef.ecef2geo( pos_ecef );

    EXPECT_NEAR( pos_geo.lat, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo.lon, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo.alt, 0.0    , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanConvertFromGeoToEcef)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;
    mc::Vector3 pos_ecef;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;

    pos_ecef = ecef.geo2ecef( pos_geo );

    EXPECT_NEAR( pos_ecef.x(),  mc::DataWGS84::a , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(),  0.0              , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(),  0.0              , 1.0e-4 );

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;

    pos_ecef = ecef.geo2ecef( pos_geo );

    EXPECT_NEAR( pos_ecef.x(),  0.0              , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(),  mc::DataWGS84::a , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(),  0.0              , 1.0e-4 );

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;

    pos_ecef = ecef.geo2ecef( pos_geo );

    EXPECT_NEAR( pos_ecef.x(),  0.0              , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), -mc::DataWGS84::a , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(),  0.0              , 1.0e-4 );

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;

    pos_ecef = ecef.geo2ecef( pos_geo );

    EXPECT_NEAR( pos_ecef.x(), -mc::DataWGS84::a , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(),  0.0              , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(),  0.0              , 1.0e-4 );

    // 90N 0E
    pos_geo.lat = M_PI_2;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;

    pos_ecef = ecef.geo2ecef( pos_geo );

    EXPECT_NEAR( pos_ecef.x(),  0.0              , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(),  0.0              , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(),  mc::DataWGS84::b , 1.0e-4 );

    // 90S 0E
    pos_geo.lat = -M_PI_2;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;

    pos_ecef = ecef.geo2ecef( pos_geo );

    EXPECT_NEAR( pos_ecef.x(),  0.0              , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(),  0.0              , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), -mc::DataWGS84::b , 1.0e-4 );

    // 0N 30E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI * 30.0 / 180.0;
    pos_geo.alt = 0.0;

    pos_ecef = ecef.geo2ecef( pos_geo );

    EXPECT_NEAR( pos_ecef.x(), cos( pos_geo.lon ) * mc::DataWGS84::a, 1.0e-3 );
    EXPECT_NEAR( pos_ecef.y(), sin( pos_geo.lon ) * mc::DataWGS84::a, 1.0e-3 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-3 );

    // 0N 45E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 0.0;

    pos_ecef = ecef.geo2ecef( pos_geo );

    EXPECT_NEAR( pos_ecef.x(), cos( pos_geo.lon ) * mc::DataWGS84::a, 1.0e-3 );
    EXPECT_NEAR( pos_ecef.y(), sin( pos_geo.lon ) * mc::DataWGS84::a, 1.0e-3 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-3 );

    // 0N 60E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI * 60.0 / 180.0;
    pos_geo.alt = 0.0;

    pos_ecef = ecef.geo2ecef( pos_geo );

    EXPECT_NEAR( pos_ecef.x(), cos( pos_geo.lon ) * mc::DataWGS84::a, 1.0e-3 );
    EXPECT_NEAR( pos_ecef.y(), sin( pos_geo.lon ) * mc::DataWGS84::a, 1.0e-3 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-3 );

    // 45N 45E
    pos_geo.lat = M_PI_4;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 0.0;

    pos_ecef = ecef.geo2ecef( pos_geo );

    EXPECT_NEAR( pos_ecef.x(), 3194419.145061 , 1.0e-3 );
    EXPECT_NEAR( pos_ecef.y(), 3194419.145061 , 1.0e-3 );
    EXPECT_NEAR( pos_ecef.z(), 4487348.408802 , 1.0e-3 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanGetAnglesNED)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;

    mc::Angles angles_bas;
    mc::Angles angles_ned;

    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_bas.set( 0.0, 0.0, 0.0 );
    angles_ned = ecef.getAngles_NED( angles_bas );

    EXPECT_TRUE( false );

    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanGetAnglesECEF)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanGetNED2BAS)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanGetECEF2BAS)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanGetPosGeo)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanGetPosECEF)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanGetENU2NED)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanGetNED2ENU)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanGetENU2ECEF)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanGetNED2ECEF)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanGetECEF2ENU)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanGetECEF2NED)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanSetPosGeo)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, DISABLED_CanSetPosECEF)
{
    // TODO
}
