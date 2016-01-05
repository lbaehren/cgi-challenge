/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

/*!
 * \file test_DateTime.cc
 * \brief A collection of tests for the cgi::DateTime class.
 */

/// Name of Boost test module
#define BOOST_TEST_MODULE test_DateTime

#include <set>
#include <vector>
#include <boost/test/unit_test.hpp>
#include <DateTime.h>

//______________________________________________________________________________
//                                                              test_constructor

/// Test creation of object
BOOST_AUTO_TEST_CASE(datetime_constructor)
{
    int year   = 2000;
    int month  = 1;
    int day    = 2;
    int hour   = 3;
    int minute = 4;
    int second = 5;

    cgi::DateTime dt = cgi::DateTime();

    cgi::DateTime dt2 = cgi::DateTime(year, month, day);
    BOOST_CHECK_EQUAL (dt2.year(),   year);
    BOOST_CHECK_EQUAL (dt2.month(),  month);
    BOOST_CHECK_EQUAL (dt2.day(),    day);
    BOOST_CHECK_EQUAL (dt2.hour(),   0);
    BOOST_CHECK_EQUAL (dt2.minute(), 0);
    BOOST_CHECK_EQUAL (dt2.second(), 0);

    cgi::DateTime dt3 = cgi::DateTime(year, month, day, hour);
    BOOST_CHECK_EQUAL (dt3.year(),   year);
    BOOST_CHECK_EQUAL (dt3.month(),  month);
    BOOST_CHECK_EQUAL (dt3.day(),    day);
    BOOST_CHECK_EQUAL (dt3.hour(),   hour);
    BOOST_CHECK_EQUAL (dt3.minute(), 0);
    BOOST_CHECK_EQUAL (dt3.second(), 0);

    cgi::DateTime dt4 = cgi::DateTime(year, month, day, hour, minute);
    BOOST_CHECK_EQUAL (dt4.year(),   year);
    BOOST_CHECK_EQUAL (dt4.month(),  month);
    BOOST_CHECK_EQUAL (dt4.day(),    day);
    BOOST_CHECK_EQUAL (dt4.hour(),   hour);
    BOOST_CHECK_EQUAL (dt4.minute(), minute);
    BOOST_CHECK_EQUAL (dt4.second(), 0);

    cgi::DateTime dt5 = cgi::DateTime(year, month, day, hour, minute, second);
    BOOST_CHECK_EQUAL (dt5.year(),   year);
    BOOST_CHECK_EQUAL (dt5.month(),  month);
    BOOST_CHECK_EQUAL (dt5.day(),    day);
    BOOST_CHECK_EQUAL (dt5.hour(),   hour);
    BOOST_CHECK_EQUAL (dt5.minute(), minute);
    BOOST_CHECK_EQUAL (dt5.second(), second);
}

//______________________________________________________________________________
//                                                datetime_constructor_from_char

/// Test creation of object from character representation
BOOST_AUTO_TEST_CASE(datetime_constructor_from_char)
{
    time_t rawtime;
    struct tm * tm_now;
    time ( &rawtime );
    tm_now = localtime ( &rawtime );

    std::string hm  = "01:02";
    std::string hms = "01:02:03";
    std::string ymd = "2015-01-02";
    std::string iso = "2015-01-02T03:04:05Z";

    cgi::DateTime dt1 = cgi::DateTime(hm, "%H:%M");
    BOOST_CHECK_EQUAL (dt1.year(),   tm_now->tm_year+1900);
    BOOST_CHECK_EQUAL (dt1.month(),  tm_now->tm_mon+1);
    BOOST_CHECK_EQUAL (dt1.day(),    tm_now->tm_mday);
    BOOST_CHECK_EQUAL (dt1.hour(),   1);
    BOOST_CHECK_EQUAL (dt1.minute(), 2);
    BOOST_CHECK_EQUAL (dt1.second(), 0);

    cgi::DateTime dt2 = cgi::DateTime(hms, "%H:%M:%S");
    BOOST_CHECK_EQUAL (dt2.year(),   tm_now->tm_year+1900);
    BOOST_CHECK_EQUAL (dt2.month(),  tm_now->tm_mon+1);
    BOOST_CHECK_EQUAL (dt2.day(),    tm_now->tm_mday);
    BOOST_CHECK_EQUAL (dt2.hour(),   1);
    BOOST_CHECK_EQUAL (dt2.minute(), 2);
    BOOST_CHECK_EQUAL (dt2.second(), 3);

    cgi::DateTime dt3 = cgi::DateTime(ymd, "%Y-%m-%d");
    BOOST_CHECK_EQUAL (dt3.year(),   2015);
    BOOST_CHECK_EQUAL (dt3.month(),  1);
    BOOST_CHECK_EQUAL (dt3.day(),    2);
    BOOST_CHECK_EQUAL (dt3.hour(),   0);
    BOOST_CHECK_EQUAL (dt3.minute(), 0);
    BOOST_CHECK_EQUAL (dt3.second(), 0);

    cgi::DateTime dt4 = cgi::DateTime(iso, "%Y-%m-%dT%H:%M:%SZ");
    BOOST_CHECK_EQUAL (dt4.year(),   2015);
    BOOST_CHECK_EQUAL (dt4.month(),  1);
    BOOST_CHECK_EQUAL (dt4.day(),    2);
    BOOST_CHECK_EQUAL (dt4.hour(),   3);
    BOOST_CHECK_EQUAL (dt4.minute(), 4);
    BOOST_CHECK_EQUAL (dt4.second(), 5);
}

//______________________________________________________________________________
//                                                                datetime_param

/// Test methods for access to internal parameters
BOOST_AUTO_TEST_CASE(datetime_param)
{
    int year   = 2000;
    int month  = 1;
    int day    = 2;
    int hour   = 3;
    int minute = 4;
    int second = 5;

    cgi::DateTime dt = cgi::DateTime(year, month, day, hour, minute, second);
    BOOST_CHECK_EQUAL (dt.year(),   year);
    BOOST_CHECK_EQUAL (dt.month(),  month);
    BOOST_CHECK_EQUAL (dt.day(),    day);
    BOOST_CHECK_EQUAL (dt.hour(),   hour);
    BOOST_CHECK_EQUAL (dt.minute(), minute);
    BOOST_CHECK_EQUAL (dt.second(), second);

    // adjust year and re-check
    year = 2001;
    dt.setYear(year);
    BOOST_CHECK_EQUAL (dt.year(),   year);
    BOOST_CHECK_EQUAL (dt.month(),  month);
    BOOST_CHECK_EQUAL (dt.day(),    day);
    BOOST_CHECK_EQUAL (dt.hour(),   hour);
    BOOST_CHECK_EQUAL (dt.minute(), minute);
    BOOST_CHECK_EQUAL (dt.second(), second);

    // adjust month and re-check
    month = 6;
    dt.setMonth(month);
    BOOST_CHECK_EQUAL (dt.year(),   year);
    BOOST_CHECK_EQUAL (dt.month(),  month);
    BOOST_CHECK_EQUAL (dt.day(),    day);
    BOOST_CHECK_EQUAL (dt.hour(),   hour);
    BOOST_CHECK_EQUAL (dt.minute(), minute);
    BOOST_CHECK_EQUAL (dt.second(), second);

    // adjust month and re-check
    day = 7;
    dt.setDay(day);
    BOOST_CHECK_EQUAL (dt.year(),   year);
    BOOST_CHECK_EQUAL (dt.month(),  month);
    BOOST_CHECK_EQUAL (dt.day(),    day);
    BOOST_CHECK_EQUAL (dt.hour(),   hour);
    BOOST_CHECK_EQUAL (dt.minute(), minute);
    BOOST_CHECK_EQUAL (dt.second(), second);
}

//______________________________________________________________________________
//                                                           datetime_op_compare

/// Test comparison (smaller than, larger than) of objects
BOOST_AUTO_TEST_CASE(datetime_op_compare)
{
    std::vector<int> year {1999, 2000, 2001};
    int month   = 1;
    int day     = 2;
    int hour    = 3;
    int minute  = 4;
    int second  = 5;

    cgi::DateTime dt1 = cgi::DateTime(year[0], month, day, hour, minute, second);
    cgi::DateTime dt2 = cgi::DateTime(year[1], month, day, hour, minute, second);
    cgi::DateTime dt3 = cgi::DateTime(year[2], month, day, hour, minute, second);

    BOOST_CHECK_EQUAL (dt1.year(), year[0]);
    BOOST_CHECK_EQUAL (dt2.year(), year[1]);
    BOOST_CHECK_EQUAL (dt3.year(), year[2]);

    BOOST_CHECK_EQUAL (dt1.month(), month);
    BOOST_CHECK_EQUAL (dt2.month(), month);
    BOOST_CHECK_EQUAL (dt3.month(), month);

    BOOST_CHECK ( dt1 < dt2 );
    BOOST_CHECK ( dt2 < dt3 );

    BOOST_CHECK ( dt2 > dt1 );
    BOOST_CHECK ( dt3 > dt2 );

    BOOST_CHECK_EQUAL ( dt1==dt1, true );
    BOOST_CHECK_EQUAL ( dt2==dt2, true );
    BOOST_CHECK_EQUAL ( dt3==dt3, true );

}

//______________________________________________________________________________
//                                                            datetime_as_string

/// Test creation of object
BOOST_AUTO_TEST_CASE(datetime_as_string)
{
    int year   = 2000;
    int month  = 1;
    int day    = 2;
    int hour   = 3;
    int minute = 4;
    int second = 5;

    cgi::DateTime dt = cgi::DateTime(year, month, day, hour, minute, second);

    BOOST_CHECK_EQUAL (dt.asString("%Y"), std::string("2000"));
    BOOST_CHECK_EQUAL (dt.asString("%m"), std::string("01"));
    BOOST_CHECK_EQUAL (dt.asString("%d"), std::string("02"));
    BOOST_CHECK_EQUAL (dt.asString("%H"), std::string("03"));
    BOOST_CHECK_EQUAL (dt.asString("%M"), std::string("04"));

    BOOST_CHECK_EQUAL (dt.asString("%Y-%m-%d"), std::string("2000-01-02"));
    BOOST_CHECK_EQUAL (dt.asString("%Y-%b-%d"), std::string("2000-Jan-02"));
    BOOST_CHECK_EQUAL (dt.asString("%Y-%B-%d"), std::string("2000-January-02"));
    BOOST_CHECK_EQUAL (dt.asString("%H:%M:%S"), std::string("03:04:05"));

}

//______________________________________________________________________________
//                                                              test_constructor

/// Parse character input as a date/time value according to format string
BOOST_AUTO_TEST_CASE(datetime_get_time)
{
    std::string hm  = "01:02";
    std::string hms = "01:02:03";
    std::string ymd = "2015-01-02";
    std::string iso = "2015-01-02T03:04:05Z";

    std::tm tm_hm  = cgi::DateTime::getTime(hm,  "%H:%M");
    std::tm tm_hms = cgi::DateTime::getTime(hms, "%H:%M:%S");
    std::tm tm_ymd = cgi::DateTime::getTime(ymd, "%Y-%m-%d");
}

//______________________________________________________________________________
//                                                               test_containers

/// Test storing object within STL containers
BOOST_AUTO_TEST_CASE(test_containers)
{
    std::vector<int> year {1999, 2000, 2001};
    int month   = 1;
    int day     = 2;
    int hour    = 3;
    int minute  = 4;
    int second  = 5;

    cgi::DateTime dt1 = cgi::DateTime(year[0], month, day, hour, minute, second);
    cgi::DateTime dt2 = cgi::DateTime(year[1], month, day, hour, minute, second);
    cgi::DateTime dt3 = cgi::DateTime(year[2], month, day, hour, minute, second);

    std::set<cgi::DateTime> dt_set;
    dt_set.insert(dt1);
    dt_set.insert(dt2);
    dt_set.insert(dt3);

    BOOST_CHECK ( dt_set.size() == 3 );
}
