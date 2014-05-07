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
	char *WebServerName;
	char *WebServerPortNum;
	getWebServerName(data, WebServerName, WebServerPortNum);
	printf("WebServerName = %s \n", &WebServerName);
	printf("WebServerPortNum = %s \n", &WebServerPortNum);
}



void getWebServerName(char *buffer, char *WebServerName, char *WebServerPortNum){
	char* token;
	int i = 0;
	printf("buffer %s \n",buffer);
	printf("=========== \n");
	if (buffer != NULL) {
		while ((token = strsep(&buffer, ";")) != NULL)
		{
			if(i == 1){
				printf("token = %s \n", token);
				WebServerName = token;
			}else if(i == 2){
				printf("token = %s \n", token);

				WebServerPortNum = token;
			}

			i++;
		}
	}
}