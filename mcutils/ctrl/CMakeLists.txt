set( TARGET_NAME ctrl )

################################################################################

set( HEADERS
    AntiWindupPID.h
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
    System2.h
)

set( SOURCES
    AntiWindupPID.cpp
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

add_library( ${TARGET_NAME} OBJECT ${SOURCES} )

################################################################################

include( GNUInstallDirs )

set_target_properties( ${TARGET_NAME} PROPERTIES 
    PUBLIC_HEADER "${HEADERS}"
)

install( TARGETS ${TARGET_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/ctrl
)
