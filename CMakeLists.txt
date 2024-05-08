cmake_minimum_required(VERSION 3.22)

################################################################################

project(mcutils)

set(MCUTILS_VERSION_MAJOR 1)
set(MCUTILS_VERSION_MINOR 0)
set(MCUTILS_VERSION_PATCH 0)
set(MCUTILS_VERSION_STRING
    ${MCUTILS_VERSION_MAJOR}.${MCUTILS_VERSION_MINOR}.${MCUTILS_VERSION_PATCH}
)

################################################################################

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

################################################################################

include(CTest)
include(GoogleTest)

enable_testing()

################################################################################

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

################################################################################

if(UNIX)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        add_definitions(-D_LINUX_)
    endif()
elseif(WIN32)
    add_definitions(-DWIN32)
    add_definitions(-D_WINDOWS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_USE_MATH_DEFINES)
endif()

if (BUILD_TESTING)
    add_definitions(-D_GTEST_)
    add_definitions(-D_TESTS_)
endif()

################################################################################

if(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -std=c++17")
    if (BUILD_TESTING)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fno-default-inline -fno-inline -fno-inline-small-functions -fprofile-arcs -ftest-coverage -pedantic")
        set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
        set(CMAKE_CXX_FLAGS_RELEASE "-O0")
    else()
        set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
        set(CMAKE_CXX_FLAGS_RELEASE "-O2")
    endif()
elseif(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG   "-Wall -std=c++1z")
    set(CMAKE_CXX_FLAGS_RELEASE "-Wall -std=c++1z -O2")
    if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++17")
        endif()
    endif()
endif()

################################################################################

if(WIN32)
    find_library(WS2_32_LIBRARY ws2_32 REQUIRED)
endif()

################################################################################

include_directories(.)

################################################################################

add_subdirectory(mcutils)

################################################################################

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
