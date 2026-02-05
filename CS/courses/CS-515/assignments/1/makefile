CXX      = g++ 
CXXFLAGS = -std=c++23 -Isrc -Itests -Itests/drivers -Isrc/buffio -Isrc/err -Isrc/lexer
TARGET   = bin/main
SRC      = tests/main.cc \
		   tests/util.cc \
           tests/drivers/copy_compare.cc \
		   tests/drivers/unget_rewind.cc \
		   tests/drivers/eof_overread.cc \
		   tests/drivers/line_reconstruct.cc \
		   tests/drivers/lex_tester.cc \
		   src/err/error.cc \
		   src/lexer/lex.cc \
		   src/lexer/token.cc \
		   src/buffio/buffio.cc 

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf bin
