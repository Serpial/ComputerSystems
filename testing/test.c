#include <stdio.h>
#include "userInput.h"

int memory[4096];

int main(void) {
  memory[0]=0;
  userInput(memory);

  printf("%d\n", memory[0]);
  return 0;
}
