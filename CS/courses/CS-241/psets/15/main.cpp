//**************************************************************************
//
//  main.cpp
//  CSCI 241 Assignment 9
//  Created by your-name (your-zid)
//
//**************************************************************************

#include "scc.h"

/**
 * Compiles Simple code into SML and prints the program.
 *
 * @return 0 if successful, otherwise -1.
 */
int main()
{
    scc compiler;

    compiler.first_pass();

    compiler.second_pass();

    compiler.print_program();

    return 0;
}
