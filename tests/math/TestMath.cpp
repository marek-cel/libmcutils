#include <gtest/gtest.h>

#include <units.h>

#include <mcutils/math/Math.h>

using namespace units::literals;

class TestMath : public ::testing::Test
{
protected:
    TestMath() {}
    virtual ~TestMath() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMath, CanCalculatePow)
{
    EXPECT_DOUBLE_EQ(mc::Pow<0>(0.0), 1.0);
    EXPECT_DOUBLE_EQ(mc::Pow<0>(1.0), 1.0);
    EXPECT_DOUBLE_EQ(mc::Pow<0>(2.0), 1.0);
    EXPECT_DOUBLE_EQ(mc::Pow<0>(3.0), 1.0);

    EXPECT_DOUBLE_EQ(mc::Pow<2>(0.0), 0.0);
    EXPECT_DOUBLE_EQ(mc::Pow<2>(1.0), 1.0);
    EXPECT_DOUBLE_EQ(mc::Pow<2>(2.0), 4.0);
    EXPECT_DOUBLE_EQ(mc::Pow<2>(3.0), 9.0);

    EXPECT_DOUBLE_EQ(mc::Pow<3>(0.0),  0.0);
    EXPECT_DOUBLE_EQ(mc::Pow<3>(1.0),  1.0);
    EXPECT_DOUBLE_EQ(mc::Pow<3>(2.0),  8.0);
    EXPECT_DOUBLE_EQ(mc::Pow<3>(3.0), 27.0);

    EXPECT_DOUBLE_EQ(mc::Pow<4>(0.0),  0.0);
    EXPECT_DOUBLE_EQ(mc::Pow<4>(1.0),  1.0);
    EXPECT_DOUBLE_EQ(mc::Pow<4>(2.0), 16.0);
    EXPECT_DOUBLE_EQ(mc::Pow<4>(3.0), 81.0);
}

TEST_F(TestMath, CanCalculatePowWithUnits)
{
    EXPECT_DOUBLE_EQ(mc::Pow<0>(0.0_m), 1.0);
    EXPECT_DOUBLE_EQ(mc::Pow<0>(1.0_m), 1.0);
    EXPECT_DOUBLE_EQ(mc::Pow<0>(2.0_m), 1.0);
    EXPECT_DOUBLE_EQ(mc::Pow<0>(3.0_m), 1.0);

    EXPECT_DOUBLE_EQ(mc::Pow<2>(0.0_m)(), 0.0);
    EXPECT_DOUBLE_EQ(mc::Pow<2>(1.0_m)(), 1.0);
    EXPECT_DOUBLE_EQ(mc::Pow<2>(2.0_m)(), 4.0);
    EXPECT_DOUBLE_EQ(mc::Pow<2>(3.0_m)(), 9.0);

    EXPECT_DOUBLE_EQ(mc::Pow<3>(0.0_m)(),  0.0);
    EXPECT_DOUBLE_EQ(mc::Pow<3>(1.0_m)(),  1.0);
    EXPECT_DOUBLE_EQ(mc::Pow<3>(2.0_m)(),  8.0);
    EXPECT_DOUBLE_EQ(mc::Pow<3>(3.0_m)(), 27.0);

    EXPECT_DOUBLE_EQ(mc::Pow<4>(0.0_m)(),  0.0);
    EXPECT_DOUBLE_EQ(mc::Pow<4>(1.0_m)(),  1.0);
    EXPECT_DOUBLE_EQ(mc::Pow<4>(2.0_m)(), 16.0);
    EXPECT_DOUBLE_EQ(mc::Pow<4>(3.0_m)(), 81.0);
}

TEST_F(TestMath, CanDetermineIfIsInside)
{
    EXPECT_TRUE(mc::IsInside(0.0, 1.0,  0.0));
    EXPECT_TRUE(mc::IsInside(0.0, 1.0,  0.1));
    EXPECT_TRUE(mc::IsInside(0.0, 1.0,  0.5));
    EXPECT_TRUE(mc::IsInside(0.0, 1.0,  0.9));
    EXPECT_TRUE(mc::IsInside(0.0, 1.0,  1.0));

    EXPECT_FALSE(mc::IsInside(0.0, 1.0, -2.0));
    EXPECT_FALSE(mc::IsInside(0.0, 1.0,  2.0));
}

TEST_F(TestMath, CanDetermineIfIsOutside)
{
    EXPECT_FALSE(mc::IsOutside(0.0, 1.0,  0.0));
    EXPECT_FALSE(mc::IsOutside(0.0, 1.0,  0.1));
    EXPECT_FALSE(mc::IsOutside(0.0, 1.0,  0.5));
    EXPECT_FALSE(mc::IsOutside(0.0, 1.0,  0.9));
    EXPECT_FALSE(mc::IsOutside(0.0, 1.0,  1.0));

    EXPECT_TRUE(mc::IsOutside(0.0, 1.0, -2.0));
    EXPECT_TRUE(mc::IsOutside(0.0, 1.0,  2.0));
}

TEST_F(TestMath, CanCalculateSign)
{
    EXPECT_DOUBLE_EQ(mc::Sign( -2.0 ), -1.0);
    EXPECT_DOUBLE_EQ(mc::Sign( -1.0 ), -1.0);
    EXPECT_DOUBLE_EQ(mc::Sign( -0.1 ), -1.0);
    EXPECT_DOUBLE_EQ(mc::Sign(  0.0 ),  0.0);
    EXPECT_DOUBLE_EQ(mc::Sign(  0.1 ),  1.0);
    EXPECT_DOUBLE_EQ(mc::Sign(  1.0 ),  1.0);
    EXPECT_DOUBLE_EQ(mc::Sign(  2.0 ),  1.0);
}

TEST_F(TestMath, CanSaturate)
{
    EXPECT_DOUBLE_EQ(mc::Satur(  0.0, 1.0, -2.0 ),  0.0);
    EXPECT_DOUBLE_EQ(mc::Satur(  0.0, 1.0, -0.1 ),  0.0);
    EXPECT_DOUBLE_EQ(mc::Satur(  0.0, 1.0,  0.0 ),  0.0);
    EXPECT_DOUBLE_EQ(mc::Satur(  0.0, 1.0,  0.1 ),  0.1);
    EXPECT_DOUBLE_EQ(mc::Satur(  0.0, 1.0,  0.5 ),  0.5);
    EXPECT_DOUBLE_EQ(mc::Satur(  0.0, 1.0,  0.9 ),  0.9);
    EXPECT_DOUBLE_EQ(mc::Satur(  0.0, 1.0,  1.0 ),  1.0);
    EXPECT_DOUBLE_EQ(mc::Satur(  0.0, 1.0,  1.1 ),  1.0);
    EXPECT_DOUBLE_EQ(mc::Satur(  0.0, 1.0,  2.0 ),  1.0);

    EXPECT_DOUBLE_EQ(mc::Satur( -1.0, 1.0, -2.0 ), -1.0);
    EXPECT_DOUBLE_EQ(mc::Satur( -1.0, 1.0, -1.5 ), -1.0);
    EXPECT_DOUBLE_EQ(mc::Satur( -1.0, 1.0, -1.0 ), -1.0);
    EXPECT_DOUBLE_EQ(mc::Satur( -1.0, 1.0, -0.5 ), -0.5);
    EXPECT_DOUBLE_EQ(mc::Satur( -1.0, 1.0,  0.0 ),  0.0);
    EXPECT_DOUBLE_EQ(mc::Satur( -1.0, 1.0,  0.5 ),  0.5);
    EXPECT_DOUBLE_EQ(mc::Satur( -1.0, 1.0,  1.0 ),  1.0);
    EXPECT_DOUBLE_EQ(mc::Satur( -1.0, 1.0,  1.5 ),  1.0);
    EXPECT_DOUBLE_EQ(mc::Satur( -1.0, 1.0,  2.0 ),  1.0);
}

TEST_F(TestMath, CanCalculateSineWave)
{
    float x = -1.0;

    while ( x <= 1.0 + 1.0e-3 )
    {
        float y_test = mc::SineWave(x);
        float y_sin  = sin(M_PI * x);

        EXPECT_NEAR(y_test, y_sin, 1.0e-3);

        x += 0.1f;
    }
}

TEST_F(TestMath, CanCalculateSmoothstep1Arg)
{
    EXPECT_DOUBLE_EQ(mc::Smoothstep( 0.0 ), 0.0);
    EXPECT_DOUBLE_EQ(mc::Smoothstep( 0.5 ), 0.5);
    EXPECT_DOUBLE_EQ(mc::Smoothstep( 1.0 ), 1.0);

    EXPECT_GE(mc::Smoothstep( 0.25 ), 0.0);
    EXPECT_LT(mc::Smoothstep( 0.25 ), 0.5);

    EXPECT_GE(mc::Smoothstep( 0.75 ), 0.5);
    EXPECT_LT(mc::Smoothstep( 0.75 ), 1.0);

    EXPECT_DOUBLE_EQ(mc::Smoothstep( -1.0 ), 0.0);
    EXPECT_DOUBLE_EQ(mc::Smoothstep(  2.0 ), 1.0);
}

TEST_F(TestMath, CanCalculateSmoothstep3Args)
{
    EXPECT_DOUBLE_EQ(mc::Smoothstep( -1.0, 1.0, -1.0 ), 0.0);
    EXPECT_DOUBLE_EQ(mc::Smoothstep( -1.0, 1.0,  0.0 ), 0.5);
    EXPECT_DOUBLE_EQ(mc::Smoothstep( -1.0, 1.0,  1.0 ), 1.0);

    EXPECT_GE(mc::Smoothstep( -1.0, 1.0, -0.5 ), 0.0);
    EXPECT_LT(mc::Smoothstep( -1.0, 1.0, -0.5 ), 0.5);

    EXPECT_GE(mc::Smoothstep( -1.0, 1.0,  0.5 ), 0.5);
    EXPECT_LT(mc::Smoothstep( -1.0, 1.0,  0.5 ), 1.0);

    EXPECT_DOUBLE_EQ(mc::Smoothstep( -1.0, 1.0, -2.0 ), 0.0);
    EXPECT_DOUBLE_EQ(mc::Smoothstep( -1.0, 1.0,  2.0 ), 1.0);
}

TEST_F(TestMath, CanCalculateSmoothstep5Args)
{
    EXPECT_DOUBLE_EQ(mc::Smoothstep( -1.0, 1.0, -5.0, 5.0, -1.0 ), -5.0);
    EXPECT_DOUBLE_EQ(mc::Smoothstep( -1.0, 1.0, -5.0, 5.0,  0.0 ),  0.0);
    EXPECT_DOUBLE_EQ(mc::Smoothstep( -1.0, 1.0, -5.0, 5.0,  1.0 ),  5.0);

    EXPECT_GE(mc::Smoothstep( -1.0, 1.0, -5.0, 5.0, -0.5 ), -5.0);
    EXPECT_LT(mc::Smoothstep( -1.0, 1.0, -5.0, 5.0, -0.5 ),  0.0);

    EXPECT_GE(mc::Smoothstep( -1.0, 1.0, -5.0, 5.0,  0.5 ), 0.0);
    EXPECT_LT(mc::Smoothstep( -1.0, 1.0, -5.0, 5.0,  0.5 ), 5.0);

    EXPECT_DOUBLE_EQ(mc::Smoothstep( -1.0, 1.0, -5.0, 5.0, -2.0 ), -5.0);
    EXPECT_DOUBLE_EQ(mc::Smoothstep( -1.0, 1.0, -5.0, 5.0,  2.0 ),  5.0);
}

TEST_F(TestMath, CanCalculateStandardDeviation)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_math_stat.m

    double x1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    double x2[] { 26.0, 20.0, 50.0, 19.0, 61.0, 51.0, 91.0, 28.0, 38.0 };

    double sd1 = mc::StdDev(x1, 9);
    double sd2 = mc::StdDev(x2, 9);

    EXPECT_NEAR(sd1,  2.738613, 1.0e-5);
    EXPECT_NEAR(sd2, 23.409400, 1.0e-5);
}
