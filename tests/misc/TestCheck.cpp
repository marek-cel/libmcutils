#include <gtest/gtest.h>

#include <limits>

#include <mcutils/misc/Check.h>

class TestCheck : public ::testing::Test
{
protected:

    TestCheck() {}
    virtual ~TestCheck() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestCheck, CanCheckIfIsInf)
{
    double zero = 0.0;

    EXPECT_FALSE(mc::IsInf(0.0));
    EXPECT_FALSE(mc::IsInf(DBL_MIN));
    EXPECT_FALSE(mc::IsInf(DBL_MAX));
    EXPECT_FALSE(mc::IsInf(std::numeric_limits<double>::min()));
    EXPECT_FALSE(mc::IsInf(std::numeric_limits<double>::max()));

    EXPECT_TRUE(mc::IsInf(std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(mc::IsInf(1.0 / zero));
}

TEST_F(TestCheck, CanCheckIfIsNaN)
{
    EXPECT_FALSE(mc::IsNaN(0.0));
    EXPECT_FALSE(mc::IsNaN(DBL_MIN));
    EXPECT_FALSE(mc::IsNaN(DBL_MAX));
    EXPECT_FALSE(mc::IsNaN(std::numeric_limits<double>::min()));
    EXPECT_FALSE(mc::IsNaN(std::numeric_limits<double>::max()));

    EXPECT_TRUE(mc::IsNaN(std::numeric_limits<double>::quiet_NaN()));
}

TEST_F(TestCheck, CanCheckIfIsValid)
{
    double zero = 0.0;

    EXPECT_TRUE(mc::IsValid(0.0));
    EXPECT_TRUE(mc::IsValid(DBL_MIN));
    EXPECT_TRUE(mc::IsValid(DBL_MAX));
    EXPECT_TRUE(mc::IsValid(std::numeric_limits<double>::min()));
    EXPECT_TRUE(mc::IsValid(std::numeric_limits<double>::max()));

    EXPECT_FALSE(mc::IsValid(std::numeric_limits<double>::quiet_NaN()));
    EXPECT_FALSE(mc::IsValid(std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(mc::IsValid(1.0 / zero));
}

TEST_F(TestCheck, CanCheckIfIsValidArray)
{
    double zero = 0.0;

    double a1[] = { 0.0, 1.0, 2.0 };
    EXPECT_TRUE(mc::IsValid(a1, 3));

    double a2[] = { 0.0, 1.0, DBL_MIN };
    EXPECT_TRUE(mc::IsValid(a2, 3));

    double a3[] = { 0.0, 1.0, DBL_MAX };
    EXPECT_TRUE(mc::IsValid(a3, 3));

    double a4[] = { 0.0, 1.0, std::numeric_limits<double>::min() };
    EXPECT_TRUE(mc::IsValid(a4, 3));

    double a5[] = { 0.0, 1.0, std::numeric_limits<double>::max() };
    EXPECT_TRUE(mc::IsValid(a5, 3));

    double a6[] = { 0.0, 1.0, std::numeric_limits<double>::quiet_NaN() };
    EXPECT_FALSE(mc::IsValid(a6, 3));

    double a7[] = { 0.0, 1.0, std::numeric_limits<double>::infinity() };
    EXPECT_FALSE(mc::IsValid(a7, 3));

    double a8[] = { 0.0, 1.0, 1.0 / zero };
    EXPECT_FALSE(mc::IsValid(a8, 3));
}
