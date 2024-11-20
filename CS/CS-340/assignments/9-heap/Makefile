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
CXXFLAGS = -std=c++20 -g -Wall
all : 1-basic 2-bubble 3-insdel 4-heapify 5-heapsort 6-pq

1-basic : test-basic.cc heap.h
	$(CXX) $(CXXFLAGS) -o 1-basic test-basic.cc

2-bubble : test-bubble.cc heap.h
	$(CXX) $(CXXFLAGS) -o 2-bubble test-bubble.cc

3-insdel : test-insdel.cc heap.h
	$(CXX) $(CXXFLAGS) -o 3-insdel test-insdel.cc

4-heapify : test-heapify.cc heap.h
	$(CXX) $(CXXFLAGS) -o 4-heapify test-heapify.cc

5-heapsort : test-heapsort.cc heap.h
	$(CXX) $(CXXFLAGS) -o 5-heapsort test-heapsort.cc

6-pq : test-pq.cc heap.h heap_priority_queue.h
	$(CXX) $(CXXFLAGS) -o 6-pq test-pq.cc

clean : 
	-rm -f 1-basic 2-bubble 3-insdel 4-heapify 5-heapsort 6-pq
