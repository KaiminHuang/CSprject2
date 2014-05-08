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
void getWebServerName(char *buffer, char *WebServerName, char *WebServerPortNum);


void handle(char* buffer, int clientSockfd){
	int n, serverSockfd;
	char WebServerName[50];
	char WebServerPortNum[50];
	getWebServerName(buffer, WebServerName, WebServerPortNum);
	serverSockfd = connectServer(WebServerName, WebServerPortNum);
	sendRequest(WebServerName, WebServerPortNum, serverSockfd);
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