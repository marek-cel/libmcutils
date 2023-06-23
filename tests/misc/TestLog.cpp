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

    mc::Log::set_out_stream(nullptr);

    mc::Log::set_verb_level(mc::Log::VerboseLevel::Debug);

    EXPECT_NO_THROW( mc::Log::Error(msg.c_str()) );
    EXPECT_NO_THROW( mc::Log::Warning(msg.c_str()) );
    EXPECT_NO_THROW( mc::Log::Info(msg.c_str()) );
    EXPECT_NO_THROW( mc::Log::Debug(msg.c_str()) );
    EXPECT_NO_THROW( mc::Log::Out() << msg );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanPrintFormatedStream)
{
    std::string msg = "lorem";

    std::stringstream ss;
    mc::Log::set_out_stream(&ss);

    std::string result;
    std::string expected;

    mc::Log::set_verb_level(mc::Log::VerboseLevel::Debug);

    EXPECT_NO_THROW( mc::Log::Error("aaa %s bbb", msg.c_str()) );
    result   = ss.str().substr(25);
    expected = "[ERROR] aaa " + msg + " bbb\n";
    EXPECT_TRUE( result == expected );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanPrintErrorMsg)
{
    std::string msg = "Lorem ipsum dolor sit amet";

    std::stringstream ss;
    mc::Log::set_out_stream(&ss);

    std::string result;
    std::string expected;

    mc::Log::set_verb_level(mc::Log::VerboseLevel::Error);
    EXPECT_NO_THROW( mc::Log::Error(msg.c_str()) );
    result   = ss.str().substr(25);
    expected = "[ERROR] " + msg + "\n";
    EXPECT_TRUE( result == expected );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanPrintWarningMsg)
{
    std::string msg = "Lorem ipsum dolor sit amet";

    std::stringstream ss;
    mc::Log::set_out_stream(&ss);

    std::string result;
    std::string expected;

    mc::Log::set_verb_level(mc::Log::VerboseLevel::Error);
    EXPECT_NO_THROW( mc::Log::Warning(msg.c_str()) );
    result   = ss.str();
    expected = "";
    EXPECT_TRUE( result == expected );

    mc::Log::set_verb_level(mc::Log::VerboseLevel::Warning);
    EXPECT_NO_THROW( mc::Log::Warning(msg.c_str()) );
    result   = ss.str().substr(25);
    expected = "[WARNING] " + msg + "\n";
    EXPECT_TRUE( result == expected );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanPrintInfoMsg)
{
    std::string msg = "Lorem ipsum dolor sit amet";

    std::stringstream ss;
    mc::Log::set_out_stream(&ss);

    std::string result;
    std::string expected;

    mc::Log::set_verb_level(mc::Log::VerboseLevel::Warning);
    EXPECT_NO_THROW( mc::Log::Info(msg.c_str()) );
    result   = ss.str();
    expected = "";
    EXPECT_TRUE( result == expected );

    mc::Log::set_verb_level(mc::Log::VerboseLevel::Info);
    EXPECT_NO_THROW( mc::Log::Info(msg.c_str()) );
    result   = ss.str().substr(25);
    expected = "[INFO] " + msg + "\n";
    EXPECT_TRUE( result == expected );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanPrintDebugMsg)
{
    std::string msg = "Lorem ipsum dolor sit amet";

    std::stringstream ss;
    mc::Log::set_out_stream(&ss);

    std::string result;
    std::string expected;

    mc::Log::set_verb_level(mc::Log::VerboseLevel::Info);
    EXPECT_NO_THROW( mc::Log::Debug(msg.c_str()) );
    result   = ss.str();
    expected = "";
    EXPECT_TRUE( result == expected );

    mc::Log::set_verb_level(mc::Log::VerboseLevel::Debug);
    EXPECT_NO_THROW( mc::Log::Debug(msg.c_str()) );
    result   = ss.str().substr(25);
    expected = "[DEBUG] " + msg + "\n";
    EXPECT_TRUE( result == expected );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanSetOutStream)
{
    std::stringstream ss;
    EXPECT_NO_THROW( mc::Log::set_out_stream(&ss) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanSetSyslogOut)
{
    std::stringstream ss;
    EXPECT_NO_THROW( mc::Log::set_syslog_out(false) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLog, CanSetVerbLevel)
{
    std::stringstream ss;
    EXPECT_NO_THROW( mc::Log::set_verb_level(mc::Log::VerboseLevel::Debug) );
}
