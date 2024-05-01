CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -pedantic -ansi -std=c++14
RM = /bin/rm

qtest: FORCE
	$(CXX) $(CXXFLAGS) -o symtree symtree.cpp solution.cpp

clean: FORCE
	$(RM) -rf symtree *.o
	
FORCE:
