#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/Lag.h>

#include <CsvFileReader.h>
#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestLag : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP     { 0.01 };
    static constexpr double TIME_CONSTANT { 2.0 };

    TestLag() {}
    virtual ~TestLag() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanCalculate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lag.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_lag_step.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 101 ) ? 0.0 : 1.0;
        y = mc::Lag::calculate( u, y, TIME_STEP, TIME_CONSTANT );

        double tolerance = std::max( 1.0e-3, 1.0e-3 * vals.at( i ) );
        EXPECT_NEAR( y, vals.at( i ), tolerance ) << "Error at index " << i;

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanCalculate2)
{
    std::vector<double> t_ref;
    std::vector<double> y_ref;

    // expected values calculated with GNU Octave
    // tests/control/octave/test_lag.m
    CsvFileReader::readData( "../tests/ctrl/data/test_lag_step.csv", &t_ref, &y_ref );

    EXPECT_GT( t_ref.size(), 0 ) << "No reference data.";
    EXPECT_GT( y_ref.size(), 0 ) << "No reference data.";
    EXPECT_EQ( t_ref.size(), y_ref.size() ) << "Reference data corrupted.";

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < t_ref.size(); i++ )
    {
        double u = ( i == 0 ) ? 0.0 : 1.0;
        y = mc::Lag::calculate( u, y, TIME_STEP, TIME_CONSTANT );

        EXPECT_NEAR( y, y_ref.at( i ), 1.0e-6 ) << "Mismatch at time= " << t;

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanConstruct)
{
    mc::Lag *lag = nullptr;
    EXPECT_NO_THROW( lag = new mc::Lag() );
    delete lag;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanDestruct)
{
    mc::Lag *lag = new mc::Lag();
    EXPECT_NO_THROW( delete lag );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanInstantiate)
{
    mc::Lag lag;

    EXPECT_DOUBLE_EQ( lag.getTimeConst(), 1.0 );
    EXPECT_DOUBLE_EQ( lag.getValue(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanInstantiateAndSetData)
{
    mc::Lag lag( 2.0, 3.0 );

    EXPECT_DOUBLE_EQ( lag.getTimeConst(), 2.0 );
    EXPECT_DOUBLE_EQ( lag.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanGetValue)
{
    mc::Lag lag( 2.0, 3.0 );

    EXPECT_DOUBLE_EQ( lag.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanSetValue)
{
    mc::Lag lag;

    lag.setValue( 1.0 );
    EXPECT_DOUBLE_EQ( lag.getValue(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanGetTimeConst)
{
    mc::Lag lag( 2.0 );

    EXPECT_DOUBLE_EQ( lag.getTimeConst(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanSetTimeConst)
{
    mc::Lag lag;

    lag.setTimeConst( 2.0 );
    EXPECT_DOUBLE_EQ( lag.getTimeConst(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanUpdateStep)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lag.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_lag_step.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::Lag lag( TIME_CONSTANT );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 101 ) ? 0.0 : 1.0;

        lag.update( TIME_STEP, u );
        y = lag.getValue();

        double tolerance = std::max( 1.0e-3, 1.0e-3 * vals.at( i ) );
        EXPECT_NEAR( y, vals.at( i ), tolerance ) << "Error at index " << i;

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanUpdateStep2)
{
    std::vector<double> t_ref;
    std::vector<double> y_ref;

    // expected values calculated with GNU Octave
    // tests/control/octave/test_lag.m
    CsvFileReader::readData( "../tests/ctrl/data/test_lag_step.csv", &t_ref, &y_ref );

    EXPECT_GT( t_ref.size(), 0 ) << "No reference data.";
    EXPECT_GT( y_ref.size(), 0 ) << "No reference data.";
    EXPECT_EQ( t_ref.size(), y_ref.size() ) << "Reference data corrupted.";

    mc::Lag lag( TIME_CONSTANT );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < t_ref.size(); i++ )
    {
        double u = ( i == 0 ) ? 0.0 : 1.0;

        lag.update( TIME_STEP, u );
        y = lag.getValue();

        EXPECT_NEAR( y, y_ref.at( i ), 1.0e-6 ) << "Mismatch at time= " << t;

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag, CanUpdateSine)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lag.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_lag_sine.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::Lag lag( TIME_CONSTANT );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = sin( t + TIME_STEP );

        lag.update( TIME_STEP, u );
        y = lag.getValue();

        double tolerance = std::max( 1.0e-2, 1.0e-2 * vals.at( i ) );
        EXPECT_NEAR( y, vals.at( i ), tolerance ) << "Error at index " << i;

        t += TIME_STEP;
    }
}
