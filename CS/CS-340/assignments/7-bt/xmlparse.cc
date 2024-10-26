/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include "xml.h"
#include <algorithm>
#include <string>
#include <iostream>

// returns whether a character is whitespace, according to XML standard
static inline bool is_whitespace(char c) { return ( c==' ' || c == '\t' || c == '\n' || c == '\r' ); }

// returns whether a character is whitespace, according to XML standard, or the end of a tag
static inline bool is_whitespace_or_tagend(char c) { return ( c==' ' || c == '\t' || c == '\n' || c == '\r' || c == '>' ); }

// remove leading and trailing whitespace
std::string trim(const std::string &input) {
  auto b = std::find_if_not(input.begin(), input.end(), is_whitespace);
  if(b == input.end()) { // no non-whitespace found
    return ""; }

  auto re = std::find_if_not(input.rbegin(), input.rend(), is_whitespace);
  if(re == input.rend()) { // probably won't ever be triggered, but no non-whitespace found
    return ""; }
 
  return std::string(b, re.base());
}

int parse_xml(std::istream &ist, xml_tree_state &state, bool verbose) {
  bool intag = false;
  std::string curstr; // current string
  std::string trimmed;
  char c;
  if(verbose) std::cout << "parsing begins\n";

  curstr.clear();

  // read entire stream, one character at a time
  while( ist && (c = ist.get() ) != EOF ) {

    if(!intag && c == '<') { // we weren't in a tag, and now we are
      trimmed = trim(curstr); 
      if(!trimmed.empty()) { // there was plaintext before the tag started
        xml_handle_plaintext(trimmed, state, verbose);          
      }
      curstr.clear();
      intag = true; // in a tag declaration now
      curstr.push_back(c); // put the < char into the string
    }
    else if (intag && c == '>') { // in tag (opening or closing) that is now done
      curstr.push_back(c); // put the > char into the string
      xml_handle_tag(curstr, state, verbose);
      intag = false; // no longer in tag declaration
      curstr.clear();
    }
    else { // whether in tag or out of tag, nothing changed, so build string
      curstr.push_back(c);
    }
  }

  // done getting input, check if there is anything left to handle
  if(intag) { // still expecting > and didn't get it
    std::cout << "ERROR: Expecting > and did not find in remaining text: \"" << curstr << "\"\n";
  }
  else { // done with input, not still expecting >
    trimmed = trim(curstr);
    if(!trimmed.empty()) {
      xml_handle_plaintext(trimmed, state, verbose); } }
  if(verbose) std::cout << "parsing done\n";
  return 0;
}


