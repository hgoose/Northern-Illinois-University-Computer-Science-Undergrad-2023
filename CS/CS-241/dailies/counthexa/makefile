CXX = /usr/bin/g++
CXXFLAGS = -ansi -pedantic -Wall -Werror -std=c++14
RM = /bin/rm

chexa: FORCE
	$(CXX) $(CXXFLAGS) -o chexa chexa.cpp solution.cpp

clean: FORCE
	$(RM) -rf chexa *.o
	
FORCE:
