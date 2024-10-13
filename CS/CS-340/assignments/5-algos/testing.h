
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef NIU_CSCI_340_GENALGO_TESTING_H
#define NIU_CSCI_340_GENALGO_TESTING_H

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

#include "gen-algo.h"

namespace testing {
  const std::vector< std::vector<int> > int_table{ 
    {  1,   2,   3,   4,   5}, 
    {200, 400,  30, 902,  70}, 
    { 31,  42,  69, 420,   6}, 
    { 50,  63,  99,  32,   7}, 
    { 33,  47,  56, 101,  42} 
  };

  const std::vector< std::vector<std::string> > str_table{ 
    { "This", "table", "is", "filled", "with" },  
    { "strings", "instead", "of", "integers", "so"},
    { "we", "can", "test", "displaying", "data"},
    { "like", "what", "would", "be", "read"}, 
    { "from", "the", "input", "files.", "!!!!" }
  };
  
  const std::vector< std::vector<std::string> > str_table2{ 
    { "Another", "table", "full", "of", "strings" },  
    { "that", "had some", "different", "lengths", "of"},
    { "strings", "was", "necessary", "to", "make"},
    { "a", "good", "test", "of", "the"}, 
    { "calc_width", "function", "you", "must", "do" }
  };
  
  const std::vector< std::vector<std::string> > str_table3{ 
    { "1.04", "2.40", "3.41", "0.57", "6.40" },  
    { "2.69", "4.20", "1.32", "2.18", "4.80" },
    { "3.41", "1.20", "3.14", "5.60", "9.23" },
    { "1.23", "4.56", "5.67", "6.78", "7.89" },
    { "0.69", "1.33", "2.33", "1.24", "5.12" }
  };
}

template <typename TABLE>
void test_print_table(const char * label, TABLE &table, const std::vector <int> & widths, bool leftalign) {
  std::cout << "**** TESTING print_table ON " << label << " ****\n";
  //std::cout << "  Narrowest row has " << table_min_cols(table) << " columns\n";
  //std::cout << "  Widest row has " << table_max_cols(table) << " columns\n";
  std::cout << "  Column Widths:\n";
  for(unsigned int col=0; col<widths.size(); ++col) {
    std::cout << "    Column " << col << ": " << widths[col] << " wide\n";
  }
  std::cout << "\n";
  std::cout << "  TABLE:\n";
  print_table(std::cout, table, widths, widths.size(), "    [ ", " | ", " ]", leftalign);
  std::cout << "\n";
}

template <typename FN>
void test_sorting(const char * label, const STR_TABLE &input, FN sortfn) {
  STR_TABLE temp(input);

  std::cout << "**** Testing sort - " << label << " ****\n";
  auto widths = calc_widths(temp);
  std::cout << "  Before sorting: \n";
  print_table(std::cout, temp, widths, widths.size(), "    [ ", " | ", " ]", true);

  for(unsigned int i=0; i<widths.size(); ++i) {
    sortfn(temp, i);
    std::cout << "  After sorting by column " << i << "\n";
    print_table(std::cout, temp, widths, widths.size(), "    [ ", " | ", " ]", true);
  }

  std::cout << "\n";

}

template <typename TABLE>
void test_calc_widths(const char * label, const TABLE &table, bool leftalign) {
  std::vector <int> widths = calc_widths(table);
  test_print_table(label, table, widths, leftalign);
}

void test_read_lines(const char * filename) {
  std::istream *input;
  std::ifstream file;
  if( !strcmp(filename, "-") ) {
    std::cout << "**** PRINTING STANDARD INPUT ****\n";
    input = &std::cin;
  }
  else {
    std::cout << "**** PRINTING FILE " << filename << " ****\n";
    file.open(filename);
    if( !file.is_open() ) {
      std::cout << "  Could not open file. Skipping.\n";
      return;
    }
    input = &file;
  }
  read_lines(*input, [] (const std::string & x) { std::cout << x << "\n"; } );
}

void test_split_string_greedy(const std::string &input, char delim) {
  std::cout << "**** TESTING split_string_greedy ****\n";
  std::cout << "Input String: \"" << input << "\"\n";
  std::cout << "Using delimiter '" << delim << "'\n";
  int i = 0;
  int count = split_string_greedy(input, [&i] (std::string &token) { 
      std::cout << "Token " << i << ") \"" << token << "\"\n";
      ++i;
      }, delim);
  std::cout << "**** DONE - FOUND " << count << " TOKENS ****\n\n";
}

void test_split_string_strict(const std::string &input, char delim) {
  std::cout << "**** TESTING split_string_strict ****\n";
  std::cout << "Input String: \"" << input << "\"\n";
  std::cout << "Using delimiter '" << delim << "'\n";
  int i = 0;
  int count = split_string_strict(input, [&i] (std::string &token) { 
      std::cout << "Token " << i << ") \"" << token << "\"\n";
      ++i;
      }, delim);
  std::cout << "**** DONE - FOUND " << count << " TOKENS ****\n\n";
}

void test_load_tsv(const char * label, const std::string & filename) {
  auto x = load_tsv(filename);

  // find out the widths of the columns in the loaded file
  auto widths = calc_widths(x);
  test_print_table(label, x, widths, true);
}

int get_answer(const std::string &prompt) {
  int input;
  std::cout << prompt;
  
  if(std::cin >> input) {
    return input;
  }
  else {
    do {
      if(std::cin.eof()) return -1;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << prompt;
    }
    while( !(std::cin >> input) );
  
    return input;
  }
  
}

void test_load_tsv_and_sort(const char * label, const std::string & filename) {
  auto x = load_tsv(filename);

  // find out the widths of the columns in the loaded file
  auto widths = calc_widths(x);
  int minw = table_min_cols(x); 

  std::cout << "Table read from file, no sorting performed:\n";
  print_table(std::cout, x, widths, minw, "    [ ", " | ", " ]", true);
  std::cout << std::endl;

  const std::string colprompt = "Which column do you want to sort on? (-1 to quit) ";
  const std::string sortprompt = "Sort how? 1) Alphabetical 2) Numeric: ";
  int column, sortmethod;

  // goes until EOF or -1
  while( (column = get_answer(colprompt)) || true) {
    if(column < 0) { return; }
    else if(column < minw) {
      do {
	sortmethod = get_answer(sortprompt);
      } while(sortmethod != 1 && sortmethod != 2); 

      std::cout << std::endl;

      if(sortmethod == 1) {
	std::cout << "  Sorting alphabetically on column " << column << "\n";
        table_sort_alpha(x, column);  
	print_table(std::cout, x, widths, minw, "    [ ", " | ", " ]", true); 
      }
      else if(sortmethod == 2) {
	std::cout << "  Sorting numerically on column " << column << "\n";
        table_sort_numer(x, column);  
	print_table(std::cout, x, widths, minw, "    [ ", " | ", " ]", false); 
      }
      else {
        std::cout << "  Not sorting, as sorting method " << sortmethod << " is not valid.\n";
      }
      std::cout << std::endl;
    }
    else std::cout << "  Column number " << column << " is outside of the bounds of this table.\n";
  }

}


#endif
