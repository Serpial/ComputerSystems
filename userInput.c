#include <stdio.h>

void userInput() {
  unsigned int moreArguments:1; // bool
  moreArguments=1;
  char entry[255];
  printf("Enter stop to exit.\n");
  for(;;) {
    printf("Input : ");
    scanf(" %s", entry);
    if (!takeMoreArguments) {
      break;
    }
  }
}
