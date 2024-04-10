//*******************************************************************
//
//  scc.cpp
//  CSCI 241 Assignment 15
//  Created by Nate Warner z2004109
//
//********************************************************************

// Includes
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cctype>
#include "inpost.h"
#include "sml.h"
#include "scc.h"

// Using directives
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::internal;
using std::istringstream;
using std::noshowpos;
using std::setfill;
using std::setw;
using std::showpos;
using std::string;


/**
 * Constructor - initializes memory and flags arrays.
 */
scc::scc()
{
    // Initializes the memory array to 7777, flags array to -1
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = DEFAULT;
        flags[i] = -1;
    }
}

/**
 * Performs first pass of compilation.
 */
void scc::first_pass()
{
    string buffer, command;
    int line_number;

    // Grab the entire line
    while (getline(cin, buffer))
    {
        // Stream to grab each word in line
        istringstream iss(buffer);

        // Read the line number.
        iss >> line_number;

        // Add line number to the symbol table.
        symbol_table[next_symbol_table_idx].symbol = line_number;
        symbol_table[next_symbol_table_idx].type = 'L';
        symbol_table[next_symbol_table_idx++].location = next_instruction_addr;

        // Read the command.
        iss >> command;

        // Deduce each command and handle accordingly
        if (command == "input")
        {
            // Code to process "input" command.
            handle_input(iss);
        }
        else if (command == "data")
        {
            // Code to process "data" command.
            handle_data(iss);
        }
        else if (command == "let")
        {
            // Code to process "let" command.
            handle_let(iss, buffer);
        }
        else if (command == "goto")
        {
            // Code to process "goto" command.
            handle_goto(iss);
        }
        else if (command == "if")
        {
            // Code to process "if" command.
            handle_if(iss);
        }
        else if (command == "print")
        {
            // Code to process "print" command.
            handle_print(iss);
        }
        else if (command == "rem")
        {
            // Code to process "rem" command.
        }
        else
        {
            // Code to process "end" command.
            handle_end();
        }
    }
}


/**
 * Performs second pass of compilation.
 */
void scc::second_pass()
{
    // int index;

    // Compute address of first element of the stack.
    int stack_start = next_const_or_var_addr - 1;


    // Get the right operand
    int right_operand_location = next_const_or_var_addr; 

    // Loop through flags and memory array.
    for (int i = 0; i < next_instruction_addr; i++)
    {
        // If an instruction is marked incomplete in the flags
        // array, we complete it.
        if (flags[i] != -1)
        {
            // Line number forward references
            if (flags[i] > 0)
            {
                // Search the symbol table for the line number to find its memory location
                int lineNum = flags[i];
                int location = search_symbol_table(lineNum, 'L');
                if (location != -1)
                {
                    // Update the instruction with the correct memory location
                    memory[i] += symbol_table[location].location;
                }
            }
            // Right operand
            else if (flags[i] == -2)
            {
                memory[i] += right_operand_location;
            }
            // Memory location in the stack
            else if (flags[i] < -2)
            {
                int idx = -3 - flags[i]; // Calculate stack index
                int stack_address = stack_start - idx; // Calculate stack address

                // Check if we ran out of stack space
                if (stack_address <= next_instruction_addr)
                {
                    cout << "*** ERROR: insufficient stack space ***\n";
                    exit(1);
                }
                // Update memory with stack address
                memory[i] += stack_address;
            }
        }
    }
}

/**
 * Prints memory and data for the compiled SML program.
 */
void scc::print_program() const
{
    cout << showpos << internal << setfill('0');

    // Print memory.
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        cout << setw(5) << memory[i] << endl;
    }

    cout << noshowpos << "-99999\n";

    // Print data.

    for (int i = 0; i < ndata; i++)
    {
        cout << data[i] << endl;
    }
}

/**
 * Generates code for an "input" instruction.
 *
 * @param iss Input stringstream used to read the remainder of
 *            the instruction.
 */
void scc::handle_input(istringstream& iss)
{
    // Grab the symbol
    string symbol;
    iss >> symbol;

    // Get the location in memory
    int location = get_symbol_location(symbol);

    // Write the instruction to memory
    memory_check();
    memory[next_instruction_addr++] = READ * 100 + location;
}

/**
 * Generates code for a "data" instruction.
 *
 * @param iss Input stringstream used to read the remainder of
 *            the instruction.
 */
void scc::handle_data(std::istringstream& iss)
{
    // Grab the contant
    int number;
    iss >> number;

    // Add the constant to data arary
    data_check();
    data[ndata++] = number;
}

/**
 * Generates code for a "let" instruction.
 *
 * @param iss Input stringstream used to read the remainder of
 *            the instruction.
 * @param buffer Input buffer from which to extract an infix
 *               expression so it can be converted to postfix.
 */
void scc::handle_let(istringstream& iss, const string& buffer)
{
    // Search for "=" in buffer that contains infix string.
    size_t index = buffer.find_first_of("=");

    // Extract the infix string that follows the '=' operator.
    string infix = buffer.substr(index + 2, string::npos);

    // Extract the first variable
    string symbol;
    iss >> symbol;

    // Get the location in memory of the first variable
    int location = get_symbol_location(symbol);

    // Convert the postfix expression to infix
    string postfix = convert(infix);

    // Define stack index
    int next_stack_idx = 0;

    // Stream to grab operands and operator
    string tmp;
    istringstream ps(postfix);

    while (ps >> tmp) {

        // If we have a constant of variable
        if (isdigit(tmp[0]) || isalpha(tmp[0])) {

            // Get the location of the operand
            int operand_location = get_symbol_location(tmp);

            // Write load instruction
            memory_check();
            memory[next_instruction_addr++] = LOAD * 100 + operand_location;

            // Write partial store instruction
            memory_check();
            memory[next_instruction_addr] = STORE * 100;
            flags[next_instruction_addr++] = -3 - next_stack_idx;
            ++next_stack_idx;

        // Addition operator
        } else if (tmp == "+") {

            // Write partial load (pop the stack)
            memory_check();
            memory[next_instruction_addr] = LOAD * 100; 
            next_stack_idx--;
            flags[next_instruction_addr++] = -3 - next_stack_idx;

            // Parital add 
            memory_check();
            memory[next_instruction_addr] = ADD * 100; 
            next_stack_idx--;
            flags[next_instruction_addr++] = -3 - next_stack_idx;

            // Partial store
            memory_check();
            memory[next_instruction_addr] = STORE * 100;
            flags[next_instruction_addr++] = -3 - next_stack_idx;
            next_stack_idx++;

        // Multiplication operator
        } else if (tmp == "*") {

            // Write partial load
            memory_check();
            memory[next_instruction_addr] = LOAD * 100; 
            next_stack_idx--;
            flags[next_instruction_addr++] = -3 - next_stack_idx;

            // Write partial multiply
            memory_check();
            memory[next_instruction_addr] = MULTIPLY * 100; 
            next_stack_idx--;
            flags[next_instruction_addr++] = -3 - next_stack_idx;

            // Write partial store
            memory_check();
            memory[next_instruction_addr] = STORE * 100;
            flags[next_instruction_addr++] = -3 - next_stack_idx;
            next_stack_idx++;

        // Subtraction operator
        } else if (tmp == "-") {

            // Partial load
            memory_check();
            memory[next_instruction_addr] = LOAD * 100; 
            next_stack_idx--;
            flags[next_instruction_addr++] = -3 - next_stack_idx;

            // Partial store
            memory_check();
            memory[next_instruction_addr] = STORE * 100;
            flags[next_instruction_addr++] = -2;

            // Partial load
            memory_check();
            memory[next_instruction_addr] = LOAD * 100;
            next_stack_idx--;
            flags[next_instruction_addr++] = -3 - next_stack_idx;

            // Partial subtract
            memory_check();
            memory[next_instruction_addr] = SUBTRACT * 100;
            flags[next_instruction_addr++] = -2;

            // Partial store
            memory_check();
            memory[next_instruction_addr] = STORE * 100;
            flags[next_instruction_addr++] = -3 - next_stack_idx;
            next_stack_idx++;

        // Division operator
        } else if (tmp == "/") {

            // Partial load
            memory_check();
            memory[next_instruction_addr] = LOAD * 100; 
            next_stack_idx--;
            flags[next_instruction_addr++] = -3 - next_stack_idx;

            // Partial store
            memory_check();
            memory[next_instruction_addr] = STORE * 100;
            flags[next_instruction_addr++] = -2;

            // Partial load
            memory_check();
            memory[next_instruction_addr] = LOAD * 100;
            next_stack_idx--;
            flags[next_instruction_addr++] = -3 - next_stack_idx;

            // Partial divide
            memory_check();
            memory[next_instruction_addr] = DIVIDE * 100;
            flags[next_instruction_addr++] = -2;

            // Partial store
            memory_check();
            memory[next_instruction_addr] = STORE * 100;
            flags[next_instruction_addr++] = -3 - next_stack_idx;
            next_stack_idx++;
        }
    }

    // Partial load 
    memory_check();
    memory[next_instruction_addr] = LOAD * 100; 
    flags[next_instruction_addr++] = -3;  // Top of stack

    // Full store into variable of let command
    memory_check();
    memory[next_instruction_addr++] = STORE * 100 + location;

}

/**
 * Generates code for a "goto" instruction.
 *
 * @param iss Input stringstream used to read the remainder of
 *            the instruction.
 */
void scc::handle_goto(istringstream& iss)
{
    // Grab the line number
    int line_no;
    iss >> line_no;

    // Search the symbol table for location in symbol table
    int location = search_symbol_table(line_no, 'L');

    // If the location is not -1, the line already exists and we can write a full instruction
    memory_check();
    if (location != -1) {

        // Get the memory location and add instruction to memory
        int memory_location  = symbol_table[location].location;
        memory[next_instruction_addr] = BRANCH * 100 + memory_location; 

    // Line does not exist yet, we write a partial instruction
    } else {

        // Write partial instruction
        memory[next_instruction_addr] = BRANCH * 100;
        flags[next_instruction_addr] = line_no;
    }
    ++next_instruction_addr;
}

/**
 * Generates code for an "if" instruction.
 *
 * @param iss Input stringstream used to read the remainder of
 *            the instruction.
 */
void scc::handle_if(istringstream& iss)
{

    // Grab contents of statement
    string lop, relop, rop, goto_statement;
    int line_num;
    iss >> lop >> relop >> rop >> goto_statement >> line_num;

    // Left operand location in memory
    int l_lop = get_symbol_location(lop);
    // Right operand location in memory
    int l_rop = get_symbol_location(rop);
    // Line number location in symbol table
    int l_ln = search_symbol_table(line_num, 'L');

    if (relop == "<") {
        // Load at location of left operand
        memory_check();
        memory[next_instruction_addr++] = LOAD * 100 + l_lop;

        // Subtract at location of right operand
        memory_check();
        memory[next_instruction_addr++] = SUBTRACT * 100 + l_rop;

        // Paths depending on if line number exsits yet
        if (l_ln != -1) {
            // If it does, we write a full branchneg instruction at location of line number
            memory_check();
            memory[next_instruction_addr++] = BRANCHNEG * 100 + symbol_table[l_ln].location;
        } else {
            // Else, we write a partial branchneg
            memory_check();
            memory[next_instruction_addr] = BRANCHNEG * 100;
            flags[next_instruction_addr++] = line_num;
        }
    } else if (relop == ">") {
        // Load at location of right operand
        memory_check();
        memory[next_instruction_addr++] = LOAD * 100 + l_rop;

        // Subtract at location of left operand
        memory_check();
        memory[next_instruction_addr++] = SUBTRACT * 100 + l_lop;

        // Same as less than operator
        if (l_ln != -1) {
            memory_check();
            memory[next_instruction_addr++] = BRANCHNEG * 100 + symbol_table[l_ln].location;
        } else {
            memory_check();
            memory[next_instruction_addr] = BRANCHNEG * 100;
            flags[next_instruction_addr] = line_num;
            ++next_instruction_addr;
        }
    } else if (relop == "==") {
        // Load at location of left operator
        memory_check();
        memory[next_instruction_addr++] = LOAD * 100 + l_lop;

        // Subtract at location of right operator
        memory_check();
        memory[next_instruction_addr++] = SUBTRACT * 100 + l_rop;

        if (l_ln != -1) {
            // If the line number exists, write full branchzero
            memory_check();
            memory[next_instruction_addr++] = BRANCHZERO * 100 + symbol_table[l_ln].location;
        } else {
            // Else, write partial branchzero
            memory_check();
            memory[next_instruction_addr] = BRANCHZERO * 100;
            flags[next_instruction_addr++] = line_num;
        }
    } else if (relop == ">=") {
        // Load at location of right operand
        memory_check();
        memory[next_instruction_addr++] = LOAD * 100 + l_rop;

        // Subtract at location of left operand
        memory_check();
        memory[next_instruction_addr++] = SUBTRACT * 100 + l_lop;

        if (l_ln != -1) {
            // Full branchneg at location of line number
            memory_check();
            memory[next_instruction_addr++] = BRANCHNEG * 100 + symbol_table[l_ln].location;

            // Full branchzero at location of line number
            memory_check();
            memory[next_instruction_addr++] = BRANCHZERO * 100 + symbol_table[l_ln].location; 
        } else {
            // Else, some partials
            memory_check();
            memory[next_instruction_addr] = BRANCHNEG * 100; 
            flags[next_instruction_addr++] = line_num;

            memory_check();
            memory[next_instruction_addr] = BRANCHZERO * 100; 
            flags[next_instruction_addr++] = line_num;
        }
    // Similar to >=
    } else if (relop == "<=") {
        memory_check();
        memory[next_instruction_addr++] = LOAD * 100 + l_lop;

        memory_check();
        memory[next_instruction_addr++] = SUBTRACT * 100 + l_rop;

        if (l_ln != -1) {
            memory_check();
            memory[next_instruction_addr++] = BRANCHNEG * 100 + symbol_table[l_ln].location;
            memory_check();
            memory[next_instruction_addr++] = BRANCHZERO * 100 + symbol_table[l_ln].location;
        } else {
            memory_check();
            memory[next_instruction_addr] = BRANCHNEG * 100; 
            flags[next_instruction_addr++] = line_num;

            memory_check();
            memory[next_instruction_addr] = BRANCHZERO * 100; 
            flags[next_instruction_addr++] = line_num;
        }

    /*<remark> 
    
    </remark>*/
    } else if (relop == "!=") {

        memory_check();
        memory[next_instruction_addr++] = LOAD * 100 + l_lop;

        memory_check();
        memory[next_instruction_addr++] = SUBTRACT * 100 + l_rop;

        // If the result of the subtraction is zero, we branch ahead two instructions
        memory_check();
        memory[next_instruction_addr] = BRANCHZERO * 100 + (next_instruction_addr + 2);
        next_instruction_addr++;

        // Not zero, we branch to line number (or partial)
        if (l_ln != -1) {
            memory_check();
            memory[next_instruction_addr++] = BRANCH * 100 + symbol_table[l_ln].location;
        } else {
            memory_check();
            memory[next_instruction_addr] = BRANCH * 100;
            flags[next_instruction_addr++] = line_num;
        }
    }
}

/**
 * Generates code for a "print" instruction.
 *
 * @param iss Input stringstream used to read the remainder of
 *            the instruction.
 */
void scc::handle_print(istringstream& iss)
{
    // Grab the symbol
    string symbol;
    iss >> symbol;

    // Get the location in memory of the symbol
    int location = get_symbol_location(symbol);

    // Write the instruction to memory
    memory_check();
    memory[next_instruction_addr++] = WRITE * 100 + location;
}

/**
 * Generates code for an "end" instruction.
 */
void scc::handle_end()
{
    // We simply write a halt instruction
    memory_check();
    memory[next_instruction_addr++] = HALT * 100;
}

/**
 * Checks to make sure there is room in the memory array
 * to add another instruction.
 */
void scc::memory_check() const
{
    // If the number of instructions plus constants and variables
    // exceeds the number of elements in the memory array, print an 
    // error message and exit.
    if (next_instruction_addr >= MEMORY_SIZE ||
        next_instruction_addr > next_const_or_var_addr)
    {
        cout << "*** ERROR: ran out of Simplesim memory ***\n";
        exit(1);
    }
}

/**
 * Checks to make sure there is room in the data array
 * to add another data value.
 */
void scc::data_check() const
{
    // If the number of data items exceeds the number of 
    // elements in the data array, print an error message and
    // exit.
    if (ndata >= MEMORY_SIZE)
    {
        cout << "*** ERROR: too many data lines ***\n";
        exit(1);
    }
}

/**
 * Checks whether the top of the stack has crossed into the region
 * of the memory array that contains instructions.
 *
 * @param location Location of the top of the stack.
 */
void scc::stack_space_check(int location) const
{
    // If the top of the stack has hit the instructions in
    // the memory array, print an error message and exit.
    if (location < next_instruction_addr)
    {
        cout << "*** ERROR: insufficient stack space ***\n";
        exit(1);
    }
}

/**
 * Gets the location of a constant or variable, adding it to the 
 * symbol table and memory if necessary.
 *
 * @param token The symbol to locate.
 *
 * @return The symbol's location.
 */
int scc::get_symbol_location(const string& token)
{
    int location, symbol;
    char type;

    if (islower(token[0]))
    {
        // This is a variable.
        symbol = token[0];
        type = 'V';
    }
    else
    {
        // This is an integer constant.
        symbol = stoi(token);
        type = 'C';
    }

    int index = search_symbol_table(symbol, type);

    if (index == -1)
    {
        // This symbol is not in the symbol table. Add it to
        // the symbol table.
        location = next_const_or_var_addr;

        symbol_table[next_symbol_table_idx].symbol = symbol;
        symbol_table[next_symbol_table_idx].type = type;
        symbol_table[next_symbol_table_idx].location = location;
        next_symbol_table_idx++;

        memory_check();
        if (type == 'V')
            memory[location] = 0;
        else
            memory[location] = symbol;

        next_const_or_var_addr--;
    }
    else
    {
        // This symbol is in the symbol table at array element
        // index.
        location = symbol_table[index].location;
    }

    return location;
}

/**
 * Searches the symbol table for a symbol with the specified type.
 * 
 * @param symbol The symbol to search for.
 * @param type The type of the symbol to search for.
 *
 * @return The index of the symbol table entry where the symbol'
 *         was found or -1 if the search fails.
 *
 * @note Uses the linear search algorithm.
 */
int scc::search_symbol_table(int symbol, char type) const
{
    for (int i = 0; i < next_symbol_table_idx; i++)
    {
        if (symbol == symbol_table[i].symbol && type == 
            symbol_table[i].type)
        {
            return i;
        }
    }

    return -1;
}
