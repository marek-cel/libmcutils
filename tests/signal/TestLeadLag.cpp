#include <gtest/gtest.h>

#include <mcutil/signal/LeadLag.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestLeadLag : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP { 0.1 };

    static constexpr double C_1 { 1.0 };
    static constexpr double C_2 { 0.0 };
    static constexpr double C_3 { 1.0 };
    static constexpr double C_4 { 1.0 };

    TestLeadLag() {}
    virtual ~TestLeadLag() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanConstruct)
{
    mc::LeadLag *leadLag = nullptr;
    EXPECT_NO_THROW( leadLag = new mc::LeadLag() );
    delete leadLag;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanDestruct)
{
    mc::LeadLag *leadLag = new mc::LeadLag();
    EXPECT_NO_THROW( delete leadLag );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanInstantiate)
{
    mc::LeadLag leadLag;

    EXPECT_DOUBLE_EQ( leadLag.getC1(), 0.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC2(), 0.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC3(), 0.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC4(), 0.0 );
    EXPECT_DOUBLE_EQ( leadLag.getValue(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanInstantiateAndSetData)
{
    mc::LeadLag leadLag( 1.0, 2.0, 3.0, 4.0, 99.0 );

    EXPECT_DOUBLE_EQ( leadLag.getC1(), 1.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC2(), 2.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC3(), 3.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC4(), 4.0 );
    EXPECT_DOUBLE_EQ( leadLag.getValue(), 99.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanGetC1)
{
    mc::LeadLag leadLag( 1.0, 2.0, 3.0, 4.0, 99.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC1(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanGetC2)
{
    mc::LeadLag leadLag( 1.0, 2.0, 3.0, 4.0, 99.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC2(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanGetC3)
{
    mc::LeadLag leadLag( 1.0, 2.0, 3.0, 4.0, 99.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC3(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanGetC4)
{
    mc::LeadLag leadLag( 1.0, 2.0, 3.0, 4.0, 99.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC4(), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanGetValue)
{
    mc::LeadLag leadLag( 1.0, 2.0, 3.0, 4.0, 99.0 );
    EXPECT_DOUBLE_EQ( leadLag.getValue(), 99.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanSetC1)
{
    mc::LeadLag leadLag;
    leadLag.setC1( 1.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC1(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanSetC2)
{
    mc::LeadLag leadLag;
    leadLag.setC2( 2.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC2(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanSetC3)
{
    mc::LeadLag leadLag;
    leadLag.setC3( 3.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC3(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanSetC4)
{
    mc::LeadLag leadLag;
    leadLag.setC4( 4.0 );
    EXPECT_DOUBLE_EQ( leadLag.getC4(), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanSetValue)
{
    mc::LeadLag leadLag;
    leadLag.setValue( 1.0 );
    EXPECT_DOUBLE_EQ( leadLag.getValue(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLeadLag, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/signal/xcos/test_lead_lag.xcos
    XcosBinFileReader::readData( "../tests/signal/data/test_lead_lag.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::LeadLag leadLag( C_1, C_2, C_3, C_4 );

    double t = 0.0;
    double y = 0.0;

    int devider = 10;
    int index = 0;
    double dt = TIME_STEP / (double)devider;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( t < 0.99 ) ? 0.0 : 1.0;

        leadLag.update( dt, u );
        y = leadLag.getValue();

        if ( i % devider == 0 )
        {
            if ( index > 0 )
            {
                EXPECT_NEAR( y, vals.at( index - 1 ), 1.0e-1 );
            }

            index++;
        }

        t += dt;
    }

}
