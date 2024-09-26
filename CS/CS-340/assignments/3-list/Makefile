################################################################################
#  This is the Makefile provided for the assignment. You can compile the test  #
# program by typing "make" at the command line. To run it using default        #
# settings, type "make test", or make it normally and then run "./container"   #
# at the shell prompt.                                                         #
#                                                                              #
#  You can feel free to add NEW rules to this file in your local copy of the   #
# repo. For instance, if you want to write your own simpler test program that  #
# tests only a portion of the container. However, you should not commit any of #
# those changes; keep them local, and...                                       #
#                                                                              #
# DO NOT MAKE CHANGES TO ANY OF THE RULES PROVIDED!                            #
################################################################################
CXX=g++
CXXFLAGS=-Wall -Werror -g -std=c++2a

all: container 

# compile the testing program for the STL-capable linked list 
container:  container.cc simple_linked_list.h assign2-algos.h
	$(CXX) $(CXXFLAGS) container.cc -o container

assign2-algos.h :
	@echo ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR
	@echo ERROR
	@echo ERROR   This assignment uses the assign2-algos.h 
	@echo ERROR from the previous assignment, which is not
	@echo ERROR present. Place it in this directory and 
	@echo ERROR this message will go away.
	@echo ERROR
	@echo ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR
	@false

# run the program, compiling if needed
test: container
	./container

# clean up by removing the files created during complation
clean :
	-rm -f container 
