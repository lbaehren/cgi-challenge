/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

/*!
 * \file test_Interval.cc
 * \brief A collection of tests for the cgi::Interval class.
 */

/// Name of Boost test module
#define BOOST_TEST_MODULE test_Interval

#include <iostream>
#include <string>
#include <boost/test/unit_test.hpp>
#include <Interval.h>

//______________________________________________________________________________
//                                                              test_constructor

/// Test creation of object
int test_constructor ()
{
    int nofFailedTests (0);

    // === Test 1 : Default constructor ===

    try {
        cgi::Interval<int,std::string> inter_int_string = cgi::Interval<int,std::string>();
        std::cout << " Interval<int,string> : " << inter_int_string << std::endl;
    } catch (std::string message) {
        std::cerr << message << std::endl;
        ++nofFailedTests;
    }

    try {
        cgi::Interval<std::string,int> inter_string_int = cgi::Interval<std::string,int>();
        std::cout << " Interval<string,int> : " << inter_string_int << std::endl;
    } catch (std::string message) {
        std::cerr << message << std::endl;
        ++nofFailedTests;
    }

    try {
        cgi::Interval<std::string,double> inter_string_double = cgi::Interval<std::string,double>();
        std::cout << " Interval<string,double> : " << inter_string_double << std::endl;
    } catch (std::string message) {
        std::cerr << message << std::endl;
        ++nofFailedTests;
    }

    try {
        cgi::Interval<std::string,std::string> inter_string_string = cgi::Interval<std::string,std::string>();
        std::cout << " Interval<string,string> : " << inter_string_string << std::endl;
    } catch (std::string message) {
        std::cerr << message << std::endl;
        ++nofFailedTests;
    }

    return nofFailedTests;
}

/// Test argumented constructor for Interval<int,int>
BOOST_AUTO_TEST_CASE(interval_int_int)
{
    int begin (1);
    int end (2);
    int value (3);

    // default constructor
    cgi::Interval<int,int> interval1 = cgi::Interval<int,int>();
    BOOST_CHECK_EQUAL(interval1.begin(), 0);
    BOOST_CHECK_EQUAL(interval1.end(),   0);
    BOOST_CHECK_EQUAL(interval1.value(), 0);

    // argumented constructor
    cgi::Interval<int,int> interval2 (begin, end, value);

    BOOST_CHECK_EQUAL(interval2.begin(), begin);
    BOOST_CHECK_EQUAL(interval2.end(),   end);
    BOOST_CHECK_EQUAL(interval2.value(), value);
}

/// Test argumented constructor for Interval<int,double>
BOOST_AUTO_TEST_CASE(interval_int_double)
{
    int begin (1);
    int end (2);
    double value (0.123);

    // default constructor
    cgi::Interval<int,double> interval1 = cgi::Interval<int,double>();
    BOOST_CHECK_EQUAL(interval1.begin(), 0);
    BOOST_CHECK_EQUAL(interval1.end(),   0);
    BOOST_CHECK_EQUAL(interval1.value(), 0.0);

    // argumented constructor
    cgi::Interval<int,double> interval(begin, end, value);
    BOOST_CHECK_EQUAL(interval.begin(), begin);
    BOOST_CHECK_EQUAL(interval.end(),   end);
    BOOST_CHECK_EQUAL(interval.value(), value);
}

/// Test argumented constructor for Interval<int,std::string>
BOOST_AUTO_TEST_CASE(interval_int_string)
{
    int begin (1);
    int end (2);
    std::string value ("a");

    cgi::Interval<int,std::string> interval(begin, end, value);

    BOOST_CHECK_EQUAL(interval.begin(), begin);
    BOOST_CHECK_EQUAL(interval.end(), end);
    BOOST_CHECK_EQUAL(interval.value(), value);
}

/// Test argumented constructor for Interval<std::string,int>
BOOST_AUTO_TEST_CASE(interval_string_int)
{
    std::string begin = "13:00";
    std::string end   = "13:12";
    int value         = 1;

    cgi::Interval<std::string,int> interval(begin, end, value);

    BOOST_CHECK_EQUAL(interval.begin(), begin);
    BOOST_CHECK_EQUAL(interval.end(), end);
    BOOST_CHECK_EQUAL(interval.value(), value);
}

/// Test argumented constructor for Interval<std::string,double>
BOOST_AUTO_TEST_CASE(interval_string_double)
{
    std::string begin = "13:00";
    std::string end   = "13:12";
    double value      = 0.123;

    cgi::Interval<std::string,double> interval(begin, end, value);

    BOOST_CHECK_EQUAL(interval.begin(), begin);
    BOOST_CHECK_EQUAL(interval.end(), end);
    BOOST_CHECK_EQUAL(interval.value(), value);
}

//______________________________________________________________________________
//                                                               test_parameters

/// Test access to and manipulation of internal parameters
BOOST_AUTO_TEST_CASE(interval_param_value)
{
    int value_int            = 1;
    double value_double      = 0.123;
    std::string value_string = "Hello";

    // Interval<std::string,int>

    cgi::Interval<std::string,int> interval_int = cgi::Interval<std::string,int>();
    BOOST_CHECK_EQUAL(interval_int.value(), 0);

    interval_int.setValue(value_int);
    BOOST_CHECK_EQUAL(interval_int.value(), value_int);

    // Interval<std::string,double>

    cgi::Interval<std::string,double> interval = cgi::Interval<std::string,double>();

    BOOST_CHECK_EQUAL(interval.value(), 0.0);

    interval.setValue(value_double);
    BOOST_CHECK_EQUAL(interval.value(), value_double);

    // Interval<std::string,std::string>

    cgi::Interval<std::string,std::string> interval_string = cgi::Interval<std::string,std::string>();

    BOOST_CHECK_EQUAL(interval_string.value(), "");

    interval_string.setValue(value_string);
    BOOST_CHECK_EQUAL(interval_string.value(), value_string);
}
