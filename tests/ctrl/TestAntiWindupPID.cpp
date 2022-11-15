#include <gtest/gtest.h>

#include <mcutils/ctrl/AntiWindupPID.h>
#include <mcutils/ctrl/Inertia.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestAntiWindupPID : public ::testing::Test
{
protected:

    static constexpr double DT { 0.01 };
    static constexpr double TC { 5.0 };
    static constexpr double KP { 5.0 };
    static constexpr double KI { 0.5 };
    static constexpr double KD { 0.1 };
    static constexpr double MIN { -0.5 };
    static constexpr double MAX {  0.5 };

    TestAntiWindupPID() {}
    virtual ~TestAntiWindupPID() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanConstruct)
{
    mc::AntiWindupPID *pid = nullptr;
    EXPECT_NO_THROW( pid = new mc::AntiWindupPID() );
    delete pid;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanDestruct)
{
    mc::AntiWindupPID *pid = new mc::AntiWindupPID();
    EXPECT_NO_THROW( delete pid );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanInstantiate)
{
    mc::AntiWindupPID pid( KP, KI, KD );

    EXPECT_DOUBLE_EQ( pid.getKp(), KP );
    EXPECT_DOUBLE_EQ( pid.getKi(), KI );
    EXPECT_DOUBLE_EQ( pid.getKd(), KD );

    EXPECT_DOUBLE_EQ( pid.getKaw(), 0.0 );

    EXPECT_DOUBLE_EQ( pid.getMin(), std::numeric_limits<double>::min() );
    EXPECT_DOUBLE_EQ( pid.getMax(), std::numeric_limits<double>::max() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanInstantiateAndSetData)
{
    mc::AntiWindupPID pid( 2.0, 3.0, 4.0, 5.0, 6.0 );

    EXPECT_DOUBLE_EQ( pid.getKp(), 2.0 );
    EXPECT_DOUBLE_EQ( pid.getKi(), 3.0 );
    EXPECT_DOUBLE_EQ( pid.getKd(), 4.0 );

    EXPECT_DOUBLE_EQ( pid.getKaw(), 0.0 );

    EXPECT_DOUBLE_EQ( pid.getMin(), 5.0 );
    EXPECT_DOUBLE_EQ( pid.getMax(), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanReset)
{
    mc::AntiWindupPID pid( KP, KI, KD, MIN, MAX );

    pid.update( DT, 1.0 );
    pid.update( DT, 2.0 );
    pid.update( DT, 3.0 );

    EXPECT_NO_THROW( pid.reset() );
    EXPECT_DOUBLE_EQ( pid.getValue(), 0.0 );
    EXPECT_DOUBLE_EQ( pid.getError(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanGetValue)
{
    mc::AntiWindupPID pid;

    pid.setValue( 7.0 );

    EXPECT_DOUBLE_EQ( pid.getValue(), 7.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanGetKp)
{
    mc::AntiWindupPID pid( KP, KI, KD, MIN, MAX );

    EXPECT_DOUBLE_EQ( pid.getKp(), KP );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanGetKi)
{
    mc::AntiWindupPID pid( KP, KI, KD, MIN, MAX );

    EXPECT_DOUBLE_EQ( pid.getKi(), KI );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanGetKd)
{
    mc::AntiWindupPID pid( KP, KI, KD, MIN, MAX );

    EXPECT_DOUBLE_EQ( pid.getKd(), KD );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanGetKaw)
{
    mc::AntiWindupPID pid( KP, KI, KD, MIN, MAX );

    pid.setKaw( 1.1 );

    EXPECT_DOUBLE_EQ( pid.getKaw(), 1.1 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanGetMin)
{
    mc::AntiWindupPID pid( KP, KI, KD, -9.0, 9.0 );

    EXPECT_DOUBLE_EQ( pid.getMin(), -9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanGetMax)
{
    mc::AntiWindupPID pid( KP, KI, KD, -9.0, 9.0 );

    EXPECT_DOUBLE_EQ( pid.getMax(), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanGetAntiWindup)
{
    mc::AntiWindupPID pid;

    EXPECT_EQ( pid.getAntiWindup(), mc::AntiWindupPID::AntiWindup::None );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetParallel)
{
    mc::AntiWindupPID pid;

    pid.setParallel( KP, KI, KD );

    EXPECT_DOUBLE_EQ( pid.getKp(), KP );
    EXPECT_DOUBLE_EQ( pid.getKi(), KI );
    EXPECT_DOUBLE_EQ( pid.getKd(), KD );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetSeries)
{
    mc::AntiWindupPID pid;

    pid.setSeries( 1.0, 2.0, 3.0 );

    // expected values calculated with GNU Octave
    // tests/control/octave/test_pid.m

    EXPECT_DOUBLE_EQ( pid.getKp(), 2.5 );
    EXPECT_DOUBLE_EQ( pid.getKi(), 0.5 );
    EXPECT_DOUBLE_EQ( pid.getKd(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetStandard)
{
    mc::AntiWindupPID pid;

    pid.setStandard( 1.0, 2.0, 3.0 );

    // expected values calculated with GNU Octave
    // tests/control/octave/test_pid.m

    EXPECT_DOUBLE_EQ( pid.getKp(), 1.0 );
    EXPECT_DOUBLE_EQ( pid.getKi(), 0.5 );
    EXPECT_DOUBLE_EQ( pid.getKd(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetError)
{
    mc::AntiWindupPID pid;

    EXPECT_NO_THROW( pid.setError( 6.0 ) );
    EXPECT_DOUBLE_EQ( pid.getError(), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetValue)
{
    mc::AntiWindupPID pid;

    EXPECT_NO_THROW( pid.setValue( 7.0 ) );
    EXPECT_DOUBLE_EQ( pid.getValue(), 7.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetValueAndError)
{
    mc::AntiWindupPID pid( KP, KI, KD, MIN, MAX );

    EXPECT_NO_THROW( pid.setValue( 0.1, 6.0, 7.0 ) );
    EXPECT_DOUBLE_EQ( pid.getValue(), 7.0 );
    EXPECT_DOUBLE_EQ( pid.getError(), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetKp)
{
    mc::AntiWindupPID pid;

    EXPECT_NO_THROW( pid.setKp( KP ) );
    EXPECT_DOUBLE_EQ( pid.getKp(), KP );
}
////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetKi)
{
    mc::AntiWindupPID pid;

    EXPECT_NO_THROW( pid.setKi( KI ) );
    EXPECT_DOUBLE_EQ( pid.getKi(), KI );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetKd)
{
    mc::AntiWindupPID pid;

    EXPECT_NO_THROW( pid.setKd( KD ) );
    EXPECT_DOUBLE_EQ( pid.getKd(), KD );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetKaw)
{
    mc::AntiWindupPID pid;

    EXPECT_NO_THROW( pid.setKaw( 1.1 ) );
    EXPECT_DOUBLE_EQ( pid.getKaw(), 1.1 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetMin)
{
    mc::AntiWindupPID pid;

    EXPECT_NO_THROW( pid.setMin( -9.0 ) );
    EXPECT_DOUBLE_EQ( pid.getMin(), -9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetMax)
{
    mc::AntiWindupPID pid;

    EXPECT_NO_THROW( pid.setMax( 9.0 ) );
    EXPECT_DOUBLE_EQ( pid.getMax(), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanSetAntiWindup)
{
    mc::AntiWindupPID pid;

    EXPECT_EQ( pid.getAntiWindup(), mc::AntiWindupPID::AntiWindup::None );

    EXPECT_NO_THROW( pid.setAntiWindup( mc::AntiWindupPID::AntiWindup::Calculation ) );
    EXPECT_EQ( pid.getAntiWindup(), mc::AntiWindupPID::AntiWindup::Calculation );

    EXPECT_NO_THROW( pid.setAntiWindup( mc::AntiWindupPID::AntiWindup::Conditional ) );
    EXPECT_EQ( pid.getAntiWindup(), mc::AntiWindupPID::AntiWindup::Conditional );

    EXPECT_NO_THROW( pid.setAntiWindup( mc::AntiWindupPID::AntiWindup::Filtering ) );
    EXPECT_EQ( pid.getAntiWindup(), mc::AntiWindupPID::AntiWindup::Filtering );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_pid_satur.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    mc::AntiWindupPID pid( KP, KI, KD, MIN, MAX );

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 500 ) ? 0.0 : 1.0;
        double e = u - y;
        pid.update( DT, e );
        y = mc::Inertia::calculate( pid.getValue(), y, DT, TC );

        EXPECT_NEAR( y, vals.at( i ), 1.0e-1 );

        t += DT;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanUpdateAntiwindupCalculation)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_pid_antiwindup_calculation.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    mc::AntiWindupPID pid( KP, KI, KD, MIN, MAX, mc::AntiWindupPID::AntiWindup::Calculation );

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 500 ) ? 0.0 : 1.0;
        double e = u - y;
        pid.update( DT, e );
        y = mc::Inertia::calculate( pid.getValue(), y, DT, TC );

        EXPECT_NEAR( y, vals.at( i ), 1.0e-1 );

        t += DT;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanUpdateAntiwindupConditional)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_pid_antiwindup_conditional.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    mc::AntiWindupPID pid( KP, KI, KD, MIN, MAX, mc::AntiWindupPID::AntiWindup::Conditional );

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 500 ) ? 0.0 : 1.0;
        double e = u - y;
        pid.update( DT, e );
        y = mc::Inertia::calculate( pid.getValue(), y, DT, TC );

        EXPECT_NEAR( y, vals.at( i ), 1.0e-1 );

        t += DT;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAntiWindupPID, CanUpdateAntiwindupFilter)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_pid_antiwindup_filter.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    mc::AntiWindupPID pid( KP, KI, KD, MIN, MAX, mc::AntiWindupPID::AntiWindup::Filtering );

    pid.setKaw( 1.0 );

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 500 ) ? 0.0 : 1.0;
        double e = u - y;
        pid.update( DT, e );
        y = mc::Inertia::calculate( pid.getValue(), y, DT, TC );

        EXPECT_NEAR( y, vals.at( i ), 1.0e-1 );

        t += DT;
    }
}
