#include <gtest/gtest.h>

#include <mcutils/signal/Filter2.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestFilter2 : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP { 0.1 };

    static constexpr double C_1 { 2.0 };
    static constexpr double C_2 { 2.0 };
    static constexpr double C_3 { 2.0 };
    static constexpr double C_4 { 1.0 };
    static constexpr double C_5 { 2.0 };
    static constexpr double C_6 { 4.0 };

    TestFilter2() {}
    virtual ~TestFilter2() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanConstruct)
{
    mc::Filter2 *f = nullptr;
    EXPECT_NO_THROW( f = new mc::Filter2() );
    delete f;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanDestruct)
{
    mc::Filter2 *f = new mc::Filter2();
    EXPECT_NO_THROW( delete f );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanInstantiate)
{
    mc::Filter2 f;

    EXPECT_DOUBLE_EQ( f.getC1(), 0.0 );
    EXPECT_DOUBLE_EQ( f.getC2(), 0.0 );
    EXPECT_DOUBLE_EQ( f.getC3(), 0.0 );
    EXPECT_DOUBLE_EQ( f.getC4(), 0.0 );
    EXPECT_DOUBLE_EQ( f.getC5(), 0.0 );
    EXPECT_DOUBLE_EQ( f.getC6(), 0.0 );

    EXPECT_DOUBLE_EQ( f.getValue(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanInstantiateAndSetData)
{
    mc::Filter2 f( 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0 );

    EXPECT_DOUBLE_EQ( f.getC1(), 1.0 );
    EXPECT_DOUBLE_EQ( f.getC2(), 2.0 );
    EXPECT_DOUBLE_EQ( f.getC3(), 3.0 );
    EXPECT_DOUBLE_EQ( f.getC4(), 4.0 );
    EXPECT_DOUBLE_EQ( f.getC5(), 5.0 );
    EXPECT_DOUBLE_EQ( f.getC6(), 6.0 );

    EXPECT_DOUBLE_EQ( f.getValue(), 99.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanGetC1)
{
    mc::Filter2 f( 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0 );
    EXPECT_DOUBLE_EQ( f.getC1(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanGetC2)
{
    mc::Filter2 f( 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0 );
    EXPECT_DOUBLE_EQ( f.getC2(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanGetC3)
{
    mc::Filter2 f( 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0 );
    EXPECT_DOUBLE_EQ( f.getC3(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanGetC4)
{
    mc::Filter2 f( 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0 );
    EXPECT_DOUBLE_EQ( f.getC4(), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanGetC5)
{
    mc::Filter2 f( 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0 );
    EXPECT_DOUBLE_EQ( f.getC5(), 5.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanGetC6)
{
    mc::Filter2 f( 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0 );
    EXPECT_DOUBLE_EQ( f.getC6(), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanGetValue)
{
    mc::Filter2 f( 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 99.0 );
    EXPECT_DOUBLE_EQ( f.getValue(), 99.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanSetC1)
{
    mc::Filter2 f;
    f.setC1( 1.0 );
    EXPECT_DOUBLE_EQ( f.getC1(), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanSetC2)
{
    mc::Filter2 f;
    f.setC2( 2.0 );
    EXPECT_DOUBLE_EQ( f.getC2(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanSetC3)
{
    mc::Filter2 f;
    f.setC3( 3.0 );
    EXPECT_DOUBLE_EQ( f.getC3(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanSetC4)
{
    mc::Filter2 f;
    f.setC4( 4.0 );
    EXPECT_DOUBLE_EQ( f.getC4(), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanSetC5)
{
    mc::Filter2 f;
    f.setC5( 5.0 );
    EXPECT_DOUBLE_EQ( f.getC5(), 5.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanSetC6)
{
    mc::Filter2 f;
    f.setC6( 6.0 );
    EXPECT_DOUBLE_EQ( f.getC6(), 6.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanSetValue)
{
    mc::Filter2 f;
    f.setValue( 99.0 );
    EXPECT_DOUBLE_EQ( f.getValue(), 99.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFilter2, CanUpdate)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/signal/xcos/test_filter2.xcos
    XcosBinFileReader::readData( "../tests/signal/data/test_filter2.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    mc::Filter2 filter( C_1, C_2, C_3, C_4, C_5, C_6 );

    double t = 0.0;
    double y = 0.0;

    int devider = 10;
    int index = 0;
    double dt = TIME_STEP / (double)devider;

    for ( unsigned int i = 0; i < devider * vals.size(); i++ )
    {
        double u = ( t < 0.99 ) ? 0.0 : 1.0;

        filter.update( dt, u );
        y = filter.getValue();

        if ( i % devider == 0 )
        {
            if ( index > 0 )
            {
                //std::cout << y << std::endl;
                EXPECT_NEAR( y, vals.at( index - 1 ), 1.0e-1 );
            }

            index++;
        }

        t += dt;
    }
}
