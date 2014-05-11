#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>  

#include "logger.h"
#include "connection.h"


// struct User{
// 	ip
// 	...
// }

// struct Users activeusers[64];
void getWebServerName(char *buffer,char *WebServerName, char *WebServerPortNum);


void *handle(void *sockfd){
	char buffer[256];
	int clientSockfd = *(int*)sockfd;
	int n, serverSockfd;
	char WebServerName[50];
	char WebServerPortNum[50];
	bzero(buffer,256);
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
	char* token;
	int i = 0;
	if (buffer != NULL) {
		while ((token = strsep(&buffer, ";")) != NULL)
		{
			if(i == 1){
				strcpy(WebServerName,token);
			}else if(i == 2){
				strcpy(WebServerPortNum,token);
			}

			i=i+1;
		}
	}
}