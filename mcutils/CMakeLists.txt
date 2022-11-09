set( TARGET_NAME mcutils )

################################################################################

set( HEADERS
    defs.h
    Result.h
    Types.h
)

################################################################################

add_library( ${TARGET_NAME} INTERFACE )

################################################################################

include( GNUInstallDirs )

set_target_properties( ${TARGET_NAME} PROPERTIES 
    PUBLIC_HEADER "${HEADERS}"
)

install( TARGETS ${TARGET_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils
)

################################################################################

add_subdirectory( ctrl )
add_subdirectory( datatree )
add_subdirectory( geo )
add_subdirectory( math )
add_subdirectory( misc )
add_subdirectory( net )
add_subdirectory( physics )
add_subdirectory( time )
add_subdirectory( xml )
