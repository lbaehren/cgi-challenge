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
project (cgi-challenge CXX)

set (PROJECT_VERSION_MAJOR 1)
set (PROJECT_VERSION_MINOR 0)
set (PROJECT_VERSION_PATCH 0)
set (PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## CMake policy (https://cmake.org/Wiki/CMake_Policies)
cmake_policy (VERSION 2.8)

if (POLICY CMP0042)
    cmake_policy (SET CMP0042 NEW)
endif (POLICY CMP0042)

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

option (BUILD_SHARED_LIBS "Enable building shared libraries?"  ON  )
option (ENABLE_TESTING    "Enable the CTest test driver?"      ON  )
option (ENABLE_PACKAGING  "Enable the CPack packaging tool?"   OFF )

##__________________________________________________________
##  Handle option: Enable the CTest test driver?

if (ENABLE_TESTING)
    include (CTest)
    enable_testing()
endif (ENABLE_TESTING)

##__________________________________________________________
##  Handle option: Enable the CPack packaging tool?

if (ENABLE_PACKAGING)
    # Package configuration settings
    set (CPACK_PACKAGE_VENDOR  "Lars Baehren")
    set (CPACK_PACKAGE_CONTACT "lbaehren@gmail.com")
    set (CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.md")
    set (CPACK_PACKAGE_VERSION_MAJOR    "${PROJECT_VERSION_MAJOR}")
    set (CPACK_PACKAGE_VERSION_MINOR    "${PROJECT_VERSION_MINOR}")
    set (CPACK_PACKAGE_VERSION_PATCH    "${PROJECT_VERSION_PATCH}")
    set (CPACK_SOURCE_IGNORE_FILES      "${CMAKE_CURRENT_BINARY_DIR}")
    # Include module
    include (CPack)
endif (ENABLE_PACKAGING)

## =============================================================================
##
##  System inspection
##
## =============================================================================

##____________________________________________________________________
##  Boost C++ libraries                                 [unit testing]

set (Boost_USE_MULTITHREADED TRUE)

find_package (Boost 1.45.0 COMPONENTS program_options unit_test_framework)

##____________________________________________________________________
##  Doxygen                                 [documentation generation]

find_package (Doxygen)

##____________________________________________________________________
##  Enable usage of C++11 features                          [compiler]

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
message ( "  .. Enable test driver .......... = ${ENABLE_TESTING}"         )
message ( "  .. Enable packaging tool ....... = ${ENABLE_PACKAGING}"       )
message ( " * System configuration"                                        )
message ( "  .. Processor type .............. = ${CMAKE_SYSTEM_PROCESSOR}" )
message ( "  .. System name ................. = ${CMAKE_SYSTEM_NAME}"      )
message ( "  .. System version .............. = ${CMAKE_SYSTEM_VERSION}"   )
message ( "  .. C++ compiler ................ = ${CMAKE_CXX_COMPILER}"     )
message ( "  .. C++ compiler flags .......... = ${CMAKE_CXX_FLAGS}"        )
message ( "  .. Memory checker .............. = ${MEMORYCHECK_COMMAND}"    )
message ( "  .. CMake executable ............ = ${CMAKE_COMMAND}"          )
message ( "  .. CMake version ............... = ${CMAKE_VERSION}"          )
message ( " * Dependencies"                                                )
message ( "  .. Have Doxygen ................ = ${DOXYGEN_FOUND}"          )
message ( "  .. Have Boost .................. = ${Boost_FOUND}"            )
message ( "     - Boost version ............. = ${Boost_VERSION}"          )
message ( "     - Include directories ....... = ${Boost_INCLUDE_DIRS}"     )
message ( "     - Link directories .......... = ${Boost_LIBRARY_DIRS}"     )
message ( " --------------------------------------------------------"      )
