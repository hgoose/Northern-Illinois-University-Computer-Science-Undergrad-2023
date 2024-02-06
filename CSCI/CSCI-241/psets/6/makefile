#
# PROGRAM:    Quicksort
# PROGRAMMER: your name
# LOGON ID:   your z-ID
#

# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14

# Rule to link object code files to create executable file
quicksort: main.o quicksort.o
	$(CXX) $(CXXFLAGS) -o quicksort $^

# Rules to compile source code files to object code
main.o: main.cpp
quicksort.o: quicksort.cpp

# Pseudo-target to remove object code and executable files
clean:
	rm -f *.o quicksort
