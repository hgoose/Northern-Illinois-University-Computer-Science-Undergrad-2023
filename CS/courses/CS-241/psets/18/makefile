#
# PROGRAM:  BaseballA12
# AUTHOR::  your-name
# Z-ID:     your-zid
# DATE DUE: due date of program  
#

# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -ansi -std=c++14

# Rule to link object code files to create executable file
baseball: main.o player.o hitter.o pitcher.o print.o
	$(CXX) $(CXXFLAGS) -o baseball $^

# Rules to compile source code files to object code
main.o: main.cpp player.h hitter.h pitcher.h
player.o: player.cpp player.h
hitter.o: hitter.cpp hitter.h
pitcher.o: pitcher.cpp pitcher.h
print.o: print.cpp player.h hitter.h pitcher.h

# Pseudo-target to remove object code and executable files
clean:
	rm -f baseball *.o
