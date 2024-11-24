set(TARGET_NAME tests-mcutils)

################################################################################

find_package(GTest REQUIRED)

################################################################################

include_directories(.)

################################################################################

set(SOURCES
    CsvFileReader.cpp
    TestingEnvironment.cpp
    TestingUtils.cpp
    XcosBinFileReader.cpp
    main.cpp

    astro/TestEphemeris.cpp
    astro/TestGregorianCal.cpp
    astro/TestJulianDate.cpp
    astro/TestRaDec2AzEl.cpp

    ctrl/TestHighPassFilter.cpp
    ctrl/TestInertia.cpp
    ctrl/TestInertia2.cpp
    ctrl/TestLead.cpp
    ctrl/TestLeadLag.cpp
    ctrl/TestLowPassFilter.cpp
    ctrl/TestMovingAverage.cpp
    ctrl/TestMovingMedian.cpp
    ctrl/TestOscillator.cpp
    ctrl/TestPID.cpp
    ctrl/TestPID_BackCalc.cpp
    ctrl/TestPID_CondCalc.cpp
    ctrl/TestPID_FilterAW.cpp
    ctrl/TestSystem2.cpp
    ctrl/TestZeroOrderHold.cpp

    geo/TestECEF.cpp
    geo/TestEllipsoid.cpp
    geo/TestMercator.cpp

    math/TestAngles.cpp
    math/TestDegMinSec.cpp
    math/TestEulerRect.cpp
    math/TestGaussJordan.cpp
    math/TestMath.cpp
    math/TestMatrix3x3.cpp
    math/TestMatrixMxN.cpp
    math/TestMatrixNxN.cpp
    math/TestQuaternion.cpp
    math/TestRotMatrix.cpp
    math/TestRandom.cpp
    math/TestRungeKutta4.cpp
    math/TestSegPlaneIsect.cpp
    math/TestTable.cpp
    math/TestTable2.cpp
    math/TestVector3.cpp
    math/TestVectorN.cpp

    misc/TestCheck.cpp
    misc/TestLog.cpp
    misc/TestMapUtils.cpp
    misc/TestPtrUtils.cpp
    misc/TestString.cpp
    misc/TestUnits.cpp

    net/TestEndianness.cpp

    physics/TestInertia.cpp
    physics/TestParallelAxis.cpp

    time/TestClockTime.cpp
    time/TestISO8601.cpp
    time/TestTimer.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    mcutils
    GTest::gtest
    GTest::gtest_main
)

if (UNIX)
    set(LIBS ${LIBS} ${ARMADILLO_LIBRARIES} gcov)
elseif(WIN32)
    set(LIBS ${LIBS} ws2_32)
endif()

target_link_libraries(${TARGET_NAME} ${LIBS})

################################################################################

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
