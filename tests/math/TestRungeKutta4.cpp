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
    EXPECT_FALSE( static_cast<bool>(rk.deriv_fun()) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestRungeKutta4, CanSolve)
{
    mc::RungeKutta4 rk1;
    DiffEquationSolver des1(1.0, 1.0, 3.0, &rk1);
    EXPECT_TRUE( des1.Solve(0.0, 1.0) );

    mc::RungeKutta4 rk2;
    DiffEquationSolver des2(1.0, 1.0, 3.0, &rk2);
    EXPECT_TRUE( des2.Solve(1.0, 0.0) );

    mc::RungeKutta4 rk3;
    DiffEquationSolver des3(1.0, 1.0, 3.0, &rk3);
    EXPECT_TRUE( des3.Solve(1.0, 1.0) );

    mc::RungeKutta4 rk4;
    DiffEquationSolver des4(1.0, 1.0, 1.0, &rk4);
    EXPECT_TRUE( des4.Solve(0.0, 1.0) );

    mc::RungeKutta4 rk5;
    DiffEquationSolver des5(1.0, 1.0, 1.0, &rk5);
    EXPECT_TRUE( des5.Solve(1.0, 0.0) );

    mc::RungeKutta4 rk6;
    DiffEquationSolver des6(1.0, 1.0, 1.0, &rk6);
    EXPECT_TRUE( des6.Solve(1.0, 1.0) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestRungeKutta4, CanSetDerivFun)
{
    mc::RungeKutta4 rk;
    EXPECT_NO_THROW( rk.set_deriv_fun( [](const mc::Vector &, mc::Vector *ds)
    {
        for ( unsigned int i = 0; i < ds->size(); ++i )
        {
            (*ds)(i) = 1.0;
        }
    } ));
    EXPECT_TRUE( static_cast<bool>(rk.deriv_fun()) );
}
