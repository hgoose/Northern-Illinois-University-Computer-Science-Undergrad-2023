CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

maxdiff: FORCE
	$(CXX) $(CXXFLAGS) -o maxdiff maxdiff.cpp solution.cpp

clean: FORCE
	$(RM) -rf maxdiff *.o
	
FORCE:
