CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

heapsort: FORCE
	$(CXX) $(CXXFLAGS) -o heapsort heapsort.cpp solution.cpp

clean: FORCE
	$(RM) -rf heapsort *.o
	
FORCE:
