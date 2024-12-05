#include <gtest/gtest.h>

#include <mcutils/ctrl/PID.h>
#include <mcutils/ctrl/Inertia.h>

#include <XcosBinFileReader.h>

class TestPID : public ::testing::Test
{
protected:

    static constexpr units::time::second_t DT = 0.01_s;
    static constexpr units::time::second_t TC = 5.0_s;

    static constexpr double KP { 5.0 };
    static constexpr double KI { 0.5 };
    static constexpr double KD { 0.1 };

    TestPID() {}
    virtual ~TestPID() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestPID, CanInstantiate)
{
    mc::PID pid;

    EXPECT_DOUBLE_EQ(pid.kp(), 1.0);
    EXPECT_DOUBLE_EQ(pid.ki(), 0.0);
    EXPECT_DOUBLE_EQ(pid.kd(), 0.0);
}

TEST_F(TestPID, CanInstantiateAndSetData)
{
    mc::PID pid(2.0, 3.0, 4.0);

    EXPECT_DOUBLE_EQ(pid.kp(), 2.0);
    EXPECT_DOUBLE_EQ(pid.ki(), 3.0);
    EXPECT_DOUBLE_EQ(pid.kd(), 4.0);
}

TEST_F(TestPID, CanReset)
{
    mc::PID pid(KP, KI, KD);

    pid.Update(DT, 1.0);
    pid.Update(DT, 2.0);
    pid.Update(DT, 3.0);

    EXPECT_NO_THROW(pid.Reset());
    EXPECT_DOUBLE_EQ(pid.value(), 0.0);
    EXPECT_DOUBLE_EQ(pid.error(), 0.0);
}

TEST_F(TestPID, CanSetAsParallel)
{
    mc::PID pid;

    pid.SetAsParallel(KP, KI, KD);

    EXPECT_DOUBLE_EQ(pid.kp(), KP);
    EXPECT_DOUBLE_EQ(pid.ki(), KI);
    EXPECT_DOUBLE_EQ(pid.kd(), KD);
}

TEST_F(TestPID, CanSetAsSeries)
{
    mc::PID pid;

    pid.SetAsSeries(1.0, 2.0, 3.0);

    // expected values calculated with GNU Octave
    // tests/control/octave/test_pid.m

    EXPECT_DOUBLE_EQ(pid.kp(), 2.5);
    EXPECT_DOUBLE_EQ(pid.ki(), 0.5);
    EXPECT_DOUBLE_EQ(pid.kd(), 3.0);
}

TEST_F(TestPID, CanSetAsStandard)
{
    mc::PID pid;

    pid.SetAsStandard(1.0, 2.0, 3.0);

    // expected values calculated with GNU Octave
    // tests/control/octave/test_pid.m

    EXPECT_DOUBLE_EQ(pid.kp(), 1.0);
    EXPECT_DOUBLE_EQ(pid.ki(), 0.5);
    EXPECT_DOUBLE_EQ(pid.kd(), 3.0);
}

TEST_F(TestPID, CanSetValueAndError)
{
    mc::PID pid(KP, KI, KD);

    EXPECT_NO_THROW(pid.SetValueAndError(6.0, 7.0, 0.1_s));
    EXPECT_DOUBLE_EQ(pid.value(), 6.0);
    EXPECT_DOUBLE_EQ(pid.error(), 7.0);
}

TEST_F(TestPID, CanGetValue)
{
    mc::PID pid(KP, KI, KD);
    pid.set_value(7.0);
    EXPECT_DOUBLE_EQ(pid.value(), 7.0);
}

TEST_F(TestPID, CanGetKp)
{
    mc::PID pid(KP, KI, KD);
    EXPECT_DOUBLE_EQ(pid.kp(), KP);
}

TEST_F(TestPID, CanGetKi)
{
    mc::PID pid(KP, KI, KD);
    EXPECT_DOUBLE_EQ(pid.ki(), KI);
}

TEST_F(TestPID, CanGetKd)
{
    mc::PID pid(KP, KI, KD);
    EXPECT_DOUBLE_EQ(pid.kd(), KD);
}

TEST_F(TestPID, CanSetError)
{
    mc::PID pid(KP, KI, KD);
    EXPECT_NO_THROW(pid.set_error(6.0));
    EXPECT_DOUBLE_EQ(pid.error(), 6.0);
}

TEST_F(TestPID, CanSetValue)
{
    mc::PID pid(KP, KI, KD);
    EXPECT_NO_THROW(pid.set_value(7.0));
    EXPECT_DOUBLE_EQ(pid.value(), 7.0);
}

TEST_F(TestPID, CanSetKp)
{
    mc::PID pid;
    EXPECT_NO_THROW(pid.set_kp(KP));
    EXPECT_DOUBLE_EQ(pid.kp(), KP);
}

TEST_F(TestPID, CanSetKi)
{
    mc::PID pid;
    EXPECT_NO_THROW(pid.set_ki(KI));
    EXPECT_DOUBLE_EQ(pid.ki(), KI);
}

TEST_F(TestPID, CanSetKd)
{
    mc::PID pid;
    EXPECT_NO_THROW(pid.set_kd(KD));
    EXPECT_DOUBLE_EQ(pid.kd(), KD);
}

TEST_F(TestPID, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_pid.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    mc::PID pid(KP, KI, KD);

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
