CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

stats: FORCE
	$(CXX) $(CXXFLAGS) -o stats stats.cpp solution.cpp

clean: FORCE
	$(RM) -rf stats *.o
	
FORCE:
