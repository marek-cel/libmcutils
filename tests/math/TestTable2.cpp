#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/math/Table2.h>

class TestTable2 : public ::testing::Test
{
protected:
    TestTable2() {}
    virtual ~TestTable2() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestTable2, CanInstantiate)
{
    mc::Table2<double,double,double> tab;

    EXPECT_EQ(tab.rows(), 1);
    EXPECT_EQ(tab.cols(), 1);
    EXPECT_DOUBLE_EQ(tab.GetValue(0.0, 0.0), 0.0);
    EXPECT_DOUBLE_EQ(tab.GetValue(2.2, 3.3), 0.0);

    mc::Table2<double,double,double> tab2(1.1, 2.2, 3.3);
    EXPECT_EQ(tab2.rows(), 1);
    EXPECT_EQ(tab2.cols(), 1);
    EXPECT_DOUBLE_EQ(tab2.GetValue(0.0, 0.0), 1.1);
    EXPECT_DOUBLE_EQ(tab2.GetValue(2.2, 3.3), 1.1);
}

TEST_F(TestTable2, CanInstantiateAndCopy)
{
    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab1(r, c, v);

    mc::Table2<double,double,double> tab(tab1);

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.rows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.cols(); ++ic )
        {
             EXPECT_DOUBLE_EQ(tab.GetValue( r[ir], c[ic] ), fun(ir,ic)) << "ir= " << ir << " ic= " << ic;
        }
    }

    EXPECT_EQ(tab.rows(), 4);
    EXPECT_EQ(tab.cols(), 2);
}

TEST_F(TestTable2, CanInstantiateAndMove)
{
    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab(std::move(mc::Table2<double,double,double>(r, c, v)));

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.rows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.cols(); ++ic )
        {
             EXPECT_DOUBLE_EQ(tab.GetValue(r[ir], c[ic]), fun(ir,ic)) << "ir= " << ir << " ic= " << ic;
        }
    }

    EXPECT_EQ(tab.rows(), 4);
    EXPECT_EQ(tab.cols(), 2);
}

TEST_F(TestTable2, CanInstantiateAndSetDataFromArray)
{
    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v
    {
        0.0,  1.0,
       -1.0,  0.0,
        0.0,  1.0,
        3.0,  4.0
    };

    mc::Table2<double,double,double> tab(r, c, v);

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.rows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.cols(); ++ic )
        {
             EXPECT_DOUBLE_EQ(tab.GetValue(r[ir], c[ic]), fun(ir,ic)) << "ir= " << ir << " ic= " << ic;
        }
    }

    EXPECT_EQ(tab.rows(), 4);
    EXPECT_EQ(tab.cols(), 2);
}

TEST_F(TestTable2, CanInstantiateAndSetDataFromVector)
{
    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab(r, c, v);

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.rows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.cols(); ++ic )
        {
             EXPECT_DOUBLE_EQ(tab.GetValue(r[ir], c[ic]), fun(ir,ic)) << "ir= " << ir << " ic= " << ic;
        }
    }

    EXPECT_EQ(tab.rows(), 4);
    EXPECT_EQ(tab.cols(), 2);
}

TEST_F(TestTable2, CanGetRows)
{
    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v
    {
        0.0,  1.0,
       -1.0,  0.0,
        0.0,  1.0,
        3.0,  4.0
    };

    mc::Table2<double,double,double> tab(r, c, v);

    EXPECT_EQ(tab.rows(), 4);
}

TEST_F(TestTable2, CanGetCols)
{
    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v
    {
        0.0,  1.0,
       -1.0,  0.0,
        0.0,  1.0,
        3.0,  4.0
    };

    mc::Table2<double,double,double> tab(r, c, v);

    EXPECT_EQ(tab.cols(), 2);
}

TEST_F(TestTable2, CanGetTable)
{
    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v
    {
        0.0,  1.0,
       -1.0,  0.0,
        0.0,  1.0,
        3.0,  4.0
    };

    mc::Table2<double,double,double> tab(r, c, v);

    mc::Table tab0 = tab.GetTable(0);
    mc::Table tab1 = tab.GetTable(1);

    EXPECT_DOUBLE_EQ(tab0.GetKeyByIndex(0), -1.0);
    EXPECT_DOUBLE_EQ(tab0.GetKeyByIndex(1),  0.0);
    EXPECT_DOUBLE_EQ(tab0.GetKeyByIndex(2),  1.0);
    EXPECT_DOUBLE_EQ(tab0.GetKeyByIndex(3),  2.0);

    EXPECT_DOUBLE_EQ(tab0.GetValue( -1.0 ),  0.0);
    EXPECT_DOUBLE_EQ(tab0.GetValue(  0.0 ), -1.0);
    EXPECT_DOUBLE_EQ(tab0.GetValue(  1.0 ),  0.0);
    EXPECT_DOUBLE_EQ(tab0.GetValue(  2.0 ),  3.0);

    EXPECT_DOUBLE_EQ(tab1.GetKeyByIndex(0), -1.0);
    EXPECT_DOUBLE_EQ(tab1.GetKeyByIndex(1),  0.0);
    EXPECT_DOUBLE_EQ(tab1.GetKeyByIndex(2),  1.0);
    EXPECT_DOUBLE_EQ(tab1.GetKeyByIndex(3),  2.0);

    EXPECT_DOUBLE_EQ(tab1.GetValue( -1.0 ),  1.0);
    EXPECT_DOUBLE_EQ(tab1.GetValue(  0.0 ),  0.0);
    EXPECT_DOUBLE_EQ(tab1.GetValue(  1.0 ),  1.0);
    EXPECT_DOUBLE_EQ(tab1.GetValue(  2.0 ),  4.0);
}

TEST_F(TestTable2, CanGetValue)
{
    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab(r, c, v);

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.rows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.cols(); ++ic )
        {
             EXPECT_DOUBLE_EQ(tab.GetValue(r[ir], c[ic]), fun(ir,ic)) << "ir= " << ir << " ic= " << ic;
        }
    }
}

TEST_F(TestTable2, CanGetValueInterpolate)
{
    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab(r, c, v);

    EXPECT_DOUBLE_EQ(tab.GetValue(  0.5, 0.0 ), -0.5);
    EXPECT_DOUBLE_EQ(tab.GetValue( -1.0, 0.5 ),  0.5);
    EXPECT_DOUBLE_EQ(tab.GetValue( -0.5, 0.5 ),  0.0);
}

TEST_F(TestTable2, CanGetValueOutOfRange)
{
    mc::Table2<double,double,double> tab0;
    EXPECT_DOUBLE_EQ(tab0.GetValue(0.0, 0.0), 0.0);
    EXPECT_DOUBLE_EQ(tab0.GetValue(3.0, 0.0), 0.0);

    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab(r, c, v);

    EXPECT_DOUBLE_EQ(tab.GetValue(  3.0,  0.0 ),  3.0);
    EXPECT_DOUBLE_EQ(tab.GetValue( -2.0,  0.0 ),  0.0);
    EXPECT_DOUBLE_EQ(tab.GetValue( -1.0,  2.0 ),  1.0);
    EXPECT_DOUBLE_EQ(tab.GetValue(  3.0,  2.0 ),  4.0);
    EXPECT_DOUBLE_EQ(tab.GetValue(  0.0, -1.0 ), -1.0);
}

TEST_F(TestTable2, CanGetValueByIndex)
{
    mc::Table2<double,double,double> tab0;
    EXPECT_DOUBLE_EQ(tab0.GetValueByIndex(0, 0), 0.0);
    EXPECT_TRUE(std::isnan(tab0.GetValueByIndex(1, 0)));
    EXPECT_TRUE(std::isnan(tab0.GetValueByIndex(0, 1)));
    EXPECT_TRUE(std::isnan(tab0.GetValueByIndex(1, 1)));

    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab(r, c, v);

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.rows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.cols(); ++ic )
        {
             EXPECT_DOUBLE_EQ(tab.GetValueByIndex(ir, ic), fun(ir,ic)) << "ir= " << ir << " ic= " << ic;
        }
    }
}

TEST_F(TestTable2, CanValidate)
{
    std::vector<double> r1 { 0.0, 1.0, 2.0 };
    std::vector<double> c1 { 0.0, 1.0 };
    std::vector<double> v1 { 0.0, 3.0,
                             1.0, 4.0,
                             2.0, 5.0 };
    mc::Table2<double,double,double> t1(r1, c1, v1);
    EXPECT_TRUE(t1.IsValid());

    std::vector<double> r2 { std::numeric_limits<double>::quiet_NaN(), 1.0, 2.0 };
    std::vector<double> c2 { 0.0, 1.0 };
    std::vector<double> v2 { 0.0, 3.0,
                             1.0, 4.0,
                             2.0, 5.0 };
    mc::Table2<double,double,double> t2(r2, c2, v2);
    EXPECT_FALSE(t2.IsValid());

    std::vector<double> r3 { 0.0, 1.0, 2.0 };
    std::vector<double> c3 { std::numeric_limits<double>::quiet_NaN(), 1.0 };
    std::vector<double> v3 { 0.0, 3.0,
                             1.0, 4.0,
                             2.0, 5.0 };
    mc::Table2<double,double,double> t3(r3, c3, v3);
    EXPECT_FALSE(t3.IsValid());

    std::vector<double> r4 { 0.0, 1.0, 2.0 };
    std::vector<double> c4 { 0.0, 1.0 };
    std::vector<double> v4 { std::numeric_limits<double>::quiet_NaN(), 3.0,
                             1.0, 4.0,
                             2.0, 5.0 };
    mc::Table2<double,double,double> t4(r4, c4, v4);
    EXPECT_FALSE(t4.IsValid());
}

TEST_F(TestTable2, CanMultiplyRows)
{
    const double r_coef = 2.0;

    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab(r, c, v);

    tab.MultiplyRows(r_coef);

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.rows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.cols(); ++ic )
        {
             EXPECT_DOUBLE_EQ(tab.GetValue(r_coef*r[ir], c[ic]), fun(ir,ic)) << "ir= " << ir << " ic= " << ic;
        }
    }
}

TEST_F(TestTable2, CanMultiplyCols)
{
    const double c_coef = 2.0;

    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab(r, c, v);

    tab.MultiplyCols(c_coef);

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.rows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.cols(); ++ic )
        {
             EXPECT_DOUBLE_EQ(tab.GetValue(r[ir], c_coef*c[ic]), fun(ir,ic)) << "ir= " << ir << " ic= " << ic;
        }
    }
}

TEST_F(TestTable2, CanMultiplyValues)
{
    const double v_coef = 2.0;

    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab(r, c, v);

    tab.MultiplyValues(v_coef);

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.rows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.cols(); ++ic )
        {
             EXPECT_DOUBLE_EQ(tab.GetValue(r[ir], c[ic]), v_coef*fun(ir,ic)) << "ir= " << ir << " ic= " << ic;
        }
    }
}

TEST_F(TestTable2, CanSetDataFromVector)
{
    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab;
    tab.SetData(r, c, v);

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.rows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.cols(); ++ic )
        {
             EXPECT_DOUBLE_EQ(tab.GetValue(r[ir], c[ic]), fun(ir,ic)) << "ir= " << ir << " ic= " << ic;
        }
    }

    EXPECT_EQ(tab.rows(), 4);
    EXPECT_EQ(tab.cols(), 2);
}

TEST_F(TestTable2, CanSetDataFromString)
{
    char str[] =
    { R"##(
             1.0  2.0  3.0
        1.0  2.0  3.0  4.0
        2.0  3.0  4.0  5.0
    )##" };

    mc::Table2<double,double,double> tab;
    tab.SetFromString(str);

    EXPECT_TRUE(tab.IsValid());

    EXPECT_EQ(tab.cols(), 3);
    EXPECT_EQ(tab.rows(), 2);

    for ( unsigned int ir = 0; ir < 2; ++ir )
    {
        for ( unsigned int ic = 0; ic < 3; ++ic )
        {
            double xr = ir + 1;
            double xc = ic + 1;
            double y = xr + xc;
            EXPECT_DOUBLE_EQ(tab.GetValue(xr, xc), y);
        }
    }

    char str2[] = { "lorem ipsum" };
    mc::Table2<double,double,double> tab2;
    tab2.SetFromString(str2);
    EXPECT_FALSE(tab2.IsValid());
}

TEST_F(TestTable2, CanConvertToString)
{
    // z = x^2 + y - 1
    std::vector<double> r { 0.0, 1.0, 2.0 };
    std::vector<double> c { 0.0, 1.0 };
    std::vector<double> v { 0.0, 1.0,
                            2.0, 3.0,
                            4.0, 5.0 };

    mc::Table2<double,double,double> tab(r, c, v);

    EXPECT_STREQ(tab.ToString().c_str(), "\t0\t1\n0\t0\t1\n1\t2\t3\n2\t4\t5\n");
}

TEST_F(TestTable2, CanAssign)
{
    mc::Table2<double,double,double> tab;

    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab1(r, c, v);

    tab = tab1;

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.rows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.cols(); ++ic )
        {
             EXPECT_DOUBLE_EQ(tab.GetValue(r[ir], c[ic]), fun(ir,ic)) << "ir= " << ir << " ic= " << ic;
        }
    }

    EXPECT_EQ(tab.rows(), 4);
    EXPECT_EQ(tab.cols(), 2);
}

TEST_F(TestTable2, CanAssignAndMove)
{
    // z = x^2 + y - 1
    std::vector<double> r { -1.0,  0.0,  1.0,  2.0 };
    std::vector<double> c {  0.0,  1.0 };
    std::vector<double> v {  0.0,  1.0,
                            -1.0,  0.0,
                             0.0,  1.0,
                             3.0,  4.0 };

    mc::Table2<double,double,double> tab;
    tab = std::move(mc::Table2<double,double,double>(r, c, v));

    auto fun = [&](int ir, int ic){ return r[ir]*r[ir] + c[ic] - 1.0; };

    for ( unsigned int ir = 0; ir < tab.rows(); ++ir )
    {
        for ( unsigned int ic = 0; ic < tab.cols(); ++ic )
        {
             EXPECT_DOUBLE_EQ(tab.GetValue(r[ir], c[ic]), fun(ir,ic)) << "ir= " << ir << " ic= " << ic;
        }
    }

    EXPECT_EQ(tab.rows(), 4);
    EXPECT_EQ(tab.cols(), 2);
}
