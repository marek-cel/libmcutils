set( TARGET_NAME tests )

################################################################################

find_package( GTest REQUIRED )
find_package( Threads REQUIRED )

################################################################################

include_directories( . )

################################################################################

set( SOURCES
    CsvFileReader.cpp
    DiffEquationSolver.cpp
    TestDummy.cpp
    TestingEnvironment.cpp
    XcosBinFileReader.cpp
    main.cpp

    ctrl/TestAntiWindupPID.cpp
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
    ctrl/TestStateSpace.cpp
    ctrl/TestSystem2.cpp

    geo/TestDataMars.cpp
    geo/TestDataWGS84.cpp
    geo/TestECEF.cpp
    geo/TestMercator.cpp
    geo/TestWGS84.cpp

    math/TestAngles.cpp
    math/TestDegMinSec.cpp
    math/TestEulerRect.cpp
    math/TestMath.cpp
    math/TestMatrix.cpp
    math/TestMatrix3x3.cpp
    math/TestMatrix4x4.cpp
    math/TestMatrix6x6.cpp
    math/TestMatrixSq.cpp
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
    misc/TestString.cpp
    misc/TestUnits.cpp

    net/TestEndianness.cpp

    physics/TestPhysics.cpp

    time/TestClockTime.cpp
    time/TestISO8601.cpp
)

################################################################################

add_executable( ${TARGET_NAME} WIN32 ${SOURCES} )

target_link_libraries( ${TARGET_NAME}

    -Wl,--start-group

    gcov

    mcutils-ctrl
    mcutils-geo
    mcutils-math
    mcutils-misc
    mcutils-net
    mcutils-time

    GTest::gtest
    GTest::gtest_main
    ${CMAKE_THREAD_LIBS_INIT}

    -Wl,--end-group
)

################################################################################

add_test( NAME ${TARGET_NAME} COMMAND ${TARGET_NAME} )
