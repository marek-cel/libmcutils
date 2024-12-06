set(TARGET_NAME mcutils-time)

################################################################################

set(HEADERS
    ClockTime.h
    DateTime.h
    ISO8601.h
    Timer.h
)

################################################################################

add_library(${TARGET_NAME} INTERFACE)

################################################################################

include(GNUInstallDirs)

set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/time
)
