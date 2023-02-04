#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/geo/Mercator.h>
#include <mcutils/geo/DataWGS84.h>

////////////////////////////////////////////////////////////////////////////////

class TestMercator : public ::testing::Test
{
protected:
    TestMercator() {}
    virtual ~TestMercator() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMercator, CanConstruct)
{
    mc::Mercator *merc = nullptr;
    EXPECT_NO_THROW( merc = new mc::Mercator( mc::DataWGS84::a, mc::DataWGS84::e ) );
    delete merc;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMercator, CanDestruct)
{
    mc::Mercator *merc = new mc::Mercator( mc::DataWGS84::a, mc::DataWGS84::e );
    EXPECT_NO_THROW( delete merc );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMercator, CanInstantiate)
{
    mc::Mercator merc( mc::DataWGS84::a, mc::DataWGS84::e );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMercator, CanCalculateLat)
{
    mc::Mercator merc( mc::DataWGS84::a, mc::DataWGS84::e );

    constexpr double nautical_mile = 1852.0;
    constexpr double arc_deg = 60.0 * nautical_mile;

    constexpr double arc_deg30 = 30.0 * arc_deg;
    constexpr double arc_deg45 = 45.0 * arc_deg;
    constexpr double arc_deg60 = 60.0 * arc_deg;
    constexpr double arc_deg90 = 90.0 * arc_deg;

    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_mercator.py

    EXPECT_NEAR( merc.lat( 0.0 ), 0.0, 1.0e-6 );

    EXPECT_NEAR( merc.lat( arc_deg30 ), 0.503202371118002  , 1.0e-6 );
    EXPECT_NEAR( merc.lat( arc_deg45 ), 0.7174954798366173 , 1.0e-6 );
    EXPECT_NEAR( merc.lat( arc_deg60 ), 0.8979087261408331 , 1.0e-6 );
    EXPECT_NEAR( merc.lat( arc_deg90 ), 1.1622044409794392 , 1.0e-6 );

    EXPECT_NEAR( merc.lat( -arc_deg30 ), -0.5032023711180025 , 1.0e-6 );
    EXPECT_NEAR( merc.lat( -arc_deg45 ), -0.7174954798366175 , 1.0e-6 );
    EXPECT_NEAR( merc.lat( -arc_deg60 ), -0.8979087261408334 , 1.0e-6 );
    EXPECT_NEAR( merc.lat( -arc_deg90 ), -1.1622044409794392 , 1.0e-6 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMercator, CanCalculateLon)
{
    mc::Mercator merc( mc::DataWGS84::a, mc::DataWGS84::e );

    constexpr double nautical_mile = 1852.0;
    constexpr double arc_deg = 60.0 * nautical_mile;

    constexpr double arc_deg30  =  30.0 * arc_deg;
    constexpr double arc_deg45  =  45.0 * arc_deg;
    constexpr double arc_deg60  =  60.0 * arc_deg;
    constexpr double arc_deg90  =  90.0 * arc_deg;
    constexpr double arc_deg120 = 120.0 * arc_deg;
    constexpr double arc_deg150 = 150.0 * arc_deg;
    constexpr double arc_deg180 = 180.0 * arc_deg;

    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_mercator.py

    EXPECT_NEAR( merc.lon( 0.0 ), 0.0, 1.0e-6 );

    EXPECT_NEAR( merc.lon( arc_deg30  ), 0.522660457120943  , 1.0e-6 );
    EXPECT_NEAR( merc.lon( arc_deg45  ), 0.7839906856814144 , 1.0e-6 );
    EXPECT_NEAR( merc.lon( arc_deg60  ), 1.045320914241886  , 1.0e-6 );
    EXPECT_NEAR( merc.lon( arc_deg90  ), 1.5679813713628288 , 1.0e-6 );
    EXPECT_NEAR( merc.lon( arc_deg120 ), 2.090641828483772  , 1.0e-6 );
    EXPECT_NEAR( merc.lon( arc_deg150 ), 2.613302285604715  , 1.0e-6 );
    EXPECT_NEAR( merc.lon( arc_deg180 ), 3.1359627427256576 , 1.0e-6 );

    EXPECT_NEAR( merc.lon( -arc_deg30  ), -0.522660457120943  , 1.0e-6 );
    EXPECT_NEAR( merc.lon( -arc_deg45  ), -0.7839906856814144 , 1.0e-6 );
    EXPECT_NEAR( merc.lon( -arc_deg60  ), -1.045320914241886  , 1.0e-6 );
    EXPECT_NEAR( merc.lon( -arc_deg90  ), -1.5679813713628288 , 1.0e-6 );
    EXPECT_NEAR( merc.lon( -arc_deg120 ), -2.090641828483772  , 1.0e-6 );
    EXPECT_NEAR( merc.lon( -arc_deg150 ), -2.613302285604715  , 1.0e-6 );
    EXPECT_NEAR( merc.lon( -arc_deg180 ), -3.1359627427256576 , 1.0e-6 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMercator, CanCalculateX)
{
    mc::Mercator merc( mc::DataWGS84::a, mc::DataWGS84::e );

    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_mercator.py

    double lon = 0.0;
    EXPECT_NEAR( merc.x( lon ), 0.0, 1.0e-6 );

    lon = 30.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), 3339584.723798207, 1.0e-6 );

    lon = 45.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), 5009377.085697311, 1.0e-6 );

    lon = 60.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), 6679169.447596414, 1.0e-6 );

    lon = 90.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), 10018754.171394622, 1.0e-6 );

    lon = 120.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), 13358338.895192828, 1.0e-6 );

    lon = 150.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), 16697923.618991036, 1.0e-6 );

    lon = 180.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), 20037508.342789244, 1.0e-6 );

    lon = -30.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), -3339584.723798207, 1.0e-6 );

    lon = -45.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), -5009377.085697311, 1.0e-6 );

    lon = -60.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), -6679169.447596414, 1.0e-6 );

    lon = -90.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), -10018754.171394622, 1.0e-6 );

    lon = -120.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), -13358338.895192828, 1.0e-6 );

    lon = -150.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), -16697923.618991036, 1.0e-6 );

    lon = -180.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.x( lon ), -20037508.342789244, 1.0e-6 );
}


////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMercator, CanCalculateY)
{
    mc::Mercator merc( mc::DataWGS84::a, mc::DataWGS84::e );

    // expected values calculated with PROJ4
    // tests/geo/python/test_geo_mercator.py

    double lat = 0.0;
    EXPECT_NEAR( merc.y( lat ), 0.0, 1.0e-6 );

    lat = 30.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.y( lat ), 3482189.0854086173, 1.0e-6 );

    lat = 45.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.y( lat ), 5591295.918553392, 1.0e-6 );

    lat = 60.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.y( lat ), 8362698.548500749, 1.0e-6 );

    lat = 85.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.y( lat ), 19929239.113379154, 1.0e-6 );

    lat = -30.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.y( lat ), -3482189.085408616, 1.0e-6 );

    lat = -45.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.y( lat ), -5591295.9185533915, 1.0e-6 );

    lat = -60.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.y( lat ), -8362698.548500745, 1.0e-6 );

    lat = -85.0 * ( M_PI / 180.0 );
    EXPECT_NEAR( merc.y( lat ), -19929239.113379147, 1.0e-6 );

}
