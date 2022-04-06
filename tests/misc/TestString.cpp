#include <gtest/gtest.h>

#include <mcutils/misc/String.h>

////////////////////////////////////////////////////////////////////////////////

class TestString : public ::testing::Test
{
protected:

    TestString() {}
    virtual ~TestString() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanGetFirstLine)
{
    std::string l1 = "abc123";
    std::string l2 = "cde456";
    std::string l3 = "fgh789";
    std::string ml = l1 + "\n" + l2 + "\n" + l3 + "\n";
    std::string res = mc::String::getFirstLine( ml );
    EXPECT_TRUE( l1 == res );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanICompare)
{
    std::string lowerCase = "loremipsum";
    std::string upperCase = "LOREMIPSUM";
    std::string camelCase = "loremIpsum";

    EXPECT_EQ( 0, mc::String::icompare( lowerCase, upperCase ) );
    EXPECT_EQ( 0, mc::String::icompare( upperCase, camelCase ) );
    EXPECT_EQ( 0, mc::String::icompare( lowerCase, camelCase ) );

    std::string lowerCase1 = "moremipsum";
    std::string upperCase1 = "mOREMIPSUM";
    std::string camelCase1 = "moremIpsum";

    EXPECT_FALSE( 0 == mc::String::icompare( lowerCase, upperCase1 ) );
    EXPECT_FALSE( 0 == mc::String::icompare( upperCase, camelCase1 ) );
    EXPECT_FALSE( 0 == mc::String::icompare( lowerCase, camelCase1 ) );
}
