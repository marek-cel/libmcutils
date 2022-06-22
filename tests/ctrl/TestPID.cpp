#include <gtest/gtest.h>

#include <mcutils/ctrl/PID.h>
#include <mcutils/ctrl/Inertia.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestPID : public ::testing::Test
{
protected:

    static constexpr double DT { 0.01 };
    static constexpr double TC { 5.0 };
    static constexpr double KP { 5.0 };
    static constexpr double KI { 0.5 };
    static constexpr double KD { 0.1 };

    TestPID() {}
    virtual ~TestPID() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanConstruct)
{
    mc::PID *pid = nullptr;
    EXPECT_NO_THROW( pid = new mc::PID() );
    delete pid;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanDestruct)
{
    mc::PID *pid = new mc::PID();
    EXPECT_NO_THROW( delete pid );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanInstantiate)
{
    mc::PID pid;

    EXPECT_DOUBLE_EQ( pid.getKp(), 1.0 );
    EXPECT_DOUBLE_EQ( pid.getKi(), 0.0 );
    EXPECT_DOUBLE_EQ( pid.getKd(), 0.0 );

    EXPECT_DOUBLE_EQ( pid.getKaw(), 0.0 );

    EXPECT_DOUBLE_EQ( pid.getMin(), std::numeric_limits<double>::min() );
    EXPECT_DOUBLE_EQ( pid.getMax(), std::numeric_limits<double>::max() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanInstantiateAndSetData)
{
    mc::PID pid( 2.0, 3.0, 4.0, 5.0, 6.0 );

    EXPECT_DOUBLE_EQ( pid.getKp(), 2.0 );
    EXPECT_DOUBLE_EQ( pid.getKi(), 3.0 );
    EXPECT_DOUBLE_EQ( pid.getKd(), 4.0 );

    EXPECT_DOUBLE_EQ( pid.getKaw(), 0.0 );

    EXPECT_DOUBLE_EQ( pid.getMin(), 5.0 );
    EXPECT_DOUBLE_EQ( pid.getMax(), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanReset)
{
    mc::PID pid( KP, KI, KD );

    pid.update( DT, 1.0 );
    pid.update( DT, 2.0 );
    pid.update( DT, 3.0 );

    EXPECT_NO_THROW( pid.reset() );
    EXPECT_DOUBLE_EQ( pid.getValue(), 0.0 );
    EXPECT_DOUBLE_EQ( pid.getError(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanGetValue)
{
    mc::PID pid( KP, KI, KD );

    pid.setValue( 7.0 );

    EXPECT_DOUBLE_EQ( pid.getValue(), 7.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanGetKp)
{
    mc::PID pid( KP, KI, KD );

    EXPECT_DOUBLE_EQ( pid.getKp(), KP );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanGetKi)
{
    mc::PID pid( KP, KI, KD );

    EXPECT_DOUBLE_EQ( pid.getKi(), KI );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanGetKd)
{
    mc::PID pid( KP, KI, KD );

    EXPECT_DOUBLE_EQ( pid.getKd(), KD );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanGetKaw)
{
    mc::PID pid( KP, KI, KD );

    pid.setKaw( 1.1 );

    EXPECT_DOUBLE_EQ( pid.getKaw(), 1.1 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanGetMin)
{
    mc::PID pid( KP, KI, KD, -9.0, 9.0 );

    EXPECT_DOUBLE_EQ( pid.getMin(), -9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanGetMax)
{
    mc::PID pid( KP, KI, KD, -9.0, 9.0 );

    EXPECT_DOUBLE_EQ( pid.getMax(), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanGetAntiWindup)
{
    mc::PID pid;

    EXPECT_EQ( pid.getAntiWindup(), mc::PID::AntiWindup::None );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanGetSaturation)
{
    mc::PID pid1( KP, KI, KD );
    EXPECT_FALSE( pid1.getSaturation() );

    mc::PID pid2( KP, KI, KD, -9.0, 9.0 );
    EXPECT_TRUE( pid2.getSaturation() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetParallel)
{
    mc::PID pid;

    pid.setParallel( KP, KI, KD );

    EXPECT_DOUBLE_EQ( pid.getKp(), KP );
    EXPECT_DOUBLE_EQ( pid.getKi(), KI );
    EXPECT_DOUBLE_EQ( pid.getKd(), KD );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetSeries)
{
    mc::PID pid;

    pid.setSeries( 1.0, 2.0, 3.0 );

    // expected values calculated with GNU Octave
    // tests/control/octave/test_pid.m

    EXPECT_DOUBLE_EQ( pid.getKp(), 2.5 );
    EXPECT_DOUBLE_EQ( pid.getKi(), 0.5 );
    EXPECT_DOUBLE_EQ( pid.getKd(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetStandard)
{
    mc::PID pid;

    pid.setStandard( 1.0, 2.0, 3.0 );

    // expected values calculated with GNU Octave
    // tests/control/octave/test_pid.m

    EXPECT_DOUBLE_EQ( pid.getKp(), 1.0 );
    EXPECT_DOUBLE_EQ( pid.getKi(), 0.5 );
    EXPECT_DOUBLE_EQ( pid.getKd(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetError)
{
    mc::PID pid( KP, KI, KD );

    EXPECT_NO_THROW( pid.setError( 6.0 ) );
    EXPECT_DOUBLE_EQ( pid.getError(), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetValue)
{
    mc::PID pid( KP, KI, KD );

    EXPECT_NO_THROW( pid.setValue( 7.0 ) );
    EXPECT_DOUBLE_EQ( pid.getValue(), 7.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetValueAndError)
{
    mc::PID pid( KP, KI, KD );

    EXPECT_NO_THROW( pid.setValue( 0.1, 6.0, 7.0 ) );
    EXPECT_DOUBLE_EQ( pid.getValue(), 7.0 );
    EXPECT_DOUBLE_EQ( pid.getError(), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetKp)
{
    mc::PID pid;

    EXPECT_NO_THROW( pid.setKp( KP ) );
    EXPECT_DOUBLE_EQ( pid.getKp(), KP );
}
////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetKi)
{
    mc::PID pid;

    EXPECT_NO_THROW( pid.setKi( KI ) );
    EXPECT_DOUBLE_EQ( pid.getKi(), KI );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetKd)
{
    mc::PID pid;

    EXPECT_NO_THROW( pid.setKd( KD ) );
    EXPECT_DOUBLE_EQ( pid.getKd(), KD );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetKaw)
{
    mc::PID pid;

    EXPECT_NO_THROW( pid.setKaw( 1.1 ) );
    EXPECT_DOUBLE_EQ( pid.getKaw(), 1.1 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetMin)
{
    mc::PID pid;

    EXPECT_NO_THROW( pid.setMin( -9.0 ) );
    EXPECT_DOUBLE_EQ( pid.getMin(), -9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetMax)
{
    mc::PID pid;

    EXPECT_NO_THROW( pid.setMax( 9.0 ) );
    EXPECT_DOUBLE_EQ( pid.getMax(), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetAntiWindup)
{
    mc::PID pid( KP, KI, KD );

    EXPECT_EQ( pid.getAntiWindup(), mc::PID::AntiWindup::None );

    EXPECT_NO_THROW( pid.setAntiWindup( mc::PID::AntiWindup::Calculation ) );
    EXPECT_EQ( pid.getAntiWindup(), mc::PID::AntiWindup::Calculation );

    EXPECT_NO_THROW( pid.setAntiWindup( mc::PID::AntiWindup::Conditional ) );
    EXPECT_EQ( pid.getAntiWindup(), mc::PID::AntiWindup::Conditional );

    EXPECT_NO_THROW( pid.setAntiWindup( mc::PID::AntiWindup::Filtering ) );
    EXPECT_EQ( pid.getAntiWindup(), mc::PID::AntiWindup::Filtering );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanSetSaturation)
{
    mc::PID pid( KP, KI, KD );

    EXPECT_FALSE( pid.getSaturation() );

    pid.setSaturation( true );

    EXPECT_TRUE( pid.getSaturation() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPID, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_pid.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    mc::PID pid( KP, KI, KD );

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

TEST_F(TestPID, CanUpdateAntiwindupCalculation)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_pid_antiwindup_calculation.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    mc::PID pid( KP, KI, KD, -0.5, 0.5 );

    pid.setAntiWindup( mc::PID::AntiWindup::Calculation );

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

TEST_F(TestPID, CanUpdateAntiwindupConditional)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_pid_antiwindup_conditional.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    mc::PID pid( KP, KI, KD, -0.5, 0.5 );

    pid.setAntiWindup( mc::PID::AntiWindup::Conditional );

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

TEST_F(TestPID, CanUpdateAntiwindupFilter)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_pid_antiwindup_filter.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    mc::PID pid( KP, KI, KD, -0.5, 0.5 );

    pid.setAntiWindup( mc::PID::AntiWindup::Filtering );
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
