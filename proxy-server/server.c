/* Hello World program */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "connection.h"


#define MAXUSERS 64

/*---
-- Function declarations
---*/

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

struct Server config(char * port, int timeout){
	struct Server newServer;
	newServer.port = port;
	newServer.timeout = timeout;
	return newServer;
}

void luanchServer (struct Server s){
	listenOnPort(s.port);
}


