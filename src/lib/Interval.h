/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

#ifndef CGI_INTERVAL_H
#define CGI_INTERVAL_H

/*!
 * \file Interval.h
 * \brief Class for the representing an interval and its properties
 */

#include <iostream>
#include <string>

namespace cgi {

    /*!
     * \class Interval
     * \brief Class for the representing an interval and its properties
     * \test test_Interval.cc
     */
    template <typename K, typename T>
    class Interval {

        /// Begin of the interval
        K itsBegin;
        /// End of the interval
        K itsEnd;
        /// Value associated with the interval
        T itsValue;

    public:

        // === Construction ====================================================

        /// Default constructor
        Interval () : itsBegin(K()),
                      itsEnd(K()),
                      itsValue(T()) {}

        /*!
         * \brief Argumented constructor
         * \param begin -- Begin of the interval.
         * \param end   -- End of the interval.
         * \param value -- Value associated with the interval.
         */
        Interval (const K& begin,
                  const K& end,
                  const T& value=T()) : itsBegin(begin),
                                        itsEnd(end),
                                        itsValue(value) {}

        // === Parameter access ================================================

        /// Get the begin of the interval
        inline K begin() const {
            return itsBegin;
        }
        /// Get the end of the interval
        inline K end() const {
            return itsEnd;
        }
        /// Get the value associated with the interval
        inline T value() const {
            return itsValue;
        }
        /// Set the begin of the interval
        inline void setBegin (const K& begin) {
            itsBegin = begin;
        }
        /// Set the end of the interval
        inline void setEnd (const K& end) {
            itsEnd = end;
        }
        /// Set the value associated with the interval
        inline void setValue (const T& value) {
            itsValue = value;
        }

    };  //  class Interval -- END

}  //  namespace cgi -- END

/// Overloading of output operator for cgi::Interval class
template <typename K, typename T>
inline std::ostream& operator<<(std::ostream& os, const cgi::Interval<K,T>& obj)
{
    os << "[ " << obj.begin() << " .. " << obj.end() << " ] -> '" << obj.value() << "'";

    return os;
}

#endif
