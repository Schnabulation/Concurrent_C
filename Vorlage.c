/* Author: Steve Heller, Severin Müller
 * Date: 09.04.14
 * Homework: KW 14
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
      printf("%s\n",buffer);
    }
    close(clientSock);
  }
  close(sock);
}

void startClient() {
  printf("Starting Client!\n");
  printf("Please wait...\n");

  int sock;
  struct sockaddr_in serverAddress;
  unsigned short server_port;
  char *server_ip;
  int bytes_received, total_bytes_received;

  server_ip = "127.0.0.1";
  server_port = 2354;
  
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = inet_addr(server_ip);
  serverAddress.sin_port = server_port;

  int breakUp = 0;
  while (breakUp == 0) {
    char input_string[256];
    char *p;
    unsigned int inputStringLen;
    fgets(input_string, sizeof(input_string), stdin);       
    if ((p = strchr(input_string, '\n')) != NULL) {
      *p = '\0';
    }
    if (strcmp(input_string,"EXIT") == 0) {
      printf("You disconnected!\n");
      breakUp = 1;
    }
    inputStringLen = strlen(input_string);
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    int count = send(sock, input_string, inputStringLen, 0);
    if (count != inputStringLen) {
      error("send() sent a different number of bytes than expected");
    }
    close(sock);
  }

}

void main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("This is a small one-direction chat programm. It includes Server\n");
    printf("and Client side. Usage as follow:\n\n");
    printf("To start the Servercomponent: %s -s\n",argv[0]);
    printf("To start the Clientcomponent: %s -c\n",argv[0]);
    exit(0);
  } else if (strcmp(argv[1], "-s") == 0) {
      startServer();
  } else if (strcmp(argv[1], "-c") == 0) {
      startClient();
  } else {
      main(1,argv);
  }
}
