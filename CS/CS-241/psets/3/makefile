#
# PROGRAM:    Bubble Sort
# PROGRAMMER: your name
# LOGON ID:   your z-ID
#

# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14

# Rule to link object code files to create executable file
bubble_sort: main.o bubble_sort.o
	$(CXX) $(CXXFLAGS) -o bubble_sort $^

# Rules to compile source code files to object code
main.o: main.cpp
bubble_sort.o: bubble_sort.cpp

# Pseudo-target to remove object code and executable files
clean:
	rm -f *.o bubble_sort
