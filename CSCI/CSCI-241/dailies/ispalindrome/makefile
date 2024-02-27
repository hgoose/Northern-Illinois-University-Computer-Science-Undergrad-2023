CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

palindrome: FORCE
	$(CXX) $(CXXFLAGS) -o palindrome palindrome.cpp solution.cpp

clean: FORCE
	$(RM) -rf palindrome *.o
	
FORCE:
