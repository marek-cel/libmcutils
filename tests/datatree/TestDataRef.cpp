#include <gtest/gtest.h>

#include <mcutils/datatree/DataRef.h>
#include <mcutils/datatree/ValueNode.h>

////////////////////////////////////////////////////////////////////////////////

class TestDataRef : public ::testing::Test
{
protected:
    TestDataRef() {}
    virtual ~TestDataRef() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataRef, CanConstruct)
{
    mc::DataRef<bool> *refB = nullptr;
    EXPECT_NO_THROW( refB = new mc::DataRef<bool>() );
    delete refB;

    mc::DataRef<int> *refI = nullptr;
    EXPECT_NO_THROW( refI = new mc::DataRef<int>() );
    delete refI;

    mc::DataRef<double> *refD = nullptr;
    EXPECT_NO_THROW( refD = new mc::DataRef<double>() );
    delete refD;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataRef, CanDestruct)
{
    mc::DataRef<bool> *refB = new mc::DataRef<bool>();
    EXPECT_NO_THROW( delete refB );

    mc::DataRef<int> *refI = new mc::DataRef<int>();
    EXPECT_NO_THROW( delete refI );

    mc::DataRef<double> *refD = new mc::DataRef<double>();
    EXPECT_NO_THROW( delete refD );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataRef, CanInstantiate)
{
    mc::DataRef<bool> refB1;
    EXPECT_FALSE( refB1.get() );
    EXPECT_FALSE( refB1.isValid() );
    EXPECT_EQ( refB1.set( true ), mc::Result::Failure );

    mc::DataRef<int> refI1;
    EXPECT_EQ( refI1.get(), 0 );
    EXPECT_FALSE( refI1.isValid() );
    EXPECT_EQ( refI1.set( 1 ), mc::Result::Failure );

    mc::DataRef<double> refD1;
    EXPECT_NEAR( refD1.get(), 0.0, 1.0e-12 );
    EXPECT_FALSE( refD1.isValid() );
    EXPECT_EQ( refD1.set( 3.14 ), mc::Result::Failure );

    std::shared_ptr< mc::ValueNodeBool > valueNodeBShared = std::make_shared< mc::ValueNodeBool >();
    std::weak_ptr< mc::ValueNodeBool > valueNodeBSWeak = valueNodeBShared;
    mc::DataRefBool refB( valueNodeBSWeak );
    EXPECT_FALSE( refB.get() );
    EXPECT_TRUE( refB.isValid() );
    EXPECT_EQ( refB.set( true ), mc::Result::Success );

    std::shared_ptr< mc::ValueNodeInt > valueNodeIShared = std::make_shared< mc::ValueNodeInt >();
    std::weak_ptr< mc::ValueNodeInt > valueNodeISWeak = valueNodeIShared;
    mc::DataRefInt refI( valueNodeISWeak );
    EXPECT_EQ( refI.get(), 0 );
    EXPECT_TRUE( refI.isValid() );
    EXPECT_EQ( refI.set( 1 ), mc::Result::Success );

    std::shared_ptr< mc::ValueNodeReal > valueNodeDShared = std::make_shared< mc::ValueNodeReal >();
    std::weak_ptr< mc::ValueNodeReal > valueNodeDSWeak = valueNodeDShared;
    mc::DataRefReal refD( valueNodeDSWeak );
    EXPECT_NEAR( refD.get(), 0.0, 1.0e-12 );
    EXPECT_TRUE( refD.isValid() );
    EXPECT_EQ( refD.set( 3.14 ), mc::Result::Success );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataRef, CanGetValue)
{
    std::shared_ptr< mc::ValueNodeBool > valueNodeBShared = std::make_shared< mc::ValueNodeBool >();
    std::weak_ptr< mc::ValueNodeBool > valueNodeBSWeak = valueNodeBShared;
    mc::DataRefBool refB( valueNodeBSWeak );
    EXPECT_EQ( refB.set( true ), mc::Result::Success );
    EXPECT_TRUE( refB.get() );

    std::shared_ptr< mc::ValueNodeInt > valueNodeIShared = std::make_shared< mc::ValueNodeInt >();
    std::weak_ptr< mc::ValueNodeInt > valueNodeISWeak = valueNodeIShared;
    mc::DataRefInt refI( valueNodeISWeak );
    EXPECT_EQ( refI.set( 1 ), mc::Result::Success );
    EXPECT_EQ( refI.get(), 1 );

    std::shared_ptr< mc::ValueNodeReal > valueNodeDShared = std::make_shared< mc::ValueNodeReal >();
    std::weak_ptr< mc::ValueNodeReal > valueNodeDSWeak = valueNodeDShared;
    mc::DataRefReal refD( valueNodeDSWeak );
    EXPECT_EQ( refD.set( 3.14 ), mc::Result::Success );
    EXPECT_NEAR( refD.get(), 3.14, 1.0e-12 );
}
