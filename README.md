CGI programming challenge
=========================


Dependencies
------------

| Name   | Version | Relevance | Notes                                  |
|--------|---------|-----------|----------------------------------------|
| CMake  | >= 2.8.3| mandatory | Cross-platform build system generator. |
| Doxyen | > 1.7.x | optional  | Documentation generator.               |


Organization of files and directories
-------------------------------------

After checking out a working copy, you will be left with the following directory
structure:


Configuration and build
-----------------------

The software uses the CMake (www.cmake.org) cross-platform makefile generator in
order to configure for building library, tools and test programs.

It is advised to perform an out-of-source build, in order to prevent polluting
the source directories:

    mkdir build
    cd build
    cmake [OPTIONS] ..

If the configuration completed succesfully, in order to build all available
components simply type (the optional `-j` option is for parallel builds):

    make [-j]


Installation
------------

Once the build has completed you can install the software: to do this run

    make install

such that header files, libraries, program executables and documentation will be
placed into the appropriate locations.


Documentation
-------------

Source code documentation and extended documentation are generated via Doxygen.

    make doc
