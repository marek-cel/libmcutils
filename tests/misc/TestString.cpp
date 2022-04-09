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
    EXPECT_STREQ( l1.c_str(), res.c_str() );
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

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanSplitString)
{
    std::string s1 = "Lorem ipsum dolor sit amet";
    std::string s2 = "Lorem_ipsum_dolor_sit_amet";

    std::vector<std::string> vs1 = mc::String::splitString( s1, " " );
    std::vector<std::string> vs2 = mc::String::splitString( s2, "_" );

    EXPECT_EQ( 5, vs1.size() );
    EXPECT_EQ( 5, vs2.size() );

    EXPECT_STREQ( vs1[0].c_str(), "Lorem" );
    EXPECT_STREQ( vs1[1].c_str(), "ipsum" );
    EXPECT_STREQ( vs1[2].c_str(), "dolor" );
    EXPECT_STREQ( vs1[3].c_str(), "sit" );
    EXPECT_STREQ( vs1[4].c_str(), "amet" );

    EXPECT_STREQ( vs2[0].c_str(), "Lorem" );
    EXPECT_STREQ( vs2[1].c_str(), "ipsum" );
    EXPECT_STREQ( vs2[2].c_str(), "dolor" );
    EXPECT_STREQ( vs2[3].c_str(), "sit" );
    EXPECT_STREQ( vs2[4].c_str(), "amet" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanStripLeadingSpaces)
{

}
