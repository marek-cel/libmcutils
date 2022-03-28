#include <gtest/gtest.h>

#include <mcutil/signal/MovingAverageFilter.h>
#include <mcutil/math/Random.h>

////////////////////////////////////////////////////////////////////////////////

class TestMovingAverageFilter : public ::testing::Test
{
protected:

    TestMovingAverageFilter() {}
    virtual ~TestMovingAverageFilter() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingAverageFilter, CanConstruct)
{
    mc::MovingAverageFilter *maf = nullptr;
    EXPECT_NO_THROW( maf = new mc::MovingAverageFilter() );
    delete maf;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingAverageFilter, CanDestruct)
{
    mc::MovingAverageFilter *maf = new mc::MovingAverageFilter();
    EXPECT_NO_THROW( delete maf );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingAverageFilter, CanInstantiate)
{
    mc::MovingAverageFilter maf;

    EXPECT_EQ( maf.getLength(), 1 );
    EXPECT_NEAR( maf.getValue(), 0.0, 1.0e-9 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingAverageFilter, CanInstantiateAndSetData)
{
    mc::MovingAverageFilter maf( 5, 1.0 );

    EXPECT_EQ( maf.getLength(), 5 );
    EXPECT_NEAR( maf.getValue(), 1.0, 1.0e-9 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingAverageFilter, CanSetLenght)
{
    mc::MovingAverageFilter maf;

    EXPECT_NO_THROW( maf.setLength( 5 ) );
    EXPECT_EQ( maf.getLength(), 5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingAverageFilter, CanGetLenght)
{
    mc::MovingAverageFilter maf( 7 );

    EXPECT_EQ( maf.getLength(), 7 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingAverageFilter, CanUpdate)
{
    mc::MovingAverageFilter maf( 5 );

    double u[] = { 44.0, 64.0, 18.0, 65.0, 81.0, 28.0, 1.0, 25.0, 41.0, 39.0 };

    maf.update( 1.0, u[ 0 ] );
    // 44
    EXPECT_DOUBLE_EQ( maf.getValue(), 44.0 );

    maf.update( 1.0, u[ 1 ] );
    // ( 44 + 64 ) / 2 = 54
    EXPECT_DOUBLE_EQ( maf.getValue(), 54.0 );

    maf.update( 1.0, u[ 2 ] );
    // ( 44 + 64 + 18 ) / 3 = 42
    EXPECT_DOUBLE_EQ( maf.getValue(), 42.0 );

    maf.update( 1.0, u[ 3 ] );
    // ( 44 + 64 + 18 + 65 ) / 4 = 47.75
    EXPECT_DOUBLE_EQ( maf.getValue(), 47.75 );

    maf.update( 1.0, u[ 4 ] );
    // ( 44 + 64 + 18 + 65 + 81 ) / 5 = 54.4
    EXPECT_DOUBLE_EQ( maf.getValue(), 54.4 );

    maf.update( 1.0, u[ 5 ] );
    // ( 64 + 18 + 65 + 81 + 28 ) / 5 = 51.2
    EXPECT_DOUBLE_EQ( maf.getValue(), 51.2 );

    maf.update( 1.0, u[ 6 ] );
    // ( 18 + 65 + 81 + 28 + 1 ) / 5 = 38.6
    EXPECT_DOUBLE_EQ( maf.getValue(), 38.6 );

    maf.update( 1.0, u[ 7 ] );
    // ( 65 + 81 + 28 + 1 + 25 ) / 5 = 40
    EXPECT_DOUBLE_EQ( maf.getValue(), 40.0 );

    maf.update( 1.0, u[ 8 ] );
    // ( 81 + 28 + 1 + 25 + 41 ) / 5 = 35.2
    EXPECT_DOUBLE_EQ( maf.getValue(), 35.2 );

    maf.update( 1.0, u[ 9 ] );
    // ( 28 + 1 + 25 + 41 + 39 ) / 5 = 26.8
    EXPECT_DOUBLE_EQ( maf.getValue(), 26.8 );
}
