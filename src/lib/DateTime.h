/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

#ifndef CGI_DATETIME_H
#define CGI_DATETIME_H

/*!
 * \file DateTime.h
 * \brief Class for the representation of date and time
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <string>
#include <chrono>

namespace cgi {

    /*!
     * \class DateTime
     * \brief Class for the representation of date and time
     *
     * The C++ standard library -- even with the C++11 addition of ``std::chrono`` --
     * does not provide a proper date type. C++ inherits the structs and functions
     * for date and time manipulation from C. To access date and time related
     * functions and structures, we build the subsequent functionality on top of
     * the data structures and routines provided through `<ctime>`.
     *
     * \note Due to the fact that the implementation is based on the data
     *       structures and routines provided through ``<ctime>`` dates earlier
     *       than 1900-01-01T00:00:00Z are out of reach. By the same token simple
     *       operations, such as "add 1 year to current date", are not supported -
     *       this would require a more intricate implementation on top of the
     *       C++ ``std::chrono`` library.
     *
     * \test test_DateTime.cc
     */
    class DateTime
    {
        /// Arithmetic type capable of representing times.
        std::time_t itsRawtime;

    public:

        // === Construction ====================================================

        /// Default constructor
        DateTime () {
            itsRawtime = time(NULL);
        }

        /// Argumented constructor
        DateTime (const std::chrono::system_clock::time_point& tp) {
            itsRawtime = std::chrono::system_clock::to_time_t(tp);
        }

        /// Argumented constructor
        DateTime (const time_t& rawtime) {
            itsRawtime = rawtime;
        }

        /*!
         * \brief Argumented constructor
         * \param year   -- year
         * \param month  -- month of the year – [1, 12]
         * \param day    -- day of the month – [1, 31]
         * \param hour   -- hours since midnight – [0, 23]
         * \param minute -- minutes after the hour – [0, 59]
         * \param second -- seconds after the minute – [0, 60]
         */
        DateTime (const int& year,
                  const int& month,
                  const int& day,
                  const int& hour=0,
                  const int& minute=0,
                  const int& second=0);

        /*!
         * \brief Argumented constructor
         * \param in     -- Character representation of date/time value.
         * \param format -- string specifying the conversion format.
         *
         * The character input ``in`` is parsed as a date/time value according to
         * the ``format`` string. If the information provided with ``in`` is
         * incomplete, e.g. for the case where only the time of day is given
         * (``HH:MM``),  we auto-complete using the current date.
         */
        DateTime (const std::string& in,
                  const std::string& format);

        // === Operator overloading ============================================

        /// Check if this is smaller than other
        bool operator< (const DateTime& rhs) const {
            return (itsRawtime) < rhs.itsRawtime;
        }

        /// Check if this is larger than other
        bool operator> (const DateTime& rhs) const {
            return (itsRawtime) > rhs.itsRawtime;
        }

        /// Comparison Operator
        bool operator== (const DateTime& rhs) const {
            return (itsRawtime) == rhs.itsRawtime;
        }

        /// Overloading of output stream operator
        friend std::ostream& operator<< (std::ostream& os, const DateTime& rhs);

        // === Parameter access ================================================

        /// Get internally used storage format for date and time
        inline std::time_t rawtime () const {
            return itsRawtime;
        }

        /// Get date and time as `time_point` object
        inline std::chrono::system_clock::time_point asTimePoint () const {
            return std::chrono::system_clock::from_time_t(itsRawtime);
        }

        /// Get year
        inline int year () const {
            struct tm *tminfo = std::localtime(&itsRawtime);
            return (tminfo->tm_year + 1900);
        }
        /// Get year as string
        inline std::string yearAsString () const {
            return asString("%Y");
        }
        /// Set year
        void setYear (const int& year);

        /// Get month of year (1 .. 12)
        inline int month () const {
            struct tm *tminfo = std::localtime(&itsRawtime);
            return (tminfo->tm_mon + 1);
        }
        /// Get month of year (1 .. 12) - as string
        inline std::string monthAsString () const {
            return asString("%m");
        }
        /// Set month of the year – [1, 12]
        void setMonth (const int& month);

        /// Get day of the month – [1, 31]
        inline int day () const {
            struct tm *tminfo = std::localtime(&itsRawtime);
            return tminfo->tm_mday;
        }
        /// Get day of the month – [1, 31] - as string
        inline std::string dayAsString () const {
            return asString("%d");
        }
        /// Set day of the month – [1, 31]
        void setDay (const int& day);

        /// Get hours since midnight – [0, 23]
        int hour () const {
            struct tm *tminfo = std::localtime(&itsRawtime);
            return tminfo->tm_hour;
        }
        /// Get hours since midnight – [0, 23] - as string
        inline std::string hourAsString () const {
            return asString("%H");
        }
        /// Set hours since midnight – [0, 23]
        void setHour (const int& hour);

        /// Get minutes after the hour – [0, 59]
        int minute () const {
            struct tm *tminfo = std::localtime(&itsRawtime);
            return tminfo->tm_min;
        }
        /// Get minutes after the hour – [0, 59] - as string
        inline std::string minuteAsString () {
            return asString("%M");
        }
        /// Set minutes after the hour – [0, 59]
        void setMinute (const int& minute);

        /// Get second of minute (0 .. 59 and 60 for leap seconds)
        int second () const {
            struct tm *tminfo = std::localtime(&itsRawtime);
            return tminfo->tm_sec;
        }
        /// Set second of minute (0 .. 59 and 60 for leap seconds)
        void setSecond (const int& second);

        /// Get date and time as formatted string
        std::string asString (const std::string& format="") const;

        // === Public static methods ===========================================

        /*!
         * brief Parse character input as a date/time value according to format string
         * \param in     -- Character representation of date/time value.
         * \param format -- Format according to which ``in`` will be parsed as a
         *        date/time value.
         */
        static std::tm getTime (const std::string& in,
                                const std::string& format);

    };  //  class DateTime -- END

}  //  namespace cgi -- END

#endif
