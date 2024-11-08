#ifndef SCC_H
#define SCC_H

//********************************************************************
//
//  scc.h
//  CSCI 241 Assignment 15
//  Created by Nate Warner z2004109
//
//********************************************************************

#include <sstream>
#include <string>

/**
 * Symbol table entry.
 */
struct table_entry
{
    int symbol = -1;
    char type = 'X';     // 'C' = constant, 'L' = Simple line number, 
                         // 'V' = variable
    int location = -1;   // Simplesim address
};

/**
 * Simple compiler.
 */
class scc
{
public:
    
    // Data members.
    static const int MEMORY_SIZE = 100;
    static const int SYMBOL_TABLE_SIZE = 1000;
    
    // Member functions.
    scc();
    void first_pass();
    void second_pass();
    void print_program() const;

private:
    
    // Data members.
    int memory[MEMORY_SIZE];
    int data[MEMORY_SIZE];
    int ndata = 0;
    
    table_entry symbol_table[SYMBOL_TABLE_SIZE];
    int flags[MEMORY_SIZE];
    
    int next_instruction_addr = 0;
    int next_const_or_var_addr = MEMORY_SIZE - 1;
    int next_symbol_table_idx = 0;
    
    // Add additional private member functions as desired.
    void handle_input(std::istringstream&);
    void handle_data(std::istringstream&);
    void handle_let(std::istringstream&, const std::string&);
    void handle_goto(std::istringstream&);
    void handle_if(std::istringstream&);
    void handle_print(std::istringstream&);
    void handle_end();

    void memory_check() const;
    void data_check() const;
    void stack_space_check(int) const;

    int get_symbol_location(const std::string&);
    int search_symbol_table(int, char) const;
};

#endif
