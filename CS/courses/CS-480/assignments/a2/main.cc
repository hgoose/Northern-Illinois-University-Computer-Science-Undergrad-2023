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

#define CHILD 0
#define READ_END 0
#define WRITE_END 1

using std::cout;

// Maybe I should write an enum
static const int N = 5;
static const int GOAL = 1000;
static const int MAX_FUEL = 300;
static const int NO_PROGRESS = 0;

// In the worst case, each progress report is 10 light years,
// so the buffer size should be 100*8, since each entry is eight bytes
static const int BUF_SIZE = 8;
static const int ENTRY_LEN = 4;

// We want progress reports to be a random residue in the ring Z/51Z
static const int MOD = 51;

bool procman();
void race_and_report(int& fuel, int& progress);

// This name is meaningful
bool procman() {

    // pids of children
    pid_t children[N];

    // pipes \in R^{N\times 2} holds two file descriptors for N children, 
    // one for reading and one for writing
    int pipes[N][2];

    // one pipe for each child
    for (int i=0; i<N; ++i) {
        // Space for pipes file descriptors
        char buf[BUF_SIZE];

        // perror if the pipe call fails, message will be sent to stderr
        if (pipe(pipes[i]) == -1) {
            perror("pipe failed");

            return EXIT_FAILURE;
        }

        // Try to create child job
        pid_t pid = fork();

        // Check if job creation was a failure
        if (pid < 0) {
            perror("Failed to create child ");
            return EXIT_FAILURE;
        }

        if (pid == CHILD) {
            // Close the read end
            close(pipes[i][READ_END]);

            // Start child at 300 fuel
            int fuel = MAX_FUEL;
            int dist_traveled = 0;

            // The children can not escape this loop, they will die first
            for (;;) {
                // selection of a residue
                int progress = rand() % MOD;

                // kid must stop to refuel
                if (progress > fuel) {
                    progress = NO_PROGRESS;
                    fuel = MAX_FUEL;
                // enough fuel
                } else {
                    // Use fuel to make progress
                    fuel-=progress;
                    dist_traveled+=progress;
                }

                // Put progress and fuel use in buffer.
                // Just overwrite the previous progress 
                snprintf(buf, BUF_SIZE, "%d", dist_traveled);
                snprintf(buf + ENTRY_LEN, BUF_SIZE, "%d", fuel);

                // Write these things to the child's pipe, see if error occurred
                if (write(pipes[i][WRITE_END], buf, BUF_SIZE) == -1) {
                    perror("Failed to report childs progress");
                    return EXIT_FAILURE;
                }
            }
        // The parent gets the pid of its child through fork
        } else {
            children[i] = pid;
        }
    }

    // It's time for parent to process data and kill children gracefully
    // once the race is over.
    
    // Close the write end of pipes
    for (int i=0; i<N; ++i) {
        close(pipes[i][WRITE_END]);

    }
    
    // Gather data from children and report.
    // Run until someone wins
    for(;;sleep(1)) {
         
    }
    
    // Reap zombie processes
    for (int i=0; i<N; ++i) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}


int main(int argc, char** argv) {

    procman();

    return EXIT_SUCCESS;
}
