#ifndef SCC_H
#define SCC_H

//**************************************************************************
//
//  scc.h
//  CSCI 241 Assignment 9
//  Created by your-name (your-zid)
//
//**************************************************************************

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
    
    // Add additonal private member functions as desired.
};

#endif
