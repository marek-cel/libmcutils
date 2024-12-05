#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/HighPassFilter.h>

#include <XcosBinFileReader.h>

class TestHighPassFilter : public ::testing::Test
{
protected:

    static constexpr units::time::second_t TIME_STEP = 0.01_s;
    static constexpr units::angular_velocity::radians_per_second_t OMEGA = 2.0_rad_per_s;

    TestHighPassFilter() {}
    virtual ~TestHighPassFilter() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestHighPassFilter, CanInstantiate)
{
    mc::HighPassFilter<double> hpf;
    EXPECT_DOUBLE_EQ(hpf.omega()(), 2.0 * M_PI);
    EXPECT_DOUBLE_EQ(hpf.value(), 0.0);
}

TEST_F(TestHighPassFilter, CanInstantiateAndSetData)
{
    mc::HighPassFilter<double> hpf(2.0_rad_per_s, 3.0);
    EXPECT_DOUBLE_EQ(hpf.omega()(), 2.0);
    EXPECT_DOUBLE_EQ(hpf.value(), 3.0);
}

TEST_F(TestHighPassFilter, CanSetCutoffFreq)
{
    mc::HighPassFilter<double> hpf;
    hpf.SetCutoffFreq(2.0_Hz);
    EXPECT_DOUBLE_EQ(hpf.omega()(), 4.0 * M_PI);
}

TEST_F(TestHighPassFilter, CanUpdateStep)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_highpassfilter.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_highpassfilter_step.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::HighPassFilter<double> hpf(OMEGA);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for (unsigned int i = 0; i < vals.size(); i++)
    {
        double u = (i < 100) ? 0.0 : 1.0;

        hpf.Update(TIME_STEP, u);
        y = hpf.value();

        double tolerance = std::max(1.0e-2, 1.0e-2 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}

TEST_F(TestHighPassFilter, CanUpdateSine)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_highpassfilter.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_highpassfilter_sine.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::HighPassFilter<double> hpf(OMEGA);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = sin(t());

        hpf.Update(TIME_STEP, u);
        y = hpf.value();

        double tolerance = std::max(1.0e-2, 1.0e-2 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}

TEST_F(TestHighPassFilter, CanGetOmega)
{
    mc::HighPassFilter<double> hpf(2.0_rad_per_s, 3.0);
    EXPECT_DOUBLE_EQ(hpf.omega()(), 2.0);
}

TEST_F(TestHighPassFilter, CanGetValue)
{
    mc::HighPassFilter<double> hpf(2.0_rad_per_s, 3.0);
    EXPECT_DOUBLE_EQ(hpf.value(), 3.0);
}

TEST_F(TestHighPassFilter, CanSetOmega)
{
    mc::HighPassFilter<double> hpf;
    hpf.set_omega(2.0_rad_per_s);
    EXPECT_DOUBLE_EQ(hpf.omega()(), 2.0);
}

TEST_F(TestHighPassFilter, CanSetValue)
{
    mc::HighPassFilter<double> hpf;
    hpf.set_value(3.0);
    EXPECT_DOUBLE_EQ(hpf.value(), 3.0);
}
