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

void testInsertLines() {
  printf("\nNow testing function InsertLines...\n");
  printf("***********************************\n");
  sleep(2);
  char input_string[256];
  int inputStringLen;
  int count;
  memset(input_string, 0, sizeof(input_string));
  strcpy(input_string, "InsertLines 1 2");
  inputStringLen = strlen(input_string); 
  printf("Sending string: %s\n", input_string);
  count = send(sock, input_string, inputStringLen, 0);
  if (count != inputStringLen) {
    perror("send() sent a different number of bytes than expected");
  }
  sleep(1);
  memset(input_string, 0, sizeof(input_string));
  strcpy(input_string, "This is the content of the first line");
  inputStringLen = strlen(input_string); 
  printf("Sending string: %s\n", input_string);
  count = send(sock, input_string, inputStringLen, 0);
  if (count != inputStringLen) {
    perror("send() sent a different number of bytes than expected");
  }
  sleep(1);
  memset(input_string, 0, sizeof(input_string));
  strcpy(input_string, "This is the content of the second line");
  inputStringLen = strlen(input_string); 
  printf("Sending string: %s\n", input_string);
  count = send(sock, input_string, inputStringLen, 0);
  if (count != inputStringLen) {
    perror("send() sent a different number of bytes than expected");
  }

  char answer[1024];
  memset(answer, 0, sizeof(answer));
  recv(sock,answer,1023,0);
  printf("Server answered: %s\n", answer);
}

void testReplaceLines() {
  printf("\nNow testing function ReplaceLines...\n");
  printf("************************************\n");
  sleep(2);
  char input_string[256];
  int inputStringLen;
  int count;
  memset(input_string, 0, sizeof(input_string));
  strcpy(input_string, "ReplaceLines 5 2");
  inputStringLen = strlen(input_string); 
  printf("Sending string: %s\n", input_string);
  count = send(sock, input_string, inputStringLen, 0);
  if (count != inputStringLen) {
    perror("send() sent a different number of bytes than expected");
  }
  sleep(1);
  memset(input_string, 0, sizeof(input_string));
  strcpy(input_string, "This is the content of the first line");
  inputStringLen = strlen(input_string); 
  printf("Sending string: %s\n", input_string);
  count = send(sock, input_string, inputStringLen, 0);
  if (count != inputStringLen) {
    perror("send() sent a different number of bytes than expected");
  }
  sleep(1);
  memset(input_string, 0, sizeof(input_string));
  strcpy(input_string, "This is the content of the second line");
  inputStringLen = strlen(input_string); 
  printf("Sending string: %s\n", input_string);
  count = send(sock, input_string, inputStringLen, 0);
  if (count != inputStringLen) {
    perror("send() sent a different number of bytes than expected");
  }

  char answer[1024];
  memset(answer, 0, sizeof(answer));
  recv(sock,answer,1023,0);
  printf("Server answered: %s\n", answer);
}

void testReadLines() {
  printf("\nNow testing function ReadLines...\n");
  printf("*********************************\n");
  sleep(2);
  char input_string[256];
  int inputStringLen;
  int count;
  memset(input_string, 0, sizeof(input_string));
  strcpy(input_string, "ReadLines 1 10");
  inputStringLen = strlen(input_string); 
  printf("Sending string: %s\n", input_string);
  count = send(sock, input_string, inputStringLen, 0);
  if (count != inputStringLen) {
    perror("send() sent a different number of bytes than expected");
  }

  char answer[1024];
  memset(answer, 0, sizeof(answer));
  recv(sock,answer,1023,0);
  printf("Server answered: %s\n", answer);
}

void testDeleteLines() {
  printf("\nNow testing function DeleteLines...\n");
  printf("***********************************\n");
  sleep(2);
  char input_string[256];
  int inputStringLen;
  int count;
  memset(input_string, 0, sizeof(input_string));
  strcpy(input_string, "DeleteLines 10 10");
  inputStringLen = strlen(input_string); 
  printf("Sending string: %s\n", input_string);
  count = send(sock, input_string, inputStringLen, 0);
  if (count != inputStringLen) {
    perror("send() sent a different number of bytes than expected");
  }

  char answer[1024];
  memset(answer, 0, sizeof(answer));
  recv(sock,answer,1023,0);
  printf("Server answered: %s\n", answer);
}

void testNumLines() {
  printf("\nNow testing function NumLines...\n");
  printf("********************************\n");
  sleep(2);
  char input_string[256];
  int inputStringLen;
  int count;
  memset(input_string, 0, sizeof(input_string));
  strcpy(input_string, "NumLines");
  inputStringLen = strlen(input_string); 
  printf("Sending string: %s\n", input_string);
  count = send(sock, input_string, inputStringLen, 0);
  if (count != inputStringLen) {
    perror("send() sent a different number of bytes than expected");
  }

  char answer[1024];
  memset(answer, 0, sizeof(answer));
  recv(sock,answer,1023,0);
  printf("Server answered: %s\n", answer);
}

void main(int argc, char *argv[]) {
  int manual = 0;
  signal(SIGINT, shutdownClient);

  if (argc > 1) {
    if (strcmp(argv[1], "-manual") == 0) {
      manual = 1;
    }
  } 

  if (manual == 1) {
    printf("**********************************\n");
    printf("*    TESTCLIENT - MANUAL MODE    *\n");
    printf("**********************************\n");  
  } else {
    printf("**********************************\n");
    printf("*           TESTCLIENT           *\n");
    printf("**********************************\n");
  }

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

  printf("Client started - connected on port %i\n\n", server_port);
  
  if (manual == 1) {
    while (1) {
      char input_string[256];
      char *p;
      unsigned int inputStringLen;
      fgets(input_string, sizeof(input_string), stdin);       
      if ((p = strchr(input_string, '\n')) != NULL) {
        *p = '\0';
      }
      if (strcmp(input_string,"EXIT") == 0) {
        printf("You disconnected!\n");
        shutdownClient();
      }
      inputStringLen = strlen(input_string);
      int count = send(sock, input_string, inputStringLen, 0);
      if (count != inputStringLen) {
        perror("send() sent a different number of bytes than expected");
      }
      char answer[1024];
      memset(answer, 0, sizeof(answer));
      recv(sock,answer,1023,0);
      printf("Server answered: %s\n", answer);
    }
  }
  testInsertLines();
  testReplaceLines();
  testReadLines();
  testDeleteLines();
  testNumLines();
  shutdownClient();

}
