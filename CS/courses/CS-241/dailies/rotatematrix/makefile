CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

rotate: FORCE
	$(CXX) $(CXXFLAGS) -o rotate rotate.cpp solution.cpp

clean: FORCE
	$(RM) -rf rotate *.o
	
FORCE:
