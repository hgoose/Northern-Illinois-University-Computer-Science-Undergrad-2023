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
CXXFLAGS=-g -Wall -std=c++20

# Only the non-verbose modes are compiled by default
all : test1 test2 test3 test4 test5

# Type "make verbose" to compile versions with the verbose flag on
verbose : test2v test4v test5v


test1 : testing.h bintree.h test1.cc
	$(CXX) $(CXXFLAGS) -o test1 test1.cc

test2 : testing.h test2.cc xml.o
	$(CXX) $(CXXFLAGS) -o test2 test2.cc xml.o

test2v : testing.h test2.cc xml.o
	$(CXX) $(CXXFLAGS) -DVERBOSE=true -o test2v test2.cc xml.o

test3 : testing.h test3.cc xml.o
	$(CXX) $(CXXFLAGS) -o test3 test3.cc xml.o


# test4 is used for testing on autograder, test4v is for local debugging
test4 : testing.h test4.cc xml.o xmlparse.o
	$(CXX) $(CXXFLAGS) -o test4 test4.cc xml.o xmlparse.o

test4v : testing.h test3.cc xml.o
	$(CXX) $(CXXFLAGS) -DVERBOSE=true -o test4v test4.cc xml.o xmlparse.o


# test5 is used for testing on autograder, test5v is for local debugging
test5 : testing.h test5.cc xml.o xmlparse.o
	$(CXX) $(CXXFLAGS) -o test5 test5.cc xml.o xmlparse.o

test5v : testing.h test3.cc xml.o
	$(CXX) $(CXXFLAGS) -DVERBOSE=true -o test5v test5.cc xml.o xmlparse.o


xml.o : xml.cc xml.h
	$(CXX) $(CXXFLAGS) -c xml.cc

xmlparse.o : xmlparse.cc xml.h
	$(CXX) $(CXXFLAGS) -c xmlparse.cc

clean :
	-rm -f test1 test2 test2v test3 test4 test4v test5 test5v xml.o xmlparse.o
