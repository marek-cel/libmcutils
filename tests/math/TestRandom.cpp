#include <gtest/gtest.h>

#include <mcutils/math/Random.h>

class TestRandom : public ::testing::Test
{
protected:
    TestRandom() {}
    virtual ~TestRandom() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestRandom, CanGetInt)
{
    int min;
    int max;
    int temp;

    min = -100;
    max =  100;
    temp = mc::Random::Get(min, max);
    EXPECT_GE(temp, min);
    EXPECT_LE(temp, max);

    min = -100;
    max = -50;
    temp = mc::Random::Get(min, max);
    EXPECT_GE(temp, min);
    EXPECT_LE(temp, max);

    min = 50;
    max = 100;
    temp = mc::Random::Get(min, max);
    EXPECT_GE(temp, min);
    EXPECT_LE(temp, max);

    min = 0;
    max = RAND_MAX + 1;
    temp = mc::Random::Get(min, max);
    EXPECT_EQ(temp, 0);
}

TEST_F(TestRandom, CanGetFloat)
{
    float min;
    float max;
    float temp;

    min = -123.4f;
    max =  876.5f;
    temp = mc::Random::Get(min, max);
    EXPECT_GE(temp, min);
    EXPECT_LE(temp, max);

    min = -123.4f;
    max = -12.3f;
    temp = mc::Random::Get(min, max);
    EXPECT_GE(temp, min);
    EXPECT_LE(temp, max);

    min = 12.3f;
    max = 123.4f;
    temp = mc::Random::Get(min, max);
    EXPECT_GE(temp, min);
    EXPECT_LE(temp, max);
}

TEST_F(TestRandom, CanGetDouble)
{
    double min;
    double max;
    double temp;

    min = -123.4;
    max =  876.5;
    temp = mc::Random::Get(min, max);
    EXPECT_GE(temp, min);
    EXPECT_LE(temp, max);

    min = -123.4;
    max = -12.3;
    temp = mc::Random::Get(min, max);
    EXPECT_GE(temp, min);
    EXPECT_LE(temp, max);

    min = 12.3;
    max = 123.4;
    temp = mc::Random::Get(min, max);
    EXPECT_GE(temp, min);
    EXPECT_LE(temp, max);
}
