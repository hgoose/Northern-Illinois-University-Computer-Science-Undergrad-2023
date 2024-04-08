# Makefile for compiling z2004109.cpp

# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11

# Target executable name
TARGET = program

# Build target
all: $(TARGET)

$(TARGET): z2004109.o
	$(CXX) $(CXXFLAGS) z2004109.o -o $(TARGET)

z2004109.o: z2004109.cxx
	$(CXX) $(CXXFLAGS) -c z2004109.cxx

# Clean the build
clean:
	rm -f *.o $(TARGET)
