CXX = /usr/bin/g++
CXXFLAGS = -ansi -pedantic -Wall -Werror -std=c++14
RM = /bin/rm

cut: FORCE
	$(CXX) $(CXXFLAGS) -o cut cut.cpp solution.cpp

clean: FORCE
	$(RM) -rf cut *.o
	
FORCE:
