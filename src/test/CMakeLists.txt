#-------------------------------------------------------------------------------
# (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.
# This software is distributed under the BSD 2-clause license.
#-------------------------------------------------------------------------------

file (GLOB test_sources *.h *.cpp)

foreach (test_source ${test_sources})

    # get filename component
    get_filename_component (test_name ${test_source} NAME_WE)

    # compiler instructions
    add_executable (${test_name} ${test_source})

    # linker instructions
    target_link_libraries (${test_name} cgi)

    # testing
    if (ENABLE_TESTING)
        add_test (${test_name} ${test_name})
    endif (ENABLE_TESTING)

endforeach (test_source)
