HEADERS += \
    $$PWD/defs.h \
    $$PWD/doxygen.h \
    $$PWD/Result.h \
    $$PWD/Types.h

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
    $$PWD/math/Geometry.h \
    $$PWD/math/Integrator.h \
    $$PWD/math/Math.h \
    $$PWD/math/Matrix.h \
    $$PWD/math/Matrix3x3.h \
    $$PWD/math/Matrix4x4.h \
    $$PWD/math/Matrix6x6.h \
    $$PWD/math/MatrixSq.h \
    $$PWD/math/Quaternion.h \
    $$PWD/math/Random.h \
    $$PWD/math/RungeKutta4.h \
    $$PWD/math/Table.h \
    $$PWD/math/Table2D.h \
    $$PWD/math/Vector.h \
    $$PWD/math/Vector3.h \
    $$PWD/math/Vector4.h \
    $$PWD/math/Vector6.h \
    $$PWD/math/VectorN.h

SOURCES += \
    $$PWD/math/Angles.cpp \
    $$PWD/math/DegMinSec.cpp \
    $$PWD/math/EulerRect.cpp \
    $$PWD/math/Geometry.cpp \
    $$PWD/math/Matrix3x3.cpp \
    $$PWD/math/Matrix4x4.cpp \
    $$PWD/math/Matrix6x6.cpp \
    $$PWD/math/Quaternion.cpp \
    $$PWD/math/Random.cpp \
    $$PWD/math/RungeKutta4.cpp \
    $$PWD/math/Table.cpp \
    $$PWD/math/Table2D.cpp \
    $$PWD/math/Vector3.cpp \
    $$PWD/math/Vector4.cpp \
    $$PWD/math/Vector6.cpp \
    $$PWD/math/VectorN.cpp

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
    $$PWD/net/Endianness.h

SOURCES += \
    $$PWD/net/Endianness.cpp

################################################################################

HEADERS += \
    $$PWD/physics/Physics.h

SOURCES += \

################################################################################

HEADERS += \
    $$PWD/signal/ISignalElement.h \
    $$PWD/signal/Filter2.h \
    $$PWD/signal/HighPassFilter.h \
    $$PWD/signal/LowPassFilter.h \
    $$PWD/signal/Lag.h \
    $$PWD/signal/Lag2.h \
    $$PWD/signal/Lead.h \
    $$PWD/signal/LeadLag.h \
    $$PWD/signal/MovingAverageFilter.h \
    $$PWD/signal/MovingMedianFilter.h \
    $$PWD/signal/PID.h

SOURCES += \
    $$PWD/signal/Filter2.cpp \
    $$PWD/signal/HighPassFilter.cpp \
    $$PWD/signal/LowPassFilter.cpp \
    $$PWD/signal/Lag.cpp \
    $$PWD/signal/Lag2.cpp \
    $$PWD/signal/Lead.cpp \
    $$PWD/signal/LeadLag.cpp \
    $$PWD/signal/MovingAverageFilter.cpp \
    $$PWD/signal/MovingMedianFilter.cpp \
    $$PWD/signal/PID.cpp

################################################################################

HEADERS += \
    $$PWD/time/ClockTime.h \
    $$PWD/time/DateTime.h \
    $$PWD/time/ISO8601.h

SOURCES += \
    $$PWD/time/ISO8601.cpp

################################################################################

HEADERS += \
    $$PWD/xml/XmlDoc.h \
    $$PWD/xml/XmlNode.h

SOURCES += \
    $$PWD/xml/XmlDoc.cpp \
    $$PWD/xml/XmlNode.cpp
