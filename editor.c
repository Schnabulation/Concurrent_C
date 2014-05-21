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
  if (strncmp(inputArg,"InsertLines",3) == 0) {
    InsertLines(inputArg);
  } else if (strncmp(inputArg,"ReplaceLines",3) == 0) {
    ReplaceLines(inputArg);
  } else if (strncmp(inputArg,"ReadLines",3) == 0) {
    ReadLines(inputArg);
  } else if (strncmp(inputArg,"DeleteLines",3) == 0) {
    DeleteLines(inputArg);
  } else if (strncmp(inputArg,"NumLines",3) == 0) {
    NumLines(inputArg);
  } else {
    printf("Invalid command\n");
  }
}

void runProcess(int clientSock) {
  printf("Client connected with process %ld!\n", (long)getpid());   
  while (1) {
    char buffer[256];
    bzero(buffer,256);  
    read(clientSock,buffer,255);
    if (strcmp(buffer,"EXIT") == 0) {
      printf("Client disconnected\n");
    break;
    } else {
      runCommand(buffer);
    }
  }
  close(clientSock);
}

void startServer() {
  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;
  unsigned int clientAddressLen;
  pid_t childpid;

  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  

  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = 2354; 

  if (bind(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
    perror("ERROR on binding");
  }

  listen(sock, 5);
  printf("Server started - waiting for connection on Port %i\n",serverAddress.sin_port); 
  while(1) {
    int clientSock = accept(sock, (struct sockaddr *) & clientAddress, &clientAddressLen);
    childpid = fork();
    if (childpid == -1) {
      perror("Fork failed!");
    }
    if (childpid == 0) {
      runProcess(clientSock);
      break;
    } else {
      // if there is something that only the parent-process should do, put it here
    }
  }
  close(sock);
}

void main(int argc, char *argv[]) {
  startServer();
}
