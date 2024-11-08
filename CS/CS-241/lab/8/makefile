CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

vectorn: FORCE
	$(CXX) $(CXXFLAGS) -o vectorn main.cpp vectorn.cpp

clean: FORCE
	$(RM) -rf vectorn *.o
	
FORCE:
