//***************************************************************************
//
//  dfa.cc 
//  CSCI 401 Assignment  (1)
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

// Includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

// Using
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::stringstream;
using std::string;

// Global constants
const size_t N_COLUMN = 2;

// Function to grab the information from the textfiles
void get_info(std::istream& input, int& nstates, int& n_astates, vector<int>& accepting, vector<vector<int>>& transitions, int& n_strings, vector<string>& strlist) {

    // String to hold the lines we grab from stdin
    string tmp;

    // Grab the number of states and number of accepting states from the first line
    input >> nstates >> n_astates;
    // Ingnore the rest of the first line
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Start grabbing the lines with one entry, the states that are accepting
    while (std::getline(input, tmp)) {
        if (tmp.size() > 1) { 
            break;
        }
        accepting.push_back((int) tmp[0] - '0');
    }

    // Start grabbing the next few lines which will have two entries, for the del fn
    // Vector to store entries
    vector<int> tempvec;
    do {
        tempvec.clear(); // Make sure the vector is emtpy before we begin storing
        if (tmp.size() < 3) break; // Lines that are less than three should not be stored in the vector

        // Grab the data, but not the newline, recall tmp will be the current line from the text file
        for (auto it = tmp.begin(); it != tmp.end(); ++it) {
            if (*it != ' ') {
                tempvec.push_back((int) *it - '0'); // Arithmetic to convert char to int
            }
        }
        transitions.push_back(tempvec); // Push the vector to the matrix
    } while (std::getline(input, tmp)); // Continue with next line

    // After we get the matrix entries, tmp will be the number of strings
    n_strings = stoi(tmp);

    // Grab the rest of the text file, which is the strings we need to process
    for (int i = 0; i < n_strings; ++i) {
        std::getline(input, tmp);
        strlist.push_back(tmp);
    }
}

// Function to process the string and discern if its in the language
bool proc_string(string str, int& nstates, vector<int>& accepting, vector<vector<int>>& transitions, int& transition_list_jump) { 
    int memory = 0; // Current state

    // Loop through the symbols in the string
    for (const auto& item : str) {

        int symbol = item - 'a'; // Turn the symbol into an int to naviage the transitions matrix

        // See if the symbol is valid 
        if (symbol < 0 || symbol >= transition_list_jump) {
            return false;
        }

        // Index the transitions matrix based on symbol and current state
        memory = transitions[memory][symbol];
    }

    // Check to see if we are in an accepting state
    for (const auto item : accepting) {
        if (memory == item) {
            return true; // In an accepting state
        }
    }

    // Not in an acceping state
    return false;
}

// Function to print the table
void print_transition_table(const vector<vector<int>>& transitions, int nstates, const vector<int>& accepting) {
    cout << "    |  a  b" << endl;
    cout << "----+------" << endl;

    bool star;

    // Loop through the states
    for (int i = 0; i < nstates; ++i) {
        star=false;
        // Check if the state is accepting
        for (const auto& item : accepting) {
            if (i == item) {
                star = true; // If it is, we output a star next to the state number
            }
        }
        cout << (star ? "* " : "  ") << i << " | "; // Output the star if we need one

        // Output the transitions matrix entries
        for (long unsigned j = 0; j < transitions[i].size(); ++j) {
            cout << " " << transitions[i][j];
        }
        cout << endl;
    }
}

// Entry
int main(int argc, const char* argv[]) {

    int nstates = 0, n_astates = 0, n_strings = 0, transition_list_jump = N_COLUMN;
    vector<int> accepting, states;
    vector<vector<int>> transitions;
    vector<string> strlist;
    vector<bool> outcomes;

    get_info(std::cin, nstates, n_astates, accepting, transitions, n_strings, strlist);

    // States vector
    for (int i=0; i<nstates; ++i) {
        states.push_back(i);
    }

    // Get the outcomes for each string
    for (const auto& item : strlist) {
        outcomes.push_back(proc_string(item, nstates, accepting, transitions, transition_list_jump));
    }

    // Output results
    print_transition_table(transitions, nstates, accepting);
    for (int i=0; i<n_strings; ++i) {
        cout << strlist[i] << (outcomes[i] ? " accepted" : " rejected") << endl;
    }

    return 0;
}
