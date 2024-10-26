// Implement a simple parser for XML that uses a tilted binary tree for storage
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <regex>
using std::regex;
using std::regex_match;
using std::smatch;


#include "nodes.h" // supplied node declarations
#include "bintree.h"
#include "xml.h"

using std::ostringstream;

std::string to_string(const xml_element &element, bool opening) {
    if (!element.name.size()) {
        return element.fulltext;
    }

    ostringstream return_string;
    if (!opening) {
        return_string << "<" << element.name << "/>";
        return return_string.str();
    }

    return_string << "<" << element.name;
    for (auto& pair : element.attrs) {
        return_string << " " << pair.first << "=" << pair.second;
    }
    return_string << ">";
    return return_string.str();
}

std::vector <XMLNODE *> xml_find_by_name(XMLNODE * root, const std::string &name) {
  // XXX You must implement this
  return {};
}

std::vector <XMLNODE *> xml_find_with_attr(XMLNODE * root, const std::string &attrname) {
  // XXX You must implement this
  return {};
}

int xml_add_node(const xml_element &element, xml_tree_state & state, bool verbose) {
   // XXX You must implement this.
   return 1000;
}

int xml_close_tag(const std::string name, xml_tree_state & state, bool verbose) {
   // XXX You must implement this.
   return 1000;
}

int xml_handle_plaintext(std::string &plaintext, xml_tree_state & state, bool verbose) {
   // XXX You must implement this.
   return 1000;
}

int xml_handle_attributes(const std::string &input, std::map<std::string, std::string> &attrs, bool verbose) {

   return 0;
}

int xml_handle_tag(std::string &tagstring, xml_tree_state & state, bool verbose) {
    typedef std::map<std::string, std::string> attributes;
    smatch capture_space;

    // Check if its empty or does not start with < and end with >
    if (!tagstring.size() || !regex_match(tagstring, capture_space, regex(R"(^<(/)?(\w+)((\s+\w+=\S+)*)\s*>$)"))) {
        return 1;
    }
    // Not a closer (first capture is the optional /)
    if (capture_space[1] != '/') {
        attributes attrs;
        int error = xml_handle_attributes(capture_space[3], attrs, 0);
    }


    // TODO Finish 

   return 1000;
}

void xml_print_subtree(XMLNODE *root, std::ostream & ost) {
  // XXX You must implement this.
}

