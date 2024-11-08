#
# PROGRAM:    Assignment 11
# PROGRAMMER: your name
# LOGON ID:   your z-id
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
        
# Rule to link object code files to create executable file
stack_test: stack_test.o mystack.o
	$(CXX) $(CXXFLAGS) -o stack_test $^

# Rules to compile source code file to object code
stack_test.o: stack_test.cpp mystack.h
mystack.o: mystack.cpp mystack.h
   
# Pseudo-target to remove object code and executable files
clean:
	rm -f stack_test *.o
