CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -pedantic -ansi -std=c++14
RM = /bin/rm

chexa: FORCE
	$(CXX) $(CXXFLAGS) -o wc main.cpp solution.cpp

clean: FORCE
	$(RM) -rf wc *.o
	
FORCE:
