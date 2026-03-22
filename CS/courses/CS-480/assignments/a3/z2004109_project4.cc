#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <regex>

using std::string;

struct PROC;

typedef unsigned int uint;
typedef std::pair<char, int> Data;
typedef std::vector<Data> History;
typedef std::deque<PROC*> Queue;

static constexpr int MAX_TIME = 500;
static constexpr int IN_USE = 5;
static constexpr int HOW_OFTEN = 25;

namespace ACTIVE {
    PROC* active,
        * IActive,
        * Oactive;

    bool is_active,
         is_IActive,
         is_OActive;
}

namespace QUEUE {
    Queue entry,
         ready,
         input,
         output;

    int in_play() {
        return ACTIVE::is_active 
            + ACTIVE::is_IActive 
            + ACTIVE::is_OActive 
            + QUEUE::ready.size() 
            + QUEUE::input.size() 
            + QUEUE::output.size();
    }
}

static uint next_id;

namespace ERROR {
    inline bool bad_input() { puts("Unwell input"); exit(EXIT_FAILURE); return true; }
    inline bool validate_first(string& first) { return std::regex_match(first, std::regex("^\\w+\\s+\\d+$")); }
    inline bool validate_second(string& second) { return std::regex_match(second, std::regex("^(\\s*[CcIiOo]\\s+\\d+)*\\s*(\\s*[Nn]\\s+\\d+)+$")); }
}

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
    uint process_id{next_id++};

    uint arrival_time{};

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
    PROC(string process_name, int arrival_time, History history) 
        : process_name(process_name),
        arrival_time(arrival_time),
        history(history)
    {}
};

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
//      5. The burst line is not terminated by a sequence of (N, [0-9]) pairs
//
// Un-well input is cause for termination
static void populate_entry(const char* file) {
    std::ifstream input(file);

    // Get the line that has name and arrival time
    string proc_info{}, burst_info{};
    while (std::getline(input, proc_info)) {
        if (proc_info.size()) {
            ERROR::validate_first(proc_info) || ERROR::bad_input();

            do {
                std::getline(input,burst_info);
            } while (burst_info.empty());

            ERROR::validate_second(burst_info) || ERROR::bad_input();
        } else continue;

        // Skip initial space before the process name
        size_t start = 0;
        while (proc_info[start] == ' ') ++start;

        // Find the space that separates name from arrival time, guaranteed to exist at this point. 
        // Then, extract the process name
        size_t space = proc_info.find(' ');
        string process_name = proc_info.substr(start,space);

        // Move to start of arrival time, then extract it. Stoi is guaranteed no throw
        while (proc_info[space] == ' ') ++space;
        uint arrival_time = stoi(proc_info.substr(space));

        History history;

        std::istringstream word_reader(burst_info);
        string s_type{}, s_amount{};

        // Get all pairs (type, amount), re enforces no errors will occur in the stoi
        char type{}; int amount{};
        while (word_reader >> s_type >> s_amount) {
            type = s_type[0];
            amount = stoi(s_amount);
            history.emplace_back(std::make_pair(type, amount));
        }

        PROC* proc = new PROC(process_name, arrival_time, history);

        QUEUE::entry.push_back(proc);
    }
}

// Gets the next process pointer from the entry queue, then pops the queue.
// Returns: 
//          - nullptr on empty queue
//          - pointer to next process otherwise
static PROC* next_entry() {
    if (QUEUE::entry.empty()) return nullptr;

    PROC* next = QUEUE::entry.front();
    QUEUE::entry.pop_front();
    return next;
}

// Elegant scheduler
void esch(const char* file) {
    uint timer{};

    if (QUEUE::entry.empty()) return;

    // FIGURE OUT EXIT CONDITION LATER
    for (;;) {
        // Put the first few processes in the ready queue
        PROC* curr = next_entry();
        while (curr && curr->arrival_time <= timer && QUEUE::in_play() < IN_USE) {
            QUEUE::ready.push_front(curr); 
            curr = next_entry();

            ++timer;
        }
    }

    populate_entry(file);
}

int main(int argc, char** argv) {

    // std::vector<std::string> names{"input", "names.txt", "output_fcfs", "small", "small_output_fcfs", "tiny", "tiny_output_fcfs"};
    // for (const auto& name : names) {
    //     esch(name.data());
    // }

    if (argc != 2) {
        std::cout << "Usage: ./z2004109_project4 <input>\n";
        return EXIT_FAILURE;
    }

    const char* input_file = argv[1];

    esch(input_file);

    return EXIT_SUCCESS;
}
