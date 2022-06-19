#include <gtest/gtest.h>

#include <mcutils/ctrl/MovingMedianFilter.h>
#include <mcutils/math/Random.h>

////////////////////////////////////////////////////////////////////////////////

class TestMovingMedianFilter : public ::testing::Test
{
protected:

    TestMovingMedianFilter() {}
    virtual ~TestMovingMedianFilter() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingMedianFilter, CanConstruct)
{
    mc::MovingMedianFilter *mmf = nullptr;
    EXPECT_NO_THROW( mmf = new mc::MovingMedianFilter() );
    delete mmf;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingMedianFilter, CanDestruct)
{
    mc::MovingMedianFilter *mmf = new mc::MovingMedianFilter();
    EXPECT_NO_THROW( delete mmf );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingMedianFilter, CanInstantiate)
{
    mc::MovingMedianFilter mmf;

    EXPECT_EQ( mmf.getLength(), 1 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingMedianFilter, CanInstantiateAndSetData)
{
    mc::MovingMedianFilter mmf( 5 );

    EXPECT_EQ( mmf.getLength(), 5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingMedianFilter, CanSetLenght)
{
    mc::MovingMedianFilter mmf;

    EXPECT_NO_THROW( mmf.setLength( 5 ) );
    EXPECT_EQ( mmf.getLength(), 5 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingMedianFilter, CanGetLenght)
{
    mc::MovingMedianFilter mmf( 7 );

    EXPECT_EQ( mmf.getLength(), 7 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestMovingMedianFilter, CanUpdate)
{
    mc::MovingMedianFilter mmf( 5 );

    double u[] = { 44.0, 64.0, 18.0, 65.0, 81.0, 28.0, 1.0, 25.0, 41.0, 39.0 };

    mmf.update( 1.0, u[ 0 ] );
    // [44]
    EXPECT_DOUBLE_EQ( mmf.getValue(), 44.0 );

    mmf.update( 1.0, u[ 1 ] );
    // [44, 64]
    // ( 44 + 64 ) / 2 = 54
    EXPECT_DOUBLE_EQ( mmf.getValue(), 54.0 );

    mmf.update( 1.0, u[ 2 ] );
    // 18, [44], 64
    EXPECT_DOUBLE_EQ( mmf.getValue(), 44.0 );

    mmf.update( 1.0, u[ 3 ] );
    // 18, [44, 64], 65
    // ( 44 + 64 ) / 2 = 54
    EXPECT_DOUBLE_EQ( mmf.getValue(), 54.0 );

    mmf.update( 1.0, u[ 4 ] );
    // 18, 44, [64], 65, 81
    EXPECT_DOUBLE_EQ( mmf.getValue(), 64.0 );

    mmf.update( 1.0, u[ 5 ] );
    // 18, 28, [64], 65, 81
    EXPECT_DOUBLE_EQ( mmf.getValue(), 64.0 );

    mmf.update( 1.0, u[ 6 ] );
    // 1, 18, [28], 65, 81
    EXPECT_DOUBLE_EQ( mmf.getValue(), 28.0 );

    mmf.update( 1.0, u[ 7 ] );
    // 1, 25, [28], 65, 81
    EXPECT_DOUBLE_EQ( mmf.getValue(), 28.0 );

    mmf.update( 1.0, u[ 8 ] );
    // 1, 25, [28], 41, 81
    EXPECT_DOUBLE_EQ( mmf.getValue(), 28.0 );

    mmf.update( 1.0, u[ 9 ] );
    // 1, 25, [28], 39, 41
    EXPECT_DOUBLE_EQ( mmf.getValue(), 28.0 );
}
