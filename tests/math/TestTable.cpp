#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/math/Table.h>

////////////////////////////////////////////////////////////////////////////////

class TestTable : public ::testing::Test
{
protected:
    TestTable() {}
    virtual ~TestTable() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanConstruct)
{
    mc::Table *tab = nullptr;
    EXPECT_NO_THROW( tab = new mc::Table() );
    delete tab;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanDestruct)
{
    mc::Table *tab = new mc::Table();
    EXPECT_NO_THROW( delete tab );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanCreateOneRecordTable)
{
    mc::Table tab = mc::Table::oneRecordTable( 2.2, 1.7 );

    EXPECT_EQ( tab.getSize(), 1 );
    EXPECT_DOUBLE_EQ( tab.getValue( 1.7 ), 2.2 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanInstantiate)
{
    mc::Table tab;

    EXPECT_EQ( tab.getSize(), 0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanInstantiateAndSetDataFromArray)
{
    // y = x^2 - 1
    double key_values[] { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    double table_data[] {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data, 6 );

    for ( unsigned int i = 0; i < tab.getSize(); ++i )
    {
        EXPECT_DOUBLE_EQ( tab.getValue( key_values[ i ] ), table_data[ i ] );
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanInstantiateAndSetDataFromVector)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    for ( unsigned int i = 0; i < key_values.size(); ++i )
    {
        EXPECT_DOUBLE_EQ( tab.getValue( key_values[ i ] ), table_data[ i ] );
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanInstantiateAndCopy)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    mc::Table tab1( tab );

    for ( unsigned int i = 0; i < key_values.size(); ++i )
    {
        EXPECT_DOUBLE_EQ( tab1.getValue( key_values[ i ] ), tab.getValue( key_values[ i ] ) );
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetKeyByIndex)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getKeyByIndex( 0 ), -2.0 );
    EXPECT_DOUBLE_EQ( tab.getKeyByIndex( 1 ), -1.0 );
    EXPECT_DOUBLE_EQ( tab.getKeyByIndex( 2 ),  0.0 );
    EXPECT_DOUBLE_EQ( tab.getKeyByIndex( 3 ),  1.0 );
    EXPECT_DOUBLE_EQ( tab.getKeyByIndex( 4 ),  2.0 );
    EXPECT_DOUBLE_EQ( tab.getKeyByIndex( 5 ),  3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetKeyByIndexNotInited)
{
    mc::Table tab;
    EXPECT_TRUE( std::isnan( tab.getKeyByIndex( 0 ) ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetSize)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_EQ( tab.getSize(), 6 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetKeyOfValueMin)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getKeyOfValueMin(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetKeyOfValueMinRanged)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getKeyOfValueMin( 1.0, 2.0 ), 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetKeyOfValueMax)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getKeyOfValueMax(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetKeyOfValueMaxRanged)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getKeyOfValueMax( 1.0, 2.0 ), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetValue)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getValue( 2.0 ), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetValueAndInterpolate)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getValue( 2.5 ), 5.5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetValueOutOfRange)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getValue( -9.0 ), 1.0 );
    EXPECT_DOUBLE_EQ( tab.getValue(  9.0 ), 8.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetValueNotInited)
{
    mc::Table tab;
    EXPECT_TRUE( std::isnan( tab.getValue( 0.0 ) ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetValueByIndex)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getValueByIndex( 0 ), table_data[ 0 ] );
    EXPECT_DOUBLE_EQ( tab.getValueByIndex( 1 ), table_data[ 1 ] );
    EXPECT_DOUBLE_EQ( tab.getValueByIndex( 2 ), table_data[ 2 ] );
    EXPECT_DOUBLE_EQ( tab.getValueByIndex( 3 ), table_data[ 3 ] );
    EXPECT_DOUBLE_EQ( tab.getValueByIndex( 4 ), table_data[ 4 ] );
    EXPECT_DOUBLE_EQ( tab.getValueByIndex( 5 ), table_data[ 5 ] );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetValueByIndexNotInited)
{
    mc::Table tab;
    EXPECT_TRUE( std::isnan( tab.getValueByIndex( 0 ) ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetFirstValue)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getFirstValue(), table_data[ 0 ] );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetFirstValueNotInited)
{
    mc::Table tab;
    EXPECT_TRUE( std::isnan( tab.getFirstValue() ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetLastValue)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getLastValue(), table_data[ 5 ] );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetLastValueNotInited)
{
    mc::Table tab;
    EXPECT_TRUE( std::isnan( tab.getLastValue() ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetValueMin)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getValueMin(), -1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetValueMinNotInited)
{
    mc::Table tab;
    EXPECT_TRUE( std::isnan( tab.getValueMin() ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetValueMax)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_DOUBLE_EQ( tab.getValueMax(), 8.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanGetValueMaxNotInited)
{
    mc::Table tab;
    EXPECT_TRUE( std::isnan( tab.getValueMax() ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanValidate)
{
    std::vector< double > k1 { 0.0,  1.0,  2.0 };
    std::vector< double > v1 { 0.0,  1.0,  2.0 };
    mc::Table t1( k1, v1 );
    EXPECT_TRUE( t1.isValid() );

    std::vector< double > k2 { std::numeric_limits<double>::quiet_NaN(), 1.0, 2.0 };
    std::vector< double > v2 { 0.0, 1.0, 2.0 };
    mc::Table t2( k2, v2 );
    EXPECT_FALSE( t2.isValid() );

    std::vector< double > k3 { 0.0, 1.0, 2.0 };
    std::vector< double > v3 { std::numeric_limits<double>::quiet_NaN(), 1.0, 2.0 };
    mc::Table t3( k3, v3 );
    EXPECT_FALSE( t3.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanMultiplyKeys)
{
    const double coef = 2.0;

    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    tab.multiplyKeys( coef );

    for ( unsigned int i = 0; i < tab.getSize(); ++i )
    {
        EXPECT_DOUBLE_EQ( tab.getKeyByIndex( i ), key_values[ i ] * coef );
        EXPECT_DOUBLE_EQ( tab.getValue( key_values[ i ] * coef ), table_data[ i ] );
    }

    EXPECT_DOUBLE_EQ( tab.getValue( 1.5 * coef ), 1.5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanMultiplyValues)
{
    const double coef = 2.0;

    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab( key_values, table_data );

    tab.multiplyValues( coef );

    for ( unsigned int i = 0; i < tab.getSize(); ++i )
    {
        EXPECT_DOUBLE_EQ( tab.getKeyByIndex( i ), key_values[ i ] );
        EXPECT_DOUBLE_EQ( tab.getValue( key_values[ i ] ), table_data[ i ] * coef );
    }

    EXPECT_DOUBLE_EQ( tab.getValue( 1.5 ), 1.5 * coef );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanConvertToString)
{
    std::vector< double > key_values { 0.0,  1.0,  2.0 };
    std::vector< double > table_data { 0.0,  2.0,  4.0 };

    mc::Table tab( key_values, table_data );

    EXPECT_STREQ( tab.toString().c_str(), "0\t0\n1\t2\n2\t4\n" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanSetDataFromArray)
{
    // y = x^2 - 1
    double key_values[] { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    double table_data[] {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab;
    tab.setData( key_values, table_data, 6 );

    for ( unsigned int i = 0; i < tab.getSize(); ++i )
    {
        EXPECT_DOUBLE_EQ( tab.getValue( key_values[ i ] ), table_data[ i ] );
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanSetDataFromVector)
{
    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab;
    tab.setData( key_values, table_data );

    for ( unsigned int i = 0; i < key_values.size(); ++i )
    {
        EXPECT_DOUBLE_EQ( tab.getValue( key_values[ i ] ), table_data[ i ] );
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanSetFromString)
{
    char str[] =
    { R"##(
      -2.0  4.0
      -1.0  1.0
       0.0  0.0
       1.0  1.0
       2.0  4.0
       3.0  9.0
    )##" };
    mc::Table tab;
    tab.setFromString( str );

    EXPECT_TRUE( tab.isValid() );

    EXPECT_EQ( tab.getSize(), 6 );

    for ( int i = 0; i < 6; ++i )
    {
        double x = i - 2;
        double y = x*x;
        EXPECT_DOUBLE_EQ( tab.getValue( x ), y );
    }

    char str2[] = { "lorem ipsum" };
    mc::Table tab2;
    tab2.setFromString( str2 );
    EXPECT_FALSE( tab2.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanAdd)
{
    mc::Table tab;

    double k0[] { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    double t1[] {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 }; // y = x^2 - 1
    double t2[] { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 }; // y = x

    mc::Table tab1( k0, t1, 6 );
    mc::Table tab2( k0, t2, 6 );

    tab = tab1 + tab2;

    for ( unsigned int i = 0; i < tab.getSize(); ++i )
    {
        EXPECT_DOUBLE_EQ( tab.getKeyByIndex( i ), k0[ i ] );
        EXPECT_DOUBLE_EQ( tab.getValue( k0[ i ] ), t1[ i ] + t2[ i ] );
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestTable, CanMultiply)
{
    mc::Table tab;

    const double coef = 2.0;

    // y = x^2 - 1
    std::vector< double > key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector< double > table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table t1( key_values, table_data );

    tab = t1 * coef;

    for ( unsigned int i = 0; i < tab.getSize(); ++i )
    {
        EXPECT_DOUBLE_EQ( tab.getKeyByIndex( i ), key_values[ i ] );
        EXPECT_DOUBLE_EQ( tab.getValue( key_values[ i ] ), table_data[ i ] * coef );
    }

    EXPECT_DOUBLE_EQ( tab.getValue( 1.5 ), 3.0 );
}
