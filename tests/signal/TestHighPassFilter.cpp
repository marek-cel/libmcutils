#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/signal/HighPassFilter.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestHighPassFilter : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP { 0.1 };

    static constexpr double OMEGA { 2.0 };

    TestHighPassFilter() {}
    virtual ~TestHighPassFilter() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestHighPassFilter, CanConstruct)
{
    mc::HighPassFilter *hpf = nullptr;
    EXPECT_NO_THROW( hpf = new mc::HighPassFilter() );
    delete hpf;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestHighPassFilter, CanDestruct)
{
    mc::HighPassFilter *hpf = new mc::HighPassFilter();
    EXPECT_NO_THROW( delete hpf );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestHighPassFilter, CanInstantiate)
{
    mc::HighPassFilter hpf;
    EXPECT_DOUBLE_EQ( hpf.getOmega(), 1.0 );
    EXPECT_DOUBLE_EQ( hpf.getValue(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestHighPassFilter, CanInstantiateAndSetData)
{
    mc::HighPassFilter hpf( 2.0, 3.0 );
    EXPECT_DOUBLE_EQ( hpf.getOmega(), 2.0 );
    EXPECT_DOUBLE_EQ( hpf.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestHighPassFilter, CanGetOmega)
{
    mc::HighPassFilter hpf( 2.0, 3.0 );
    EXPECT_DOUBLE_EQ( hpf.getOmega(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestHighPassFilter, CanGetValue)
{
    mc::HighPassFilter hpf( 2.0, 3.0 );
    EXPECT_DOUBLE_EQ( hpf.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestHighPassFilter, CanSetOmega)
{
    mc::HighPassFilter hpf;
    hpf.setOmega( 2.0 );
    EXPECT_DOUBLE_EQ( hpf.getOmega(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestHighPassFilter, CanSetValue)
{
    mc::HighPassFilter hpf;
    hpf.setValue( 3.0 );
    EXPECT_DOUBLE_EQ( hpf.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestHighPassFilter, CanSetCutoffFreq)
{
    mc::HighPassFilter hpf;
    hpf.setCutoffFreq( 1.0 );
    EXPECT_DOUBLE_EQ( hpf.getOmega(), 2.0 * M_PI );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestHighPassFilter, CanUpdate1)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/signal/xcos/test_highpassfilter.xcos
    XcosBinFileReader::readData( "../tests/signal/data/test_highpassfilter.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::HighPassFilter hpf1( OMEGA );

    double t = 0.0;
    double y = 0.0;

    int devider = 10;
    int index = 0;
    double dt = TIME_STEP / (double)devider;

    for ( unsigned int i = 0; i < devider * vals.size(); i++ )
    {
        double u = ( t < 0.99 ) ? 0.0 : 1.0;

        hpf1.update( dt, u );
        y = hpf1.getValue();

        if ( i % devider == 0 )
        {
            if ( index > 0 )
            {
                //std::cout << y << std::endl;
                EXPECT_NEAR( y, vals.at( index - 1 ), 1.0e-1 );
            }

            index++;
        }

        t += dt;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestHighPassFilter, CanUpdate2)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/signal/xcos/test_highpassfilter_2.xcos
    XcosBinFileReader::readData( "../tests/signal/data/test_highpassfilter_2.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::HighPassFilter hpf2( OMEGA );

    double t = 0.0;
    double y = 0.0;

    int devider = 10;
    int index = 0;
    double dt = TIME_STEP / (double)devider;

    for ( unsigned int i = 0; i < devider * vals.size(); i++ )
    {
        double u = sin( t );

        hpf2.update( dt, u );
        y = hpf2.getValue();

        if ( i % devider == 0 )
        {
            if ( index > 0 )
            {
                //std::cout << y << std::endl;
                EXPECT_NEAR( y, vals.at( index - 1 ), 1.0e-1 );
            }

            index++;
        }

        t += dt;
    }
}
