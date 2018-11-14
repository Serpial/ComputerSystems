#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "fileInput.h"

#define INST_SIZE 16 // Instruction size

int16_t memory[4096];
// Registers
uint16_t registers[4];
uint16_t *PC;
uint16_t *MB;
uint16_t *AC;
uint16_t *MAR; // has to be 12 bits

int main(/* to fill later */) {
  getMemFromFile("./binTest", memory, INST_SIZE );
  
  return 0;
}
