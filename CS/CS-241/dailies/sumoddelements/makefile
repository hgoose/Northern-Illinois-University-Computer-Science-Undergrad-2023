CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

sumodd: FORCE
	$(CXX) $(CXXFLAGS) -o sumodd sumodd.cpp solution.cpp

clean: FORCE
	$(RM) -rf sumodd *.o
	
FORCE:
