#include <gtest/gtest.h>

#include <mcutils/time/ISO8601.h>

////////////////////////////////////////////////////////////////////////////////

class TestISO8601 : public ::testing::Test
{
protected:
    TestISO8601() {}
    virtual ~TestISO8601() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestISO8601, CanConvertToISO8601FromYMDHMSms)
{
    std::string result;

    result = mc::toISO8601( 2001, 02, 03, 14, 15, 16, 123 );
    EXPECT_STREQ( result.c_str(), "2001-02-03T14:15:16.123" );

    result = mc::toISO8601( 2001, 02, 03, 14, 15, 16, 123, true );
    EXPECT_STREQ( result.c_str(), "2001-02-03T14:15:16.123" );

    result = mc::toISO8601( 2001, 02, 03, 14, 15, 16, 123, false );
    EXPECT_STREQ( result.c_str(), "2001-02-03T14:15:16" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestISO8601, CanConvertToISO8601FromYMD)
{
    std::string result;

    result = mc::toISO8601( 2001, 02, 03 );
    EXPECT_STREQ( result.c_str(), "2001-02-03" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestISO8601, CanConvertToISO8601FromHMSms)
{
    std::string result;

    result = mc::toISO8601( 14, 15, 16, 123 );
    EXPECT_STREQ( result.c_str(), "14:15:16.123" );

    result = mc::toISO8601( 14, 15, 16, 123, true );
    EXPECT_STREQ( result.c_str(), "14:15:16.123" );

    result = mc::toISO8601( 14, 15, 16, 123, false );
    EXPECT_STREQ( result.c_str(), "14:15:16" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestISO8601, CanConvertToISO8601FromDateTime)
{
    mc::DateTime dateTime;

    dateTime.year   = 2001;
    dateTime.month  = 02;
    dateTime.day    = 03;
    dateTime.hour   = 14;
    dateTime.minute = 15;
    dateTime.second = 16;
    dateTime.msec   = 123;

    std::string result;

    result = mc::toISO8601( dateTime );
    EXPECT_STREQ( result.c_str(), "2001-02-03T14:15:16.123" );

    result = mc::toISO8601( dateTime, true );
    EXPECT_STREQ( result.c_str(), "2001-02-03T14:15:16.123" );

    result = mc::toISO8601( dateTime, false );
    EXPECT_STREQ( result.c_str(), "2001-02-03T14:15:16" );
}
