// Server side implementation of UDP client-server model
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	 8080
#define MAXLINE 1024
	

int main() {
	int sockfd;
	char buffer[MAXLINE];
	
	struct sockaddr_in servaddr, cliaddr;
		
	
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
		
	int n;
    socklen_t len;
	
	len = sizeof(cliaddr); 
	while (true)
	{
		recvfrom(sockfd, (char*)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr*)&cliaddr, &len);
		std::cout << "Client: " << buffer << std::endl;
		

		std::string str;
		str.clear();
		std::getline(std::cin, str);

		sendto(sockfd, str.c_str(), strlen(str.c_str()), MSG_CONFIRM, (const struct sockaddr*)&cliaddr, len);
		std::cout << "Server: " << str << std::endl;
		
	}
	
		
	return 0;
}
