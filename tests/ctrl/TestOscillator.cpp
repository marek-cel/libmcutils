#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/Oscillator.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestOscillator : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP { 0.01 };
    static constexpr double OMEGA     { 2.0 };
    static constexpr double ZETA      { 1.0/50.0 };

    TestOscillator() {}
    virtual ~TestOscillator() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestOscillator, CanConstruct)
{
    mc::Oscillator *oscillator = nullptr;
    EXPECT_NO_THROW( oscillator = new mc::Oscillator() );
    delete oscillator;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestOscillator, CanDestruct)
{
    mc::Oscillator *oscillator = new mc::Oscillator();
    EXPECT_NO_THROW( delete oscillator );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestOscillator, CanInstantiate)
{
    mc::Oscillator oscillator;

    EXPECT_DOUBLE_EQ( oscillator.getOmega(), 1.0 );
    EXPECT_DOUBLE_EQ( oscillator.getOmega(), 1.0 );
    EXPECT_DOUBLE_EQ( oscillator.getValue(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestOscillator, CanInstantiateAndSetData)
{
    mc::Oscillator oscillator( 2.0, 3.0, 4.0 );

    EXPECT_DOUBLE_EQ( oscillator.getOmega()   , 2.0 );
    EXPECT_DOUBLE_EQ( oscillator.getDamping() , 3.0 );
    EXPECT_DOUBLE_EQ( oscillator.getValue()   , 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestOscillator, CanGetOmega)
{
    mc::Oscillator oscillator( 2.0, 3.0, 4.0 );
    EXPECT_DOUBLE_EQ( oscillator.getOmega(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestOscillator, CanGetValue)
{
    mc::Oscillator oscillator( 2.0, 3.0, 4.0 );
    EXPECT_DOUBLE_EQ( oscillator.getValue(), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestOscillator, CanSetOmega)
{
    mc::Oscillator oscillator;

    oscillator.setOmega( 2.0 );
    EXPECT_DOUBLE_EQ( oscillator.getOmega(), 2.0 );

    oscillator.setOmega( -1.0 );
    EXPECT_DOUBLE_EQ( oscillator.getOmega(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestOscillator, CanSetDamping)
{
    mc::Oscillator oscillator;

    oscillator.setDamping( 2.0 );
    EXPECT_DOUBLE_EQ( oscillator.getDamping(), 1.0 );

    oscillator.setDamping( -1.0 );
    EXPECT_DOUBLE_EQ( oscillator.getDamping(), 0.0 );

    oscillator.setDamping( 0.5 );
    EXPECT_DOUBLE_EQ( oscillator.getDamping(), 0.5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestOscillator, CanSetValue)
{
    mc::Oscillator oscillator;
    oscillator.setValue( 3.0 );
    EXPECT_DOUBLE_EQ( oscillator.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestOscillator, CanUpdateStep)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_oscillator.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_oscillator_step.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::Oscillator oscillator( OMEGA, ZETA );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 100 ) ? 0.0 : 1.0;

        oscillator.update( TIME_STEP, u );
        y = oscillator.getValue();

        double tolerance = std::max( 1.0e-2, 1.0e-2 * vals.at( i ) );
        EXPECT_NEAR( y, vals.at( i ), tolerance ) << "Error at index " << i;

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestOscillator, CanUpdateSine)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_oscillator.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_oscillator_sine.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::Oscillator oscillator( OMEGA, ZETA );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = sin( t );

        oscillator.update( TIME_STEP, u );
        y = oscillator.getValue();

        double tolerance = std::max( 1.0e-2, 1.0e-2 * vals.at( i ) );
        EXPECT_NEAR( y, vals.at( i ), tolerance ) << "Error at index " << i;

        t += TIME_STEP;
    }
}
