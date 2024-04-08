CXX = /usr/bin/g++
CXXFLAGS = -ansi -pedantic -Wall -Werror -std=c++14
RM = /bin/rm

samed: FORCE
	$(CXX) $(CXXFLAGS) -o samed samed.cpp solution.cpp

clean: FORCE
	$(RM) -rf samed *.o
	
FORCE:
