#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/AWCondCalc.h>
#include <mcutils/ctrl/Inertia.h>
#include <mcutils/ctrl/PID.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestAWCondCalc : public ::testing::Test
{
protected:

    static constexpr double DT { 0.01 };
    static constexpr double TC { 5.0 };
    static constexpr double KP { 5.0 };
    static constexpr double KI { 0.5 };
    static constexpr double KD { 0.1 };

    static constexpr double MIN { -0.5 };
    static constexpr double MAX {  0.5 };

    TestAWCondCalc() {}
    virtual ~TestAWCondCalc() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWCondCalc, CanConstruct)
{
    mc::AWCondCalc *aw = nullptr;
    EXPECT_NO_THROW( aw = new mc::AWCondCalc() );
    delete aw;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWCondCalc, CanDestruct)
{
    mc::AWCondCalc *aw = new mc::AWCondCalc();
    EXPECT_NO_THROW( delete aw );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWCondCalc, CanInstantiate)
{
    mc::AWCondCalc aw;

    EXPECT_DOUBLE_EQ( aw.min(), DBL_MIN );
    EXPECT_DOUBLE_EQ( aw.max(), DBL_MAX );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWCondCalc, CanInstantiateAndSetData)
{
    mc::AWCondCalc aw(MIN, MAX);

    EXPECT_DOUBLE_EQ( aw.min(), MIN );
    EXPECT_DOUBLE_EQ( aw.max(), MAX );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWCondCalc, CanGetMin)
{
    mc::AWCondCalc aw(MIN, MAX);
    EXPECT_DOUBLE_EQ( aw.min(), MIN );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWCondCalc, CanGetMax)
{
    mc::AWCondCalc aw(MIN, MAX);
    EXPECT_DOUBLE_EQ( aw.max(), MAX );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWCondCalc, CanSetMin)
{
    mc::AWCondCalc aw;
    aw.set_min(MIN);
    EXPECT_DOUBLE_EQ( aw.min(), MIN );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWCondCalc, CanSetMax)
{
    mc::AWCondCalc aw;
    aw.set_max(MAX);
    EXPECT_DOUBLE_EQ( aw.max(), MAX );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWCondCalc, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
        // tests/control/xcos/test_pid.xcos
        XcosBinFileReader::readData( "../tests/ctrl/data/test_pid_antiwindup_conditional.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    mc::PID pid( KP, KI, KD, std::make_unique<mc::AWCondCalc>(MIN, MAX) );

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 500 ) ? 0.0 : 1.0;
        double e = u - y;
        pid.Update( DT, e );
        y = mc::Inertia::Calculate( pid.value(), y, DT, TC );

        EXPECT_NEAR( y, vals.at( i ), 1.0e-1 );

        t += DT;
    }
}
