#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////

class TestGeometry : public ::testing::Test
{
protected:
    TestGeometry() {}
    virtual ~TestGeometry() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGeometry, ExpectTrue)
{
    EXPECT_TRUE(true);
}
