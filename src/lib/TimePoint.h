/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

/*!
 * \file TimePoint.h
 * \brief Class for the container to the storage of log data.
 */

#ifndef CGI_TIMEPOINT_H
#define CGI_TIMEPOINT_H

#include <set>
#include <string>
#include "DateTime.h"

namespace cgi {

    /*!
     * \class TimePoint
     * \brief Point in time with associated counter
     * \test test_TimePoint.cc
     *
     * \note The current implementation still very much is based on the
     *       requirements for solving the original problem, where a TimePoint is
     *       used for recording the event of a visitor entering (``count=1``) or
     *       leaving (``count=-1``). As indicated by the overloading of the
     *       incement and decrement operators simultaneous events -- such as e.g.
     *       multiple visitors entering/leaving at the same point in time -- can
     *       be accounted for. With this in mind the current implementation could
     *       be extended (and probably renamed) to the more generalized notion of
     *       an event with the type of event encoded through an ``Event::Type``.
     */
    class TimePoint {

        /// Date/Time for the event
        cgi::DateTime itsTime;
        /// Counter associated with the point in time
        int itsCount;

    public:

        // === Construction ====================================================

        /// Default constructor
        TimePoint () : itsCount(0) {
            itsTime  = cgi::DateTime();
        }

        /// Argumented constructor
        TimePoint (const cgi::DateTime& time,
                   const int& count=0) : itsCount(count) {
            itsTime  = time;
        }

        // === Operator overloading ============================================

        /// Check if this is smaller than other
        bool operator< (const TimePoint& rhs) const {
            if (itsTime < rhs.itsTime) {
                return true;
            } else {
                if (itsTime == rhs.itsTime) {
                    return itsCount < rhs.itsCount;
                } else {
                    return false;
                }
            }
        }

        /// Check if this is larger than other
        bool operator> (const TimePoint& rhs) const {
            if (itsTime > rhs.itsTime) {
                return true;
            } else {
                if (itsTime == rhs.itsTime) {
                    return itsCount > rhs.itsCount;
                } else {
                    return false;
                }
            }
        }

        /// Overloading of increment operator, ++TimePoint
        TimePoint & operator++ () {
            ++itsCount;
            return *this;
        }

        /// Overloading of increment operator, TimePoint++
        TimePoint operator++ (int) {
            TimePoint result = *this ;
            ++itsCount;
            return result;
        }

        /// Overloading of decrement operator, --TimePoint
        TimePoint & operator-- () {
            itsCount -= 1;
            return *this;
        }

        /// Overloading of decrement operator, TimePoint--
        TimePoint operator-- (int) {
            TimePoint result = *this ;
            --itsCount;
            return result;
        }

        /// Overloading of output stream operator
        friend std::ostream& operator<< (std::ostream& os, const TimePoint& rhs);

        // === Parameter access ================================================

        /// Get date/time for the event
        inline cgi::DateTime time () const {
            return itsTime;
        }

        /// Get the count for the time point
        inline int count () const {
            return itsCount;
        }

        /*!
         * \brief Set the count for the time point
         * \param count -- New value of the `count` parameter
         */
        void setCount (const int& count) {
            itsCount = count;
        }

    };  //  class TimePoint -- END

}  //  namespace cgi -- END

#endif
