set(TARGET_NAME mcutils-ctrl)

################################################################################

set(HEADERS
    HighPassFilter.h
    Inertia.h
    Inertia2.h
    Lead.h
    LeadLag.h
    LowPassFilter.h
    MovingAverage.h
    MovingMedian.h
    Oscillator.h
    PID.h
    PID_BackCalc.h
    PID_CondCalc.h
    PID_FilterAW.h
    System2.h
    ZeroOrderHold.h
)

################################################################################

add_library(${TARGET_NAME} INTERFACE)

################################################################################

include(GNUInstallDirs)

set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/ctrl
)
