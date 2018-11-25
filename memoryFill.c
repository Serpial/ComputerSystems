#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h> // used for 'pow()' | Make sure to use -lm when compiling

// Custom files
#include "twoCompConv.h"

#define INST_SIZE 16 // Size of an instruction
#define INVALID_MEMORY_ITEM 12<<12 // There are opcodes 0 to 11. As soon as one uses 12 the whole istruction is invalid


/*
 * Gets user input from console making sure
 * to deal with some errors that the user may
 * accidently cause.
 */
void userInput(int *memory) {
  char binaryInput[INST_SIZE+1];
  int validEntry=1; // bool | assumes valid
  int displayMemory=0; // bool | used when closing function
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
    scanf (" %s", binaryInput);

    // Don't commit the given instruction to memory if it is too big
    if (binaryInput[INST_SIZE]!='\0') {
      printf("SYNTAX ERROR : Too many characters\n");
      binaryInput[INST_SIZE]= '\0';
      continue;
    }

    // If the user enters 'stop' then leave the function
    if (strstr(binaryInput, "stop")!=NULL) {      
      return;
    } 
    
    // check the format
    //    If it isn't all in binary,
    for (int i=0; i<INST_SIZE; i++) {
      if (binaryInput[i]!='1'&&binaryInput[i]!='0') {
        printf("SYNTAX ERROR : Something you entered was not quite right\n");
        validEntry=0;
        break;
      } 
    }
    //    If the opcode doesn't exist
    if (validEntry) { // if the entry is in proper binary
      if(binToDec(binaryInput)>=INVALID_MEMORY_ITEM) {
        printf("SYNTAX EROR : The opcode you entered doesn't exist\n");
        validEntry=0;
      }
    }

    if (validEntry) {      
      memory[counter]=binToDec(binaryInput);
      counter++;
    }
  } 
}

/*
 * A default program for when the user runs 
 * the program using -d
 */
void placeDefaultInMem(int *memory) {
  // The jump and skip example
  memory[0]=0x4000;    // 0100000000000000
  memory[1]=0x7000;    // 0111000000000000
  memory[2]=0x6000;    // 0110000000000000
  memory[3]=0x2001;    // 0010000000000001
  memory[4]=0x7000;    // 0111000000000000
  memory[5]=0x8003;    // 1000000000000011
  memory[6]=0x5000;    // 0101000000000000
  memory[7]=0x6000;    // 0110000000000000

}

/* Given a file location in a string format, 
 * search that location to get something to fill
 * the memory
 * 
 * also returns whether or not the action was a success
 * and -1 if there is a syntax error
 */
int getMemFromFile(char *fileLocation, int *memory) {
    FILE *fp=NULL; //file pointer
    int counter=0;
    char buffer[0xFF]; // 255 characters before buffer overload

    // Opens the file the user has entered
    fp=fopen(fileLocation, "r");
    
    if (fp != NULL) { // checking if the file exists
        while(fscanf(fp,"%20s",buffer) == 1) { // fscanf for making sure what comes is max 20 characters long
          if (binToDec(buffer)>=INVALID_MEMORY_ITEM){
            printf("SYNTAX ERROR :  Wrong opcode found on line %i\n", counter+1);
            return 0;
          } else {
            memory[counter]= binToDec(buffer);
            counter++;
          }
        }
        fclose(fp);
        return 1;
    } else {
        printf("This file does not exist\n");
        return 0;
    }
}


/* The default should be 12<<12 as twelve is the first invalid
 * opcode and thus the decimal value in memory should always be 
 * smaller. It is logically shifted left to push it into the
 * location of the opcode
 */
void wipeMemory(int *memory) {
  int max= pow(2, 12);
  for (int i=0; i<max; i++) {
    memory[i]=INVALID_MEMORY_ITEM;  
  }
}


/* Prints the arguments that the user has the option of
 * using when they wish to use the program
 */
void printHelp(){
  printf("You can run the commands:\n");
  printf("\t-c\t\t\tGo into user-input mode\n");
  printf("\t-d\t\t\tLoads default contents into memory\n");
  printf("\t-f <file location>\tLoads contents of a\
 file into memory\n");
  printf("\t--help\t\t\tGo into user-input mode\n");
}

/*
 * Returns 1 if we have successfully filled memory
 * Returns 0 if the arguements the user has entered were incorrect
 */
int fillMemory(int argc, char *argv[], int *memory){
  wipeMemory(memory);

  if (argc==1) {
    printf("Please run --help to find out commands\n");
    return 0;
  }
  
  if ((argv[1][1]=='f' && argc-1>2) || (argv[1][1]!='f' && argc-1>1)) {
    printf("You have entered an invalid argument or\
 too many arguments\n");
    return 0;
  }

  if (argv[1][0]=='-') {
    switch(argv[1][1]){
    case '-': // There is only one '--x' command right now -> --help
      if (argv[1][2]=='h' && argv[1][3]=='e' &&
          argv[1][4]=='l' && argv[1][5]=='p' && argv[1][6]=='\0') {
        printHelp();
        return 0;
      }
      return 0;
    case 'c':
      userInput(memory);
      return 1;
    case 'd':
      placeDefaultInMem(memory);
      return 1;
    case 'f':
      if (!getMemFromFile(argv[2], memory)) {
        return 0; // if we are not able to find the file, close the program
      } else {
        return 1;
      }
      return 0;
    }
  }
  return 0;

}
