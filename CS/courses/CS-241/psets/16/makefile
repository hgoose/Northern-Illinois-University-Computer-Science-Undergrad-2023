#
# PROGRAM:    Assignment 16
# PROGRAMMER: your name
# LOGON ID:   your z-id
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
        
# Rule to link object code files to create executable file
list_test: list_test.o
	$(CXX) $(CXXFLAGS) -o list_test $^

# Rules to compile source code file to object code
list_test.o: list_test.cpp mylist.h
   
# Pseudo-target to remove object code and executable files
clean:
	rm -f list_test *.o
