CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -pedantic -ansi -std=c++14
RM = /bin/rm

qtest: FORCE
	$(CXX) $(CXXFLAGS) -o reverse mylist.cpp reverse.cpp

clean: FORCE
	$(RM) -rf reverse *.o
	
FORCE:
