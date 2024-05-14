#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/math/Matrix3x3.h>
#include <mcutils/math/Quaternion.h>

class TestQuaternion : public ::testing::Test
{
protected:
    TestQuaternion() {}
    virtual ~TestQuaternion() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestQuaternion, CanInstantiate)
{
    mc::Quaternion q0;

    EXPECT_DOUBLE_EQ(q0.e0(), 1.0);
    EXPECT_DOUBLE_EQ(q0.ex(), 0.0);
    EXPECT_DOUBLE_EQ(q0.ey(), 0.0);
    EXPECT_DOUBLE_EQ(q0.ez(), 0.0);
}

TEST_F(TestQuaternion, CanInstantiateAndSetData)
{
    mc::Quaternion q0(0.1, 0.2, 0.3, 0.4);

    EXPECT_DOUBLE_EQ(q0.e0(), 0.1);
    EXPECT_DOUBLE_EQ(q0.ex(), 0.2);
    EXPECT_DOUBLE_EQ(q0.ey(), 0.3);
    EXPECT_DOUBLE_EQ(q0.ez(), 0.4);
}

TEST_F(TestQuaternion, CanInstantiateAndSetDataFromAngles)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_quaternion.m

    mc::Quaternion q0(mc::Angles(M_PI_2/3.0, M_PI_4, 2.0*M_PI_2/3.0));

    EXPECT_NEAR(q0.e0(), 0.82236, 1.0e-5);
    EXPECT_NEAR(q0.ex(), 0.02226, 1.0e-5);
    EXPECT_NEAR(q0.ey(), 0.43968, 1.0e-5);
    EXPECT_NEAR(q0.ez(), 0.36042, 1.0e-5);
}

TEST_F(TestQuaternion, CanInstantiateAndSetDataFromAngleAndVector)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_quaternion.m

    mc::Quaternion q1(M_PI_4, mc::Vector3(1.0, 0.0, 0.0));

    EXPECT_NEAR(q1.e0(), 0.92388, 1.0e-5);
    EXPECT_NEAR(q1.ex(), 0.38268, 1.0e-5);
    EXPECT_NEAR(q1.ey(), 0.00000, 1.0e-5);
    EXPECT_NEAR(q1.ez(), 0.00000, 1.0e-5);

    mc::Quaternion q2(M_PI_4, mc::Vector3(0.0, 1.0, 0.0 ));

    EXPECT_NEAR(q2.e0(), 0.92388, 1.0e-5);
    EXPECT_NEAR(q2.ex(), 0.00000, 1.0e-5);
    EXPECT_NEAR(q2.ey(), 0.38268, 1.0e-5);
    EXPECT_NEAR(q2.ez(), 0.00000, 1.0e-5);

    mc::Quaternion q3(M_PI_4, mc::Vector3(0.0, 0.0, 1.0));

    EXPECT_NEAR(q3.e0(), 0.92388, 1.0e-5);
    EXPECT_NEAR(q3.ex(), 0.00000, 1.0e-5);
    EXPECT_NEAR(q3.ey(), 0.00000, 1.0e-5);
    EXPECT_NEAR(q3.ez(), 0.38268, 1.0e-5);

    mc::Vector3 v111(1.0, 1.0, 1.0);
    v111.Normalize();
    mc::Quaternion q4(M_PI_4, v111);

    EXPECT_NEAR(q4.e0(), 0.92388, 1.0e-5);
    EXPECT_NEAR(q4.ex(), 0.22094, 1.0e-5);
    EXPECT_NEAR(q4.ey(), 0.22094, 1.0e-5);
    EXPECT_NEAR(q4.ez(), 0.22094, 1.0e-5);
}

TEST_F(TestQuaternion, CanValidate)
{
    mc::Quaternion q0;

    EXPECT_TRUE(q0.IsValid());

    q0.e0() = 0.5;
    q0.ex() = 0.5;
    q0.ey() = 0.5;
    q0.ez() = 0.5;

    EXPECT_TRUE(q0.IsValid());

    q0.e0() = std::numeric_limits<double>::quiet_NaN();
    q0.ex() = 0.5;
    q0.ey() = 0.5;
    q0.ez() = 0.5;

    EXPECT_FALSE(q0.IsValid());

    q0.e0() = 0.5;
    q0.ex() = std::numeric_limits<double>::quiet_NaN();
    q0.ey() = 0.5;
    q0.ez() = 0.5;

    EXPECT_FALSE(q0.IsValid());

    q0.e0() = 0.5;
    q0.ex() = 0.5;
    q0.ey() = std::numeric_limits<double>::quiet_NaN();
    q0.ez() = 0.5;

    EXPECT_FALSE(q0.IsValid());

    q0.e0() = 0.5;
    q0.ex() = 0.5;
    q0.ey() = 0.5;
    q0.ez() = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE(q0.IsValid());

    q0.e0() = std::numeric_limits<double>::quiet_NaN();
    q0.ex() = std::numeric_limits<double>::quiet_NaN();
    q0.ey() = std::numeric_limits<double>::quiet_NaN();
    q0.ez() = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE(q0.IsValid());
}

TEST_F(TestQuaternion, CanConjugate)
{
    mc::Quaternion q0(1.0, 2.0, 3.0, 4.0);

    q0.Conjugate();

    EXPECT_DOUBLE_EQ(q0.e0(),  1.0);
    EXPECT_DOUBLE_EQ(q0.ex(), -2.0);
    EXPECT_DOUBLE_EQ(q0.ey(), -3.0);
    EXPECT_DOUBLE_EQ(q0.ez(), -4.0);
}

TEST_F(TestQuaternion, CanInverse)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_quaternion.m

    mc::Vector3 v111(1.0, 1.0, 1.0);
    v111.Normalize();

    mc::Quaternion q0(M_PI_4, v111);
    const mc::Quaternion qr(-M_PI_4, v111);

    q0.Invert();

    EXPECT_DOUBLE_EQ(q0.e0(), qr.e0());
    EXPECT_DOUBLE_EQ(q0.ex(), qr.ex());
    EXPECT_DOUBLE_EQ(q0.ey(), qr.ey());
    EXPECT_DOUBLE_EQ(q0.ez(), qr.ez());

    EXPECT_NEAR(q0.e0(),  0.92388, 1.0e-5);
    EXPECT_NEAR(q0.ex(), -0.22094, 1.0e-5);
    EXPECT_NEAR(q0.ey(), -0.22094, 1.0e-5);
    EXPECT_NEAR(q0.ez(), -0.22094, 1.0e-5);
}

TEST_F(TestQuaternion, CanNormalize)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_quaternion.m

    mc::Quaternion q0(1.0, 2.0, 3.0, 4.0);

    q0.Normalize();

    EXPECT_NEAR(q0.e0(), 0.18257, 1.0e-5);
    EXPECT_NEAR(q0.ex(), 0.36515, 1.0e-5);
    EXPECT_NEAR(q0.ey(), 0.54772, 1.0e-5);
    EXPECT_NEAR(q0.ez(), 0.73030, 1.0e-5);
}

TEST_F(TestQuaternion, CanGetLength2)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_quaternion.m

    mc::Quaternion q1(1.0, 1.0, 1.0, 1.0);
    mc::Quaternion q2(0.5, 0.5, 0.5, 0.5);

    EXPECT_NEAR(q1.GetLength2(), 4.0, 1.0e-9);
    EXPECT_NEAR(q2.GetLength2(), 1.0, 1.0e-9);
}

TEST_F(TestQuaternion, CanGetLength)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_quaternion.m

    mc::Quaternion q1(1.0, 1.0, 1.0, 1.0);
    mc::Quaternion q2(0.5, 0.5, 0.5, 0.5);

    EXPECT_NEAR(q1.GetLength(), 2.0, 1.0e-9);
    EXPECT_NEAR(q2.GetLength(), 1.0, 1.0e-9);
}

TEST_F(TestQuaternion, CanGetAnglesPhiQuarterPi)
{
    const mc::Angles ang(M_PI_4, 0.0, 0.0);
    mc::Quaternion quat(ang);
    mc::Angles result = quat.GetAngles();
    EXPECT_DOUBLE_EQ(result.phi(), ang.phi());
    EXPECT_DOUBLE_EQ(result.tht(), ang.tht());
    EXPECT_DOUBLE_EQ(result.psi(), ang.psi());
}

TEST_F(TestQuaternion, CanGetAnglesThetaQuarterPi)
{
    const mc::Angles ang(0.0, M_PI_4, 0.0);
    mc::Quaternion quat(ang);
    mc::Angles result = quat.GetAngles();
    EXPECT_DOUBLE_EQ(result.phi(), ang.phi());
    EXPECT_DOUBLE_EQ(result.tht(), ang.tht());
    EXPECT_DOUBLE_EQ(result.psi(), ang.psi());
}

TEST_F(TestQuaternion, CanGetAnglesPsiQuarterPi)
{
    const mc::Angles ang(0.0, 0.0, M_PI_4);
    mc::Quaternion quat(ang);
    mc::Angles result = quat.GetAngles();
    EXPECT_DOUBLE_EQ(result.phi(), ang.phi());
    EXPECT_DOUBLE_EQ(result.tht(), ang.tht());
    EXPECT_DOUBLE_EQ(result.psi(), ang.psi());
}

TEST_F(TestQuaternion, CanGetAnglesPhiThetaPsiQuarterPi)
{
    const mc::Angles ang(M_PI_4, M_PI_4, M_PI_4);
    mc::Quaternion quat(ang);
    mc::Angles result = quat.GetAngles();
    EXPECT_DOUBLE_EQ(result.phi(), ang.phi());
    EXPECT_DOUBLE_EQ(result.tht(), ang.tht());
    EXPECT_DOUBLE_EQ(result.psi(), ang.psi());
}

TEST_F(TestQuaternion, CanGetConjugated)
{
    mc::Quaternion q0(1.0, 2.0, 3.0, 4.0);
    mc::Quaternion q1 = q0.GetConjugated();

    EXPECT_DOUBLE_EQ(q0.e0(),  1.0);
    EXPECT_DOUBLE_EQ(q0.ex(),  2.0);
    EXPECT_DOUBLE_EQ(q0.ey(),  3.0);
    EXPECT_DOUBLE_EQ(q0.ez(),  4.0);

    EXPECT_DOUBLE_EQ(q1.e0(),  1.0);
    EXPECT_DOUBLE_EQ(q1.ex(), -2.0);
    EXPECT_DOUBLE_EQ(q1.ey(), -3.0);
    EXPECT_DOUBLE_EQ(q1.ez(), -4.0);
}

TEST_F(TestQuaternion, CanGetInverted)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_quaternion.m

    mc::Vector3 v111(1.0, 1.0, 1.0);
    v111.Normalize();

    mc::Quaternion q0(M_PI_4, v111);
    const mc::Quaternion qc(q0);
    const mc::Quaternion qr(-M_PI_4, v111);

    mc::Quaternion q1 = q0.GetInverted();

    EXPECT_DOUBLE_EQ(q0.e0(), qc.e0());
    EXPECT_DOUBLE_EQ(q0.ex(), qc.ex());
    EXPECT_DOUBLE_EQ(q0.ey(), qc.ey());
    EXPECT_DOUBLE_EQ(q0.ez(), qc.ez());

    EXPECT_DOUBLE_EQ(q1.e0(), qr.e0());
    EXPECT_DOUBLE_EQ(q1.ex(), qr.ex());
    EXPECT_DOUBLE_EQ(q1.ey(), qr.ey());
    EXPECT_DOUBLE_EQ(q1.ez(), qr.ez());

    EXPECT_NEAR(q1.e0(),  0.92388, 1.0e-5);
    EXPECT_NEAR(q1.ex(), -0.22094, 1.0e-5);
    EXPECT_NEAR(q1.ey(), -0.22094, 1.0e-5);
    EXPECT_NEAR(q1.ez(), -0.22094, 1.0e-5);
}

TEST_F(TestQuaternion, CanGetDerivative)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_quaternion.m

    mc::Vector3 v111(1.0, 1.0, 1.0);
    v111.Normalize();

    mc::Quaternion q(M_PI_4, v111);
    mc::Vector3 omega(1.0, 2.0, 3.0);

    mc::Quaternion q0 = q.GetDerivative(omega);

    EXPECT_NEAR(q0.e0(), -0.66283, 1.0e-5);
    EXPECT_NEAR(q0.ex(),  0.57241, 1.0e-5);
    EXPECT_NEAR(q0.ey(),  0.70294, 1.0e-5);
    EXPECT_NEAR(q0.ez(),  1.49630, 1.0e-5);
}

TEST_F(TestQuaternion, CanGetDerivativeLambdaGreaterThanZero)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_quaternion.m

    mc::Vector3 v111(1.0, 1.0, 1.0);
    v111.Normalize();

    mc::Quaternion q(M_PI_4, v111);
    mc::Vector3 omega(1.0, 2.0, 3.0);

    mc::Quaternion q0 = q.GetDerivative(omega, 0.1);

    EXPECT_NEAR(q0.e0(), -0.66283, 1.0e-5);
    EXPECT_NEAR(q0.ex(),  0.57241, 1.0e-5);
    EXPECT_NEAR(q0.ey(),  0.70294, 1.0e-5);
    EXPECT_NEAR(q0.ez(),  1.49630, 1.0e-5);
}

TEST_F(TestQuaternion, CanGetNormalized)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_quaternion.m

    mc::Quaternion q0(1.0, 2.0, 3.0, 4.0);
    mc::Quaternion q1 = q0.GetNormalized();

    EXPECT_DOUBLE_EQ(q0.e0(),  1.0);
    EXPECT_DOUBLE_EQ(q0.ex(),  2.0);
    EXPECT_DOUBLE_EQ(q0.ey(),  3.0);
    EXPECT_DOUBLE_EQ(q0.ez(),  4.0);

    EXPECT_NEAR(q1.e0(), 0.18257, 1.0e-5);
    EXPECT_NEAR(q1.ex(), 0.36515, 1.0e-5);
    EXPECT_NEAR(q1.ey(), 0.54772, 1.0e-5);
    EXPECT_NEAR(q1.ez(), 0.73030, 1.0e-5);
}

TEST_F(TestQuaternion, CanSetValues)
{
    mc::Quaternion q0;

    q0.Set(1.0, 2.0, 3.0, 4.0);

    EXPECT_DOUBLE_EQ(q0.e0(), 1.0);
    EXPECT_DOUBLE_EQ(q0.ex(), 2.0);
    EXPECT_DOUBLE_EQ(q0.ey(), 3.0);
    EXPECT_DOUBLE_EQ(q0.ez(), 4.0);
}

TEST_F(TestQuaternion, CanAdd)
{
    mc::Quaternion q0(1.0, 2.0, 3.0, 4.0);
    mc::Quaternion q1(5.0, 6.0, 7.0, 8.0);
    mc::Quaternion q2 = q0 + q1;

    EXPECT_DOUBLE_EQ(q2.e0(),  6.0);
    EXPECT_DOUBLE_EQ(q2.ex(),  8.0);
    EXPECT_DOUBLE_EQ(q2.ey(), 10.0);
    EXPECT_DOUBLE_EQ(q2.ez(), 12.0);
}

TEST_F(TestQuaternion, CanSubstract)
{
    mc::Quaternion q0(4.0, 3.0, 2.0, 1.0);
    mc::Quaternion q1(5.0, 6.0, 7.0, 8.0);
    mc::Quaternion q2 = q1 - q0;

    EXPECT_DOUBLE_EQ(q2.e0(), 1.0);
    EXPECT_DOUBLE_EQ(q2.ex(), 3.0);
    EXPECT_DOUBLE_EQ(q2.ey(), 5.0);
    EXPECT_DOUBLE_EQ(q2.ez(), 7.0);
}

TEST_F(TestQuaternion, CanMultiplyByScalar)
{
    mc::Quaternion q0(1.0, 2.0, 3.0, 4.0);
    mc::Quaternion q1 = q0 * 2.0;

    EXPECT_DOUBLE_EQ(q1.e0(), 2.0);
    EXPECT_DOUBLE_EQ(q1.ex(), 4.0);
    EXPECT_DOUBLE_EQ(q1.ey(), 6.0);
    EXPECT_DOUBLE_EQ(q1.ez(), 8.0);
}

TEST_F(TestQuaternion, CanMultiplyByQuaternion)
{
    // expected values calculated with GNU Octave
    // tests/math/octave/test_quaternion.m

    mc::Quaternion q1(M_PI_2, mc::Vector3(1.0, 0.0, 0.0 ));
    mc::Quaternion q2(M_PI_4, mc::Vector3(0.0, 1.0, 0.0 ));
    mc::Quaternion q = q1 * q2;

    EXPECT_NEAR(q.e0(), 0.65328, 1.0e-5);
    EXPECT_NEAR(q.ex(), 0.65328, 1.0e-5);
    EXPECT_NEAR(q.ey(), 0.27060, 1.0e-5);
    EXPECT_NEAR(q.ez(), 0.27060, 1.0e-5);
}

TEST_F(TestQuaternion, CanDivideByScalar)
{
    mc::Quaternion q0(2.0, 4.0, 6.0, 8.0);
    mc::Quaternion q1 = q0 / 2.0;

    EXPECT_DOUBLE_EQ(q1.e0(), 1.0);
    EXPECT_DOUBLE_EQ(q1.ex(), 2.0);
    EXPECT_DOUBLE_EQ(q1.ey(), 3.0);
    EXPECT_DOUBLE_EQ(q1.ez(), 4.0);
}

TEST_F(TestQuaternion, CanUnaryAdd)
{
    mc::Quaternion q0(1.0, 2.0, 3.0, 4.0);
    mc::Quaternion q1(5.0, 6.0, 7.0, 8.0);

    q0 += q1;

    EXPECT_DOUBLE_EQ(q0.e0(),  6.0);
    EXPECT_DOUBLE_EQ(q0.ex(),  8.0);
    EXPECT_DOUBLE_EQ(q0.ey(), 10.0);
    EXPECT_DOUBLE_EQ(q0.ez(), 12.0);
}

TEST_F(TestQuaternion, CanUnarySubstract)
{
    mc::Quaternion q0(4.0, 3.0, 2.0, 1.0);
    mc::Quaternion q1(5.0, 6.0, 7.0, 8.0);

    q1 -= q0;

    EXPECT_DOUBLE_EQ(q1.e0(), 1.0);
    EXPECT_DOUBLE_EQ(q1.ex(), 3.0);
    EXPECT_DOUBLE_EQ(q1.ey(), 5.0);
    EXPECT_DOUBLE_EQ(q1.ez(), 7.0);
}

TEST_F(TestQuaternion, CanUnaryMultiplyByScalar)
{
    mc::Quaternion q0(1.0, 2.0, 3.0, 4.0);

    q0 *= 2.0;

    EXPECT_DOUBLE_EQ(q0.e0(), 2.0);
    EXPECT_DOUBLE_EQ(q0.ex(), 4.0);
    EXPECT_DOUBLE_EQ(q0.ey(), 6.0);
    EXPECT_DOUBLE_EQ(q0.ez(), 8.0);
}

TEST_F(TestQuaternion, CanUnaryDivideByScalar)
{
    mc::Quaternion q0(2.0, 4.0, 6.0, 8.0);

    q0 /= 2.0;

    EXPECT_DOUBLE_EQ(q0.e0(), 1.0);
    EXPECT_DOUBLE_EQ(q0.ex(), 2.0);
    EXPECT_DOUBLE_EQ(q0.ey(), 3.0);
    EXPECT_DOUBLE_EQ(q0.ez(), 4.0);
}

TEST_F(TestQuaternion, CanConvertToString)
{
    mc::Quaternion q(1.0, 2.0, 3.0, 4.0);
    EXPECT_STREQ(q.ToString().c_str(), "1,2,3,4");
}

TEST_F(TestQuaternion, CanCompare)
{
    mc::Quaternion q(0.0, 0.0, 0.0, 0.0);

    mc::Quaternion q1(1.0, 0.0, 0.0, 0.0);
    mc::Quaternion q2(0.0, 1.0, 0.0, 0.0);
    mc::Quaternion q3(0.0, 0.0, 1.0, 0.0);
    mc::Quaternion q4(0.0, 0.0, 0.0, 1.0);
    mc::Quaternion q5(1.0, 1.0, 1.0, 1.0);

    EXPECT_FALSE(q == q1);
    EXPECT_TRUE(q != q1);
    q = q1;
    EXPECT_TRUE(q == q1);
    EXPECT_FALSE(q != q1);

    EXPECT_FALSE(q == q2);
    EXPECT_TRUE(q != q2);
    q = q2;
    EXPECT_TRUE(q == q2);
    EXPECT_FALSE(q != q2);

    EXPECT_FALSE(q == q3);
    EXPECT_TRUE(q != q3);
    q = q3;
    EXPECT_TRUE(q == q3);
    EXPECT_FALSE(q != q3);

    EXPECT_FALSE(q == q4);
    EXPECT_TRUE(q != q4);
    q = q4;
    EXPECT_TRUE(q == q4);
    EXPECT_FALSE(q != q4);

    EXPECT_FALSE(q == q5);
    EXPECT_TRUE(q != q5);
    q = q5;
    EXPECT_TRUE(q == q5);
    EXPECT_FALSE(q != q5);
}

