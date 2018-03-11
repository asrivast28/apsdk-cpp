# C++ API for AP-SDK
[![Apache 2.0 License](https://img.shields.io/badge/license-Apache%20v2.0-blue.svg)](LICENSE)

This repository provides a C++ API for AP-SDK, by wrapping around [the C API](http://www.micronautomata.com/apsdk_documentation/1.7-34/modules.html) provided by the SDK.
A class was created for encapsulating every datatype used by the C API. In each case, the class also provides all the related functionality and some helper functions.

## Requirements
* **gcc** (with C++11 support)  
This project has been test built only on Linux platform, using gcc with C++11 support.
* **AP SDK** (*v1.7.26* or *v1.7.34*)  
The SDK provides the C API around which this wrapper works. 
* **SCons**  
SCons, a cross-platform Python based build environment, is required for building the project.
 More information about the tool can be found at [http://scons.org/](http://scons.org/).

## Building
This repository is not intended to be used in a stand-alone mode. Therefore, only an `SConscript` file is provided for the repository, which can be
called by the `SConstruct` of another project.
