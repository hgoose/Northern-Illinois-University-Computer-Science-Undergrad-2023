CXX=g++
CXXFLAGS=-g -Wall -std=c++20

all : test1 test2 test2-1 test2-2 test3 test4 test5 test6


test1 : test1.cc iniparse.o
	$(CXX) $(CXXFLAGS) -o test1 test1.cc iniparse.o


# test2 - test loading ini and printing contents, -n versions set verbosity level
test2 : test2.cc iniparse.o
	$(CXX) $(CXXFLAGS) -o test2 test2.cc iniparse.o

test2-1 : test2.cc iniparse.o
	$(CXX) $(CXXFLAGS) -DVERBOSITY=1 -o test2-1 test2.cc iniparse.o 

test2-2 : test2.cc iniparse.o
	$(CXX) $(CXXFLAGS) -DVERBOSITY=2 -o test2-2 test2.cc iniparse.o


test3 : test3.cc sudoku.o
	$(CXX) $(CXXFLAGS) -o test3 test3.cc sudoku.o

test4 : test4.cc sudoku.o
	$(CXX) $(CXXFLAGS) -o test4 test4.cc sudoku.o

test5 : test5.cc sudoku.o
	$(CXX) $(CXXFLAGS) -o test5 test5.cc sudoku.o
	
test6 : test6.cc sudoku.o iniparse.o
	$(CXX) $(CXXFLAGS) -o test6 test6.cc sudoku.o iniparse.o

sudoku.o : sudoku.cc sudoku.h settings.h
	$(CXX) $(CXXFLAGS) -c sudoku.cc

iniparse.o : iniparse.cc iniparse.h settings.h
	$(CXX) $(CXXFLAGS) -c iniparse.cc

clean :
	-rm -f test1 test2 test2-1 test2-2 test3 test4 test5 test6 iniparse.o sudoku.o
