#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

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
	handle(buffer, newsockfd);
	close(sockfd);
}

/* connectServer take portNum, serv_addr as parameters, and setting up connectin with web server 
than sending the buffer to web server*/
int connectServer(char* serverName, char *webportno){
	int sockfd, n, webPortno;
	struct sockaddr_in serv_addr;
	struct hostent *webserver;

	

	if ((serverName==NULL) || (webportno==NULL))
	{
		printf("empty serverName and port number\n");
		exit(0);
	}
	
	webPortno = atoi(webportno);
	/* Translate host name into peer's IP address ;
	 * This is name translation service by the operating system 
	 */
	 webserver = gethostbyname(serverName);

	 if (webserver == NULL) 
	 {
	 	fprintf(stderr,"ERROR, no such host\n");
	 	exit(0);
	 }

	/* Building data structures for socket */
	 bzero((char *) &serv_addr, sizeof(serv_addr));

	 serv_addr.sin_family = AF_INET;

	 bcopy((char *)webserver->h_addr, 
	 	(char *)&serv_addr.sin_addr.s_addr,
	 	webserver->h_length);

	 serv_addr.sin_port = htons(webPortno);

	/* Create TCP socket -- active open 
	* Preliminary steps: Setup: creation of active open socket
	*/
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0) 
	{
		perror("ERROR opening socket");
		exit(0);
	}
	
	if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
	{
		perror("ERROR connecting");
		exit(0);
	}
	return sockfd;

}

void sendRequest(char* serverName, char *webportno, int sockfd){
	char buffer[256];
	int n;
	// set up the request
	// GET / HTTP/1.1\nHost: google.com:4000
	buffer[0] = '\0';
	strcat(buffer,"GET / HTTP/1.1\nHost: ");
	strcat(buffer,serverName);
	strcat(buffer,"\r\n\r\n");

	// send request
	n = write(sockfd,buffer,strlen(buffer));

	if (n < 0) 
	{
		perror("ERROR writing to socket");
		exit(0);
	}

}

void getAndSendReturn(int clientSocket, int serverSocket){
	char buffer[256];
	int cn, sn;
	bzero(buffer,256);
	//read the return file from server
	sn = read(serverSocket,buffer,256);
	// output the reuturn file
	while(sn ==256){
		cn = write(clientSocket,buffer,strlen(buffer));
		bzero(buffer,256);
		sn = read(serverSocket,buffer,256);
	}
	if (sn < 0)
	{
		perror("ERROR reading from server socket");
		exit(0);
	}
	cn = write(clientSocket,buffer,strlen(buffer));	
	
	if (cn < 0) 
	{
		perror("ERROR writing to client socket");
		exit(0);
	}
}
