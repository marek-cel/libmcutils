set(TARGET_NAME mcutils-math)

################################################################################

set(HEADERS
    Angles.h
    DegMinSec.h
    EulerRect.h
    GaussJordan.h
    Math.h
    Matrix.h
    Matrix3x3.h
    MatrixMxN.h
    MatrixNxN.h
    Quaternion.h
    Random.h
    RMatrix.h
    RungeKutta4.h
    SegPlaneIsect.h
    Table2.h
    Table.h
    UVector3.h
    Vector.h
    Vector3.h
    VectorN.h
)

################################################################################

add_library(${TARGET_NAME} INTERFACE)

################################################################################

include(GNUInstallDirs)

set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/math
)
