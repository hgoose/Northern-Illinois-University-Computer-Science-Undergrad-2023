#ifndef SML_H
#define SML_H

//********************************************************************
//
// sml.h
// CSCI 241 Assignment 8
//
// Created by Nate Warner z2004109
//
//********************************************************************

#define READ 11
#define WRITE 12

// input / Output Operations:
#define READ 11             // Read a word into a specific memory location.
#define WRITE 12            // Print a word from a specific memory location. 

// Store / Load Operations:
#define STORE 21            // Store the word in the accumulator in a specific memory location.
#define LOAD 22             // Load a word from a specific memory location into the accumulator. 

// Arithmetic Operations:
#define ADD 31              // Add a word in a specific memory location to the word in the accumulator (leave result in accumulator).
#define SUBTRACT 32         // Subtract a word in a specific memory location from the word in the accumulator (leave result in accumulator).
#define MULTIPLY 33         // Multiply a word in a specific memory location by the word in the accumulator (leave result in accumulator). 

#define DIVIDE 34           // Divide a word in a specific memory location into the word in the accumulator (leave result in accumulator).

// Transfer of Control Operations:
#define BRANCH 41           // Branch to a specific memory location.
#define BRANCHZERO 42       // Branch to a specific memory location if the accumulator is zero.
#define BRANCHNEG 43        // Branch to a specific memory location if the accumulator is negative.
#define HALT 44             // Halt, i.e., the program has completed its task. 

#define DEFAULT 7777        // Default value for empty memory elements

#endif
