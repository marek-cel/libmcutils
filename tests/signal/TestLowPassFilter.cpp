#include <gtest/gtest.h>

#include <cmath>

#include <mcutil/signal/LowPassFilter.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestLowPassFilter : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP { 0.1 };
    static constexpr double OMEGA     { 0.5 };

    TestLowPassFilter() {}
    virtual ~TestLowPassFilter() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLowPassFilter, CanConstruct)
{
    mc::LowPassFilter *lpf = nullptr;
    EXPECT_NO_THROW( lpf = new mc::LowPassFilter() );
    delete lpf;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLowPassFilter, CanDestruct)
{
    mc::LowPassFilter *lpf = new mc::LowPassFilter();
    EXPECT_NO_THROW( delete lpf );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLowPassFilter, CanInstantiate)
{
    mc::LowPassFilter lpf;

    EXPECT_DOUBLE_EQ( lpf.getOmega(), 1.0 );
    EXPECT_DOUBLE_EQ( lpf.getValue(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLowPassFilter, CanInstantiateAndSetData)
{
    mc::LowPassFilter lpf( 2.0, 3.0 );

    EXPECT_DOUBLE_EQ( lpf.getOmega(), 2.0 );
    EXPECT_DOUBLE_EQ( lpf.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLowPassFilter, CanGetOmega)
{
    mc::LowPassFilter lpf( 2.0, 3.0 );
    EXPECT_DOUBLE_EQ( lpf.getOmega(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLowPassFilter, CanGetValue)
{
    mc::LowPassFilter lpf( 2.0, 3.0 );
    EXPECT_DOUBLE_EQ( lpf.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLowPassFilter, CanSetOmega)
{
    mc::LowPassFilter lpf;
    lpf.setOmega( 2.0 );
    EXPECT_DOUBLE_EQ( lpf.getOmega(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLowPassFilter, CanSetValue)
{
    mc::LowPassFilter lpf;
    lpf.setValue( 3.0 );
    EXPECT_DOUBLE_EQ( lpf.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLowPassFilter, CanSetCutoffFreq)
{
    mc::LowPassFilter lpf;
    lpf.setCutoffFreq( 1.0 );
    EXPECT_DOUBLE_EQ( lpf.getOmega(), 2.0 * M_PI );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLowPassFilter, CanUpdate1)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/signal/xcos/test_lowpassfilter.xcos
    XcosBinFileReader::readData( "../tests/signal/data/test_lowpassfilter.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::LowPassFilter lpf( OMEGA );

    double t = 0.0;
    double y = 0.0;

    int devider = 10;
    int index = 0;
    double dt = TIME_STEP / (double)devider;

    for ( unsigned int i = 0; i < devider * vals.size(); i++ )
    {
        double u = ( t < 0.99 ) ? 0.0 : 1.0;

        lpf.update( dt, u );
        y = lpf.getValue();

        if ( i % devider == 0 )
        {
            if ( index > 0 )
            {
                EXPECT_NEAR( y, vals.at( index - 1 ), 1.0e-2 );
            }

            index++;
        }

        t += dt;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLowPassFilter, CanUpdate2)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/signal/xcos/test_lowpassfilter_2.xcos
    XcosBinFileReader::readData( "../tests/signal/data/test_lowpassfilter_2.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::LowPassFilter lpf( OMEGA );

    double t = 0.0;
    double y = 0.0;

    int devider = 10;
    int index = 0;
    double dt = TIME_STEP / (double)devider;

    for ( unsigned int i = 0; i < devider * vals.size(); i++ )
    {
        double u = sin( t );

        lpf.update( dt, u );
        y = lpf.getValue();

        if ( i % devider == 0 )
        {
            if ( index > 0 )
            {
                EXPECT_NEAR( y, vals.at( index - 1 ), 1.0e-2 );
            }

            index++;
        }

        t += dt;
    }
}
