//********************************************************************
//
// simplesim.cpp
// CSCI 241 Assignment 8
//
// Created by Nate Warner z2004109
//
//********************************************************************

// Includes
#include <iostream>         // For input/output streams
#include <ios>              // For output stream manipulators
#include <iomanip>          // For output stream manipulators

// Header files
#include "simplesim.h"
#include "sml.h"

// Using from standard namespace
using  std::cin;
using  std::cerr;
using  std::cout;
using  std::endl;
using  std::internal;
using  std::left;
using  std::noshowpos;
using  std::right;
using  std::setfill;
using  std::setw;
using  std::showpos;

/**
 * Initializes the Simplesim's memory to default values.
 */
simplesim::simplesim()
{

    for (int i=0; i<100; ++i) {
        this->memory[i] = 7777;
    }
}

/**
 * Loads an SML program into the Simplesim's memory.
 *
 * @return Returns true if a valid program is successfully loaded into 
 *         memory; otherwise, false.
 */
bool simplesim::load_program()
{
    int count = 0;          // Instruction count.
    int instruction = 0;    // Holds instruction read.

    // While not EOF and we have not encountered the sentinel value...
    while (cin >> instruction && instruction != -99999)
    {
        // Check for an invalid word. If invalid, print error message
        // and return false.
        if (instruction < -9999 || instruction > 9999) {
            cerr << "*** ABEND: pgm load: invalid word ***" << endl;
            return 0;
        }
        
        // Check for too large a program. If count is outside the 
        // boundaries of the memory array, print error message and
        // return false.
        if (count >= 100) {
            cerr << "*** ABEND: pgm load: pgm too large ***" << endl;
            return 0;
        }

        // Add the instruction to the memory array at subscript count.
        memory[count] = instruction;

        // Increment instruction count by 1.
        ++count;
    }

    // No erros
    return true;
}

/**
 * Executes an SML program loaded into the Simplesim's memory.
 */
void simplesim::execute_program()
{

    bool done = false;      // For loop control
    int result = 0;         // Used to hold the result from arithmetic operations

    while (!done)
    {
        // Check for an addressability error. If instruction_counter
        // is outside the boundaries of the memory array, print error
        // and return.

        // Fetch the instruction and extract the operation code
        // and operand.
        if (instruction_counter >= 0 && instruction_counter <= 99 ) {
            instruction_register = memory[instruction_counter];
        } else {
            cerr << "*** ABEND: addressability error ***" << endl;
            return; 
        }

        operation_code = instruction_register / 100;        // Extract the left two digits
        operand = instruction_register % 100;               // Extract the right two digits
        
        // Execute the correct instruction.
        switch (operation_code)
        {

        // Instruction 11: Read a word into a specific memory location. 
        case READ:
            int value;
            cin >> value; // Grab the input from the file

            // Check for valid input, if the input is valid, store in memory and output to standard out
            if (value > -9999 && value < 9999) {
                memory[operand] = value;
                cout << "READ: " << right << setw(5) << setfill('0') << internal <<  showpos << value << noshowpos << setfill(' ') << endl;
            } else {
                cerr << "*** ABEND: illegal input ***" << endl;
                return;
            }
            ++instruction_counter; // Increment the instruction counter
            break;

        // Instruction 12: Print a word from a specific memory location.
        case WRITE:
            // Output the word in memory at address specifed by the operand.
            cout << right << setw(5) << setfill('0') << internal << showpos << memory[operand] << noshowpos << setfill(' ') << endl;

            ++instruction_counter; // Increment instruction_counter
            break;

        // Instruction 22: Load a word from a specific memory location into the accumulator.
        case LOAD:
            accumulator = memory[operand]; // Store the word from memory into the accumulator register

            ++instruction_counter; // Increment the instruction counter
            break;

        // Instruction 21: Store the word in the accumulator in a specific memory location.
        case STORE:
            memory[operand] = accumulator; // Store the word

            ++instruction_counter; // Increment the instruction counter
            break;

        // Instruction 31: Add a word in a specific memory location to the word in the accumulator (leave result in accumulator)
        case ADD:

            // Compute
            result = accumulator + memory[operand];

            // Validate
            if (result < -9999) {
                cerr << "*** ABEND: underflow ***" << endl;
                return;
            } else if (result > 9999) {
                cerr << "*** ABEND: overflow ***" << endl;
                return;
            }

            // Store
            accumulator = result;

            ++instruction_counter; // Increment the instruction counter
            break;

        // Instruction 32: Subtract a word in a specific memory location from the word in the accumulator (leave result in accumulator).
        case SUBTRACT:

            // Compute
            result = accumulator - memory[operand];

            // Validate
            if (result < -9999) {
                cerr << "*** ABEND: underflow ***" << endl;
                return;
            } else if (result > 9999) {
                cerr << "*** ABEND: overflow ***" << endl;
                return;
            }

            // Store
            accumulator = result;

            ++instruction_counter; // Increment the instruction counter
            break;

        // Instruction 33: Multiply a word in a specific memory location by the word in the accumulator (leave result in accumulator). 
        case MULTIPLY:

            // Compute
            result = accumulator * memory[operand];

            // Validate
            if (result < -9999) {
                cerr << "*** ABEND: underflow ***" << endl;
                return;
            } else if (result > 9999) {
                cerr << "*** ABEND: overflow ***" << endl;
                return;
            }

            // Store
            accumulator = result;

            ++instruction_counter; // Increment the instruction counter
            break;

        // Instruction 34: Divide a word in a specific memory location into the word in the accumulator (leave result in accumulator)
        case DIVIDE:

            // Make sure we are not attempting to divide by zero
            if (memory[operand] == 0) {
                cerr << "*** ABEND: attempted division by 0 ***" << endl;
                return;
            }

            // Store
            accumulator /= memory[operand];

            ++instruction_counter; // Increment the instruction counter
            break;

        // Instruction 41: Branch to a specific memory location.
        case BRANCH:
            instruction_counter = operand;
            break;

        // Instruction 43: Branch to a specific memory location if the accumulator is negative. 
        case BRANCHNEG:

            // Check if the value in the accumulator is negative, if it is, branch.
            if (accumulator < 0) {
                instruction_counter = operand;
            } else {
                ++instruction_counter; // If not, increment the instruction counter
            }
            break;

        // Instruction 42: Branch to a specific memory location if the accumulator is zero.
        case BRANCHZERO:

            // Check if the value in the accumulator is zero, if it is, branch.
            if (accumulator == 0) {
                instruction_counter = operand;
            } else {
                ++instruction_counter; // If not, increment the instruction counter
            }
            break;


        // Instruction 44: Halt, i.e., the program has completed its task. 
        case HALT:
            cout << "*** Simplesim execution terminated ***" << endl;
            done = true;
            return;

        // Invalid instruction
        default:
            cout << "*** ABEND: invalid opcode ***" << endl; 
            return;
        }

    }
    
    // Print successful termination message.
    cout << "*** Simplesim execution terminated ***" << endl;
}

/**
 * Prints the contents of the Simplesim's registers and memory.
 */
void simplesim::dump() const
{
    // Print registers.
    cout << endl << "REGISTERS:" << endl 
        <<  left <<  setw(24) << "accumulator:" <<  right <<  setw(5) <<  setfill('0') <<  internal <<  showpos << accumulator  << endl
        <<  setfill(' ') <<  left <<  setw(24) << "instruction_counter:"  << right << setw(2) << setfill('0') <<  noshowpos << instruction_counter  << endl 
        <<  setfill(' ') <<  left <<  setw(24) << "instruction_register:"  <<  right <<  setw(5) <<  setfill('0') <<  internal <<  showpos << instruction_register << endl
        <<  setfill(' ') <<  left <<  setw(24) << "operation_code:" <<  right << setw(2) << setfill('0') <<  noshowpos << operation_code << endl 
        <<  setfill(' ') <<  left <<  setw(24) << "operand:" << right << setw(2) << setfill('0') << operand << endl << endl << setfill(' ');

    // Print memory.
    
    // Output column labels 0-9
    cout << "MEMORY:" << endl;
    for (int i=0; i<=9; ++i) {
        if (i == 0) {
            cout <<  right <<  setw(8) << i;
        } else {
            cout <<  right <<  setw(6) << i;
        }
    }
    cout << endl;

    // Output row labels 0-90 and words in memory
    cout <<  right <<  setw(2) << 0 << " "; // This outputs the first row label (0), needed separately for correct formatting
    for (int i=0, j=10; i<100; ++i) {

        // Outputs the memory
        cout <<  right <<  setw(5) <<  setfill('0') <<  internal <<   showpos << memory[i] << " ";

        // Output the row labels when needed
        if((i+1) % 10 == 0 && j!=100) {
            cout << endl <<  noshowpos << j << " ";
            j+=10; // Increment row label
        }

    }
    // Reset the fill to whitespace
    cout << setfill(' ') << endl;
}
