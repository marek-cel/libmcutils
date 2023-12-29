#include <gtest/gtest.h>

#include <mcutils/misc/PtrUtils.h>

class TestPtrUtils : public ::testing::Test
{
protected:

    TestPtrUtils() {}
    virtual ~TestPtrUtils() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestPtrUtils, CanDelPtrNull)
{
    double* ptr = nullptr;
    EXPECT_NO_THROW(mc::deletePtr(ptr));
}

TEST_F(TestPtrUtils, CanDelPtr)
{
    double* ptr = new double;
    EXPECT_NO_THROW(mc::deletePtr(ptr));
    EXPECT_TRUE(ptr == nullptr);
}

TEST_F(TestPtrUtils, CanDelPtrArrayNull)
{
    double* ptr = nullptr;
    EXPECT_NO_THROW(mc::deleteArrayPtr(ptr));
}

TEST_F(TestPtrUtils, CanDelArrayPtr)
{
    double* ptr = new double [10];
    EXPECT_NO_THROW(mc::deleteArrayPtr(ptr));
    EXPECT_TRUE(ptr == nullptr);
}
