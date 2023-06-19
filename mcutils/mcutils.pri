HEADERS += \
    $$PWD/defs.h \
    $$PWD/doxygen.h \
    $$PWD/Result.h \
    $$PWD/Types.h

################################################################################

HEADERS += \
    $$PWD/ctrl/AWBackCalc.h \
    $$PWD/ctrl/AWCondCalc.h \
    $$PWD/ctrl/AWFilter.h \
    $$PWD/ctrl/HighPassFilter.h \
    $$PWD/ctrl/IAntiWindup.h \
    $$PWD/ctrl/Inertia.h \
    $$PWD/ctrl/Inertia2.h \
    $$PWD/ctrl/Lead.h \
    $$PWD/ctrl/LeadLag.h \
    $$PWD/ctrl/LowPassFilter.h \
    $$PWD/ctrl/MovingAverage.h \
    $$PWD/ctrl/MovingMedian.h \
    $$PWD/ctrl/Oscillator.h \
    $$PWD/ctrl/PID.h \
    $$PWD/ctrl/System2.h

SOURCES += \
    $$PWD/ctrl/AWBackCalc.cpp \
    $$PWD/ctrl/AWCondCalc.cpp \
    $$PWD/ctrl/AWFilter.cpp \
    $$PWD/ctrl/HighPassFilter.cpp \
    $$PWD/ctrl/Inertia.cpp \
    $$PWD/ctrl/Inertia2.cpp \
    $$PWD/ctrl/Lead.cpp \
    $$PWD/ctrl/LeadLag.cpp \
    $$PWD/ctrl/LowPassFilter.cpp \
    $$PWD/ctrl/MovingAverage.cpp \
    $$PWD/ctrl/MovingMedian.cpp \
    $$PWD/ctrl/Oscillator.cpp \
    $$PWD/ctrl/PID.cpp \
    $$PWD/ctrl/System2.cpp

################################################################################

HEADERS += \
    $$PWD/geo/DataMars.h \
    $$PWD/geo/DataWGS84.h \
    $$PWD/geo/ECEF.h \
    $$PWD/geo/Geo.h \
    $$PWD/geo/Mercator.h \
    $$PWD/geo/WGS84.h

SOURCES += \
    $$PWD/geo/ECEF.cpp \
    $$PWD/geo/Mercator.cpp \
    $$PWD/geo/WGS84.cpp

################################################################################

HEADERS += \
    $$PWD/math/Angles.h \
    $$PWD/math/DegMinSec.h \
    $$PWD/math/EulerRect.h \
    $$PWD/math/GaussJordan.h \
    $$PWD/math/Integrator.h \
    $$PWD/math/Math.h \
    $$PWD/math/Matrix3x3.h \
    $$PWD/math/Matrix4x4.h \
    $$PWD/math/Matrix6x6.h \
    $$PWD/math/MatrixMxN.h \
    $$PWD/math/MatrixNxN.h \
    $$PWD/math/Quaternion.h \
    $$PWD/math/Random.h \
    $$PWD/math/RungeKutta4.h \
    $$PWD/math/SegPlaneIsect.h \
    $$PWD/math/Table.h \
    $$PWD/math/Table2.h \
    $$PWD/math/Vector.h \
    $$PWD/math/Vector3.h \
    $$PWD/math/Vector4.h \
    $$PWD/math/Vector6.h \
    $$PWD/math/VectorN.h

SOURCES += \
    $$PWD/math/Angles.cpp \
    $$PWD/math/DegMinSec.cpp \
    $$PWD/math/EulerRect.cpp \
    $$PWD/math/Matrix3x3.cpp \
    $$PWD/math/Matrix4x4.cpp \
    $$PWD/math/Matrix6x6.cpp \
    $$PWD/math/Quaternion.cpp \
    $$PWD/math/Random.cpp \
    $$PWD/math/RungeKutta4.cpp \
    $$PWD/math/SegPlaneIsect.cpp \
    $$PWD/math/Table.cpp \
    $$PWD/math/Table2.cpp \
    $$PWD/math/Vector.cpp \
    $$PWD/math/Vector3.cpp \
    $$PWD/math/Vector4.cpp \
    $$PWD/math/Vector6.cpp

################################################################################

HEADERS += \
    $$PWD/misc/Check.h \
    $$PWD/misc/Log.h \
    $$PWD/misc/Map.h \
    $$PWD/misc/Singleton.h \
    $$PWD/misc/String.h \
    $$PWD/misc/Units.h

SOURCES += \
    $$PWD/misc/Log.cpp \
    $$PWD/misc/String.cpp \
    $$PWD/misc/Units.cpp

################################################################################

HEADERS += \
    $$PWD/physics/Physics.h

SOURCES += \

################################################################################

HEADERS += \
    $$PWD/time/ClockTime.h \
    $$PWD/time/DateTime.h \
    $$PWD/time/ISO8601.h

SOURCES += \
    $$PWD/time/ISO8601.cpp
