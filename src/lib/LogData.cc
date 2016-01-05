/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

#include "LogData.h"

namespace cgi {

    // =========================================================================
    //
    //  Operator overloading
    //
    // =========================================================================

    std::ostream& operator<< (std::ostream &os, const LogData &rhs)
    {
        for (auto iter = rhs.itsData.begin(); iter != rhs.itsData.end(); ++iter) {
            os << *iter << "\n";
        }
        os << "Number of entries = " << rhs.itsData.size() << "\n";

        return os;
    }

    // =========================================================================
    //
    //  Public methods
    //
    // =========================================================================

    //__________________________________________________________________________
    //                                                                  readData

    void LogData::readData (const std::string& filename,
                            const bool& overwriteData)
    {
        if (overwriteData) {
            itsDataSources.push_back(filename);
            itsData.clear();
        }

        std::ifstream infile (filename);

        if (infile.is_open()) {
            std::string logline;
            while (std::getline(infile, logline)) {
                itsData.insert(cgi::LogEntry(logline));
            }
            // report number of lines read
            std::cout << "--> Finished reading " << itsData.size()
                      << " lines from file."
                      << std::endl;
        } else {
            std::cerr << "Error opening: " << filename << "\n";
        }
    }

    //__________________________________________________________________________
    //                                                              rangeOfTimes

    std::pair<DateTime,DateTime> LogData::rangeOfTimes ()
    {
        std::pair<DateTime,DateTime> result;

        result.first  = itsData.begin()->timeEntry();
        result.second = itsData.begin()->timeExit();

        // step through the log entries in order to determine maximum exit time
        for (auto it=itsData.begin(); it!=itsData.end(); ++it) {
            if (result.second < it->timeExit()) {
                result.second = it->timeExit();
            }
        }

        return result;
    }

    //__________________________________________________________________________
    //                                                            maxNofVisitors

    int LogData::maxNofVisitors () const
    {
        int visitors_max     = 0;
        int visitors_current = 0;
        std::multiset<TimePoint> set_tp;

        for (auto it=itsData.begin(); it!=itsData.end(); ++it) {
            set_tp.insert(cgi::TimePoint(it->timeEntry(),+1));
            set_tp.insert(cgi::TimePoint(it->timeExit(),-1));
        }

        for (auto it=set_tp.begin(); it!=set_tp.end(); ++it) {
            visitors_current += it->count();
            // keep track of the maximum
            if (visitors_current > visitors_max) {
                visitors_max = visitors_current;
            }
        }

        return visitors_max;
    }

    //__________________________________________________________________________
    //                                                      entranceTimepoints

    std::multimap<DateTime,int> LogData::entranceTimepoints () const
    {
        std::multimap<DateTime,int> timepoints;

        for (auto it=itsData.begin(); it!=itsData.end(); ++it) {
            timepoints.insert ( std::pair<DateTime,int>(it->timeEntry(),+1) );
            timepoints.insert ( std::pair<DateTime,int>(it->timeExit(),-1) );
        }

        return timepoints;
    }

}  //  namespace cgi -- END
