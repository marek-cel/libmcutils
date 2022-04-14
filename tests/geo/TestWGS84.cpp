#include <gtest/gtest.h>

#include <mcutils/geo/WGS84.h>
#include <mcutils/geo/DataWGS84.h>

////////////////////////////////////////////////////////////////////////////////

class TestWGS84 : public ::testing::Test
{
protected:
    TestWGS84() {}
    virtual ~TestWGS84() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestWGS84, CanConstruct)
{
    mc::WGS84 *wgs = nullptr;
    EXPECT_NO_THROW( wgs = new mc::WGS84 );
    delete wgs;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestWGS84, CanDestruct)
{
    mc::WGS84 *wgs = new mc::WGS84;
    EXPECT_NO_THROW( delete wgs );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestWGS84, CanInstantiate)
{
    mc::WGS84 wgs;

    EXPECT_NEAR( wgs.getA   (), mc::DataWGS84::a   , 1.0e-9 );
    EXPECT_NEAR( wgs.getF   (), mc::DataWGS84::f   , 1.0e-9 );
    EXPECT_NEAR( wgs.getB   (), mc::DataWGS84::b   , 1.0e-4 );
    EXPECT_NEAR( wgs.getR1  (), mc::DataWGS84::r1  , 1.0e-4 );
    EXPECT_NEAR( wgs.getA2  (), mc::DataWGS84::a2  , 1.0e3  ); // sic!
    EXPECT_NEAR( wgs.getB2  (), mc::DataWGS84::b2  , 1.0e3  ); // sic!
    EXPECT_NEAR( wgs.getE2  (), mc::DataWGS84::e2  , 1.0e-4 );
    EXPECT_NEAR( wgs.getE   (), mc::DataWGS84::e   , 1.0e-4 );
    EXPECT_NEAR( wgs.getEp2 (), mc::DataWGS84::ep2 , 1.0e-4 );
    EXPECT_NEAR( wgs.getEp  (), mc::DataWGS84::ep  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestWGS84, CanInstantiateAndCopy)
{
    mc::Geo pos_geo;
    mc::Geo pos_geo_out;

    pos_geo.lat = M_PI_4;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 100.0;

    mc::WGS84 wgs0( pos_geo );

    mc::WGS84 wgs( wgs0 );

    pos_geo_out = wgs.getPos_Geo();

    EXPECT_DOUBLE_EQ( pos_geo_out.lat, M_PI_4 );
    EXPECT_DOUBLE_EQ( pos_geo_out.lon, M_PI_4 );
    EXPECT_DOUBLE_EQ( pos_geo_out.alt, 100.0  );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestWGS84, CanInstantiateAndMove)
{
    mc::Geo pos_geo;
    mc::Geo pos_geo_out;

    pos_geo.lat = M_PI_4;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 100.0;

    mc::WGS84 wgs( std::move( mc::WGS84( pos_geo ) ) );

    pos_geo_out = wgs.getPos_Geo();

    EXPECT_DOUBLE_EQ( pos_geo_out.lat, M_PI_4 );
    EXPECT_DOUBLE_EQ( pos_geo_out.lon, M_PI_4 );
    EXPECT_DOUBLE_EQ( pos_geo_out.alt, 100.0  );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestWGS84, CanInstantiateAndSetPosGeo)
{
    mc::Geo pos_geo;

    pos_geo.lat = M_PI_4;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 100.0;

    mc::WGS84 wgs( pos_geo );

    mc::Geo     pos_geo_out = wgs.getPos_Geo();
    mc::Vector3 pos_wgs_out = wgs.getPos_WGS();

    EXPECT_NEAR( pos_geo_out.lat, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo_out.lon, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo_out.alt, 100.0  , 1.0e-4 );

    EXPECT_NEAR( pos_wgs_out.x(), 3194469.1450605746 , 1.0e-4 );
    EXPECT_NEAR( pos_wgs_out.y(), 3194469.145060574  , 1.0e-4 );
    EXPECT_NEAR( pos_wgs_out.z(), 4487419.119544039  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestWGS84, CanInstantiateAndSetPosWGS)
{
    mc::Vector3 pos_wgs;

    pos_wgs.x() = 3194469.1450605746;
    pos_wgs.y() = 3194469.145060574;
    pos_wgs.z() = 4487419.119544039;

    mc::WGS84 wgs( pos_wgs );

    mc::Geo     pos_geo_out = wgs.getPos_Geo();
    mc::Vector3 pos_wgs_out = wgs.getPos_WGS();

    EXPECT_NEAR( pos_geo_out.lat, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo_out.lon, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo_out.alt, 100.0  , 1.0e-4 );

    EXPECT_NEAR( pos_wgs_out.x(), 3194469.1450605746 , 1.0e-4 );
    EXPECT_NEAR( pos_wgs_out.y(), 3194469.145060574  , 1.0e-4 );
    EXPECT_NEAR( pos_wgs_out.z(), 4487419.119544039  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestWGS84, CanSetPosWGS)
{
    mc::Vector3 pos_wgs;

    pos_wgs.x() = 3194469.1450605746;
    pos_wgs.y() = 3194469.145060574;
    pos_wgs.z() = 4487419.119544039;

    mc::WGS84 wgs;

    EXPECT_NO_THROW( wgs.setPos_WGS( pos_wgs ) );

    mc::Geo     pos_geo_out = wgs.getPos_Geo();
    mc::Vector3 pos_wgs_out = wgs.getPos_WGS();

    EXPECT_NEAR( pos_geo_out.lat, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo_out.lon, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo_out.alt, 100.0  , 1.0e-4 );

    EXPECT_NEAR( pos_wgs_out.x(), 3194469.1450605746 , 1.0e-4 );
    EXPECT_NEAR( pos_wgs_out.y(), 3194469.145060574  , 1.0e-4 );
    EXPECT_NEAR( pos_wgs_out.z(), 4487419.119544039  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestWGS84, CanGetPosWGS)
{
    mc::Vector3 pos_wgs;

    pos_wgs.x() = 3194469.1450605746;
    pos_wgs.y() = 3194469.145060574;
    pos_wgs.z() = 4487419.119544039;

    mc::WGS84 wgs;

    wgs.setPos_WGS( pos_wgs );

    mc::Vector3 pos_wgs_out = wgs.getPos_WGS();

    EXPECT_NEAR( pos_wgs_out.x(), 3194469.1450605746 , 1.0e-4 );
    EXPECT_NEAR( pos_wgs_out.y(), 3194469.145060574  , 1.0e-4 );
    EXPECT_NEAR( pos_wgs_out.z(), 4487419.119544039  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestWGS84, CanAssign)
{
    mc::WGS84 wgs;

    mc::Geo pos_geo;

    pos_geo.lat = M_PI_4;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 100.0;

    mc::WGS84 wgs0( pos_geo );

    wgs = wgs0;

    mc::Geo     pos_geo_out = wgs.getPos_Geo();
    mc::Vector3 pos_wgs_out = wgs.getPos_WGS();

    EXPECT_NEAR( pos_geo_out.lat, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo_out.lon, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo_out.alt, 100.0  , 1.0e-4 );

    EXPECT_NEAR( pos_wgs_out.x(), 3194469.1450605746 , 1.0e-4 );
    EXPECT_NEAR( pos_wgs_out.y(), 3194469.145060574  , 1.0e-4 );
    EXPECT_NEAR( pos_wgs_out.z(), 4487419.119544039  , 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestWGS84, CanAssignMove)
{
    mc::WGS84 wgs;

    mc::Geo pos_geo;

    pos_geo.lat = M_PI_4;
    pos_geo.lon = M_PI_4;
    pos_geo.alt = 100.0;

    wgs = std::move( mc::WGS84( pos_geo ) );

    mc::Geo     pos_geo_out = wgs.getPos_Geo();
    mc::Vector3 pos_wgs_out = wgs.getPos_WGS();

    EXPECT_NEAR( pos_geo_out.lat, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo_out.lon, M_PI_4 , 1.0e-5 );
    EXPECT_NEAR( pos_geo_out.alt, 100.0  , 1.0e-4 );

    EXPECT_NEAR( pos_wgs_out.x(), 3194469.1450605746 , 1.0e-4 );
    EXPECT_NEAR( pos_wgs_out.y(), 3194469.145060574  , 1.0e-4 );
    EXPECT_NEAR( pos_wgs_out.z(), 4487419.119544039  , 1.0e-4 );
}
