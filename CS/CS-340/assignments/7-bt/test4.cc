
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>

#include "xml.h"

#ifndef VERBOSE
#define VERBOSE (false)
#endif

const char * default_filename = "input/testing.xml";

void test_load_and_print(std::istream &input, const char * label, bool verbose) {
  using namespace std;
  xml_tree_state state;
  cout << "********************************************************************************\n";
  cout << "* Parsing and Printing - " << label << "\n";
  if(verbose) cout << "* - Running parse_xml - verbose on, it's ok to print things here.\n";
  else        cout << "* - Running parse_xml - verbose debug info off, nothing should show\n";
  cout << "********************************************************************************\n";
  parse_xml(input, state, verbose);
  cout << "\n"; 
  cout << "********************************************************************************\n";
  cout << "* - Done parsing. Calling xml_print_subtree on resulting tree.\n";
  cout << "********************************************************************************\n";
  xml_print_subtree(state.root, cout); 
  cout << "\n\n";
}

// Use `parse_xml` and `print_xml_tree` the whole tree generated.
int main(int argc, char *argv[]) {
  using namespace std;
  char labelbuf[256];

  cout << "********************************************************************************\n";
  cout << "* test4 - Parse an XML file to build a tree, and then convert it back to XML. \n"; 
  cout << "*                              \n"; 
  cout << "*   If called without command line parameters, it will load the default file, \n"; 
  cout << "* which is \"" << default_filename << "\". \n"; 
  cout << "*   If command line parameters are supplied, it will treat them as files, unless\n"; 
  cout << "* the filename is \"-\", in which case standard input is used. The data from    \n"; 
  cout << "* each source is parsed to a tree, and then printed.                            \n"; 
  cout << "*   Your result should basically match the input file, but with whitespace \n"; 
  cout << "* removed, and all attributes in alphabetical order because of the sorting from\n";
  cout << "* being stored in an STL map.\n"; 
  //cout << "********************************************************************************\n";
  if(argc > 1) { // we have command line arguments
    for(int i=1; i<argc; ++i) { // for each argument
      if(!strcmp(argv[i], "-")) { // use stdin
        snprintf(labelbuf, 255, "Command Line Argument %d - stdin", i);
        test_load_and_print(std::cin, labelbuf, (VERBOSE)); 
      }
      else { // use filename
        ifstream file(argv[i]); 
        if(file.is_open()) {
          snprintf(labelbuf, 255, "Command Line Argument %d - \"%s\"", i, argv[i]);
          test_load_and_print(file, labelbuf, (VERBOSE));
        }
        else {
          cout << "Could not open file \"" << argv[i] << "\". Skipping. \n";
        }
      }
    }
  }
  else { // no command line arguments - default file
    ifstream file(default_filename); 
    if(file.is_open()) {
      snprintf(labelbuf, 255, "Default File - \"%s\"", default_filename);
      test_load_and_print(file, labelbuf, (VERBOSE)); 
    }
    else {
      cout << "ERROR: Default file missing: \"" << default_filename << "\". Cannot continue. \n";
    }
  }
}
