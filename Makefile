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

CXX = g++
LINKER = g++
TARGETLIB	= libapsdk.so

LIBS := -lapexec\
			  -lapcompile

# Release flags
#CXXFLAGS = -fPIC -Wall -std=c++0x -O3 -DNDEBUG
#LDFLAGS = -shared
# Debug flags
CXXFLAGS = -fPIC -Wall -std=c++0x -g
LDFLAGS = -shared -g

SOURCES:= SymbolChange.cpp\
					AnmlMacro.cpp\
					AnmlNetwork.cpp\
					Automaton.cpp\
					ElementMap.cpp\
					ElementRef.cpp\
					Runtime.cpp\
          Device.cpp\
					Anml.cpp

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGETLIB) : $(OBJECTS)
	$(LINKER) $(LDFLAGS) -o $@ $^ $(LIBS)

all : $(OBJECTS) $(TARGETLIB)

clean:
	-rm -rf #.o $(TARGETLIB)
