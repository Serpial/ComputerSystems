#include <stdio.h>
#include <string.h>
#include "twoCompConv.h"

#define INST_SIZE 16
#define OPCODE_SIZE 4


char* getAddressFromDec(int dec) {
  char instruction[INST_SIZE+1];
  static char address[INST_SIZE-OPCODE_SIZE+1];

  strcpy(instruction, decToBinStr(dec,INST_SIZE));
  
  for (int i=0; i<INST_SIZE-4; i++) {
    address[i]=instruction[i+4];
  }
  address[INST_SIZE-OPCODE_SIZE]='\0';
  return address;
}

int getDecOpcodeFromDec(int dec) {
  char instruction[INST_SIZE+1];
  char opcode[OPCODE_SIZE+1];

  strcpy(instruction, decToBinStr(dec,INST_SIZE));
  
  //gets the opcode in binary
  for (int i=0; i<4; i++) {
    opcode[i]=instruction[i];
  }
  opcode[OPCODE_SIZE]='\0';
  
  return binToDec(opcode);
}
