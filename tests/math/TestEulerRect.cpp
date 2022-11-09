#include <gtest/gtest.h>

#include <functional>

#include <mcutils/math/EulerRect.h>

#include <DiffEquationSolver.h>

////////////////////////////////////////////////////////////////////////////////

class TestEulerRect : public ::testing::Test
{
protected:
    TestEulerRect() {}
    virtual ~TestEulerRect() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestEulerRect, CanConstruct)
{
    mc::EulerRect *er = nullptr;
    EXPECT_NO_THROW( er = new mc::EulerRect() );
    delete er;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestEulerRect, CanDestruct)
{
    mc::EulerRect *er = new mc::EulerRect();
    EXPECT_NO_THROW( delete er );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestEulerRect, CanInstantiate)
{
    mc::EulerRect er;
    EXPECT_FALSE( er.isDerivFunSet() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestEulerRect, CanInstantiateAndSetFun)
{
    std::function<void(const mc::VectorN &, mc::VectorN *)> fun =
            [](const mc::VectorN &, mc::VectorN *){};
    mc::EulerRect er( fun );
    EXPECT_TRUE( er.isDerivFunSet() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestEulerRect, CanSolve)
{
    mc::EulerRect er1;
    DiffEquationSolver des1( 1.0, 1.0, 3.0, &er1 );
    EXPECT_TRUE( des1.solve( 0.0, 1.0 ) );

    mc::EulerRect er2;
    DiffEquationSolver des2( 1.0, 1.0, 3.0, &er2 );
    EXPECT_TRUE( des2.solve( 1.0, 0.0 ) );

    mc::EulerRect er3;
    DiffEquationSolver des3( 1.0, 1.0, 3.0, &er3 );
    EXPECT_TRUE( des3.solve( 1.0, 1.0 ) );

    mc::EulerRect er4;
    DiffEquationSolver des4( 1.0, 1.0, 1.0, &er4 );
    EXPECT_TRUE( des4.solve( 0.0, 1.0 ) );

    mc::EulerRect er5;
    DiffEquationSolver des5( 1.0, 1.0, 1.0, &er5 );
    EXPECT_TRUE( des5.solve( 1.0, 0.0 ) );

    mc::EulerRect er6;
    DiffEquationSolver des6( 1.0, 1.0, 1.0, &er6 );
    EXPECT_TRUE( des6.solve( 1.0, 1.0 ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestEulerRect, CanSetDerivFun)
{
    mc::EulerRect er;
    EXPECT_NO_THROW( er.setDerivFun( [](const mc::VectorN &, mc::VectorN *ds)
    {
        for ( unsigned int i = 0; i < ds->getSize(); ++i )
        {
            (*ds)(i) = 1.0;
        }
    } ) );
    EXPECT_TRUE( er.isDerivFunSet() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestEulerRect, CanCheckIfDerivFunIsSet)
{
    mc::EulerRect er;
    EXPECT_FALSE( er.isDerivFunSet() );
    er.setDerivFun( [](const mc::VectorN &, mc::VectorN *ds)
    {
        for ( unsigned int i = 0; i < ds->getSize(); ++i )
        {
            (*ds)(i) = 1.0;
        }
    } );
    EXPECT_TRUE( er.isDerivFunSet() );
}
