#include <gtest/gtest.h>

#include <mcutils/geo/DataMars.h>

////////////////////////////////////////////////////////////////////////////////

class TestDataMars : public ::testing::Test
{
protected:
    TestDataMars() {}
    virtual ~TestDataMars() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataMars, IsEquatorialRadiusCorrect)
{
    // Report of the IAU Working Group on Cartographic Coordinates and Rotational Elements: 2015, p.28
    EXPECT_NEAR(mc::DataMars::a, 3396.19e3, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataMars, IsPolarRadiusCorrect)
{
    // Report of the IAU Working Group on Cartographic Coordinates and Rotational Elements: 2015, p.28
    EXPECT_NEAR(mc::DataMars::b, 3376.2e3, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataMars, IsEllipsoidFlatteningCorrect)
{
    // calculated with GNU Octave
    // tests/geo/python/test_geo_data_mars.py
    EXPECT_NEAR(mc::DataMars::f, 0.005886007555525457, 1.0e-12);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataMars, IsMeanRadiusCorrect)
{
    // calculated with GNU Octave
    // tests/geo/python/test_geo_data_mars.py
    EXPECT_NEAR(mc::DataMars::r1, 3389526.6666666665, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataMars, IsEquatorialRadiusSquaredCorrect)
{
    // calculated with GNU Octave
    // tests/geo/python/test_geo_data_mars.py
    EXPECT_NEAR(mc::DataMars::a2, 11534106516100.0, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataMars, IsPolarRadiusSquaredCorrect)
{
    // calculated with GNU Octave
    // tests/geo/python/test_geo_data_mars.py
    EXPECT_NEAR(mc::DataMars::b2, 11398726440000.0, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataMars, IsEllipsoidFirstEccentricitySquaredCorrect)
{
    // calculated with GNU Octave
    // tests/geo/python/test_geo_data_mars.py
    EXPECT_NEAR(mc::DataMars::e2, 0.011737370026107197, 1.0e-12);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataMars, IsEllipsoidFirstEccentricityCorrect)
{
    // calculated with GNU Octave
    // tests/geo/python/test_geo_data_mars.py
    EXPECT_NEAR(mc::DataMars::e, 0.1083391435544291, 1.0e-12);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataMars, IsEllipsoidSecondEccentricitySquaredCorrect)
{
    // calculated with GNU Octave
    // tests/geo/python/test_geo_data_mars.py
    EXPECT_NEAR(mc::DataMars::ep2, 0.0118767720949009, 1.0e-12);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataMars, IsEllipsoidSecondEccentricityCorrect)
{
    // calculated with GNU Octave
    // tests/geo/python/test_geo_data_mars.py
    EXPECT_NEAR(mc::DataMars::ep, 0.10898060421424034, 1.0e-12);
}
