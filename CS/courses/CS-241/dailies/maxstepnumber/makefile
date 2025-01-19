CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

maxstep: FORCE
	$(CXX) $(CXXFLAGS) -o maxstep maxstep.cpp solution.cpp

clean: FORCE
	$(RM) -rf maxstep *.o
	
FORCE:
