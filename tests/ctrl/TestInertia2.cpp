#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/Inertia2.h>

#include <CsvFileReader.h>
#include <XcosBinFileReader.h>

class TestInertia2 : public ::testing::Test
{
protected:

    static constexpr units::time::second_t TIME_STEP = 0.01_s;

    static constexpr units::time::second_t TIME_CONSTANT_1 = 2.0_s;
    static constexpr units::time::second_t TIME_CONSTANT_2 = 3.0_s;

    TestInertia2() {}
    virtual ~TestInertia2() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestInertia2, CanInstantiate)
{
    mc::Inertia2<double> inertia;

    EXPECT_DOUBLE_EQ(inertia.time_const_1()(), 0.0);
    EXPECT_DOUBLE_EQ(inertia.time_const_2()(), 0.0);
    EXPECT_DOUBLE_EQ(inertia.value(), 0.0);
}

TEST_F(TestInertia2, CanInstantiateAndSetData)
{
    mc::Inertia2<double> inertia(2.0_s, 3.0_s, 4.0);

    EXPECT_DOUBLE_EQ(inertia.time_const_1()(), 2.0);
    EXPECT_DOUBLE_EQ(inertia.time_const_2()(), 3.0);
    EXPECT_DOUBLE_EQ(inertia.value(), 4.0);
}

TEST_F(TestInertia2, CanUpdateStep)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lag2.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_inertia2_step.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::Inertia2<double> inertia(TIME_CONSTANT_1, TIME_CONSTANT_2);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = (i < 101) ? 0.0 : 1.0;

        inertia.Update(TIME_STEP, u);
        y = inertia.value();

        double tolerance = std::max(1.0e-3, 1.0e-3 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}

TEST_F(TestInertia2, CanUpdateStep2)
{
    std::vector<double> t_ref;
    std::vector<double> y_ref;

    // expected values calculated with GNU Octave
    // tests/control/octave/test_lag2.m
    ReadCsvDataFromFile("../tests/ctrl/data/test_inertia2_step.csv", &t_ref, &y_ref);

    EXPECT_GT(t_ref.size(), 0) << "No reference data.";
    EXPECT_GT(y_ref.size(), 0) << "No reference data.";
    EXPECT_EQ(t_ref.size(), y_ref.size()) << "Reference data corrupted.";

    mc::Inertia2<double> inertia(TIME_CONSTANT_1, TIME_CONSTANT_2);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < y_ref.size(); i++ )
    {
        double u = ( i == 0 ) ? 0.0 : 1.0;
        inertia.Update(TIME_STEP, u);
        y = inertia.value();
        EXPECT_NEAR(y, y_ref.at(i), 5.0e-3) << "Mismatch at time= " << t;

        t += TIME_STEP;
    }
}

TEST_F(TestInertia2, CanUpdateSine)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/control/xcos/test_lag2.xcos
    XcosBinFileReader::ReadData("../tests/ctrl/data/test_inertia2_sine.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    mc::Inertia2<double> inertia(TIME_CONSTANT_1, TIME_CONSTANT_2);

    units::time::second_t t = 0.0_s;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = sin(t() + TIME_STEP());

        inertia.Update(TIME_STEP, u);
        y = inertia.value();

        double tolerance = std::max(1.0e-2, 1.0e-2 * vals.at(i));
        EXPECT_NEAR(y, vals.at(i), tolerance) << "Error at index " << i;

        t += TIME_STEP;
    }
}

TEST_F(TestInertia2, CanGetTimeConst1)
{
    mc::Inertia2<double> inertia(2.0_s, 3.0_s, 4.0);
    EXPECT_DOUBLE_EQ(inertia.time_const_1()(), 2.0);
}

TEST_F(TestInertia2, CanGetTimeConst2)
{
    mc::Inertia2<double> inertia(2.0_s, 3.0_s, 4.0);
    EXPECT_DOUBLE_EQ(inertia.time_const_2()(), 3.0);
}

TEST_F(TestInertia2, CanGetValue)
{
    mc::Inertia2<double> inertia(2.0_s, 3.0_s, 4.0);
    EXPECT_DOUBLE_EQ(inertia.value(), 4.0);
}

TEST_F(TestInertia2, CanSetTimeConst1)
{
    mc::Inertia2<double> inertia;
    inertia.set_time_const_1(2.0_s);
    EXPECT_DOUBLE_EQ(inertia.time_const_1()(), 2.0);
}

TEST_F(TestInertia2, CanSetTimeConst2)
{
    mc::Inertia2<double> inertia;
    inertia.set_time_const_2(3.0_s);
    EXPECT_DOUBLE_EQ(inertia.time_const_2()(), 3.0);
}

TEST_F(TestInertia2, CanSetValue)
{
    mc::Inertia2<double> inertia;
    inertia.set_value(4.0);
    EXPECT_DOUBLE_EQ(inertia.value(), 4.0);
}
