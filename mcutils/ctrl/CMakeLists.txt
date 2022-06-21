set( TARGET_NAME mcutils-ctrl )

################################################################################

set( HEADERS
    BandPassFilter.h
    BandStopFilter.h
    HighPassFilter.h
    IControlElement.h
    Lag2.h
    Lag.h
    Lead.h
    LeadLag.h
    LowPassFilter.h
    MovingAverageFilter.h
    MovingMedianFilter.h
    Oscillator.h
    PID.h
    StateSpace.h
    System2.h
)

set( SOURCES
    HighPassFilter.cpp
    Lag2.cpp
    Lag.cpp
    Lead.cpp
    LeadLag.cpp
    LowPassFilter.cpp
    MovingAverageFilter.cpp
    MovingMedianFilter.cpp
    Oscillator.cpp
    PID.cpp
    System2.cpp
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
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/ctrl
)
