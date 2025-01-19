CXX=g++
CXXFLAGS=-Wall -g -std=c++2a -fconcepts

all: stattest printtest histotest do_ints do_strings

histotest : histotest.cc assign2-algos.h
	$(CXX) $(CXXFLAGS) histotest.cc -o histotest

stattest : stattest.cc assign2-algos.h
	$(CXX) $(CXXFLAGS) stattest.cc -o stattest

printtest : printtest.cc assign2-algos.h
	$(CXX) $(CXXFLAGS) printtest.cc -o printtest

do_ints:  do_ints.cc assign2-algos.h
	$(CXX) $(CXXFLAGS) do_ints.cc -o do_ints

do_strings:  do_strings.cc assign2-algos.h
	$(CXX) $(CXXFLAGS) do_strings.cc -o do_strings

test_ints: do_ints
	./do_ints

test_strings: do_strings
	./do_strings

clean :
	-rm -f stattest printtest histotest do_ints do_strings
