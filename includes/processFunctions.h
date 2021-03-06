/* Author: Steve Heller
 * 
 * Includes all the functions for the algorithm after the fork.
 *
 *
 */

#ifndef PROCESSFUNCTIONS_H_FILE
#define PROCESSFUNCTIONS_H_FILE

int isInCommand = 0;
char buffer[1024];
int clientSock;

void printToClient(char stringToSend[]) {
  char *sendText = stringToSend; 
  send(clientSock, sendText, strlen(sendText), 0);
}

void processInput(char inputArg[]) {
  if (strcmp(inputArg,"EXIT") != 0) {
    switch (isInCommand) {
      case 0:
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
          printf("Invalid command - force disconnect!\n");
	  exit(1);
        }
        break;
      case 1:
        InsertLines(inputArg);
        break;
      case 2:
        ReplaceLines(inputArg);
        break;
      case 3:
        ReadLines(inputArg);
        break;
      case 4:
        DeleteLines(inputArg);
        break;
      case 5:
        NumLines(inputArg);
        break;
    }
  } else {
    printf("Client disconnected!\n");
    exit(0);
  }
}

void runProcess(int sock) {
  clientSock = sock;
  printf("Client connected with process id %ld!\n\n", (long)getpid());   
  while (1) {
    memset(buffer, 0, sizeof(buffer));
    recv(clientSock,buffer,1023,0);
    processInput(buffer);
  }
  close(clientSock);
}

#endif
