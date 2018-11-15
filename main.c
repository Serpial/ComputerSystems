#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "twoCompConv.h"

#define INST_SIZE 16 // Instruction size
#define BITS_NUM_WORDS 12+1 // 2^12=4096 plus 1 for twos comp

void displayMemBin();
void getMemFromFile(char *fileLocation);

int16_t memory[4096];
// Registers
uint16_t registers[4];
uint16_t *PC;
uint16_t *MB;
uint16_t *AC;
uint16_t *MAR; // has to be 12 bits

int main(/* to fill later */) {
  getMemFromFile("./binTest");
  displayMemBin();
  
  return 0;
}

void displayMemBin () {
	int counter=0;
	printf("Memory Location\t->\tInstruction\n"); // Heading
	char memLoc[BITS_NUM_WORDS+1], instruc[INST_SIZE+1];

	while(memory[counter]!=0) {
		strcpy(memLoc, decToBinStr(counter,BITS_NUM_WORDS));
		strcpy(instruc, decToBinStr(memory[counter], INST_SIZE));
		printf("%s\t->\t%s\n", memLoc, instruc);
		counter++;
	}
}

void getMemFromFile(char *fileLocation) {

  FILE *fp;
  int counter=0;
  char buffer[0xFF];

  fp=fopen(fileLocation, "r");

  if (fp != NULL) {
    while(fscanf(fp,"%20s",buffer) == 1) {
        memory[counter]=binToDec(buffer);
        counter++;
    }
  } else {
    printf("This file does not exist\n");
  }
  fclose(fp);
}
