CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

hello: FORCE
	$(CXX) $(CXXFLAGS) -o hello hello.cpp

clean: FORCE
	$(RM) -rf hello *.o
	
FORCE:
