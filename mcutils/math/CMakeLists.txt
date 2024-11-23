set(TARGET_NAME mcutils-math)

################################################################################

set(HEADERS
    Angles.h
    DegMinSec.h
    EulerRect.h
    GaussJordan.h
    Math.h
    Matrix3x3.h
    Matrix4x4.h
    Matrix6x6.h
    MatrixMxN.h
    MatrixNxN.h
    Quaternion.h
    Random.h
    RotMatrix.h
    RungeKutta4.h
    SegPlaneIsect.h
    Table2.h
    Table.h
    Vector.h
    Vector3.h
    Vector4.h
    Vector6.h
    VectorN.h
)

set(SOURCES
    Angles.cpp
    DegMinSec.cpp
    Matrix3x3.cpp
    Matrix4x4.cpp
    Matrix6x6.cpp
    Quaternion.cpp
    Random.cpp
    RotMatrix.cpp
    SegPlaneIsect.cpp
    Table2.cpp
    Table.cpp
    Vector.cpp
    Vector3.cpp
    Vector4.cpp
    Vector6.cpp
)

################################################################################

add_library(${TARGET_NAME} OBJECT ${SOURCES})

################################################################################

include(GNUInstallDirs)

set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/math
)
