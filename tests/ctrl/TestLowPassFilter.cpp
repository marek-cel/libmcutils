#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/LowPassFilter.h>

#include <XcosBinFileReader.h>

using namespace units::literals;

class TestLowPassFilter : public ::testing::Test
{
protected:

    static constexpr units::time::second_t TIME_STEP = 0.01_s;
    static constexpr units::angular_velocity::radians_per_second_t OMEGA = 0.5_rad_per_s;

    TestLowPassFilter() {}
    virtual ~TestLowPassFilter() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestLowPassFilter, CanInstantiate)
{
    mc::LowPassFilter<double> lpf;

    EXPECT_DOUBLE_EQ(lpf.omega()(), 2.0 * M_PI);
    EXPECT_DOUBLE_EQ(lpf.value(), 0.0);
}

TEST_F(TestLowPassFilter, CanInstantiateAndSetData)
{
    mc::LowPassFilter<double> lpf(2.0_rad_per_s, 3.0);

    EXPECT_DOUBLE_EQ(lpf.omega()(), 2.0);
    EXPECT_DOUBLE_EQ(lpf.value(), 3.0);
}

TEST_F(TestLowPassFilter, CanSetCutoffFreq)
{
    mc::LowPassFilter<double> lpf;
    lpf.SetCutoffFreq(1.0_Hz);
    EXPECT_DOUBLE_EQ(lpf.omega()(), 2.0 * M_PI);
}

TEST_F(TestLowPassFilter, CanUpdateStep)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lowpassfilter.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_lowpassfilter_step.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::LowPassFilter<double> lpf(OMEGA);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 100 ) ? 0.0 : 1.0;

        lpf.Update(TIME_STEP, u);
        y = lpf.value();

        double tolerance = std::max(1.0e-2, 1.0e-2 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}

TEST_F(TestLowPassFilter, CanUpdateSine)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lowpassfilter.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_lowpassfilter_sine.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::LowPassFilter<double> lpf(OMEGA);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = sin(t());

        lpf.Update(TIME_STEP, u);
        y = lpf.value();

        double tolerance = std::max(1.0e-2, 1.0e-2 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}

TEST_F(TestLowPassFilter, CanGetOmega)
{
    mc::LowPassFilter<double> lpf(2.0_rad_per_s, 3.0);
    EXPECT_DOUBLE_EQ(lpf.omega()(), 2.0);
}

TEST_F(TestLowPassFilter, CanGetValue)
{
    mc::LowPassFilter<double> lpf(2.0_rad_per_s, 3.0);
    EXPECT_DOUBLE_EQ(lpf.value(), 3.0);
}

TEST_F(TestLowPassFilter, CanSetOmega)
{
    mc::LowPassFilter<double> lpf;
    lpf.set_omega(2.0_rad_per_s);
    EXPECT_DOUBLE_EQ(lpf.omega()(), 2.0);
}

TEST_F(TestLowPassFilter, CanSetValue)
{
    mc::LowPassFilter<double> lpf;
    lpf.set_value(3.0);
    EXPECT_DOUBLE_EQ(lpf.value(), 3.0);
}
