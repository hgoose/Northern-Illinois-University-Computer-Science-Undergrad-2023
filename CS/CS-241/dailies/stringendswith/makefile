CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

strend: FORCE
	$(CXX) $(CXXFLAGS) -o strend strend.cpp solution.cpp

clean: FORCE
	$(RM) -rf strend *.o
	
FORCE:
