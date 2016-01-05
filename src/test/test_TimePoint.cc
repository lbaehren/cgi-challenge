/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

/*!
 * \file test_TimePoint.cc
 * \brief A collection of tests for the cgi::TimePoint class.
 */

/// Name of Boost test module
#define BOOST_TEST_MODULE test_TimePoint

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

#include <DateTime.h>
#include <TimePoint.h>

//______________________________________________________________________________
//                                                         TimePoint_constructor

/// Test creation of object
BOOST_AUTO_TEST_CASE (TimePoint_constructor)
{
    int count          = 2;
    std::string iso    = "2015-01-02T03:04:05Z";
    std::string format = "%Y-%m-%dT%H:%M:%SZ";
    cgi::DateTime dt   = cgi::DateTime(iso, format);

    cgi::TimePoint tp1 = cgi::TimePoint();
    BOOST_CHECK_EQUAL (tp1.count(), 0);

    cgi::TimePoint tp2 = cgi::TimePoint(dt);
    BOOST_CHECK_EQUAL (tp2.time(), dt);
    BOOST_CHECK_EQUAL (tp2.count(), 0);

    cgi::TimePoint tp3 = cgi::TimePoint(dt, count);
    BOOST_CHECK_EQUAL (tp3.time(), dt);
    BOOST_CHECK_EQUAL (tp3.count(), count);
}

//______________________________________________________________________________
//                                                          TimePoint_op_compare

/// Test overloading of comparison operator(s)
BOOST_AUTO_TEST_CASE (TimePoint_op_compare)
{
    int count         = 2;
    cgi::DateTime dt1 = cgi::DateTime("2015-01-02T03:04:05Z", "%Y-%m-%dT%H:%M:%SZ");
    cgi::DateTime dt2 = cgi::DateTime("2015-01-02T03:04:06Z", "%Y-%m-%dT%H:%M:%SZ");

    cgi::TimePoint tp1 = cgi::TimePoint(dt1);
    cgi::TimePoint tp2 = cgi::TimePoint(dt2);
    cgi::TimePoint tp3 = cgi::TimePoint(dt2, count);

    BOOST_CHECK (tp1 < tp2);
    BOOST_CHECK (tp1 < tp3);
    BOOST_CHECK (tp2 < tp3);  /*  Difference in count only */

    BOOST_CHECK (tp2 > tp1);
    BOOST_CHECK (tp3 > tp1);
    BOOST_CHECK (tp3 > tp2);  /*  Difference in count only */
}

//______________________________________________________________________________
//                                                            TimePoint_op_count

/// Test overloading of increment/decrement operator
BOOST_AUTO_TEST_CASE (TimePoint_op_count)
{
    cgi::DateTime dt = cgi::DateTime("2015-01-02T03:04:05Z", "%Y-%m-%dT%H:%M:%SZ");

    cgi::TimePoint tp = cgi::TimePoint(dt);
    BOOST_CHECK_EQUAL (tp.count(), 0);

    ++tp;
    BOOST_CHECK_EQUAL (tp.count(), 1);

    ++tp;
    BOOST_CHECK_EQUAL (tp.count(), 2);

    --tp;
    BOOST_CHECK_EQUAL (tp.count(), 1);
}
