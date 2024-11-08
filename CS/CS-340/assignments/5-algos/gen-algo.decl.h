
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef NIU_CSCI340_GEN_ALGO_DECL_H
#define NIU_CSCI340_GEN_ALGO_DECL_H

#include <iostream>
#include <vector>
#include <string>

typedef std::vector < std::vector < std::string > > STR_TABLE;

template <typename FN>
size_t read_lines(std::istream &instream, FN linecb);

template <typename FN>
size_t split_string_strict(const std::string &instring, FN tokencb, char delim);

template <typename FN>
size_t split_string_greedy(const std::string &instring, FN tokencb, char delim);

template <typename TABLE, typename ARRLIKE>
void print_table(std::ostream & ost, 
                 const TABLE & table, 
                 const ARRLIKE & widths, 
                 unsigned int maxcol, 
                 const std::string &pre, 
                 const std::string &sep,
                 const std::string &post,
                 bool leftalign);

int table_min_cols(const STR_TABLE &table);

template <typename STR_TABLE>
std::vector <int> calc_widths(const STR_TABLE & table);

STR_TABLE load_tsv(const std::string & filename);

void table_sort_alpha(STR_TABLE & table, unsigned int col);

void table_sort_numer(STR_TABLE & table, unsigned int col);

#endif

