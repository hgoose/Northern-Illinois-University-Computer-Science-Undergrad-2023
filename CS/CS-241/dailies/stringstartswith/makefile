CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

strstart: FORCE
	$(CXX) $(CXXFLAGS) -o strstart strstart.cpp solution.cpp

clean: FORCE
	$(RM) -rf strstart *.o
	
FORCE:
