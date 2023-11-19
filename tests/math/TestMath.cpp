#include <gtest/gtest.h>

#include <mcutils/math/Math.h>

////////////////////////////////////////////////////////////////////////////////

class TestMath : public ::testing::Test
{
protected:
    TestMath() {}
    virtual ~TestMath() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMath, CanCalculatePow2)
{
    EXPECT_DOUBLE_EQ(mc::Math::Pow2(0.0), 0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Pow2(1.0), 1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Pow2(2.0), 4.0);
    EXPECT_DOUBLE_EQ(mc::Math::Pow2(3.0), 9.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMath, CanCalculatePow3)
{
    EXPECT_DOUBLE_EQ(mc::Math::Pow3(0.0),  0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Pow3(1.0),  1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Pow3(2.0),  8.0);
    EXPECT_DOUBLE_EQ(mc::Math::Pow3(3.0), 27.0);
}

//////////////////////////////////////////////

TEST_F(TestMath, CanCalculatePow4)
{
    EXPECT_DOUBLE_EQ(mc::Math::Pow4(0.0),  0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Pow4(1.0),  1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Pow4(2.0), 16.0);
    EXPECT_DOUBLE_EQ(mc::Math::Pow4(3.0), 81.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMath, CanCalculatePow5)
{
    EXPECT_DOUBLE_EQ(mc::Math::Pow5(0.0),   0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Pow5(1.0),   1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Pow5(2.0),  32.0);
    EXPECT_DOUBLE_EQ(mc::Math::Pow5(3.0), 243.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMath, CanDetermineIfIsInside)
{
    EXPECT_TRUE(mc::Math::IsInside(0.0, 1.0,  0.0));
    EXPECT_TRUE(mc::Math::IsInside(0.0, 1.0,  0.1));
    EXPECT_TRUE(mc::Math::IsInside(0.0, 1.0,  0.5));
    EXPECT_TRUE(mc::Math::IsInside(0.0, 1.0,  0.9));
    EXPECT_TRUE(mc::Math::IsInside(0.0, 1.0,  1.0));

    EXPECT_FALSE(mc::Math::IsInside(0.0, 1.0, -2.0));
    EXPECT_FALSE(mc::Math::IsInside(0.0, 1.0,  2.0));
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMath, CanDetermineIfIsOutside)
{
    EXPECT_FALSE(mc::Math::IsOutside(0.0, 1.0,  0.0));
    EXPECT_FALSE(mc::Math::IsOutside(0.0, 1.0,  0.1));
    EXPECT_FALSE(mc::Math::IsOutside(0.0, 1.0,  0.5));
    EXPECT_FALSE(mc::Math::IsOutside(0.0, 1.0,  0.9));
    EXPECT_FALSE(mc::Math::IsOutside(0.0, 1.0,  1.0));

    EXPECT_TRUE(mc::Math::IsOutside(0.0, 1.0, -2.0));
    EXPECT_TRUE(mc::Math::IsOutside(0.0, 1.0,  2.0));
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMath, CanCalculateSign)
{
    EXPECT_DOUBLE_EQ(mc::Math::Sign( -2.0 ), -1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Sign( -1.0 ), -1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Sign( -0.1 ), -1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Sign(  0.0 ),  0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Sign(  0.1 ),  1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Sign(  1.0 ),  1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Sign(  2.0 ),  1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMath, CanSaturate)
{
    EXPECT_DOUBLE_EQ(mc::Math::Satur(  0.0, 1.0, -2.0 ),  0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Satur(  0.0, 1.0, -0.1 ),  0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Satur(  0.0, 1.0,  0.0 ),  0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Satur(  0.0, 1.0,  0.1 ),  0.1);
    EXPECT_DOUBLE_EQ(mc::Math::Satur(  0.0, 1.0,  0.5 ),  0.5);
    EXPECT_DOUBLE_EQ(mc::Math::Satur(  0.0, 1.0,  0.9 ),  0.9);
    EXPECT_DOUBLE_EQ(mc::Math::Satur(  0.0, 1.0,  1.0 ),  1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Satur(  0.0, 1.0,  1.1 ),  1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Satur(  0.0, 1.0,  2.0 ),  1.0);

    EXPECT_DOUBLE_EQ(mc::Math::Satur( -1.0, 1.0, -2.0 ), -1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Satur( -1.0, 1.0, -1.5 ), -1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Satur( -1.0, 1.0, -1.0 ), -1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Satur( -1.0, 1.0, -0.5 ), -0.5);
    EXPECT_DOUBLE_EQ(mc::Math::Satur( -1.0, 1.0,  0.0 ),  0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Satur( -1.0, 1.0,  0.5 ),  0.5);
    EXPECT_DOUBLE_EQ(mc::Math::Satur( -1.0, 1.0,  1.0 ),  1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Satur( -1.0, 1.0,  1.5 ),  1.0);
    EXPECT_DOUBLE_EQ(mc::Math::Satur( -1.0, 1.0,  2.0 ),  1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMath, CanCalculateSineWave)
{
    float x = -1.0;

    while ( x <= 1.0 + 1.0e-3 )
    {
        float y_test = mc::Math::SineWave(x);
        float y_sin  = sin(M_PI * x);

        EXPECT_NEAR(y_test, y_sin, 1.0e-3);

        x += 0.1f;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMath, CanCalculateSmoothstep1Arg)
{
    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( 0.0 ), 0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( 0.5 ), 0.5);
    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( 1.0 ), 1.0);

    EXPECT_GE(mc::Math::Smoothstep( 0.25 ), 0.0);
    EXPECT_LT(mc::Math::Smoothstep( 0.25 ), 0.5);

    EXPECT_GE(mc::Math::Smoothstep( 0.75 ), 0.5);
    EXPECT_LT(mc::Math::Smoothstep( 0.75 ), 1.0);

    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( -1.0 ), 0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep(  2.0 ), 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMath, CanCalculateSmoothstep3Args)
{
    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( -1.0, 1.0, -1.0 ), 0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( -1.0, 1.0,  0.0 ), 0.5);
    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( -1.0, 1.0,  1.0 ), 1.0);

    EXPECT_GE(mc::Math::Smoothstep( -1.0, 1.0, -0.5 ), 0.0);
    EXPECT_LT(mc::Math::Smoothstep( -1.0, 1.0, -0.5 ), 0.5);

    EXPECT_GE(mc::Math::Smoothstep( -1.0, 1.0,  0.5 ), 0.5);
    EXPECT_LT(mc::Math::Smoothstep( -1.0, 1.0,  0.5 ), 1.0);

    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( -1.0, 1.0, -2.0 ), 0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( -1.0, 1.0,  2.0 ), 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMath, CanCalculateSmoothstep5Args)
{
    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( -1.0, 1.0, -5.0, 5.0, -1.0 ), -5.0);
    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( -1.0, 1.0, -5.0, 5.0,  0.0 ),  0.0);
    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( -1.0, 1.0, -5.0, 5.0,  1.0 ),  5.0);

    EXPECT_GE(mc::Math::Smoothstep( -1.0, 1.0, -5.0, 5.0, -0.5 ), -5.0);
    EXPECT_LT(mc::Math::Smoothstep( -1.0, 1.0, -5.0, 5.0, -0.5 ),  0.0);

    EXPECT_GE(mc::Math::Smoothstep( -1.0, 1.0, -5.0, 5.0,  0.5 ), 0.0);
    EXPECT_LT(mc::Math::Smoothstep( -1.0, 1.0, -5.0, 5.0,  0.5 ), 5.0);

    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( -1.0, 1.0, -5.0, 5.0, -2.0 ), -5.0);
    EXPECT_DOUBLE_EQ(mc::Math::Smoothstep( -1.0, 1.0, -5.0, 5.0,  2.0 ),  5.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMath, CanCalculateStandardDeviation)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_math_stat.m

    double x1[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    double x2[] { 26.0, 20.0, 50.0, 19.0, 61.0, 51.0, 91.0, 28.0, 38.0 };

    double sd1 = mc::Math::StdDev(x1, 9);
    double sd2 = mc::Math::StdDev(x2, 9);

    EXPECT_NEAR(sd1,  2.738613, 1.0e-5);
    EXPECT_NEAR(sd2, 23.409400, 1.0e-5);
}
