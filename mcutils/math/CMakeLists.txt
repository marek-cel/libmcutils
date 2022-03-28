set( TARGET_NAME mcutils_math )

################################################################################

set( HEADERS
    Angles.h
    DegMinSec.h
    EulerRect.h
    GaussJordan.h
    Geometry.h
    IIntegrator.h
    Math.h
    Matrix3x3.h
    Matrix4x4.h
    Matrix6x6.h
    Matrix.h
    MatrixSquare.h
    Quaternion.h
    Random.h
    RungeKutta4.h
    Table2D.h
    Table.h
    Vector3.h
    Vector4.h
    Vector6.h
    Vector.h
    VectorN.h
)

set( SOURCES
    Angles.cpp
    DegMinSec.cpp
    EulerRect.cpp
    Geometry.cpp
    Matrix3x3.cpp
    Matrix4x4.cpp
    Matrix6x6.cpp
    Quaternion.cpp
    Random.cpp
    RungeKutta4.cpp
    Table2D.cpp
    Table.cpp
    Vector3.cpp
    Vector4.cpp
    Vector6.cpp
    VectorN.cpp
)

################################################################################

add_library( ${TARGET_NAME} SHARED ${SOURCES} )

################################################################################

include( GNUInstallDirs )

set_target_properties( ${TARGET_NAME} PROPERTIES 
    VERSION ${MCUTILS_VERSION_STRING}
    SOVERSION ${MCUTILS_VERSION_MAJOR}
    PUBLIC_HEADER "${HEADERS}"
)

install( TARGETS ${TARGET_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/math
)
