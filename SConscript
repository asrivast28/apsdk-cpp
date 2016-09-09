##
# @file SConscript
# @brief Provides functionality for building the apsdk static library.
# @author Ankit Srivastava <asrivast@gatech.edu>
# @version 1.0
# @date 2016-09-09

import platform

Import('env')

libName = 'apsdk'

cppLibs = [
           'apexec',
           'apcompile',
           ]

srcFiles = [
            'SymbolChange.cpp',
            'AnmlMacro.cpp',
            'AnmlNetwork.cpp',
            'Automaton.cpp',
            'ElementMap.cpp',
            'ElementRef.cpp',
            'Runtime.cpp',
            'Device.cpp',
            'Anml.cpp',
            ]

apsdk = env.StaticLibrary(target = libName, source = srcFiles, LIBS = cppLibs)
#apsdk = env.SharedLibrary(target = libName, source = srcFiles, LIBS = cppLibs)
Return("apsdk")
