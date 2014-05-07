#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "handler.h"
/* close a socket */
void close(int sockfd);

/* read a socket */
int read(int newsockfd,char* buffer,int size);


/* TODO: Function should continue to listen even when process has finished with a client */

void listenOnPort(char * port){
	int sockfd, newsockfd, portno;
	uint clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	printf("Listening on port %s\n", port);
	 /* Create TCP socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{
		perror("ERROR opening socket");
		exit(1);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	// Set the port number according to the parameter passed in
	portno = atoi(port);
	/* Create address we're going to listen on (given port number)
	 - converted to network byte order & any IP address for 
	 this machine */
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);  // store in machine-neutral format
	/* Bind address to the socket */
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			sizeof(serv_addr)) < 0) 
	{
		perror("ERROR on binding");
		exit(1);
	}

	/* Listen on socket - means we're ready to accept connections - 
	 incoming connection requests will be queued */
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	/* Accept a connection - block until a connection is ready to
	 be accepted. Get back a new file descriptor to communicate on. */
	newsockfd = accept(	sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) 
	{
		perror("ERROR on accept");
		exit(1);
	}
	bzero(buffer,256);
	/* Read characters from the connection,
		then process */
	n = read(newsockfd,buffer,255);
	handle(buffer);

	close(sockfd);
}