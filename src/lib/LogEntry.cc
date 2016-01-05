/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

#include "LogEntry.h"

namespace cgi {

    // =========================================================================
    //
    //  Operator overloading
    //
    // =========================================================================

    std::ostream& operator<< (std::ostream& os, const LogEntry& rhs)
    {
        std::string format    = "%Y-%m-%dT%H:%M:%SZ";
        std::string timeEntry = rhs.timeEntry().asString(format);
        std::string timeExit  = rhs.timeExit().asString(format);
        os << rhs.data() << " -> " << timeEntry << " - " << timeExit;

        return os;
    }

    // =========================================================================
    //
    //  Public methods
    //
    // =========================================================================

    //__________________________________________________________________________
    //                                                                   setData

    void LogEntry::setData (const std::string &data,
                            const std::string& format)
    {
        if (data[data.size()-1] == '\r') {
            itsData = data.substr( 0, data.size() - 1 );
        } else {
            itsData = data;
        }

        std::size_t pos = itsData.find(",");
        std::string substringEntry = itsData.substr(0, pos);
        std::string substringExit  = itsData.substr(pos+1, itsData.size()-1);

        itsTimeEntry = cgi::DateTime (substringEntry, format);
        itsTimeExit  = cgi::DateTime (substringExit,  format);
    }

}  //  namespace cgi -- END
