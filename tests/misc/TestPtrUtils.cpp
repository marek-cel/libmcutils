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
    EXPECT_NO_THROW(mc::DeletePtr(ptr));
}

TEST_F(TestPtrUtils, CanDelPtr)
{
    double* ptr = new double;
    EXPECT_NO_THROW(mc::DeletePtr(ptr));
    EXPECT_TRUE(ptr == nullptr);
}

TEST_F(TestPtrUtils, CanDelPtrArrayNull)
{
    double* ptr = nullptr;
    EXPECT_NO_THROW(mc::DeletePtrArray(ptr));
}

TEST_F(TestPtrUtils, CanDelPtrArray)
{
    double* ptr = new double [10];
    EXPECT_NO_THROW(mc::DeletePtrArray(ptr));
    EXPECT_TRUE(ptr == nullptr);
}
