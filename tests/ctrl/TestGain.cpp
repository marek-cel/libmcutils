#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/Gain.h>

////////////////////////////////////////////////////////////////////////////////

class TestGain : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP { 0.01 };
    static constexpr double GAIN      { 2.0  };

    TestGain() {}
    virtual ~TestGain() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGain, CanConstruct)
{
    mc::Gain *gain = nullptr;
    EXPECT_NO_THROW( gain = new mc::Gain() );
    delete gain;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGain, CanDestruct)
{
    mc::Gain *gain = new mc::Gain();
    EXPECT_NO_THROW( delete gain );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGain, CanInstantiate)
{
    mc::Gain gain;
    EXPECT_DOUBLE_EQ( gain.getGain(), 1.0 );
    EXPECT_DOUBLE_EQ( gain.getValue(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGain, CanInstantiateAndSetData)
{
    mc::Gain gain( 2.0, 3.0 );
    EXPECT_DOUBLE_EQ( gain.getGain(), 2.0 );
    EXPECT_DOUBLE_EQ( gain.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGain, CanGetValue)
{
    mc::Gain gain( 2.0, 3.0 );
    EXPECT_DOUBLE_EQ( gain.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGain, CanSetValue)
{
    mc::Gain gain;
    gain.setValue( 1.0 );
    EXPECT_DOUBLE_EQ( gain.getValue(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGain, CanGetGain)
{
    mc::Gain gain( 2.0 );
    EXPECT_DOUBLE_EQ( gain.getGain(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGain, CanSetGain)
{
    mc::Gain gain;
    gain.setGain( 2.0 );
    EXPECT_DOUBLE_EQ( gain.getGain(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGain, CanUpdateStep)
{
    mc::Gain gain( GAIN );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < 300; i++ )
    {
        double u = ( i < 101 ) ? 0.0 : 1.0;

        gain.update( TIME_STEP, u );
        y = gain.getValue();

        double tolerance = 1.0e-3;
        EXPECT_NEAR( y, GAIN * u, tolerance ) << "Error at index " << i;

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGain, CanUpdateSine)
{
    mc::Gain gain( GAIN );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < 300; i++ )
    {
        double u = sin( t + TIME_STEP );

        gain.update( TIME_STEP, u );
        y = gain.getValue();

        double tolerance = 1.0e-3;
        EXPECT_NEAR( y, GAIN * u, tolerance ) << "Error at index " << i;

        t += TIME_STEP;
    }
}
