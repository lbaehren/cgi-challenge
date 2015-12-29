#-------------------------------------------------------------------------------
# (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.
# This software is distributed under the BSD 2-clause license.
#-------------------------------------------------------------------------------

## =============================================================================
##
##  CMake project settings
##
## =============================================================================

## Name of the project handled by CMake
project (Visitors)

set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 1)
set (PROJECT_VERSION_PATCH 0)
set (PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## CMake policy (https://cmake.org/Wiki/CMake_Policies)
cmake_policy (VERSION 2.8)
cmake_policy (SET CMP0042 NEW)

## CMake standard modules
include (CheckIncludeFile)
include (CheckFunctionExists)
include (CheckTypeSize)
include (FindPackageHandleStandardArgs)

## =============================================================================
##
##  Comfiguration options
##
## =============================================================================

option (ENABLE_TESTING    "Enable the CTest test driver?"              YES )
option (BUILD_SHARED_LIBS "Enable building shared libraries?"          YES )

##__________________________________________________________
## Handle option: Enable the CTest test driver?

if (ENABLE_TESTING)
    include (CTest)
    enable_testing()
endif (ENABLE_TESTING)

##__________________________________________________________
## Installation prefix

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX
        "${PROJECT_SOURCE_DIR}/release" CACHE PATH "Installation location prefix" FORCE
    )
endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

## =============================================================================
##
##  System inspection
##
## =============================================================================

find_package (Doxygen)

# Enable usage of C++11 features
if (CMAKE_COMPILER_IS_GNUCXX)
    if (${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.7)
        set (CMAKE_CXX_FLAGS "-fPIC -std=c++0x")
    else ()
        set (CMAKE_CXX_FLAGS "-fPIC -std=c++11")
    endif ()
else (CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "C++ compiler is other than GNU")
    set (CMAKE_CXX_FLAGS "-std=c++11")
endif (CMAKE_COMPILER_IS_GNUCXX)

## =============================================================================
##
##  Projet sub-directories
##
## =============================================================================

add_subdirectory (src)

if (DOXYGEN_FOUND)
    add_subdirectory (doc)
endif (DOXYGEN_FOUND)

## =============================================================================
##
##  Configuration summary
##
## =============================================================================

message ( " --------------------------------------------------------"      )
message ( " [${PROJECT_NAME}] Configuration summary."                      )
message ( " --------------------------------------------------------"      )
message ( " * Project configuration"                                       )
message ( "  .. Project name ................ = ${PROJECT_NAME}"           )
message ( "  .. Project version ............. = ${PROJECT_VERSION}"        )
message ( "  .. Installation prefix ......... = ${CMAKE_INSTALL_PREFIX}"   )
message ( "  .. Build shared libraries ...... = ${BUILD_SHARED_LIBS}"      )
message ( " * System configuration"                                        )
message ( "  .. Processor type .............. = ${CMAKE_SYSTEM_PROCESSOR}" )
message ( "  .. CMake executable ............ = ${CMAKE_COMMAND}"          )
message ( "  .. CMake version ............... = ${CMAKE_VERSION}"          )
message ( "  .. System name ................. = ${CMAKE_SYSTEM_NAME}"      )
message ( "  .. System version .............. = ${CMAKE_SYSTEM_VERSION}"   )
message ( "  .. C++ compiler ................ = ${CMAKE_CXX_COMPILER}"     )
message ( "  .. C++ compiler flags .......... = ${CMAKE_CXX_FLAGS}"        )
message ( "  .. Memory checker .............. = ${MEMORYCHECK_COMMAND}"    )
message ( " --------------------------------------------------------"      )
