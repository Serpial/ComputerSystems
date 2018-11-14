#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "twoCompConv.h"

uint16_t memory[4096];
// Registers
uint16_t registers[5];
uint16_t *PC;
uint16_t *MB;
uint16_t *AC;
uint16_t *MA;

int main(/* to fill later */) {
  int numBits;

  
  char binValPos[17];
  char binValNeg[17];

  numBits=16;
  strcpy(binValPos, decToBinStr(38,numBits));
  strcpy(binValNeg, decToBinStr(-38,numBits));

  
  printf("%s|%d\n", binValPos, numBits);
  printf("%s|%d\n", binValNeg, numBits);
  printf("----------------\n");
  printf("%d\n",binToDec(binValPos));
  printf("%d\n",binToDec(binValNeg));

  ///////////////////////////////////////////
  
  numBits=17;
  strcpy(binValPos, decToBinStr(38,numBits));
  strcpy(binValNeg, decToBinStr(-38,numBits));

  
  printf("%s|%d\n", binValPos, numBits);
  printf("%s|%d\n", binValNeg, numBits);
  printf("----------------\n");
  printf("%d\n",binToDec(binValPos));
  printf("%d\n",binToDec(binValNeg));

  return 0;
}
