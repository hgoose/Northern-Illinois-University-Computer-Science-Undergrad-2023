CXX      = g++
CXXFLAGS = -std=c++23 -Isrc -Itests -Itests/drivers -Isrc/buffio -Isrc/err -Isrc/lexer -Isrc/parser -Isrc/codegen -g

TARGET   = bin/ncc
OBJDIR   = obj

SRC = \
	tests/main.cc \
	tests/util.cc \
	tests/drivers/parsertest.cc \
	src/err/error.cc \
	src/lexer/lex.cc \
	src/lexer/token.cc \
	src/buffio/buffio.cc \
	src/parser/parser.cc \
	src/parser/ast_utils.cc \
	src/codegen/codegen.cc \
	src/codegen/tree_eval.cc
	

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
