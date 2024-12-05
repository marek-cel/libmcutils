#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/ZeroOrderHold.h>

#include <CsvFileReader.h>
#include <XcosBinFileReader.h>

using namespace units::literals;

class TestZeroOrderHold : public ::testing::Test
{
protected:

    static constexpr units::time::second_t TIME_STEP = 0.01_s;
    static constexpr units::time::second_t TIME_HOLD = 0.5_s;

    TestZeroOrderHold() {}
    virtual ~TestZeroOrderHold() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestZeroOrderHold, CanInstantiate)
{
    mc::ZeroOrderHold<double> zho;
    EXPECT_DOUBLE_EQ(zho.t_hold()(), 0.0);
    EXPECT_DOUBLE_EQ(zho.value(), 0.0);
}

TEST_F(TestZeroOrderHold, CanInstantiateAndSetData)
{
    mc::ZeroOrderHold<double> zho(2.0_s, 3.0);
    EXPECT_DOUBLE_EQ(zho.t_hold()(), 2.0);
    EXPECT_DOUBLE_EQ(zho.value(), 3.0);
}

TEST_F(TestZeroOrderHold, CanGetValue)
{
    mc::ZeroOrderHold<double> zho(2.0_s, 3.0);
    EXPECT_DOUBLE_EQ(zho.value(), 3.0);
}

TEST_F(TestZeroOrderHold, CanSetValue)
{
    mc::ZeroOrderHold<double> zho;
    zho.set_value(1.0);
    EXPECT_DOUBLE_EQ(zho.value(), 1.0);
}

TEST_F(TestZeroOrderHold, CanGetTimeHold)
{
    mc::ZeroOrderHold<double> zho(2.0_s);
    EXPECT_DOUBLE_EQ(zho.t_hold()(), 2.0);
}

TEST_F(TestZeroOrderHold, CanSetTimeHold)
{
    mc::ZeroOrderHold<double> zho;

    zho.set_t_hold(2.0_s);
    EXPECT_DOUBLE_EQ(zho.t_hold()(), 2.0);
}

TEST_F(TestZeroOrderHold, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_zero_order_hold.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_zero_order_hold.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::ZeroOrderHold<double> zho(TIME_HOLD);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size() - 1; i++ )
    {
        double u = sin(t() + TIME_STEP());

        zho.Update(TIME_STEP, u);
        y = zho.value();

        double tolerance = std::max(1.0e-3, 1.0e-3 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i+1), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}
