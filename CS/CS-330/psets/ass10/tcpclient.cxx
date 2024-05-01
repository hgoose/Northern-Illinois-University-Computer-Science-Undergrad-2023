/*
 * TCPClient.cxx
 * 
 * TCP client
 * 
 * 	sends message to TCP server
 * 	waits for message received from server 
 * 	      
 * 	command line arguments:
 * 		argv[1] FQDN of server
 * 		argv[2] port number to send to
 * 		argv[3] request to send
 *  
 */
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 4) {
		cerr << "USAGE: TCPClient server_name port request\n";
		exit(EXIT_FAILURE);
	}	
	// lookup FQDN
	struct addrinfo *res, hints;
		
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	int error = getaddrinfo(argv[1], argv[2], &hints, &res);
	if (error) {
		cerr << argv[1] << ": " << gai_strerror(error) << endl;
		exit(EXIT_FAILURE);
	}		
	char buffer[1024];
	int sent, received;
	
	// Create the TCP socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("Failed to create socket");
		exit(EXIT_FAILURE);
	}	
	
	// connect to server
	if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
		perror("connect");
		exit(EXIT_FAILURE);
	}
		
	// Send the message string to the server 
	sent = write(sock, argv[3], strlen(argv[3])+1);
	if (sent < 0) {
		perror("write");
		exit(EXIT_FAILURE);
	}
			
	// Receive the message back from the server 
	do {
		received = read(sock, buffer, sizeof(buffer));
		if (received < 0) {
			perror("read");
			exit(EXIT_FAILURE);
		}
		cout.write(buffer, received);
	} while (received > 0);
	cout << endl;	
		
	close(sock);
}
