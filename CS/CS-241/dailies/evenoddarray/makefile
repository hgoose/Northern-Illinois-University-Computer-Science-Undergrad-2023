CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

evenodd: FORCE
	$(CXX) $(CXXFLAGS) -o evenodd evenodd.cpp solution.cpp

clean: FORCE
	$(RM) -rf evenodd *.o
	
FORCE:
