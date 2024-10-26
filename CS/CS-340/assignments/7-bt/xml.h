
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef NIU_CSCI340_XML_H
#define NIU_CSCI340_XML_H

#include <string>
#include <vector>
#include <map>

#include "nodes.h"

////////////////////////////////////////////////////////////////////////////////
//
// Defining the types used for the XML parser 
//
////////////////////////////////////////////////////////////////////////////////

enum xml_type { plain, tag };

class xml_element {
  public:
  xml_type    type; 
  std::string name;      // name of tag, empty for plaintxt
  std::string fulltext;  // keep the full text of the opening tag, or the full plain text
  std::map<std::string, std::string> attrs;
  bool closed;           // starts as false, used to know whether new items are children or siblings

  xml_element() {}
  xml_element(xml_type type, 
              const std::string &name, 
              const std::string &fulltext, 
              const std::map<std::string, std::string> & attrs) 
      : type(type), name(name), fulltext(fulltext), attrs(attrs), closed(false) {}
};

typedef NodeLRP <xml_element> XMLNODE; // NodeLRP has data, left, right, parent

// object to allow access to the state of a tree, in a class instead of
// using global variable to encourage thread safety
class xml_tree_state {
  public:
  XMLNODE *root; // root of the tree
  XMLNODE *cur;  // current position
  xml_tree_state() : root(nullptr), cur(nullptr) {} // default constructor
};

////////////////////////////////////////////////////////////////////////////////
//
// Functions provided with the assignment - implemented in xmlparse.cc
//
////////////////////////////////////////////////////////////////////////////////

int         parse_xml(std::istream &ist, xml_tree_state &state, bool verbose);
std::string trim(const std::string &input);

////////////////////////////////////////////////////////////////////////////////
//
// Functions you will need to implement in xml.cc - details in README
//
////////////////////////////////////////////////////////////////////////////////

std::string to_string(const xml_element &element, bool opening=true);

int  xml_handle_tag(std::string &tagstring, xml_tree_state & state, bool verbose=false);
int  xml_handle_plaintext(std::string &plaintext, xml_tree_state & state, bool verbose=false);
int  xml_handle_attributes(const std::string &input, std::map<std::string, std::string> &attrs, bool verbose=false);

int  xml_add_node(const xml_element &element, xml_tree_state & state, bool verbose=false);
int  xml_close_tag(const std::string name, xml_tree_state & state, bool verbose=false);

void xml_print_subtree(XMLNODE *root, std::ostream & ost);

std::vector <XMLNODE *> xml_find_by_name(XMLNODE * root, const std::string &name);
std::vector <XMLNODE *> xml_find_with_attr(XMLNODE * root, const std::string &attrname);

#endif
