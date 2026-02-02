CXX      = g++
CXXFLAGS = -std=c++23 
TARGET   = bin/main
SRC      = tests/main.cc buffio/buffio.cc 

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf bin
