/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/
/*!
 * \file LogData.h
 * \brief Class for the container to the storage of log data.
 */

#ifndef CGI_LOGDATA_H
#define CGI_LOGDATA_H

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "LogEntry.h"
#include "TimePoint.h"

namespace cgi {

    /*!
     * \class LogData
     * \brief Container to the storage of log data.
     * \test test_LogData.cc
     */
    class LogData {

        /// Name of the input file from which the log data are read
        std::vector<std::string> itsDataSources;
        /// (Sorted) Log data read from the input file
        std::set<LogEntry> itsData;

    public:

        // === Construction ====================================================

        /// Default constructor
        LogData () {
            itsDataSources.clear();
            itsData.clear();
        }

        /// Argumented constructor
        LogData (const std::string& filename) {
            readData(filename, true);
        }

        // === Operator overloading ============================================

        /// Overloading of output stream operator
        friend std::ostream& operator<< (std::ostream& os, const LogData& rhs);

        // === Parameter access ================================================

        /// Get the name(s) of the input source(s) for the log data
        inline std::vector<std::string> dataSources () const {
            return itsDataSources;
        }

        /// Get a copy of the internally stored data
        inline std::set<LogEntry> data () const {
            return itsData;
        }

        /*!
         * \brief Read data from input source
         * \param filename -- Name of the input file from which the log data are
         *        read
         * \param overwriteData -- Overwrite the internally stored log data.
         */
        void readData (const std::string& filename,
                       const bool& overwriteData=true);

        // === Public methods ==================================================

        /// Get range of times (min,max) covered by the log entry data
        std::pair<DateTime,DateTime> rangeOfTimes ();

        /// Get the number of visitors
        int maxNofVisitors () const;

        /*!
         * \brief Get map with ordered values of entrance events
         *
         * Depending of the type of event (visitor entering/leaving) the counter
         * for the Timepoint is set to the corresponding value:
         * \li entrance event with visitor entering : weight = +1
         * \li entrance event with visitor leaving : weight = -1
         */
        std::multimap<DateTime,int> entranceTimepoints () const;

    };  //  class LogData -- END

}  //  namespace cgi -- END

#endif
