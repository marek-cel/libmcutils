#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/Inertia.h>
#include <mcutils/ctrl/PID_BackCalc.h>

#include <XcosBinFileReader.h>

class TestPID_BackCalc : public ::testing::Test
{
protected:

    static constexpr units::time::second_t DT = 0.01_s;
    static constexpr units::time::second_t TC = 5.0_s;

    static constexpr double KP { 5.0 };
    static constexpr double KI { 0.5 };
    static constexpr double KD { 0.1 };

    static constexpr double MIN { -0.5 };
    static constexpr double MAX {  0.5 };

    TestPID_BackCalc() {}
    virtual ~TestPID_BackCalc() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestPID_BackCalc, CanInstantiate)
{
    mc::PID_BackCalc<double> pid;

    EXPECT_DOUBLE_EQ(pid.min(), DBL_MIN);
    EXPECT_DOUBLE_EQ(pid.max(), DBL_MAX);
}

TEST_F(TestPID_BackCalc, CanInstantiateAndSetData)
{
    mc::PID_BackCalc<double> pid(KP, KI, KD, MIN, MAX);

    EXPECT_DOUBLE_EQ(pid.min(), MIN);
    EXPECT_DOUBLE_EQ(pid.max(), MAX);
}

TEST_F(TestPID_BackCalc, CanGetMin)
{
    mc::PID_BackCalc<double> pid(KP, KI, KD, MIN, MAX);
    EXPECT_DOUBLE_EQ(pid.min(), MIN);
}

TEST_F(TestPID_BackCalc, CanGetMax)
{
    mc::PID_BackCalc<double> pid(KP, KI, KD, MIN, MAX);
    EXPECT_DOUBLE_EQ(pid.max(), MAX);
}

TEST_F(TestPID_BackCalc, CanSetMin)
{
    mc::PID_BackCalc<double> pid;
    pid.set_min(MIN);
    EXPECT_DOUBLE_EQ(pid.min(), MIN);
}

TEST_F(TestPID_BackCalc, CanSetMax)
{
    mc::PID_BackCalc<double> pid;
    pid.set_max(MAX);
    EXPECT_DOUBLE_EQ(pid.max(), MAX);
}

TEST_F(TestPID_BackCalc, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_pid_antiwindup_calculation.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    mc::PID_BackCalc<double> pid(KP, KI, KD, MIN, MAX);

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = (i < 500) ? 0.0 : 1.0;
        double e = u - y;
        pid.Update(DT, e);
        y = mc::Inertia<double>::Calculate(DT, TC, pid.value(), y);

        EXPECT_NEAR(y, vals.at(i), 1.0e-1);

        t += DT;
    }
}
