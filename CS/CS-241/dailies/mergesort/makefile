#
# PROGRAM:    Merge Sort
# PROGRAMMER: your name
# LOGON ID:   your z-ID
#

# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14

# Rule to link object code files to create executable file
merge_sort: main.o merge_sort.o
	$(CXX) $(CXXFLAGS) -o merge_sort $^

# Rules to compile source code files to object code
main.o: main.cpp
merge_sort.o: merge_sort.cpp

# Pseudo-target to remove object code and executable files
clean:
	rm -f *.o merge_sort
