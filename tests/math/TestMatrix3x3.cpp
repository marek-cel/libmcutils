#include <gtest/gtest.h>

#include <mcutils/math/Matrix3x3.h>

class TestMatrix3x3 : public ::testing::Test
{
protected:
    constexpr static int size = 3;
    TestMatrix3x3() {}
    virtual ~TestMatrix3x3() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMatrix3x3, CanGetIdentityMatrix)
{
    mc::Matrix3x3 m = mc::Matrix3x3::GetIdentityMatrix();

    EXPECT_DOUBLE_EQ(m(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m(0,1), 0.0);
    EXPECT_DOUBLE_EQ(m(0,2), 0.0);

    EXPECT_DOUBLE_EQ(m(1,0), 0.0);
    EXPECT_DOUBLE_EQ(m(1,1), 1.0);
    EXPECT_DOUBLE_EQ(m(1,2), 0.0);

    EXPECT_DOUBLE_EQ(m(2,0), 0.0);
    EXPECT_DOUBLE_EQ(m(2,1), 0.0);
    EXPECT_DOUBLE_EQ(m(2,2), 1.0);
}

TEST_F(TestMatrix3x3, CanConstruct)
{
    mc::Matrix3x3* m = nullptr;
    EXPECT_NO_THROW(m = new mc::Matrix3x3());
    delete m;
}

TEST_F(TestMatrix3x3, CanDestruct)
{
    mc::Matrix3x3* m = new mc::Matrix3x3();
    EXPECT_NO_THROW(delete m);
}

TEST_F(TestMatrix3x3, CanInstantiate)
{
    mc::Matrix3x3 m;
    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3, CanInstantiateAndCopy)
{
    constexpr int size = 3;

    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::Matrix3x3 m0;
    m0.SetFromArray(x);

    mc::Matrix3x3 m1(m0);

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetData)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    EXPECT_DOUBLE_EQ(m1(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m1(0,1), 2.0);
    EXPECT_DOUBLE_EQ(m1(0,2), 3.0);
    EXPECT_DOUBLE_EQ(m1(1,0), 4.0);
    EXPECT_DOUBLE_EQ(m1(1,1), 5.0);
    EXPECT_DOUBLE_EQ(m1(1,2), 6.0);
    EXPECT_DOUBLE_EQ(m1(2,0), 7.0);
    EXPECT_DOUBLE_EQ(m1(2,1), 8.0);
    EXPECT_DOUBLE_EQ(m1(2,2), 9.0);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromAnglesZeros)
{
    mc::Angles ang(0.0_rad, 0.0_rad, 0.0_rad);
    mc::Matrix3x3 m(ang);

    EXPECT_NEAR(m.xx(), 1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(), 1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(), 1.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromPhiPi)
{
    mc::Angles ang(1.0_rad * M_PI, 0.0_rad, 0.0_rad);
    mc::Matrix3x3 m(ang);

    EXPECT_NEAR(m.xx(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(), -1.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromThetaPi)
{
    mc::Angles ang(0.0_rad, 1.0_rad * M_PI, 0.0_rad);
    mc::Matrix3x3 m(ang);

    EXPECT_NEAR(m.xx(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(), -1.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromPsiPi)
{
    mc::Angles ang(0.0_rad, 0.0_rad, 1.0_rad * M_PI);
    mc::Matrix3x3 m(ang);

    EXPECT_NEAR(m.xx(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(),  1.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromPhiThetaPsiHalfPi)
{
    mc::Angles ang(1.0_rad * M_PI_2, 1.0_rad * M_PI_2, 1.0_rad * M_PI_2);
    mc::Matrix3x3 m(ang);

    EXPECT_NEAR(m.xx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(),  0.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromPhiThetaPsiQuarterPi)
{
    mc::Angles ang(1.0_rad * M_PI_4, 1.0_rad * M_PI_4, 1.0_rad * M_PI_4);
    mc::Matrix3x3 m(ang);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    EXPECT_NEAR(m.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m.xy(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m.xz(), -0.7071, 1.0e-3);
    EXPECT_NEAR(m.yx(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m.yy(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m.yz(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m.zx(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m.zy(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m.zz(),  0.5000, 1.0e-3);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromRandomAngles)
{
    mc::Angles a1(-1.0_rad * M_PI_4,  1.0_rad * M_PI_4,  1.0_rad * M_PI_4);
    mc::Angles a2( 1.0_rad * M_PI_4, -1.0_rad * M_PI_4,  1.0_rad * M_PI_4);
    mc::Angles a3( 1.0_rad * M_PI_4,  1.0_rad * M_PI_4, -1.0_rad * M_PI_4);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 m1(a1);
    EXPECT_NEAR(m1.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m1.xy(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m1.xz(), -0.7071, 1.0e-3);
    EXPECT_NEAR(m1.yx(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m1.yy(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m1.yz(), -0.5000, 1.0e-3);
    EXPECT_NEAR(m1.zx(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m1.zy(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m1.zz(),  0.5000, 1.0e-3);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 m2(a2);
    EXPECT_NEAR(m2.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m2.xy(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m2.xz(),  0.7071, 1.0e-3);
    EXPECT_NEAR(m2.yx(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m2.yy(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m2.yz(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m2.zx(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m2.zy(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m2.zz(),  0.5000, 1.0e-3);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 m3(a3);
    EXPECT_NEAR(m3.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m3.xy(), -0.5000, 1.0e-3);
    EXPECT_NEAR(m3.xz(), -0.7071, 1.0e-3);
    EXPECT_NEAR(m3.yx(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m3.yy(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m3.yz(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m3.zx(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m3.zy(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m3.zz(),  0.5000, 1.0e-3);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromQuaternionAngleZeros)
{
    mc::Angles ang(0.0_rad, 0.0_rad, 0.0_rad);
    mc::Quaternion quat(ang);
    mc::Matrix3x3 m(quat);

    EXPECT_NEAR(m.xx(), 1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(), 1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(), 1.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromQuaternionPhiPi)
{
    mc::Angles ang(1.0_rad * M_PI, 0.0_rad, 0.0_rad);
    mc::Quaternion quat(ang);
    mc::Matrix3x3 m(quat);

    EXPECT_NEAR(m.xx(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(), -1.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromQuaternionThetaPi)
{
    mc::Angles ang(0.0_rad, 1.0_rad * M_PI, 0.0_rad);
    mc::Quaternion quat(ang);
    mc::Matrix3x3 m(quat);

    EXPECT_NEAR(m.xx(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(), -1.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromQuaternionPsiPi)
{
    mc::Angles ang(0.0_rad, 0.0_rad, 1.0_rad * M_PI);
    mc::Quaternion quat(ang);
    mc::Matrix3x3 m(quat);

    EXPECT_NEAR(m.xx(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(),  1.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromQuaternionPhiThetaPsiHalfPi)
{
    mc::Angles ang(1.0_rad * M_PI_2, 1.0_rad * M_PI_2, 1.0_rad * M_PI_2);
    mc::Quaternion quat(ang);
    mc::Matrix3x3 m(quat);

    EXPECT_NEAR(m.xx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(),  0.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromQuaternionPhiThetaPsiQuarterPi)
{
    mc::Angles ang(1.0_rad * M_PI_4, 1.0_rad * M_PI_4, 1.0_rad * M_PI_4);
    mc::Quaternion quat(ang);
    mc::Matrix3x3 m(quat);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    EXPECT_NEAR(m.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m.xy(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m.xz(), -0.7071, 1.0e-3);
    EXPECT_NEAR(m.yx(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m.yy(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m.yz(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m.zx(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m.zy(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m.zz(),  0.5000, 1.0e-3);
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetDataFromQuaternionRandomAngle)
{
    mc::Angles a1(-1.0_rad * M_PI_4,  1.0_rad * M_PI_4,  1.0_rad * M_PI_4);
    mc::Angles a2( 1.0_rad * M_PI_4, -1.0_rad * M_PI_4,  1.0_rad * M_PI_4);
    mc::Angles a3( 1.0_rad * M_PI_4,  1.0_rad * M_PI_4, -1.0_rad * M_PI_4);

    mc::Quaternion q1(a1);
    mc::Quaternion q2(a2);
    mc::Quaternion q3(a3);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 m1(q1);
    EXPECT_NEAR(m1.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m1.xy(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m1.xz(), -0.7071, 1.0e-3);
    EXPECT_NEAR(m1.yx(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m1.yy(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m1.yz(), -0.5000, 1.0e-3);
    EXPECT_NEAR(m1.zx(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m1.zy(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m1.zz(),  0.5000, 1.0e-3);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 m2(q2);
    EXPECT_NEAR(m2.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m2.xy(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m2.xz(),  0.7071, 1.0e-3);
    EXPECT_NEAR(m2.yx(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m2.yy(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m2.yz(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m2.zx(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m2.zy(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m2.zz(),  0.5000, 1.0e-3);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_matrix3x3.m
    mc::Matrix3x3 m3(q3);
    EXPECT_NEAR(m3.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m3.xy(), -0.5000, 1.0e-3);
    EXPECT_NEAR(m3.xz(), -0.7071, 1.0e-3);
    EXPECT_NEAR(m3.yx(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m3.yy(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m3.yz(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m3.zx(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m3.zy(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m3.zz(),  0.5000, 1.0e-3);
}

TEST_F(TestMatrix3x3, CanAccessXX)
{
    mc::Matrix3x3 m0;

    m0.xx() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessXY)
{
    mc::Matrix3x3 m0;

    m0.xy() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessXZ)
{
    mc::Matrix3x3 m0;

    m0.xz() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 1.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessYX)
{
    mc::Matrix3x3 m0;

    m0.yx() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 1.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessYY)
{
    mc::Matrix3x3 m0;

    m0.yy() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessYZ)
{
    mc::Matrix3x3 m0;

    m0.yz() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 1.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessZX)
{
    mc::Matrix3x3 m0;

    m0.zx() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 1.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessZY)
{
    mc::Matrix3x3 m0;

    m0.zy() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessZZ)
{
    mc::Matrix3x3 m0;

    m0.zz() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 1.0);
}

TEST_F(TestMatrix3x3, CanSetData)
{
    mc::Matrix3x3 m0;

    m0.Set( 11.0, 12.0, 13.0,
            21.0, 22.0, 23.0,
            31.0, 32.0, 33.0 );

    EXPECT_DOUBLE_EQ(m0.xx(), 11.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 12.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 13.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 21.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 22.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 23.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 31.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 32.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 33.0);
}

TEST_F(TestMatrix3x3, CanGetAnglesZeros)
{
    mc::Matrix3x3 m(mc::Angles(0.0_rad, 0.0_rad, 0.0_rad));
    mc::Angles ang = m.GetAngles();

    EXPECT_NEAR(ang.phi()(), 0.0, 1.0e-9);
    EXPECT_NEAR(ang.tht()(), 0.0, 1.0e-9);
    EXPECT_NEAR(ang.psi()(), 0.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanGetAnglesPhiPi)
{
    mc::Matrix3x3 m(mc::Angles(1.0_rad * M_PI, 0.0_rad, 0.0_rad));
    mc::Angles ang = m.GetAngles();

    EXPECT_NEAR(ang.phi()(), M_PI, 1.0e-9);
    EXPECT_NEAR(ang.tht()(), 0.0, 1.0e-9);
    EXPECT_NEAR(ang.psi()(), 0.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanGetAnglesPsiPi)
{
    mc::Matrix3x3 m(mc::Angles(0.0_rad, 0.0_rad, 1.0_rad * M_PI));
    mc::Angles ang = m.GetAngles();

    EXPECT_NEAR(ang.phi()(), 0.0, 1.0e-9);
    EXPECT_NEAR(ang.tht()(), 0.0, 1.0e-9);
    EXPECT_NEAR(ang.psi()(), M_PI, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanGetAnglesInGimbalLock)
{
    // singularity - gimbal lock
    mc::Matrix3x3 mas1(mc::Angles( 0.0_rad          , 1.0_rad * M_PI_2 , 0.0_rad          ));
    mc::Matrix3x3 mas2(mc::Angles( 1.0_rad * M_PI_4 , 1.0_rad * M_PI_2 , 0.0_rad          ));
    mc::Matrix3x3 mas3(mc::Angles( 1.0_rad * M_PI_2 , 1.0_rad * M_PI_2 , 0.0_rad          ));
    mc::Matrix3x3 mas4(mc::Angles( 1.0_rad * M_PI   , 1.0_rad * M_PI_2 , 0.0_rad          ));
    mc::Matrix3x3 mas5(mc::Angles( 0.0_rad          , 1.0_rad * M_PI_2 , 1.0_rad * M_PI_2 ));

    mc::Angles as1 = mas1.GetAngles();
    mc::Angles as2 = mas2.GetAngles();
    mc::Angles as3 = mas3.GetAngles();
    mc::Angles as4 = mas4.GetAngles();
    mc::Angles as5 = mas5.GetAngles();

    EXPECT_NEAR(as1.phi()(),     0.0, 1.0e-9);
    EXPECT_NEAR(as1.tht()(),  M_PI_2, 1.0e-9);
    EXPECT_NEAR(as1.psi()(),     0.0, 1.0e-9);

    EXPECT_NEAR(as2.phi()(),  M_PI_4, 1.0e-9);
    EXPECT_NEAR(as2.tht()(),  M_PI_2, 1.0e-9);
    EXPECT_NEAR(as2.psi()(),     0.0, 1.0e-9);

    EXPECT_NEAR(as3.phi()(),  M_PI_2, 1.0e-9);
    EXPECT_NEAR(as3.tht()(),  M_PI_2, 1.0e-9);
    EXPECT_NEAR(as3.psi()(),     0.0, 1.0e-9);

    EXPECT_NEAR(as4.phi()(),    M_PI, 1.0e-9);
    EXPECT_NEAR(as4.tht()(),  M_PI_2, 1.0e-9);
    EXPECT_NEAR(as4.psi()(),     0.0, 1.0e-9);

    EXPECT_NEAR(as5.phi()(), -M_PI_2, 1.0e-9);
    EXPECT_NEAR(as5.tht()(),  M_PI_2, 1.0e-9);
    EXPECT_NEAR(as5.psi()(),     0.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanGetQuaternion)
{
    mc::Matrix3x3 m(mc::Quaternion(0.6, 0.0, 0.0, 0.8));
    mc::Quaternion q = m.GetQuaternion();

    EXPECT_NEAR(q.e0(), 0.6, 1.0e-9);
    EXPECT_NEAR(q.ex(), 0.0, 1.0e-9);
    EXPECT_NEAR(q.ey(), 0.0, 1.0e-9);
    EXPECT_NEAR(q.ez(), 0.8, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanGetQuaternionWhichMatchesAngles)
{
    mc::Matrix3x3 m1(  1.0,  0.0,  0.0,
                       0.0,  1.0,  0.0,
                       0.0,  0.0,  1.0 );
    mc::Matrix3x3 m2( -1.0,  0.0,  0.0,
                       0.0, -1.0,  0.0,
                       0.0,  0.0,  1.0 );
    mc::Matrix3x3 m3( -1.0,  0.0,  0.0,
                       0.0,  1.0,  0.0,
                       0.0,  0.0, -1.0 );
    mc::Matrix3x3 m4(  1.0,  0.0,  0.0,
                       0.0, -1.0,  0.0,
                       0.0,  0.0, -1.0 );

    mc::Angles a1 = m1.GetAngles();
    mc::Angles a2 = m2.GetAngles();
    mc::Angles a3 = m3.GetAngles();
    mc::Angles a4 = m4.GetAngles();

    mc::Quaternion qa1(a1);
    mc::Quaternion qa2(a2);
    mc::Quaternion qa3(a3);
    mc::Quaternion qa4(a4);

    mc::Quaternion qm1 = m1.GetQuaternion();
    mc::Quaternion qm2 = m2.GetQuaternion();
    mc::Quaternion qm3 = m3.GetQuaternion();
    mc::Quaternion qm4 = m4.GetQuaternion();

    EXPECT_NEAR(qa1.e0(), qm1.e0(), 1.0e-9);
    EXPECT_NEAR(qa1.ex(), qm1.ex(), 1.0e-9);
    EXPECT_NEAR(qa1.ey(), qm1.ey(), 1.0e-9);
    EXPECT_NEAR(qa1.ez(), qm1.ez(), 1.0e-9);

    EXPECT_NEAR(qa2.e0(), qm2.e0(), 1.0e-9);
    EXPECT_NEAR(qa2.ex(), qm2.ex(), 1.0e-9);
    EXPECT_NEAR(qa2.ey(), qm2.ey(), 1.0e-9);
    EXPECT_NEAR(qa2.ez(), qm2.ez(), 1.0e-9);

    EXPECT_NEAR(qa3.e0(), qm3.e0(), 1.0e-9);
    EXPECT_NEAR(qa3.ex(), qm3.ex(), 1.0e-9);
    EXPECT_NEAR(qa3.ey(), qm3.ey(), 1.0e-9);
    EXPECT_NEAR(qa3.ez(), qm3.ez(), 1.0e-9);

    EXPECT_NEAR(qa4.e0(), qm4.e0(), 1.0e-9);
    EXPECT_NEAR(qa4.ex(), qm4.ex(), 1.0e-9);
    EXPECT_NEAR(qa4.ey(), qm4.ey(), 1.0e-9);
    EXPECT_NEAR(qa4.ez(), qm4.ez(), 1.0e-9);
}

TEST_F(TestMatrix3x3, CanGetTransposed)
{
    double x[] { 1.0, 2.0, 3.0,
                 4.0, 5.0, 6.0,
                 7.0, 8.0, 9.0 };

    mc::Matrix3x3 m0;
    m0.SetFromArray(x);

    mc::Matrix3x3 m1(m0);
    mc::Matrix3x3 mt = m1.GetTransposed();

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
            EXPECT_DOUBLE_EQ(mt(r,c), m0(c,r)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3, CanAdd)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m2( 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0 );

    mc::Matrix3x3 m0 = m1 + m2;

    EXPECT_DOUBLE_EQ(m0.xx(),  2.0);
    EXPECT_DOUBLE_EQ(m0.xy(),  3.0);
    EXPECT_DOUBLE_EQ(m0.xz(),  4.0);
    EXPECT_DOUBLE_EQ(m0.yx(),  5.0);
    EXPECT_DOUBLE_EQ(m0.yy(),  6.0);
    EXPECT_DOUBLE_EQ(m0.yz(),  7.0);
    EXPECT_DOUBLE_EQ(m0.zx(),  8.0);
    EXPECT_DOUBLE_EQ(m0.zy(),  9.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 10.0);
}

TEST_F(TestMatrix3x3, CanNegate)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m0 = -m1;

    EXPECT_DOUBLE_EQ(m0.xx(), -1.0);
    EXPECT_DOUBLE_EQ(m0.xy(), -2.0);
    EXPECT_DOUBLE_EQ(m0.xz(), -3.0);
    EXPECT_DOUBLE_EQ(m0.yx(), -4.0);
    EXPECT_DOUBLE_EQ(m0.yy(), -5.0);
    EXPECT_DOUBLE_EQ(m0.yz(), -6.0);
    EXPECT_DOUBLE_EQ(m0.zx(), -7.0);
    EXPECT_DOUBLE_EQ(m0.zy(), -8.0);
    EXPECT_DOUBLE_EQ(m0.zz(), -9.0);
}

TEST_F(TestMatrix3x3, CanSubstract)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m2( 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0 );

    mc::Matrix3x3 m0 = m1 - m2;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 3.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 5.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 6.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 7.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 8.0);
}

TEST_F(TestMatrix3x3, CanMultiplyByScalar)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m0 = m1 * 0.5;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m0.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m0.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m0.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 4.5);
}

TEST_F(TestMatrix3x3, CanMultiplyByMatrix)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m2( 1.1, 2.2, 3.3,
                      4.4, 5.5, 6.6,
                      7.7, 8.8, 9.9 );

    mc::Matrix3x3 m0 = m1 * m2;

    EXPECT_NEAR(m0.xx(),  33.0, 1.0e-9);
    EXPECT_NEAR(m0.xy(),  39.6, 1.0e-9);
    EXPECT_NEAR(m0.xz(),  46.2, 1.0e-9);
    EXPECT_NEAR(m0.yx(),  72.6, 1.0e-9);
    EXPECT_NEAR(m0.yy(),  89.1, 1.0e-9);
    EXPECT_NEAR(m0.yz(), 105.6, 1.0e-9);
    EXPECT_NEAR(m0.zx(), 112.2, 1.0e-9);
    EXPECT_NEAR(m0.zy(), 138.6, 1.0e-9);
    EXPECT_NEAR(m0.zz(), 165.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanMultiplyByVector)
{
    mc::Matrix3x3 m1( 1.0, 0.0, 0.0,
                      0.0, 1.0, 0.0,
                      0.0, 0.0, 1.0 );

    mc::Matrix3x3 m2( -1.0,  0.0,  0.0,
                       0.0, -1.0,  0.0,
                       0.0,  0.0, -1.0 );

    mc::Matrix3x3 m3( 0.0, 1.0, 0.0,
                      1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0 );

    mc::Matrix3x3 m4( 1.0,  0.0,  0.0,
                      0.0,  0.0, -1.0,
                      0.0, -1.0,  0.0 );

    mc::Vector3 v(1.0, 2.0, 3.0);

    mc::Vector3 v1 = m1 * v;
    EXPECT_NEAR(v1.x(),  1.0, 1.0e-9);
    EXPECT_NEAR(v1.y(),  2.0, 1.0e-9);
    EXPECT_NEAR(v1.z(),  3.0, 1.0e-9);

    mc::Vector3 v2 = m2 * v;
    EXPECT_NEAR(v2.x(), -1.0, 1.0e-9);
    EXPECT_NEAR(v2.y(), -2.0, 1.0e-9);
    EXPECT_NEAR(v2.z(), -3.0, 1.0e-9);

    mc::Vector3 v3 = m3 * v;
    EXPECT_NEAR(v3.x(),  2.0, 1.0e-9);
    EXPECT_NEAR(v3.y(),  1.0, 1.0e-9);
    EXPECT_NEAR(v3.z(),  3.0, 1.0e-9);

    mc::Vector3 v4 = m4 * v;
    EXPECT_NEAR(v4.x(),  1.0, 1.0e-9);
    EXPECT_NEAR(v4.y(), -3.0, 1.0e-9);
    EXPECT_NEAR(v4.z(), -2.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanDivideByScalar)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );
    mc::Matrix3x3 m0 = m1 / 2.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m0.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m0.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m0.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 4.5);
}

TEST_F(TestMatrix3x3, CanUnaryAdd)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m2( 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0 );

    m1 += m2;

    EXPECT_DOUBLE_EQ(m1.xx(),  2.0);
    EXPECT_DOUBLE_EQ(m1.xy(),  3.0);
    EXPECT_DOUBLE_EQ(m1.xz(),  4.0);
    EXPECT_DOUBLE_EQ(m1.yx(),  5.0);
    EXPECT_DOUBLE_EQ(m1.yy(),  6.0);
    EXPECT_DOUBLE_EQ(m1.yz(),  7.0);
    EXPECT_DOUBLE_EQ(m1.zx(),  8.0);
    EXPECT_DOUBLE_EQ(m1.zy(),  9.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 10.0);
}

TEST_F(TestMatrix3x3, CanUnarySubstract)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::Matrix3x3 m2( 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0 );

    m1 -= m2;

    EXPECT_DOUBLE_EQ(m1.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m1.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m1.xz(), 2.0);
    EXPECT_DOUBLE_EQ(m1.yx(), 3.0);
    EXPECT_DOUBLE_EQ(m1.yy(), 4.0);
    EXPECT_DOUBLE_EQ(m1.yz(), 5.0);
    EXPECT_DOUBLE_EQ(m1.zx(), 6.0);
    EXPECT_DOUBLE_EQ(m1.zy(), 7.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 8.0);
}

TEST_F(TestMatrix3x3, CanUnaryMultiplyByScalar)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    m1 *= 0.5;

    EXPECT_DOUBLE_EQ(m1.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m1.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m1.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m1.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m1.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m1.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m1.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m1.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 4.5);
}

TEST_F(TestMatrix3x3, CanUnaryDivideByScalar)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    m1 /= 2.0;

    EXPECT_DOUBLE_EQ(m1.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m1.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m1.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m1.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m1.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m1.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m1.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m1.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 4.5);
}
