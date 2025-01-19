//***************************************************************************
//
//  nfa_e.cc 
//  CSCI 401 Assignment 3
//  Nondeterministic Finite Automata
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

// Includes
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include <map>
#include <set>

// Using
using std::endl;
using std::cout;
using std::string;
using std::vector;
using std::map;
using std::set;
using std::setw;
using std::right;

// Custom Types
template <typename T>
using matrix = vector<vector<T>>;

using transition_table = map<short, matrix<short>>;

// Function Signatures
void get_info(std::istream& input, short& nstates, short& naccepting, vector<short>& accepting, transition_table& transitions, int& nstrings, vector<string>& strings);
bool proc_string(const string& str, const vector<short>& accepting, transition_table& transitions, const short& nstates);
void print_table(short& nstates, vector<short>& accepting, transition_table& transitions);
void print_outcomes(vector<string>& strings, vector<bool>& outcomes);

// Entry
int main(int argc, const char* argv[]) {

    //  Needed variables
    short nstates = 0, naccepting = 0;
    int nstrings=0;
    vector<short> accepting;
    vector<string> strings;
    transition_table transitions;

    // Call the function to read data
    get_info(std::cin, nstates, naccepting, accepting, transitions, nstrings, strings);

    // Create outcome vector and call proc string function for each string
    vector<bool> outcomes;
    for (const auto& item : strings) {
        outcomes.push_back(proc_string(item, accepting, transitions, nstates));
    }

    // Print the table and results
    print_table(nstates, accepting, transitions);
    print_outcomes(strings, outcomes);

    return 0;
}


// Function to get info from stdin
void get_info(std::istream& input, short& nstates, short& naccepting, vector<short>& accepting, transition_table& transitions, int& nstrings, vector<string>& strings) {

    // Temporary variables
    string stmp;
    matrix<short> vtmp_large;
    vector<short> vtmp_small;

    // Line control variables (For transition table entries)
    short line_idx, state_transitions;

    // Grab the number of states and number of accepting states
    input >> nstates >> naccepting;

    // Ingnore the rest of the first line
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Read the accepting states (while there is only one character on the line)
    std::getline(input, stmp);
    while (stmp.size() == 1) {
        // Push accepting state into vector
        accepting.push_back((short) stmp[0] - '0');
        // get the next line
        std::getline(input, stmp);
    }

    // For each state (line)
    for (short state=0; state< nstates; ++state) {
        // Clear the large one because we're on a new line
        vtmp_large.clear();

        // Line index control
        line_idx=0, state_transitions=0;

        // While we still have things to process
        int count = 0;
        while (line_idx < (short) stmp.size()) {

            // Start of loop setup
            vtmp_small.clear();
            state_transitions=(stmp[line_idx] - '0'); // Grab the number of transitions for each symbol
            line_idx+=2; // Increment line index control to next character

            // For the number of transitions for each symbol
            for (short j=0;j<state_transitions && line_idx < (short) stmp.size(); ++j) {
                vtmp_small.push_back(stmp[line_idx] - '0'); // Grab the transition
                line_idx+=2; // Increment to next transition
            }

            vtmp_large.push_back(vtmp_small); 
            ++count;
        }

        // Send to map
        transitions.insert({state, vtmp_large});

        // Get the next line
        std::getline(input, stmp);
    }

    // Grab the number of strings
    nstrings=stoi(stmp);

    // Loop for each string, put in strings vector
    for (int i=0; i<nstrings; ++i) {
        std::getline(input, stmp);
        strings.push_back(stmp);
    }
}

// Function to send each string through the machine
// If a symbol and a state maps to a set \in P(Q) with a cardinality greater than one, 
// we will be in all states of the subset simultaneously
bool proc_string(const string& str, const vector<short>& accepting, transition_table& transitions, const short& nstates) {

    // Start at state zero, also need a copy of memory because we need to clear 
    // the memory set but we still need to know what was in there
    set<short> memory = {0};
    set<short> memorytmp = memory;

    // Symbol control: a->0 b->1 (to index for transition vector inside the map)
    int symbol;

    set<short> subset;

    // Loop through each symbol in the string
    for (auto it = str.begin(); it!=str.end(); ++it) {
        symbol = *it - 'a'; // Get the index
        
        // Reset memory
        memory.clear(); 
        subset.clear();  
        
        // For each state in s \subset P(Q), find the set of states it can go to and insert into the memory subset
        for (set<short>::iterator it=memorytmp.begin(); it!=memorytmp.end(); ++it) {
            subset.insert(transitions[*it][symbol].begin(), transitions[*it][symbol].end());

            // Add the \epsilon transitions
            for (const auto& item : subset) {
                subset.insert(transitions[item][2].begin(), transitions[item][2].end());
            }
        }
        // Insert the memory subset into memory
        memory.insert(subset.begin(), subset.end());
        memorytmp = memory;
    }

    // See if any of the final states we are on are accepting
    for (const auto& end_state : memory) {
        for (const auto& accepting_state: accepting) {
            if (end_state == accepting_state) {
                return true;
            }
        }
    }
    return false;
}

// Function to print the table 
void print_table(short& nstates, vector<short>& accepting, transition_table& transitions) {
    cout << right << setw(6)  << "| " << "a " << "b" << "e"<< endl
        << "----+------" << endl;

    bool star;
    for (short i=0; i<nstates; ++i) {
        star=false;

        for (const auto& item : accepting) {
            if (item == i) star=true;
        }
        cout << (star ? "* " : "  " ) << i << " | ";
        for (const auto& vector : transitions[i]) {
            cout << "{ ";
            for (auto it = vector.begin(); it!=vector.end(); ++it) {
                cout << *it << (it != vector.end()-1 ? " " : "");
            }
            cout << "} ";
        }
        cout << endl;
    }
}

// Function to print the outcomes for each word
void print_outcomes(vector<string>& strings, vector<bool>& outcomes) {
    std::vector<string>::iterator word = strings.begin();
    for (const auto& item : outcomes) {
        cout << *word << " " << (item ? "accepted" : "rejected") << endl;
        ++word;
    }
}
