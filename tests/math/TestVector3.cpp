#include <gtest/gtest.h>

#include <mcutils/math/Vector.h>

class TestVector3 : public ::testing::Test
{
protected:
    TestVector3() {}
    virtual ~TestVector3() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestVector3, CanCreateI)
{
    mc::Vector3d v1 = mc::Vector3d::i();

    EXPECT_DOUBLE_EQ(v1.x(), 1.0);
    EXPECT_DOUBLE_EQ(v1.y(), 0.0);
    EXPECT_DOUBLE_EQ(v1.z(), 0.0);
}

TEST_F(TestVector3, CanCreateJ)
{
    mc::Vector3d v1 = mc::Vector3d::j();

    EXPECT_DOUBLE_EQ(v1.x(), 0.0);
    EXPECT_DOUBLE_EQ(v1.y(), 1.0);
    EXPECT_DOUBLE_EQ(v1.z(), 0.0);
}

TEST_F(TestVector3, CanCreateK)
{
    mc::Vector3d v1 = mc::Vector3d::k();

    EXPECT_DOUBLE_EQ(v1.x(), 0.0);
    EXPECT_DOUBLE_EQ(v1.y(), 0.0);
    EXPECT_DOUBLE_EQ(v1.z(), 1.0);
}

TEST_F(TestVector3, CanInstantiate)
{
    mc::Vector3d v1;

    EXPECT_DOUBLE_EQ(v1.x(), 0.0);
    EXPECT_DOUBLE_EQ(v1.y(), 0.0);
    EXPECT_DOUBLE_EQ(v1.z(), 0.0);
}

TEST_F(TestVector3, CanInstantiateAndSetData)
{
    mc::Vector3d v1(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(v1.x(), 1.0);
    EXPECT_DOUBLE_EQ(v1.y(), 2.0);
    EXPECT_DOUBLE_EQ(v1.z(), 3.0);
}

TEST_F(TestVector3, CanGetLengthXY)
{
    mc::Vector3d v1(1.0, 2.0, 3.0);
    // 1^2 + 2^2 = 1 + 4 = 5
    EXPECT_DOUBLE_EQ(v1.GetLengthXY(), sqrt(5.0));

    mc::Vector3d v2(2.0, 3.0, 4.0);
    // 2^2 + 3^2 = 4 + 9 = 13
    EXPECT_DOUBLE_EQ(v2.GetLengthXY(), sqrt(13.0));
}

TEST_F(TestVector3, CanGetLengthXZ)
{
    mc::Vector3d v1(1.0, 2.0, 3.0);
    // 1^2 + 3^2 = 1 + 9 = 10
    EXPECT_DOUBLE_EQ(v1.GetLengthXZ(), sqrt(10.0));

    mc::Vector3d v2(2.0, 3.0, 4.0);
    // 2^2 + 4^2 = 4 + 16 = 20
    EXPECT_DOUBLE_EQ(v2.GetLengthXZ(), sqrt(20.0));
}

TEST_F(TestVector3, CanGetLengthYZ)
{
    mc::Vector3d v1(1.0, 2.0, 3.0);
    // 2^2 + 3^2 = 4 + 9 = 13
    EXPECT_DOUBLE_EQ(v1.GetLengthYZ(), sqrt(13.0));

    mc::Vector3d v2(2.0, 3.0, 4.0);
    // 3^2 + 4^2 = 9 + 16 = 25
    EXPECT_DOUBLE_EQ(v2.GetLengthYZ(), sqrt(25.0));
}

TEST_F(TestVector3, CanGetNormalized)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector3.m

    mc::Vector3d v1(1.0, 2.0, 3.0);
    mc::Vector3d v1_n = v1.GetNormalized();

    EXPECT_NEAR(v1_n.x(), 0.267261, 1.0e-5);
    EXPECT_NEAR(v1_n.y(), 0.534522, 1.0e-5);
    EXPECT_NEAR(v1_n.z(), 0.801784, 1.0e-5);

    EXPECT_DOUBLE_EQ(v1_n.GetLength(), 1.0);
}

TEST_F(TestVector3, CanSetData)
{
    mc::Vector3d v;

    v.Set(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
}

TEST_F(TestVector3, CanAccessElementsViaFunctionsXYZ)
{
    mc::Vector3d v;

    v.x() = 1.0;
    v.y() = 2.0;
    v.z() = 3.0;

    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
}

TEST_F(TestVector3, CanAssign)
{
    mc::Vector3d v;
    mc::Vector3d v1(1.0, 2.0, 3.0);

    v = v1;
    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
}

TEST_F(TestVector3, CanAdd)
{
    mc::Vector3d v1(1.0, 2.0, 3.0);
    mc::Vector3d v2(4.0, 5.0, 6.0);

    mc::Vector3d v12 = v1 + v2;

    EXPECT_DOUBLE_EQ(v12.x(), 5.0);
    EXPECT_DOUBLE_EQ(v12.y(), 7.0);
    EXPECT_DOUBLE_EQ(v12.z(), 9.0);
}

TEST_F(TestVector3, CanNegate)
{
    mc::Vector3d v1(1.0, 2.0, 3.0);

    mc::Vector3d v1_n = -v1;

    EXPECT_DOUBLE_EQ(v1_n.x(), -1.0);
    EXPECT_DOUBLE_EQ(v1_n.y(), -2.0);
    EXPECT_DOUBLE_EQ(v1_n.z(), -3.0);
}

TEST_F(TestVector3, CanSubstract)
{
    mc::Vector3d v1(4.0, 5.0, 6.0);
    mc::Vector3d v2(3.0, 2.0, 1.0);

    mc::Vector3d v12 = v1 - v2;

    EXPECT_DOUBLE_EQ(v12.x(), 1.0);
    EXPECT_DOUBLE_EQ(v12.y(), 3.0);
    EXPECT_DOUBLE_EQ(v12.z(), 5.0);
}

TEST_F(TestVector3, CanMultiplyByNumber)
{
    mc::Vector3d v1(1.0, 2.0, 3.0);

    mc::Vector3d v1_2 = v1 * 2.0;

    EXPECT_DOUBLE_EQ(v1_2.x(), 2.0);
    EXPECT_DOUBLE_EQ(v1_2.y(), 4.0);
    EXPECT_DOUBLE_EQ(v1_2.z(), 6.0);
}

TEST_F(TestVector3, CanDivideByNumber)
{
    mc::Vector3d v1(1.0, 2.0, 3.0);

    mc::Vector3d v1_2 = v1 / 2.0;

    EXPECT_DOUBLE_EQ(v1_2.x(), 0.5);
    EXPECT_DOUBLE_EQ(v1_2.y(), 1.0);
    EXPECT_DOUBLE_EQ(v1_2.z(), 1.5);
}

TEST_F(TestVector3, CanCalculateVectorDotProduct)
{
    mc::Vector3d v1(1.0, 0.0, 0.0);
    mc::Vector3d v2(0.0, 1.0, 0.0);
    mc::Vector3d v3(0.0, 0.0, 1.0);
    mc::Vector3d v4(1.0, 2.0, 3.0);

    double s41 = v4 * v1;
    double s42 = v4 * v2;
    double s43 = v4 * v3;
    double s44 = v4 * v4;

    // expected values calculated with wxMaxima
    // tests/math/octave/test_vector3_dot_product.m
    EXPECT_DOUBLE_EQ(s41,  1.0);
    EXPECT_DOUBLE_EQ(s42,  2.0);
    EXPECT_DOUBLE_EQ(s43,  3.0);
    EXPECT_DOUBLE_EQ(s44, 14.0);
}

TEST_F(TestVector3, CanCalculateVectorCrossProduct)
{
    mc::Vector3d v1(1.0, 0.0, 0.0);
    mc::Vector3d v2(0.0, 1.0, 0.0);
    mc::Vector3d v3(0.0, 0.0, 1.0);
    mc::Vector3d v4(1.0, 2.0, 3.0);

    mc::Vector3d v41 = v4 % v1;
    mc::Vector3d v42 = v4 % v2;
    mc::Vector3d v43 = v4 % v3;

    // expected values calculated with wxMaxima
    // tests/math/octave/test_vector3_cross_product.m
    EXPECT_DOUBLE_EQ(v41.x(),  0.0);
    EXPECT_DOUBLE_EQ(v41.y(),  3.0);
    EXPECT_DOUBLE_EQ(v41.z(), -2.0);

    EXPECT_DOUBLE_EQ(v42.x(), -3.0);
    EXPECT_DOUBLE_EQ(v42.y(),  0.0);
    EXPECT_DOUBLE_EQ(v42.z(),  1.0);

    EXPECT_DOUBLE_EQ(v43.x(),  2.0);
    EXPECT_DOUBLE_EQ(v43.y(), -1.0);
    EXPECT_DOUBLE_EQ(v43.z(),  0.0);
}

TEST_F(TestVector3, CanUnaryAdd)
{
    mc::Vector3d v0(1.0, 2.0, 3.0);
    mc::Vector3d v1(2.0, 3.0, 4.0);

    v0 += v1;

    EXPECT_DOUBLE_EQ(v0.x(), 3.0);
    EXPECT_DOUBLE_EQ(v0.y(), 5.0);
    EXPECT_DOUBLE_EQ(v0.z(), 7.0);
}

TEST_F(TestVector3, CanUnarySubstract)
{
    mc::Vector3d v0(3.0, 5.0, 7.0);
    mc::Vector3d v1(2.0, 3.0, 4.0);

    v0 -= v1;

    EXPECT_DOUBLE_EQ(v0.x(), 1.0);
    EXPECT_DOUBLE_EQ(v0.y(), 2.0);
    EXPECT_DOUBLE_EQ(v0.z(), 3.0);
}

TEST_F(TestVector3, CanUnaryMultiplyByNumber)
{
    mc::Vector3d v0(2.0, 4.0, 6.0);

    v0 *= 0.5;

    EXPECT_DOUBLE_EQ(v0.x(), 1.0);
    EXPECT_DOUBLE_EQ(v0.y(), 2.0);
    EXPECT_DOUBLE_EQ(v0.z(), 3.0);
}

TEST_F(TestVector3, CanUnaryDivideByNumber)
{
    mc::Vector3d v0(2.0, 4.0, 6.0);

    v0 /= 2.0;

    EXPECT_DOUBLE_EQ(v0.x(), 1.0);
    EXPECT_DOUBLE_EQ(v0.y(), 2.0);
    EXPECT_DOUBLE_EQ(v0.z(), 3.0);
}

TEST_F(TestVector3, CanUnaryVectorCrossProduct)
{
    mc::Vector3d v0(1.0, 2.0, 3.0);

    mc::Vector3d v1(1.0, 0.0, 0.0);
    mc::Vector3d v2(0.0, 1.0, 0.0);
    mc::Vector3d v3(0.0, 0.0, 1.0);

    mc::Vector3d vt;

    vt = v0;
    vt %= v1;

    EXPECT_DOUBLE_EQ(vt.x(),  0.0);
    EXPECT_DOUBLE_EQ(vt.y(),  3.0);
    EXPECT_DOUBLE_EQ(vt.z(), -2.0);

    vt = v0;
    vt %= v2;

    EXPECT_DOUBLE_EQ(vt.x(), -3.0);
    EXPECT_DOUBLE_EQ(vt.y(),  0.0);
    EXPECT_DOUBLE_EQ(vt.z(),  1.0);

    vt = v0;
    vt %= v3;

    EXPECT_DOUBLE_EQ(vt.x(),  2.0);
    EXPECT_DOUBLE_EQ(vt.y(), -1.0);
    EXPECT_DOUBLE_EQ(vt.z(),  0.0);
}

TEST_F(TestVector3, CanMultiplyNumberByVector)
{
    mc::Vector3d v1(1.0, 0.0, 0.0);
    mc::Vector3d r = 2.0 * v1;

    EXPECT_DOUBLE_EQ(r.x(), 2.0);
    EXPECT_DOUBLE_EQ(r.y(), 0.0);
    EXPECT_DOUBLE_EQ(r.z(), 0.0);
}
