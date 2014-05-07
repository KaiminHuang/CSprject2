#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

struct stat st = {0};

char * getReadableTime();

void logRequest(char * ipAddress,char * port,int size,char * host){
	
	if (stat("./logs", &st) == -1) {
    	mkdir("./logs", 0700);
	}

	FILE * fp;
	fp = fopen("./logs/proxy.log", "a");
	fprintf(fp, "%s,%s,%s,%d,%s\n", getReadableTime(), ipAddress, port, size, host);
	fclose(fp);
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