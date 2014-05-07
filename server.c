/* Hello World program */

#include <stdio.h>
#include <time.h>
#include <string.h>

/*---
-- Function declarations
---*/


sdjhfg
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

int main(int argc, char *argv[])
{
	//config a server
	struct Server s = config(1234, 500);
	//launch server
	luanchServer(s);

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

int storeUserDetails(){

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

