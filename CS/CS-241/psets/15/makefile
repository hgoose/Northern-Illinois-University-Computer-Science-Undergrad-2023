#
# PROGRAM:    Assignment 9
# PROGRAMMER: your name
# LOGON ID:   your z-id
# DATE DUE:   due date of program
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
        
# Rule to link object code files to create executable file
scc: main.o scc.o inpost.o mystack.o
	$(CXX) $(CXXFLAGS) -o scc $^

# Rules to compile source code file to object code
scc.o: scc.cpp scc.h sml.h inpost.h
inpost.o: inpost.cpp inpost.h mystack.h
mystack.o: mystack.cpp mystack.h
main.o: main.cpp scc.h
   
# Pseudo-target to remove object code and executable files
clean:
	rm -f scc *.o
