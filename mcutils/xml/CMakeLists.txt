set( TARGET_NAME mcutils_xml )

################################################################################

set( HEADERS
    XmlDoc.h
    XmlNode.h
)

set( SOURCES
    XmlDoc.cpp
    XmlNode.cpp
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
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/xml
)
