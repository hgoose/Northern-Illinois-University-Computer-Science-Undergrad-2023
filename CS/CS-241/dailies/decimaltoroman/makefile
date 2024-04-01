CXX = /usr/bin/g++
CXXFLAGS = -ansi -pedantic -Wall -Werror -std=c++14
RM = /bin/rm

dtor: FORCE
	$(CXX) $(CXXFLAGS) -o dtor dtor.cpp solution.cpp

clean: FORCE
	$(RM) -rf dtor *.o
	
FORCE:
