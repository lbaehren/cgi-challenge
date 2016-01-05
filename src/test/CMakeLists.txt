#-------------------------------------------------------------------------------
# (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.
# This software is distributed under the BSD 2-clause license.
#-------------------------------------------------------------------------------

file (GLOB test_sources *.cc)

include_directories (${Boost_INCLUDE_DIRS})
add_definitions (-DBOOST_TEST_DYN_LINK)

foreach (test_source ${test_sources})

    # get filename component
    get_filename_component (test_name ${test_source} NAME_WE)

    # compiler instructions
    add_executable (${test_name} ${test_source})

    # linker instructions
    target_link_libraries (${test_name} cgi ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE})

    # set up target to actually run the test
    add_test (${test_name} ${test_name} --log_level=message)

endforeach (test_source)
