#
# PROGRAM:    Eight Queens
# PROGRAMMER: your name
# LOGON ID:   your z-ID
#

# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14

# Rule to link object code files to create executable file
queens: queens.o
	$(CXX) $(CXXFLAGS) -o queens $^

# Rules to compile source code files to object code
queens.o: queens.cpp

# Pseudo-target to remove object code and executable files
clean:
	rm -f *.o queens
