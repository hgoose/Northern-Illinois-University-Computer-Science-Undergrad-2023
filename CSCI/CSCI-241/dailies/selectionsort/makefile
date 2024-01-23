#
# PROGRAM:    Selection Sort
# PROGRAMMER: your name
# LOGON ID:   your z-ID
#

# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14

# Rule to link object code files to create executable file
selection_sort: main.o selection_sort.o
	$(CXX) $(CXXFLAGS) -o selection_sort $^

# Rules to compile source code files to object code
main.o: main.cpp
selection_sort.o: selection_sort.cpp

# Pseudo-target to remove object code and executable files
clean:
	rm -f *.o selection_sort
