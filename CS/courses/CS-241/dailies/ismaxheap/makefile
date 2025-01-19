CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -pedantic -ansi -std=c++14
RM = /bin/rm

chexa: FORCE
	$(CXX) $(CXXFLAGS) -o isheap main.cpp solution.cpp

clean: FORCE
	$(RM) -rf isheap *.o
	
FORCE:
