set( TARGET_NAME mcutils-geo )

################################################################################

set( HEADERS
    DataMars.h
    DataWGS84.h
    ECEF.h
    Geo.h
    Mercator.h
    WGS84.h
)

set( SOURCES
    ECEF.cpp
    Mercator.cpp
    WGS84.cpp
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
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/geo
)
