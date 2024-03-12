CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

hash_table: FORCE
	$(CXX) $(CXXFLAGS) -o hash_table main.cpp hash_table.cpp

clean: FORCE
	$(RM) -rf hash_table *.o
	
FORCE:
