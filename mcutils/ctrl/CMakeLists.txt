set( TARGET_NAME mcutils-ctrl )

################################################################################

set( HEADERS
    ICtrlElement.h
    Gain.h
    HighPassFilter.h
    Inertia.h
    Inertia2.h
    Lead.h
    LeadLag.h
    LowPassFilter.h
    MovingAverage.h
    MovingMedian.h
    Oscillator.h
    PID.h
    StateSpace.h
    System2.h
)

set( SOURCES
    Gain.cpp
    HighPassFilter.cpp
    Inertia.cpp
    Inertia2.cpp
    Lead.cpp
    LeadLag.cpp
    LowPassFilter.cpp
    MovingAverage.cpp
    MovingMedian.cpp
    Oscillator.cpp
    PID.cpp
    System2.cpp
)

################################################################################

add_library( ${TARGET_NAME} ${SOURCES} )

################################################################################

include( GNUInstallDirs )

set_target_properties( ${TARGET_NAME} PROPERTIES 
    VERSION ${MCUTILS_VERSION_STRING}
    SOVERSION ${MCUTILS_VERSION_MAJOR}
    PUBLIC_HEADER "${HEADERS}"
)

install( TARGETS ${TARGET_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/ctrl
)
