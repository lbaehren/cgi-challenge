#-------------------------------------------------------------------------------
# (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.
# This software is distributed under the BSD 2-clause license.
#-------------------------------------------------------------------------------


file (GLOB libcgi_sources *.h *.cpp)

add_library (cgi ${libcgi_sources})
