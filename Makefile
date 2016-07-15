CXX = g++
LINKER = g++
TARGETLIB	= libapsdk.so 

#LIBS:= -lboost_filesystem\
       -lboost_program_options\
			 -lboost_regex\
       -lboost_system

LIBS := -lapexec\
			  -lapcompile

CXXFLAGS = -fPIC -Wall -std=c++0x -O3 -DNDEBUG 
LDFLAGS = -shared

SOURCES:= AnmlMacro.cpp\
					AnmlNetwork.cpp\
					Automaton.cpp\
					Anml.cpp

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGETLIB) : $(OBJECTS)
	$(LINKER) $(LDFLAGS) -o $@ $^ $(LIBS)

all : $(OBJECTS) $(TARGETLIB)

clean:
	-rm -rf *.o $(TARGETLIB) 
