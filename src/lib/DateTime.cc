/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

#include "DateTime.h"

namespace cgi {

    // =========================================================================
    //
    //  Construction
    //
    // =========================================================================

    //__________________________________________________________________________
    //                                                                  DateTime

    DateTime::DateTime (const int& year,
                        const int& month,
                        const int& day,
                        const int& hour,
                        const int& minute,
                        const int& second)
    {
        std::tm t;
        t.tm_sec   = second;    // second of minute (0 .. 59 and 60 for leap seconds)
        t.tm_min   = minute;    // minute of hour (0 .. 59)
        t.tm_hour  = hour;      // hour of day (0 .. 23)
        t.tm_mday  = day;       // day of month (0 .. 31)
        t.tm_mon   = month-1;   // month of year (0 .. 11)
        t.tm_year  = year-1900; // year since 1900
        t.tm_isdst = -1;        // determine whether daylight saving time

        std::time_t tt = std::mktime(&t);
        if (tt == -1) {
            throw "ERROR [DateTime::DateTime] No valid system time";
        }
        itsRawtime = tt;
    }

    //__________________________________________________________________________
    //                                                                  DateTime

    DateTime::DateTime (const std::string& in,
                        const std::string& format)
    {
        // Initialize the structure into which the parsed input will be written
        struct std::tm tm = getTime(in, format);

        std::time_t tt = std::mktime(&tm);
        if (tt == -1) {
            throw "ERROR [DateTime::DateTime] No valid system time";
        }
        itsRawtime = tt;

    }

    // =========================================================================
    //
    //  Operator overloading
    //
    // =========================================================================

    /// Overloading of output operator for cgi::DateTime class
    std::ostream& operator<< (std::ostream& os, const DateTime& rhs)
    {
        os << rhs.asString("%Y-%m-%dT%H:%M:%SZ");
        return os;
    }

    // =========================================================================
    //
    //  Parameter access
    //
    // =========================================================================

    //__________________________________________________________________________
    //                                                                   setYear

    void DateTime::setYear (const int& year)
    {
        struct tm *tminfo = std::localtime(&itsRawtime);
        tminfo->tm_year   = year-1900;
        tminfo->tm_isdst  = 0;

        std::time_t tt = std::mktime(tminfo);
        if (tt == -1) {
            throw "ERROR [DateTime::setYear] No valid system time";
        }
        itsRawtime = tt;
    }

    //__________________________________________________________________________
    //                                                                  setMonth

    void DateTime::setMonth (const int& month)
    {
        struct tm *tminfo = std::localtime(&itsRawtime);
        tminfo->tm_mon    = month-1;
        tminfo->tm_isdst  = -1;

        std::time_t tt = std::mktime(tminfo);
        if (tt == -1) {
            throw "ERROR [DateTime::setMonth] No valid system time";
        }
        itsRawtime = tt;
    }

    //__________________________________________________________________________
    //                                                                    setDay

    void DateTime::setDay (const int& day)
    {
        struct tm *tminfo = std::localtime(&itsRawtime);
        tminfo->tm_mday   = day;
        tminfo->tm_isdst  = -1;

        std::time_t tt = std::mktime(tminfo);
        if (tt == -1) {
            throw "ERROR [DateTime::setDay] No valid system time";
        }
        itsRawtime = tt;
    }

    //__________________________________________________________________________
    //                                                                   setHour

    void DateTime::setHour (const int& hour)
    {
        struct tm *tminfo = std::localtime(&itsRawtime);
        tminfo->tm_hour   = hour;
        tminfo->tm_isdst  = -1;

        std::time_t tt = std::mktime(tminfo);
        if (tt == -1) {
            throw "ERROR [DateTime::setHour] No valid system time";
        }
        itsRawtime = tt;
    }

    //__________________________________________________________________________
    //                                                                 setMinute

    void DateTime::setMinute (const int& minute)
    {
        struct tm *tminfo = std::localtime(&itsRawtime);
        tminfo->tm_min    = minute;
        tminfo->tm_isdst  = -1;

        std::time_t tt = std::mktime(tminfo);
        if (tt == -1) {
            throw "ERROR [DateTime::setMinute] No valid system time";
        }
        itsRawtime = tt;
    }

    //__________________________________________________________________________
    //                                                                 setSecond

    void DateTime::setSecond (const int& second)
    {
        struct tm *tminfo = std::localtime(&itsRawtime);
        tminfo->tm_sec    = second;
        tminfo->tm_isdst  = -1;

        std::time_t tt = std::mktime(tminfo);
        if (tt == -1) {
            throw "ERROR [DateTime::setSecond] No valid system time";
        }
        itsRawtime = tt;
    }

    //__________________________________________________________________________
    //                                                                  asString

    std::string DateTime::asString (const std::string& format) const
    {
        std::string result;

        if (format.empty()) {
            // convert to calendar time:
            result = std::ctime(&itsRawtime);
            // skip trailing newline
            result.resize(result.size()-1);
        } else {
            char buffer[100];
            if (std::strftime(buffer, sizeof(buffer), format.c_str(), std::localtime(&itsRawtime))) {
                result = std::string(buffer);
            } else {
                return asString("");
            }
        }

        return result;
    }


    //__________________________________________________________________________
    //                                                                   getTime

    std::tm DateTime::getTime (const std::string& in,
                               const std::string& format)
    {
        // Get current date/time in order to fill in missing information
        time_t rawtime;
        struct tm * tm_now;
        time ( &rawtime );
        tm_now = localtime ( &rawtime );

        // Initialize the structure into which the parsed input will be written
        struct std::tm tm = *tm_now;
        tm.tm_hour = 0;
        tm.tm_min  = 0;
        tm.tm_sec  = 0;

        // parse input character representation of date/time ...
        strptime (in.c_str(), format.c_str(), &tm);
        // ... and inspect the outcome
        if ( (tm.tm_year==0) && (tm.tm_mon==0) && (tm.tm_mday==0) ) {
            tm.tm_year = tm_now->tm_year;
            tm.tm_mon  = tm_now->tm_mon;
            tm.tm_mday = tm_now->tm_mday;
        }

        return tm;
    }

}
