#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/AWBackCalc.h>
#include <mcutils/ctrl/Inertia.h>
#include <mcutils/ctrl/PID.h>

#include <XcosBinFileReader.h>

class TestAWBackCalc : public ::testing::Test
{
protected:

    static constexpr double DT { 0.01 };

    static constexpr double TC { 5.0 };
    static constexpr double KP { 5.0 };
    static constexpr double KI { 0.5 };
    static constexpr double KD { 0.1 };

    static constexpr double MIN { -0.5 };
    static constexpr double MAX {  0.5 };

    TestAWBackCalc() {}
    virtual ~TestAWBackCalc() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestAWBackCalc, CanConstruct)
{
    mc::AWBackCalc* aw = nullptr;
    EXPECT_NO_THROW(aw = new mc::AWBackCalc());
    delete aw;
}

TEST_F(TestAWBackCalc, CanDestruct)
{
    mc::AWBackCalc* aw = new mc::AWBackCalc();
    EXPECT_NO_THROW(delete aw);
}

TEST_F(TestAWBackCalc, CanInstantiate)
{
    mc::AWBackCalc aw;

    EXPECT_DOUBLE_EQ(aw.min(), DBL_MIN);
    EXPECT_DOUBLE_EQ(aw.max(), DBL_MAX);
}

TEST_F(TestAWBackCalc, CanInstantiateAndSetData)
{
    mc::AWBackCalc aw(MIN, MAX);

    EXPECT_DOUBLE_EQ(aw.min(), MIN);
    EXPECT_DOUBLE_EQ(aw.max(), MAX);
}

TEST_F(TestAWBackCalc, CanGetMin)
{
    mc::AWBackCalc aw(MIN, MAX);
    EXPECT_DOUBLE_EQ(aw.min(), MIN);
}

TEST_F(TestAWBackCalc, CanGetMax)
{
    mc::AWBackCalc aw(MIN, MAX);
    EXPECT_DOUBLE_EQ(aw.max(), MAX);
}

TEST_F(TestAWBackCalc, CanSetMin)
{
    mc::AWBackCalc aw;
    aw.set_min(MIN);
    EXPECT_DOUBLE_EQ(aw.min(), MIN);
}

TEST_F(TestAWBackCalc, CanSetMax)
{
    mc::AWBackCalc aw;
    aw.set_max(MAX);
    EXPECT_DOUBLE_EQ(aw.max(), MAX);
}

TEST_F(TestAWBackCalc, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_pid.xcos
    XcosBinFileReader::ReadData( "../tests/ctrl/data/test_pid_antiwindup_calculation.bin", &vals );

    EXPECT_GT(vals.size(), 0) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    mc::PID pid(KP, KI, KD, std::make_unique<mc::AWBackCalc>(MIN, MAX));

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
