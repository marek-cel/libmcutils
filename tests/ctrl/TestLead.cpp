#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/Lead.h>

#include <XcosBinFileReader.h>

using namespace units::literals;

class TestLead : public ::testing::Test
{
protected:

    static constexpr units::time::second_t TIME_STEP = 0.01_s;

    static constexpr double TIME_CONSTANT { 0.3 };

    TestLead() {}
    virtual ~TestLead() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestLead, CanInstantiate)
{
    mc::Lead lead;

    EXPECT_DOUBLE_EQ(lead.time_const(), 0.0);
    EXPECT_DOUBLE_EQ(lead.value(), 0.0);
}

TEST_F(TestLead, CanInstantiateAndSetData)
{
    mc::Lead lead(2.0, 3.0);

    EXPECT_DOUBLE_EQ(lead.time_const(), 2.0);
    EXPECT_DOUBLE_EQ(lead.value(), 3.0);
}

TEST_F(TestLead, CanUpdateSine)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lead.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_lead_sine.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::Lead lead(TIME_CONSTANT);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = sin(t());

        lead.Update(TIME_STEP, u);
        y = lead.value();

        double tolerance = std::max(1.0e-2, 1.0e-2 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }

}

TEST_F(TestLead, CanGetValue)
{
    mc::Lead lead(2.0, 3.0);

    EXPECT_DOUBLE_EQ(lead.value(), 3.0);
}

TEST_F(TestLead, CanSetValue)
{
    mc::Lead lead;

    lead.set_value(1.0);
    EXPECT_DOUBLE_EQ(lead.value(), 1.0);
}

TEST_F(TestLead, CanGetTimeConst)
{
    mc::Lead lead(2.0, 3.0);

    EXPECT_DOUBLE_EQ(lead.time_const(), 2.0);
}

TEST_F(TestLead, CanSetTimeConst)
{
    mc::Lead lead;

    lead.set_time_const(2.0);
    EXPECT_DOUBLE_EQ(lead.time_const(), 2.0);
}
