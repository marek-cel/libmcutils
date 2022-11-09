SOURCES += \
    $$PWD/main.cpp

################################################################################

HEADERS += \
    $$PWD/CsvFileReader.h \
    $$PWD/DiffEquationSolver.h \
    $$PWD/XcosBinFileReader.h

SOURCES += \
    $$PWD/CsvFileReader.cpp \
    $$PWD/DiffEquationSolver.cpp \
    $$PWD/TestDummy.cpp \
    $$PWD/TestingEnvironment.cpp \
    $$PWD/XcosBinFileReader.cpp

################################################################################

SOURCES += \
    $$PWD/ctrl/TestGain.cpp \
    $$PWD/ctrl/TestHighPassFilter.cpp \
    $$PWD/ctrl/TestInertia.cpp \
    $$PWD/ctrl/TestInertia2.cpp \
    $$PWD/ctrl/TestLead.cpp \
    $$PWD/ctrl/TestLeadLag.cpp \
    $$PWD/ctrl/TestLowPassFilter.cpp \
    $$PWD/ctrl/TestMovingAverage.cpp \
    $$PWD/ctrl/TestMovingMedian.cpp \
    $$PWD/ctrl/TestOscillator.cpp \
    $$PWD/ctrl/TestPID.cpp \
    $$PWD/ctrl/TestStateSpace.cpp \
    $$PWD/ctrl/TestSystem2.cpp

################################################################################

SOURCES += \
    $$PWD/datatree/TestDataRef.cpp \
    $$PWD/datatree/TestDataTree.cpp \
    $$PWD/datatree/TestGroupNode.cpp \
    $$PWD/datatree/TestNode.cpp \
    $$PWD/datatree/TestValueNode.cpp

################################################################################

SOURCES += \
    $$PWD/geo/TestDataMars.cpp \
    $$PWD/geo/TestDataWGS84.cpp \
    $$PWD/geo/TestECEF.cpp \
    $$PWD/geo/TestMercator.cpp \
    $$PWD/geo/TestWGS84.cpp

################################################################################

SOURCES += \
    $$PWD/math/TestAngles.cpp \
    $$PWD/math/TestDegMinSec.cpp \
    $$PWD/math/TestEulerRect.cpp \
    $$PWD/math/TestMath.cpp \
    $$PWD/math/TestMatrix.cpp \
    $$PWD/math/TestMatrix3x3.cpp \
    $$PWD/math/TestMatrix4x4.cpp \
    $$PWD/math/TestMatrix6x6.cpp \
    $$PWD/math/TestMatrixSq.cpp \
    $$PWD/math/TestQuaternion.cpp \
    $$PWD/math/TestRandom.cpp \
    $$PWD/math/TestRungeKutta4.cpp \
    $$PWD/math/TestSegPlaneIsect.cpp \
    $$PWD/math/TestTable.cpp \
    $$PWD/math/TestTable2.cpp \
    $$PWD/math/TestVector.cpp \
    $$PWD/math/TestVector3.cpp \
    $$PWD/math/TestVector4.cpp \
    $$PWD/math/TestVector6.cpp \
    $$PWD/math/TestVectorN.cpp

################################################################################

SOURCES += \
    $$PWD/misc/TestCheck.cpp \
    $$PWD/misc/TestLog.cpp \
    $$PWD/misc/TestString.cpp \
    $$PWD/misc/TestUnits.cpp

################################################################################

SOURCES += \
    $$PWD/net/TestEndianness.cpp

################################################################################

SOURCES += \
    $$PWD/physics/TestPhysics.cpp

################################################################################

SOURCES += \
    $$PWD/time/TestClockTime.cpp \
    $$PWD/time/TestISO8601.cpp

################################################################################

SOURCES += \
    $$PWD/xml/TestXmlDoc.cpp \
    $$PWD/xml/TestXmlNode.cpp
