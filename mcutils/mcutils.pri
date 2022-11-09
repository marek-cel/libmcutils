HEADERS += \
    $$PWD/defs.h \
    $$PWD/doxygen.h \
    $$PWD/Result.h \
    $$PWD/Types.h

################################################################################

HEADERS += \
    $$PWD/ctrl/ICtrlElement.h \
    $$PWD/ctrl/Gain.h \
    $$PWD/ctrl/HighPassFilter.h \
    $$PWD/ctrl/Inertia.h \
    $$PWD/ctrl/Inertia2.h \
    $$PWD/ctrl/Lead.h \
    $$PWD/ctrl/LeadLag.h \
    $$PWD/ctrl/LowPassFilter.h \
    $$PWD/ctrl/MovingAverage.h \
    $$PWD/ctrl/MovingMedian.h \
    $$PWD/ctrl/Oscillator.h \
    $$PWD/ctrl/PID.h \
    $$PWD/ctrl/StateSpace.h \
    $$PWD/ctrl/System2.h

SOURCES += \
    $$PWD/ctrl/Gain.cpp \
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
    $$PWD/datatree/DataRef.h \
    $$PWD/datatree/DataTree.h \
    $$PWD/datatree/GroupNode.h \
    $$PWD/datatree/Node.h \
    $$PWD/datatree/NodeType.h \
    $$PWD/datatree/ValueNode.h

SOURCES += \
    $$PWD/datatree/DataTree.cpp \
    $$PWD/datatree/GroupNode.cpp

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
    $$PWD/math/Matrix.h \
    $$PWD/math/Matrix3x3.h \
    $$PWD/math/Matrix4x4.h \
    $$PWD/math/Matrix6x6.h \
    $$PWD/math/MatrixSq.h \
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
