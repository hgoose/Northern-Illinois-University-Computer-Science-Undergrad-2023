#ifndef SIMPLESIM_H
#define SIMPLESIM_H

//********************************************************************
//
// simplesim.h
// CSCI 241 Assignment 8
//
// Created by Nate Warner z2004109
//
//********************************************************************

class simplesim
{
    // Simplesim memory.
    int memory[100];

    // Simplesim registers.
    int accumulator{0};
    int instruction_counter{0};
    int instruction_register{0};
    int operation_code{0};
    int operand{0};

public:

    // Member Functions
    simplesim();
    bool load_program();
    void execute_program();
    void dump() const;
};

#endif
