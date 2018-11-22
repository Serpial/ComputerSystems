#include <stdio.h>
#include "twoCompConvT.h"

#define BITS_NUM_WORDS 4096
#define INST_SIZE 16

int memory[BITS_NUM_WORDS];

void displayMemBin ();

int main() {
  
  memory[0]=50;
  memory[1]=35;
  memory[2]='\0';

  displayMemBin();
  return 0;
}


void displayMemBin () {
  int counter=0;
  printf("Memory Location\t->\tInstruction\n"); // Heading
  char instruc[INST_SIZE+1];

  while(memory[counter]!=0) {
    printf("%s\t->\t%s\n", decToBinStr(counter, 12),
           decToBinStr2s(memory[counter],INST_SIZE));
    counter++;
  }
}
