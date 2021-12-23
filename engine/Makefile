CXX=g++
CXXFLAGS=-std=c++1z -Wall -Werror -Wextra -pedantic

EXECUTABLE=minesweeper_backend

# list of sources used in project
SOURCES     = $(wildcard *.cpp)
# list of objects used in project
OBJECTS     = $(SOURCES:%.cpp=%.o)

all: release debug

# Dependencies
backend.o: backend.h

# rule for creating objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# make release - will compile "all" with $(CXXFLAGS) and the -O3 flag
#                also defines NDEBUG so that asserts will not check
release: CXXFLAGS += -O3 -DNDEBUG
release: $(EXECUTABLE)

# make debug - will compile sources with $(CXXFLAGS) and the -g3 flag
#              also defines DEBUG, so "#ifdef DEBUG /*...*/ #endif" works
debug: CXXFLAGS += -g3 -DDEBUG
debug:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)_debug


# make clean - remove .o files, executables, tarball
clean:
	rm -f *.o *.exe $(EXECUTABLE) $(EXECUTABLE)_debug $(EXECUTABLE)_profile
	rm -Rf *.dSYM

.PHONY: all clean
