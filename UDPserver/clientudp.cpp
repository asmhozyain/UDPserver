// Client side implementation of UDP client-server model
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	 8080
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from client";
	struct sockaddr_in	 servaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
		
	int n;
    socklen_t len;
    while (true)
    {
		std::string str;
		str.clear();
        std::getline(std::cin, str);
        sendto(sockfd, str.c_str(), strlen(str), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
		std::cout << "Client: " << str << std::endl;
		//printf("Hello message sent.\n");
			
		recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		std::cout << "Server: " << buffer << std::endl;
		//buffer[n] = '\0';
		//printf("Server : %s\n", buffer);
    }
    
		
	
	
	close(sockfd);
	return 0;
}
