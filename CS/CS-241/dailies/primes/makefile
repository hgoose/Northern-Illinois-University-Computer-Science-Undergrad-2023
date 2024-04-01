CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

primes: FORCE
	$(CXX) $(CXXFLAGS) -o primes primes.cpp solution.cpp

clean: FORCE
	$(RM) -rf primes *.o
	
FORCE:
