/* server.c
	avin chadee - kaimin huang
	
	executable point of origin
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "connection.h"


/* configures a new server on startup */
struct Server config(char * port);

/* launches the server */
void luanchServer (struct Server s);

/* new proxy server object */
struct Server {
   char * port;
};

int main(int argc, char **argv)
{
	if (argc < 2) 
	{
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	//config a server
	struct Server s = config(argv[1]);
	//launch server
	luanchServer(s);

	return 0;
}

struct Server config(char * port){
	struct Server newServer;
	newServer.port = port;
	return newServer;
}

/* luanchs the server */
void luanchServer (struct Server s){
	listenOnPort(s.port);
}


