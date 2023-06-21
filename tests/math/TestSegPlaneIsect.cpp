#include <gtest/gtest.h>

#include <mcutils/math/SegPlaneIsect.h>

////////////////////////////////////////////////////////////////////////////////

class TestSegPlaneIsect : public ::testing::Test
{
protected:
    TestSegPlaneIsect() {}
    virtual ~TestSegPlaneIsect() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestSegPlaneIsect, CanCheckIfThereIsSegPlaneIsect)
{
    mc::Vector3 b;
    mc::Vector3 e;
    mc::Vector3 r;
    mc::Vector3 n;

    b.set(0.0, 0.0,  1.0);
    e.set(0.0, 0.0, -1.0);
    r.set(0.0, 0.0,  0.0);
    n.set(0.0, 0.0,  1.0);
    EXPECT_TRUE( mc::IsSegPlaneIsect(b, e, r, n) );

    b.set(0.0, 0.0,  1.0);
    e.set(0.0, 0.0,  0.0);
    r.set(0.0, 0.0, -1.0);
    n.set(0.0, 0.0,  1.0);
    EXPECT_FALSE( mc::IsSegPlaneIsect(b, e, r, n) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestSegPlaneIsect, CanGetSegPlaneIsect)
{
    mc::Vector3 b;
    mc::Vector3 e;
    mc::Vector3 r;
    mc::Vector3 n;
    mc::Vector3 i;

    b.set(0.0, 0.0,  1.0);
    e.set(0.0, 0.0, -1.0);
    r.set(0.0, 0.0,  0.0);
    n.set(0.0, 0.0,  1.0);
    i = mc::GetSegPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ( 0.0, i.x() );
    EXPECT_DOUBLE_EQ( 0.0, i.y() );
    EXPECT_DOUBLE_EQ( 0.0, i.z() );

    b.set(1.0, 0.0,  1.0);
    e.set(1.0, 0.0, -1.0);
    r.set(0.0, 0.0,  0.0);
    n.set(0.0, 0.0,  1.0);
    i = mc::GetSegPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ( 1.0, i.x() );
    EXPECT_DOUBLE_EQ( 0.0, i.y() );
    EXPECT_DOUBLE_EQ( 0.0, i.z() );

    b.set(0.0, 1.0,  1.0);
    e.set(0.0, 1.0, -1.0);
    r.set(0.0, 0.0,  0.0);
    n.set(0.0, 0.0,  1.0);
    i = mc::GetSegPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ( 0.0, i.x() );
    EXPECT_DOUBLE_EQ( 1.0, i.y() );
    EXPECT_DOUBLE_EQ( 0.0, i.z() );

    b.set(1.0, 1.0,  1.0);
    e.set(1.0, 1.0, -1.0);
    r.set(0.0, 0.0,  0.5);
    n.set(0.0, 0.0,  1.0);
    i = mc::GetSegPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ( 1.0, i.x() );
    EXPECT_DOUBLE_EQ( 1.0, i.y() );
    EXPECT_DOUBLE_EQ( 0.5, i.z() );

    b.set(1.0, 1.0,  1.0);
    e.set(1.0, 1.0, -1.0);
    r.set(0.0, 0.0,  0.5);
    n.set(0.0, 0.0,  1.0);
    i = mc::GetSegPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ( 1.0, i.x() );
    EXPECT_DOUBLE_EQ( 1.0, i.y() );
    EXPECT_DOUBLE_EQ( 0.5, i.z() );

    // no intersection
    b.set(0.0, 0.0,  1.0);
    e.set(0.0, 0.0,  0.0);
    r.set(0.0, 0.0, -1.0);
    n.set(0.0, 0.0,  1.0);
    i = mc::GetSegPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ( 0.0, i.x() );
    EXPECT_DOUBLE_EQ( 0.0, i.y() );
    EXPECT_DOUBLE_EQ( 0.0, i.z() );

    // no intersection (parallel)
    b.set(0.0, 0.0,  1.0);
    e.set(1.0, 1.0,  1.0);
    r.set(0.0, 0.0, -1.0);
    n.set(0.0, 0.0,  1.0);
    i = mc::GetSegPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ( 1.0, i.x() );
    EXPECT_DOUBLE_EQ( 1.0, i.y() );
    EXPECT_DOUBLE_EQ( 1.0, i.z() );

    // on the plane
    b.set(1.0, 1.0,  0.0);
    e.set(0.0, 0.0,  0.0);
    r.set(0.0, 0.0,  0.0);
    n.set(0.0, 0.0,  1.0);
    i = mc::GetSegPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ( 1.0, i.x() );
    EXPECT_DOUBLE_EQ( 1.0, i.y() );
    EXPECT_DOUBLE_EQ( 0.0, i.z() );
}
