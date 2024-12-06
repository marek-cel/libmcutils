#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/Oscillator.h>

#include <XcosBinFileReader.h>

class TestOscillator : public ::testing::Test
{
protected:

    static constexpr units::time::second_t TIME_STEP = 0.01_s;

    static constexpr units::angular_velocity::radians_per_second_t OMEGA = 2.0_rad_per_s;
    static constexpr double ZETA  { 1.0/50.0 };

    TestOscillator() {}
    virtual ~TestOscillator() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestOscillator, CanInstantiate)
{
    mc::Oscillator<double> oscillator;

    EXPECT_DOUBLE_EQ(oscillator.omega()(), 2.0 * M_PI);

    EXPECT_DOUBLE_EQ(oscillator.zeta()  , 1.0);
    EXPECT_DOUBLE_EQ(oscillator.value() , 0.0);
}

TEST_F(TestOscillator, CanInstantiateAndSetData)
{
    mc::Oscillator<double> oscillator(2.0_rad_per_s, 0.5, 4.0);

    EXPECT_DOUBLE_EQ(oscillator.omega()(), 2.0);

    EXPECT_DOUBLE_EQ(oscillator.zeta()  , 0.5);
    EXPECT_DOUBLE_EQ(oscillator.value() , 4.0);

    mc::Oscillator<double> oscillator2(2.0_rad_per_s, 2.0, 4.0);
    EXPECT_DOUBLE_EQ(oscillator2.zeta()  , 1.0); // zeta is clamped to <0.0;1.0>

    mc::Oscillator<double> oscillator3(2.0_rad_per_s, -1.0, 4.0);
    EXPECT_DOUBLE_EQ(oscillator3.zeta()  , 0.0); // zeta is clamped to <0.0;1.0>
}

TEST_F(TestOscillator, CanUpdateStep)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_oscillator.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_oscillator_step.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::Oscillator<double> oscillator(OMEGA, ZETA);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 100 ) ? 0.0 : 1.0;

        oscillator.Update(TIME_STEP, u);
        y = oscillator.value();

        double tolerance = std::max(1.0e-2, 1.0e-2 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}

TEST_F(TestOscillator, CanUpdateSine)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_oscillator.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_oscillator_sine.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::Oscillator<double> oscillator(OMEGA, ZETA);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for (unsigned int i = 0; i < vals.size(); i++)
    {
        double u = sin(t());

        oscillator.Update(TIME_STEP, u);
        y = oscillator.value();

        double tolerance = std::max(1.0e-2, 1.0e-2 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}

TEST_F(TestOscillator, CanGetOmega)
{
    mc::Oscillator<double> oscillator(2.0_rad_per_s, 0.5, 4.0);
    EXPECT_DOUBLE_EQ(oscillator.omega()(), 2.0);
}

TEST_F(TestOscillator, CanGetZeta)
{
    mc::Oscillator<double> oscillator(2.0_rad_per_s, 0.5, 4.0);
    EXPECT_DOUBLE_EQ(oscillator.zeta(), 0.5);
}

TEST_F(TestOscillator, CanGetValue)
{
    mc::Oscillator<double> oscillator(2.0_rad_per_s, 0.5, 4.0);
    EXPECT_DOUBLE_EQ(oscillator.value(), 4.0);
}

TEST_F(TestOscillator, CanSetOmega)
{
    mc::Oscillator<double> oscillator;

    oscillator.set_omega(2.0_rad_per_s);
    EXPECT_DOUBLE_EQ(oscillator.omega()(), 2.0);

    oscillator.set_omega(-1.0_rad_per_s);
    EXPECT_DOUBLE_EQ(oscillator.omega()(), 0.0);
}

TEST_F(TestOscillator, CanSetDamping)
{
    mc::Oscillator<double> oscillator;

    oscillator.set_zeta(2.0);
    EXPECT_DOUBLE_EQ(oscillator.zeta(), 1.0); // zeta is clamped to <0.0;1.0>

    oscillator.set_zeta(-1.0);
    EXPECT_DOUBLE_EQ(oscillator.zeta(), 0.0); // zeta is clamped to <0.0;1.0>

    oscillator.set_zeta(0.5);
    EXPECT_DOUBLE_EQ(oscillator.zeta(), 0.5);
}

TEST_F(TestOscillator, CanSetValue)
{
    mc::Oscillator<double> oscillator;
    oscillator.set_value(3.0);
    EXPECT_DOUBLE_EQ(oscillator.value(), 3.0);
}
