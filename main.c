/**************************************************************************
 * Assessment Title: Assessed Coursework Exercise 3
 *
 *
 * Number of Submitted C Files:  4 c files and 3 header files
 *
 * 
 * Date: 
 *
 * 
 * Authors: 
 *	1. Paul Hutchison, Reg no: 201741535
 *	2. Lucy Pennington, Reg no: 201707823
 *	3. Ismael Ahmed, Reg no: 201707978
 *	4. Christopher Reilly, Reg no: 201717835
 *	5. Adil Ameen, Reg no: 201720531
 * 
 *
 *	Statement: We confirm that this submission is all our own work.
 *
 *  (Signed) _Paul_James_Hutchison_
 *	
 *  (Signed) _Lucy_Pennington_
 *	
 *  (Signed) _Christopher_Thomas_Reilly_
 *	
 *  (Signed) _Ismael_Ahmed_
 *
 *  (Signed) _Adil_Ameen_
 *
 **************************************************************************/

// Please use this to compile in a nix environment:
//    gcc -std=c99 printingFunc.c memoryFill.c twoCompConv.c main.c -lm

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Custom files
#include "twoCompConv.h"
#include "memoryFill.h"
#include "printingFunc.h"

typedef struct {
  unsigned int PC:12;
  unsigned int MAR:12;
  unsigned int IR:16;
  unsigned int MB:16;
  unsigned int AC:16;
  unsigned int InREG:16;
  unsigned int OutREG:16;
} Registers;



// Registers
Registers registers;
////////////////////
int memory[4096];
// To get the opcode from the int please use memory[i]>>12 (Using shifts)
// to get the operand, please you memory[i]&0xFFF (Using 'and' masking)


// function prototypes
int displayMemAfterInput();
int operation();


/* main that takes in arguments -c, -d, -f, or 
 * --help (used to get a list of commands)
 */
int main(int argc, char *argv[]) {
  

  // init registers
  registers.PC=0;
  registers.MAR=0;
  registers.IR=0;
  registers.MB=0;
  registers.AC=0;
  registers.InREG=0;
  registers.OutREG=0;
  
  if (fillMemory(argc,argv, memory)==0) {
    return 0;
  }
  
  
  // Check if the user would like to display memory
  if(displayMemAfterInput()){;
    printf("\t--------------------\n");
  }
  machToAss(memory);
  printf("\t----RUNNING-CODE----\n");

  // Fetch/Execute
  int halt = 1;
  while(halt){
    registers.MAR = registers.PC;
    registers.IR = memory[registers.MAR];
    registers.PC++;
    registers.MB = memory[registers.MAR];
    halt = operation();
  }


  displayMemAfterInput();

  printf("\t--------------------\n");
  
  return 0;
}

/* run the operation from memory
 */
int operation(){
  int opcode = registers.IR >> 12;

  switch(opcode){
  case 0: // Load
    registers.AC = registers.MB;
    break;
  case 1: // Store
    memory[registers.MAR] = registers.AC;
    break;
  case 2: // Subtract
    registers.AC = dec2sToDec(decTo2sDec(registers.AC&0xFFF) - decTo2sDec(registers.MB&0xFFF));
    break;
  case 3: // Add
    registers.AC = dec2sToDec(decTo2sDec(registers.AC&0xFFF) + decTo2sDec(registers.MB&0xFFF));
    break;
  case 4: // Input
    printf("Enter input for AC, in decimal: ");
    int temp;
    scanf("%d", &temp); // needed because you cant & a bitfield
    registers.InREG = dec2sToDec(temp);
    registers.AC = registers.InREG;
    break;
  case 5: // Output
    registers.OutREG = registers.AC;

    printf("AC is currently %d\n", decTo2sDec(registers.OutREG&0xFFF));
    break;
  case 6: // Halt
    return 1;
    break;
  case 7: // Skipcond
    if (registers.AC>0) {
      registers.PC += 1;
    }
    break;  
  case 8: // Jump
    registers.PC = registers.MAR-1;
    break;
  case 9: // Mult
    registers.AC = dec2sToDec(decTo2sDec(registers.AC&0xFFF) * decTo2sDec(registers.MB&0xFFF));
    break;
  case 10: // Sll
    registers.AC = registers.AC >> registers.MAR;
    break;
  case 11: // Sll
    registers.AC = registers.AC << registers.MAR;
    break;
  case 12: // null location in memory
    return 0;
  default:
    printf("Not an opcode! \n");
  }
  
}

/*
 * A little recursive function that continues to ask
 * if the would like to print memory until they enter 
 * a syntatically correct answer.
 */
int displayMemAfterInput() {
  char entry[255];
  printf("Would you like to print memory? (y or n) :");
  scanf(" %s", entry);

  if (strcmp(entry, "y")==0) {
    displayMemBin(memory);
    return 1;
  } else if (strcmp(entry, "n")==0) {
    return 0;
  } else {
    return displayMemAfterInput();
  }
  
}
