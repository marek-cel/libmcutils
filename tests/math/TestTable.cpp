#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/math/Table.h>

class TestTable : public ::testing::Test
{
protected:
    TestTable() {}
    virtual ~TestTable() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestTable, CanInstantiate)
{
    mc::Table tab1;
    EXPECT_EQ(tab1.size(), 1);
    EXPECT_DOUBLE_EQ(tab1.GetValue(0.0), 0.0);
    EXPECT_DOUBLE_EQ(tab1.GetValue(1.7), 0.0);

    mc::Table tab2(2.2, 1.7);
    EXPECT_EQ(tab2.size(), 1);
    EXPECT_DOUBLE_EQ(tab2.GetValue(0.0), 2.2);
    EXPECT_DOUBLE_EQ(tab2.GetValue(1.7), 2.2);
}

TEST_F(TestTable, CanInstantiateAndSetDataFromArray)
{
    // y = x^2 - 1
    double key_values[] { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    double table_data[] {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data, 6);

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.GetValue(key_values[i]), table_data[i]);
    }
}

TEST_F(TestTable, CanInstantiateAndSetDataFromVector)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    for ( unsigned int i = 0; i < key_values.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.GetValue(key_values[i]), table_data[i]);
    }
}

TEST_F(TestTable, CanInstantiateAndCopy)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);
    mc::Table tab1(tab);

    for ( unsigned int i = 0; i < key_values.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab1.GetValue(key_values[i]), tab.GetValue(key_values[i]));
    }
}

TEST_F(TestTable, CanInstantiateAndMove)
{
    // y = x^2 - 1
    double key_values[] { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    double table_data[] {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(std::move(mc::Table(key_values, table_data, 6)));

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.GetValue(key_values[i]), table_data[i]);
    }
}

TEST_F(TestTable, CanGetKeyByIndex)
{
    mc::Table tab0;
    EXPECT_DOUBLE_EQ(tab0.GetKeyByIndex(0), 0.0);

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetKeyByIndex(0), -2.0);
    EXPECT_DOUBLE_EQ(tab.GetKeyByIndex(1), -1.0);
    EXPECT_DOUBLE_EQ(tab.GetKeyByIndex(2),  0.0);
    EXPECT_DOUBLE_EQ(tab.GetKeyByIndex(3),  1.0);
    EXPECT_DOUBLE_EQ(tab.GetKeyByIndex(4),  2.0);
    EXPECT_DOUBLE_EQ(tab.GetKeyByIndex(5),  3.0);
}

TEST_F(TestTable, CanGetKeyByIndexNotInited)
{
    mc::Table tab;
    EXPECT_TRUE(std::isnan(tab.GetKeyByIndex(1)));
}

TEST_F(TestTable, CanGetSize)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_EQ(tab.size(), 6);
}

TEST_F(TestTable, CanGetKeyOfValueMin)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetKeyOfValueMin(), 0.0);
}

TEST_F(TestTable, CanGetKeyOfValueMinRanged)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetKeyOfValueMin(-2.0, 0.0), 0.0);
}

TEST_F(TestTable, CanGetKeyOfValueMax)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetKeyOfValueMax(), 3.0);
}

TEST_F(TestTable, CanGetKeyOfValueMaxRanged)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetKeyOfValueMax(1.0, 2.0), 2.0);
}

TEST_F(TestTable, CanGetValue)
{
    mc::Table tab0;
    EXPECT_DOUBLE_EQ(tab0.GetValue(0.0), 0.0);
    EXPECT_DOUBLE_EQ(tab0.GetValue(1.7), 0.0);

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetValue(2.0), 3.0);
}

TEST_F(TestTable, CanGetValueFromEmptyTable)
{
    double key_values[] { 0.0 };
    double table_data[] { 0.0 };
    mc::Table tab(key_values, table_data, 0);
    double x = tab.GetValue(0.0);
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestTable, CanGetValueAndInterpolate)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetValue(2.5), 5.5);
}

TEST_F(TestTable, CanGetValueOutOfRange)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetValue( -9.0 ), 1.0);
    EXPECT_DOUBLE_EQ(tab.GetValue(  9.0 ), 8.0);
}

TEST_F(TestTable, CanGetValueByIndex)
{
    mc::Table tab0;
    EXPECT_DOUBLE_EQ(tab0.GetValueByIndex(0), 0.0);
    EXPECT_TRUE(std::isnan(tab0.GetValueByIndex(1)));

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetValueByIndex(0), table_data[0]);
    EXPECT_DOUBLE_EQ(tab.GetValueByIndex(1), table_data[1]);
    EXPECT_DOUBLE_EQ(tab.GetValueByIndex(2), table_data[2]);
    EXPECT_DOUBLE_EQ(tab.GetValueByIndex(3), table_data[3]);
    EXPECT_DOUBLE_EQ(tab.GetValueByIndex(4), table_data[4]);
    EXPECT_DOUBLE_EQ(tab.GetValueByIndex(5), table_data[5]);
}

TEST_F(TestTable, CanGetFirstValue)
{
    mc::Table tab0;
    EXPECT_DOUBLE_EQ(tab0.GetFirstValue(), 0.0);

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetFirstValue(), table_data[0]);
}

TEST_F(TestTable, CanGetFirstValueFromEmptyTable)
{
    double key_values[] { 0.0 };
    double table_data[] { 0.0 };
    mc::Table tab(key_values, table_data, 0);
    double x = tab.GetFirstValue();
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestTable, CanGetLastValue)
{
    mc::Table tab0;
    EXPECT_DOUBLE_EQ( tab0.GetLastValue(), 0.0 );

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetLastValue(), table_data[5]);
}

TEST_F(TestTable, CanGetLastValueFromEmptyTable)
{
    double key_values[] { 0.0 };
    double table_data[] { 0.0 };
    mc::Table tab(key_values, table_data, 0);
    double x = tab.GetLastValue();
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestTable, CanGetValueMin)
{
    mc::Table tab0;
    EXPECT_DOUBLE_EQ(tab0.GetValueMin(), 0.0);

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetValueMin(), -1.0);
}

TEST_F(TestTable, CanGetValueMinFromEmptyTable)
{
    double key_values[] { 0.0 };
    double table_data[] { 0.0 };
    mc::Table tab(key_values, table_data, 0);
    double x = tab.GetValueMin();
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestTable, CanGetValueMax)
{
    mc::Table tab0;
    EXPECT_NEAR(tab0.GetValueMax(), 0.0, 1.0e-16);

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.GetValueMax(), 8.0);
}

TEST_F(TestTable, CanGetValueMaxFromEmptyTable)
{
    double key_values[] { 0.0 };
    double table_data[] { 0.0 };
    mc::Table tab(key_values, table_data, 0);
    double x = tab.GetValueMin();
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestTable, CanValidate)
{
    std::vector<double> k1 { 0.0,  1.0,  2.0 };
    std::vector<double> v1 { 0.0,  1.0,  2.0 };
    mc::Table t1(k1, v1);
    EXPECT_TRUE(t1.IsValid());

    std::vector<double> k2 { std::numeric_limits<double>::quiet_NaN(), 1.0, 2.0 };
    std::vector<double> v2 { 0.0, 1.0, 2.0 };
    mc::Table t2(k2, v2);
    EXPECT_FALSE(t2.IsValid());

    std::vector<double> k3 { 0.0, 1.0, 2.0 };
    std::vector<double> v3 { std::numeric_limits<double>::quiet_NaN(), 1.0, 2.0 };
    mc::Table t3(k3, v3);
    EXPECT_FALSE(t3.IsValid());
}

TEST_F(TestTable, CanMultiplyKeys)
{
    const double coef = 2.0;

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    tab.MultiplyKeys(coef);

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.GetKeyByIndex(i), key_values[i] * coef);
        EXPECT_DOUBLE_EQ(tab.GetValue(key_values[i] * coef), table_data[i]);
    }

    EXPECT_DOUBLE_EQ(tab.GetValue(1.5 * coef), 1.5);
}

TEST_F(TestTable, CanMultiplyValues)
{
    const double coef = 2.0;

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab(key_values, table_data);

    tab.MultiplyValues(coef);

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.GetKeyByIndex(i), key_values[i]);
        EXPECT_DOUBLE_EQ(tab.GetValue(key_values[i]), table_data[i] * coef);
    }

    EXPECT_DOUBLE_EQ(tab.GetValue(1.5), 1.5 * coef);
}

TEST_F(TestTable, CanConvertToString)
{
    std::vector<double> key_values { 0.0,  1.0,  2.0 };
    std::vector<double> table_data { 0.0,  2.0,  4.0 };

    mc::Table tab(key_values, table_data);

    EXPECT_STREQ(tab.ToString().c_str(), "0\t0\n1\t2\n2\t4\n");
}

TEST_F(TestTable, CanSetDataFromArray)
{
    // y = x^2 - 1
    double key_values[] { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    double table_data[] {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab;
    tab.SetData(key_values, table_data, 6);

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.GetValue(key_values[i]), table_data[i]);
    }
}

TEST_F(TestTable, CanSetDataFromVector)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab;
    tab.SetData(key_values, table_data);

    for ( unsigned int i = 0; i < key_values.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.GetValue(key_values[i]), table_data[i]);
    }
}

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
    tab.SetFromString(str);

    EXPECT_TRUE(tab.IsValid());

    EXPECT_EQ(tab.size(), 6);

    for ( int i = 0; i < 6; ++i )
    {
        double x = i - 2;
        double y = x*x;
        EXPECT_DOUBLE_EQ(tab.GetValue(x), y);
    }

    char str2[] = { "lorem ipsum" };
    mc::Table tab2;
    tab2.SetFromString(str2);
    EXPECT_FALSE(tab2.IsValid());
}

TEST_F(TestTable, CanAdd)
{
    mc::Table tab;

    double k0[] { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    double t1[] {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 }; // y = x^2 - 1
    double t2[] { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 }; // y = x

    mc::Table tab1(k0, t1, 6);
    mc::Table tab2(k0, t2, 6);

    tab = tab1 + tab2;

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.GetKeyByIndex(i), k0[i]);
        EXPECT_DOUBLE_EQ(tab.GetValue(k0[i]), t1[i] + t2[i]);
    }
}

TEST_F(TestTable, CanMultiply)
{
    mc::Table tab;

    const double coef = 2.0;

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table t1(key_values, table_data);

    tab = t1 * coef;

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.GetKeyByIndex(i), key_values[i]);
        EXPECT_DOUBLE_EQ(tab.GetValue(key_values[i]), table_data[i] * coef);
    }

    EXPECT_DOUBLE_EQ(tab.GetValue(1.5), 3.0);
}

TEST_F(TestTable, CanAssign)
{
    // y = x^2 - 1
    double key_values[] { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    double table_data[] {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab1(key_values, table_data, 6);
    mc::Table tab;

    tab = tab1;

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.GetValue(key_values[i]), table_data[i]);
    }
}

TEST_F(TestTable, CanAssignAndMove)
{
    // y = x^2 - 1
    double key_values[] { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    double table_data[] {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table tab;
    tab = std::move(mc::Table(key_values, table_data, 6));

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.GetValue(key_values[i]), table_data[i]);
    }
}