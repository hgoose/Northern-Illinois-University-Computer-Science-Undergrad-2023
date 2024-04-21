#include <iostream> // For Input/OUtput tasks
#include <string>
#include <cstdlib> // For random, system, exit, EXIT_SUCCESS, EXIT_FAILURE, and malloc
#include <unistd.h> // For unix sys calls file stuff and sleep
#include <cstdio> // C standard
#include <fcntl.h> // O_WRONLY, etc...
#include <sys/stat.h> // File stats
#include <sys/types.h> // Types
#include <dirent.h>
#include <regex.h>
#include <sys/wait.h> // wait system call
#include <vector>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::istringstream;

#define _MAX_ARGS 5 

int main(int argc, const char* argv[]) {

    string input;
    pid_t pid, status;

    cout << "Enter command: ";
    while (getline(cin, input) && input != "exit") {

        istringstream getargs(input);
        std::vector<string> str_args;
        std::vector<char*> args;
        string arg_tmp; 

        while (getargs >> arg_tmp) {
            str_args.push_back(arg_tmp);
        }

        if (str_args.size() > _MAX_ARGS) {
            cerr << "Error: Too many args passed in execution" << endl;
            exit(EXIT_FAILURE);
        }

        for (auto& each_arg : str_args) {
            args.push_back(&each_arg[0]);
        }
        args.push_back(nullptr);

        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Child process 
            execvp(args[0], args.data());
            perror(args[0]);
            exit(EXIT_FAILURE);

        } else { // Parent
            wait(&status);

        }
        cout << "Enter command: ";
    }

    return EXIT_SUCCESS;
}
