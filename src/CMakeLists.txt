#-------------------------------------------------------------------------------
# (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.
# This software is distributed under the BSD 2-clause license.
#-------------------------------------------------------------------------------

add_definitions (-Wc++11-extensions)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory (lib)
add_subdirectory (test)
add_subdirectory (app)
