#
# PROGRAM:    MatrixA10
# PROGRAMMER: Nate Warner
# LOGON ID:   z2004109
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
        
# Rule to link object code files to create executable file
matrix: main.o matrix.o
	$(CXX) $(CXXFLAGS) -o matrix $^

# Rules to compile source code file to object code
main.o: main.cpp matrix.h
matrix.o: matrix.cpp matrix.h
   
# Pseudo-target to remove object code and executable files
clean:
	rm -f matrix *.o
