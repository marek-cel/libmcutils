#include <gtest/gtest.h>

class TestingEnvironment : public ::testing::Environment
{
public:

    ~TestingEnvironment() override {}
    void SetUp() override {}
    void TearDown() override {}
};

