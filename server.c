/* Hello World program */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
/*---
-- Function declarations
---*/

#define MAXUSERS 64

/* returns a readable date as a string */
char * getReadableTime();

/* logs information throughout the code */
void logger(char * message);

/* configures a new server on startup */
struct Server config(int port, int timeout);

/* launches the server */
void luanchServer (struct Server s);

/* stores a single request */
struct connectionDetails {
	char * host;
	int  * port;
};

/* individual client details (per connection) */
struct Client {
	struct connectionDetails clientDetails;
	struct connectionDetails requestDetails;
};

/* new proxy server object */
struct Server {
   int port;
   int timeout;
   struct Client users[MAXUSERS];
};

int main(int argc, char **argv)
{
	int sockfd, newsockfd, portno, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	if (argc < 2) 
	{
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	 /* Create TCP socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{
		perror("ERROR opening socket");
		exit(1);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	// Set the port number according to the parameter passed in
	portno = atoi(argv[1]);
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
	newsockfd = accept(	sockfd, (struct sockaddr *) &cli_addr, 
						&clilen);
	if (newsockfd < 0) 
	{
		perror("ERROR on accept");
		exit(1);
	}
	bzero(buffer,256);
	/* Read characters from the connection,
		then process */
	n = read(newsockfd,buffer,255);

	logger(buffer);

	close(sockfd);
	//config a server
	struct Server s = config(1234, 500);
	//launch server
	// luanchServer(s);

	return 0;
}

void logger(char* message){
	printf("proxy-server [%s]: %s\n", getReadableTime(), message);
}

struct Server config(int port, int timeout){
	struct Server newServer;
	newServer.port = port;
	newServer.timeout = timeout;
	return newServer;
}

char * getReadableTime(){
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	char * realTime = asctime (timeinfo);
	realTime[strlen(realTime)-1] = '\0';
	return realTime;
}

void luanchServer (struct Server s){
	while(1) {

		// 1. receive connection from client
		// 2. store connection details
		//		-- GET, POST
		//		-- standard, http, https etc.
		// 3. request external host
		// 4. get response and send it to client
		// 5. log details

	}
}


