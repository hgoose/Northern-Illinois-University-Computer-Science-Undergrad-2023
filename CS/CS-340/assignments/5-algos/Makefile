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
CXXFLAGS = -g -Wall -std=c++20

all : alltests


alltests: test-read-lines test-simple-strict test-simple-greedy \
	test-print-table test-sorting test-calc-widths test-load-tsv \
	test-load-sort

test-read-lines : test-read-lines.cc gen-algo.h gen-algo.decl.h testing.h
	$(CXX) $(CXXFLAGS) test-read-lines.cc -o test-read-lines

test-simple-strict : test-simple-strict.cc gen-algo.h gen-algo.decl.h testing.h
	$(CXX) $(CXXFLAGS) test-simple-strict.cc -o test-simple-strict

test-simple-greedy : test-simple-greedy.cc gen-algo.h gen-algo.decl.h testing.h
	$(CXX) $(CXXFLAGS) test-simple-greedy.cc -o test-simple-greedy

test-print-table : test-print-table.cc gen-algo.h gen-algo.decl.h testing.h
	$(CXX) $(CXXFLAGS) test-print-table.cc -o test-print-table

test-calc-widths : test-calc-widths.cc gen-algo.h gen-algo.decl.h testing.h
	$(CXX) $(CXXFLAGS) test-calc-widths.cc -o test-calc-widths

test-sorting : test-sorting.cc gen-algo.h gen-algo.decl.h testing.h
	$(CXX) $(CXXFLAGS) test-sorting.cc -o test-sorting


test-load-tsv : test-load-tsv.cc gen-algo.h gen-algo.decl.h testing.h
	$(CXX) $(CXXFLAGS) test-load-tsv.cc -o test-load-tsv

test-load-sort : test-load-sort.cc gen-algo.h gen-algo.decl.h testing.h
	$(CXX) $(CXXFLAGS) test-load-sort.cc -o test-load-sort

clean :
	-rm -f test-read-lines test-simple-strict test-simple-greedy \
 	       test-print-table test-sorting test-calc-widths test-load-tsv \
	       test-load-sort
