set(TARGET_NAME mcutils)

################################################################################

if(WIN32)
    if(BUILD_SHARED_LIBS)
        add_definitions(-DMCUTILS_DLL_EXPORTS)
    endif()
endif()

################################################################################

set(HEADERS
    defs.h
    Result.h
    Types.h
)

set(SOURCES
    units_utils.cpp
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

add_library(${TARGET_NAME} ${SOURCES}
    $<TARGET_OBJECTS:mcutils-astro>
    $<TARGET_OBJECTS:mcutils-ctrl>
    $<TARGET_OBJECTS:mcutils-geo>
    $<TARGET_OBJECTS:mcutils-math>
    $<TARGET_OBJECTS:mcutils-misc>
    $<TARGET_OBJECTS:mcutils-net>
    $<TARGET_OBJECTS:mcutils-time>
)

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

################################################################################

if(WIN32)
    set(LIBS ws2_32)
endif()

################################################################################

target_link_libraries(${TARGET_NAME} ${LIBS})

