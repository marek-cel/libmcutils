set( TARGET_NAME geo )

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

add_library( ${TARGET_NAME} OBJECT ${SOURCES} )

################################################################################

include( GNUInstallDirs )

set_target_properties( ${TARGET_NAME} PROPERTIES 
    PUBLIC_HEADER "${HEADERS}"
)

install( TARGETS ${TARGET_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/geo
)
