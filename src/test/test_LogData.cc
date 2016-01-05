/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

/*!
 * \file test_LogData.cc
 * \brief A collection of tests for the cgi::LogData class.
 */

/// Name of Boost test module
#define BOOST_TEST_MODULE test_LogData

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

#include <LogData.h>

//______________________________________________________________________________
//                                                           LogData_constructor

/// Test creation of object
BOOST_AUTO_TEST_CASE(LogData_constructor)
{
    cgi::LogData log = cgi::LogData();
}
