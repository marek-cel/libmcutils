SOURCES += \
    $$PWD/main.cpp

################################################################################

HEADERS += \
    $$PWD/DiffEquationSolver.h \
    $$PWD/XcosBinFileReader.h

SOURCES += \
    $$PWD/DiffEquationSolver.cpp \
    $$PWD/TestDummy.cpp \
    $$PWD/TestingEnvironment.cpp \
    $$PWD/XcosBinFileReader.cpp

################################################################################

SOURCES += \
    $$PWD/geo/TestECEF.cpp

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
    $$PWD/math/TestQuaternion.cpp \
    $$PWD/math/TestRungeKutta4.cpp \
    $$PWD/math/TestTable.cpp \
    $$PWD/math/TestTable2D.cpp \
    $$PWD/math/TestVector.cpp \
    $$PWD/math/TestVector3.cpp \
    $$PWD/math/TestVector4.cpp \
    $$PWD/math/TestVector6.cpp \
    $$PWD/math/TestVectorN.cpp

################################################################################

SOURCES += \
    $$PWD/physics/TestPhysics.cpp

################################################################################

SOURCES += \
    $$PWD/signal/TestFilter2.cpp \
    $$PWD/signal/TestHighPassFilter.cpp \
    $$PWD/signal/TestLag.cpp \
    $$PWD/signal/TestLag2.cpp \
    $$PWD/signal/TestLead.cpp \
    $$PWD/signal/TestLeadLag.cpp \
    $$PWD/signal/TestLowPassFilter.cpp \
    $$PWD/signal/TestMovingAverageFilter.cpp \
    $$PWD/signal/TestMovingMedianFilter.cpp \
    $$PWD/signal/TestPID.cpp

