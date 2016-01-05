/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

#include "TimePoint.h"

namespace cgi {

    /// Overloading of output operator for cgi::DateTime class
    std::ostream& operator<< (std::ostream& os, const TimePoint& rhs)
    {
        os << "[" << rhs.itsTime << "] = " << rhs.itsCount;
        return os;
    }

}  //  namespace cgi -- END
