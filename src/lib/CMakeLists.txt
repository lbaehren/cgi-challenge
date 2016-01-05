#-------------------------------------------------------------------------------
# (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.
# This software is distributed under the BSD 2-clause license.
#-------------------------------------------------------------------------------


file (GLOB libcgi_sources *.h *.cc)

add_library (cgi ${libcgi_sources})

# Installation of library
install (
  TARGETS cgi
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  )

# Installation of header files
FILE (GLOB libcgi_headers *.h)

install (
    FILES ${libcgi_headers}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/cgi
)
