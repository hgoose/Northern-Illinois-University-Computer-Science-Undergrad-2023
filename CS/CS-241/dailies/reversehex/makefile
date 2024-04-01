CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

revhex: FORCE
	$(CXX) $(CXXFLAGS) -o revhex revhex.cpp solution.cpp

clean: FORCE
	$(RM) -rf revhex *.o
	
FORCE:
