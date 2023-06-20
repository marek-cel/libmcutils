#include <gtest/gtest.h>

#include <mcutils/math/DegMinSec.h>
#include <mcutils/misc/Units.h>

////////////////////////////////////////////////////////////////////////////////

class TestDegMinSec : public ::testing::Test
{
protected:
    TestDegMinSec() {}
    virtual ~TestDegMinSec() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDegMinSec, CanConstruct)
{
    mc::DegMinSec *dms = nullptr;
    EXPECT_NO_THROW( dms = new mc::DegMinSec() );
    delete dms;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDegMinSec, CanDestruct)
{
    mc::DegMinSec *dms = new mc::DegMinSec();
    EXPECT_NO_THROW( delete dms );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDegMinSec, CanInstantiate)
{
    mc::DegMinSec dms;

    EXPECT_EQ( dms.deg(), 0 );
    EXPECT_EQ( dms.min(), 0 );
    EXPECT_DOUBLE_EQ( dms.sec(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDegMinSec, CanInstantiateAndSetData)
{
    mc::DegMinSec dms(mc::Units::deg2rad( 1.0 + 2.0 / 60.0 + 3.0 / 3600.0 ));

    EXPECT_EQ( dms.deg(), 1 );
    EXPECT_EQ( dms.min(), 2 );
    EXPECT_NEAR( dms.sec(), 3.0, 1e-9 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDegMinSec, CanValidate)
{
    mc::DegMinSec dms1(M_PI_4);
    EXPECT_TRUE( dms1.IsValid() );

    mc::DegMinSec dms2( std::numeric_limits<double>::quiet_NaN() );
    EXPECT_FALSE( dms2.IsValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDegMinSec, CanGetAngle)
{
    mc::DegMinSec dms(M_PI_4);

    EXPECT_DOUBLE_EQ( dms.GetAngle(), M_PI_4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDegMinSec, CanSetAngle)
{
    mc::DegMinSec dms;

    dms.SetAngle(M_PI_4);
    EXPECT_DOUBLE_EQ( dms.GetAngle(), M_PI_4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDegMinSec, CanConvertToString)
{
    mc::DegMinSec dms( mc::Units::deg2rad( 1.0 + 2.0 / 60.0 + 3.0 / 3600.0 ) );

    EXPECT_STREQ( dms.ToString().c_str(), "1 deg 2 min 3.00 sec" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDegMinSec, CanCompare)
{
    mc::DegMinSec dms;

    mc::DegMinSec dms1(mc::Units::deg2rad( 1.0 + 2.0 / 60.0 + 3.0 / 3600.0 ));

    EXPECT_FALSE( dms == dms1 );
    EXPECT_TRUE(  dms != dms1 );
    dms = dms1;
    EXPECT_TRUE(  dms == dms1 );
    EXPECT_FALSE( dms != dms1 );
}
