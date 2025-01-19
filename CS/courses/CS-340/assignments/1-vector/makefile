CXX=g++
CXXFLAGS=-Wall -g -std=c++2a

all: vectortest

vectortest : main.cc solution.cc
	$(CXX) $(CXXFLAGS) -o vectortest main.cc solution.cc

clean :
	-rm -f vectortest
