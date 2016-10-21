# C++ API for AP-SDK
This repository provides a C++ API for AP-SDK, by wrapping around [the C API](http://www.micronautomata.com/apsdk_documentation/1.7-34/modules.html) provided by the SDK.
We create a class each for encapsulating every datatype used by the C API. In each case, the class also provides all the related functionality and some helper functions.

## Requirements
* **gcc** (with C++11 support)  
This project has been test built only on Linux platform, using gcc with C++11 support.
* **AP SDK** (*v1.6* or *v1.7*)  
The SDK can be downloaded from the following links: [Windows](https://drive.google.com/open?id=0B7SP70jwzihbSHRGMFhmUVQ2MG8),
 [Ubuntu](https://drive.google.com/open?id=0B7SP70jwzihbbzJnN3Y0Zmd1N2c),
 and [CentOS](https://drive.google.com/open?id=0B7SP70jwzihbVUlydlR5a0NwbUE).  
Please note that the provided links to the SDK are for the purpose of evaluation of this work and should not be distributed without the permission of Micron, Inc.
* **SCons**  
SCons, a cross-platform Python based build environment, is required for building the project.
 More information about the tool can be found at [http://scons.org/](http://scons.org/).

## Building
This repository is not intended to be used in a stand-alone mode. Therefore, we only provide an `SConscript` file for the repository, which can be
called by the `SConstruct` of another project.
