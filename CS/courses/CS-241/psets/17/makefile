#
# PROGRAM:    Assignment 17
# PROGRAMMER: your name
# LOGON ID:   your z-id
# DATE DUE:   due date of program
#

# Compiler variables
CXXFLAGS = -Wall -Werror -pedantic -ansi -std=c++14

# Rule to link object code files to create executable file

bstree: main.o
	g++ $(CXXFLAGS) -o bstree main.o

# Rules to compile source code files to object code
main.o: main.cpp bstree.h

# Pseudo-target to remove object code and executable files
clean:
	rm -f bstree *.o
