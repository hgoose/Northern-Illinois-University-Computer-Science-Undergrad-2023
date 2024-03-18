# Makefile for compiling main.cpp

# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Target executable name
TARGET = program

# Build target
all: $(TARGET)

$(TARGET): main.o
	$(CXX) $(CXXFLAGS) main.o -o $(TARGET)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Clean the build
clean:
	rm -f *.o $(TARGET)
