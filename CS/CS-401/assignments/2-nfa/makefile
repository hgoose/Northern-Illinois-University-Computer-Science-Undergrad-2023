cpp=g++
cppflags=-Wall -Werror -std=c++2a
target=nfa

all: ${target}

${target}: nfa.o
	${cpp} ${cppflags} -o ${target} nfa.o

nfa.o: nfa.cc
	${cpp} ${cppflags} -c nfa.cc

clean: FORCE
	-/bin/rm -rf *.o ${target}	
FORCE:

