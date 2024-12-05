set(TARGET_NAME mcutils-astro)

################################################################################

set(HEADERS
    Coordinates.h
    Ephemeris.h
    GregorianCal.h
    JulianDate.h
    Utils.h
)

set(SOURCES
    Utils.cpp
)

################################################################################

add_library(${TARGET_NAME} OBJECT ${SOURCES})

################################################################################

include(GNUInstallDirs)

set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/astro
)
