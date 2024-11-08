CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

summit: FORCE
	$(CXX) $(CXXFLAGS) -o summit summit.cpp solution.cpp

clean: FORCE
	$(RM) -rf summit *.o
	
FORCE:
