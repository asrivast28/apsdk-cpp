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
					Anml.cpp

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGETLIB) : $(OBJECTS)
	$(LINKER) $(LDFLAGS) -o $@ $^ $(LIBS)

all : $(OBJECTS) $(TARGETLIB)

clean:
	-rm -rf *.o $(TARGETLIB)
