#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/BandPassFilter.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class BandPassFilter : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP { 0.01 };

    static constexpr double BETA  { 3.14 };
    static constexpr double OMEGA { 2.0 * 3.14 };

    BandPassFilter() {}
    virtual ~BandPassFilter() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(BandPassFilter, CanConstruct)
{
    mc::BandPassFilter *bpf = nullptr;
    EXPECT_NO_THROW( bpf = new mc::BandPassFilter() );
    delete bpf;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(BandPassFilter, CanDestruct)
{
    mc::BandPassFilter *bpf = new mc::BandPassFilter();
    EXPECT_NO_THROW( delete bpf );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(BandPassFilter, CanInstantiate)
{
    mc::BandPassFilter bpf;
    EXPECT_DOUBLE_EQ( bpf.getBeta(), 0.0 );
    EXPECT_DOUBLE_EQ( bpf.getOmega(), 0.0 );
    EXPECT_DOUBLE_EQ( bpf.getValue(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(BandPassFilter, CanInstantiateAndSetData)
{
    mc::BandPassFilter bpf( 2.0, 3.0, 4.0 );
    EXPECT_DOUBLE_EQ( bpf.getBeta(), 2.0 );
    EXPECT_DOUBLE_EQ( bpf.getOmega(), 3.0 );
    EXPECT_DOUBLE_EQ( bpf.getValue(), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(BandPassFilter, CanGetBeta)
{
    mc::BandPassFilter bpf( 2.0, 3.0, 4.0 );
    EXPECT_DOUBLE_EQ( bpf.getBeta(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(BandPassFilter, CanGetOmega)
{
    mc::BandPassFilter bpf( 2.0, 3.0, 4.0 );
    EXPECT_DOUBLE_EQ( bpf.getOmega(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(BandPassFilter, CanGetValue)
{
    mc::BandPassFilter bpf( 2.0, 3.0, 4.0 );
    EXPECT_DOUBLE_EQ( bpf.getValue(), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(BandPassFilter, CanSetBeta)
{
    mc::BandPassFilter bpf;
    bpf.setBeta( 1.0 );
    EXPECT_DOUBLE_EQ( bpf.getBeta(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(BandPassFilter, CanSetOmega)
{
    mc::BandPassFilter bpf;
    bpf.setOmega( 2.0 );
    EXPECT_DOUBLE_EQ( bpf.getOmega(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(BandPassFilter, CanSetValue)
{
    mc::BandPassFilter bpf;
    bpf.setValue( 3.0 );
    EXPECT_DOUBLE_EQ( bpf.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(BandPassFilter, CanUpdateStep)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_bandpassfilter.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_bandpassfilter_step.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::BandPassFilter bpf( BETA, OMEGA );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 100 ) ? 0.0 : 1.0;

        bpf.update( TIME_STEP, u );
        y = bpf.getValue();

        double tolerance = std::max( 1.0e-2, 1.0e-2 * vals.at( i ) );
        EXPECT_NEAR( y, vals.at( i ), tolerance ) << "Error at index " << i;

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(BandPassFilter, CanUpdateSine1Hz)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_bandpassfilter.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_bandpassfilter_sine_1Hz.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::BandPassFilter bpf( BETA, OMEGA );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = sin( 2.0 * 3.14 * t );

        bpf.update( TIME_STEP, u );
        y = bpf.getValue();

        double tolerance = std::max( 1.0e-2, 1.0e-2 * vals.at( i ) );
        EXPECT_NEAR( y, vals.at( i ), tolerance ) << "Error at index " << i;

        t += TIME_STEP;
    }
}
