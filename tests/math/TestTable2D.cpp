#include <gtest/gtest.h>

#include <cmath>

#include <mcutil/math/Table2D.h>

////////////////////////////////////////////////////////////////////////////////

class TestTable2D : public ::testing::Test
{
protected:
    TestTable2D() {}
    virtual ~TestTable2D() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanConstruct)
{
    mc::Table2D *tab = nullptr;
    EXPECT_NO_THROW( tab = new mc::Table2D() );
    delete tab;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanDestruct)
{
    mc::Table2D *tab = new mc::Table2D();
    EXPECT_NO_THROW( delete tab );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanCreateOneRecordTable)
{
    mc::Table2D tab = mc::Table2D::oneRecordTable( 1.1, 2.2, 3.3 );

    EXPECT_EQ( tab.getRows(), 1 );
    EXPECT_EQ( tab.getCols(), 1 );
    EXPECT_DOUBLE_EQ( tab.getValue( 2.2, 3.3 ), 1.1 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanInstantiate)
{
    mc::Table2D tab;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanInstantiateAndSetDataFromArray)
{
    // z = x^2 + y - 1
    double r[] { -1.0,  0.0,  1.0,  2.0 };
    double c[] {  0.0,  1.0 };
    double v[] {  0.0,  1.0,
                 -1.0,  0.0,
                  0.0,  1.0,
                  3.0,  4.0 };

    mc::Table2D tab( r, c, v, 4, 2 );

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.getRows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.getCols(); ++ic )
        {
             EXPECT_DOUBLE_EQ( tab.getValue( r[ir], c[ic] ), fun(ir,ic) ) << "ir= " << ir << " ic= " << ic;
        }
    }

    EXPECT_EQ( tab.getRows(), 4 );
    EXPECT_EQ( tab.getCols(), 2 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanInstantiateAndSetDataFromVector)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2D tab( r, c, v );

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.getRows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.getCols(); ++ic )
        {
             EXPECT_DOUBLE_EQ( tab.getValue( r[ir], c[ic] ), fun(ir,ic) ) << "ir= " << ir << " ic= " << ic;
        }
    }

    EXPECT_EQ( tab.getRows(), 4 );
    EXPECT_EQ( tab.getCols(), 2 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanInstantiateAndCopy)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2D tab1( r, c, v );

    mc::Table2D tab( tab1 );

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.getRows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.getCols(); ++ic )
        {
             EXPECT_DOUBLE_EQ( tab.getValue( r[ir], c[ic] ), fun(ir,ic) ) << "ir= " << ir << " ic= " << ic;
        }
    }

    EXPECT_EQ( tab.getRows(), 4 );
    EXPECT_EQ( tab.getCols(), 2 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanGetRows)
{
    // z = x^2 + y - 1
    double r[] { -1.0,  0.0,  1.0,  2.0 };
    double c[] {  0.0,  1.0 };
    double v[] {  0.0,  1.0,
                 -1.0,  0.0,
                  0.0,  1.0,
                  3.0,  4.0 };

    mc::Table2D tab( r, c, v, 4, 2 );

    EXPECT_EQ( tab.getRows(), 4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanGetCols)
{
    // z = x^2 + y - 1
    double r[] { -1.0,  0.0,  1.0,  2.0 };
    double c[] {  0.0,  1.0 };
    double v[] {  0.0,  1.0,
                 -1.0,  0.0,
                  0.0,  1.0,
                  3.0,  4.0 };

    mc::Table2D tab( r, c, v, 4, 2 );

    EXPECT_EQ( tab.getCols(), 2 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanGetTable)
{
    // z = x^2 + y - 1
    double r[] { -1.0,  0.0,  1.0,  2.0 };
    double c[] {  0.0,  1.0 };
    double v[] {  0.0,  1.0,
                 -1.0,  0.0,
                  0.0,  1.0,
                  3.0,  4.0 };

    mc::Table2D tab( r, c, v, 4, 2 );

    mc::Table tab0 = tab.getTable( 0 );
    mc::Table tab1 = tab.getTable( 1 );

    EXPECT_DOUBLE_EQ( tab0.getKeyByIndex( 0 ), -1.0 );
    EXPECT_DOUBLE_EQ( tab0.getKeyByIndex( 1 ),  0.0 );
    EXPECT_DOUBLE_EQ( tab0.getKeyByIndex( 2 ),  1.0 );
    EXPECT_DOUBLE_EQ( tab0.getKeyByIndex( 3 ),  2.0 );

    EXPECT_DOUBLE_EQ( tab0.getValue( -1.0 ),  0.0 );
    EXPECT_DOUBLE_EQ( tab0.getValue(  0.0 ), -1.0 );
    EXPECT_DOUBLE_EQ( tab0.getValue(  1.0 ),  0.0 );
    EXPECT_DOUBLE_EQ( tab0.getValue(  2.0 ),  3.0 );

    EXPECT_DOUBLE_EQ( tab1.getKeyByIndex( 0 ), -1.0 );
    EXPECT_DOUBLE_EQ( tab1.getKeyByIndex( 1 ),  0.0 );
    EXPECT_DOUBLE_EQ( tab1.getKeyByIndex( 2 ),  1.0 );
    EXPECT_DOUBLE_EQ( tab1.getKeyByIndex( 3 ),  2.0 );

    EXPECT_DOUBLE_EQ( tab1.getValue( -1.0 ),  1.0 );
    EXPECT_DOUBLE_EQ( tab1.getValue(  0.0 ),  0.0 );
    EXPECT_DOUBLE_EQ( tab1.getValue(  1.0 ),  1.0 );
    EXPECT_DOUBLE_EQ( tab1.getValue(  2.0 ),  4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanGetValue)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2D tab( r, c, v );

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.getRows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.getCols(); ++ic )
        {
             EXPECT_DOUBLE_EQ( tab.getValue( r[ir], c[ic] ), fun(ir,ic) ) << "ir= " << ir << " ic= " << ic;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanGetValueInterpolate)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2D tab( r, c, v );

    EXPECT_DOUBLE_EQ( tab.getValue(  0.5, 0.0 ), -0.5 );
    EXPECT_DOUBLE_EQ( tab.getValue( -1.0, 0.5 ),  0.5 );
    EXPECT_DOUBLE_EQ( tab.getValue( -0.5, 0.5 ),  0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanGetValueOutOfRange)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2D tab( r, c, v );

    EXPECT_DOUBLE_EQ( tab.getValue(  3.0,  0.0 ),  3.0 );
    EXPECT_DOUBLE_EQ( tab.getValue( -2.0,  0.0 ),  0.0 );
    EXPECT_DOUBLE_EQ( tab.getValue( -1.0,  2.0 ),  1.0 );
    EXPECT_DOUBLE_EQ( tab.getValue(  3.0,  2.0 ),  4.0 );
    EXPECT_DOUBLE_EQ( tab.getValue(  0.0, -1.0 ), -1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanGetValueNotInited)
{
    mc::Table2D tab;
    EXPECT_TRUE( std::isnan( tab.getValue( 0.0, 0.0 ) ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanGetValueByIndex)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2D tab( r, c, v );

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.getRows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.getCols(); ++ic )
        {
             EXPECT_DOUBLE_EQ( tab.getValueByIndex( ir, ic ), fun(ir,ic) ) << "ir= " << ir << " ic= " << ic;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanGetValueByIndexNotInited)
{
    mc::Table2D tab;
    EXPECT_TRUE( std::isnan( tab.getValueByIndex( 0, 0 ) ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanValidate)
{
    std::vector< double > r1 { 0.0, 1.0, 2.0 };
    std::vector< double > c1 { 0.0, 1.0 };
    std::vector< double > v1 { 0.0, 3.0,
                               1.0, 4.0,
                               2.0, 5.0 };
    mc::Table2D t1( r1, c1, v1 );
    EXPECT_TRUE( t1.isValid() );

    std::vector< double > r2 { std::numeric_limits<double>::quiet_NaN(), 1.0, 2.0 };
    std::vector< double > c2 { 0.0, 1.0 };
    std::vector< double > v2 { 0.0, 3.0,
                               1.0, 4.0,
                               2.0, 5.0 };
    mc::Table2D t2( r2, c2, v2 );
    EXPECT_FALSE( t2.isValid() );

    std::vector< double > r3 { 0.0, 1.0, 2.0 };
    std::vector< double > c3 { std::numeric_limits<double>::quiet_NaN(), 1.0 };
    std::vector< double > v3 { 0.0, 3.0,
                               1.0, 4.0,
                               2.0, 5.0 };
    mc::Table2D t3( r3, c3, v3 );
    EXPECT_FALSE( t3.isValid() );

    std::vector< double > r4 { 0.0, 1.0, 2.0 };
    std::vector< double > c4 { 0.0, 1.0 };
    std::vector< double > v4 { std::numeric_limits<double>::quiet_NaN(), 3.0,
                               1.0, 4.0,
                               2.0, 5.0 };
    mc::Table2D t4( r4, c4, v4 );
    EXPECT_FALSE( t4.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanMultiplyRowsAndCols)
{
    const double c_coef = 2.0;
    const double r_coef = 3.0;

    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2D tab( r, c, v );

    tab.multiplyRowsAndCols( r_coef, c_coef );

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.getRows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.getCols(); ++ic )
        {
             EXPECT_DOUBLE_EQ( tab.getValue( r_coef*r[ir], c_coef*c[ic] ), fun(ir,ic) ) << "ir= " << ir << " ic= " << ic;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanMultiplyRows)
{
    const double r_coef = 2.0;

    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2D tab( r, c, v );

    tab.multiplyRows( r_coef );

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.getRows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.getCols(); ++ic )
        {
             EXPECT_DOUBLE_EQ( tab.getValue( r_coef*r[ir], c[ic] ), fun(ir,ic) ) << "ir= " << ir << " ic= " << ic;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanMultiplyCols)
{
    const double c_coef = 2.0;

    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2D tab( r, c, v );

    tab.multiplyCols( c_coef );

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.getRows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.getCols(); ++ic )
        {
             EXPECT_DOUBLE_EQ( tab.getValue( r[ir], c_coef*c[ic] ), fun(ir,ic) ) << "ir= " << ir << " ic= " << ic;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanMultiplyValues)
{
    const double v_coef = 2.0;

    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2D tab( r, c, v );

    tab.multiplyValues( v_coef );

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.getRows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.getCols(); ++ic )
        {
             EXPECT_DOUBLE_EQ( tab.getValue( r[ir], c[ic] ), v_coef*fun(ir,ic) ) << "ir= " << ir << " ic= " << ic;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanConvertToString)
{
    // z = x^2 + y - 1
    std::vector< double > r { 0.0, 1.0, 2.0 };
    std::vector< double > c { 0.0, 1.0 };
    std::vector< double > v { 0.0, 1.0,
                              2.0, 3.0,
                              4.0, 5.0 };

    mc::Table2D tab( r, c, v );

    EXPECT_STREQ( tab.toString().c_str(), "\t0\t1\n0\t0\t1\n1\t2\t3\n2\t4\t5\n" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2D, CanAssign)
{
    mc::Table2D tab;

    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2D tab1( r, c, v );

    tab = tab1;

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.getRows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.getCols(); ++ic )
        {
             EXPECT_DOUBLE_EQ( tab.getValue( r[ir], c[ic] ), fun(ir,ic) ) << "ir= " << ir << " ic= " << ic;
        }
    }

    EXPECT_EQ( tab.getRows(), 4 );
    EXPECT_EQ( tab.getCols(), 2 );
}
