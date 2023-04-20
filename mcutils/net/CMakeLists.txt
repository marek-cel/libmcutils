set( TARGET_NAME net )

################################################################################

set( HEADERS
    Endianness.h
)

set( SOURCES
    Endianness.cpp
)

################################################################################

add_library( ${TARGET_NAME} OBJECT ${SOURCES} )

################################################################################

include( GNUInstallDirs )

set_target_properties( ${TARGET_NAME} PROPERTIES 
    VERSION ${MCUTILS_VERSION_STRING}
    SOVERSION ${MCUTILS_VERSION_MAJOR}
    PUBLIC_HEADER "${HEADERS}"
)

install( TARGETS ${TARGET_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/net
)
