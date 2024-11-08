CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

replace: FORCE
	$(CXX) $(CXXFLAGS) -o replace replace.cpp solution.cpp

clean: FORCE
	$(RM) -rf replace *.o
	
FORCE:
