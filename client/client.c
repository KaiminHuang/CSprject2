
/* A simple client program for server.c

   To compile: gcc client.c -o client -lsocket -lnsl
   				      (-l links required on csse Unix machines)	

   To run: start the server, then the client */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 


int write(int sockfd,char *buffer, int length);

int read(int sockfd,char *buffer, int length);

int main(int argc, char**argv)
{
	int sockfd,proxyportno, n;
	struct sockaddr_in serv_addr, proxy_addr;
	struct hostent *proxy;
	struct hostent *webserver;
	char *webportno;

	// const char *webportno = *argv[4];
	
	// printf("%s\n", argv[4]);
	// printf("%d\n", *webportno);
	char buffer[256];

	if (argc < 4) 
	{
		fprintf(stderr,"usage %s proxyHostName proxyport hostname\n", argv[0]);
		exit(0);
	}

	proxyportno = atoi(argv[2]);
	webportno = "80";
	
	/* Translate host name into peer's IP address ;
	 * This is name translation service by the operating system 
	 */
	proxy = gethostbyname(argv[1]);
	webserver = gethostbyname(argv[3]);
	
	if (proxy == NULL) 
	{
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	
	/* Building data structures for socket */
	bzero((char *) &proxy_addr, sizeof(proxy_addr));

	proxy_addr.sin_family = AF_INET;

	bcopy((char *)proxy->h_addr, 
			(char *)&proxy_addr.sin_addr.s_addr,
			proxy->h_length);

	proxy_addr.sin_port = htons(proxyportno);

	/* Create TCP socket -- active open 
	* Preliminary steps: Setup: creation of active open socket
	*/
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0) 
	{
		perror("ERROR opening socket");
		exit(0);
	}
	
	if (connect(sockfd,(struct sockaddr *)&proxy_addr,sizeof(proxy_addr)) < 0) 
	{
		perror("ERROR connecting");
		exit(0);
	}
	// set up the request
	buffer[0] = '\0';
	strcat(buffer,"GET http://");
	strcat(buffer,	argv[3]);
	strcat(buffer,"/ HTTP/1.0\r\n\r\n");
	// send request
	n = write(sockfd,buffer,strlen(buffer));

	if (n < 0) 
	{
		perror("ERROR writing to socket");
		exit(0);
	}
	bzero(buffer,256);


	printf("this is the return =====> \n");

	//read the return file from server
	n = read(sockfd,buffer,256);
	printf("%s",buffer);
	// output the reuturn file
	while(n >0 ){
		bzero(buffer,256);
		n = read(sockfd,buffer,256);
		printf("%s",buffer);
	}
	if (n < 0)
	{
		perror("ERROR reading from socket");
		exit(0);
	}
	return 0;
}
