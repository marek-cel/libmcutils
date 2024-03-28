set(TARGET_NAME astro)

################################################################################

set(HEADERS
    AzEl.h
    Ephemeris.h
    GregorianCal.h
    J2000.h
    JulianDate.h
)

set(SOURCES
    Ephemeris.cpp
    GregorianCal.cpp
    J2000.cpp
    JulianDate.cpp
)

################################################################################

add_library(${TARGET_NAME} OBJECT ${SOURCES})

################################################################################

include(GNUInstallDirs)

set_target_properties(${TARGET_NAME} PROPERTIES 
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/misc
)
