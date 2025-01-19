CXX = /usr/bin/g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
RM = /bin/rm

vector3: FORCE
	$(CXX) $(CXXFLAGS) -o vector3 main.cpp vector3.cpp

clean: FORCE
	$(RM) -rf vector3 *.o
	
FORCE:
