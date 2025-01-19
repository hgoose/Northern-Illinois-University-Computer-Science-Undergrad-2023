cpp=g++
cppflags= -Wall -Werror -std=c++2a
target=dfa

all: ${target}

${target}: dfa.o
	${cpp} ${cppflags} dfa.o -o ${target}

dfa.o: dfa.cc
	${cpp} ${cppflags} -c dfa.cc

clean:
	-/bin/rm -rf ${target} *.o
