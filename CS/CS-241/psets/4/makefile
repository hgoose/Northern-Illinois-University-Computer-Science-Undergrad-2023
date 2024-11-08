#
# PROGRAM:    Towers of Hanoi
# PROGRAMMER: your name
# LOGON ID:   your z-ID
#

# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14

# Rule to link object code files to create executable file
hanoi: hanoi.o
	$(CXX) $(CXXFLAGS) -o hanoi $^

# Rules to compile source code files to object code
hanoi.o: hanoi.cpp

# Pseudo-target to remove object code and executable files
clean:
	rm -f *.o hanoi
