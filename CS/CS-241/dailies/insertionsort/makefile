#
# PROGRAM:    Insertion Sort
# PROGRAMMER: your name
# LOGON ID:   your z-ID
#

# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14

# Rule to link object code files to create executable file
insertion_sort: main.o insertion_sort.o
	$(CXX) $(CXXFLAGS) -o insertion_sort $^

# Rules to compile source code files to object code
main.o: main.cpp
insertion_sort.o: insertion_sort.cpp

# Pseudo-target to remove object code and executable files
clean:
	rm -f *.o insertion_sort
