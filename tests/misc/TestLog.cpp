#include <gtest/gtest.h>

#include <mcutils/misc/Log.h>

////////////////////////////////////////////////////////////////////////////////

class TestLog : public ::testing::Test
{
protected:

    TestLog() {}
    virtual ~TestLog() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanPrintNullStream)
{
    std::string msg = "Lorem ipsum dolor sit amet";

    mc::Log::setOutputStream( nullptr );

    mc::Log::setVerboseLevel( mc::Log::VerboseLevel::Debug );

    EXPECT_NO_THROW( mc::Log::e( msg.c_str() ) );
    EXPECT_NO_THROW( mc::Log::w( msg.c_str() ) );
    EXPECT_NO_THROW( mc::Log::i( msg.c_str() ) );
    EXPECT_NO_THROW( mc::Log::d( msg.c_str() ) );
    EXPECT_NO_THROW( mc::Log::out() << msg );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanPrintFormatedStream)
{
    std::string msg = "lorem";

    std::stringstream ss;
    mc::Log::setOutputStream( &ss );

    std::string result;
    std::string expected;

    mc::Log::setVerboseLevel( mc::Log::VerboseLevel::Debug );

    EXPECT_NO_THROW( mc::Log::e( "aaa %s bbb", msg.c_str() ) );
    result   = ss.str().substr(25);
    expected = "[ERROR] aaa " + msg + " bbb\n";
    EXPECT_TRUE( result == expected );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanPrintErrorMsg)
{
    std::string msg = "Lorem ipsum dolor sit amet";

    std::stringstream ss;
    mc::Log::setOutputStream( &ss );

    std::string result;
    std::string expected;

    mc::Log::setVerboseLevel( mc::Log::VerboseLevel::Error );
    EXPECT_NO_THROW( mc::Log::e( msg.c_str() ) );
    result   = ss.str().substr(25);
    expected = "[ERROR] " + msg + "\n";
    EXPECT_TRUE( result == expected );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanPrintWarningMsg)
{
    std::string msg = "Lorem ipsum dolor sit amet";

    std::stringstream ss;
    mc::Log::setOutputStream( &ss );

    std::string result;
    std::string expected;

    mc::Log::setVerboseLevel( mc::Log::VerboseLevel::Error );
    EXPECT_NO_THROW( mc::Log::w( msg.c_str() ) );
    result   = ss.str();
    expected = "";
    EXPECT_TRUE( result == expected );

    mc::Log::setVerboseLevel( mc::Log::VerboseLevel::Warning );
    EXPECT_NO_THROW( mc::Log::w( msg.c_str() ) );
    result   = ss.str().substr(25);
    expected = "[WARNING] " + msg + "\n";
    EXPECT_TRUE( result == expected );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanPrintInfoMsg)
{
    std::string msg = "Lorem ipsum dolor sit amet";

    std::stringstream ss;
    mc::Log::setOutputStream( &ss );

    std::string result;
    std::string expected;

    mc::Log::setVerboseLevel( mc::Log::VerboseLevel::Warning );
    EXPECT_NO_THROW( mc::Log::i( msg.c_str() ) );
    result   = ss.str();
    expected = "";
    EXPECT_TRUE( result == expected );

    mc::Log::setVerboseLevel( mc::Log::VerboseLevel::Info );
    EXPECT_NO_THROW( mc::Log::i( msg.c_str() ) );
    result   = ss.str().substr(25);
    expected = "[INFO] " + msg + "\n";
    EXPECT_TRUE( result == expected );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanPrintDebugMsg)
{
    std::string msg = "Lorem ipsum dolor sit amet";

    std::stringstream ss;
    mc::Log::setOutputStream( &ss );

    std::string result;
    std::string expected;

    mc::Log::setVerboseLevel( mc::Log::VerboseLevel::Info );
    EXPECT_NO_THROW( mc::Log::d( msg.c_str() ) );
    result   = ss.str();
    expected = "";
    EXPECT_TRUE( result == expected );

    mc::Log::setVerboseLevel( mc::Log::VerboseLevel::Debug );
    EXPECT_NO_THROW( mc::Log::d( msg.c_str() ) );
    result   = ss.str().substr(25);
    expected = "[DEBUG] " + msg + "\n";
    EXPECT_TRUE( result == expected );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanSetOutputStream)
{
    std::stringstream ss;
    EXPECT_NO_THROW( mc::Log::setOutputStream( &ss ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanSetSyslogOutput)
{
    std::stringstream ss;
    EXPECT_NO_THROW( mc::Log::setSyslogOutput( false ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanSetVerboseLevel)
{
    std::stringstream ss;
    EXPECT_NO_THROW( mc::Log::setVerboseLevel( mc::Log::VerboseLevel::Debug ) );
}
