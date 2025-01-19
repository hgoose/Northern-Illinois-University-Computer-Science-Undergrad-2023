#include "filetree.h"

#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <regex>
#include <tuple>

using std::istream;
using std::vector;
using std::string;
using std::istringstream;
using std::regex;
using std::regex_match;
using std::smatch;
using std::tuple;
using std::cout;
using std::endl;

/* For each functon, make sure you call your readInput function to
 *
    load the data */

struct node {
    vector<node*> children;
    string name{""};
    bool isDir{0};
    int filesize{0};

    node(string name) {
        this->name = name;
    }

    node(int size, string name) : name(name), filesize(size) {}
};

string extractDir(string& s) {

    regex pattern(R"(^\$\s*cd\s*([^/]*)/?\s*)");
    smatch matches;

    if (regex_match(s, matches, pattern)) {
        if (matches.size() > 1) {
            return matches[1];
        }
    }
    return "";
}

int splitString(string& s, string& name) {
    regex pattern(R"(^\s*(\d*)\s*([^/]*)/?\s*)");
    smatch matches;

    if (regex_match(s, matches, pattern)) {
        if (matches.size() > 1) {
            name = matches[2];
            return stoi(matches[1]);
        }
    }
    return 0;
}

node* search(node*& curr, string name) {
    vector<node*> children = curr->children;

    for (auto& child : children) {
        if (child->name == name) {
            return child;
        }
    }
    return nullptr;
}


node* readInput(istream& is) {
    string s;
    getline(is, s);
    node* root = new node("");
    root->isDir=true;
    node* prev = root; // to handle cd ..
    node* curr = root;

    bool ls = false;
    while (getline(is, s)) {
        if (ls && s[0] != '$') {
            string name = "";
            int size = splitString(s,name);
            node* new_node = new node(size,name);
            if (size == 0) {
                new_node->isDir = true;
            }
            curr->children.push_back(new_node);
            continue;
        }

        if (s[0] == '$' && s.find("ls") != string::npos) {
            ls=true;
            continue;
        }

        if (s[0] == '$' && s.find("cd") != string::npos) {
            ls=false;
            string dir = extractDir(s);
            if (s == "..") {
                curr=prev;
            } else if (s == "/") {
                curr=root;
            } else {
                node* tmp = search(curr, dir); 
                prev = curr;
                curr = tmp;
            }
        }
            continue;
        }

    return root;
}

/* For each functon, make sure you call your readInput function to
    load the data */

void printNode(node * n, int lvl=0) {
    // Print the vertical lines '|' to show depth
    for (int i = 0; i < lvl; i++)
        cout << "| "; // one vertical bar for each level

    cout << endl;

    // Print the horizontal connection and node name
    for (int i = 0; i < lvl-1; i++)
        cout << "| "; // continue the vertical bar for connection
    if (lvl > 0)
        cout << "+-"; // add the horizontal connector for children
    
    // Print the current node's name
    cout << "(" << n->name << ")" << endl;

    // Recursively print the children, increasing the level
    for (auto child : n->children)
        printNode(child, lvl+1);
}

void printTree(istream & is) {
    node* root = readInput(is);
    printNode(root, 0);
}

int computeSize(istream & is, string path)
{
    /* TO BE COMPLETED */
    return -1;
}

string smallestDir(istream & is, int targetSize, string ext)
{
    /* TO BE COMPLETED */
    return "";
}

void listDeleted(istream & is, int targetSize, string ext)
{
    /* TO BE COMPLETED */
}
