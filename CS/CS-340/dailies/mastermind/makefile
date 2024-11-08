cc=g++
ccflags= -Wall -Werror -std=c++2a
target=mastermind

all: ${target}

${target}: soln_func.o main.o
	${cc} ${ccflags} -o ${target} soln_func.o main.o

soln_func.o: soln_func.cc 
	${cc} ${ccflags} -c soln_func.cc

main.o: main.cc 
	${cc} ${ccflags} -c main.cc

clean:
	-rm -rf *.o ${target}
