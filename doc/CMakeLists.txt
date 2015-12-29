#-------------------------------------------------------------------------------
# (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.
# This software is distributed under the BSD 2-clause license.
#-------------------------------------------------------------------------------

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf.in
  ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf
)

add_custom_target (doc
    COMMAND ${DOXYGEN_EXECUTABLE} doxygen.conf
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running Doxygen to generate source code documentation"
)
