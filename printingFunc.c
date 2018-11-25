#include <stdio.h>

// Custom files
#include "twoCompConv.h"

#define INVALID_MEMORY_ITEM 12<<12 // There are opcodes 0 to 11. As soon as one uses 12 the whole istruction is invalid

/* This function displays everything in memory in a 
 * binary format such as:
 * <A memory Location> -> <an instruction from that location in memory>
 * 000000100001 -> 0001000000000001
 */
void displayMemBin (int *memory) {
  int counter=0;
  printf("Memory Location\t->\tInstruction\n"); // Heading
  while(memory[counter]!=INVALID_MEMORY_ITEM) {
    printf("%s\t->\t", decToBinStr(counter, 12));
    printf("%s\n", decToBinStr(memory[counter],16));
    counter++;
  }
}

/*
 * Simply prints the opcode translate into assembly along side
 * the operand of the instruction.
 */
void machToAss(int *memory){
  int operand_1;
  unsigned int opcode_2;
  const char MNEMONIC[12][9]={"LOAD","STORE","SUBT","ADD","INPUT","OUTPUT",
                              "HALT","SKIPCOND","JUMP","MULT","SRL","SLL"};  
  
  for (int i=0; i < 4096; i++){
    if (memory[i]!=INVALID_MEMORY_ITEM) {
      opcode_2 = memory[i]>>12;
      operand_1 = memory[i]&0xFFF;
      
      printf("\t");
      printf("\t%s  ", MNEMONIC[opcode_2]);
      printf("%d\n", decTo2sDec(operand_1));
    } else {
      return;
    }
  }
}