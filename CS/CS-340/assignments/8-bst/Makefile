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
CXX=g++
CXXFLAGS=-g -Wall -Wuninitialized -std=c++20

all : test1 test2 test3 test4

test1 : test1.cc bst.h bintree.h testing.h
	$(CXX) $(CXXFLAGS) -o test1 test1.cc

test2 : test2.cc bst.h bintree.h testing.h
	$(CXX) $(CXXFLAGS) -o test2 test2.cc

test3 : test3.cc bst.h bintree.h testing.h
	$(CXX) $(CXXFLAGS) -o test3 test3.cc

test4 : test4.cc bst.h bintree.h testing.h
	$(CXX) $(CXXFLAGS) -o test4 test4.cc

clean :
	-rm -f test1 test2 test3 test4
