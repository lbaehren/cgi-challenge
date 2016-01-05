#-------------------------------------------------------------------------------
# (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.
# This software is distributed under the BSD 2-clause license.
#-------------------------------------------------------------------------------

file (GLOB app_sources *.cc)

foreach (app_source ${app_sources})

    # get filename component
    get_filename_component (app_name ${app_source} NAME_WE)

    # compiler instructions
    add_executable (${app_name} ${app_source})

    # linker instructions
    target_link_libraries (${app_name} cgi)

    # installation instructions
    install (
      TARGETS ${app_name}
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
      LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
      ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
      )

endforeach (app_source)

# testing
if (ENABLE_TESTING)
    set (testdata ${PROJECT_SOURCE_DIR}/testdata)
    add_test (process_logs_case1 process_logs ${testdata}/testdata-case1.txt)
    add_test (process_logs_case2 process_logs ${testdata}/testdata-case2.txt)
    add_test (process_logs_case3 process_logs ${testdata}/testdata-case3.txt)
    add_test (process_logs_case4 process_logs ${testdata}/testdata-case4.txt)
    add_test (process_logs_case5 process_logs ${testdata}/testdata-case5.txt)
    add_test (process_logs process_logs ${testdata}/visitingtimes.txt)
endif (ENABLE_TESTING)
