/* Author: Steve Heller
 * 
 * Includes all the functions that the server has to handle.
 * For a further explaination please see document "Funktionen Editor"
 *
 */

#ifndef EDITORFUNCTIONS_H_FILE
#define EDITORFUNCTIONS_H_FILE

extern int isInCommand;

int editingStartLine;
int editingNumOfLines;

void printToClient(char stringToSend[]);

void InsertLines(char inputArg[]) {
  if (isInCommand == 0) {
    char *command = strtok(inputArg," ");
    char *tmpNum = strtok(NULL," ");
    char *tmpLines = strtok(NULL," ");

    if (tmpNum == NULL || tmpLines == NULL) {
      printf("%s: Wrong use of command!\n", command);
    } else {
      int startNum = atoi(tmpNum);
      int numLines = atoi(tmpLines);
      editingStartLine = startNum;
      editingNumOfLines = numLines;
      printf("You want to insert %i lines starting from line number %i!\n", numLines, startNum);
      isInCommand = 1;
    }
  } else {
    if (editingNumOfLines > 1) {
      while (isLineLocked(editingStartLine) == 1) {
        sleep(1);
      }
      lockLine(editingStartLine);
      // here comes the file modification
      // do stuff for the first n lines!
      printf("Inserted Line %i: %s\n", editingStartLine, inputArg);
      unlockLine(editingStartLine);
      editingStartLine++;
      editingNumOfLines--;
    } else {
      while (isLineLocked(editingStartLine) == 1) {
        sleep(1);
      }
      lockLine(editingStartLine);
      // here comes the file modification
      // do stuff for the last line!
      printf("Inserted last line %i: %s\n", editingStartLine, inputArg);
      printToClient("INSERTED");
      unlockLine(editingStartLine);
      editingStartLine = 0;
      editingNumOfLines = 0;
      isInCommand = 0;
    }
  }
}

void ReplaceLines(char inputArg[]) {
  if (isInCommand == 0) {
    char *command = strtok(inputArg," ");
    char *tmpNum = strtok(NULL," ");
    char *tmpLines = strtok(NULL," ");

    if (tmpNum == NULL || tmpLines == NULL) {
      printf("%s: Wrong use of command!\n", command);
    } else {
      int startNum = atoi(tmpNum);
      int numLines = atoi(tmpLines);
      editingStartLine = startNum;
      editingNumOfLines = numLines;
      printf("You want to replace %i lines starting from line number %i!\n", numLines, startNum);
      isInCommand = 2;
    }
  } else {
    if (editingNumOfLines > 1) {
      while (isLineLocked(editingStartLine) == 1) {
        sleep(1);
      }
      lockLine(editingStartLine);
      // here comes the file modification
      // do stuff for the first n lines!
      printf("Replaced line %i: %s\n", editingStartLine, inputArg);
      unlockLine(editingStartLine);
      editingStartLine++;
      editingNumOfLines--;
    } else {
      while (isLineLocked(editingStartLine) == 1) {
        sleep(1);
      }
      lockLine(editingStartLine);
      // here comes the file modification
      // do stuff for the last line!
      printf("Replaced last line %i: %s\n", editingStartLine, inputArg);
      printToClient("REPLACED");
      unlockLine(editingStartLine);
      editingStartLine = 0;
      editingNumOfLines = 0;
      isInCommand = 0;
    }
  }
}

void ReadLines(char inputArg[]) {
  char *command = strtok(inputArg," ");
  char *tmpNum = strtok(NULL," ");
  char *tmpLines = strtok(NULL," ");

  if (tmpNum == NULL || tmpLines == NULL) {
    printf("%s: Wrong use of command!\n", command);
  } else {
    char response[1024];
    memset(response, 0, sizeof(response));
    int startNum = atoi(tmpNum);
    int numLines = atoi(tmpLines);
    editingStartLine = startNum;
    editingNumOfLines = numLines;
    printf("You want to read %i lines starting from line number %i!\n", numLines, startNum);
    sprintf(response, "LINES %s", tmpLines);
    int i;
    int endLine = (startNum + numLines - 1);
    while (areLinesLocked(startNum, endLine) == 1) {
      sleep(1);
    }
    for (i = startNum; i <= endLine; i++) {
      lockLine(i);
      // here comes the file modification
      printf("Read line %i\n", i);
      char content[256];
      memset(content, 0, sizeof(content));
      sprintf(content, "\nContent of line %i", i);
      strcat(response, content);
      unlockLine(i);
    }
    printToClient(response);
  }
}

void DeleteLines(char inputArg[]) {
  char *command = strtok(inputArg," ");
  char *tmpNum = strtok(NULL," ");
  char *tmpLines = strtok(NULL," ");

  if (tmpNum == NULL || tmpLines == NULL) {
    printf("%s: Wrong use of command!\n", command);
  } else {
    int startNum = atoi(tmpNum);
    int numLines = atoi(tmpLines);
    printf("You want to delete %i lines starting from line number %i!\n", numLines, startNum);
    int i;
    int endLine = (startNum + numLines - 1);
    while (areLinesLocked(startNum, endLine) == 1) {
      sleep(1);
    }
    lockMultipleLines(startNum, endLine);
    for (i = startNum; i <= endLine; i++) {
      // here comes the file modification
      printf("Delete line %i\n", i);
      unlockLine(i);
    }
    printToClient("DELETED");
  }
}

void NumLines(char inputArg[]) {
  printf("You want to know the number of lines!\n");
  printToClient("Number of Lines");
}

#endif
