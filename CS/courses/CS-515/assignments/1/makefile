CXX      = g++
CXXFLAGS = -std=c++23 -Isrc -Itests -Itests/drivers -Isrc/buffio -Isrc/err -Isrc/lexer

TARGET   = bin/main
OBJDIR   = obj

SRC = \
	tests/main.cc \
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

OBJ = $(SRC:%=$(OBJDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CXX) $(OBJ) -o $(TARGET)

$(OBJDIR)/%.cc.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf bin obj
