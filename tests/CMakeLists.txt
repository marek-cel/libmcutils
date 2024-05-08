set(TARGET_NAME tests)

################################################################################

add_definitions(-DTEST_USING_ARMADILLO)

################################################################################

find_package(Armadillo REQUIRED)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

################################################################################

include_directories(.)

if (WIN32)
    include_directories("${ARMADILLO_INCLUDE_DIRS}/armadillo/include")
endif()

################################################################################

set(SOURCES
    CsvFileReader.cpp
    TestingEnvironment.cpp
    TestingUtils.cpp
    XcosBinFileReader.cpp
    main.cpp

    astro/TestEphemeris.cpp
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
    geo/TestMercator.cpp
    geo/TestWGS84.cpp

    math/TestAngles.cpp
    math/TestDegMinSec.cpp
    math/TestEulerRect.cpp
    math/TestGaussJordan.cpp
    math/TestMath.cpp
    math/TestMatrix3x3.cpp
    math/TestMatrix3x3_Armadillo.cpp
    math/TestMatrix4x4.cpp
    math/TestMatrix4x4_Armadillo.cpp
    math/TestMatrix6x6.cpp
    math/TestMatrix6x6_Armadillo.cpp
    math/TestMatrixMxN.cpp
    math/TestMatrixMxN_Armadillo.cpp
    math/TestMatrixNxN.cpp
    math/TestMatrixNxN_Armadillo.cpp
    math/TestQuaternion.cpp
    math/TestRandom.cpp
    math/TestRungeKutta4.cpp
    math/TestSegPlaneIsect.cpp
    math/TestTable.cpp
    math/TestTable2.cpp
    math/TestVector.cpp
    math/TestVector3.cpp
    math/TestVector4.cpp
    math/TestVector6.cpp
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
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    mcutils
    GTest::gtest
    GTest::gtest_main
    ${ARMADILLO_LIBRARIES}
)

if (UNIX)
    set(LIBS ${LIBS} gcov)
elseif(WIN32)
    set(LIBS ${LIBS} ${WS2_32_LIBRARY})
endif()

target_link_libraries(${TARGET_NAME} ${LIBS})

################################################################################

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
