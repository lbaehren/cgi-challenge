/*----------------------------------------------------------------------------*/
/* (c) Lars Baehren <lbaehren@gmail.com> (2015). All Rights Reserved.         */
/* This software is distributed under the BSD 2-clause license.               */
/*----------------------------------------------------------------------------*/

/*!
 * \file process_logs.cc
 * \brief Program executable for the processing of the visitor logs
 *
 * This program present the user interface (not to be confused with the library
 * API) for processing of the data.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <getopt.h>

#include <LogData.h>
#include <TimePoint.h>
#include <Interval.h>

//______________________________________________________________________________
//                                                                    show_usage

/*!
 * \brief Show help with usage instructions
 * \param name -- Name of/path to the programm executable.
 *
 * At this point in time support for reading command line options is minimal; a
 * fully fledged application would either be using [getopt](http://linux.die.net/man/3/getopt)
 * of the [Boost Program Options](http://www.boost.org/doc/libs/release/libs/program_options/)
 * library.
 */
void show_usage (std::string name)
{
    std::cerr << std::endl;
    std::cerr << "Usage: " <<std::endl;
    std::cerr << "\t" << name << " [options] <path-to-logfile>" << std::endl;
    std::cerr << std::endl;
    std::cerr << "Options:" << std::endl;
    std::cerr << "\t-H,--help\t= Print usage information and exit." << std::endl;
    std::cerr << std::endl;
}

//______________________________________________________________________________
//                                                               show_statistics

/*!
 * \brief Show visitor statistics, i.e. nof. visitors per time interval
 * \param visitorsPerTime -- Array of time-points, storing the number of visitor
 *                           at a given point in time.
 * \param visitorsMax     -- Array of intervals, storing the time-intervals during
 *                           which there was the maximum number of visitors (keep
 *                           in mind that we might have multiple maxima).
 * \param timeformat      -- Format specification for the time information.
 */
void show_statistics (const std::vector<cgi::TimePoint>& visitorsPerTime,
                      const std::vector<cgi::Interval<cgi::DateTime,int> > visitorsMax,
                      const std::string& timeformat="%H:%M")
{
    /* ------------------------------------------------------------ */
    /*  Output 1 : Number of visitors per time interval             */

    std::cout << "\n Visitors per time interval:" << std::endl;

    for (auto it = visitorsPerTime.begin(), next=visitorsPerTime.begin()+1;
         it!=visitorsPerTime.end()-1;
         ++it, ++next) {
        std::cout << "\t" << it->time().asString(timeformat)
                  << "-"  << next->time().asString(timeformat)
                  << ";"  << it->count()
                  << std::endl;
    }

    /* ------------------------------------------------------------ */
    /*  Output 2 : maximum number of visitors and corresponding     */
    /*             time interval(s)                                 */

    std::cout << "\n Maximum number of visitors:" << std::endl;

    for (auto n: visitorsMax) {
        std::cout << n.begin().asString("%H:%M")
                  << " ... "
                  << n.end().asString("%H:%M")
                  << "  =>  "
                  << n.value()
                  << std::endl;
    }

}

//______________________________________________________________________________
//                                                                  process_logs

/*!
 * \brief Process visitor log to extra statistics
 * \param data -- Set (i.e. ordered list) of log entries to process.
 */
void process_logs (const cgi::LogData& data)
{
    auto map_tp = data.entranceTimepoints ();
    int count   = 0;
    std::vector<cgi::TimePoint> result;

    /* Sum up events (entries vs. exists) per point in time. */
    for (auto it = map_tp.begin();
         it != map_tp.end();
         it=map_tp.upper_bound(it->first))
    {
        for (auto iter = map_tp.lower_bound(it->first);
             iter != map_tp.upper_bound(it->first);
             ++iter)
        {
            count += iter->second;
        }
        result.push_back(cgi::TimePoint(it->first, count));
        count = 0;
    }

    /* Determine max nof. visitors and visitors per time interval. */
    std::vector<cgi::Interval<cgi::DateTime,int> > max;
	int current_vistors = 0;
    int visitors_max    = data.maxNofVisitors();
    auto it_begin       = result.begin();
    auto it_end         = result.begin();

    for (auto it=result.begin(); it!=result.end(); ++it) {
        current_vistors += it->count();
        it->setCount(current_vistors);
        // keep track of the maximum
        if (current_vistors == visitors_max) {
            it_end       = it;
            it_begin     = it_end++;
            max.push_back(cgi::Interval<cgi::DateTime,int>(it_begin->time(),
                                                           it_end->time(),
                                                           current_vistors));
        }
    }

    /* Show visitor statistics */
    show_statistics (result, max);
}

//______________________________________________________________________________
//                                                                          main

/// Program main function
int main (int argc, char *argv[])
{
    // Check for command line arguments
    if (argc < 2) {
        show_usage(argv[0]);
        return 1;
    }

    // Read data from input file
    cgi::LogData logdata = cgi::LogData(argv[1]);

    std::pair<cgi::DateTime,cgi::DateTime> time_range = logdata.rangeOfTimes();

    std::cout << "--> Range of times = "
              << time_range.first << " ... " << time_range.second
              << std::endl;

    process_logs(logdata);

    return 0;
}
