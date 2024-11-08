//***************************************************************************
//
//  gen-algo.h 
//  CSCI 340 Assignment 5 
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

#ifndef NIU_CSCI340_GEN_ALGO_IMPL_H
#define NIU_CSCI340_GEN_ALGO_IMPL_H

#include "gen-algo.decl.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <functional>

using std::string;
using std::invoke;

/**
 * Reads lines from an input stream and passes each line to a callback.
 *
 * @param instream Input stream to read from.
 * @param linecb Callback function to handle each line.
 *
 * @return Number of lines read.
 */
template <typename FN>
size_t read_lines(std::istream &instream, FN linecb) {

    // Variable to hold line and getline count
    string get; size_t count{0};

    // While getline succeeds in getting a line
    while (getline(instream, get)) { 
        // Pass the line to the callable
        linecb(get);
        ++count;
    }
    return count;
}


/**
 * Splits a string based on a delimiter, passes each token to a callback.
 * Stops processing at exact matches.
 *
 * @param instring Input string to split.
 * @param tokencb Callback function to handle each token.
 * @param delim Delimiter character to split by.
 * @return Number of tokens found.
 */
template <typename FN>
size_t split_string_strict(const std::string&instring, FN tokencb, char delim) {

    // Iterator to start and end of string
    string::const_iterator start = instring.begin(), end = instring.end();

    // Token count
    size_t count{0};

    // While we are not at the end of the string
    while (start != end) {

        // Find a delimiter
        string::const_iterator t = std::find(start,end, delim);

        // If found
        if (t != end) {
            // Create the substr
            string stmp(start,t);

            // Invoke callable with token
            invoke(tokencb, stmp);
            
            // Set start to one past delim (start of next token)
            start = t+1;
            ++count;

        // Else iterator is at the end of string, pass token: current pos to end 
        // Might be the whole string
        } else {
            // Create the substr
            string stmp(start, t);

            // Invoke callable with token
            invoke(tokencb, stmp); 
            ++count;

            // Done, string is parsed
            break; 
        }
    }
    // Return the token count
    return count;
}


/**
 * Splits a string based on a delimiter, passes non-whitespace tokens to a callback.
 * Ignores tokens that are only whitespace.
 *
 * @param instring Input string to split.
 * @param tokencb Callback function to handle each token.
 * @param delim Delimiter character to split by.
 * @return Number of tokens found.
 */
template <typename FN>
size_t split_string_greedy(const std::string &instring, FN tokencb, char delim) {

    // Get iterators to start and end of string
    string::const_iterator start = instring.begin(), end = instring.end();

    size_t count{0};

    // For the entire string
    while (start != end) {

        // Try to find a delimiter
        string::const_iterator t = std::find(start,end, delim);

        // If found
        if (t != end) {
            
            // Construct the substr
            string snew(start, t);

            // Check if the token is not just whitespace (don't care about it)
            if ( !(all_of(snew.begin(), snew.end(), [] (char c) { return c == ' '; }))) {

                // Substr is not all whitespace, give to callable
                invoke(tokencb, snew);

                // Advance start to start of next token
                start = t + 1;
                ++count;

            // Token was just whitespace, skip
            } else {++start;}
        
        // No delim found, substr is then current pos to end
        } else {
            // Construct string
            string snew(start,t);

            // Pass off to callable
            invoke(tokencb, snew);
            ++count;
            break; // Done
        }
    }
    // Return token count
    return count;
}


/**
 * Prints a formatted table to an output stream.
 *
 * @param ost Output stream to print to.
 * @param table Table data to print.
 * @param widths Vector of column widths.
 * @param maxcol Maximum number of columns to print.
 * @param pre Prefix to print before each row.
 * @param sep Separator between columns.
 * @param post Suffix to print after each row.
 * @param leftalign Whether to left-align the text in each column.
 */
template <typename TABLE, typename ARRLIKE>
void print_table(std::ostream & ost, 
                 const TABLE & table, 
                 const ARRLIKE & widths, 
                 unsigned int maxcol, 
                 const std::string &pre, 
                 const std::string &sep,
                 const std::string &post,
                 bool leftalign) 
{
    unsigned colcount{0}, widthidx = 0;

    // For each row
    for (auto it = table.begin(); it!=table.end(); ++it) {

        // Reset colcount and widthidx for each row
        colcount=0;
        widthidx = 0;

        // Pre output
        ost << pre;

        // For each string in the row
        std::for_each(it->begin(), it->end(), [&] (const auto& s) {
                // If we still have output allowance, output the entry
                if (colcount != maxcol) {
                    ost << (leftalign ? std::left : std::right) << std::setw(widths[widthidx++]) << s << (colcount == (maxcol - 1) ? "" : sep);
                    ++colcount;
                }
        });
        // Post output
        ost << post << '\n';
    }
}


/**
 * Finds the row with the smallest width
 *
 * @param table Table of strings.
 * @return The width of the smallest row
 */
int table_min_cols(const STR_TABLE &table) {

    // Assume row with the smallest width is the first
    int min = table[0].size();
    
    // For row 1 to end 
    std::for_each(table.begin() + 1, table.end(), [&] (const auto& row) {
            // Check if row size is smaller than current min
            if ((int) row.size() < min) min = row.size();
    });
    return min;
}


/**
 * Finds the largest string width in each column
 *
 * @param table Table of strings.
 * @return Vector of widths
 */
template <typename STR_TABLE>
std::vector<int> calc_widths(const STR_TABLE & table) {

    // Vector to house the largest string widths in each column
    std::vector<int> biggest_widths;

    // Get the number of cols
    int cols = table[0].size();

    int biggest{0};
    // For each col
    for (int i=0; i<cols; ++i) {

        // Assume biggest is the first column entry
        biggest = table[0][i].size();

        // For each row
        for_each(table.begin(), table.end(), [&](const auto& row) {

                // Get the entry size
                int tmp = row[i].size();

                // Check if its bigger than current biggest
                if (tmp > biggest) {
                    biggest = tmp;
                }
        });

        // Push the biggest found to vector
        biggest_widths.push_back(biggest);
    }
    // Return vector
    return biggest_widths;
}


/**
 * Loads a tab-separated values (TSV) file into a table.
 *
 * @param filename Path to the file.
 * @return Table loaded from the file.
 */
STR_TABLE load_tsv(const std::string & filename) {

    // STR TABLE to hold file contents
    STR_TABLE table;

    // If stream with passed filename
    std::ifstream input(filename);

    // Call readlines with input, and lambda
    // lambda takes a string, readlines calls this lambda with each line grabbed by getline
    // this gives us access to the string passed. Thus, we can invoke split string with it
    read_lines(input, [&] (const string& s) -> void{
            // Create a vector to hold the tokens, gets reset for each line in file
            std::vector<string> tmp;

            // Invoke split_string_strict with each line in file, and a lambda 
            // that takes a string. Split string with invoke this lambda with each token found in a line
            // this gives us access to the token, and we can push to the vector
            split_string_strict(s,[&] (const string& substr) {
                    tmp.push_back(substr);

            },'\t');

            // Line is parsed, push to table
            table.push_back(tmp);
    });
    return table;
}


/**
 * Sorts a table alphabetically by a specified column.
 *
 * @param table Table of strings.
 * @param col Column to sort by.
 */
void table_sort_alpha(STR_TABLE & table, unsigned int col) {
    // Invoke sort with the entire table, sort based on column entries
    std::sort(table.begin(), table.end(), [&col] (const auto& a, const auto& b) -> bool {
            return a[col] < b[col];
    });
}


/**
 * Sorts a table numerically by a specified column.
 * Falls back to alphabetical sort if the column contains non-numeric data.
 *
 * @param table Table of strings.
 * @param col Column to sort by.
 */
void table_sort_numer(STR_TABLE & table, unsigned int col) {
    // Invoke sort with entire table, try to sort numerically
    // If stod throws an error, we must have tried to sort a column numerically that housed no numbers
    // in this case, we catch the error and sort alphabetically instead.
    std::sort(table.begin(), table.end(), [&col] (const auto& a, const auto& b) -> bool {
            // Try to convert the string into a double, if we succeed, we can sort numerically
            try {
                return stod(a[col]) < stod(b[col]);
            // Stod failed, catch and sort alphabetically
            } catch (const std::invalid_argument& e) {
                return a[col] < b[col];
            }
    });
}
#endif
