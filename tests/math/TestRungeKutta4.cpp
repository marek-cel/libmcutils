#include <gtest/gtest.h>

#include <mcutils/math/RungeKutta4.h>

#include <DiffEquationSolver.h>

////////////////////////////////////////////////////////////////////////////////

class TestRungeKutta4 : public ::testing::Test
{
protected:
    TestRungeKutta4() {}
    virtual ~TestRungeKutta4() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestRungeKutta4, CanConstruct)
{
    mc::RungeKutta4 *rk = nullptr;
    EXPECT_NO_THROW( rk = new mc::RungeKutta4() );
    delete rk;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestRungeKutta4, CanDestruct)
{
    mc::RungeKutta4 *rk = new mc::RungeKutta4();
    EXPECT_NO_THROW( delete rk );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestRungeKutta4, CanInstantiate)
{
    mc::RungeKutta4 rk;
    EXPECT_FALSE( rk.isDerivFunSet() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestRungeKutta4, CanInstantiateAndSetFun)
{
    std::function<void(const mc::VectorN &, mc::VectorN *)> fun =
            [](const mc::VectorN &, mc::VectorN *){};
    mc::RungeKutta4 rk( fun );
    EXPECT_TRUE( rk.isDerivFunSet() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestRungeKutta4, CanSolve)
{
    mc::RungeKutta4 rk1;
    DiffEquationSolver des1( 1.0, 1.0, 3.0, &rk1 );
    EXPECT_TRUE( des1.solve( 0.0, 1.0 ) );

    mc::RungeKutta4 rk2;
    DiffEquationSolver des2( 1.0, 1.0, 3.0, &rk2 );
    EXPECT_TRUE( des2.solve( 1.0, 0.0 ) );

    mc::RungeKutta4 rk3;
    DiffEquationSolver des3( 1.0, 1.0, 3.0, &rk3 );
    EXPECT_TRUE( des3.solve( 1.0, 1.0 ) );

    mc::RungeKutta4 rk4;
    DiffEquationSolver des4( 1.0, 1.0, 1.0, &rk4 );
    EXPECT_TRUE( des4.solve( 0.0, 1.0 ) );

    mc::RungeKutta4 rk5;
    DiffEquationSolver des5( 1.0, 1.0, 1.0, &rk5 );
    EXPECT_TRUE( des5.solve( 1.0, 0.0 ) );

    mc::RungeKutta4 rk6;
    DiffEquationSolver des6( 1.0, 1.0, 1.0, &rk6 );
    EXPECT_TRUE( des6.solve( 1.0, 1.0 ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestRungeKutta4, CanSetDerivFun)
{
    mc::RungeKutta4 rk;
    EXPECT_NO_THROW( rk.setDerivFun( [](const mc::VectorN &, mc::VectorN *ds)
    {
        for ( unsigned int i = 0; i < ds->getSize(); ++i )
        {
            (*ds)(i) = 1.0;
        }
    } ) );
    EXPECT_TRUE( rk.isDerivFunSet() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestRungeKutta4, CanCheckIfDerivFunIsSet)
{
    mc::RungeKutta4 rk;
    EXPECT_FALSE( rk.isDerivFunSet() );
    rk.setDerivFun( [](const mc::VectorN &, mc::VectorN *ds)
    {
        for ( unsigned int i = 0; i < ds->getSize(); ++i )
        {
            (*ds)(i) = 1.0;
        }
    } );
    EXPECT_TRUE( rk.isDerivFunSet() );
}
