/* Author: Steve Heller
 * 
 * This is the mainfile of my project.
 * It includes the server and further importend stuff.
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
#include <signal.h>
#include "includes/lockingFunctions.h"
#include "includes/editorFunctions.h"
#include "includes/processFunctions.h"

int sock;

void startServer() {
  if (setup_shm() == 1) {
    perror("Error on setup_shm!\n");
  }
  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;
  unsigned int clientAddressLen;
  pid_t childpid;

  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  

  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = 2354; 

  if (bind(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
    perror("ERROR on binding");
  }

  listen(sock, 5);
  printf("**********************************\n");
  printf("*             SERVER             *\n");
  printf("**********************************\n");
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

void shutdownServer() {
  printf("Server shutting down...\n");
  shutdown_shm();
  close(sock);
  exit(0);
}

void main(int argc, char *argv[]) {
  signal(SIGINT, shutdownServer);
  startServer();
}
