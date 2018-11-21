#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "twoCompConv.h"


void getMemFromFile(char *fileLocation, int *memory) {
    FILE *fp=NULL; //file pointer
    int counter=0;
    char buffer[0xFF]; // 255 characters before buffer overload
    char sub[0xFF];
    int opcode=0;

    // Opens the file the user has entered
    fp=fopen(fileLocation, "r");

    if (fp != NULL) { // checking if the file exists
        // wipeMemory(); // Clear memory
        while(fscanf(fp,"%20s",buffer) == 1) { // fscanf for making sure what comes is max 20 characters long
          for (int i=0; i<0xFF;i++) {
            sub[i]=buffer[i+4];
          }

          // Convert the opcode from binary
          for (int i=0; i<4;i++) {
            if (buffer[i]=='1') {
              opcode+=pow(2,4-i-1);
            }
          }
          opcode= opcode<<12; // make space for the operand
          // bit of bitmasking magic to join the opcode and the operand together
          memory[counter]=opcode | binToDec(sub); 

          // reset opcode and move onto next instruction
          opcode=0;
          counter++;
        }
    } else {
        printf("This file does not exist\n");
    }
    fclose(fp);
}