CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

quadsum: FORCE
	$(CXX) $(CXXFLAGS) -o quadsum quadsum.cpp solution.cpp

clean: FORCE
	$(RM) -rf quadsum *.o
	
FORCE:
