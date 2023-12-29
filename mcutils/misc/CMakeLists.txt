set(TARGET_NAME misc)

################################################################################

set(HEADERS
    Check.h
    Log.h
    MapUtils.h
    Polymorphic.h
    Singleton.h
    String.h
    Units.h
)

set(SOURCES
    Log.cpp
    String.cpp
    Units.cpp
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
