#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definitions */
#define PATHSIZE 200
#define MAX_INSTR 512

/* Prototypes */
char* switchHome(char* currentDir);
char* buildPrefix(char* currentDir);
void parseInput(char* instruction) {
  
}


int main() {
  char currentPath[PATHSIZE];
  char instruction[MAX_INSTR];
  
  strcpy(currentPath, getenv("HOME"));
  strcat(currentPath,"/Documents");

  for(;;) {
    printf("%s",buildPrefix(currentPath));

    fgets(instruction,MAX_INSTR,stdin);
    parseInput(instruction);
  }
}


/* switches "/home/<username>" to "~"
 */
char* switchHome(char* currentDir) {
  char* temp = malloc(PATHSIZE);
  static char newDir[PATHSIZE];
  if (strstr(currentDir, getenv("HOME"))) {
    newDir[0] = '~'; newDir[1]='\0';
    strncpy(temp, currentDir+strlen(getenv("HOME")),PATHSIZE);
    strcat(newDir, temp);
    return newDir;
  }
  return currentDir;
}

/* Try to get the user's username and build the
 * prefix on top of that
 */
char* buildPrefix(char* currentDir) {
  static char prefix[PATHSIZE];
  char *name;

  strcpy(prefix, getenv("USER"));
  strcat(prefix, ":");
  strcat(prefix, switchHome(currentDir));
  strcat(prefix, "$ ");
  return prefix;
}
