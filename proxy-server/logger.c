#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

struct stat st = {0};

char * getReadableTime();

void logRequest(int s){

	char ipstr[INET6_ADDRSTRLEN];
	uint client;
	int port;
	
	struct sockaddr_in serv_addr, cli_addr;
	client = sizeof(cli_addr);

	getpeername(s, (struct sockaddr*)&cli_addr, &client);
	struct sockaddr_in *sockfd = (struct sockaddr_in *)&cli_addr;
	port = ntohs(sockfd->sin_port);
	inet_ntop(AF_INET, &sockfd->sin_addr, ipstr, sizeof ipstr);

	printf("Peer IP address: %s\n", ipstr);
	printf("Peer port      : %d\n", port);


	// if (stat("./logs", &st) == -1) {
 //    	mkdir("./logs", 0700);
	// }

	// FILE * fp;
	// fp = fopen("./logs/proxy.log", "a");
	//TODO replace the old varables
	//fprintf(fp, "%s,%s,%s,%d,%s\n", getReadableTime(), ipAddress, port, size, host);
	// fclose(fp);
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