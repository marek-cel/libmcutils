#include <gtest/gtest.h>

#include <mcutils/signal/Lag.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestLag : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP     { 0.1 };
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
    // tests/signal/xcos/test_lag.xcos
    XcosBinFileReader::readData( "../tests/signal/data/test_lag.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( t < 0.99 ) ? 0.0 : 1.0;

        int steps = 10;
        for ( int j = 0; j < steps; j++ )
        {
            double dt = TIME_STEP / (double)steps;
            y = mc::Lag::calculate( u, y, dt, TIME_CONSTANT );
        }

        EXPECT_NEAR( y, vals.at( i ), 1.0e-3 );

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

TEST_F(TestLag, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/signal/xcos/test_lag.xcos
    XcosBinFileReader::readData( "../tests/signal/data/test_lag.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::Lag lag( TIME_CONSTANT );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( t < 0.99 ) ? 0.0 : 1.0;

        int steps = 10;
        for ( int j = 0; j < steps; j++ )
        {
            double dt = TIME_STEP / (double)steps;
            lag.update( dt, u );
            y = lag.getValue();
        }

        EXPECT_NEAR( y, vals.at( i ), 1.0e-3 );

        t += TIME_STEP;
    }

}
