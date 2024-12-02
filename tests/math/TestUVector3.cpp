#include <gtest/gtest.h>

#include <mcutils/math/Vector.h>

using namespace units::literals;

class TestUVector3 : public ::testing::Test
{
protected:
    TestUVector3() {}
    virtual ~TestUVector3() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestUVector3, CanCreateI)
{
    mc::Vector3_m v1 = mc::Vector3_m::i();

    EXPECT_DOUBLE_EQ(v1.x()(), 1.0);
    EXPECT_DOUBLE_EQ(v1.y()(), 0.0);
    EXPECT_DOUBLE_EQ(v1.z()(), 0.0);
}

TEST_F(TestUVector3, CanCreateJ)
{
    mc::Vector3_m v1 = mc::Vector3_m::j();

    EXPECT_DOUBLE_EQ(v1.x()(), 0.0);
    EXPECT_DOUBLE_EQ(v1.y()(), 1.0);
    EXPECT_DOUBLE_EQ(v1.z()(), 0.0);
}

TEST_F(TestUVector3, CanCreateK)
{
    mc::Vector3_m v1 = mc::Vector3_m::k();

    EXPECT_DOUBLE_EQ(v1.x()(), 0.0);
    EXPECT_DOUBLE_EQ(v1.y()(), 0.0);
    EXPECT_DOUBLE_EQ(v1.z()(), 1.0);
}

TEST_F(TestUVector3, CanInstantiate)
{
    mc::Vector3_m v1;

    EXPECT_DOUBLE_EQ(v1.x()(), 0.0);
    EXPECT_DOUBLE_EQ(v1.y()(), 0.0);
    EXPECT_DOUBLE_EQ(v1.z()(), 0.0);
}

TEST_F(TestUVector3, CanInstantiateAndSetData)
{
    mc::Vector3_m v1(1.0_m, 2.0_m, 3.0_m);

    EXPECT_DOUBLE_EQ(v1.x()(), 1.0);
    EXPECT_DOUBLE_EQ(v1.y()(), 2.0);
    EXPECT_DOUBLE_EQ(v1.z()(), 3.0);
}

TEST_F(TestUVector3, CanGetLengthXY)
{
    mc::Vector3_m v1(1.0_m, 2.0_m, 3.0_m);
    // 1^2 + 2^2 = 1 + 4 = 5
    EXPECT_DOUBLE_EQ(v1.GetLengthXY()(), sqrt(5.0));
}

TEST_F(TestUVector3, CanGetLengthXZ)
{
    mc::Vector3_m v1(1.0_m, 2.0_m, 3.0_m);
    // 1^2 + 3^2 = 1 + 9 = 10
    EXPECT_DOUBLE_EQ(v1.GetLengthXZ()(), sqrt(10.0));
}

TEST_F(TestUVector3, CanGetLengthYZ)
{
    mc::Vector3_m v1(1.0_m, 2.0_m, 3.0_m);
    // 2^2 + 3^2 = 4 + 9 = 13
    EXPECT_DOUBLE_EQ(v1.GetLengthYZ()(), sqrt(13.0));
}

TEST_F(TestUVector3, CanGetNormalized)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_vector3.m

    mc::Vector3_m v1(1.0_m, 2.0_m, 3.0_m);
    mc::Vector3_m v1_n = v1.GetNormalized();

    EXPECT_NEAR(v1_n.x()(), 0.267261, 1.0e-5);
    EXPECT_NEAR(v1_n.y()(), 0.534522, 1.0e-5);
    EXPECT_NEAR(v1_n.z()(), 0.801784, 1.0e-5);

    EXPECT_DOUBLE_EQ(v1_n.GetLength()(), 1.0);
}

TEST_F(TestUVector3, CanSetData)
{
    mc::Vector3_m v;

    v.Set(1.0_m, 2.0_m, 3.0_m);
    EXPECT_DOUBLE_EQ(v.x()(), 1.0);
    EXPECT_DOUBLE_EQ(v.y()(), 2.0);
    EXPECT_DOUBLE_EQ(v.z()(), 3.0);
}

TEST_F(TestUVector3, CanAccessElementsViaFunctionsXYZ)
{
    mc::Vector3_m v;

    v.x() = 1.0_m;
    v.y() = 2.0_m;
    v.z() = 3.0_m;

    EXPECT_DOUBLE_EQ(v.x()(), 1.0);
    EXPECT_DOUBLE_EQ(v.y()(), 2.0);
    EXPECT_DOUBLE_EQ(v.z()(), 3.0);
    EXPECT_DOUBLE_EQ(v(0)(), 1.0);
    EXPECT_DOUBLE_EQ(v(1)(), 2.0);
    EXPECT_DOUBLE_EQ(v(2)(), 3.0);
}

TEST_F(TestUVector3, CanAccessElementsViaFunctionsPQR)
{
    mc::Vector3_m v;

    v.p() = 1.0_m;
    v.q() = 2.0_m;
    v.r() = 3.0_m;

    EXPECT_DOUBLE_EQ(v.p()(), 1.0);
    EXPECT_DOUBLE_EQ(v.q()(), 2.0);
    EXPECT_DOUBLE_EQ(v.r()(), 3.0);
    EXPECT_DOUBLE_EQ(v(0)(), 1.0);
    EXPECT_DOUBLE_EQ(v(1)(), 2.0);
    EXPECT_DOUBLE_EQ(v(2)(), 3.0);
}

TEST_F(TestUVector3, CanAccessElementsViaFunctionsUVW)
{
    mc::Vector3_m v;

    v.u() = 1.0_m;
    v.v() = 2.0_m;
    v.w() = 3.0_m;

    EXPECT_DOUBLE_EQ(v.u()(), 1.0);
    EXPECT_DOUBLE_EQ(v.v()(), 2.0);
    EXPECT_DOUBLE_EQ(v.w()(), 3.0);
    EXPECT_DOUBLE_EQ(v(0)(), 1.0);
    EXPECT_DOUBLE_EQ(v(1)(), 2.0);
    EXPECT_DOUBLE_EQ(v(2)(), 3.0);
}

TEST_F(TestUVector3, CanCastToVector3d)
{
    mc::Vector3_m v1(1.0_m, 2.0_m, 3.0_m);
    mc::Vector3d v2 = v1;

    EXPECT_DOUBLE_EQ(v2.x(), 1.0);
    EXPECT_DOUBLE_EQ(v2.y(), 2.0);
    EXPECT_DOUBLE_EQ(v2.z(), 3.0);
}

TEST_F(TestUVector3, CanAssign)
{
    mc::Vector3_m v;
    mc::Vector3_m v1(1.0_m, 2.0_m, 3.0_m);

    v = v1;
    EXPECT_DOUBLE_EQ(v.x()(), 1.0);
    EXPECT_DOUBLE_EQ(v.y()(), 2.0);
    EXPECT_DOUBLE_EQ(v.z()(), 3.0);
}

TEST_F(TestUVector3, CanAdd)
{
    mc::Vector3_m v1(1.0_m, 2.0_m, 3.0_m);
    mc::Vector3_m v2(4.0_m, 5.0_m, 6.0_m);

    mc::Vector3_m v12 = v1 + v2;

    EXPECT_DOUBLE_EQ(v12.x()(), 5.0);
    EXPECT_DOUBLE_EQ(v12.y()(), 7.0);
    EXPECT_DOUBLE_EQ(v12.z()(), 9.0);
}

TEST_F(TestUVector3, CanNegate)
{
    mc::Vector3_m v1(1.0_m, 2.0_m, 3.0_m);

    mc::Vector3_m v1_n = -v1;

    EXPECT_DOUBLE_EQ(v1_n.x()(), -1.0);
    EXPECT_DOUBLE_EQ(v1_n.y()(), -2.0);
    EXPECT_DOUBLE_EQ(v1_n.z()(), -3.0);
}

TEST_F(TestUVector3, CanSubstract)
{
    mc::Vector3_m v1(4.0_m, 5.0_m, 6.0_m);
    mc::Vector3_m v2(3.0_m, 2.0_m, 1.0_m);

    mc::Vector3_m v12 = v1 - v2;

    EXPECT_DOUBLE_EQ(v12.x()(), 1.0);
    EXPECT_DOUBLE_EQ(v12.y()(), 3.0);
    EXPECT_DOUBLE_EQ(v12.z()(), 5.0);
}

TEST_F(TestUVector3, CanMultiplyByNumber)
{
    mc::Vector3_m v1(1.0_m, 2.0_m, 3.0_m);

    mc::Vector3_m v1_2 = v1 * 2.0;

    EXPECT_DOUBLE_EQ(v1_2.x()(), 2.0);
    EXPECT_DOUBLE_EQ(v1_2.y()(), 4.0);
    EXPECT_DOUBLE_EQ(v1_2.z()(), 6.0);
}

TEST_F(TestUVector3, CanMultiplyByScalar)
{
    mc::Vector3_m r(1.0_m, 2.0_m, 3.0_m);
    mc::Vector3_Nm t = r * 2.0_N;

    EXPECT_DOUBLE_EQ(t.x()(), 2.0);
    EXPECT_DOUBLE_EQ(t.y()(), 4.0);
    EXPECT_DOUBLE_EQ(t.z()(), 6.0);
}

TEST_F(TestUVector3, CanDivideByNumber)
{
    mc::Vector3_m v1(1.0_m, 2.0_m, 3.0_m);

    mc::Vector3_m v1_2 = v1 / 2.0;

    EXPECT_DOUBLE_EQ(v1_2.x()(), 0.5);
    EXPECT_DOUBLE_EQ(v1_2.y()(), 1.0);
    EXPECT_DOUBLE_EQ(v1_2.z()(), 1.5);
}

TEST_F(TestUVector3, CanDivideByScalar)
{
    mc::Vector3_Nm t(2.0_Nm, 4.0_Nm, 6.0_Nm);
    mc::Vector3_m r = t / 2.0_N;

    EXPECT_DOUBLE_EQ(r.x()(), 1.0);
    EXPECT_DOUBLE_EQ(r.y()(), 2.0);
    EXPECT_DOUBLE_EQ(r.z()(), 3.0);
}

TEST_F(TestUVector3, CanCalculateVectorDotProduct)
{
    mc::Vector3_m v1(1.0_m, 0.0_m, 0.0_m);
    mc::Vector3_m v2(0.0_m, 1.0_m, 0.0_m);
    mc::Vector3_m v3(0.0_m, 0.0_m, 1.0_m);
    mc::Vector3_m v4(1.0_m, 2.0_m, 3.0_m);

    units::area::square_meter_t s41 = v4 * v1;
    units::area::square_meter_t s42 = v4 * v2;
    units::area::square_meter_t s43 = v4 * v3;
    units::area::square_meter_t s44 = v4 * v4;

    // expected values calculated with wxMaxima
    // tests/math/octave/test_vector3_dot_product.m
    EXPECT_DOUBLE_EQ(s41(),  1.0);
    EXPECT_DOUBLE_EQ(s42(),  2.0);
    EXPECT_DOUBLE_EQ(s43(),  3.0);
    EXPECT_DOUBLE_EQ(s44(), 14.0);
}

TEST_F(TestUVector3, CanCalculateVectorCrossProduct)
{
    mc::Vector3_m r(1.0_m, 2.0_m, 3.0_m);
    mc::Vector3_N f(4.0_N, 5.0_N, 6.0_N);

    mc::Vector3_Nm t = r % f;

    // expected values calculated with wxMaxima
    // tests/math/octave/test_vector3_cross_product.m
    EXPECT_DOUBLE_EQ(t.x()(), -3.0);
    EXPECT_DOUBLE_EQ(t.y()(),  6.0);
    EXPECT_DOUBLE_EQ(t.z()(), -3.0);
}

TEST_F(TestUVector3, CanCalculateVectorCrossProduct_AngularVelocity)
{
    mc::Vector3_rad_per_s omega(1.0_rad_per_s, 2.0_rad_per_s, 3.0_rad_per_s);
    mc::Vector3_m r(4.0_m, 5.0_m, 6.0_m);

    mc::Vector3_mps t = omega % r;

    // expected values calculated with wxMaxima
    // tests/math/octave/test_vector3_cross_product.m
    EXPECT_DOUBLE_EQ(t.x()(), -3.0);
    EXPECT_DOUBLE_EQ(t.y()(),  6.0);
    EXPECT_DOUBLE_EQ(t.z()(), -3.0);
}

TEST_F(TestUVector3, CanUnaryAdd)
{
    mc::Vector3_m v0(1.0_m, 2.0_m, 3.0_m);
    mc::Vector3_m v1(2.0_m, 3.0_m, 4.0_m);

    v0 += v1;

    EXPECT_DOUBLE_EQ(v0.x()(), 3.0);
    EXPECT_DOUBLE_EQ(v0.y()(), 5.0);
    EXPECT_DOUBLE_EQ(v0.z()(), 7.0);
}

TEST_F(TestUVector3, CanUnarySubstract)
{
    mc::Vector3_m v0(3.0_m, 5.0_m, 7.0_m);
    mc::Vector3_m v1(2.0_m, 3.0_m, 4.0_m);

    v0 -= v1;

    EXPECT_DOUBLE_EQ(v0.x()(), 1.0);
    EXPECT_DOUBLE_EQ(v0.y()(), 2.0);
    EXPECT_DOUBLE_EQ(v0.z()(), 3.0);
}

TEST_F(TestUVector3, CanUnaryMultiplyByNumber)
{
    mc::Vector3_m v0(2.0_m, 4.0_m, 6.0_m);

    v0 *= 0.5;

    EXPECT_DOUBLE_EQ(v0.x()(), 1.0);
    EXPECT_DOUBLE_EQ(v0.y()(), 2.0);
    EXPECT_DOUBLE_EQ(v0.z()(), 3.0);
}

TEST_F(TestUVector3, CanUnaryDivideByNumber)
{
    mc::Vector3_m v0(2.0_m, 4.0_m, 6.0_m);

    v0 /= 2.0;

    EXPECT_DOUBLE_EQ(v0.x()(), 1.0);
    EXPECT_DOUBLE_EQ(v0.y()(), 2.0);
    EXPECT_DOUBLE_EQ(v0.z()(), 3.0);
}

TEST_F(TestUVector3, CanMultiplyNumberByVector)
{
    mc::Vector3_m v1(1.0_m, 2.0_m, 3.0_m);
    mc::Vector3_m r = 2.0 * v1;

    EXPECT_DOUBLE_EQ(r.x()(), 2.0);
    EXPECT_DOUBLE_EQ(r.y()(), 4.0);
    EXPECT_DOUBLE_EQ(r.z()(), 6.0);
}
