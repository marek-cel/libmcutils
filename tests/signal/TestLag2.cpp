#include <gtest/gtest.h>

#include <mcutils/signal/Lag2.h>

#include <CsvFileReader.h>
#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestLag2 : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP { 0.1 };

    static constexpr double TIME_CONSTANT_1 { 2.0 };
    static constexpr double TIME_CONSTANT_2 { 3.0 };

    TestLag2() {}
    virtual ~TestLag2() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanConstruct)
{
    mc::Lag2 *lag = nullptr;
    EXPECT_NO_THROW( lag = new mc::Lag2() );
    delete lag;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanDestruct)
{
    mc::Lag2 *lag = new mc::Lag2();
    EXPECT_NO_THROW( delete lag );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanInstantiate)
{
    mc::Lag2 lag;

    EXPECT_DOUBLE_EQ( lag.getTimeConst1(), 1.0 );
    EXPECT_DOUBLE_EQ( lag.getTimeConst2(), 1.0 );
    EXPECT_DOUBLE_EQ( lag.getValue(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanInstantiateAndCopy)
{
    mc::Lag2 lag( 2.0, 3.0, 4.0 );
    mc::Lag2 lag1( lag );

    EXPECT_DOUBLE_EQ( lag1.getTimeConst1(), 2.0 );
    EXPECT_DOUBLE_EQ( lag1.getTimeConst2(), 3.0 );
    EXPECT_DOUBLE_EQ( lag1.getValue(), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanInstantiateAndSetData)
{
    mc::Lag2 lag( 2.0, 3.0, 4.0 );

    EXPECT_DOUBLE_EQ( lag.getTimeConst1(), 2.0 );
    EXPECT_DOUBLE_EQ( lag.getTimeConst2(), 3.0 );
    EXPECT_DOUBLE_EQ( lag.getValue(), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanGetTimeConst1)
{
    mc::Lag2 lag( 2.0, 3.0, 4.0 );

    EXPECT_DOUBLE_EQ( lag.getTimeConst1(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanGetTimeConst2)
{
    mc::Lag2 lag( 2.0, 3.0, 4.0 );

    EXPECT_DOUBLE_EQ( lag.getTimeConst2(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanGetValue)
{
    mc::Lag2 lag( 2.0, 3.0, 4.0 );

    EXPECT_DOUBLE_EQ( lag.getValue(), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanSetTimeConst1)
{
    mc::Lag2 lag;
    lag.setTimeConst1( 2.0 );
    EXPECT_DOUBLE_EQ( lag.getTimeConst1(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanSetTimeConst2)
{
    mc::Lag2 lag;
    lag.setTimeConst2( 3.0 );
    EXPECT_DOUBLE_EQ( lag.getTimeConst2(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanSetValue)
{
    mc::Lag2 lag;
    lag.setValue( 4.0 );
    EXPECT_DOUBLE_EQ( lag.getValue(), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/signal/xcos/test_lag2.xcos
    XcosBinFileReader::readData( "../tests/signal/data/test_lag2.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::Lag2 lag( TIME_CONSTANT_1, TIME_CONSTANT_2 );

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

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanUpdate2)
{
    std::vector<double> t_ref;
    std::vector<double> y_ref;

    // expected values calculated with GNU Octave
    // tests/signal/octave/test_lag2.m
    CsvFileReader::readData( "../tests/signal/data/test_lag2_1.csv", &t_ref, &y_ref );

    EXPECT_GT( t_ref.size(), 0 ) << "No reference data.";
    EXPECT_GT( y_ref.size(), 0 ) << "No reference data.";
    EXPECT_EQ( t_ref.size(), y_ref.size() ) << "Reference data corrupted.";

    mc::Lag2 lag( TIME_CONSTANT_1, TIME_CONSTANT_2 );

    double t = 0.0;
    double y = 0.0;

    double dt = 0.01;

    for ( unsigned int i = 0; i < y_ref.size(); i++ )
    {
        double u = ( i == 0 ) ? 0.0 : 1.0;
        lag.update( dt, u );
        y = lag.getValue();
        EXPECT_NEAR( y, y_ref.at( i ), 5.0e-3 ) << "Mismatch at time= " << t;

        t += dt;
    }

}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLag2, CanAssign)
{
    mc::Lag2 lag( 2.0, 3.0, 4.0 );
    mc::Lag2 lag1;

    lag1 = lag;

    EXPECT_DOUBLE_EQ( lag1.getTimeConst1(), 2.0 );
    EXPECT_DOUBLE_EQ( lag1.getTimeConst2(), 3.0 );
    EXPECT_DOUBLE_EQ( lag1.getValue(), 4.0 );
}

