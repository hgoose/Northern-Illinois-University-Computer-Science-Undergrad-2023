/********************************************************************
CSCI 480 - Assignment 3 - Spring 26

Programmer: Nate Warner
Section: 1
TA: Hannah
Date Due: 03/27/26 

Purpose: Simulate a FCFS CPU scheduler or a single processor, single core system
*********************************************************************/

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <regex>
#include <cctype>
#include <string>
#include <iomanip>

#define NOPROC nullptr

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
        * OActive;

    bool is_active,
         is_IActive,
         is_OActive;
}

namespace QUEUE {
    Queue entry,
         ready,
         input,
         output;
}

namespace ERROR {
    inline bool bad_input() { puts("Unwell input"); exit(EXIT_FAILURE); return true; }

    // These should be fine
    inline bool validate_first(string& first) { return std::regex_match(first, std::regex(R"(^\s*\w+\s+\d+\s*$)")); }
    inline bool validate_second(string& second) { return std::regex_match(second, std::regex(R"(^\s*(\s*[CcIiOo]\s+\d+)*\s*(\s*[Nn]\s+\d+)+\s*$)")); }
}

// Global scheduler statistics
namespace STATS {
    uint terminated{},
         idle{},
         total_wait{},
         kproc{};
}

static uint next_id{101};

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

    // Subscript into history
    size_t sub{};

    // Timers for each burst
    uint cpu_timer{};
    uint i_timer{};
    uint o_timer{};

    // Total times spent bursting
    uint cpu_total{};
    uint i_total{};
    uint o_total{};

    // Number of bursts
    uint cpu_count{};
    uint i_count{};
    uint o_count{};

    uint start_time{};

    uint prev_exit{};
    uint total_wait{};

    PROC() = default;
    PROC(string process_name, int arrival_time, History history) 
        : process_name(process_name),
        arrival_time(arrival_time),
        history(history)
    {}

    char get_burst_type() {
        return std::toupper(history[sub].first); 
    }

    char get_burst_length() {
        return history[sub].second; 
    }

    bool cpu_burst_complete() {
        return cpu_timer == history[sub].second;
    }

    bool input_burst_complete() {
        return i_timer == history[sub].second;
    }

    bool output_burst_complete() {
        return o_timer == history[sub].second;
    }
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
        // Get first line
        if (proc_info.size()) {
            // Validate it, (the noreturn will be jumped over unless the line is invalid)
            ERROR::validate_first(proc_info) || ERROR::bad_input();

            // Get second line (skip over blank lines)
            do {
                std::getline(input,burst_info);
            } while (burst_info.empty());

            // Then validate it
            ERROR::validate_second(burst_info) || ERROR::bad_input();
        } else continue;

        // Skip initial space before the process name
        size_t start = 0;
        while (proc_info[start] == ' ') ++start;

        // Find the space that separates name from arrival time, guaranteed to exist at this point. 
        // Then, extract the process name
        size_t space = proc_info.find(' ');
        string process_name = proc_info.substr(start,space);

        // End of input
        if (process_name == "STOPHERE") return;

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

        // Number of processes 
        ++STATS::kproc;
    }
}

// Calculates the number of processes in play
static int in_play() {
    return ACTIVE::is_active 
        + ACTIVE::is_IActive 
        + ACTIVE::is_OActive 
        + QUEUE::ready.size() 
        + QUEUE::input.size() 
        + QUEUE::output.size();
}

// Checks if the scheduler is finished
static bool exhausted(const uint& timer) {
    return timer == MAX_TIME 
        || !ACTIVE::is_active 
        && !ACTIVE::is_IActive 
        && !ACTIVE::is_OActive
        && QUEUE::entry.empty()
        && QUEUE::ready.empty()
        && QUEUE::input.empty()
        && QUEUE::output.empty();
}

// Gets the next process pointer from the entry queue, then pops the queue.
// Returns: 
//          - nullptr on empty queue
//          - pointer to next process otherwise
//
// <note> Popping the queue is an activity for the caller
static PROC* next_entry() {
    if (QUEUE::entry.empty()) return nullptr;

    PROC* next = QUEUE::entry.front();

    return next;
}

// Fetch a process from the ready queue, set as active
//
// Note: Pulling from entry here is not required, if a process is able to 
// be active, it will be in ready
static void fetch_active(const uint& timer) {
    if (QUEUE::ready.size()) {
        ACTIVE::active = QUEUE::ready.front();
        QUEUE::ready.pop_front();

        ACTIVE::is_active = true;
        ACTIVE::active->total_wait += timer - ACTIVE::active->prev_exit;

        puts("");
    } 
}

// Fetch a process from the input queue, let it run on the input device
static void fetch_IActive(const uint& timer) {
    if (QUEUE::input.size()) {
        ACTIVE::IActive = QUEUE::input.front();
        QUEUE::input.pop_front();

        ACTIVE::is_IActive = true;
        ACTIVE::IActive->total_wait += timer - ACTIVE::IActive->prev_exit;
    } 
}

// Fetch a process from the output queue, let it run on the output device
static void fetch_OActive(const uint& timer) {
    if (QUEUE::output.size()) {
        ACTIVE::OActive = QUEUE::output.front();
        QUEUE::output.pop_front();

        ACTIVE::is_OActive = true;
        ACTIVE::OActive->total_wait += timer - ACTIVE::OActive->prev_exit;
    } 
}

// Terminate a process: Free the memory and output its information
static void terminate_process(PROC* proc, const uint& timer) {
    std::cout << "Process " << proc->process_id << " has terminated\n"
        << "Name: " << proc->process_name << '\n'
        << "Started at time: " << proc->start_time << " and ended at time " << timer+1 << '\n'
        << "Total CPU time: " << proc->cpu_total  << " in " << proc->cpu_count << " CPU bursts\n" 
        << "Total input time: " << proc->i_total << " in " << proc->i_count << " input bursts\n" 
        << "Total output time: " << proc->o_total << " in " << proc->o_count << " output bursts\n" 
        << "Time spent in waiting: " << proc->total_wait << "\n\n"; 

    // Set some global stuff too
    STATS::total_wait += proc->total_wait;
    ++STATS::terminated;

    delete proc;
}

// Moves a process into a queue depending on its current burst type (or terminate it)
static void move_process(PROC* proc, const uint& timer) {
    switch (proc->get_burst_type()) {
        case 'C':
            QUEUE::ready.push_back(proc);
            return;
        case 'I':
            QUEUE::input.push_back(proc);
            return;
        case 'O':
            QUEUE::output.push_back(proc);
            return;
        case 'N':
            terminate_process(proc, timer);
            return;
    }
}

// Moves a process to the ready queue
static void move_to_ready(PROC* proc) {
    QUEUE::ready.push_back(proc);
}

// Outputs the queues
//
// Note: Not in the namespace because I don't want it to have internal linkage 
// (although it doesn't matter for this assignment)
void output_queues() {
    PROC* curr{};

    std::cout << "Entry queue: ";
    Queue tmp_entry = QUEUE::entry;
    while (tmp_entry.size()) {
        curr = tmp_entry.front();
        tmp_entry.pop_front();

        std::cout << '(' << curr->process_name << ", " << curr->process_id << ')' 
            << (tmp_entry.empty() ? "" : ", ");
    } puts("");

    std::cout << "Ready queue: ";
    Queue tmp_ready = QUEUE::ready;
    while (tmp_ready.size()) {
        curr = tmp_ready.front();
        tmp_ready.pop_front();

        std::cout << '(' << curr->process_name << ", " << curr->process_id << ')' 
            << (tmp_ready.empty() ? "" : ", ");
    } puts("");

    std::cout << "Input queue: ";
    Queue tmp_input = QUEUE::input;
    while (tmp_input.size()) {
        curr = tmp_input.front();
        tmp_input.pop_front();

        std::cout << '(' << curr->process_name << ", " << curr->process_id << ')' 
            << (tmp_input.empty() ? "" : ", ");
    } puts("");

    std::cout << "Output queue: ";
    Queue tmp_output = QUEUE::output;
    while (tmp_output.size()) {
        curr = tmp_output.front();
        tmp_output.pop_front();

        std::cout << '(' << curr->process_name << ", " << curr->process_id << ')' 
            << (tmp_output.empty() ? "" : ", ");
    } puts("\n");
}

// Outputs the active processes
void output_actives() {
    std::cout << std::left << std::setw(35) << "CPU active" << ": " <<
        (ACTIVE::is_active ? std::to_string(ACTIVE::active->process_id) : "None") << '\n';

    std::cout << std::left << std::setw(35) << "Process on input device" << ": " <<
        (ACTIVE::is_IActive ? std::to_string(ACTIVE::IActive->process_id) : "None") << '\n';

    std::cout << std::left << std::setw(35) << "Process on output device" << ": " <<
        (ACTIVE::is_OActive ? std::to_string(ACTIVE::OActive->process_id) : "None") << "\n\n";
}

// Reports current state
void state_report(const uint& timer) {
    std::cout << "\nState Report (t=" << timer << ")\n"; 
    std::cout << std::string(25, '-') << '\n';

    output_actives();
    output_queues();
}

// Outputs global stats
void global_stats(const uint& timer) {
    std::cout << "The run has ended\n"
        << "The final value of the timer was: " << timer << '\n'
        << "Time spent idle: " << STATS::idle << '\n'
        << "Number of terminated processes: " << STATS::terminated << '\n'
        << "Average wait time was: " 
        << STATS::total_wait / STATS::kproc << "\n\n";

    output_actives();
    output_queues();
}

// Elegant scheduler
void esch(const char* file) {
    std::cout << "FCFS CPU Scheduler\n\n";

    uint timer{};

    populate_entry(file);

    // Input file must have been empty
    if (QUEUE::entry.empty()) return;

    // One cycle (one ms) per iteration
    while (!exhausted(timer)) {
        PROC* curr; 

        // Only if there is nothing running on the CPU, and the ready queue is empty,
        // can we move a process from entry to ready
        if (!ACTIVE::is_active && QUEUE::ready.empty()) {
            // For all those whose arrival time is less or equal to the current timer value, move
            // from entry to ready (bounded by the value of IN_USE)
            while (in_play() < IN_USE) {
                curr = next_entry();
                if (curr && curr->arrival_time <= timer) {
                    std::cout << "Process " << curr->process_id 
                        << " moved from the Entry Queue to the Ready Queue at time " 
                        << timer << "\n\n";

                    QUEUE::ready.push_back(curr);

                    // This pop is a next_entry() caller activity
                    QUEUE::entry.pop_front();

                    curr->start_time = timer;
                    curr->prev_exit = timer;

                    curr = next_entry();
                } else break;
            }
        }

        // Find a process for the input device
        if (!ACTIVE::is_IActive) { fetch_IActive(timer); }

        // Find a process for the output device
        if (!ACTIVE::is_OActive) { fetch_OActive(timer); }

        if (timer % HOW_OFTEN == 0) {
            state_report(timer);
        }

        // Find a process for CPU instruction execution
        if (!ACTIVE::is_active) { fetch_active(timer); }

        if (ACTIVE::is_active) {
            // In the case that the process is in active but not on a CPU burst, move it
            if (ACTIVE::active->get_burst_type() != 'C') {
                // Move to input / output, or terminate
                move_process(ACTIVE::active, timer); 
                ACTIVE::active->prev_exit = timer+1;

                ACTIVE::active = NOPROC;
                ACTIVE::is_active = false;
            } 
            // Otherwise the current active process is engaging in a CPU burst
            else {
                ++ACTIVE::active->cpu_timer;
                ++ACTIVE::active->cpu_total;

                if (ACTIVE::active->cpu_burst_complete()) {
                    ACTIVE::active->cpu_timer = 0;
                    ++ACTIVE::active->cpu_count;
                    ++ACTIVE::active->sub;

                    // Move to input or output queue
                    move_process(ACTIVE::active, timer);
                    ACTIVE::active->prev_exit = timer+1;
                    ACTIVE::active = NOPROC;
                    ACTIVE::is_active = false;

                }
            }
        } else {
            std::cout << "No process eligable for CPU instruction execution at time " 
                << timer << ", idle time\n";

            ++STATS::idle;
        }

        if (ACTIVE::is_OActive) {
            ++ACTIVE::OActive->o_timer;
            ++ACTIVE::OActive->o_total;


            if (ACTIVE::OActive->output_burst_complete()) {
                ACTIVE::OActive->o_timer = 0;
                ++ACTIVE::OActive->o_count;
                ++ACTIVE::OActive->sub;

                // Done with output, go back to ready
                move_to_ready(ACTIVE::OActive);
                ACTIVE::OActive->prev_exit = timer+1;
                ACTIVE::OActive = NOPROC;
                ACTIVE::is_OActive = false;
            }
        }

        if (ACTIVE::is_IActive) {
            ++ACTIVE::IActive->i_timer;
            ++ACTIVE::IActive->i_total;

            if (ACTIVE::IActive->input_burst_complete()) {
                ACTIVE::IActive->i_timer = 0;
                ++ACTIVE::IActive->i_count;
                ++ACTIVE::IActive->sub;

                // Done with input, go back to ready
                move_to_ready(ACTIVE::IActive);
                ACTIVE::IActive->prev_exit = timer+1;
                ACTIVE::IActive = NOPROC;
                ACTIVE::is_IActive = false;
            }
        }

        ++timer;
    }

    global_stats(timer);
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
