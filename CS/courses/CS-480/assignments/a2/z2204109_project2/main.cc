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
#include <signal.h>
#include <bitset>

#define CHILD 0
#define READ_END 0
#define WRITE_END 1

using std::cout;

// Maybe I should write an enum
static const int N = 5;
static const int GOAL = 1000;
static const int MAX_FUEL = 300;
static const int NO_PROGRESS = 0;

static const int MIN_SYMBOL_WIDTH = 0;
static const int MAX_SYMBOL_WIDTH = 30;
static const int MIN_PROGRESS = 0;
static const int MAX_PROGRESS = 1050;

static const int MOD = 41;

typedef unsigned int _uint; 

struct Data {
    _uint distance{};
    _uint fuel{};
};

int procman();
int race_and_report(Data& d, int pipes[N][2], std::bitset<N> fd_exists, size_t i);
int output_progress(pid_t children[N], int pipes[N][2], bool& done, size_t& winner);

// Write a progress symbol for every 50 light-years
static inline size_t xScale(int progress) {
    return progress / 50;
}

// process manager
int procman() {

    // pids of children
    pid_t children[N];

    // pipes \in R^{N\times 2} holds two file descriptors for N children, 
    // one for reading and one for writing
    int pipes[N][2];

    std::bitset<N> fd_exists(0);

    // Create N children
    for (size_t i=0; i<N; ++i) {

        Data d;

        // Create pipe for child i
        if (pipe(pipes[i]) == -1) {
            perror("pipe failed");
            return EXIT_FAILURE;
        }

        fd_exists[i] = 1;

        // Try to create child job
        pid_t pid = fork();

        // Check if job creation was a failure
        if (pid < 0) {
            perror("fork failed");
            return EXIT_FAILURE;
        }

        if (pid == CHILD) {
            if (race_and_report(d, pipes, fd_exists, i) == EXIT_FAILURE) {
                std::cerr << "\nFatal error, exiting\n"; 
                _exit(EXIT_FAILURE);
            }
            // This child won, let it exit gracefully, pipe end closed in race_and_report
            _exit(EXIT_SUCCESS);
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
        // Winning child may have already exited gracefully, ESRCH is no such process, 
        // so we don't want that to output an error message.
        if (kill(children[i], SIGTERM) == -1 && errno != ESRCH) {
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

int race_and_report(Data& d, int pipes[N][2], std::bitset<N> fd_exists, size_t i) {
    // Seed child's residue selector with its pid
    srand(getpid());

    // Close the read end
    if (close(pipes[i][READ_END]) == -1) {
        perror("Closing pipe failed");
        return EXIT_FAILURE;
    }

    // Close all other ends that exist
    for (size_t j = 0; j<N; ++j) {
        if (j==i) continue;
        if (!fd_exists[j]) break;

        if (close(pipes[j][WRITE_END]) == -1 || close(pipes[j][READ_END]) == -1) {
            perror("Closing pipe failed");
            return EXIT_FAILURE;
        }

    }

    // Start child at 300 fuel, and zero distance traveled
    int fuel = MAX_FUEL;
    int dist_traveled = 0;

    // The children can not escape this loop unless they win or exit with status 1
    for (;;sleep(1)) {
        int progress = (rand() % MOD) + 10;

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

        d.distance = dist_traveled;
        d.fuel = fuel;

        // Send new data to parent
        ssize_t n = write(pipes[i][WRITE_END], &d, sizeof(d));

        // Bad, errno set
        if (n < 0) {
            perror("Failed to write childs progress to pipe");
            return EXIT_FAILURE;
        } 
        // No space to write full progress, also bad
        else if (n != sizeof(d)) {
            std::cerr << "Not enough space to write progress for child " << i+1 << '\n'; 
            return EXIT_FAILURE;
        }
        // Otherwise, n == sizeof(d), the write is good
            
        // This child has won the race
        if (dist_traveled >= GOAL) {
            if (close(pipes[i][WRITE_END]) == -1) {
                perror("Failed to close pipe");
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }
    }
}

int output_progress(pid_t children[N], int pipes[N][2], bool& done, size_t& winner) {

    Data d;

    // Get progress report for each child
    for (int i=0; i<N; ++i) {
        // Try to read data from child i
        ssize_t n = read(pipes[i][READ_END], &d, sizeof(d));

        // Child has exited, pipe ends closed for that child
        if (n == 0) {
            continue; 
        // Error, errno set 
        } else if (n < 0) {
            perror("Failed to read from pipe");
            return EXIT_FAILURE;
        }
        // Otherwise the read is good

        _uint distance = d.distance;
        _uint fuel = d.fuel;

        // Use scale to find width of progress bar
        size_t width = xScale(distance);

        // Output child is progress
        cout << "Spaceship " << i+1 << " (" << children[i] << "): (" << width << ") ";
        for (size_t w = 0; w < width; ++w) { cout << "="; } cout << " ";
        cout << distance << " light-years, fuel " << fuel << "\n\n";

        // Child i reached goal
        if (distance >= GOAL) {
            done = true, winner = i+1;
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

// Main at the bottom
int main(int argc, char** argv) {
    return procman();
}
