################################################################################
#  This is the Makefile provided for the assignment. You can compile the test  #
# program by typing "make" at the command line. Running make without any       #
# parameters will try to compile all the tests. If you'd like to compile less  #
# than that, you can type the name of the target you'd like to make, i.e.      #
#   % make test1                                                               #
#                                                                              #
#  You can feel free to add NEW rules to this file in your local copy of the   #
# repo. For instance, if you want to write your own simpler test program that  #
# tests only a portion of the container. However, you should not commit any of #
# those changes; keep them local, and...                                       #
#                                                                              #
# DO NOT MAKE CHANGES TO ANY OF THE RULES PROVIDED!                            #
################################################################################

CXX = g++ 
CXXFLAGS = -g -Wall -Werror -std=c++2a

all : alltests

alltests: test1 test2 test3 test4 test5 test6 test7 test8

test1 : test1.cc grids.h grids.decl.h gridtests.h
	$(CXX) $(CXXFLAGS) test1.cc -o test1

test2 : test2.cc grids.h grids.decl.h gridtests.h
	$(CXX) $(CXXFLAGS) test2.cc -o test2

test3 : test3.cc grids.h grids.decl.h gridtests.h
	$(CXX) $(CXXFLAGS) test3.cc -o test3

test4 : test4.cc grids.h grids.decl.h gridtests.h
	$(CXX) $(CXXFLAGS) test4.cc -o test4

test5 : test5.cc grids.h grids.decl.h gridtests.h
	$(CXX) $(CXXFLAGS) test5.cc -o test5

test6 : test6.cc grids.h grids.decl.h gridtests.h
	$(CXX) $(CXXFLAGS) test6.cc -o test6

test7 : test7.cc grids.h grids.decl.h gridtests.h
	$(CXX) $(CXXFLAGS) test7.cc -o test7

test8 : test8.cc grids.h grids.decl.h gridtests.h
	$(CXX) $(CXXFLAGS) test8.cc -o test8

clean :
	-rm -f test[1-8]
