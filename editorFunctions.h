/* Author: Steve Heller
 * 
 * Includes all the functions that the server has to handle.
 * For a further explaination please see document "Funktionen Editor"
 *
 */

#ifndef EDITORFUNCTIONS_H_FILE
#define EDITORFUNCTIONS_H_FILE

extern int isInCommand;

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
      printf("%s: You want to insert %i lines starting from line number %i!\n", command, startNum, numLines);
      isInCommand = 1;
    }
  } else {
    printf("You inserted this line: %s\n", inputArg);
    isInCommand = 0;
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
