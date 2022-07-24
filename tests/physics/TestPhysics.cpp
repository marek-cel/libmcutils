#include <gtest/gtest.h>

#include <mcutils/physics/Physics.h>

#include <mcutils/math/Matrix3x3.h>
#include <mcutils/math/Vector3.h>

#include <XcosBinFileReader.h>

////////////////////////////////////////////////////////////////////////////////

class TestPhysics : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP     { 0.1 };
    static constexpr double TIME_CONSTANT { 2.0 };

    TestPhysics() {}
    virtual ~TestPhysics() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, IsSpeedOfLightCorrect)
{
    // The International System of Units (SI) 9th edition, p.127
    EXPECT_NEAR( mc::Physics::speedOfLight, 299'792'458.0, 1.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, IsGravitationalConstCorrect)
{
    // The International System of Units: Physical Constants and Conversion Factors, NASA-SP-7012, p.9
    EXPECT_NEAR( mc::Physics::gravitationalConst, 6.6732e-11, 1.0e-14 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, IsAvogadroConstCorrect)
{
    // The International System of Units (SI) 9th edition, p.127
    EXPECT_NEAR( mc::Physics::avogadroConst, 6.02214076e23, 1.0e16 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, IsBoltzmannConstCorrect)
{
    // The International System of Units (SI) 9th edition, p.127
    EXPECT_NEAR( mc::Physics::boltzmannConst, 1.380649e-23, 1.0e-28 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, IsUniversalGasConstCorrect)
{
    // The International System of Units: Physical Constants and Conversion Factors, NASA-SP-7012, p.9
    EXPECT_NEAR( mc::Physics::universalGasConst, 8.31434e3, 1.0e-2 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, IsFaradayConstCorrect)
{
    // The International System of Units (SI) 9th edition, p.127
    EXPECT_NEAR( mc::Physics::faradayConst, 9.64867e7, 1.0e-2 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, IsPlanckConstCorrect)
{
    // The International System of Units (SI) 9th edition, p.127
    EXPECT_NEAR( mc::Physics::planckConst, 6.62607015e-34, 1.0e-41 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, IsElementaryChargeCorrect)
{
    // The International System of Units (SI) 9th edition, p.127
    EXPECT_NEAR( mc::Physics::elementaryCharge, 1.602176634e-19, 1.0e-27 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, IsStefanBoltzmanConstCorrect)
{
    // The International System of Units: Physical Constants and Conversion Factors, NASA-SP-7012, p.9
    EXPECT_NEAR( mc::Physics::stefanBoltzmanConst, 5.66961e-8, 1.0e-12 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, IsStandardGravityCorrect)
{
    // The International System of Units (SI) 9th edition, p.159
    EXPECT_NEAR( mc::Physics::standardGravity, 9.80665, 1.0e-4 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, CanComputeInertia)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/math/xcos/test_inertia.xcos
    XcosBinFileReader::readData( "../tests/physics/data/test_inertia.bin", &vals );

    EXPECT_GT( vals.size(), 0 ) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    double u_prev = 0.0;
    double y_prev = 0.0;

    for ( unsigned int i = 0; i < vals.size(); i++ )
    {
        double u = ( t < 0.99 ) ? 0.0 : 1.0;

        int steps = 10;
        for ( int j = 0; j < steps; j++ )
        {
            double dt = TIME_STEP / (double)steps;
            y = mc::Physics::inertia( u, y, dt, TIME_CONSTANT );

            if ( 0 )
            {
                double c1 = 1.0 / TIME_CONSTANT;
                double denom = 2.0 + dt * c1;
                double ca = dt * c1 / denom;
                double cb = ( 2.0 - dt * c1 ) / denom;

                y = ( u + u_prev ) * ca + y_prev * cb;

                u_prev = u;
                y_prev = y;
            }
        }

        EXPECT_NEAR( y, vals.at( i ), 1.0e-3 );

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, CanComputeInertiaTimeConst0)
{
    double y = 0.0;

    for ( unsigned int i = 0; i < 100; i++ )
    {
        double u = ( i < 10 ) ? 0.0 : 1.0;
        y = mc::Physics::inertia( u, y, 0.01, 0.0 );
        EXPECT_NEAR( y, u, 1.0e-3 );
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, DISABLED_CanComputePacejkaFormula)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestPhysics, CanComputeParallelAxisInertia)
{
    // https://en.wikipedia.org/wiki/List_of_moments_of_inertia

    constexpr double l = 1.0;
    constexpr double m = 1.0;

    // Slender rod along y-axis of length l and mass m about center
    mc::Matrix3x3 m1( m*l*l / 12.0, 0.0, 0.0,
                      0.0, 0.0, 0.0,
                      0.0, 0.0, m*l*l / 12.0);

    // Slender rod along y-axis of length l and mass m about end
    mc::Matrix3x3 m2( m*l*l / 3.0, 0.0, 0.0,
                      0.0, 0.0, 0.0,
                      0.0, 0.0, m*l*l / 3.0);

    mc::Vector3 r( 0.0, l / 2.0, 0.0 );

    mc::Matrix3x3 m3 = mc::Physics::parallelAxisInertia( m, m1, r );

    EXPECT_NEAR( m3(0,0), m2(0,0), 1.0e-12 );
    EXPECT_NEAR( m3(0,1), m2(0,1), 1.0e-12 );
    EXPECT_NEAR( m3(0,2), m2(0,2), 1.0e-12 );

    EXPECT_NEAR( m3(1,0), m2(1,0), 1.0e-12 );
    EXPECT_NEAR( m3(1,1), m2(1,1), 1.0e-12 );
    EXPECT_NEAR( m3(1,2), m2(1,2), 1.0e-12 );

    EXPECT_NEAR( m3(2,0), m2(2,0), 1.0e-12 );
    EXPECT_NEAR( m3(2,1), m2(2,1), 1.0e-12 );
    EXPECT_NEAR( m3(2,2), m2(2,2), 1.0e-12 );
}
