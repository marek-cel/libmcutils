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
    $$PWD/control/TestHighPassFilter.cpp \
    $$PWD/control/TestLag.cpp \
    $$PWD/control/TestLag2.cpp \
    $$PWD/control/TestLead.cpp \
    $$PWD/control/TestLeadLag.cpp \
    $$PWD/control/TestLowPassFilter.cpp \
    $$PWD/control/TestMovingAverageFilter.cpp \
    $$PWD/control/TestMovingMedianFilter.cpp \
    $$PWD/control/TestOscillator.cpp \
    $$PWD/control/TestPID.cpp \
    $$PWD/control/TestSystem2.cpp

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
    $$PWD/math/TestTable2D.cpp \
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
