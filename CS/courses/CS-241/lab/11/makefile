CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -pedantic -ansi -std=c++14
RM = /bin/rm

qtest: FORCE
	$(CXX) $(CXXFLAGS) -o sltest sorted_list.cpp sltest.cpp

clean: FORCE
	$(RM) -rf sltest *.o
	
FORCE:
