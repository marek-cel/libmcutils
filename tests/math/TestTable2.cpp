#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/math/Table2.h>

////////////////////////////////////////////////////////////////////////////////

class TestTable2 : public ::testing::Test
{
protected:
    TestTable2() {}
    virtual ~TestTable2() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanConstruct)
{
    mc::Table2 *tab = nullptr;
    EXPECT_NO_THROW( tab = new mc::Table2() );
    delete tab;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanDestruct)
{
    mc::Table2 *tab = new mc::Table2();
    EXPECT_NO_THROW( delete tab );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanCreateOneRecordTable)
{
    mc::Table2 tab = mc::Table2::oneRecordTable( 1.1, 2.2, 3.3 );

    EXPECT_EQ( tab.getRows(), 1 );
    EXPECT_EQ( tab.getCols(), 1 );
    EXPECT_DOUBLE_EQ( tab.getValue( 2.2, 3.3 ), 1.1 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanInstantiate)
{
    mc::Table2 tab;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanInstantiateAndCopy)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab1( r, c, v );

    mc::Table2 tab( tab1 );

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

TEST_F(TestTable2, CanInstantiateAndMove)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab( std::move(mc::Table2( r, c, v )) );

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

TEST_F(TestTable2, CanInstantiateAndSetDataFromArray)
{
    // z = x^2 + y - 1
    double r[] { -1.0,  0.0,  1.0,  2.0 };
    double c[] {  0.0,  1.0 };
    double v[] {  0.0,  1.0,
                 -1.0,  0.0,
                  0.0,  1.0,
                  3.0,  4.0 };

    mc::Table2 tab( r, c, v, 4, 2 );

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

TEST_F(TestTable2, CanInstantiateAndSetDataFromVector)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab( r, c, v );

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

TEST_F(TestTable2, CanGetRows)
{
    // z = x^2 + y - 1
    double r[] { -1.0,  0.0,  1.0,  2.0 };
    double c[] {  0.0,  1.0 };
    double v[] {  0.0,  1.0,
                 -1.0,  0.0,
                  0.0,  1.0,
                  3.0,  4.0 };

    mc::Table2 tab( r, c, v, 4, 2 );

    EXPECT_EQ( tab.getRows(), 4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanGetCols)
{
    // z = x^2 + y - 1
    double r[] { -1.0,  0.0,  1.0,  2.0 };
    double c[] {  0.0,  1.0 };
    double v[] {  0.0,  1.0,
                 -1.0,  0.0,
                  0.0,  1.0,
                  3.0,  4.0 };

    mc::Table2 tab( r, c, v, 4, 2 );

    EXPECT_EQ( tab.getCols(), 2 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanGetTable)
{
    // z = x^2 + y - 1
    double r[] { -1.0,  0.0,  1.0,  2.0 };
    double c[] {  0.0,  1.0 };
    double v[] {  0.0,  1.0,
                 -1.0,  0.0,
                  0.0,  1.0,
                  3.0,  4.0 };

    mc::Table2 tab(r, c, v, 4, 2);

    mc::Table tab0 = tab.getTable(0);
    mc::Table tab1 = tab.getTable(1);

    EXPECT_DOUBLE_EQ( tab0.GetKeyByIndex(0), -1.0 );
    EXPECT_DOUBLE_EQ( tab0.GetKeyByIndex(1),  0.0 );
    EXPECT_DOUBLE_EQ( tab0.GetKeyByIndex(2),  1.0 );
    EXPECT_DOUBLE_EQ( tab0.GetKeyByIndex(3),  2.0 );

    EXPECT_DOUBLE_EQ( tab0.GetValue( -1.0 ),  0.0 );
    EXPECT_DOUBLE_EQ( tab0.GetValue(  0.0 ), -1.0 );
    EXPECT_DOUBLE_EQ( tab0.GetValue(  1.0 ),  0.0 );
    EXPECT_DOUBLE_EQ( tab0.GetValue(  2.0 ),  3.0 );

    EXPECT_DOUBLE_EQ( tab1.GetKeyByIndex(0), -1.0 );
    EXPECT_DOUBLE_EQ( tab1.GetKeyByIndex(1),  0.0 );
    EXPECT_DOUBLE_EQ( tab1.GetKeyByIndex(2),  1.0 );
    EXPECT_DOUBLE_EQ( tab1.GetKeyByIndex(3),  2.0 );

    EXPECT_DOUBLE_EQ( tab1.GetValue( -1.0 ),  1.0 );
    EXPECT_DOUBLE_EQ( tab1.GetValue(  0.0 ),  0.0 );
    EXPECT_DOUBLE_EQ( tab1.GetValue(  1.0 ),  1.0 );
    EXPECT_DOUBLE_EQ( tab1.GetValue(  2.0 ),  4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanGetValue)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab( r, c, v );

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

TEST_F(TestTable2, CanGetValueInterpolate)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab( r, c, v );

    EXPECT_DOUBLE_EQ( tab.getValue(  0.5, 0.0 ), -0.5 );
    EXPECT_DOUBLE_EQ( tab.getValue( -1.0, 0.5 ),  0.5 );
    EXPECT_DOUBLE_EQ( tab.getValue( -0.5, 0.5 ),  0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanGetValueOutOfRange)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab( r, c, v );

    EXPECT_DOUBLE_EQ( tab.getValue(  3.0,  0.0 ),  3.0 );
    EXPECT_DOUBLE_EQ( tab.getValue( -2.0,  0.0 ),  0.0 );
    EXPECT_DOUBLE_EQ( tab.getValue( -1.0,  2.0 ),  1.0 );
    EXPECT_DOUBLE_EQ( tab.getValue(  3.0,  2.0 ),  4.0 );
    EXPECT_DOUBLE_EQ( tab.getValue(  0.0, -1.0 ), -1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanGetValueNotInited)
{
    mc::Table2 tab;
    EXPECT_TRUE( std::isnan( tab.getValue( 0.0, 0.0 ) ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanGetValueByIndex)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab( r, c, v );

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

TEST_F(TestTable2, CanGetValueByIndexNotInited)
{
    mc::Table2 tab;
    EXPECT_TRUE( std::isnan( tab.getValueByIndex( 0, 0 ) ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanValidate)
{
    std::vector< double > r1 { 0.0, 1.0, 2.0 };
    std::vector< double > c1 { 0.0, 1.0 };
    std::vector< double > v1 { 0.0, 3.0,
                               1.0, 4.0,
                               2.0, 5.0 };
    mc::Table2 t1( r1, c1, v1 );
    EXPECT_TRUE( t1.isValid() );

    std::vector< double > r2 { std::numeric_limits<double>::quiet_NaN(), 1.0, 2.0 };
    std::vector< double > c2 { 0.0, 1.0 };
    std::vector< double > v2 { 0.0, 3.0,
                               1.0, 4.0,
                               2.0, 5.0 };
    mc::Table2 t2( r2, c2, v2 );
    EXPECT_FALSE( t2.isValid() );

    std::vector< double > r3 { 0.0, 1.0, 2.0 };
    std::vector< double > c3 { std::numeric_limits<double>::quiet_NaN(), 1.0 };
    std::vector< double > v3 { 0.0, 3.0,
                               1.0, 4.0,
                               2.0, 5.0 };
    mc::Table2 t3( r3, c3, v3 );
    EXPECT_FALSE( t3.isValid() );

    std::vector< double > r4 { 0.0, 1.0, 2.0 };
    std::vector< double > c4 { 0.0, 1.0 };
    std::vector< double > v4 { std::numeric_limits<double>::quiet_NaN(), 3.0,
                               1.0, 4.0,
                               2.0, 5.0 };
    mc::Table2 t4( r4, c4, v4 );
    EXPECT_FALSE( t4.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanMultiplyRowsAndCols)
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

    mc::Table2 tab( r, c, v );

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

TEST_F(TestTable2, CanMultiplyRows)
{
    const double r_coef = 2.0;

    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab( r, c, v );

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

TEST_F(TestTable2, CanMultiplyCols)
{
    const double c_coef = 2.0;

    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab( r, c, v );

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

TEST_F(TestTable2, CanMultiplyValues)
{
    const double v_coef = 2.0;

    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab( r, c, v );

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

TEST_F(TestTable2, CanSetDataFromArray)
{
    // z = x^2 + y - 1
    double r[] { -1.0,  0.0,  1.0,  2.0 };
    double c[] {  0.0,  1.0 };
    double v[] {  0.0,  1.0,
                 -1.0,  0.0,
                  0.0,  1.0,
                  3.0,  4.0 };

    mc::Table2 tab;
    tab.setData( r, c, v, 4, 2 );

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

TEST_F(TestTable2, CanSetDataFromVector)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab;
    tab.setData( r, c, v );

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

TEST_F(TestTable2, CanSetDataFromString)
{
    char str[] =
    { R"##(
             1.0  2.0  3.0
        1.0  2.0  3.0  4.0
        2.0  3.0  4.0  5.0
    )##" };

    mc::Table2 tab;
    tab.setFromString( str );

    EXPECT_TRUE( tab.isValid() );

    EXPECT_EQ( tab.getCols(), 3 );
    EXPECT_EQ( tab.getRows(), 2 );

    for ( unsigned int ir = 0; ir < 2; ++ir )
    {
        for ( unsigned int ic = 0; ic < 3; ++ic )
        {
            double xr = ir + 1;
            double xc = ic + 1;
            double y = xr + xc;
            EXPECT_DOUBLE_EQ( tab.getValue( xr, xc ), y );
        }
    }

    char str2[] = { "lorem ipsum" };
    mc::Table2 tab2;
    tab2.setFromString( str2 );
    EXPECT_FALSE( tab2.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanConvertToString)
{
    // z = x^2 + y - 1
    std::vector< double > r { 0.0, 1.0, 2.0 };
    std::vector< double > c { 0.0, 1.0 };
    std::vector< double > v { 0.0, 1.0,
                              2.0, 3.0,
                              4.0, 5.0 };

    mc::Table2 tab( r, c, v );

    EXPECT_STREQ( tab.toString().c_str(), "\t0\t1\n0\t0\t1\n1\t2\t3\n2\t4\t5\n" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanAssign)
{
    mc::Table2 tab;

    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab1( r, c, v );

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

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable2, CanAssignAndMove)
{
    // z = x^2 + y - 1
    std::vector< double > r { -1.0,  0.0,  1.0,  2.0 };
    std::vector< double > c {  0.0,  1.0 };
    std::vector< double > v {  0.0,  1.0,
                              -1.0,  0.0,
                               0.0,  1.0,
                               3.0,  4.0 };

    mc::Table2 tab;
    tab = std::move(mc::Table2( r, c, v ));

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
