#include <gtest/gtest.h>

#include <mcutils/misc/MapUtils.h>

class TestMapUtils : public ::testing::Test
{
protected:

    TestMapUtils() {}
    virtual ~TestMapUtils() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMapUtils, CanAddMapItem)
{
    std::map<int,double> map;
    EXPECT_EQ(mc::AddMapItem(&map, 0, 3.14), mc::Result::Success);
}

TEST_F(TestMapUtils, CanGetMapItem)
{
    std::map<int,double> map;
    mc::AddMapItem(&map, 0, 3.14);
    EXPECT_DOUBLE_EQ(mc::GetMapItemByKey(&map, 0), 3.14);
    EXPECT_NO_THROW(mc::GetMapItemByKey(&map, 1));
}
