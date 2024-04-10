#include <cstdlib>
#include <iostream> // For input/output tasks
#include <iomanip> // For input/output manipulators
#include <unistd.h> // File stuff
#include <fcntl.h> // O_WRONLY, etc...
#include <sys/stat.h> // File stats
#include <cstring>

// Some macros

// Using
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

enum {
    _NO_C = 3,
    _HAS_C
};

// Usage ./z2004109 [-c] out_file message_string
int main(int argc, const char* argv[]) {

    const char* out_file, *message_string;
    struct stat fileStat;
    int fd, count; 
    ssize_t n_bytes;
    bool has_c = 0;

    switch (argc) {
        case _NO_C:
            out_file = argv[1];
            message_string = argv[2];
            break;

        case _HAS_C:
            out_file = argv[2];
            message_string = argv[3];
            has_c = 1;
            break;

        default:
            printf("%s\n\t%s\n\t%s\n", "Usage: ./z2004109 [-c] out_file message_string", 
                    "Where the message string is appended to out_file",
                    "The -c option clears the file before the message is appended");
            exit(EXIT_FAILURE);
    }

    fd = open(out_file, O_WRONLY | O_CREAT, 0000);
    close(fd);

    if (stat(out_file, &fileStat) < 0) {
        perror("Failed to retrieve file stats");
        exit(EXIT_FAILURE);
    }

    if (fileStat.st_mode & S_IRUSR 
            || fileStat.st_mode & S_IWUSR 
            || fileStat.st_mode & S_IXUSR 
            || fileStat.st_mode & S_IRGRP 
            || fileStat.st_mode & S_IWGRP 
            || fileStat.st_mode & S_IXGRP 
            || fileStat.st_mode & S_IROTH 
            || fileStat.st_mode & S_IWOTH 
            || fileStat.st_mode & S_IXOTH) {
        std::cerr <<  out_file << " is not secure. Ignoring" << endl;
    }

    if (chmod(out_file, S_IWUSR) < 0) {
        perror("Failed to change file permissions");
        exit(EXIT_FAILURE);
    }

    fd = open(out_file, O_WRONLY | (has_c ? O_TRUNC : O_APPEND));
    if (fd == -1) {
        perror("Failed to open file for writing");
        chmod(out_file, 0000);
        exit(EXIT_FAILURE);

    }
    if (write(fd, message_string, strlen(message_string)) < 0 || write(fd, "\n", 1) < 0 ) {
        perror("Failed to write message to file");
        close(fd);
        chmod(out_file, 0000);
        exit(EXIT_FAILURE);
    }

    if (chmod(out_file, 0000)) {
        perror("Failed to clear permissions");
        exit(EXIT_FAILURE);
    }

    close(fd);
    
    return EXIT_SUCCESS;
}
