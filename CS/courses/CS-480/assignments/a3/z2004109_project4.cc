#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <exception>

static constexpr int MAX_TIME = 500;
static constexpr int IN_USE = 5;
static constexpr int HOW_OFTEN = 25;

using std::string;

struct PROC;

typedef unsigned int uint;
typedef std::pair<char, int> Data;
typedef std::vector<Data> History;
typedef std::deque<PROC> Queue;

static Queue Q_entry;
static Queue Q_ready;
static Queue Q_input;
static Queue Q_output;

inline bool bad_input() { puts("Unwell input"); exit(EXIT_FAILURE); return true; }

/* 
    // The structure of a process
    
    - ProcessName is the name of the process, a string.

    - ProcessID is an integer, the ID number for the process. This is assigned
    by the system (i.e., your program). Use consecutive values such as 101,
    102, 103, etc.

    - History is an array or vector of pairs of the form (letter, value). They
    are from the supplied input file, described below.

    - Sub is a subscript into the array/vector History

    - CPUTimer counts clock ticks for the process until it reaches
    the end of the CPU burst for FCFS (or end of the quantum for RR).

    - IOTimer counts clock ticks for the process until it reaches the end of the
    I/O burst. You need two variables for I and O respectively.

    - CPUTotal accumulates the number of clock ticks the process spends as
    Active.

    - IOTotal accumulates the number of clock ticks the process spends as
    IOActive. You need two variables.

    - CPUCount counts the number of completed CPU bursts for this process.

    - IOCount counts the number of completed I/O bursts for this process. You
    need two variables.
 */
struct PROC {
    string process_name{};
    int process_id{};

    History history;
    size_t sub{};

    uint cpu_timer{};
    uint io_timer{};
    uint o_timer{};
    uint i_total{};
    uint o_total{};
    uint cpu_count{};
    uint i_count{};
    uint o_count{};

    PROC() = default;
    PROC(string process_name, int process_id, History history) 
        : process_name(process_name),
        process_id(process_id),
        history(history)
    {}
};

// Just wanted an excuse to use regular expressions
bool validate_first(string& first) {

}

// Populates the entry queue from an well-formed input file of processes.
// A well-formed input consists of pairs of lines, where the first line contains
// the process name followed by the process id, and the second line contains (type, amount)
// pairs for each burst.
//
// The input is unwell iff
//      1. Either the process name or process id is missing from the first line
//      2. The process id cannot be sent into four bytes interpreted as an integer
//      3. The line that contains burst info from a process is missing
//      4. A (type, amount) pair is missing either the type or the amount
//
// Un-well input is cause for termination
void populate_entry(const char* file) {
    std::ifstream input(file);

    // Get the line that has name and id
    string proc_info{}, burst_info{};
    while (std::getline(input, proc_info)) {
        // Good first line
        if (proc_info.size()) {
            // Get the line with burst info, skip over blank lines
            do {
                std::getline(input,burst_info);
            } while (burst_info.empty());
        // If the first line was blank we skip
        } else continue;

        // Find the space that separates name from id
        size_t space = proc_info.find(' ');

        // No space \implies bad input
        space != std::string::npos || bad_input();

        // Skip over all whitespace
        while (proc_info[space++] == ' ');

        string process_name = proc_info.substr(0,space);

        int process_id{};
        try {
            int process_id = stoi(proc_info.substr(space));
        } catch (std::exception& e) {
            // Process id was bad
            bad_input();
        }

        History history;

        std::istringstream word_reader(burst_info);
        string s_type{}, s_amount{};

        // Get all pairs (type, amount)
        char type{};
        int amount{};
        while (word_reader >> s_type >> s_amount) {
            // Either the type is a single character or we terminate
            s_type.size() == 1 || bad_input();
            type = s_type[0];

            try {
                amount = stoi(s_amount);
            } catch (std::exception& e) {
                // Burst time is malformed
                bad_input();
            }
            // All is good
            history.push_back(std::make_pair(type, amount));
        }

        PROC proc = PROC(process_name, process_id, history);

        History tmp = proc.history;

        for (size_t i{}; i < tmp.size(); ++i) {
            std::cout << tmp[i].first << ' ' << tmp[i].second << ' ';
        }
        puts("");
    }
}

// Elegant scheduler
void esch(const char* file) {
    uint timer{};

    populate_entry(file);
    
}

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cout << "Usage: ./z2004109_project4 <input>\n";
        return EXIT_FAILURE;
    }

    const char* input_file = argv[1];

    esch(input_file);

    return EXIT_SUCCESS;
}
