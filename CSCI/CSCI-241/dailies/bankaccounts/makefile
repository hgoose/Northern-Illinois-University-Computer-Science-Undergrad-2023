#
# PROGRAM:    Bank Accounts
# PROGRAMMER: your name
# LOGON ID:   your z-id
# DATE DUE:   due date of program
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14
        
# Rule to link object code files to create executable file
bank: main.o account.o bank.o
	$(CXX) $(CXXFLAGS) -o bank $^

# Rules to compile source code file to object code
main.o: main.cpp bank.h
account.o: account.cpp account.h
bank.o: bank.cpp bank.h

# Phony target to remove object code and executable files
clean:
	rm -f bank *.o
