set(TARGET_NAME mcutils-geo)

################################################################################

set(HEADERS
    ECEF.h
    Ellipsoid.h
    Geo.h
    Mars2015.h
    Mercator.h
    WGS84.h
)

################################################################################

add_library(${TARGET_NAME} INTERFACE)

################################################################################

include(GNUInstallDirs)

set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/geo
)
