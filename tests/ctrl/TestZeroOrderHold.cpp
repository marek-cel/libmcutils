#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/ZeroOrderHold.h>

#include <CsvFileReader.h>
#include <XcosBinFileReader.h>

class TestZeroOrderHold : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP { 0.01 };
    static constexpr double TIME_HOLD { 0.5 };

    TestZeroOrderHold() {}
    virtual ~TestZeroOrderHold() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestZeroOrderHold, CanConstruct)
{
    mc::ZeroOrderHold* zho = nullptr;
    EXPECT_NO_THROW(zho = new mc::ZeroOrderHold());
    delete zho;
}

TEST_F(TestZeroOrderHold, CanDestruct)
{
    mc::ZeroOrderHold* zho = new mc::ZeroOrderHold();
    EXPECT_NO_THROW(delete zho);
}

TEST_F(TestZeroOrderHold, CanInstantiate)
{
    mc::ZeroOrderHold zho;
    EXPECT_DOUBLE_EQ(zho.t_hold(), 0.0);
    EXPECT_DOUBLE_EQ(zho.value(), 0.0);
}

TEST_F(TestZeroOrderHold, CanInstantiateAndSetData)
{
    mc::ZeroOrderHold zho(2.0, 3.0);
    EXPECT_DOUBLE_EQ(zho.t_hold(), 2.0);
    EXPECT_DOUBLE_EQ(zho.value(), 3.0);
}

TEST_F(TestZeroOrderHold, CanGetValue)
{
    mc::ZeroOrderHold zho(2.0, 3.0);
    EXPECT_DOUBLE_EQ(zho.value(), 3.0);
}

TEST_F(TestZeroOrderHold, CanSetValue)
{
    mc::ZeroOrderHold zho;
    zho.set_value(1.0);
    EXPECT_DOUBLE_EQ(zho.value(), 1.0);
}

TEST_F(TestZeroOrderHold, CanGetTimeHold)
{
    mc::ZeroOrderHold zho(2.0);
    EXPECT_DOUBLE_EQ(zho.t_hold(), 2.0);
}

TEST_F(TestZeroOrderHold, CanSetTimeHold)
{
    mc::ZeroOrderHold zho;

    zho.set_t_hold(2.0);
    EXPECT_DOUBLE_EQ(zho.t_hold(), 2.0);
}

TEST_F(TestZeroOrderHold, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_zero_order_hold.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_zero_order_hold.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::ZeroOrderHold zho(TIME_HOLD);

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size() - 1; i++ )
    {
        double u = sin(t + TIME_STEP);

        zho.Update(TIME_STEP, u);
        y = zho.value();

        double tolerance = std::max(1.0e-3, 1.0e-3 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i+1), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}
