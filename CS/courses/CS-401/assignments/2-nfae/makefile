cpp=g++
cppflags=-Wall -Werror -std=c++2a
target=nfa_e

all: ${target}

${target}: nfa_e.o
	${cpp} ${cppflags} -o ${target} nfa_e.o

nfa_e.o: nfa_e.cc
	${cpp} ${cppflags} -c nfa_e.cc

clean: FORCE
	-/bin/rm -rf *.o ${target}	
FORCE:

