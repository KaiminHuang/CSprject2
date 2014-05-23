#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>  
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <regex.h>

#include "logger.h"
#include "connection.h"



// struct User{
// 	ip
// 	...
// }

// struct Users activeusers[64];
void getWebServerName(char *buffer,char *WebServerName, char *WebServerPortNum);


void handle(void *sockfd){
	char buffer[256];
	int clientSockfd = *(int*)sockfd;
	int n, serverSockfd;
	char WebServerName[50];
	char WebServerPortNum[50];
	bzero(buffer,256);
	uint clilen;

	struct sockaddr_in cli_addr;
	clilen = sizeof(cli_addr);


	/* Read */
	n = read(clientSockfd,buffer,255);
	getWebServerName(buffer, WebServerName, WebServerPortNum);
	/* Send request to web server */
	serverSockfd = connectServer(WebServerName, WebServerPortNum);
	sendRequest(WebServerName, WebServerPortNum, serverSockfd);
	/* Return */
	getAndSendReturn(clientSockfd, serverSockfd);
}



void getWebServerName(char *buffer, char WebServerName[], char WebServerPortNum[]){
	/* get hostname from GET request */
	regex_t regex;
	int reti;
	reti = regcomp(&regex, "GET http://(.*)/ HTTP/1.0", 
		REG_ICASE | REG_EXTENDED);

	const char * p = buffer;
	const int n_matches = 2;
	regmatch_t m[n_matches];
	// execute regular expression
	reti = regexec(&regex, p, n_matches, m, 0);
	if (reti == 0)
	{
		/* match found, get hostname from the request, it is test version 2 */
		int start = m[1].rm_so + (p - buffer);
		int finish = m[1].rm_eo + (p - buffer);

		strncpy(WebServerName,p + m[1].rm_so,finish - start);
	} else {
		/* no match, it is test version 1 */
		WebServerName = buffer;
	}

	

}