#include <cmath>

#include <gtest/gtest.h>

#include <mcutils/ctrl/StateSpace.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestStateSpace : public ::testing::Test
{
protected:

    TestStateSpace() {}
    virtual ~TestStateSpace() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestStateSpace, CanAssertTrue)
{
    ASSERT_TRUE( true );
}
