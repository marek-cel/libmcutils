#include <gtest/gtest.h>

#include <mcutils/misc/Units.h>

class TestUnits : public ::testing::Test
{
protected:

    TestUnits() {}
    virtual ~TestUnits() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestUnits, CanGetUnitConverter)
{
    EXPECT_EQ(nullptr, mc::Units::GetUnitConverter("gibberish"));

    // angle
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("rad")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::deg2rad(1.0), mc::Units::GetUnitConverter("deg")(1.0));

    // length
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("m")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::ft2m(1.0)  , mc::Units::GetUnitConverter("ft")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::in2m(1.0)  , mc::Units::GetUnitConverter("in")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::km2m(1.0)  , mc::Units::GetUnitConverter("km")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::nmi2m(1.0) , mc::Units::GetUnitConverter("nmi")(1.0));

    // area
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("sq_m")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::sqft2sqm(1.0), mc::Units::GetUnitConverter("sq_ft")(1.0));

    // volume
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("cu_m")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::cuft2cum(1.0) , mc::Units::GetUnitConverter("cu_ft")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::cuin2cum(1.0) , mc::Units::GetUnitConverter("cu_in")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::l2cum(1.0)    , mc::Units::GetUnitConverter("l")(1.0));

    // velocity
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("mps")(1.0));
    EXPECT_EQ(mc::Units::fpm2mps(1.0) , mc::Units::GetUnitConverter("fpm")(1.0));
    EXPECT_EQ(mc::Units::fps2mps(1.0) , mc::Units::GetUnitConverter("fps")(1.0));
    EXPECT_EQ(mc::Units::kmh2mps(1.0) , mc::Units::GetUnitConverter("kmh")(1.0));
    EXPECT_EQ(mc::Units::kts2mps(1.0) , mc::Units::GetUnitConverter("kts")(1.0));

    // angular velocity
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("rad/s")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::deg2rad(1.0)   , mc::Units::GetUnitConverter("deg/s")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::rpm2rad_s(1.0) , mc::Units::GetUnitConverter("rpm")(1.0));

    // mass
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("kg")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::lb2kg(1.0), mc::Units::GetUnitConverter("lb")(1.0));

    // force
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("N")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::lbf2n(1.0), mc::Units::GetUnitConverter("lbf")(1.0));

    // pressure
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("Pa")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::psf2pa(1.0)  , mc::Units::GetUnitConverter("psf")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::psi2pa(1.0)  , mc::Units::GetUnitConverter("psi")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::inhg2pa(1.0) , mc::Units::GetUnitConverter("inHg")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::mb2pa(1.0)   , mc::Units::GetUnitConverter("mb")(1.0));

    // power
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("W")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::ps2w(1.0), mc::Units::GetUnitConverter("PS")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::hp2w(1.0), mc::Units::GetUnitConverter("hp")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::kw2w(1.0), mc::Units::GetUnitConverter("kW")(1.0));

    // temperature
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("K")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::c2k(1.0), mc::Units::GetUnitConverter("deg_C")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::f2k(1.0), mc::Units::GetUnitConverter("deg_F")(1.0));

    // specific fuel consumption
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("kg/Ws")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::g_kWh_2_kg_Ws(1.0), mc::Units::GetUnitConverter("g/kWh")(1.0));

    // thrust specific fuel consumption
    EXPECT_DOUBLE_EQ(1.0, mc::Units::GetUnitConverter("kg/Ns")(1.0));
    EXPECT_DOUBLE_EQ(mc::Units::g_kNs_2_kg_Ns(1.0), mc::Units::GetUnitConverter("g/kNs")(1.0));
}

TEST_F(TestUnits, CanConvertDeg2Rad)
{
    EXPECT_NEAR(mc::Units::deg2rad(   0.0 ), 0.0    , 1.0e-9);
    EXPECT_NEAR(mc::Units::deg2rad(  45.0 ), M_PI_4 , 1.0e-9);
    EXPECT_NEAR(mc::Units::deg2rad(  90.0 ), M_PI_2 , 1.0e-9);
    EXPECT_NEAR(mc::Units::deg2rad( 180.0 ), M_PI   , 1.0e-9);
}

TEST_F(TestUnits, CanConvertRad2Deg)
{
    EXPECT_NEAR(mc::Units::rad2deg( 0.0    ),   0.0 , 1.0e-9);
    EXPECT_NEAR(mc::Units::rad2deg( M_PI_4 ),  45.0 , 1.0e-9);
    EXPECT_NEAR(mc::Units::rad2deg( M_PI_2 ),  90.0 , 1.0e-9);
    EXPECT_NEAR(mc::Units::rad2deg( M_PI   ), 180.0 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertM2Ft)
{
    EXPECT_NEAR(mc::Units::m2ft(0.0), 0.0       , 1.0e-9);
    EXPECT_NEAR(mc::Units::m2ft(1.0), 3.2808399 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertM2In)
{
    EXPECT_NEAR(mc::Units::m2in(0.0), 0.0        , 1.0e-9);
    EXPECT_NEAR(mc::Units::m2in(1.0), 39.3700787 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertM2Mi)
{
    EXPECT_NEAR(mc::Units::m2mi(0.0), 0.0            , 1.0e-9);
    EXPECT_NEAR(mc::Units::m2mi(1.0), 0.000621371192 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertM2Nmi)
{
    EXPECT_NEAR(mc::Units::m2nmi(0.0), 0.0            , 1.0e-9);
    EXPECT_NEAR(mc::Units::m2nmi(1.0), 0.000539956803 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertM2Km)
{
    EXPECT_NEAR(mc::Units::m2km(0.0), 0.0   , 1.0e-9);
    EXPECT_NEAR(mc::Units::m2km(1.0), 0.001 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFt2M)
{
    EXPECT_NEAR(mc::Units::ft2m(0.0), 0.0    , 1.0e-9);
    EXPECT_NEAR(mc::Units::ft2m(1.0), 0.3048 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFt2Km)
{
    EXPECT_NEAR(mc::Units::ft2km(0.0), 0.0       , 1.0e-9);
    EXPECT_NEAR(mc::Units::ft2km(1.0), 0.0003048 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFt2Mi)
{
    EXPECT_NEAR(mc::Units::ft2mi(0.0), 0.0            , 1.0e-9);
    EXPECT_NEAR(mc::Units::ft2mi(1.0), 0.000189393939 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFt2Nmi)
{
    EXPECT_NEAR(mc::Units::ft2nmi(0.0), 0.0            , 1.0e-9);
    EXPECT_NEAR(mc::Units::ft2nmi(1.0), 0.000164578834 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertIn2M)
{
    EXPECT_NEAR(mc::Units::in2m(0.0), 0.0    , 1.0e-9);
    EXPECT_NEAR(mc::Units::in2m(1.0), 0.0254 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKm2M)
{
    EXPECT_NEAR(mc::Units::km2m(0.0), 0.0    , 1.0e-9);
    EXPECT_NEAR(mc::Units::km2m(1.0), 1000.0 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKm2Ft)
{
    EXPECT_NEAR(mc::Units::km2ft(0.0), 0.0       , 1.0e-9);
    EXPECT_NEAR(mc::Units::km2ft(1.0), 3280.8399 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKm2Mi)
{
    EXPECT_NEAR(mc::Units::km2mi(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::km2mi(1.0), 0.621371192 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKm2Nmi)
{
    EXPECT_NEAR(mc::Units::km2nmi(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::km2nmi(1.0), 0.539956803 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMi2M)
{
    EXPECT_NEAR(mc::Units::mi2m(0.0), 0.0      , 1.0e-9);
    EXPECT_NEAR(mc::Units::mi2m(1.0), 1609.344 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMi2Ft)
{
    EXPECT_NEAR(mc::Units::mi2ft(0.0), 0.0    , 1.0e-9);
    EXPECT_NEAR(mc::Units::mi2ft(1.0), 5280.0 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMi2Km)
{
    EXPECT_NEAR(mc::Units::mi2km(0.0), 0.0      , 1.0e-9);
    EXPECT_NEAR(mc::Units::mi2km(1.0), 1.609344 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMi2Nmi)
{
    EXPECT_NEAR(mc::Units::mi2nmi(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::mi2nmi(1.0), 0.868976242 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertNmi2M)
{
    EXPECT_NEAR(mc::Units::nmi2m(0.0), 0.0    , 1.0e-9);
    EXPECT_NEAR(mc::Units::nmi2m(1.0), 1852.0 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertNmi2Ft)
{
    EXPECT_NEAR(mc::Units::nmi2ft(0.0), 0.0        , 1.0e-9);
    EXPECT_NEAR(mc::Units::nmi2ft(1.0), 6076.11549 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertNmi2Km)
{
    EXPECT_NEAR(mc::Units::nmi2km(0.0), 0.0   , 1.0e-9);
    EXPECT_NEAR(mc::Units::nmi2km(1.0), 1.852 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertNmi2Mi)
{
    EXPECT_NEAR(mc::Units::nmi2mi(0.0), 0.0        , 1.0e-9);
    EXPECT_NEAR(mc::Units::nmi2mi(1.0), 1.15077945 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertSqM2SqFt)
{
    EXPECT_NEAR(mc::Units::sqm2sqft(0.0), 0.0        , 1.0e-6);
    EXPECT_NEAR(mc::Units::sqm2sqft(1.0), 10.7639104 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertSqFt2SqM)
{
    EXPECT_NEAR(mc::Units::sqft2sqm(0.0), 0.0        , 1.0e-9);
    EXPECT_NEAR(mc::Units::sqft2sqm(1.0), 0.09290304 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertCuFt2CuM)
{
    EXPECT_NEAR(mc::Units::cuft2cum(0.0), 0.0          , 1.0e-9);
    EXPECT_NEAR(mc::Units::cuft2cum(1.0), 0.0283168466 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertCuIn2CuM)
{
    EXPECT_NEAR(mc::Units::cuin2cum(0.0), 0.0          , 1.0e-9);
    EXPECT_NEAR(mc::Units::cuin2cum(1.0), 1.6387064e-5 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertCuM2CuFt)
{
    EXPECT_NEAR(mc::Units::cum2cuft(0.0), 0.0        , 1.0e-6);
    EXPECT_NEAR(mc::Units::cum2cuft(1.0), 35.3146667 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertL2CuM)
{
    EXPECT_NEAR(mc::Units::l2cum(0.0), 0.0   , 1.0e-9);
    EXPECT_NEAR(mc::Units::l2cum(1.0), 0.001 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMps2Fpm)
{
    EXPECT_NEAR(mc::Units::mps2fpm(0.0), 0.0        , 1.0e-9);
    EXPECT_NEAR(mc::Units::mps2fpm(1.0), 196.850394 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMps2Fps)
{
    EXPECT_NEAR(mc::Units::mps2fps(0.0), 0.0       , 1.0e-9);
    EXPECT_NEAR(mc::Units::mps2fps(1.0), 3.2808399 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMps2Kmh)
{
    EXPECT_NEAR(mc::Units::mps2kmh(0.0), 0.0, 1.0e-9);
    EXPECT_NEAR(mc::Units::mps2kmh(1.0), 3.6, 1.0e-9);
}

TEST_F(TestUnits, CanConvertMps2Kts)
{
    EXPECT_NEAR(mc::Units::mps2kts(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::mps2kts(1.0), 1.943844492 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMps2Mph)
{
    EXPECT_NEAR(mc::Units::mps2mph(0.0), 0.0        , 1.0e-9);
    EXPECT_NEAR(mc::Units::mps2mph(1.0), 2.23693629 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFpm2Fps)
{
    EXPECT_NEAR(mc::Units::fpm2fps(0.0), 0.0        , 1.0e-9);
    EXPECT_NEAR(mc::Units::fpm2fps(1.0), 1.0 / 60.0 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFpm2Kmh)
{
    EXPECT_NEAR(mc::Units::fpm2kmh(0.0), 0.0      , 1.0e-9);
    EXPECT_NEAR(mc::Units::fpm2kmh(1.0), 0.018288 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFpm2Kts)
{
    EXPECT_NEAR(mc::Units::fpm2kts(0.0), 0.0           , 1.0e-9);
    EXPECT_NEAR(mc::Units::fpm2kts(1.0), 0.00987473002 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFpm2Mph)
{
    EXPECT_NEAR(mc::Units::fpm2mph(0.0), 0.0          , 1.0e-9);
    EXPECT_NEAR(mc::Units::fpm2mph(1.0), 0.0113636364 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFpm2Mps)
{
    EXPECT_NEAR(mc::Units::fpm2mps(0.0), 0.0     , 1.0e-9);
    EXPECT_NEAR(mc::Units::fpm2mps(1.0), 0.00508 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFps2Fpm)
{
    EXPECT_NEAR(mc::Units::fps2fpm(0.0), 0.0  , 1.0e-9);
    EXPECT_NEAR(mc::Units::fps2fpm(1.0), 60.0 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFps2Kmh)
{
    EXPECT_NEAR(mc::Units::fps2kmh(0.0), 0.0     , 1.0e-9);
    EXPECT_NEAR(mc::Units::fps2kmh(1.0), 1.09728 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFps2Kts)
{
    EXPECT_NEAR(mc::Units::fps2kts(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::fps2kts(1.0), 0.592483801 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFps2Mph)
{
    EXPECT_NEAR(mc::Units::fps2mph(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::fps2mph(1.0), 0.681818182 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertFps2Mps)
{
    EXPECT_NEAR(mc::Units::fps2mps(0.0), 0.0    , 1.0e-9);
    EXPECT_NEAR(mc::Units::fps2mps(1.0), 0.3048 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKmh2Fpm)
{
    EXPECT_NEAR(mc::Units::kmh2fpm(0.0), 0.0        , 1.0e-9);
    EXPECT_NEAR(mc::Units::kmh2fpm(1.0), 54.6806649 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKmh2Fps)
{
    EXPECT_NEAR(mc::Units::kmh2fps(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::kmh2fps(1.0), 0.911344415 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKmh2Kts)
{
    EXPECT_NEAR(mc::Units::kmh2kts(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::kmh2kts(1.0), 0.539956803 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKmh2Mph)
{
    EXPECT_NEAR(mc::Units::kmh2mph(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::kmh2mph(1.0), 0.621371192 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKmh2Mps)
{
    EXPECT_NEAR(mc::Units::kmh2mps(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::kmh2mps(1.0), 0.277777778 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKts2Fpm)
{
    EXPECT_NEAR(mc::Units::kts2fpm(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::kts2fpm(1.0), 101.2685915 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKts2Fps)
{
    EXPECT_NEAR(mc::Units::kts2fps(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::kts2fps(1.0), 1.687809858 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKts2Kmh)
{
    EXPECT_NEAR(mc::Units::kts2kmh(0.0), 0.0   , 1.0e-9);
    EXPECT_NEAR(mc::Units::kts2kmh(1.0), 1.852 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKts2Mph)
{
    EXPECT_NEAR(mc::Units::kts2mph(0.0), 0.0        , 1.0e-9);
    EXPECT_NEAR(mc::Units::kts2mph(1.0), 1.15077945 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKts2Mps)
{
    EXPECT_NEAR(mc::Units::kts2mps(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::kts2mps(1.0), 0.514444444 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMph2Fpm)
{
    EXPECT_NEAR(mc::Units::mph2fpm(0.0), 0.0  , 1.0e-9);
    EXPECT_NEAR(mc::Units::mph2fpm(1.0), 88.0 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMph2Fps)
{
    EXPECT_NEAR(mc::Units::mph2fps(0.0), 0.0          , 1.0e-9);
    EXPECT_NEAR(mc::Units::mph2fps(1.0), 1.4666666667 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMph2Kmh)
{
    EXPECT_NEAR(mc::Units::mph2kmh(0.0), 0.0      , 1.0e-9);
    EXPECT_NEAR(mc::Units::mph2kmh(1.0), 1.609344 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMph2Kts)
{
    EXPECT_NEAR(mc::Units::mph2kts(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::mph2kts(1.0), 0.868976242 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMph2Mps)
{
    EXPECT_NEAR(mc::Units::mph2mps(0.0), 0.0     , 1.0e-9);
    EXPECT_NEAR(mc::Units::mph2mps(1.0), 0.44704 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertRpm2RadS)
{
    EXPECT_NEAR(mc::Units::rpm2rad_s(0.0)  , 0.0        , 1.0e-9);
    EXPECT_NEAR(mc::Units::rpm2rad_s(60.0) , 2.0 * M_PI , 1.0e-9);
}

TEST_F(TestUnits, CanConvertRadS2Rpm)
{
    EXPECT_NEAR(mc::Units::rad_s2rpm(0.0)        , 0.0  , 1.0e-9);
    EXPECT_NEAR(mc::Units::rad_s2rpm(2.0 * M_PI) , 60.0 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKg2Lb)
{
    EXPECT_NEAR(mc::Units::kg2lb(0.0), 0.0        , 1.0e-9);
    EXPECT_NEAR(mc::Units::kg2lb(1.0), 2.20462262 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertLb2Kg)
{
    EXPECT_NEAR(mc::Units::lb2kg(0.0), 0.0        , 1.0e-9);
    EXPECT_NEAR(mc::Units::lb2kg(1.0), 0.45359237 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertN2Lbf)
{
    EXPECT_NEAR(mc::Units::n2lbf(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::n2lbf(1.0), 0.224808943 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertLbf2N)
{
    // 1 lbf = 0.45359237 kg * 9.80665 m/s^2 = 4.448221615
    EXPECT_NEAR(mc::Units::lbf2n(0.0), 0.0         , 1.0e-9);
    EXPECT_NEAR(mc::Units::lbf2n(1.0), 4.448221615 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertPa2InHg)
{
    EXPECT_NEAR(mc::Units::pa2inhg(0.0)      , 0.0        , 1.0e-6);
    EXPECT_NEAR(mc::Units::pa2inhg(101325.0) , 29.9246899 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertPa2Mb)
{
    EXPECT_NEAR(mc::Units::pa2mb(0.0)      , 0.0     , 1.0e-9);
    EXPECT_NEAR(mc::Units::pa2mb(101325.0) , 1013.25 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertPa2Psf)
{
    EXPECT_NEAR(mc::Units::pa2psf(0.0)      , 0.0        , 1.0e-3);
    EXPECT_NEAR(mc::Units::pa2psf(101325.0) , 2116.21662 , 1.0e-3);
}

TEST_F(TestUnits, CanConvertPa2Psi)
{
    EXPECT_NEAR(mc::Units::pa2psi(0.0)      , 0.0        , 1.0e-6);
    EXPECT_NEAR(mc::Units::pa2psi(101325.0) , 14.6959488 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertPsf2Pa)
{
    EXPECT_NEAR(mc::Units::psf2pa(0.0)      , 0.0        , 1.0e-3);
    EXPECT_NEAR(mc::Units::psf2pa(2116.224) , 101325.353 , 1.0e-3);
}

TEST_F(TestUnits, CanConvertPsi2Pa)
{
    EXPECT_NEAR(mc::Units::psi2pa(0.0)    , 0.0        , 1.0e-3);
    EXPECT_NEAR(mc::Units::psi2pa(14.696) , 101325.353 , 1.0e-3);
}

TEST_F(TestUnits, CanConvertPsi2InHg)
{
    EXPECT_NEAR(mc::Units::psi2inhg(0.0)    , 0.0        , 1.0e-6);
    EXPECT_NEAR(mc::Units::psi2inhg(14.696) , 29.9247942 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertPsi2Mb)
{
    EXPECT_NEAR(mc::Units::psi2mb(0.0)    , 0.0        , 1.0e-5);
    EXPECT_NEAR(mc::Units::psi2mb(14.696) , 1013.25353 , 1.0e-5);
}

TEST_F(TestUnits, CanConvertInHg2Pa)
{
    EXPECT_NEAR(mc::Units::inhg2pa(0.0)     , 0.0        , 1.0e-3);
    EXPECT_NEAR(mc::Units::inhg2pa(29.9212) , 101313.183 , 1.0e-3);
}

TEST_F(TestUnits, CanConvertInHg2Psi)
{
    EXPECT_NEAR(mc::Units::inhg2psi(0.0)     , 0.0        , 1.0e-6);
    EXPECT_NEAR(mc::Units::inhg2psi(29.9212) , 14.6942349 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertInHg2Mb)
{
    EXPECT_NEAR(mc::Units::inhg2mb(0.0)     , 0.0        , 1.0e-5);
    EXPECT_NEAR(mc::Units::inhg2mb(29.9212) , 1013.13183 , 1.0e-5);
}

TEST_F(TestUnits, CanConvertMb2Pa)
{
    EXPECT_NEAR(mc::Units::mb2pa(0.0)     , 0.0      , 1.0e-9);
    EXPECT_NEAR(mc::Units::mb2pa(1013.25) , 101325.0 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertMb2Psi)
{
    EXPECT_NEAR(mc::Units::mb2psi(0.0)     , 0.0        , 1.0e-6);
    EXPECT_NEAR(mc::Units::mb2psi(1013.25) , 14.6959488 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertMb2InHg)
{
    EXPECT_NEAR(mc::Units::mb2inhg(0.0)     , 0.0        , 1.0e-6);
    EXPECT_NEAR(mc::Units::mb2inhg(1013.25) , 29.9246899 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertPs2Hp)
{
    EXPECT_NEAR(mc::Units::ps2hp(0.0), 0.0          , 1.0e-6);
    EXPECT_NEAR(mc::Units::ps2hp(1.0), 0.9863200706 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertPs2W)
{
    EXPECT_NEAR(mc::Units::ps2w(0.0), 0.0       , 1.0e-3);
    EXPECT_NEAR(mc::Units::ps2w(1.0), 735.49875 , 1.0e-3);
}

TEST_F(TestUnits, CanConvertPs2KW)
{
    EXPECT_NEAR(mc::Units::ps2kw(0.0), 0.0        , 1.0e-6);
    EXPECT_NEAR(mc::Units::ps2kw(1.0), 0.73549875 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertHp2Ps)
{
    EXPECT_NEAR(mc::Units::hp2ps(0.0), 0.0        , 1.0e-6);
    EXPECT_NEAR(mc::Units::hp2ps(1.0), 1.01386967 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertHp2W)
{
    EXPECT_NEAR(mc::Units::hp2w(0.0), 0.0   , 1.0e-1);
    EXPECT_NEAR(mc::Units::hp2w(1.0), 745.7 , 1.0e-1);
}

TEST_F(TestUnits, CanConvertHp2KW)
{
    EXPECT_NEAR(mc::Units::hp2kw(0.0), 0.0    , 1.0e-4);
    EXPECT_NEAR(mc::Units::hp2kw(1.0), 0.7457 , 1.0e-4);
}

TEST_F(TestUnits, CanConvertW2Ps)
{
    EXPECT_NEAR(mc::Units::w2ps(0.0), 0.0           , 1.0e-9);
    EXPECT_NEAR(mc::Units::w2ps(1.0), 0.00135962162 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertW2Hp)
{
    EXPECT_NEAR(mc::Units::w2hp(0.0), 0.0           , 1.0e-9);
    EXPECT_NEAR(mc::Units::w2hp(1.0), 0.00134102209 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertW2KW)
{
    EXPECT_NEAR(mc::Units::w2kw(0.0), 0.0   , 1.0e-9);
    EXPECT_NEAR(mc::Units::w2kw(1.0), 0.001 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertKW2Ps)
{
    EXPECT_NEAR(mc::Units::kw2ps(0.0), 0.0        , 1.0e-6);
    EXPECT_NEAR(mc::Units::kw2ps(1.0), 1.35962162 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertKW2Hp)
{
    EXPECT_NEAR(mc::Units::kw2hp(0.0), 0.0        , 1.0e-6);
    EXPECT_NEAR(mc::Units::kw2hp(1.0), 1.34102209 , 1.0e-6);
}

TEST_F(TestUnits, CanConvertKW2W)
{
    EXPECT_NEAR(mc::Units::kw2w(0.0), 0.0    , 1.0e-9);
    EXPECT_NEAR(mc::Units::kw2w(1.0), 1000.0 , 1.0e-9);
}

TEST_F(TestUnits, CanConvertDegC2DegF)
{
    EXPECT_NEAR(mc::Units::c2f(0.0)  , 32.0, 1.0e-9);
    EXPECT_NEAR(mc::Units::c2f(15.0) , 59.0, 1.0e-9);
}

TEST_F(TestUnits, CanConvertDegC2K)
{
    EXPECT_NEAR(mc::Units::c2k(0.0)  , 273.15, 1.0e-9);
    EXPECT_NEAR(mc::Units::c2k(15.0) , 288.15, 1.0e-9);
}

TEST_F(TestUnits, CanConvertDegF2DegC)
{
    EXPECT_NEAR(mc::Units::f2c(  0.0), -17.7777778, 1.0e-6);
    EXPECT_NEAR(mc::Units::f2c(100.0),  37.7777778, 1.0e-6);
}

TEST_F(TestUnits, CanConvertDegF2K)
{
    EXPECT_NEAR(mc::Units::f2k(  0.0), 255.372222, 1.0e-6);
    EXPECT_NEAR(mc::Units::f2k(100.0), 310.927778, 1.0e-6);
}

TEST_F(TestUnits, CanConvertK2DegC)
{
    EXPECT_NEAR(mc::Units::k2c(273.15),  0.0, 1.0e-9);
    EXPECT_NEAR(mc::Units::k2c(288.15), 15.0, 1.0e-9);
}

TEST_F(TestUnits, CanConvertK2DegF)
{
    EXPECT_NEAR(mc::Units::k2f(273.15), 32.0, 1.0e-9);
    EXPECT_NEAR(mc::Units::k2f(288.15), 59.0, 1.0e-9);
}

TEST_F(TestUnits, CanConvertGkWh2KgWs)
{
    EXPECT_NEAR(mc::Units::g_kWh_2_kg_Ws(0.0), 0.0            , 1.0e-17);
    EXPECT_NEAR(mc::Units::g_kWh_2_kg_Ws(1.0), 2.77777778e-10 , 1.0e-17);
}

TEST_F(TestUnits, CanConvertGkNs2KgNs)
{
    EXPECT_NEAR(mc::Units::g_kNs_2_kg_Ns(0.0), 0.0    , 1.0e-9);
    EXPECT_NEAR(mc::Units::g_kNs_2_kg_Ns(1.0), 1.0e-6 , 1.0e-9);
}
