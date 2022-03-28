set( TARGET_NAME mcutils_time )

################################################################################

set( HEADERS
    ClockTime.h
    DateTime.h
    ISO8601.h
)

set( SOURCES
    ISO8601.cpp
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
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/time
)
