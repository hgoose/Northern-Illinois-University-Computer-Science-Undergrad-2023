/******************************************************************************
 * This file is provided as a part of NIU CSCI 340 Assignment 2. IT IS NOT TO *
 * BE CHANGED. To complete the assignment, please implement the methods that  *
 * are declared here in the file `340list.h`                                  *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/

#include <iostream>
#include <vector>
#include "assign2-algos.h"

int main(int argc, char *argv[]) {

  // default value in case there isn't one supplied otherwise
  std::string source = " Default test string:   you can use  command-line arguments to supply a different string. Markdown emojis :smile::laughing:"; 
  int i;

  // if first command line option is "-", read text from stdin
  if(argc > 1) { // we have a command line argument

    if(argv[1][0] == '-' && argv[1][1] == 0) {
      // command line argument is -, read from stdin
    
      // this uses the stringstream to grab all data from stdin until EOF (^D on terminal)
      std::ostringstream ss;
      ss << std::cin.rdbuf();
   
      source = ss.str();
    }
    else { // take the first command line argument and use that as the source for splitting
      source = argv[1];
    }
  }
 
  std::cout << "BEGIN SOURCE STRING\n";
  std::cout << source;
  std::cout << "\nEND SOURCE STRING\n\n";

  // Split the source string in several ways.
  
  std::cout << "SPACE ' ' AS DELIMITER\n";

  /***************************************************************************
   *                                                                         *
   * First test, strict with space                                           *
   *                                                                         *
   ***************************************************************************/
  std::cout << "  String tokenization with \"strict\" delimiter ' '\n";
  auto s_info = get_next_token_strict(source.begin(), source.end(), ' '); 

  i = 0;
  while(s_info.t_begin != source.end() )  {
    std::cout << "    " << std::setw(4) << i << ": ";
    // print current token
    print_range(std::cout, s_info.begin(), s_info.end(), "\"", "", "\"\n", 0);

    // find next token
    s_info = get_next_token_strict(s_info.t_next, source.end(), ' '); 
    ++i;
  }
  std::cout << "  Found " << i << " token(s) in the string.\n\n";

  /***************************************************************************
   *                                                                         *
   * Second test, greedy with space                                          *
   *                                                                         *
   ***************************************************************************/
  std::cout << "  String tokenization with \"greedy\" delimiter ' '\n";
  s_info = get_next_token_greedy(source.begin(), source.end(), ' '); 
 
  i = 0;
  while(s_info.t_begin != source.end() )  {
    std::cout << "    " << std::setw(4) << i << ": ";
    // print current token
    print_range(std::cout, s_info.begin(), s_info.end(), "\"", "", "\"\n", 0);

    // find next token
    s_info = get_next_token_greedy(s_info.t_next, source.end(), ' '); 
    ++i;
  }
  std::cout << "  Found " << i << " token(s) in the string.\n\n";

  std::cout << "COLON ':' AS DELIMITER\n";

  /***************************************************************************
   *                                                                         *
   * Third test, strict with colon                                           *
   *                                                                         *
   ***************************************************************************/
  std::cout << "  String tokenization with \"strict\" delimiter ':'\n";
  s_info = get_next_token_strict(source.begin(), source.end(), ':'); 
 
  i = 0;
  while(s_info.t_begin != source.end() )  {
    std::cout << "    " << std::setw(4) << i << ": ";
    // print current token
    print_range(std::cout, s_info.begin(), s_info.end(), "\"", "", "\"\n", 0);

    // find next token
    s_info = get_next_token_strict(s_info.t_next, source.end(), ':'); 
    ++i;
  }
  std::cout << "  Found " << i << " token(s) in the string.\n\n";

  /***************************************************************************
   *                                                                         *
   * Fourth test, greedy with colon                                          *
   *                                                                         *
   ***************************************************************************/
  std::cout << "  String tokenization with \"greedy\" delimiter ':'\n";
  s_info = get_next_token_greedy(source.begin(), source.end(), ':'); 
 
  i = 0;
  while(s_info.t_begin != source.end() )  {
    // print current token
    std::cout << "    " << std::setw(4) << i << ": ";
    print_range(std::cout, s_info.begin(), s_info.end(), "\"", "", "\"\n", 0);

    // find next token
    s_info = get_next_token_greedy(s_info.t_next, source.end(), ':'); 
    ++i;
  }
  std::cout << "  Found " << i << " token(s) in the string.\n";

  return 0;

}

