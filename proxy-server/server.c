/* Hello World program */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "connection.h"

#define MAXUSERS 64

/*---
-- Function declarations
---*/

/* returns a readable date as a string */
char * getReadableTime();

/* configures a new server on startup */
struct Server config(char * port, int timeout);

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
   char * port;
   int timeout;
   struct Client users[MAXUSERS];
};

int main(int argc, char **argv)
{
	if (argc < 2) 
	{
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	//config a server
	struct Server s = config(argv[1], 500);
	//launch server
	luanchServer(s);

	return 0;
}

void logger(char* message){
	printf("proxy-server [%s]: %s\n", getReadableTime(), message);
}

struct Server config(char * port, int timeout){
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
	listenOnPort(s.port);
}


