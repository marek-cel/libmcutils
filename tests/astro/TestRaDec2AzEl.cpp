#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/astro/Utils.h>
#include <mcutils/misc/Units.h>

class TestRaDec2AzEl : public ::testing::Test
{
protected:
    TestRaDec2AzEl() {}
    virtual ~TestRaDec2AzEl() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestRaDec2AzEl, CanComputeAzElFromRaDecLatAndLST1)
{
    // TODO
}
