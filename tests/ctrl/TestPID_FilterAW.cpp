#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/Inertia.h>
#include <mcutils/ctrl/PID_FilterAW.h>

#include <XcosBinFileReader.h>

using namespace units::literals;

class TestPID_FilterAW : public ::testing::Test
{
protected:

    static constexpr units::time::second_t DT = 0.01_s;

    static constexpr double TC { 5.0 };
    static constexpr double KP { 5.0 };
    static constexpr double KI { 0.5 };
    static constexpr double KD { 0.1 };

    static constexpr double KAW {  1.0 };
    static constexpr double MIN { -0.5 };
    static constexpr double MAX {  0.5 };

    TestPID_FilterAW() {}
    virtual ~TestPID_FilterAW() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestPID_FilterAW, CanInstantiate)
{
    mc::PID_FilterAW pid;

    EXPECT_DOUBLE_EQ(pid.kaw(), 0.0);
    EXPECT_DOUBLE_EQ(pid.min(), DBL_MIN);
    EXPECT_DOUBLE_EQ(pid.max(), DBL_MAX);
}

TEST_F(TestPID_FilterAW, CanInstantiateAndSetData)
{
    mc::PID_FilterAW pid(KP, KI, KD, MIN, MAX, KAW);

    EXPECT_DOUBLE_EQ(pid.kaw(), KAW);
    EXPECT_DOUBLE_EQ(pid.min(), MIN);
    EXPECT_DOUBLE_EQ(pid.max(), MAX);
}

TEST_F(TestPID_FilterAW, CanGetKaw)
{
    mc::PID_FilterAW pid(KP, KI, KD, MIN, MAX, KAW);
    EXPECT_DOUBLE_EQ(pid.kaw(), KAW);
}

TEST_F(TestPID_FilterAW, CanGetMin)
{
    mc::PID_FilterAW pid(KP, KI, KD, MIN, MAX, KAW);
    EXPECT_DOUBLE_EQ(pid.min(), MIN);
}

TEST_F(TestPID_FilterAW, CanGetMax)
{
    mc::PID_FilterAW pid(KP, KI, KD, MIN, MAX, KAW);
    EXPECT_DOUBLE_EQ(pid.max(), MAX);
}

TEST_F(TestPID_FilterAW, CanSetKaw)
{
    mc::PID_FilterAW pid;
    pid.set_kaw(KAW);
    EXPECT_DOUBLE_EQ(pid.kaw(), KAW);
}

TEST_F(TestPID_FilterAW, CanSetMin)
{
    mc::PID_FilterAW pid;
    pid.set_min(MIN);
    EXPECT_DOUBLE_EQ(pid.min(), MIN);
}

TEST_F(TestPID_FilterAW, CanSetMax)
{
    mc::PID_FilterAW pid;
    pid.set_max(MAX);
    EXPECT_DOUBLE_EQ(pid.max(), MAX);
}

TEST_F(TestPID_FilterAW, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_pid_antiwindup_filter.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    mc::PID_FilterAW pid(KP, KI, KD, MIN, MAX, KAW);

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = (i < 500) ? 0.0 : 1.0;
        double e = u - y;
        pid.Update(DT, e);
        y = mc::Inertia::Calculate(DT, TC, pid.value(), y);

        EXPECT_NEAR(y, vals.at(i), 1.0e-1);

        t += DT;
    }
}
