CXX = /usr/bin/g++
CXXFLAGS = -ansi -pedantic -Wall -Werror -std=c++14
RM = /bin/rm

qtest: FORCE
	$(CXX) $(CXXFLAGS) -o qtest myqueue.cpp qtest.cpp

clean: FORCE
	$(RM) -rf qtest *.o
	
FORCE:
