#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/Inertia.h>

#include <CsvFileReader.h>
#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestInertia : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP     { 0.01 };
    static constexpr double TIME_CONSTANT { 2.0 };

    TestInertia() {}
    virtual ~TestInertia() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanCalculate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lag.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_inertia_step.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 101 ) ? 0.0 : 1.0;
        y = mc::Inertia::calculate( u, y, TIME_STEP, TIME_CONSTANT );

        double tolerance = std::max( 1.0e-3, 1.0e-3 * vals.at( i ) );
        EXPECT_NEAR( y, vals.at( i ), tolerance ) << "Error at index " << i;

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanCalculate2)
{
    std::vector<double> t_ref;
    std::vector<double> y_ref;

    // expected values calculated with GNU Octave
    // tests/control/octave/test_lag.m
    CsvFileReader::readData( "../tests/ctrl/data/test_inertia_step.csv", &t_ref, &y_ref );

    EXPECT_GT( t_ref.size(), 0 ) << "No reference data.";
    EXPECT_GT( y_ref.size(), 0 ) << "No reference data.";
    EXPECT_EQ( t_ref.size(), y_ref.size() ) << "Reference data corrupted.";

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < t_ref.size(); i++ )
    {
        double u = ( i == 0 ) ? 0.0 : 1.0;
        y = mc::Inertia::calculate( u, y, TIME_STEP, TIME_CONSTANT );

        EXPECT_NEAR( y, y_ref.at( i ), 1.0e-6 ) << "Mismatch at time= " << t;

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanConstruct)
{
    mc::Inertia *inertia = nullptr;
    EXPECT_NO_THROW( inertia = new mc::Inertia() );
    delete inertia;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanDestruct)
{
    mc::Inertia *inertia = new mc::Inertia();
    EXPECT_NO_THROW( delete inertia );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanInstantiate)
{
    mc::Inertia inertia;

    EXPECT_DOUBLE_EQ( inertia.getTimeConst(), 0.0 );
    EXPECT_DOUBLE_EQ( inertia.getValue(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanInstantiateAndSetData)
{
    mc::Inertia inertia( 2.0, 3.0 );

    EXPECT_DOUBLE_EQ( inertia.getTimeConst(), 2.0 );
    EXPECT_DOUBLE_EQ( inertia.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanGetValue)
{
    mc::Inertia inertia( 2.0, 3.0 );

    EXPECT_DOUBLE_EQ( inertia.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanSetValue)
{
    mc::Inertia inertia;

    inertia.setValue( 1.0 );
    EXPECT_DOUBLE_EQ( inertia.getValue(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanGetTimeConst)
{
    mc::Inertia inertia( 2.0 );

    EXPECT_DOUBLE_EQ( inertia.getTimeConst(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanSetTimeConst)
{
    mc::Inertia inertia;

    inertia.setTimeConst( 2.0 );
    EXPECT_DOUBLE_EQ( inertia.getTimeConst(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanUpdateStep)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lag.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_inertia_step.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::Inertia inertia( TIME_CONSTANT );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 101 ) ? 0.0 : 1.0;

        inertia.update( TIME_STEP, u );
        y = inertia.getValue();

        double tolerance = std::max( 1.0e-3, 1.0e-3 * vals.at( i ) );
        EXPECT_NEAR( y, vals.at( i ), tolerance ) << "Error at index " << i;

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanUpdateStep2)
{
    std::vector<double> t_ref;
    std::vector<double> y_ref;

    // expected values calculated with GNU Octave
    // tests/control/octave/test_lag.m
    CsvFileReader::readData( "../tests/ctrl/data/test_inertia_step.csv", &t_ref, &y_ref );

    EXPECT_GT( t_ref.size(), 0 ) << "No reference data.";
    EXPECT_GT( y_ref.size(), 0 ) << "No reference data.";
    EXPECT_EQ( t_ref.size(), y_ref.size() ) << "Reference data corrupted.";

    mc::Inertia inertia( TIME_CONSTANT );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < t_ref.size(); i++ )
    {
        double u = ( i == 0 ) ? 0.0 : 1.0;

        inertia.update( TIME_STEP, u );
        y = inertia.getValue();

        EXPECT_NEAR( y, y_ref.at( i ), 1.0e-6 ) << "Mismatch at time= " << t;

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestInertia, CanUpdateSine)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lag.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_inertia_sine.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::Inertia inertia( TIME_CONSTANT );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = sin( t + TIME_STEP );

        inertia.update( TIME_STEP, u );
        y = inertia.getValue();

        double tolerance = std::max( 1.0e-2, 1.0e-2 * vals.at( i ) );
        EXPECT_NEAR( y, vals.at( i ), tolerance ) << "Error at index " << i;

        t += TIME_STEP;
    }
}
