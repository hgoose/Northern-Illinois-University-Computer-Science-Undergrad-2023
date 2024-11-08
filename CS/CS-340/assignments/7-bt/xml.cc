//***************************************************************************
//
//  xml.cc 
//  CSCI 340 Assignment 7 
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

// Implement a simple parser for XML that uses a tilted binary tree for storage
#include "bintree.decl.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <sstream>
#include <regex>
#include <tuple>
using std::regex;
using std::regex_match;
using std::regex_search;
using std::smatch;
using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

#include "nodes.h" // supplied node declarations
#include "bintree.h"
#include "xml.h"

// Defined types
typedef std::map<std::string, std::string> attributes;

/**
 * @brief Trims leading and trailing whitespace from a string.
 *
 * @param s The string to be trimmed.
 * @return A new string with whitespace removed from the start and end.
 */
// Elegent string trimming
inline string trim(const string& s) { smatch match; if (regex_match(s, match, regex(R"(\s*(.*)\s*)"))) { return match[1].str(); } return ""; }

/**
 * @brief Converts an xml_element to a string representation.
 *
 * @param element The XML element to convert.
 * @param opening Indicates whether to return the opening or closing tag.
 * @return A string representation of the XML element.
 */
std::string to_string(const xml_element &element, bool opening) {
    // If the name field of the element is empty, it is plain, return fulltext
    if (!element.name.size()) {
        return element.fulltext;
    }

    // Create a stringstream to build the return string
    ostringstream return_string;

    // If the element is a closer tag, it should be in the form </name>
    if (!opening) {
        return_string << "</" << element.name << ">";
        return return_string.str();
    }

    // It's not a closing tag, build the tag in form <name a_1=v_1,...>
    
    // Start by adding <name to the start of the string
    return_string << "<" << element.name;
    // For each key=value pair in the attrs map, send to string
    for (auto& pair : element.attrs) {
        return_string << " " << pair.first << "=" << "\"" << pair.second << "\"";
    }
    // Add \rangle
    return_string << ">";
    // Return built string
    return return_string.str();
}

/**
 * @brief Finds all XML nodes that contain a specific attribute in a tilted binary tree.
 *
 * @param root The root of the tilted binary tree.
 * @param attrname The attribute name to search for.
 * @return A vector of pointers to XML nodes containing the specified attribute.
 */
std::vector <XMLNODE *> xml_find_by_name(XMLNODE * root, const std::string &name) {
    // Create a vector of xmlnodes
    std::vector<XMLNODE*> v;
    // Preorder traverse the tree starting at root (preorder will handle the empty tree noop)
    preorder(root, [&](XMLNODE* p) {
        // If the current node has name field = requested name, add to vector
        if (p->data.name == name) {
            v.push_back(p);
        }
    });

    // Return vector of found xmlnodes
    return v;
}

/**
 * @brief Adds a new XML node to the tilted binary tree.
 *
 * @param element The XML element to add.
 * @param state The current state of the XML tree.
 * @param verbose Flag for verbose output during node addition.
 * @return 0 on success, 1 on error.
 */
std::vector <XMLNODE *> xml_find_with_attr(XMLNODE * root, const std::string &attrname) {
    // Create a vector of xmlnodes
    std::vector<XMLNODE*> v;
    // Preorder traverse the tree starting at root
    preorder(root, [&](XMLNODE* p) {
            // Check the current nodes attribute map, if it has a key that we are looking for, 
            // add the current node to the vector
            for (const auto& kv : p->data.attrs) {
                // Compare the key
                if (kv.first == attrname) {
                    v.push_back(p);
                }
            }
    });

    // Return vector
    return v;
}

/**
 * @brief Adds a new XML node to the tilted binary tree.
 *
 * @param element The XML element to add.
 * @param state The current state of the XML tree.
 * @param verbose Flag for verbose output during node addition.
 * @return 0 on success, 1 on error.
*/
int xml_add_node(const xml_element& element, xml_tree_state & state, bool verbose) {
    // If the tree is empty, add the node as rot
    if (!state.root) {
        state.root = new XMLNODE(element); 
        // Set current to the new node
        state.cur = state.root;
        return 0;
    }
    // If the current node is nullptr, print error message and return
    if (!state.cur) {
        cout << "Error: Current node does not exist" << endl;
        return 1;
    }

    // If the current node is closed or plaintext, add as right child of current node
    if (state.cur->data.closed || state.cur->data.type == plain) {
        // Go right until we find an empty spot
        while (state.cur->right) {
            state.cur = state.cur->right;
        }
        // Add new node to the right (in the empty spot we found)
        state.cur->right = new XMLNODE(element);
        // Set the parent
        state.cur->right->parent = state.cur;
        // Update current
        state.cur = state.cur->right;
    // Otherwise, add as left child
    } else {
        // Go left until we find an empty spot
        while (state.cur->left) {
            state.cur = state.cur->left;
        }
        // Add new node to the left
        state.cur->left = new XMLNODE(element);
        // Set parent
        state.cur->left->parent = state.cur;
        // Update current
        state.cur = state.cur->left;
    }
   return 0;
}

/**
 * @brief Closes an open XML tag in the tilted binary tree.
 *
 * @param name The name of the XML tag to close.
 * @param state The current state of the XML tree.
 * @param verbose Flag for verbose output during tag closing.
 * @return 0 on success, 1 on failure.
*/
int xml_close_tag(const std::string name, xml_tree_state& state, bool verbose) {
    // If the current node doesnt exist, return error
    if (!state.cur) return 1;

    // If the tag we want to close is the current tag, simply set current to closed
    if (state.cur->data.name == name) {
        state.cur->data.closed = true; 
        return 0;
    // Else, find the real parent of current, if it exists set it to closed
    } else {
        // Find the parent
        XMLNODE* n = tilted_find_parent(state.cur);
        // Check if it exists and it has the correct name 
        if (n && n->data.name == name) {
            n->data.closed = true;  // set closed
            state.cur = n; // set current
            return 0; // return success
        }
    }
   return 1;
}

/**
 * @brief Adds a plaintext node to the tilted binary tree.
 *
 * @param plaintext The plaintext to be added as a new XML node.
 * @param state The current state of the XML tree.
 * @param verbose Flag for verbose output during node addition.
 * @return 0 on success, 1 on failure.
*/
int xml_handle_plaintext(std::string &plaintext, xml_tree_state & state, bool verbose) {
    // Make a new element with plaintext field
    xml_element new_element(plain, "" , plaintext, {}); 
    // Add the node to the tree
    if (xml_add_node(new_element, state, verbose)) {
        // If it was added successfully, return successful
        return 0;
    }
    // Otherwise, return failure
    return 1;
}

/**
 * @brief Handles malformed attribute strings that do not have proper quotation marks.
 *
 * @param s The attribute string to be processed.
 * @param attrs The map of attributes to store the processed key-value pairs.
*/
/* Quick note: I created this function to handle the cases where the attributes string was missing quotes.
 * I was unable to create a regular expression to handle this case, however, im pretty sure that this function can
 * handle all cases, but I like my regular expression solution so I have decided to keep it.
*/
void HandleNonNiceStrings(string &s, attributes& attrs) {
    // Init iterator to start and end of string
    string::iterator start = s.begin();
    // If there are no = in the entire string, output error
    string::iterator e = std::find(s.begin(), s.end(), '=');
    if (e == s.end()) {
        cout << "  ERROR: xml_handle_attributes done. Invalid string remaining " << "\"" << s << "\"" << endl;
        return;
    }

    // Otherwise traverse the string
    while (start != s.end()) {
        // Find the equal sign, get iterator to it
        string::iterator equals = std::find(start, s.end(), '=');
        // If the equal sign is not found, done processing string
        if (equals == s.end()) {
            return;
        };
        // Get and trim the key 
        string key = string(start, equals);
        key = trim(key);

        // Advance equals until it stops being whitespace or until it finds a quote
        while (*++equals == ' ' && *equals != '"');
        
        // Init end_of_val iterator, this iterator will be advanced to the end of the current value
        string::iterator end_of_val = equals + 1;
        // Flag to signify if we need to abort the current iteration, abort if we failed to find a end quote
        bool abort = false;;

        // Advance end_of_val until we find the end quote, abort if we don't find any
        while (*end_of_val++ != '"') {
            // If we reach another equal sign or we hit the end of string, there must not be an end quote, abort
            if (*end_of_val == '=' || end_of_val == s.end()) {
                cout << "  ERROR: xml_handle_attributes tag ended before value's quotation ended." << endl;
                // Before we abort, we must walk backwards to get back to the start of the next key
                while (*--end_of_val != ' '); 

                // Set start to the start of the next key
                start = end_of_val;
                
                // Abort
                abort = true;
                break;
            }
        }
        // Check if we need to abort
        if (abort) continue;
        
        // Get the value, start iterator depends on whether there was a start quote on the value
        string value = string((*equals == '"' ? equals+1 : equals), end_of_val-1);
        // Trim the value
        value = trim(value);
        // Send the key=value pair to the attribute map
        attrs[key] = value;

        // Update start iterator to the start of the next key
        start = end_of_val;
    }
}

/**
 * @brief Validates the key, value, and equality sign of an XML attribute.
 *
 * @param key The attribute key.
 * @param value The attribute value.
 * @param equal The equality sign (=) between the key and value.
 * @return 0 if valid, 1 if invalid.
*/
int Validate(const string& key, const string& value, const string& equal) {
    // If the value is empty, print error and return
    if (value.empty()) {
        std::cout << "Expected a value, but didn't find any" << std::endl;
        return 1;
    }
    else if (equal.size() > 1) {
        std::cout << "Detected extraneous spacing around =, this incident will be reported!" << std::endl;
        return 1;
    }

    return 0; // Success
}

/**
 * @brief Parses and extracts attributes from an XML tag string.
 *
 * @param input The XML tag string containing attributes.
 * @param attrs The map to store the extracted key-value pairs of attributes.
 * @param verbose Flag for verbose output during attribute handling.
 * @return The number of attributes extracted.
*/
int xml_handle_attributes(const std::string &input, std::map<std::string, std::string> &attrs, bool verbose) {
    // Define the capture space (where the captures live)
    smatch capture_space;
    // Get iterator to start of input string
    string::const_iterator curr = input.begin();

    // If the input string is empty, return 0 (no attributes found)
    if (input.empty()) return 0;

    // If the string is nice (all values are surrounded in quotes), we can use regular expressions

    // Check if the number of quotes equals 2 * the number of equal signs (the string is nice)
    if (std::count(input.begin(), input.end(), '"') == 2 * std::count(input.begin(), input.end(), '=') && std::count(input.begin(), input.end(), '=') != 0) {

        // Loop through the string to get all the matches (key=value pairs)
        while (regex_search(curr, input.cend(), capture_space, regex(R"(\s*([^=]*)(\s*=\s*)\"([^\"]*)\"?)"))) {
            // Get the key and value from the capture space
            std::string key = capture_space[1].str();
            std::string value = capture_space[3].str();

            // Validate the key, value, and equal sign
            if (Validate(key,value, capture_space[2].str()) == 0) {
                // Validated, add to attribute map
                attrs[key] = value;
            }
            // Update start iterator to end of match (start of next key)
            curr = capture_space.suffix().first;
        }
    } else {
        // Non nice string, let the other function handle it
        string s = input;
        HandleNonNiceStrings(s, attrs);
    }

    // Return the number of attributes found
    return attrs.size();
}

/**
 * @brief Unpacks regular expression matches into a tuple of strings.
 *
 * @param cs The match result from a regular expression search.
 * @return A tuple containing the captured strings.
*/
std::tuple<string, string, string, string,string> unpack(smatch& cs) {
    // Since structured bindings require c++17, we unpack a tuple the old fashioned way... 
    
    // Create a tuple with values from regular expression captures (so we can use std::tie to unpack it)
    std::tuple<string,string,string,string,string> ret;

    // Fill the tuple
    std::get<0>(ret) = cs[1];
    std::get<1>(ret) = cs[2];
    std::get<2>(ret) = cs[3];
    std::get<3>(ret) = cs[4];
    std::get<4>(ret) = cs[5];

    // Return the tuple
    return ret;
}

/**
 * @brief Handles an XML tag string and adds the corresponding node to the tilted binary tree.
 *
 * @param tagstring The XML tag string to process.
 * @param state The current state of the XML tree.
 * @param verbose Flag for verbose output during tag handling.
 * @return 0 on success, 1 on error.
*/
int xml_handle_tag(std::string &tagstring, xml_tree_state & state, bool verbose) {
    // Define the capture space
    smatch capture_space;

    // If the string is empty, or the regular expression fails to match, return error
    if (!tagstring.size() || !regex_match(tagstring, capture_space, regex(R"(^(<)?\s*(/?)\s*(\w+)\s*([^>]*)(>?))"))) {
        return 1;
    }

    // Get the captures from the capture space
    // Start: < or ""
    // Close: / or ""
    // Name: name of tag
    // As: string containing the attributes
    // End: > or ""
    string start, close, name, as, end;
    std::tie(start, close, name, as, end) = unpack(capture_space);

    // If start is empty, end is empty, or name is empty, the tag is not valid, return error
    if (start.empty() || end.empty() || name.empty()) {
        return 1;
    }

    // If the regular expression detected its a closing tag, call xml_close_tag
    if (close.size()) {
        xml_close_tag(name, state);
        return 0;
    } 

    // Otherwise
    
    // Create an attribute map
    attributes attrs;
    // Build the attribute map with the found attributes
    xml_handle_attributes(as, attrs, 0);

    // Create a new element
    xml_element new_element(tag, name, "", attrs);
    // Add the element to the tree
    xml_add_node(new_element, state);

    // Return success
    return 0;
}

/**
 * @brief Outputs the XML content of a node to a stream.
 *
 * @param node The node whose content will be output.
 * @param ost The output stream to write the XML content to.
 */
void output(XMLNODE* node, std::ostream& ost) {
    // If the node is plain, output fulltext and return
    if (node->data.type == plain) {
        ost << node->data.fulltext;
        return;
    }

    // Otherwise, output the tag and attributes of the tag
    ost << "<" << node->data.name;
    for (const auto& pair : node->data.attrs) {
        ost << " " << pair.first << "=\"" << pair.second << "\"";
    }
    ost << ">";

}

/**
 * @brief Outputs the closing tag of an XML node.
 *
 * @param node The node whose closing tag will be output.
 * @param ost The output stream to write the closing tag to.
*/
void close(XMLNODE* node, std::ostream& ost) {
    // Noop on plaintext
    if (node->data.type == plain) return; 

    // Note: Initially I was checking if the tag was closed, only then outputting the closed version, but bool closed in the xml element starts by default as closed=false, 
    // however, test3 creates a tree with NO tags marked closed, but outputs the closed tags anyways, which lead me to remove the check. 

    // Output the closing tag
    ost << "</" << node->data.name << ">";
}

/**
 * @brief Recursively performs a (basically) preorder traversal on a tilted binary tree and outputs each node.
 *
 * @param root The root of the tilted binary tree.
 * @param p The current node being traversed.
 * @param ost The output stream to write the XML content to.
*/
void r_augmentedPre(XMLNODE* root, XMLNODE* p, std::ostream& ost) {
    if (!p) return; // Return on nullptr
    // Output the node
    output(p, ost);
    // Walk left
    r_augmentedPre(p, p->left, ost);
    // Output the closing tag
    close(p,ost);
    // Go right unless its the node we started at
    if (p != root) {
        r_augmentedPre(p, p->right, ost);
    }
}

/**
 * @brief Initiates a preorder traversal of a tilted binary tree and outputs its XML structure.
 *
 * @param root The root of the tilted binary tree.
 * @param ost The output stream to write the XML content to.
 */
void augmentedPre(XMLNODE* root, std::ostream& ost) {
    // Invoke the recursive function
    r_augmentedPre(root, root, ost);
}


/**
 * @brief Outputs the XML subtree rooted at a specified node.
 *
 * @param root The root of the subtree to output.
 * @param ost The output stream to write the XML content to.
*/
void xml_print_subtree(XMLNODE *root, std::ostream & ost) {
    // Invoke the function that invokes the recursive function
    augmentedPre(root, ost);
}
