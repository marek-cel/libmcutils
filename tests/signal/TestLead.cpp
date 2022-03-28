#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/signal/Lead.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestLead : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP     { 0.1 };
    static constexpr double TIME_CONSTANT { 0.3 };

    TestLead() {}
    virtual ~TestLead() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLead, CanConstruct)
{
    mc::Lead *lead = nullptr;
    EXPECT_NO_THROW( lead = new mc::Lead() );
    delete lead;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLead, CanDestruct)
{
    mc::Lead *lead = new mc::Lead();
    EXPECT_NO_THROW( delete lead );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLead, CanInstantiate)
{
    mc::Lead lead;

    EXPECT_DOUBLE_EQ( lead.getTimeConst(), 1.0 );
    EXPECT_DOUBLE_EQ( lead.getValue(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLead, CanInstantiateAndSetData)
{
    mc::Lead lead( 2.0, 3.0 );

    EXPECT_DOUBLE_EQ( lead.getTimeConst(), 2.0 );
    EXPECT_DOUBLE_EQ( lead.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLead, CanGetValue)
{
    mc::Lead lead( 2.0, 3.0 );

    EXPECT_DOUBLE_EQ( lead.getValue(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLead, CanSetValue)
{
    mc::Lead lead;

    lead.setValue( 1.0 );
    EXPECT_DOUBLE_EQ( lead.getValue(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLead, CanGetTimeConst)
{
    mc::Lead lead( 2.0, 3.0 );

    EXPECT_DOUBLE_EQ( lead.getTimeConst(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLead, CanSetTimeConst)
{
    mc::Lead lead;

    lead.setTimeConst( 2.0 );
    EXPECT_DOUBLE_EQ( lead.getTimeConst(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestLead, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/signal/xcos/test_lead.xcos
    XcosBinFileReader::readData( "../tests/signal/data/test_lead.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::Lead lead( TIME_CONSTANT );

    double t = 0.0;
    double y = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        int steps = 10;
        for ( int j = 0; j < steps; j++ )
        {
            double dt = TIME_STEP / (double)steps;
            double tt = t + (double)j * dt;

            double u = sin( tt );

            lead.update( dt, u );
            y = lead.getValue();
        }

        EXPECT_NEAR( y, vals.at( i ), 1.0e-1 );

        t += TIME_STEP;
    }

}
