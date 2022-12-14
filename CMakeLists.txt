cmake_minimum_required( VERSION 2.8 )

project( mcutils )

set( MCUTILS_VERSION_MAJOR 0 )
set( MCUTILS_VERSION_MINOR 1 )
set( MCUTILS_VERSION_PATCH 0 )
set( MCUTILS_VERSION_STRING
    ${MCUTILS_VERSION_MAJOR}.${MCUTILS_VERSION_MINOR}.${MCUTILS_VERSION_PATCH}
)

################################################################################

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib )

################################################################################

# set( CMAKE_VERBOSE_MAKEFILE ON )

################################################################################

if( UNIX )
    if( CMAKE_SYSTEM_NAME STREQUAL "Linux" )
        add_definitions( -D_LINUX_ )
    endif()
elseif( WIN32 )
    add_definitions( -DWIN32 )
    add_definitions( -D_WINDOWS )
    add_definitions( -D_CRT_SECURE_NO_DEPRECATE )
    add_definitions( -D_SCL_SECURE_NO_WARNINGS )
    add_definitions( -D_USE_MATH_DEFINES )
endif()

################################################################################

if( UNIX )
    set( CMAKE_CXX_FLAGS_DEBUG   "-Wall -std=c++17" )
    set( CMAKE_CXX_FLAGS_RELEASE "-Wall -std=c++17 -O2" )
elseif( WIN32 )
    set( CMAKE_CXX_FLAGS_DEBUG   "-Wall -std=c++1z" )
    set( CMAKE_CXX_FLAGS_RELEASE "-Wall -std=c++1z -O2" )
    if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++17")
        endif()
    endif()
endif()

if( CMAKE_COMPILER_IS_GNUCC )
    set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -g" )
endif()

################################################################################

include_directories(
    ./
)

if( UNIX )
    include_directories( /usr/include/libxml2 )
elseif( WIN32 )
    include_directories( ${LIBXML_DIR}/include/ )
endif()

################################################################################

find_package( LibXml2 REQUIRED )

################################################################################

add_subdirectory( mcutils )

################################################################################
