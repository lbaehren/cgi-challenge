#-------------------------------------------------------------------------------
# (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.
# This software is distributed under the BSD 2-clause license.
#-------------------------------------------------------------------------------

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory (lib)
add_subdirectory (app)

if (ENABLE_TESTING AND Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE)
    add_subdirectory (test)
endif (ENABLE_TESTING AND Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE)
