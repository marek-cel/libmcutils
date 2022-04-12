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

    std::string lowerCase1 = "ipsumlorem";
    std::string upperCase1 = "IPSUMLOREM";
    std::string camelCase1 = "ipsumLorem";

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
    std::string s1 = "      Lorem ipsum dolor sit amet";
    std::string s2 = mc::String::stripLeadingSpaces( s1 );

    EXPECT_STREQ( s2.c_str(), "Lorem ipsum dolor sit amet" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanStripTrailingSpaces)
{
    std::string s1 = "Lorem ipsum dolor sit amet      ";
    std::string s2 = mc::String::stripTrailingSpaces( s1 );

    EXPECT_STREQ( s2.c_str(), "Lorem ipsum dolor sit amet" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanStripSpaces)
{
    std::string s1 = "      Lorem ipsum dolor sit amet      ";
    std::string s2 = mc::String::stripSpaces( s1 );

    EXPECT_STREQ( s2.c_str(), "Lorem ipsum dolor sit amet" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanConvertToBool)
{
    std::string s0 = "0";
    std::string s1 = "1";
    std::string s2 = "2";

    EXPECT_FALSE( mc::String::toBool( s0 ) );

    EXPECT_TRUE( mc::String::toBool( s1 ) );
    EXPECT_TRUE( mc::String::toBool( s2 ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanConvertToInt)
{
    std::string s0 =  "0";
    std::string s1 =  "1";
    std::string s2 =  "2";
    std::string s3 = "-2";

    EXPECT_EQ(  0, mc::String::toInt( s0 ) );
    EXPECT_EQ(  1, mc::String::toInt( s1 ) );
    EXPECT_EQ(  2, mc::String::toInt( s2 ) );
    EXPECT_EQ( -2, mc::String::toInt( s3 ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanConvertToDouble)
{
    std::string s0 = "0";
    std::string s1 = "1";
    std::string s2 = "3.14";
    std::string s3 = "-2.1";

    EXPECT_DOUBLE_EQ(  0.0  , mc::String::toDouble( s0 ) );
    EXPECT_DOUBLE_EQ(  1.0  , mc::String::toDouble( s1 ) );
    EXPECT_DOUBLE_EQ(  3.14 , mc::String::toDouble( s2 ) );
    EXPECT_DOUBLE_EQ( -2.1  , mc::String::toDouble( s3 ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanConvertIntToString)
{
    int v0 =  0;
    int v1 =  1;
    int v2 =  2;
    int v3 = -2;

    EXPECT_STREQ(  "0" , mc::String::toString( v0 ).c_str() );
    EXPECT_STREQ(  "1" , mc::String::toString( v1 ).c_str() );
    EXPECT_STREQ(  "2" , mc::String::toString( v2 ).c_str() );
    EXPECT_STREQ( "-2" , mc::String::toString( v3 ).c_str() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanConvertFloatToString)
{
    float v0 =  0.0f;
    float v1 =  1.0f;
    float v2 =  3.14f;
    float v3 = -2.1f;

    EXPECT_STREQ(  "0"    , mc::String::toString( v0 ).c_str() );
    EXPECT_STREQ(  "1"    , mc::String::toString( v1 ).c_str() );
    EXPECT_STREQ(  "3.14" , mc::String::toString( v2 ).c_str() );
    EXPECT_STREQ( "-2.1"  , mc::String::toString( v3 ).c_str() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanConvertDoubleToString)
{
    double v0 =  0.0;
    double v1 =  1.0;
    double v2 =  3.14;
    double v3 = -2.1;

    EXPECT_STREQ(  "0"    , mc::String::toString( v0 ).c_str() );
    EXPECT_STREQ(  "1"    , mc::String::toString( v1 ).c_str() );
    EXPECT_STREQ(  "3.14" , mc::String::toString( v2 ).c_str() );
    EXPECT_STREQ( "-2.1"  , mc::String::toString( v3 ).c_str() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanConvertToLowerCase)
{
    std::string s1 = "LOREM IPSUM DOLOR SIT AMET";
    std::string s2 = mc::String::toLower( s1 );

    EXPECT_STREQ( s2.c_str(), "lorem ipsum dolor sit amet" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestString, CanConvertToUpperCase)
{
    std::string s1 = "lorem ipsum dolor sit amet";
    std::string s2 = mc::String::toUpper( s1 );

    EXPECT_STREQ( s2.c_str(), "LOREM IPSUM DOLOR SIT AMET" );
}
