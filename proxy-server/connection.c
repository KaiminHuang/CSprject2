/* connection.c
   avin chadee - kaimin huang

   handles inbound an outbound server logic, contains only logic that creates 
   threads, listeners and sockets. does not contain any business logic (AKA) 
   telling the server to forward the request to a webserver and wait for a 
   return
*/



#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <pthread.h>
#include "handler.h"
#include "logger.h"


/* close a socket */
void close(int sockfd);

/* read a socket */
int read(int newsockfd,char* buffer,int size);

/*	Establishes a instance of a HTTP GET server on the given port number
	and sets up a listner to listen and fork incoming requests
		
		char * port : the port number as a string taken from argc
*/
void listenOnPort(char * port){
	/* init basic variables */
	int sockfd, newsockfd, portno;
	uint client;
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	/* Create TCP socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	/* Catch any errors after creation */
	if (sockfd < 0) 
	{
		perror("ERROR opening socket");
		exit(1);
	}

    /* Get the address info */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(port);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno); 

	/* Bind address to the socket */
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0) 
	{
		perror("ERROR on binding");
		exit(1);
	}

    /* Listen */
	listen(sockfd,5);
	client = sizeof(cli_addr);
	while(1){
		newsockfd = accept(	sockfd, (struct sockaddr *) &cli_addr, &client);
		/* handle errors on accepting the connection */
		if (newsockfd < 0) 
		{
			perror("ERROR on accept");
			/* TODO  - not sure if it should be exiting here */
			exit(1);
		}else{

			/* fork off new processes every time a request is made */
			pthread_t thread;
			if (pthread_create(&thread, NULL, handle, &newsockfd) != 0) {
				fprintf(stderr, "Failed to create thread\n");
			}
			
		}

	}
	close(sockfd);

}

/* Establishes a connection with a given webhost name and port number
	char * serverName : string of the server name e.g. google.com
	char * webportno  : port number of the given web host, defualts to 80
*/
int connectServer(char* serverName, char *webportno){
	int sockfd, n, webPortno;
	struct sockaddr_in serv_addr;
	struct hostent *webserver;
	webportno = "80";

	/* kill outbound request if the host doesn't exist */
	if ((serverName==NULL) || (webportno==NULL))
	{
		printf("empty serverName or port number\n");
		exit(0);
	}
	
	webPortno = atoi(webportno);
	/* Translate host name into peer's IP address ;
	 * This is name translation service by the operating system 
	 */
	 webserver = gethostbyname(serverName);

	/* kill outbound request if the ip doesn't exist */
	 if (webserver == NULL) 
	 {
	 	fprintf(stderr,"ERROR, no such host\n");
	 	return -1;
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
	
	/* Error checking on the socket status */
	if (sockfd < 0) 
	{
		perror("ERROR opening socket");
		return(-1);
	}
	
	if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
	{
		perror("ERROR connecting");
		return(-1);
	}
	return sockfd;

}

/* 	creates default GET template and sends a request to that server
		char * serverName : name of the server
		char * webportno  : port number
		int sockfd 		  : socket id, generated in connect server
*/
void sendRequest(char* serverName, char *webportno, int sockfd){
	char buffer[256];
	int n;
	printf("WebServerName: %s\n", serverName);
	buffer[0] = '\0';
	strcat(buffer,"GET / HTTP/1.1\nHost: ");
	strcat(buffer,serverName);
	strcat(buffer,"\nConnection: close\r\n\r\n");

	// send request
	n = write(sockfd,buffer,strlen(buffer));
	if (n < 0) 
	{
		perror("ERROR writing to socket");
		exit(0);
	}

}

/* 	gets a request from the client and sends it to the handler to process
		int clientSocket  : id of socket
		int serverSocket  : id of server socket
*/
int getAndSendReturn(int clientSocket, int serverSocket){
	char buffer[256];
	int cn, sn;
	bzero(buffer,256);

	//read the return file from server
	sn = read(serverSocket,buffer,256);
	int size = 0;
	// output the reuturn file
	while(sn > 0){
		size += sn;
		cn = write(clientSocket,buffer,strlen(buffer));
		bzero(buffer,256);
		sn = read(serverSocket,buffer,256);
	}

	if (sn < 0)
	{
		perror("ERROR reading from server socket");
		exit(0);
	}
	
	if (cn < 0) 
	{
		perror("ERROR writing to client socket");
		exit(0);
	}

	return size;
}
