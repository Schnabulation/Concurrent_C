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

void startServer() {
  printf("Server STARTED!\n");
  printf("Running NumLines now\n");
  NumLines();
}

void main(int argc, char *argv[]) {
  startServer();
}
