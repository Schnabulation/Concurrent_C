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
      printf("Line %i: %s\n", editingStartLine, inputArg);
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
      printf("Last line %i: %s\n", editingStartLine, inputArg);
      unlockLine(editingStartLine);
      editingStartLine = 0;
      editingNumOfLines = 0;
      isInCommand = 0;
    }
  }
}

void ReplaceLines(char inputArg[]) {
  printf("Starting function ReplaceLines\n");
}

void ReadLines(char inputArg[]) {
  printf("Starting function ReadLines\n");
}

void DeleteLines(char inputArg[]) {
  printf("Starting function DeleteLines\n");
}

void NumLines(char inputArg[]) {
  printf("Starting function NumLines\n");
}

#endif
