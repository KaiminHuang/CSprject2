#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>  

#include "logger.h"


// struct User{
// 	ip
// 	...
// }

// struct Users activeusers[64];
void getWebServerName(char *buffer, char *WebServerName, char *WebServerPortNum);


void handle(char* data){
	char WebServerName[50];
	char WebServerPortNum[50];
	getWebServerName(data, WebServerName, WebServerPortNum);
	printf("WebServerName = %s \n", WebServerName);
	printf("WebServerPortNum = %s \n", WebServerPortNum);
}



void getWebServerName(char *buffer, char WebServerName[], char WebServerPortNum[]){
	char* token;
	int i = 0;
	printf("buffer %s \n",buffer);
	if (buffer != NULL) {
		while ((token = strsep(&buffer, ";")) != NULL)
		{
			if(i == 1){
				printf(" \n");
				printf("token = %s \n", token);
				//WebServerName = malloc(strlen(token) + 1);
				// WebServerName = token;
				strcpy(WebServerName,token);
			}else if(i == 2){
				printf("token = %s \n", token);
				//WebServerPortNum = malloc(strlen(token) + 1);
				// WebServerPortNum = token;
				strcpy(WebServerPortNum,token);
			}

			i=i+1;
		}
	}
}