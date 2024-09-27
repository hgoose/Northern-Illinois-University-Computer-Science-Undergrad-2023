# A simple Makefile suitable for building and running a single target 
# application file

# Name the executable for this build
TARGET=mixnums

# To add load-libraries, append them to the LDLIBS macro like this:
#LDLIBS+=-lm

# Name all the files need to be compiled here (default, this will compile
# anything that ends with .cc or .cpp as a C++ file.)
# Note that if you change this then you also need to change the OBJ=...
# line to match below!
CXXSRC=$(wildcard *.cc) $(wildcard *.cpp)

###########################################################################

# This makes OBJ contain the names of the .o files
OBJ=$(patsubst %.cpp,%.o,$(patsubst %.cc,%.o,$(CXXSRC)))

# Declare the names of the make targets that are not real files
.PHONY: all run valgrind clean

CXXFLAGS+=-ansi -pedantic -Wall -Werror -std=c++14

all: $(TARGET)

$(TARGET): $(OBJ)
	$(LINK.cc) -o $@ $^ $(LDLIBS)

clean:
	rm -f $(OBJ) $(TARGET)
