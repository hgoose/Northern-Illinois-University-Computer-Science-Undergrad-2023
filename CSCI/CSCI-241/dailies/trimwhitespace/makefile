CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

trim: FORCE
	$(CXX) $(CXXFLAGS) -o trim trim.cpp solution.cpp

clean: FORCE
	$(RM) -rf trim *.o
	
FORCE:
