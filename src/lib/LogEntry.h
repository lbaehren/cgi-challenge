/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

#ifndef CGI_LOGENTRY_H
#define CGI_LOGENTRY_H

/*!
 * \file LogEntry.h
 * \brief Class for the container to the data of a single log file entry.
 */

#include <iostream>
#include <string>
#include "DateTime.h"

namespace cgi {

    /*!
     * \class LogEntry
     * \brief Container to the data of a single log file entry.
     * \test test_LogEntry.cc
     *
     * \note At this point in time we are keeping a copy of the log entry data
     * in its original format, allowing for verification of the dissected pieces
     * of information against the source material. This choice leads to a memory
     * footprint larger than necessary (especially for a production system); hence
     * in future versions keeping around of the original data should be dropped
     * in favour of catching possible parsing errors via dedicated tests.
     */
    class LogEntry {

        /// Data of a single log file entry in its original format.
        std::string itsData;
        /// Time of entry
        DateTime itsTimeEntry;
        /// Time of exit
        DateTime itsTimeExit;

    public:

        // === Construction ====================================================

        /// Argumented constructor
        LogEntry (const std::string& data) {
            setData(data);
        }

        // === Operator overloading ============================================

        /*!
         * \brief Check if log entry is considered smaller than _rhs_
         * \param rhs -- Other LogEntry object to compare this to; comparison
         *        is done based on the time of entry.
         */
        bool operator< (const LogEntry& rhs) const {
            return (itsTimeEntry) < rhs.itsTimeEntry;
        }

        /*!
         * \brief Check if log entry is considered larger than _rhs_
         * \param rhs -- Other LogEntry object to compare this to; comparison
         *        is done based on the time of entry.
         */
        bool operator> (const LogEntry& rhs) const {
            return (itsTimeEntry) > rhs.itsTimeEntry;
        }

        /*!
         * \brief Check of log entry is considered equal to _rhs_
         * \param rhs -- Other LogEntry object to compare this to; comparison
         *        is done based on the original data of the log entry.
         */
        bool operator== (const LogEntry &rhs) const {
            return itsData == rhs.data();
        }

        /// Overloading of output stream operator
        friend std::ostream& operator<< (std::ostream& os, const LogEntry& rhs);

        // === Parameter access ================================================

        /// Get data of the logfile entry
        inline std::string data () const {
            return itsData;
        }

        /*!
         * \brief Set data of the logfile entry
         * \param data   -- Data of a single log file entry in its original format.
         * \param format -- Format according to which the individual times in
         *        `data` will be parsed as a date/time value.
         */
        void setData (const std::string& data,
                      const std::string& format="%H:%M");

        /// Get the time of entry
        inline DateTime timeEntry () const {
            return itsTimeEntry;
        }

        /// Get the time of exit
        inline DateTime timeExit () const {
            return itsTimeExit;
        }

    };  //  class LogEntry -- END

}  //  namespace cgi -- END

#endif
