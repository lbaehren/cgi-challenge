CGI programming challenge
=========================

_Contents:_

 1. Dependencies
 2. Organization of files and directories
 3. Configuration, Build & Installation
 4. Documentation
 5. Testing


## Dependencies

| Name           | Version  | Relevance | Notes                                             |
|----------------|----------|-----------|---------------------------------------------------|
| C++11 compiler |          | mandatory | http://en.cppreference.com/w/cpp/compiler_support |
| CMake          | >= 2.8.3 | mandatory | Cross-platform build system generator.            |
| Boost          | >= 1.46  | optional  | Libraries used: program_options, test.       |
| Doxyen         | > 1.7.x  | optional  | Documentation generator.                          |

 - Resolution on Debian GNU/Linux

       apt-get install g++
       apt-get install cmake
       apt-get install libboost-test-dev libboost-program-options-dev
       apt-get install doxygen

 - Resolution on Fedora

       dnf install gcc-c++
       dnf install cmake
       dnf install boost-devel
       dnf install doxygen

 - Resolution on Mac OS X (using MacPorts)

       sudo port install clang-<version>
       sudo port install cmake
       sudo port install boost
       sudo port install doxygen


## Organization of files and directories

After checking out a working copy (using Git) or unpacking the source archive,
you will be left with the following directory structure:

    .
    |-- CMakeLists.txt  ...  Top-level CMake configuration script.
    |-- README.md       ...  This readme file.
    |-- doc             ...  (Extended) documentation for the project
    |-- src
    |   ├-- app         ...  Directory with application program source code.
    |   ├-- lib         ...  Directory with library source code.
    |   `-- test        ...  Directory with test programs.
    `-- testdata        ...  Directory with test data.


## Configuration, Build & Installation

The software uses the CMake (www.cmake.org) cross-platform makefile generator in
order to configure for building library, tools and test programs.

It is advised to perform an out-of-source build, in order to prevent polluting
the source directories:

    mkdir build
    cd build
    cmake [OPTIONS] ..

Available configuration options are:

| Configuration option             | Default    | Description                      |
|----------------------------------|------------|----------------------------------|
| -D CMAKE_INSTALL_PREFIX=<prefix> | /usr/local | Installation location.           |
| -D BUILD_SHARED_LIBS=<bool>      | ON         | Build shared libraries.          |
| -D ENABLE_TESTING=<bool>         | ON         | Enable the CTest test driver.    |
| -D ENABLE_PACKAGING=<bool>       | OFF        | Enable the CPack packaging tool. |

If the configuration completed succesfully, in order to build all available
components simply type (the optional `-j` option is for parallel builds):

    make [-j]

In order to get an overview of the available build targets type:

    make help

Once the build has completed you can install the software: to do this run

    make install

such that header files, libraries, program executables and documentation will be
placed into the appropriate locations.


## Documentation

Source code documentation and extended documentation are generated via Doxygen.

    make doc

The resulting HTML pages will be located in ``doc/html``, so point you web-browser
to ``./build/doc/html/index.html``.

The extended documentation is kept in plain text files using Markdown syntax,

    .
    `-- doc
        |-- challenge_description.md   ...  Project descriptions and requirements
        |-- design_considerations.md   ...  Design/Implementation considerations
        `-- testdata.md                ...  Datasets for algorithm testing

such that contents is human readable and can be read without previous processing
with Doxygen (though automatic integration with source code documentation will
not be available in that case).


## Testing

Once the software has been built the tests can be run (from the build directory) by

    make test

Individual tests can be run via

    ctest [--verbose] -R <test-name>

The software routinely is build and tested on the following platforms:

    Mac OS X, Darwin 13.4.0    x86_64    Apple LLVM version 5.0 (clang-500.2.79)
    Fedora 23, 4.2.8-300       x86_64    g++ (GCC) 5.3.1 20151207 (Red Hat 5.3.1-2)
    Debian 9.x, 4.3.0-1        amd64     g++ (Debian 5.3.1-4) 5.3.1 20151219
    Debian 9.x, 4.3.0-1        i386      g++ (Debian 5.3.1-4) 5.3.1 20151219
    Debian 8.x  3.16.0-4       amd64     g++ (Debian 4.9.2-10) 4.9.2
    Debian 8.x  3.16.0-4       i686      g++ (Debian 4.9.2-10) 4.9.2
    Debian 7.x  3.2.0-4        amd64     g++ (Debian 4.7.2-5) 4.7.2

Test results are collected (and are visible) on a public dashboard at
http://my.cdash.org/index.php?project=cgi-visitors
