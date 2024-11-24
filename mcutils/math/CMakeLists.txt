set(TARGET_NAME mcutils-math)

################################################################################

set(HEADERS
    Angles.h
    DegMinSec.h
    EulerRect.h
    GaussJordan.h
    Math.h
    Matrix.h
    Quaternion.h
    Random.h
    RotMatrix.h
    RungeKutta4.h
    SegPlaneIsect.h
    Table2.h
    Table.h
    Vector.h
)

set(SOURCES
    Angles.cpp
    DegMinSec.cpp
    Matrix.cpp
    Quaternion.cpp
    Random.cpp
    SegPlaneIsect.cpp
    Table2.cpp
    Table.cpp
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
