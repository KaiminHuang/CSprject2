#ifndef CONNECTION_H

void listenOnPort(char * port);

//establish connection to the web server
int connectServer(char* serverName, char *webportno);

//send request to web server
void sendRequest(char* serverName, char *webportno, int sockfd);

//get return message from Web server and send them back to the client
int getAndSendReturn(int clientSocket, int serverSocket);

#endif