CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

discount: FORCE
	$(CXX) $(CXXFLAGS) -o discount discount.cpp solution.cpp

clean: FORCE
	$(RM) -rf discount *.o
	
FORCE:
