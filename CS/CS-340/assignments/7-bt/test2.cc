
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include "xml.h"

#ifndef VERBOSE
#define VERBOSE (false) 
#endif

auto print_pair = [] (const std::pair<std::string,std::string> &x) { std::cout << "    key=\"" << x.first << "\", value=\"" << x.second << "\"\n"; };

void test_attributes(const std::string &label, std::string &input, bool verbose) {
  using namespace std;
  std::map <string, string> attrs;
  cout << "Testing " << label << ", [" << input << "]\n";
  int n = xml_handle_attributes(input, attrs, verbose);
  cout << "  found " << n << " attributes.\n";
  for_each(attrs.begin(), attrs.end(), print_pair); 
  cout << "\n";
}

// Test printing known XML elements
int main() {
  using namespace std;
  
  string pt_text = "This is a plain text element.";
  map<string,string> attrs;
  attrs.insert(make_pair("width", "1920")); 
  attrs.insert(make_pair("height", "1080")); 
  attrs.insert(make_pair("bpp", "4")); 
  attrs.insert(make_pair("label", "1080p")); 

  // xml_element - type, name, fulltext, attrs, closed
  xml_element xml_pt(plain, "", pt_text, {});
  xml_element tag1(tag, "tag1", "", {}); 
  xml_element tag2(tag, "tag2", "", attrs); 

  cout << "********************************************************************************\n";
  if(!(VERBOSE)) {
  cout << "* test2 - Test to_string on known elements and xml_handle_attributes with known \n";
  cout << "*    strings. Verbose debug information OFF.\n";
  } 
  else {
  cout << "* test2v - Test to_string on known elements and xml_handle_attributes with known\n";
  cout << "*    strings. Verbose debug information ON.\n";
  }
  cout << "********************************************************************************\n";


  cout << "********************************************************************************\n";
  cout << "* Testing to_string on known XML elements \n";
  cout << "********************************************************************************\n";
  cout << "  Testing plain text element:\n";
  cout << "    expect: " << pt_text << "\n";
  cout << "       got: " << to_string(xml_pt, false) << "\n";
  cout << "\n";
  cout << "  Testing tag1, which has no attributes:\n";
  cout << "    opening, expect: <tag1>\n";
  cout << "                got: " << to_string(tag1, true) << "\n";
  cout << "    closing, expect: </tag1>\n";
  cout << "                got: " << to_string(tag1, false) << "\n";
  cout << "\n";
  cout << "  Testing tag2, with attributes:\n";
  cout << "    opening, expect: <tag2 bpp=\"4\" height=\"1080\" label=\"1080p\" width=\"1920\">\n";
  cout << "                got: " << to_string(tag2, true) << "\n";
  cout << "    closing, expect: </tag2>\n";
  cout << "                got: " << to_string(tag2, false) << "\n";
  cout << "\n";
  cout << "********************************************************************************\n";
  cout << "* Testing xml_handle_attributes on known strings \n";
  cout << "********************************************************************************\n";
  
  string attrstring1 = "food=\"taco\" type=\"al pastor\" quantity=\"3\"";
  string attrstring2 = "  animal=\"dog\"  size=\"big\"    name=\"Jake\"  color=\"yellow\"\t  ";
  string wrongstring1 = "computer games are fun"; // intentionally wrong
  string wrongstring2 = "badquote=\"this quote doesn't actually end";

  test_attributes("First good string",   attrstring1,  (VERBOSE));
  test_attributes("Second good string",  attrstring2,  (VERBOSE));
  test_attributes("First *BAD* string",  wrongstring1, (VERBOSE));
  test_attributes("Second *BAD* string", wrongstring2, (VERBOSE));
}
