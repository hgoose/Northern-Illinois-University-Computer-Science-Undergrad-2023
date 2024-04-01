#
# PROGRAM:    Assignment 7B
# PROGRAMMER: your name
# LOGON ID:   your z-id
# DATE DUE:   due date of program
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
        
# Rule to link object code files to create executable file
inpost: main.o inpost.o mystack.o
	$(CXX) $(CXXFLAGS) -o inpost $^

# Rules to compile source code file to object code
main.o: main.cpp inpost.h
inpost.o: inpost.cpp inpost.h mystack.h
mystack.o: mystack.cpp mystack.h
   
# Pseudo-target to remove object code and executable files
clean:
	rm -f inpost *.o
