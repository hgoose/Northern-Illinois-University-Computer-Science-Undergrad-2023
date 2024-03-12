CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

rtod: FORCE
	$(CXX) $(CXXFLAGS) -o rtod rtod.cpp solution.cpp

clean: FORCE
	$(RM) -rf rtod *.o
	
FORCE:
