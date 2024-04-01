CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

shellsort: FORCE
	$(CXX) $(CXXFLAGS) -o shellsort shellsort.cpp solution.cpp

clean: FORCE
	$(RM) -rf shellsort *.o
	
FORCE:
