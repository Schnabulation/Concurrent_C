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
#include <signal.h>

int sock;

void shutdownClient() {
  send(sock, "EXIT", 4, 0);
  close(sock);
  exit(0);
}

void main() {
  signal(SIGINT, shutdownClient);
  printf("Starting Client!\n");
  printf("Please wait...\n");

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

  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  connect(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

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
    int count = send(sock, input_string, inputStringLen, 0);
    if (count != inputStringLen) {
      perror("send() sent a different number of bytes than expected");
    }
    char answer[256];
    memset(answer, 0, sizeof(answer));
    recv(sock,answer,255,0);
    printf("Server answered: %s\n", answer);
  }
  close(sock);
}
