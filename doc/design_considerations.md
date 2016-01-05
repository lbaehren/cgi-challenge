Design considerations    {#design_considerations}
=====================

_Contents:_

 1. General considerations
 2. Development tools
 3. Library design
 4. Processing of visitor logs


## General considerations

 - Keep the architecture general enough to allow extension beyond the presented
   scenario.

 - Keep functionality encoded as part of the application executable minimal -
   place algorithms inside library for reuse across multiple applications.

 - Avoid re-inventing the wheel by coding everything from scratch; where suitable
   use well-established -- i.e. proven, tested, documented -- libraries, such as
   e.g. Boost or GSL.

 - Library classes should integrate make use of and integrate well with the C++
   STL and the containers defined therein.

\note All the considerations taken and decisions made should be taken with the
necessary grain of salt: as opposed to a real development environment no intercation
and discussion with product stakeholders and co-developers could be conducted in
order to guide the process. As a result of this some of the extrapolations from the
original problem description are likely to point into a different direction than
envisioned by the authors of the programming challenge.

\note Given the nature as a "one-off" project the balance between building up the
infrastructure -- for configuration, testing, documentation, etc. -- w.r.t. to the
actual coding has considerably been to the disadvantage of the latter. For the work
on an actual production system (of larger scope both in size and usage duration)
the front-up investments are expected to pay off after a short while -- for the
challenge alone we are barely breaking even.


## Development tools

 - Git (http://git-scm.com) is a free and open source distributed version control
   system designed to handle everything from small to very large projects with
   speed and efficiency.

 - CMake (https://cmake.org) is an extensible, open-source system that manages
   the build process in an operating system and in a compiler-independent manner.
   Unlike many cross-platform systems, CMake is designed to be used in conjunction
   with the native build environment.

 - CTest is a testing tool distributed as a part of CMake. It can be used to
   automate updating (using CVS for example), configuring, building, testing,
   performing memory checking, performing coverage, and submitting results to a
   CDash or Dart dashboard system.


## Library design

 - **Representation of log entries**

   In the case of the initial scenario visitor entry logs are available as a simple
   text file with two single pieces of information only (time of entry, time of exit).
   In order to allow for some forseeable extensions,

   - other types in input source, e.g. database, binary data,
   - recording of date (for processing log from multiple days),
   - recording of higher-resolution time,
   - ticket number/type,
   - visitor ID (e.g. in the case of subscription tickets with reductions, etc.),
   - joint gate system for staff members and visitors,

   internal representation and handling of the log data should be flexible enough
   to accommodate a larger set of configurations and use cases. An individual log
   entry is encapsulated through the cgi::LogEntry class while the interfacing
   with data source is implemented as part of cgi::LogData.

 - **Representation of times**

   While the example log-file originally provided records time as HH:MM (in a string
   representation), it is rather foreseeable that this information would be presented
   in another format -- such as

   - higher time resolution, e.g. (sub-)second precision,
   - inclusing of calendar date, e.g. for logs covering multiple days.

   In order to allow future expansing while abstrating away from the original input
   format a class cgi::DateTime is used.

 - **Representation of time intervals**

   Time and time again the problem deals with the concept of a time interval; hence
   as a forwards investment the class cgi::Interval implements the basic concept
   of a (time-)interval with properties associated. The class has been implemented
   with template parameters for both the interval limiters as well the associated
   value; this way we will be able to accomodate time-intervals, distance-intervals,
   etc.


## Processing of visitor logs

The problem stated in the programming challenge can be found in various variants,
e.g.

> A company currently pays a fixed sum for the use of a particular licensed
> software package. In determining if it has a good deal it decides to calculate
> its maximum use of the software from its license management log file.
> ...
> Save the 10,000 line log file from here into a local file then write a program
> to scan the file extracting both the maximum licenses that were out at any time,
> and the time(s) at which this occurs.
>
> Source: http://rosettacode.org/wiki/Max_Licenses_In_Use

No matter the problem specifics, the general approach is pretty much the same:

 1. Provide data in a form where events (entries and exits) are available as an
    ordered list.
 2. Go through the list while keeping track of the number of the current visitors;
    if the current number of visitors is equal or larger than the maximum, store
    the associated timestamp/interval/etc.

Based on possible changes to the format of the provided input data -- e.g. information
to enable tracking individuals (which also would allow to check for the number
of unique visitors) different approaches could be considered for the first of the
above two points. At moment log entries internally are stored order by time of
entry -- using ``std::set<cgi::LogEntry>`` -- such that for the full list of events
at least one half no longer needs to be sorted.

Particular care needs to be taken of the fact that a timestamp might not be associated
with a single event (which in part might be due to the time resolution with which
the visitor log are being recorded): at the same time-marker multi vsitors might
enter and/or leave, meaning that a simple (key,value) store for building up the
master event list will not suffice. The choice was made to use ``std::multimap<K,T>``
from C++ STL; which this multiple events for the same point in time can be
recorded and flagged according to type (``value=+1`` for an entry, ``value=-1``
for an exit).

### Future extensions

Calculation of the maximum number of users (for a single day) obviously is only
a first type of information which can be used to characterize the data:

 - average/mean/median number of visitors
 - fit of suitable parameterized function to time-series of visitors
 - pattern analysis across days of the week, months of year, etc.
 - return/display number of visitors per time interval
   - ... between entry and exit times of individual visitors
   - ... within a given time interval
   - ... for a user-selected time interval length
