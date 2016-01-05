/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

/*!
 * \file test_LogEntry.cc
 * \brief A collection of tests for the cgi::LogEntry class.
 */

/// Name of Boost test module
#define BOOST_TEST_MODULE test_LogEntry

// #include <iostream>

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

#include <LogEntry.h>

//______________________________________________________________________________
//                                                              test_constructor

/// Test creation of object
BOOST_AUTO_TEST_CASE(LogEntry_constructor)
{
    std::string logfile_entry = "11:16,11:41";

    cgi::LogEntry logEntry (logfile_entry);

    BOOST_CHECK_EQUAL (logEntry.data(), logfile_entry);
}

//______________________________________________________________________________
//                                                               test_containers

/// Test overloading of operators
BOOST_AUTO_TEST_CASE(LogEntry_operators)
{
    std::string logfile_entry = "11:16,11:41";
    cgi::LogEntry logEntry (logfile_entry);

    std::cout << logEntry << std::endl;
}

//______________________________________________________________________________
//                                                               test_containers

/// Test collecting multiple instances of a LogEntry within a STL Container
BOOST_AUTO_TEST_CASE(LogEntry_containers)
{
    std::vector<std::string> logfile_entries;

    logfile_entries.push_back("13:00,13:05");
    logfile_entries.push_back("16:20,16:40");
    logfile_entries.push_back("09:37,09:46");
    logfile_entries.push_back("10:43,10:56");
    logfile_entries.push_back("13:29,13:47");
    logfile_entries.push_back("11:36,11:58");
    logfile_entries.push_back("12:29,12:42");
    logfile_entries.push_back("14:36,14:43");
    logfile_entries.push_back("15:47,16:00");
    logfile_entries.push_back("12:29,12:53");

    std::cout << " - Test std:::vector<T> ..." << std::endl;
    {
        std::vector<cgi::LogEntry> logEntries;

        // fill the vector
        for (auto it = logfile_entries.begin(); it!=logfile_entries.end(); ++it) {
            logEntries.push_back(cgi::LogEntry(*it));
        }

        // show contents of the vector
        for (auto it=logEntries.begin(); it!=logEntries.end(); ++it) {
            std::cout << " -> " << (*it).data()
                      << " => " << (*it).timeEntry()
                      << " - "  << (*it).timeExit()
                      << std::endl;
        }
    }

    std::cout << " - Test std:::set<T> ..." << std::endl;
    {
        std::set<cgi::LogEntry> logEntries;

        // fill the set
        for (auto it = logfile_entries.begin(); it!=logfile_entries.end(); ++it) {
            logEntries.insert(cgi::LogEntry(*it));
        }

        // show contents of the set
        for (auto it=logEntries.begin(); it!=logEntries.end(); ++it) {
            std::cout << " -> " << (*it).data()
                      << " => " << (*it).timeEntry()
                      << " - "  << (*it).timeExit()
                      << std::endl;
        }
    }
}
