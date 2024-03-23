CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

windback: FORCE
	$(CXX) $(CXXFLAGS) -o windback windback.cpp solution.cpp

clean: FORCE
	$(RM) -rf windback *.o
	
FORCE:
