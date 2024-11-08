cc=g++
ccflags= -Wall -Werror -std=c++2a
target=htmlencode
proj=main.o htmlencode.o

all: ${target}

${target}: htmlencode.o main.o
	${cc} ${ccflags} -o ${target} ${proj}

htmlencode.o: htmlencode.cc
	${cc} ${ccflags} -c htmlencode.cc

main.o: main.cc
	${cc} ${ccflags} -c main.cc

clean: FORCE
	-/usr/bin/rm -rf *.o ${target}

FORCE: 
	
