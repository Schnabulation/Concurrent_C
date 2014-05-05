/* Author: Steve Heller
 * 
 * Small client for testing purposes.
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

void main() {
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

  printf("CONNECTED!\n");

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
