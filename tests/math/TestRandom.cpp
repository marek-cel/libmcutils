#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////

class TestRandom : public ::testing::Test
{
protected:
    TestRandom() {}
    virtual ~TestRandom() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestRandom, ExpectTrue)
{
    EXPECT_TRUE(true);
}
