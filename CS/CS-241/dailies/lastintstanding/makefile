CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

indexof: FORCE
	$(CXX) $(CXXFLAGS) -o lastint lastint.cpp solution.cpp

clean: FORCE
	$(RM) -rf lastint *.o
	
FORCE:
