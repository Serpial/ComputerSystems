#include <stdio.h>
#include <string.h>
#include <ctype.h> // for coverting the user's input to capitals

#include "twoCompConv.h"

#define INST_SIZE 16

const char mnemonic[12][9]={"LOAD","STORE","SUBT","ADD","INPUT","OUTPUT",
                           "HALT","SKIPCOND", "JUMP","MULT","ROR","ROL"};

void userInput(int *memory) {
  char binaryInput[INST_SIZE+1];
  int validEntry=1; // bool | assumes valid
  char opcode[5], operand[13];
  int counter=0;
  
  // setting up the input buffer
  for (int i=0; i<INST_SIZE;i++) {
    binaryInput[i]=0;
  }
  binaryInput[INST_SIZE]='\0';

  printf("Enter a 16 digit binary number. Enter 'stop' to cancel user entry\n");
  
  for(;;) {
    validEntry=1; // Assumes valid
    printf("\t");
    scanf (" %s", binaryInput); // Get 16 bitsize
    
    if (binaryInput[INST_SIZE]!='\0') {
      printf("SYNTAX ERROR : Too many characters\n");
      binaryInput[INST_SIZE]= '\0';
      continue;
    }

    if (strstr(binaryInput, "stop")!=NULL) {
      return;
    } 
    
    //check the format
    for (int i=0; i<INST_SIZE; i++) {
      if (binaryInput[i]!='1'&&binaryInput[i]!='0') {
        printf("SYNTAX ERROR : Something you entered was not quite right\n");
        validEntry=0;
        break;
      } 
    }

    if (validEntry) {      
      memory[counter]=binToDec(binaryInput);
      counter++;
    }
  } 
}

int main() {
  int memory[10]={0,0,0,0,0,0,0,0,0,0};

  userInput(memory);

  // Paul, you now what to test what characters are in memory in decimal
  
  int counter=0;
  while(memory[counter]!=0){
    printf("%d\n", memory[counter]);
    counter++;
  }
  
  counter=0;


  while(memory[counter]!=0) {
    printf("%s\t->\t", decToBinStr(counter, 12));
    printf("%s\n", decToBinStr(memory[counter],16));
    counter++;
  }
  
  
  return 0;
}
