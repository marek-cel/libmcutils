#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/AWFilter.h>
#include <mcutils/ctrl/Inertia.h>
#include <mcutils/ctrl/PID.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestAWFilter : public ::testing::Test
{
protected:

    static constexpr double DT { 0.01 };
    static constexpr double TC { 5.0 };
    static constexpr double KP { 5.0 };
    static constexpr double KI { 0.5 };
    static constexpr double KD { 0.1 };

    static constexpr double KAW {  1.0 };
    static constexpr double MIN { -0.5 };
    static constexpr double MAX {  0.5 };

    TestAWFilter() {}
    virtual ~TestAWFilter() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWFilter, CanConstruct)
{
    mc::AWFilter *aw = nullptr;
    EXPECT_NO_THROW( aw = new mc::AWFilter() );
    delete aw;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWFilter, CanDestruct)
{
    mc::AWFilter *aw = new mc::AWFilter();
    EXPECT_NO_THROW( delete aw );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWFilter, CanInstantiate)
{
    mc::AWFilter aw;

    EXPECT_DOUBLE_EQ( aw.kaw(), 0.0 );
    EXPECT_DOUBLE_EQ( aw.min(), DBL_MIN );
    EXPECT_DOUBLE_EQ( aw.max(), DBL_MAX );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWFilter, CanInstantiateAndSetData)
{
    mc::AWFilter aw(MIN, MAX, KAW);

    EXPECT_DOUBLE_EQ( aw.kaw(), KAW );
    EXPECT_DOUBLE_EQ( aw.min(), MIN );
    EXPECT_DOUBLE_EQ( aw.max(), MAX );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWFilter, CanGetKaw)
{
    mc::AWFilter aw(MIN, MAX, KAW);
    EXPECT_DOUBLE_EQ( aw.kaw(), KAW );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWFilter, CanGetMin)
{
    mc::AWFilter aw(MIN, MAX, KAW);
    EXPECT_DOUBLE_EQ( aw.min(), MIN );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWFilter, CanGetMax)
{
    mc::AWFilter aw(MIN, MAX, KAW);
    EXPECT_DOUBLE_EQ( aw.max(), MAX );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWFilter, CanSetKaw)
{
    mc::AWFilter aw;
    aw.set_kaw(KAW);
    EXPECT_DOUBLE_EQ( aw.kaw(), KAW );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWFilter, CanSetMin)
{
    mc::AWFilter aw;
    aw.set_min(MIN);
    EXPECT_DOUBLE_EQ( aw.min(), MIN );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWFilter, CanSetMax)
{
    mc::AWFilter aw;
    aw.set_max(MAX);
    EXPECT_DOUBLE_EQ( aw.max(), MAX );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAWFilter, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::readData( "../tests/ctrl/data/test_pid_antiwindup_filter.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    mc::PID pid( KP, KI, KD, std::make_unique<mc::AWFilter>(MIN, MAX, KAW) );

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 500 ) ? 0.0 : 1.0;
        double e = u - y;
        pid.Update( DT, e );
        y = mc::Inertia::calculate( pid.value(), y, DT, TC );

        EXPECT_NEAR( y, vals.at( i ), 1.0e-1 );

        t += DT;
    }
}
