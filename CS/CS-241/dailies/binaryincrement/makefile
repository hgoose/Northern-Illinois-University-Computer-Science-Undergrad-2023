CXX = /usr/bin/g++
CXXFLAGS = -ansi -pedantic -Wall -Werror -std=c++14
RM = /bin/rm

bincrement: FORCE
	$(CXX) $(CXXFLAGS) -o bincrement bincrement.cpp solution.cpp

clean: FORCE
	$(RM) -rf bincrement *.o
	
FORCE:
