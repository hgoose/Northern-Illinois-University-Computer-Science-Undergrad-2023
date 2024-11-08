#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <regex.h>
#include <cstring>
#include <string>
#include <sys/sendfile.h> // For sendfile (optional, if you use it)
#include <fcntl.h> // For open
#include <sys/stat.h> // For stat
#include <dirent.h>

#define ERR_NONVALID_PATH_ "Error: Nonvalid path"
// Non discernible path name (NDPN)
#define ERR_NDPN "Failed to disern any info about the requested pathname"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

enum REQ_TYPE {
    _NON_VALID_PATH_TYPE = -1,
    _DIR,
    _FILE
};


bool validatePath(const char* path) {
    regex_t regex;
    regmatch_t pmatch[1];
    int rv;
    char errbuf[100];

    if (strstr(path, "..") != NULL) {
        cerr << ERR_NONVALID_PATH_ << endl;
    }

    const char* path_pattern = "^/([^\\s]*/?)*$";

    if (regcomp(&regex, path_pattern, REG_EXTENDED) != 0) {
        cerr << ERR_NDPN << endl;
        return false;
    }

    rv = regexec(&regex, path, 1, pmatch , 0);

    if (!rv) {
        return true;
    } else if (rv == REG_NOMATCH) {
        regfree(&regex);
        cout << ERR_NONVALID_PATH_ << endl;
        return false;
    } else {
        regerror(rv, &regex, errbuf, sizeof(errbuf));
        regfree(&regex);
        cout << "Failed... " << errbuf << endl;
        return false;
    }
}

signed discernPathType(const char* path) {
    // Opts:
    //  0 - Directory (_DIR)
    //  1 - File (_FILE)
    
    regex_t regex;
    int rv;
    regmatch_t pmatch[1];
    char errbuf[100];

    const char* pattern = "^/([^\\s]*/?)*.*\\..*";

    if(regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        cerr << ERR_NDPN << endl;
        return _NON_VALID_PATH_TYPE;
    }

    rv = regexec(&regex, path, 1, pmatch, 0);

    if (!rv) {
        regfree(&regex);
        return _FILE;
    } else if (rv == REG_NOMATCH) {
        regfree(&regex);
        return _DIR;
    } else {
        regerror(rv,&regex, errbuf, sizeof(errbuf));
        regfree(&regex);
        cout << "Failed... " << errbuf << endl;
        return _NON_VALID_PATH_TYPE;
    }
}

std::string getFullPath(const char* serverPath, const char* clientPath) {

    std::string spath = serverPath, fullpath;

    if (!spath.empty() && spath.back() == '/') {
        spath.pop_back();
    }

    return spath + clientPath;
}

bool hasPrefix(const char* src, const char* prefix) {

    size_t prefix_len = strlen(prefix);

    if (strlen(prefix) > strlen(src)) {
        return false;
    }

    for (size_t i = 0; i<prefix_len; ++i) {
        if (src[i] != prefix[i]) {
            return false;
        }
    }
    return true;
}

void sendFile(int sockFD, const char* path) {
    int fileFd = open(path, O_RDONLY);
    if (fileFd < 0) {
        if (write(sockFD, "Failed to open file", 20) < 0) {
            perror("write");
        }
        perror("Failed to pen file");
        exit(EXIT_FAILURE);
    }

    // Get file size using fstat
    struct stat fileStat;
    if (fstat(fileFd, &fileStat) < 0) {
        if (write(sockFD, "Failed to get file statistics", 20) < 0) {
            perror("write");
        }
        perror("Failed to get file statistics");
        close(fileFd);
        exit(EXIT_FAILURE);
    }

    // Send file contents using sendfile
    off_t offset = 0;
    ssize_t sentBytes = sendfile(sockFD, fileFd, &offset, fileStat.st_size);
    if (sentBytes < 0) {
        if (write(sockFD, "Failed to send file", 20) < 0 ) {
            perror("write");
        }
        perror("Failed to send file");
        close(fileFd);
        exit(EXIT_FAILURE);
    }

    // Close the file descriptor
    close(fileFd);

}

void listDirectory(int sockFd, const char* dirPath) {
    DIR* dir = opendir(dirPath);
    if (!dir) {
        perror("Failed to open directory");
        return;
    }

    struct dirent* entry;
    char buffer[1024];
    int len = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') { // Skip hidden files
            len += snprintf(buffer + len, sizeof(buffer) - len, "%s\n", entry->d_name);
            if (len >= sizeof(buffer)) break; // Buffer full
        }
    }

    write(sockFd, buffer, len); // Send the list of files
    closedir(dir);
}

void handleDirectoryRequest(int sockFD, const char* path) {

    char indexPath[1024];
    snprintf(indexPath, sizeof(indexPath), "%s/index.html", path);

    struct stat statBuf;
    if (stat(indexPath, &statBuf) == 0 && S_ISREG(statBuf.st_mode)) {
        sendFile(sockFD, indexPath);
    } else {
        listDirectory(sockFD, path);
    }
}

void procReq(int connSock, const char* serverPath) {
    char buf[1024];
    int received = 0;
    unsigned pathtype = 0;
    std::string fullpath;

    if ((received = read(connSock, buf, sizeof(buf))) <= 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    if (!hasPrefix(buf, "GET")) {
        cerr << ERR_NONVALID_PATH_ << endl;
        exit(EXIT_FAILURE);
    }

    const char* start = strchr(buf, '/'); 
    const char* end = buf + (strlen(buf));

    size_t pathLength = end - start;

    char clientPath[pathLength + 1]; 
    strncpy(clientPath, start, pathLength);
    clientPath[pathLength] = '\0'; 

    fullpath = getFullPath(serverPath, clientPath);

    pathtype = discernPathType(fullpath.c_str());

    switch (pathtype) {
        case _DIR:
            handleDirectoryRequest(connSock, fullpath.c_str());
            break;
        case _FILE:
            sendFile(connSock, fullpath.c_str());
            break;
    }

    close(connSock);
    exit(EXIT_SUCCESS);
}

int main(int argc, const char* argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: ./z2004109 <port> <pathname>" << endl;
        exit(EXIT_FAILURE);
    }

    if (!validatePath(argv[2])) {
        exit(EXIT_FAILURE);
    }


    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0 ) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    unsigned addrlen = sizeof(client_address);

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(atoi(argv[1]));

    if (bind(sock, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(sock, 64) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true) {
        int connSock = accept(sock, (struct sockaddr*) &client_address, &addrlen);
        if (connSock < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        if (fork()) {
            close(connSock);
        } else {
            procReq(connSock, (char*) argv[2]);
        }
    }
    close(sock);

    return EXIT_SUCCESS;
}
