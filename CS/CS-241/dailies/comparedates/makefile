CXX = /usr/bin/g++
CXXFLAGS = -ansi -pedantic -Wall -Werror -std=c++14
RM = /bin/rm

compdate: FORCE
	$(CXX) $(CXXFLAGS) -o compdate compdate.cpp solution.cpp

clean: FORCE
	$(RM) -rf compdate *.o
	
FORCE:
