/********************************************************************
CSCI 480 - Assignment 2 - Spring 26

Programmer: Nate Warner
Section: 1
TA: Hannah
Date Due: 02/14/26 

Purpose: Write a Linux program in C or C++ which uses fork() to start child process(es), and also uses pipe()
to do inter-process communication. Other system calls such as getpid() and wait() are also used.

Simulation of an intergalactic space race where multiple child processes represent
competing spaceships, and the parent process acts as the control center, coordinating the race and
displaying the results.
*********************************************************************/

#include <iostream>
#include <stdlib.h>
#include <unistd.h> // sleep, fork(), ...
#include <sys/types.h> // pid_t
#include <sys/wait.h>
#include <errno.h>
#include <cstdlib>
#include <cmath> // ceiling
#include <cstring> // memset

#define CHILD 0
#define READ_END 0
#define WRITE_END 1

using std::cout;

// Maybe I should write an enum
static const int N = 5;
static const int GOAL = 1000;
static const int MAX_FUEL = 300;
static const int NO_PROGRESS = 0;

// Two ints + 2 null terminators
static const int BUF_SIZE = 10;

// Size of int + null terminator
static const int ENTRY_LEN = 5;

static const int MIN_SYMBOL_WIDTH = 0;
static const int MAX_SYMBOL_WIDTH = 30;
static const int MIN_PROGRESS = 0;
static const int MAX_PROGRESS = 1050;

// We want progress reports to be a random residue in the ring Z/51Z
static const int MOD = 51;

bool procman();
bool race_and_report(char buf[], int pipes[N][2], size_t i);
bool output_progress(pid_t children[N], int pipes[N][2], bool& done, size_t& winner);

// Bijection from progress (0-1050) over to progress bar width.
static inline size_t xScale(int progress) {
    // This should be fine
    
    // <remark> this works perfectly
    return static_cast<size_t>(std::ceil((static_cast<double>(MAX_SYMBOL_WIDTH - MIN_SYMBOL_WIDTH)) / (MAX_PROGRESS - MIN_PROGRESS) * progress)); 
}

// process manager
bool procman() {

    // pids of children
    pid_t children[N];

    // pipes \in R^{N\times 2} holds two file descriptors for N children, 
    // one for reading and one for writing
    int pipes[N][2];

    // Create N children
    for (size_t i=0; i<N; ++i) {

        // Buffer for each child's progress (distance, fuel)
        char buf[BUF_SIZE];

        // Create pipe for child i
        if (pipe(pipes[i]) == -1) {
            perror("pipe failed");
            return EXIT_FAILURE;
        }

        // Try to create child job
        pid_t pid = fork();

        // Check if job creation was a failure
        if (pid < 0) {
            perror("fork failed");
            return EXIT_FAILURE;
        }

        if (pid == CHILD) {
            if (race_and_report(buf, pipes, i) == EXIT_FAILURE) {
                std::cerr << "\nExiting\n"; 
                return EXIT_FAILURE;
            }
        }
        // The parent gets the pid of its child through fork
        else {
            children[i] = pid;
        }
    }

    /* Parent processing */

    // Close the write end of pipes
    for (int i=0; i<N; ++i) {
        if (close(pipes[i][WRITE_END]) == -1) {
            perror("Closing write end of pipe failed");
            return EXIT_FAILURE;
        }
    }
    
    // Gather data from children and report.
    // Run until someone wins
    bool done = false;
    size_t winner = 0;

    // This will loop until done flag is set to true, and sleeps at the end of each iteration
    for(;!done;sleep(1)) {
        if (output_progress(children, pipes, done, winner) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
    }

    // Kill all children gracefully
    for (int i=0; i<N; ++i) {
        if (kill(children[i], SIGTERM) == -1) {
            perror("kill");
            return EXIT_FAILURE;
        }
    }
    
    // Reap zombie processes
    for (int i=0; i<N; ++i) {
        if (wait(NULL) == -1) {
            perror("wait");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

bool race_and_report(char buf[], int pipes[N][2], size_t i) {
    // Seed child's residue selector with its pid
    srand(getpid());

    // Close the read end
    if (close(pipes[i][READ_END]) == -1) {
        perror("Closing pipe failed");
        return EXIT_FAILURE;
    }

    // Start child at 300 fuel, and zero distance traveled
    int fuel = MAX_FUEL;
    int dist_traveled = 0;

    // The children can not escape this loop 
    for (;;) {
        // Selection of a residue
        int progress = rand() % MOD;

        // kid must stop to refuel
        if (progress > fuel) {
            progress = NO_PROGRESS;
            fuel = MAX_FUEL;
        } 
        // Enough fuel
        else {
            // Use fuel to make progress
            fuel-=progress;
            dist_traveled+=progress;
        }

        // Clear the buffer
        memset(buf, 0, BUF_SIZE);

        // Put new values in buffer
        // Note: A terminating null character is automatically appended after the content written 
        snprintf(buf, ENTRY_LEN, "%d", dist_traveled);
        snprintf(buf + ENTRY_LEN, ENTRY_LEN, "%d", fuel);

        // Send new data to parent
        if (write(pipes[i][WRITE_END], buf, BUF_SIZE) == -1) {
            perror("Failed to write childs progress to pipe");
            return EXIT_FAILURE;
        }
    }
}

bool output_progress(pid_t children[N], int pipes[N][2], bool& done, size_t& winner) {
    // Buffers for each child's progress
    char distances[ENTRY_LEN], fuels[ENTRY_LEN];

    // Get progress report for each child
    for (int i=0; i<N; ++i) {
        // Try to read data from child i
        if (read(pipes[i][READ_END], distances, ENTRY_LEN) == -1 
                || read(pipes[i][READ_END], fuels, ENTRY_LEN) == -1) 
        {
            perror("Failed to read from pipe");
            return EXIT_FAILURE;
        } 


        // These should be fine
        size_t distance = atoi(distances);
        size_t fuel = atoi(fuels);

        // Use scale to find width of progress bar
        size_t width = xScale(distance);

        // Output child is progress
        cout << "Spaceship " << i+1 << " (" << children[i] << "): (" << width << ") ";
        for (size_t w = 0; w < width; ++w) { cout << "="; } cout << " ";
        cout << distance << " light-years, fuel " << fuel << "\n\n";

        // Child i reached goal
        if (distance >= GOAL) {
            done = true, winner = i;
        }
    }

    // Clears screen
    if (!done) {
        cout << "\033[2J\033[1;1H";
    } else {
        cout << "------------------------------\n\n"
            << "Spaceship " << winner << " wins\n";
    }

    return EXIT_SUCCESS;
}

// I like main at the bottom
int main(int argc, char** argv) {
    return procman();
}
