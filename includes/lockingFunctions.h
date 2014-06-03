/* Author: Steve Heller
 * 
 * Includes all the functions for the locking mechanism.
 * This is based on the "shared memory" feature of C.
 *
 */

#ifndef LOCKINGFUNCTIONS_H_FILE
#define LOCKINGFUNCTIONS_H_FILE

#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <termios.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int retcode;
int shmid;
key_t key_sh;
int *lockedLines;
int key_sh = 2812;

int setup_shm() {
  shmid = shmget(key_sh, 1024, IPC_CREAT | 0666);
  if(shmid < 0) {
    error("Error in shmget");
    return 1;
  } else {
    lockedLines = (int *)shmat(shmid, 0, 0);
    return 0;
  }
}

void lockLine(int lineNum) {
  lockedLines[lineNum] = 1;
}

void lockMultipleLines(int startLine, int endLine) {
  int i;
  for (i = startLine; i <= endLine; i++) {
    lockLine(i);
  }
}

void unlockLine(int lineNum) {
  lockedLines[lineNum] = 0;
}

void unlockMultipleLines(int startLine, int endLine) {
  int i;
  for (i = startLine; i <= endLine; i++) {
    unlockLine(i);
  }
}

int isLineLocked(int lineNum) {
  return lockedLines[lineNum];
}

int areLinesLocked(int startLine, int endLine) {
  int i;
  int result = 0;
  for (i = startLine; i <= endLine; i++) {
    if (isLineLocked(i) == 1) {
      result = 1;
    }
  }
  return result;
}

void addIntToArray(int intVal, int position) {
  lockedLines[position] = intVal;
}

int readIntFromArray(int position) {
  return lockedLines[position];
} 

void shutdown_shm() {
  shmctl(shmid, IPC_RMID, 0);
}

#endif
