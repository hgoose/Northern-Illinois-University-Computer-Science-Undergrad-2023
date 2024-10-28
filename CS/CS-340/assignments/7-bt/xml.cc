// Implement a simple parser for XML that uses a tilted binary tree for storage
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <regex>
#include <tuple>
using std::regex;
using std::regex_match;
using std::regex_search;
using std::smatch;
using std::sub_match;
using std::cout;
using std::endl;
using std::string;


#include "nodes.h" // supplied node declarations
#include "bintree.h"
#include "xml.h"

using std::ostringstream;

int Validate(const string& key, const string& value, const string& equal) {

    if (value.size() < 3) {
        std::cout << "Expected a value, but didn't find any" << std::endl;
        // cout << key << endl;
        // cout << value << endl;
        return 0;
    }
    else if (equal.size() > 1) {
        std::cout << "Detected extraneous spacing around =, this incident will be reported!" << std::endl;
        return 0;
    } else if (value[value.size() - 1] != '"') { 
        std::cout << "Expected an end quote, but didn't find any" << std::endl;
        return 0;
    }

    return 1;
}

std::string to_string(const xml_element &element, bool opening) {
    if (!element.name.size()) {
        return element.fulltext;
    }

    ostringstream return_string;
    if (!opening) {
        return_string << "</" << element.name << ">";
        return return_string.str();
    }

    return_string << "<" << element.name;
    for (auto& pair : element.attrs) {
        return_string << " " << pair.first << "=" << "\"" << pair.second << "\"";
    }
    return_string << ">";
    return return_string.str();
}

std::vector <XMLNODE *> xml_find_by_name(XMLNODE * root, const std::string &name) {
    std::vector<XMLNODE*> v;
    preorder(root, [&](XMLNODE* p) {
        if (p->data.name == name) {
            v.push_back(p);
        }
    });

    return v;
}

std::vector <XMLNODE *> xml_find_with_attr(XMLNODE * root, const std::string &attrname) {
    std::vector<XMLNODE*> v;
    preorder(root, [&](XMLNODE* p) {
            for (const auto& kv : p->data.attrs) {
                if (kv.first == attrname) {
                    v.push_back(p);
                }
            }
    });

    return v;
}

int xml_add_node(const xml_element& element, xml_tree_state & state, bool verbose) {
    if (!state.root) {
        state.root = new XMLNODE(element); 
        return 0;
    }
    if (!state.cur) {
        cout << "curr is nullptr" << endl;
        return 1;
    }
    if (state.cur->data.closed || state.cur->data.name.empty() ) {
        state.cur->right = new XMLNODE(element);
        state.cur = state.cur->right;
    } else {
        state.cur->left = new XMLNODE(element);
        state.cur = state.cur->left;
    }
   return 0;
}

int xml_close_tag(const std::string name, xml_tree_state & state, bool verbose) {
    if (state.cur->data.name == name) {
        state.cur->data.closed = true; 
        return 0;
    } else {
        XMLNODE* n = tilted_find_parent(state.cur);
        if (n->data.name == name) {
            n->data.closed = true; 
            state.cur = n;
            return 0;
        }
    }
   return 1;
}

int xml_handle_plaintext(std::string &plaintext, xml_tree_state & state, bool verbose) {
    xml_element new_element(plain, "" , plaintext, {}); 
    xml_add_node(new_element, state, verbose);
    return 1000;
}

int xml_handle_attributes(const std::string &input, std::map<std::string, std::string> &attrs, bool verbose) {

    smatch capture_space;
    string::const_iterator curr = input.begin();

    // Missing end quotes breaks the expression
    if (std::count(input.begin(), input.end(), '"') == 2 * std::count(input.begin(), input.end(), '=')) {
        while (regex_search(curr, input.cend(), capture_space, regex(R"(\s*([^=]*)(\s*=\s*)(\"[^\"]*\"?))"))) {
            std::string key = capture_space[1].str();
            std::string value = capture_space[3].str();

            if (Validate(key,value, capture_space[2].str())) {
                attrs[key] = value;
            }

            curr = capture_space.suffix().first;
        }
        string other(curr, input.cend());
        smatch ocspace;
        if (!other.empty()) {
            if (regex_search(other, ocspace, regex(R"(\s*([^=]*)(\s*=\s*)(.*))"))) {
                std::string key = ocspace[1].str();
                std::string value = ocspace[3].str();

                if (Validate(key,value, capture_space[2].str())) {
                    attrs[key] = value;
                }
            }
        }
    }


    return attrs.size();
}

std::tuple<string, string, string, string,string> unpack(smatch& cs) {
    std::tuple<string,string,string,string,string> ret;
    std::get<0>(ret) = cs[1];
    std::get<1>(ret) = cs[2];
    std::get<2>(ret) = cs[3];
    std::get<3>(ret) = cs[4];
    std::get<4>(ret) = cs[5];
    return ret;
}

int xml_handle_tag(std::string &tagstring, xml_tree_state & state, bool verbose) {
    typedef std::map<std::string, std::string> attributes;
    smatch capture_space;

    if (!tagstring.size() || !regex_match(tagstring, capture_space, regex(R"(^(<)?\s*(/?)\s*(\w+)\s*([^>]*)(>?))"))) {
        return 1;
    }

    string start, close, name, as, end;
    std::tie(start, close, name, as, end) = unpack(capture_space);

    if (start.empty() || end.empty() || name.empty()) {
        return 1;
    }

    attributes attrs;
    if (close.empty()) {
        xml_handle_attributes(as, attrs, 0);
    }

    xml_element new_element(tag, name, "", attrs);
    if (close.size()) {
        new_element.closed = true;
    }

    XMLNODE new_node; 
    new_node.data = new_element;

    xml_add_node(new_element, state);

    if (close.size()) {
        xml_close_tag(name, state);
    }


   return 0;
}

void xml_print_subtree(XMLNODE *root, std::ostream & ost) {
    ost << "null for now" << endl;
}

