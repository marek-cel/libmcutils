set(TARGET_NAME mcutils)

################################################################################

set(HEADERS
    Result.h
)

################################################################################

add_subdirectory(astro)
add_subdirectory(ctrl)
add_subdirectory(geo)
add_subdirectory(math)
add_subdirectory(misc)
add_subdirectory(net)
add_subdirectory(physics)
add_subdirectory(time)

################################################################################

add_library(${TARGET_NAME} INTERFACE)

################################################################################

include(GNUInstallDirs)

set_target_properties(${TARGET_NAME} PROPERTIES
    VERSION ${MCUTILS_VERSION_STRING}
    SOVERSION ${MCUTILS_VERSION_MAJOR}
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils
)
