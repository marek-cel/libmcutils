set( TARGET_NAME mcutils-misc )

################################################################################

set( HEADERS
    Check.h
    Log.h
    Map.h
    Singleton.h
    String.h
    Units.h
)

set( SOURCES
    Log.cpp
    String.cpp
    Units.cpp
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
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/misc
)
