##
# @file SConscript
# @brief Provides functionality for building the apsdk static library.
#
# Copyright 2018 Georgia Institute of Technology
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
