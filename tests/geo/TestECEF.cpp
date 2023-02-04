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

TEST_F(TestECEF, CanInstantiateAndCopy)
{
    mc::ECEF ecef0( mc::DataMars::a, mc::DataMars::f );

    mc::ECEF ecef( ecef0 );

    EXPECT_NEAR( ecef.getA   (), mc::DataMars::a   , 1.0e-9 );
    EXPECT_NEAR( ecef.getF   (), mc::DataMars::f   , 1.0e-9 );
    EXPECT_NEAR( ecef.getB   (), mc::DataMars::b   , 1.0e-4 );
    EXPECT_NEAR( ecef.getR1  (), mc::DataMars::r1  , 1.0e-4 );
    EXPECT_NEAR( ecef.getA2  (), mc::DataMars::a2  , 1.0e3  ); // sic!
    EXPECT_NEAR( ecef.getB2  (), mc::DataMars::b2  , 1.0e3  ); // sic!
    EXPECT_NEAR( ecef.getE2  (), mc::DataMars::e2  , 1.0e-4 );
    EXPECT_NEAR( ecef.getE   (), mc::DataMars::e   , 1.0e-4 );
    EXPECT_NEAR( ecef.getEp2 (), mc::DataMars::ep2 , 1.0e-4 );
    EXPECT_NEAR( ecef.getEp  (), mc::DataMars::ep  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanInstantiateAndMove)
{
    mc::ECEF ecef( std::move( mc::ECEF( mc::DataMars::a, mc::DataMars::f ) ) );

    EXPECT_NEAR( ecef.getA   (), mc::DataMars::a   , 1.0e-9 );
    EXPECT_NEAR( ecef.getF   (), mc::DataMars::f   , 1.0e-9 );
    EXPECT_NEAR( ecef.getB   (), mc::DataMars::b   , 1.0e-4 );
    EXPECT_NEAR( ecef.getR1  (), mc::DataMars::r1  , 1.0e-4 );
    EXPECT_NEAR( ecef.getA2  (), mc::DataMars::a2  , 1.0e3  ); // sic!
    EXPECT_NEAR( ecef.getB2  (), mc::DataMars::b2  , 1.0e3  ); // sic!
    EXPECT_NEAR( ecef.getE2  (), mc::DataMars::e2  , 1.0e-4 );
    EXPECT_NEAR( ecef.getE   (), mc::DataMars::e   , 1.0e-4 );
    EXPECT_NEAR( ecef.getEp2 (), mc::DataMars::ep2 , 1.0e-4 );
    EXPECT_NEAR( ecef.getEp  (), mc::DataMars::ep  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanInstantiateAndSetData)
{
    mc::ECEF ecef( mc::DataMars::a, mc::DataMars::f );

    EXPECT_NEAR( ecef.getA   (), mc::DataMars::a   , 1.0e-9 );
    EXPECT_NEAR( ecef.getF   (), mc::DataMars::f   , 1.0e-9 );
    EXPECT_NEAR( ecef.getB   (), mc::DataMars::b   , 1.0e-4 );
    EXPECT_NEAR( ecef.getR1  (), mc::DataMars::r1  , 1.0e-4 );
    EXPECT_NEAR( ecef.getA2  (), mc::DataMars::a2  , 1.0e3  ); // sic!
    EXPECT_NEAR( ecef.getB2  (), mc::DataMars::b2  , 1.0e3  ); // sic!
    EXPECT_NEAR( ecef.getE2  (), mc::DataMars::e2  , 1.0e-4 );
    EXPECT_NEAR( ecef.getE   (), mc::DataMars::e   , 1.0e-4 );
    EXPECT_NEAR( ecef.getEp2 (), mc::DataMars::ep2 , 1.0e-4 );
    EXPECT_NEAR( ecef.getEp  (), mc::DataMars::ep  , 1.0e-4 );
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

    ecef.ecef2geo( pos_ecef, &pos_geo );
    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    pos_geo = ecef.ecef2geo( pos_ecef );
    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 0E H=100m
    pos_ecef.x() = mc::DataWGS84::a + 100.0;
    pos_ecef.y() = 0.0;
    pos_ecef.z() = 0.0;

    ecef.ecef2geo( pos_ecef, &pos_geo );
    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 100.0, 1.0e-4 );

    pos_geo = ecef.ecef2geo( pos_ecef );
    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 100.0, 1.0e-4 );

    // 0N 90E
    pos_ecef.x() = 0.0;
    pos_ecef.y() = mc::DataWGS84::a;
    pos_ecef.z() = 0.0;

    ecef.ecef2geo( pos_ecef, &pos_geo );
    EXPECT_NEAR( pos_geo.lat, 0.0    , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI_2 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0    , 1.0e-4 );

    pos_geo = ecef.ecef2geo( pos_ecef );
    EXPECT_NEAR( pos_geo.lat, 0.0    , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI_2 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0    , 1.0e-4 );

    // 0N 180E
    pos_ecef.x() = -mc::DataWGS84::a;
    pos_ecef.y() = 0.0;
    pos_ecef.z() = 0.0;

    ecef.ecef2geo( pos_ecef, &pos_geo );
    EXPECT_NEAR( pos_geo.lat, 0.0  , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0  , 1.0e-4 );

    pos_geo = ecef.ecef2geo( pos_ecef );
    EXPECT_NEAR( pos_geo.lat, 0.0  , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0  , 1.0e-4 );

    // 0N 90W
    pos_ecef.x() = 0.0;
    pos_ecef.y() = -mc::DataWGS84::a;
    pos_ecef.z() = 0.0;

    ecef.ecef2geo( pos_ecef, &pos_geo );
    EXPECT_NEAR( pos_geo.lat,  0.0    , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, -M_PI_2 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt,  0.0    , 1.0e-4 );

    pos_geo = ecef.ecef2geo( pos_ecef );
    EXPECT_NEAR( pos_geo.lat,  0.0    , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, -M_PI_2 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt,  0.0    , 1.0e-4 );

    // 90N 0E
    pos_ecef.x() = 0.0;
    pos_ecef.y() = 0.0;
    pos_ecef.z() = mc::DataWGS84::b;

    ecef.ecef2geo( pos_ecef, &pos_geo );
    EXPECT_NEAR( pos_geo.lat, M_PI_2 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 0.0    , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0    , 1.0e-4 );

    pos_geo = ecef.ecef2geo( pos_ecef );
    EXPECT_NEAR( pos_geo.lat, M_PI_2 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 0.0    , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0    , 1.0e-4 );

    // 90S 0E
    pos_ecef.x() = 0.0;
    pos_ecef.y() = 0.0;
    pos_ecef.z() = -mc::DataWGS84::b;

    ecef.ecef2geo( pos_ecef, &pos_geo );
    EXPECT_NEAR( pos_geo.lat, -M_PI_2 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon,  0.0    , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt,  0.0    , 1.0e-4 );

    pos_geo = ecef.ecef2geo( pos_ecef );
    EXPECT_NEAR( pos_geo.lat, -M_PI_2 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon,  0.0    , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt,  0.0    , 1.0e-4 );

    // 0N 30E
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_ecef.x() = 5523628.670817468;
    pos_ecef.y() = 3189068.4999999995;
    pos_ecef.z() = 0.0;

    ecef.ecef2geo( pos_ecef, &pos_geo );
    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI * 30.0 / 180.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    pos_geo = ecef.ecef2geo( pos_ecef );
    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI * 30.0 / 180.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 45E
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_ecef.x() = 4510023.924036823;
    pos_ecef.y() = 4510023.924036822;
    pos_ecef.z() = 0.0;

    ecef.ecef2geo( pos_ecef, &pos_geo );
    EXPECT_NEAR( pos_geo.lat,    0.0 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI_4 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt,    0.0 , 1.0e-4 );

    pos_geo = ecef.ecef2geo( pos_ecef );
    EXPECT_NEAR( pos_geo.lat,    0.0 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI_4 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt,    0.0 , 1.0e-4 );

    // 0N 60E
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_ecef.x() = 3189068.500000001;
    pos_ecef.y() = 5523628.670817467;
    pos_ecef.z() = 0.0;

    ecef.ecef2geo( pos_ecef, &pos_geo );
    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI * 60.0 / 180.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    pos_geo = ecef.ecef2geo( pos_ecef );
    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI * 60.0 / 180.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 45N 45E H=100m
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_ecef.x() = 3194469.1450605746;
    pos_ecef.y() = 3194469.145060574;
    pos_ecef.z() = 4487419.119544039;

    ecef.ecef2geo( pos_ecef, &pos_geo );
    EXPECT_NEAR( pos_geo.lat, M_PI_4 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI_4 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 100.0  , 1.0e-4 );

    pos_geo = ecef.ecef2geo( pos_ecef );
    EXPECT_NEAR( pos_geo.lat, M_PI_4 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI_4 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 100.0  , 1.0e-4 );
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

    ecef.geo2ecef( pos_geo, &pos_ecef );
    EXPECT_NEAR( pos_ecef.x(), mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    pos_ecef = ecef.geo2ecef( pos_geo );
    EXPECT_NEAR( pos_ecef.x(), mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 0E H=100m
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 100.0;

    ecef.geo2ecef( pos_geo, &pos_ecef );
    EXPECT_NEAR( pos_ecef.x(), mc::DataWGS84::a + 100.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    pos_ecef = ecef.geo2ecef( pos_geo );
    EXPECT_NEAR( pos_ecef.x(), mc::DataWGS84::a + 100.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;

    ecef.geo2ecef( pos_geo, &pos_ecef );
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    pos_ecef = ecef.geo2ecef( pos_geo );
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;

    ecef.geo2ecef( pos_geo, &pos_ecef );
    EXPECT_NEAR( pos_ecef.x(), -mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    pos_ecef = ecef.geo2ecef( pos_geo );
    EXPECT_NEAR( pos_ecef.x(), -mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;

    ecef.geo2ecef( pos_geo, &pos_ecef );
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), -mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    pos_ecef = ecef.geo2ecef( pos_geo );
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), -mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 90N 0E
    pos_geo.lat = M_PI_2;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;

    ecef.geo2ecef( pos_geo, &pos_ecef );
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), mc::DataWGS84::b, 1.0e-4 );

    pos_ecef = ecef.geo2ecef( pos_geo );
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), mc::DataWGS84::b, 1.0e-4 );

    // 90S 0E
    pos_geo.lat = -M_PI_2;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;

    ecef.geo2ecef( pos_geo, &pos_ecef );
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), -mc::DataWGS84::b, 1.0e-4 );

    pos_ecef = ecef.geo2ecef( pos_geo );
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), -mc::DataWGS84::b, 1.0e-4 );

    // 0N 30E
    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2 / 3.0;
    pos_geo.alt = 0.0;

    ecef.geo2ecef( pos_geo, &pos_ecef );
    EXPECT_NEAR( pos_ecef.x(), 5523628.670817468  , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 3189068.4999999995 , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    pos_ecef = ecef.geo2ecef( pos_geo );
    EXPECT_NEAR( pos_ecef.x(), 5523628.670817468  , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 3189068.4999999995 , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 45E
    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 0.0;

    ecef.geo2ecef( pos_geo, &pos_ecef );
    EXPECT_NEAR( pos_ecef.x(), 4510023.924036823, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 4510023.924036822, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    pos_ecef = ecef.geo2ecef( pos_geo );
    EXPECT_NEAR( pos_ecef.x(), 4510023.924036823, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 4510023.924036822, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 60E
    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_geo.lat = 0.0;
    pos_geo.lon = 2.0 * M_PI_2 / 3.0;
    pos_geo.alt = 0.0;

    ecef.geo2ecef( pos_geo, &pos_ecef );
    EXPECT_NEAR( pos_ecef.x(), 3189068.500000001, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 5523628.670817467, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    pos_ecef = ecef.geo2ecef( pos_geo );
    EXPECT_NEAR( pos_ecef.x(), 3189068.500000001, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 5523628.670817467, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 45N 45E H=100m
    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_geo.lat = M_PI_4;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 100.0;

    ecef.geo2ecef( pos_geo, &pos_ecef );
    EXPECT_NEAR( pos_ecef.x(), 3194469.1450605746 , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 3194469.145060574  , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 4487419.119544039  , 1.0e-4 );

    pos_ecef = ecef.geo2ecef( pos_geo );
    EXPECT_NEAR( pos_ecef.x(), 3194469.1450605746 , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 3194469.145060574  , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 4487419.119544039  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetGeoOffset)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    const double arc_min = ( 1.0 / 60.0 ) * M_PI / 180.0;

    mc::Geo pos_geo;
    mc::Geo pos_geo_off;

    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    // HDG = 0
    pos_geo_off = ecef.getGeoOffset( 0.0, 1852.0, 0.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat + arc_min, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon, 1.0e-5 );

    pos_geo_off = ecef.getGeoOffset( 0.0, -1852.0, 0.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat - arc_min, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon, 1.0e-5 );

    pos_geo_off = ecef.getGeoOffset( 0.0, 0.0, 1852.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon + arc_min, 1.0e-5 );

    pos_geo_off = ecef.getGeoOffset( 0.0, 0.0, -1852.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon - arc_min, 1.0e-5 );

    // HDG = 90
    pos_geo_off = ecef.getGeoOffset( M_PI_2, 1852.0, 0.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon + arc_min, 1.0e-5 );

    pos_geo_off = ecef.getGeoOffset( M_PI_2, -1852.0, 0.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon - arc_min, 1.0e-5 );

    pos_geo_off = ecef.getGeoOffset( M_PI_2, 0.0, 1852.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat - arc_min, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon, 1.0e-5 );

    pos_geo_off = ecef.getGeoOffset( M_PI_2, 0.0, -1852.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat + arc_min, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon, 1.0e-5 );

    // HDG = -90
    pos_geo_off = ecef.getGeoOffset( -M_PI_2, 1852.0, 0.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon - arc_min, 1.0e-5 );

    pos_geo_off = ecef.getGeoOffset( -M_PI_2, -1852.0, 0.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon + arc_min, 1.0e-5 );

    pos_geo_off = ecef.getGeoOffset( -M_PI_2, 0.0, 1852.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat + arc_min, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon, 1.0e-5 );

    pos_geo_off = ecef.getGeoOffset( -M_PI_2, 0.0, -1852.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat - arc_min, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon, 1.0e-5 );

    // HDG = 180
    pos_geo_off = ecef.getGeoOffset( M_PI, 1852.0, 0.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat - arc_min, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon, 1.0e-5 );

    pos_geo_off = ecef.getGeoOffset( M_PI, -1852.0, 0.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat + arc_min, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon, 1.0e-5 );

    pos_geo_off = ecef.getGeoOffset( M_PI, 0.0, 1852.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon - arc_min, 1.0e-5 );

    pos_geo_off = ecef.getGeoOffset( M_PI, 0.0, -1852.0 );
    EXPECT_NEAR( pos_geo_off.lat, pos_geo.lat, 1.0e-5 );
    EXPECT_NEAR( pos_geo_off.lon, pos_geo.lon + arc_min, 1.0e-5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetAnglesNED)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;

    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_ecef.set( 0.0, 0.0, 0.0 );
    angles_ned = ecef.getAngles_NED( angles_ecef );

    EXPECT_NEAR( angles_ned.phi(), 0.0    , 1.0e-6 );
    EXPECT_NEAR( angles_ned.tht(), M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ned.psi(), 0.0    , 1.0e-6 );

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_ecef.set( 0.0, 0.0, 0.0 );
    angles_ned = ecef.getAngles_NED( angles_ecef );

    EXPECT_NEAR( angles_ned.phi(), -M_PI_2    , 1.0e-6 );
    EXPECT_NEAR( angles_ned.tht(), 0.0        , 1.0e-6 );
    EXPECT_NEAR( angles_ned.psi(), 1.5 * M_PI , 1.0e-6 );

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_ecef.set( 0.0, 0.0, 0.0 );
    angles_ned = ecef.getAngles_NED( angles_ecef );

    EXPECT_NEAR( angles_ned.phi(), M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ned.tht(), 0.0    , 1.0e-6 );
    EXPECT_NEAR( angles_ned.psi(), M_PI_2 , 1.0e-6 );

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_ecef.set( 0.0, 0.0, 0.0 );
    angles_ned = ecef.getAngles_NED( angles_ecef );

    EXPECT_NEAR( angles_ned.phi(),  M_PI   , 1.0e-6 );
    EXPECT_NEAR( angles_ned.tht(), -M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ned.psi(),  0.0    , 1.0e-6 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetAnglesECEF)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;

    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_ned.set( 0.0, 0.0, 0.0 );
    angles_ecef = ecef.getAngles_ECEF( angles_ned );

    EXPECT_NEAR( angles_ecef.phi(),  0.0    , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.tht(), -M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.psi(),  0.0    , 1.0e-6 );

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_ned.set( 0.0, 0.0, 0.0 );
    angles_ecef = ecef.getAngles_ECEF( angles_ned );

    EXPECT_NEAR( angles_ecef.psi(),  0.0    , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.tht(), -M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.phi(),  M_PI_2 , 1.0e-6 );

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_ned.set( 0.0, 0.0, 0.0 );
    angles_ecef = ecef.getAngles_ECEF( angles_ned );

    EXPECT_NEAR( angles_ecef.psi(),  0.0    , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.tht(), -M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.phi(), -M_PI_2 , 1.0e-6 );

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_ned.set( 0.0, 0.0, 0.0 );
    angles_ecef = ecef.getAngles_ECEF( angles_ned );

    EXPECT_NEAR( angles_ecef.psi(),  0.0    , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.tht(), -M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.phi(),  M_PI   , 1.0e-6 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetNED2BAS)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;

    mc::Angles angles_ecef;
    mc::Angles angles_ned;

    mc::Quaternion ned2bas;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_ecef.phi() =  0.0;
    angles_ecef.tht() = -M_PI_2;
    angles_ecef.psi() =  0.0;

    ned2bas = ecef.getNED2BAS( mc::Quaternion( angles_ecef ) );
    angles_ned = ned2bas.getAngles();
    angles_ned.normalize();

    EXPECT_NEAR( angles_ned.phi(), 0.0, 1.0e-6 );
    EXPECT_NEAR( angles_ned.tht(), 0.0, 1.0e-6 );
    EXPECT_NEAR( angles_ned.psi(), 0.0, 1.0e-6 );

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_ecef.phi() =  0.0;
    angles_ecef.tht() = -M_PI_2;
    angles_ecef.psi() =  M_PI_2;

    ned2bas = ecef.getNED2BAS( mc::Quaternion( angles_ecef ) );
    angles_ned = ned2bas.getAngles();
    angles_ned.normalize();

    EXPECT_NEAR( angles_ned.phi(), 0.0, 1.0e-6 );
    EXPECT_NEAR( angles_ned.tht(), 0.0, 1.0e-6 );
    EXPECT_NEAR( angles_ned.psi(), 0.0, 1.0e-6 );

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_ecef.phi() =  0.0;
    angles_ecef.tht() = -M_PI_2;
    angles_ecef.psi() = -M_PI_2;

    ned2bas = ecef.getNED2BAS( mc::Quaternion( angles_ecef ) );
    angles_ned = ned2bas.getAngles();
    angles_ned.normalize();

    EXPECT_NEAR( angles_ned.phi(), 0.0, 1.0e-6 );
    EXPECT_NEAR( angles_ned.tht(), 0.0, 1.0e-6 );
    EXPECT_NEAR( angles_ned.psi(), 0.0, 1.0e-6 );

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    angles_ecef.phi() =  0.0;
    angles_ecef.tht() = -M_PI_2;
    angles_ecef.psi() =  M_PI;

    ned2bas = ecef.getNED2BAS( mc::Quaternion( angles_ecef ) );
    angles_ned = ned2bas.getAngles();
    angles_ned.normalize();

    EXPECT_NEAR( angles_ned.phi(), 0.0, 1.0e-6 );
    EXPECT_NEAR( angles_ned.tht(), 0.0, 1.0e-6 );
    EXPECT_NEAR( angles_ned.psi(), 0.0, 1.0e-6 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetECEF2BAS)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;
    mc::Angles angles_ecef;
    mc::Quaternion ecef2bas;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ecef2bas = ecef.getECEF2BAS( mc::Quaternion::zeroRotationQuaternion() );
    angles_ecef = ecef2bas.getAngles();
    angles_ecef.normalize();

    EXPECT_NEAR( angles_ecef.phi(),  0.0    , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.tht(), -M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.psi(),  0.0    , 1.0e-6 );

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ecef2bas = ecef.getECEF2BAS( mc::Quaternion::zeroRotationQuaternion() );
    angles_ecef = ecef2bas.getAngles();
    angles_ecef.normalize();

    EXPECT_NEAR( angles_ecef.phi(),  M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.tht(), -M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.psi(),  0.0 , 1.0e-6 );

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ecef2bas = ecef.getECEF2BAS( mc::Quaternion::zeroRotationQuaternion() );
    angles_ecef = ecef2bas.getAngles();
    angles_ecef.normalize();

    EXPECT_NEAR( angles_ecef.phi(), -M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.tht(), -M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.psi(),  0.0    , 1.0e-6 );

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ecef2bas = ecef.getECEF2BAS( mc::Quaternion::zeroRotationQuaternion() );
    angles_ecef = ecef2bas.getAngles();
    angles_ecef.normalize();

    EXPECT_NEAR( angles_ecef.phi(),  M_PI   , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.tht(), -M_PI_2 , 1.0e-6 );
    EXPECT_NEAR( angles_ecef.psi(),  0.0    , 1.0e-6 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetPosGeo)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;
    mc::Vector3 pos_ecef;

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 0E
    pos_ecef.x() = mc::DataWGS84::a;
    pos_ecef.y() = 0.0;
    pos_ecef.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 0E H=100m
    pos_ecef.x() = mc::DataWGS84::a + 100.0;
    pos_ecef.y() = 0.0;
    pos_ecef.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 100.0, 1.0e-4 );

    // 0N 90E
    pos_ecef.x() = 0.0;
    pos_ecef.y() = mc::DataWGS84::a;
    pos_ecef.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI_2, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 180E
    pos_ecef.x() = -mc::DataWGS84::a;
    pos_ecef.y() = 0.0;
    pos_ecef.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 90W
    pos_ecef.x() = 0.0;
    pos_ecef.y() = -mc::DataWGS84::a;
    pos_ecef.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, -M_PI_2, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 30E
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_ecef.x() = 5523628.670817468;
    pos_ecef.y() = 3189068.4999999995;
    pos_ecef.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 30.0 * M_PI / 180.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 45E
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_ecef.x() = 4510023.924036823;
    pos_ecef.y() = 4510023.924036822;
    pos_ecef.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 45.0 * M_PI / 180.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 60E
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_ecef.x() = 3189068.500000001;
    pos_ecef.y() = 5523628.670817467;
    pos_ecef.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 60.0 * M_PI / 180.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 45N 45E H=100m
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_ecef.x() = 3194469.1450605746;
    pos_ecef.y() = 3194469.145060574;
    pos_ecef.z() = 4487419.119544039;
    ecef.setPos_ECEF( pos_ecef );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, M_PI_4 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI_4 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 100.0  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetPosECEF)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;
    mc::Vector3 pos_ecef;

    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;

    ecef.setPos_Geo( pos_geo );
    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 0E H=100m
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 100.0;

    ecef.setPos_Geo( pos_geo );
    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), mc::DataWGS84::a + 100.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;

    ecef.setPos_Geo( pos_geo );
    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;

    ecef.setPos_Geo( pos_geo );
    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), -mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;

    ecef.setPos_Geo( pos_geo );
    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), -mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 90N 0E
    pos_geo.lat = M_PI_2;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;

    ecef.setPos_Geo( pos_geo );
    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), mc::DataWGS84::b, 1.0e-4 );

    // 90S 0E
    pos_geo.lat = -M_PI_2;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;

    ecef.setPos_Geo( pos_geo );
    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), -mc::DataWGS84::b, 1.0e-4 );

    // 0N 30E
    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2 / 3.0;
    pos_geo.alt = 0.0;

    ecef.setPos_Geo( pos_geo );
    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 5523628.670817468  , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 3189068.4999999995 , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 45E
    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 0.0;

    ecef.setPos_Geo( pos_geo );
    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 4510023.924036823, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 4510023.924036822, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 60E
    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_geo.lat = 0.0;
    pos_geo.lon = 2.0 * M_PI_2 / 3.0;
    pos_geo.alt = 0.0;

    ecef.setPos_Geo( pos_geo );
    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 3189068.500000001, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 5523628.670817467, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 45N 45E H=100m
    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_geo.lat = M_PI_4;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 100.0;

    ecef.setPos_Geo( pos_geo );
    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 3194469.1450605746 , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 3194469.145060574  , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 4487419.119544039  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetENU2NED)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Matrix3x3 enu2ned = ecef.getENU2NED();

    const mc::Vector3 v_enu( 1.0, 2.0, 3.0 );
    mc::Vector3 v_ned = enu2ned * v_enu;

    EXPECT_DOUBLE_EQ( v_ned.x(),  2.0 );
    EXPECT_DOUBLE_EQ( v_ned.y(),  1.0 );
    EXPECT_DOUBLE_EQ( v_ned.z(), -3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetNED2ENU)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Matrix3x3 ned2enu = ecef.getNED2ENU();

    const mc::Vector3 v_ned( 1.0, 2.0, 3.0 );
    mc::Vector3 v_enu = ned2enu * v_ned;

    EXPECT_DOUBLE_EQ( v_enu.x(),  2.0 );
    EXPECT_DOUBLE_EQ( v_enu.y(),  1.0 );
    EXPECT_DOUBLE_EQ( v_enu.z(), -3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetENU2ECEF)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;

    mc::Matrix3x3 enu2ecef;

    const mc::Vector3 v_enu( 1.0, 2.0, 3.0 );
    mc::Vector3 v_ecef;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    enu2ecef = ecef.getENU2ECEF();
    v_ecef = enu2ecef * v_enu;

    EXPECT_DOUBLE_EQ( v_ecef.x(),  3.0 );
    EXPECT_DOUBLE_EQ( v_ecef.y(),  1.0 );
    EXPECT_DOUBLE_EQ( v_ecef.z(),  2.0 );

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    enu2ecef = ecef.getENU2ECEF();
    v_ecef = enu2ecef * v_enu;

    EXPECT_DOUBLE_EQ( v_ecef.x(), -1.0 );
    EXPECT_DOUBLE_EQ( v_ecef.y(),  3.0 );
    EXPECT_DOUBLE_EQ( v_ecef.z(),  2.0 );

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    enu2ecef = ecef.getENU2ECEF();
    v_ecef = enu2ecef * v_enu;

    EXPECT_DOUBLE_EQ( v_ecef.x(),  1.0 );
    EXPECT_DOUBLE_EQ( v_ecef.y(), -3.0 );
    EXPECT_DOUBLE_EQ( v_ecef.z(),  2.0 );

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    enu2ecef = ecef.getENU2ECEF();
    v_ecef = enu2ecef * v_enu;

    EXPECT_DOUBLE_EQ( v_ecef.x(), -3.0 );
    EXPECT_DOUBLE_EQ( v_ecef.y(), -1.0 );
    EXPECT_DOUBLE_EQ( v_ecef.z(),  2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetNED2ECEF)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;

    mc::Matrix3x3 ned2ecef;

    const mc::Vector3 v_ned( 1.0, 2.0, 3.0 );
    mc::Vector3 v_ecef;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ned2ecef = ecef.getNED2ECEF();
    v_ecef = ned2ecef * v_ned;

    EXPECT_DOUBLE_EQ( v_ecef.x(), -3.0 );
    EXPECT_DOUBLE_EQ( v_ecef.y(),  2.0 );
    EXPECT_DOUBLE_EQ( v_ecef.z(),  1.0 );

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ned2ecef = ecef.getNED2ECEF();
    v_ecef = ned2ecef * v_ned;

    EXPECT_DOUBLE_EQ( v_ecef.x(), -2.0 );
    EXPECT_DOUBLE_EQ( v_ecef.y(), -3.0 );
    EXPECT_DOUBLE_EQ( v_ecef.z(),  1.0 );

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ned2ecef = ecef.getNED2ECEF();
    v_ecef = ned2ecef * v_ned;

    EXPECT_DOUBLE_EQ( v_ecef.x(),  2.0 );
    EXPECT_DOUBLE_EQ( v_ecef.y(),  3.0 );
    EXPECT_DOUBLE_EQ( v_ecef.z(),  1.0 );

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ned2ecef = ecef.getNED2ECEF();
    v_ecef = ned2ecef * v_ned;

    EXPECT_DOUBLE_EQ( v_ecef.x(),  3.0 );
    EXPECT_DOUBLE_EQ( v_ecef.y(), -2.0 );
    EXPECT_DOUBLE_EQ( v_ecef.z(),  1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetECEF2ENU)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;

    mc::Matrix3x3 ecef2enu;

    const mc::Vector3 v_ecef( 1.0, 2.0, 3.0 );
    mc::Vector3 v_enu;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ecef2enu = ecef.getECEF2ENU();
    v_enu = ecef2enu * v_ecef;

    EXPECT_DOUBLE_EQ( v_enu.x(),  2.0 );
    EXPECT_DOUBLE_EQ( v_enu.y(),  3.0 );
    EXPECT_DOUBLE_EQ( v_enu.z(),  1.0 );

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ecef2enu = ecef.getECEF2ENU();
    v_enu = ecef2enu * v_ecef;

    EXPECT_DOUBLE_EQ( v_enu.x(), -1.0 );
    EXPECT_DOUBLE_EQ( v_enu.y(),  3.0 );
    EXPECT_DOUBLE_EQ( v_enu.z(),  2.0 );

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ecef2enu = ecef.getECEF2ENU();
    v_enu = ecef2enu * v_ecef;

    EXPECT_DOUBLE_EQ( v_enu.x(),  1.0 );
    EXPECT_DOUBLE_EQ( v_enu.y(),  3.0 );
    EXPECT_DOUBLE_EQ( v_enu.z(), -2.0 );

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ecef2enu = ecef.getECEF2ENU();
    v_enu = ecef2enu * v_ecef;

    EXPECT_DOUBLE_EQ( v_enu.x(), -2.0 );
    EXPECT_DOUBLE_EQ( v_enu.y(),  3.0 );
    EXPECT_DOUBLE_EQ( v_enu.z(), -1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanGetECEF2NED)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo;

    mc::Matrix3x3 ecef2ned;

    const mc::Vector3 v_ecef( 1.0, 2.0, 3.0 );
    mc::Vector3 v_ned;

    // 0N 0E
    pos_geo.lat = 0.0;
    pos_geo.lon = 0.0;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ecef2ned = ecef.getECEF2NED();
    v_ned = ecef2ned * v_ecef;

    EXPECT_DOUBLE_EQ( v_ned.x(),  3.0 );
    EXPECT_DOUBLE_EQ( v_ned.y(),  2.0 );
    EXPECT_DOUBLE_EQ( v_ned.z(), -1.0 );

    // 0N 90E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ecef2ned = ecef.getECEF2NED();
    v_ned = ecef2ned * v_ecef;

    EXPECT_DOUBLE_EQ( v_ned.x(),  3.0 );
    EXPECT_DOUBLE_EQ( v_ned.y(), -1.0 );
    EXPECT_DOUBLE_EQ( v_ned.z(), -2.0 );

    // 0N 90W
    pos_geo.lat = 0.0;
    pos_geo.lon = -M_PI_2;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ecef2ned = ecef.getECEF2NED();
    v_ned = ecef2ned * v_ecef;

    EXPECT_DOUBLE_EQ( v_ned.x(),  3.0 );
    EXPECT_DOUBLE_EQ( v_ned.y(),  1.0 );
    EXPECT_DOUBLE_EQ( v_ned.z(),  2.0 );

    // 0N 180E
    pos_geo.lat = 0.0;
    pos_geo.lon = M_PI;
    pos_geo.alt = 0.0;
    ecef.setPos_Geo( pos_geo );

    ecef2ned = ecef.getECEF2NED();
    v_ned = ecef2ned * v_ecef;

    EXPECT_DOUBLE_EQ( v_ned.x(),  3.0 );
    EXPECT_DOUBLE_EQ( v_ned.y(), -2.0 );
    EXPECT_DOUBLE_EQ( v_ned.z(),  1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanSetPosGeo)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Geo pos_geo_in;
    mc::Geo pos_geo;

    // 0N 0E
    pos_geo_in.lat = 0.0;
    pos_geo_in.lon = 0.0;
    pos_geo_in.alt = 0.0;
    ecef.setPos_Geo( pos_geo_in );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 0E H=100m
    pos_geo_in.lat = 0.0;
    pos_geo_in.lon = 0.0;
    pos_geo_in.alt = 100.0;
    ecef.setPos_Geo( pos_geo_in );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 100.0, 1.0e-4 );

    // 0N 90E
    pos_geo_in.lat = 0.0;
    pos_geo_in.lon = M_PI_2;
    pos_geo_in.alt = 0.0;
    ecef.setPos_Geo( pos_geo_in );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI_2, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 180E
    pos_geo_in.lat = 0.0;
    pos_geo_in.lon = M_PI;
    pos_geo_in.alt = 0.0;
    ecef.setPos_Geo( pos_geo_in );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 90W
    pos_geo_in.lat = 0.0;
    pos_geo_in.lon = -M_PI_2;
    pos_geo_in.alt = 0.0;
    ecef.setPos_Geo( pos_geo_in );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, -M_PI_2, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 30E
    pos_geo_in.lat = 0.0;
    pos_geo_in.lon = 30.0 * M_PI / 180.0;
    pos_geo_in.alt = 0.0;
    ecef.setPos_Geo( pos_geo_in );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 30.0 * M_PI / 180.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 45E
    pos_geo_in.lat = 0.0;
    pos_geo_in.lon = 45.0 * M_PI / 180.0;
    pos_geo_in.alt = 0.0;
    ecef.setPos_Geo( pos_geo_in );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 45.0 * M_PI / 180.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 0N 60E
    pos_geo_in.lat = 0.0;
    pos_geo_in.lon = 60.0 * M_PI / 180.0;
    pos_geo_in.alt = 0.0;
    ecef.setPos_Geo( pos_geo_in );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, 0.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, 60.0 * M_PI / 180.0, 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 0.0, 1.0e-4 );

    // 45N 45E H=100m
    pos_geo_in.lat =  M_PI_4;
    pos_geo_in.lon =  M_PI_4;
    pos_geo_in.alt =  100.0;
    ecef.setPos_Geo( pos_geo_in );

    pos_geo = ecef.getPos_Geo();

    EXPECT_NEAR( pos_geo.lat, M_PI_4 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.lon, M_PI_4 , 1.0e-9 ); // ca. 6mm accuracy
    EXPECT_NEAR( pos_geo.alt, 100.0  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanSetPosECEF)
{
    mc::ECEF ecef( mc::DataWGS84::a, mc::DataWGS84::f );

    mc::Vector3 pos_ecef_in;
    mc::Vector3 pos_ecef;

    // 0N 0E
    pos_ecef_in.x() = mc::DataWGS84::a;
    pos_ecef_in.y() = 0.0;
    pos_ecef_in.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef_in );

    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 0E H=100m
    pos_ecef_in.x() = mc::DataWGS84::a + 100.0;
    pos_ecef_in.y() = 0.0;
    pos_ecef_in.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef_in );

    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), mc::DataWGS84::a + 100.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 90E
    pos_ecef_in.x() = 0.0;
    pos_ecef_in.y() = mc::DataWGS84::a;
    pos_ecef_in.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef_in );

    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 180E
    pos_ecef_in.x() = -mc::DataWGS84::a;
    pos_ecef_in.y() = 0.0;
    pos_ecef_in.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef_in );

    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), -mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 90W
    pos_ecef_in.x() = 0.0;
    pos_ecef_in.y() = -mc::DataWGS84::a;
    pos_ecef_in.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef_in );

    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), -mc::DataWGS84::a, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 90N 0E
    pos_ecef_in.x() = 0.0;
    pos_ecef_in.y() = 0.0;
    pos_ecef_in.z() = mc::DataWGS84::b;
    ecef.setPos_ECEF( pos_ecef_in );

    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), mc::DataWGS84::b, 1.0e-4 );

    // 90S 0E
    pos_ecef_in.x() = 0.0;
    pos_ecef_in.y() = 0.0;
    pos_ecef_in.z() = -mc::DataWGS84::b;
    ecef.setPos_ECEF( pos_ecef_in );

    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 0.0, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), -mc::DataWGS84::b, 1.0e-4 );

    // 0N 30E
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_ecef_in.x() = 5523628.670817468;
    pos_ecef_in.y() = 3189068.4999999995;
    pos_ecef_in.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef_in );

    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 5523628.670817468  , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 3189068.4999999995 , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 45E
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_ecef_in.x() = 4510023.924036823;
    pos_ecef_in.y() = 4510023.924036822;
    pos_ecef_in.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef_in );

    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 4510023.924036823, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 4510023.924036822, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 0N 60E
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_ecef_in.x() = 3189068.500000001;
    pos_ecef_in.y() = 5523628.670817467;
    pos_ecef_in.z() = 0.0;
    ecef.setPos_ECEF( pos_ecef_in );

    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 3189068.500000001, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 5523628.670817467, 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 0.0, 1.0e-4 );

    // 45N 45E H=100m
    // values calculated with PROJ4
    // tests/geo/python/test_geo_ecef.py
    pos_ecef_in.x() = 3194469.1450605746;
    pos_ecef_in.y() = 3194469.145060574;
    pos_ecef_in.z() = 4487419.119544039;
    ecef.setPos_ECEF( pos_ecef_in );

    pos_ecef = ecef.getPos_ECEF();
    EXPECT_NEAR( pos_ecef.x(), 3194469.1450605746 , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.y(), 3194469.145060574  , 1.0e-4 );
    EXPECT_NEAR( pos_ecef.z(), 4487419.119544039  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanAssign)
{
    mc::ECEF ecef;

    mc::ECEF ecef0( mc::DataMars::a, mc::DataMars::f );

    ecef = ecef0;

    EXPECT_NEAR( ecef.getA   (), mc::DataMars::a   , 1.0e-9 );
    EXPECT_NEAR( ecef.getF   (), mc::DataMars::f   , 1.0e-9 );
    EXPECT_NEAR( ecef.getB   (), mc::DataMars::b   , 1.0e-4 );
    EXPECT_NEAR( ecef.getR1  (), mc::DataMars::r1  , 1.0e-4 );
    EXPECT_NEAR( ecef.getA2  (), mc::DataMars::a2  , 1.0e3  ); // sic!
    EXPECT_NEAR( ecef.getB2  (), mc::DataMars::b2  , 1.0e3  ); // sic!
    EXPECT_NEAR( ecef.getE2  (), mc::DataMars::e2  , 1.0e-4 );
    EXPECT_NEAR( ecef.getE   (), mc::DataMars::e   , 1.0e-4 );
    EXPECT_NEAR( ecef.getEp2 (), mc::DataMars::ep2 , 1.0e-4 );
    EXPECT_NEAR( ecef.getEp  (), mc::DataMars::ep  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestECEF, CanAssignMove)
{
    mc::ECEF ecef;

    ecef = std::move( mc::ECEF( mc::DataMars::a, mc::DataMars::f ) );

    EXPECT_NEAR( ecef.getA   (), mc::DataMars::a   , 1.0e-9 );
    EXPECT_NEAR( ecef.getF   (), mc::DataMars::f   , 1.0e-9 );
    EXPECT_NEAR( ecef.getB   (), mc::DataMars::b   , 1.0e-4 );
    EXPECT_NEAR( ecef.getR1  (), mc::DataMars::r1  , 1.0e-4 );
    EXPECT_NEAR( ecef.getA2  (), mc::DataMars::a2  , 1.0e3  ); // sic!
    EXPECT_NEAR( ecef.getB2  (), mc::DataMars::b2  , 1.0e3  ); // sic!
    EXPECT_NEAR( ecef.getE2  (), mc::DataMars::e2  , 1.0e-4 );
    EXPECT_NEAR( ecef.getE   (), mc::DataMars::e   , 1.0e-4 );
    EXPECT_NEAR( ecef.getEp2 (), mc::DataMars::ep2 , 1.0e-4 );
    EXPECT_NEAR( ecef.getEp  (), mc::DataMars::ep  , 1.0e-4 );
}
