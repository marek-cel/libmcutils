#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/math/Angles.h>
#include <mcutils/math/Quaternion.h>

class TestAngles : public ::testing::Test
{
protected:
    TestAngles() {}
    virtual ~TestAngles() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestAngles, CanNormalizeAngle)
{
    EXPECT_DOUBLE_EQ(mc::Angles::Normalize(2.0 * M_PI + M_PI_4), M_PI_4);
    EXPECT_DOUBLE_EQ(mc::Angles::Normalize(2.0 * M_PI - M_PI_4), 1.75 * M_PI);
}

TEST_F(TestAngles, CanInstantiate)
{
    mc::Angles angles;

    EXPECT_DOUBLE_EQ(angles.phi(), 0.0);
    EXPECT_DOUBLE_EQ(angles.tht(), 0.0);
    EXPECT_DOUBLE_EQ(angles.psi(), 0.0);
}

TEST_F(TestAngles, CanInstantiateAndSetData)
{
    mc::Angles angles1(M_PI_4, 0.0, 0.0);

    EXPECT_DOUBLE_EQ(angles1.phi(), M_PI_4);
    EXPECT_DOUBLE_EQ(angles1.tht(), 0.0   );
    EXPECT_DOUBLE_EQ(angles1.psi(), 0.0   );

    mc::Angles angles2(0.0, M_PI_4, 0.0);

    EXPECT_DOUBLE_EQ(angles2.phi(), 0.0   );
    EXPECT_DOUBLE_EQ(angles2.tht(), M_PI_4);
    EXPECT_DOUBLE_EQ(angles2.psi(), 0.0   );

    mc::Angles angles3(0.0, 0.0, M_PI_4);

    EXPECT_DOUBLE_EQ(angles3.phi(), 0.0   );
    EXPECT_DOUBLE_EQ(angles3.tht(), 0.0   );
    EXPECT_DOUBLE_EQ(angles3.psi(), M_PI_4);

    mc::Angles angles4(M_PI_4, M_PI_4, M_PI_4);

    EXPECT_DOUBLE_EQ(angles4.phi(), M_PI_4);
    EXPECT_DOUBLE_EQ(angles4.tht(), M_PI_4);
    EXPECT_DOUBLE_EQ(angles4.psi(), M_PI_4);
}

TEST_F(TestAngles, CanValidate)
{
    mc::Angles angles1(0.0, 0.0, 0.0);
    EXPECT_TRUE(angles1.IsValid());

    mc::Angles angles2(std::numeric_limits<double>::quiet_NaN(), 0.0, 0.0);
    EXPECT_FALSE(angles2.IsValid());

    mc::Angles angles3(0.0, std::numeric_limits<double>::quiet_NaN(), 0.0);
    EXPECT_FALSE(angles3.IsValid());

    mc::Angles angles4(0.0, 0.0, std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(angles4.IsValid());
}

TEST_F(TestAngles, CanNormalize)
{
    mc::Angles a(2.2 * M_PI, 2.3 * M_PI, 2.4 * M_PI);
    mc::Quaternion q(a);
    mc::Angles a1 = q.GetAngles();

    a.Normalize();

    EXPECT_NEAR(a.phi(), a1.phi(), 1.0e-9);
    EXPECT_NEAR(a.tht(), a1.tht(), 1.0e-9);
    EXPECT_NEAR(a.psi(), a1.psi(), 1.0e-9);
}

TEST_F(TestAngles, CanConvertToString)
{
    mc::Angles a(M_PI_4, M_PI_4, M_PI_4);
    EXPECT_STREQ(a.ToString().c_str(), "45.00,45.00,45.00");
}

TEST_F(TestAngles, CanCompare)
{
    mc::Angles a;

    mc::Angles a1(M_PI, 0.0, 0.0);
    mc::Angles a2(0.0, M_PI, 0.0);
    mc::Angles a3(0.0, 0.0, M_PI);
    mc::Angles a4(1.0, 2.0, 3.0);

    EXPECT_FALSE(a == a1);
    EXPECT_TRUE(a != a1);
    a = a1;
    EXPECT_TRUE(a == a1);
    EXPECT_FALSE(a != a1);

    EXPECT_FALSE(a == a2);
    EXPECT_TRUE(a != a2);
    a = a2;
    EXPECT_TRUE(a == a2);
    EXPECT_FALSE(a != a2);

    EXPECT_FALSE(a == a3);
    EXPECT_TRUE(a != a3);
    a = a3;
    EXPECT_TRUE(a == a3);
    EXPECT_FALSE(a != a3);

    EXPECT_FALSE(a == a4);
    EXPECT_TRUE(a != a4);
    a = a4;
    EXPECT_TRUE(a == a4);
    EXPECT_FALSE(a != a4);
}
