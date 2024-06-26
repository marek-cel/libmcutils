#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/Inertia.h>
#include <mcutils/ctrl/PID_CondCalc.h>

#include <XcosBinFileReader.h>

class TestPID_CondCalc : public ::testing::Test
{
protected:

    static constexpr double DT { 0.01 };

    static constexpr double TC { 5.0 };
    static constexpr double KP { 5.0 };
    static constexpr double KI { 0.5 };
    static constexpr double KD { 0.1 };

    static constexpr double MIN { -0.5 };
    static constexpr double MAX {  0.5 };

    TestPID_CondCalc() {}
    virtual ~TestPID_CondCalc() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestPID_CondCalc, CanInstantiate)
{
    mc::PID_CondCalc pid;

    EXPECT_DOUBLE_EQ(pid.min(), DBL_MIN);
    EXPECT_DOUBLE_EQ(pid.max(), DBL_MAX);
}

TEST_F(TestPID_CondCalc, CanInstantiateAndSetData)
{
    mc::PID_CondCalc pid(KP, KI, KD, MIN, MAX);

    EXPECT_DOUBLE_EQ(pid.min(), MIN);
    EXPECT_DOUBLE_EQ(pid.max(), MAX);
}

TEST_F(TestPID_CondCalc, CanGetMin)
{
    mc::PID_CondCalc pid(KP, KI, KD, MIN, MAX);
    EXPECT_DOUBLE_EQ(pid.min(), MIN);
}

TEST_F(TestPID_CondCalc, CanGetMax)
{
    mc::PID_CondCalc pid(KP, KI, KD, MIN, MAX);
    EXPECT_DOUBLE_EQ(pid.max(), MAX);
}

TEST_F(TestPID_CondCalc, CanSetMin)
{
    mc::PID_CondCalc pid;
    pid.set_min(MIN);
    EXPECT_DOUBLE_EQ(pid.min(), MIN);
}

TEST_F(TestPID_CondCalc, CanSetMax)
{
    mc::PID_CondCalc pid;
    pid.set_max(MAX);
    EXPECT_DOUBLE_EQ(pid.max(), MAX);
}

TEST_F(TestPID_CondCalc, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_pid_antiwindup_conditional.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    mc::PID_CondCalc pid(KP, KI, KD, MIN, MAX);

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = (i < 500) ? 0.0 : 1.0;
        double e = u - y;
        pid.Update(DT, e);
        y = mc::Inertia::Calculate(pid.value(), y, DT, TC);

        EXPECT_NEAR(y, vals.at(i), 1.0e-1);

        t += DT;
    }
}
