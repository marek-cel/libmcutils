#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/System2.h>

#include <XcosBinFileReader.h>

using namespace units::literals;

class TestSystem2 : public ::testing::Test
{
protected:

    static constexpr units::time::second_t TIME_STEP = 0.01_s;

    TestSystem2() {}
    virtual ~TestSystem2() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestSystem2, CanInstantiate)
{
    mc::System2<double> s;

    EXPECT_DOUBLE_EQ(s.c1(), 0.0);
    EXPECT_DOUBLE_EQ(s.c2(), 0.0);
    EXPECT_DOUBLE_EQ(s.c3(), 1.0);
    EXPECT_DOUBLE_EQ(s.c4(), 0.0);
    EXPECT_DOUBLE_EQ(s.c5(), 0.0);
    EXPECT_DOUBLE_EQ(s.c6(), 1.0);

    EXPECT_DOUBLE_EQ(s.value(), 0.0);
}

TEST_F(TestSystem2, CanInstantiateAndSetData)
{
    mc::System2<double> s(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0);

    EXPECT_DOUBLE_EQ(s.c1(), 1.0);
    EXPECT_DOUBLE_EQ(s.c2(), 2.0);
    EXPECT_DOUBLE_EQ(s.c3(), 3.0);
    EXPECT_DOUBLE_EQ(s.c4(), 4.0);
    EXPECT_DOUBLE_EQ(s.c5(), 5.0);
    EXPECT_DOUBLE_EQ(s.c6(), 6.0);

    EXPECT_DOUBLE_EQ(s.value(), 99.0);
}

TEST_F(TestSystem2, CanUpdateOscillatorStep)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_filter2.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_oscillator_step.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    // harmonic oscillator
    // G(s) = omega_0^2 / ( s^2 + 2*xi*omega_0*s + omega_0^2 )
    // G(s) = 2^2 / [ s^2 + 2*(1/50)*2*s + 2^2 ]
    mc::System2<double> s(0.0, 0.0, 4.0, 1.0, 2.0*(1.0/50)*2.0, 4.0);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = (i < 100) ? 0.0 : 1.0;

        s.Update(TIME_STEP, u);
        y = s.value();

        double tolerance = std::max(1.0e-2, 1.0e-2 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}

TEST_F(TestSystem2, CanUpdateOscillatorSine)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_filter2.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_oscillator_sine.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    // harmonic oscillator
    // G(s) = omega_0^2 / ( s^2 + 2*xi*omega_0*s + omega_0^2 )
    // G(s) = 2^2 / [ s^2 + 2*(1/50)*2*s + 2^2 ]
    mc::System2<double> s(0.0, 0.0, 4.0, 1.0, 2.0*(1.0/50)*2.0, 4.0);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = sin(t());

        s.Update(TIME_STEP, u);
        y = s.value();

        double tolerance = std::max(1.0e-2, 1.0e-2 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}

TEST_F(TestSystem2, CanGetC1)
{
    mc::System2<double> s(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0);
    EXPECT_DOUBLE_EQ(s.c1(), 1.0);
}

TEST_F(TestSystem2, CanGetC2)
{
    mc::System2<double> s(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0);
    EXPECT_DOUBLE_EQ(s.c2(), 2.0);
}

TEST_F(TestSystem2, CanGetC3)
{
    mc::System2<double> s(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0);
    EXPECT_DOUBLE_EQ(s.c3(), 3.0);
}

TEST_F(TestSystem2, CanGetC4)
{
    mc::System2<double> s(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0);
    EXPECT_DOUBLE_EQ(s.c4(), 4.0);
}

TEST_F(TestSystem2, CanGetC5)
{
    mc::System2<double> s(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0);
    EXPECT_DOUBLE_EQ(s.c5(), 5.0);
}

TEST_F(TestSystem2, CanGetC6)
{
    mc::System2<double> s(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0);
    EXPECT_DOUBLE_EQ(s.c6(), 6.0);
}

TEST_F(TestSystem2, CanGetValue)
{
    mc::System2<double> s(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0);
    EXPECT_DOUBLE_EQ(s.value(), 99.0);
}

TEST_F(TestSystem2, CanSetC1)
{
    mc::System2<double> s;
    s.set_c1(1.0);
    EXPECT_DOUBLE_EQ(s.c1(), 1.0);
}

TEST_F(TestSystem2, CanSetC2)
{
    mc::System2<double> s;
    s.set_c2(2.0);
    EXPECT_DOUBLE_EQ(s.c2(), 2.0);
}

TEST_F(TestSystem2, CanSetC3)
{
    mc::System2<double> s;
    s.set_c3(3.0);
    EXPECT_DOUBLE_EQ(s.c3(), 3.0);
}

TEST_F(TestSystem2, CanSetC4)
{
    mc::System2<double> s;
    s.set_c4(4.0);
    EXPECT_DOUBLE_EQ(s.c4(), 4.0);
}

TEST_F(TestSystem2, CanSetC5)
{
    mc::System2<double> s;
    s.set_c5(5.0);
    EXPECT_DOUBLE_EQ(s.c5(), 5.0);
}

TEST_F(TestSystem2, CanSetC6)
{
    mc::System2<double> s;
    s.set_c6(6.0);
    EXPECT_DOUBLE_EQ(s.c6(), 6.0);
}

TEST_F(TestSystem2, CanSetValue)
{
    mc::System2<double> s;
    s.set_value(99.0);
    EXPECT_DOUBLE_EQ(s.value(), 99.0);
}
