set( TARGET_NAME mcutils_signal )

################################################################################

set( HEADERS
    Filter2.h
    HighPassFilter.h
    ISignalElement.h
    Lag2.h
    Lag.h
    Lead.h
    LeadLag.h
    LowPassFilter.h
    MovingAverageFilter.h
    MovingMedianFilter.h
    PID.h
)

set( SOURCES
    Filter2.cpp
    HighPassFilter.cpp
    Lag2.cpp
    Lag.cpp
    Lead.cpp
    LeadLag.cpp
    LowPassFilter.cpp
    MovingAverageFilter.cpp
    MovingMedianFilter.cpp
    PID.cpp
)

################################################################################

add_library( ${TARGET_NAME} SHARED ${SOURCES} )

################################################################################

include( GNUInstallDirs )

set_target_properties( ${TARGET_NAME} PROPERTIES 
    VERSION ${MCUTIL_VERSION_STRING}
    SOVERSION ${MCUTIL_VERSION_MAJOR}
    PUBLIC_HEADER "${HEADERS}"
)

install( TARGETS ${TARGET_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/signal
)
