#include <gtest/gtest.h>

#include <mcutils/net/Endianness.h>

class TestEndianness : public ::testing::Test
{
protected:
    TestEndianness() {}
    virtual ~TestEndianness() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestEndianness, CanConvertHostToNetUInt16)
{
    mc::UInt16 val_inp = static_cast<unsigned short>(123456U);
    mc::UInt16 val_out = mc::Net::HostToNet(val_inp);

    char* val_raw_inp = reinterpret_cast<char*>(&val_inp);
    char* val_raw_out = reinterpret_cast<char*>(&val_out);

    EXPECT_EQ(val_raw_out[0], val_raw_inp[1]);
    EXPECT_EQ(val_raw_out[1], val_raw_inp[0]);
}

TEST_F(TestEndianness, CanConvertHostToNetUInt32)
{
    mc::UInt32 val_inp = 123456789;
    mc::UInt32 val_out =  mc::Net::HostToNet(val_inp);

    char* val_raw_inp = reinterpret_cast<char*>(&val_inp);
    char* val_raw_out = reinterpret_cast<char*>(&val_out);

    EXPECT_EQ(val_raw_out[0], val_raw_inp[3]);
    EXPECT_EQ(val_raw_out[1], val_raw_inp[2]);
    EXPECT_EQ(val_raw_out[2], val_raw_inp[1]);
    EXPECT_EQ(val_raw_out[3], val_raw_inp[0]);
}

TEST_F(TestEndianness, CanConvertHostToNetDouble)
{
    double val_inp = 123.456;
    double val_out =  mc::Net::HostToNet(val_inp);

    char* val_raw_inp = reinterpret_cast<char*>(&val_inp);
    char* val_raw_out = reinterpret_cast<char*>(&val_out);

    EXPECT_EQ(val_raw_out[0], val_raw_inp[7]);
    EXPECT_EQ(val_raw_out[1], val_raw_inp[6]);
    EXPECT_EQ(val_raw_out[2], val_raw_inp[5]);
    EXPECT_EQ(val_raw_out[3], val_raw_inp[4]);
    EXPECT_EQ(val_raw_out[4], val_raw_inp[3]);
    EXPECT_EQ(val_raw_out[5], val_raw_inp[2]);
    EXPECT_EQ(val_raw_out[6], val_raw_inp[1]);
    EXPECT_EQ(val_raw_out[7], val_raw_inp[0]);
}

TEST_F(TestEndianness, CanConvertHostToNetFloat)
{
    float val_inp = 123.456;
    float val_out =  mc::Net::HostToNet(val_inp);

    char* val_raw_inp = reinterpret_cast<char*>(&val_inp);
    char* val_raw_out = reinterpret_cast<char*>(&val_out);

    EXPECT_EQ(val_raw_out[0], val_raw_inp[3]);
    EXPECT_EQ(val_raw_out[1], val_raw_inp[2]);
    EXPECT_EQ(val_raw_out[2], val_raw_inp[1]);
    EXPECT_EQ(val_raw_out[3], val_raw_inp[0]);
}
