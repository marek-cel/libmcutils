#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/LeadLag.h>

#include <XcosBinFileReader.h>

using namespace units::literals;

class TestLeadLag : public ::testing::Test
{
protected:

    static constexpr units::time::second_t TIME_STEP = 0.01_s;

    static constexpr double C_1 { 1.0 };
    static constexpr double C_2 { 0.0 };
    static constexpr double C_3 { 1.0 };
    static constexpr double C_4 { 1.0 };

    TestLeadLag() {}
    virtual ~TestLeadLag() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestLeadLag, CanInstantiate)
{
    mc::LeadLag leadLag;

    EXPECT_DOUBLE_EQ(leadLag.c1(), 0.0);
    EXPECT_DOUBLE_EQ(leadLag.c2(), 1.0);
    EXPECT_DOUBLE_EQ(leadLag.c3(), 0.0);
    EXPECT_DOUBLE_EQ(leadLag.c4(), 1.0);
    EXPECT_DOUBLE_EQ(leadLag.value(), 0.0);
}

TEST_F(TestLeadLag, CanInstantiateAndSetData)
{
    mc::LeadLag leadLag(1.0, 2.0, 3.0, 4.0, 99.0);

    EXPECT_DOUBLE_EQ(leadLag.c1(), 1.0);
    EXPECT_DOUBLE_EQ(leadLag.c2(), 2.0);
    EXPECT_DOUBLE_EQ(leadLag.c3(), 3.0);
    EXPECT_DOUBLE_EQ(leadLag.c4(), 4.0);
    EXPECT_DOUBLE_EQ(leadLag.value(), 99.0);
}

TEST_F(TestLeadLag, CanUpdateStep)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lead_lag.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_lead_lag_step.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::LeadLag leadLag(C_1, C_2, C_3, C_4);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( i < 100 ) ? 0.0 : 1.0;

        leadLag.Update(TIME_STEP, u);
        y = leadLag.value();

        double tolerance = std::max(1.0e-2, 1.0e-2 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}

TEST_F(TestLeadLag, CanUpdateSine)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lead_lag.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_lead_lag_sine.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::LeadLag leadLag(C_1, C_2, C_3, C_4);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = sin(t());

        leadLag.Update(TIME_STEP, u);
        y = leadLag.value();

        double tolerance = std::max(1.0e-2, 1.0e-2 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}

TEST_F(TestLeadLag, CanGetC1)
{
    mc::LeadLag leadLag(1.0, 2.0, 3.0, 4.0, 99.0);
    EXPECT_DOUBLE_EQ(leadLag.c1(), 1.0);
}

TEST_F(TestLeadLag, CanGetC2)
{
    mc::LeadLag leadLag(1.0, 2.0, 3.0, 4.0, 99.0);
    EXPECT_DOUBLE_EQ(leadLag.c2(), 2.0);
}

TEST_F(TestLeadLag, CanGetC3)
{
    mc::LeadLag leadLag(1.0, 2.0, 3.0, 4.0, 99.0);
    EXPECT_DOUBLE_EQ(leadLag.c3(), 3.0);
}

TEST_F(TestLeadLag, CanGetC4)
{
    mc::LeadLag leadLag(1.0, 2.0, 3.0, 4.0, 99.0);
    EXPECT_DOUBLE_EQ(leadLag.c4(), 4.0);
}

TEST_F(TestLeadLag, CanGetValue)
{
    mc::LeadLag leadLag(1.0, 2.0, 3.0, 4.0, 99.0);
    EXPECT_DOUBLE_EQ(leadLag.value(), 99.0);
}

TEST_F(TestLeadLag, CanSetC1)
{
    mc::LeadLag leadLag;
    leadLag.set_c1(1.0);
    EXPECT_DOUBLE_EQ(leadLag.c1(), 1.0);
}

TEST_F(TestLeadLag, CanSetC2)
{
    mc::LeadLag leadLag;
    leadLag.set_c2(2.0);
    EXPECT_DOUBLE_EQ(leadLag.c2(), 2.0);
}

TEST_F(TestLeadLag, CanSetC3)
{
    mc::LeadLag leadLag;
    leadLag.set_c3(3.0);
    EXPECT_DOUBLE_EQ(leadLag.c3(), 3.0);
}

TEST_F(TestLeadLag, CanSetC4)
{
    mc::LeadLag leadLag;
    leadLag.set_c4(4.0);
    EXPECT_DOUBLE_EQ(leadLag.c4(), 4.0);
}

TEST_F(TestLeadLag, CanSetValue)
{
    mc::LeadLag leadLag;
    leadLag.set_value(1.0);
    EXPECT_DOUBLE_EQ(leadLag.value(), 1.0);
}
