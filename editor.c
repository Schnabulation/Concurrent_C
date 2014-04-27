/* Author: Steve Heller
 * 
 * This is the mainfile of my project.
 * It includes the server and furhter importend stuff.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "editorFunctions.h"

void runCommand(char inputArg[]) {
  if (strcmp(inputArg,"InsertLines") == 0) {
    InsertLines();
  } else if (strcmp(inputArg,"ReplceLines") == 0) {
    ReplaceLines();
  } else if (strcmp(inputArg,"ReadLines") == 0) {
    ReadLines();
  } else if (strcmp(inputArg,"DeleteLines") == 0) {
    DeleteLines();
  } else if (strcmp(inputArg,"NumLines") == 0) {
    NumLines();
  } else {
    printf("Invalid command\n");
  }
}

void startServer() {
  printf("Starting Server!\n");
  printf("Please hold on...\n");

  char buffer[256];

  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;
  unsigned int clientAddressLen;

  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = 2354;

  if (bind(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
     error("ERROR on binding");
  }
  listen(sock, 5);
  printf("Server started - waiting for connection on Port %i\n",serverAddress.sin_port);

  int breakUp = 0;
  while (breakUp == 0) {
    int clientSock = accept(sock, (struct sockaddr *) & clientAddress, &clientAddressLen);
    bzero(buffer,256);  
    read(clientSock,buffer,255);
    if (strcmp(buffer,"EXIT") == 0) {
      printf("Client disconnected\n");
      breakUp = 1;
    } else {
      runCommand(buffer);
    }
    close(clientSock);
  }
  close(sock);
}

void main(int argc, char *argv[]) {
  startServer();
}
