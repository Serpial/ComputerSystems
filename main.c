#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "twoCompConv.h" // because it is a local file it is in double quotes instead of <>

#define INST_SIZE 16 // Size of an instruction
#define BITS_NUM_WORDS 12+1 // 2^12=4096 plus 1 for twos comp

// function prototypes
void operation(int valueX, int AC);
void getMemFromFile(char *fileLocation);
void wipeMemory(); // resets memory
void displayMemBin(); // Displays memory in binary
int validArgue (char *argv[]);
void printHelp();

int16_t memory[4096];
// Registers
uint16_t registers[4];
uint16_t* AC, IR, MB, PC; 
int MAR; // Which has to be 12 bits long


int main(int argc, char *argv[]) {
  int maxArg; // Either 0 (no right arguments), 1 (1 right arguement), 2 (2 right arguements)
  
  if (argc==1) {
    printf("Please run --help to find out commands\n");
    return 0;
  }

  maxArg=validArgue(argv);
  
  if (argc-1>maxArg) {
    printf("You have entered too many arguements\n");
    return 0;
  }
  
  switch (maxArg) {
  case 0:
    printf("Invalid arguement\n");
    return 0;
  case 1:
    switch(argv[1][1]){
    case '-':
      if (argv[1][2]=='h' && argv[1][3]=='e' &&
                  argv[1][4]=='l' && argv[1][5]=='p') {
        printHelp();
      }
    case 'c':
      break;
    case 'd':
      break;
    }
  case 2:
    if (strcmp(argv[1], "-f")==1) {
      getMemFromFile(argv[3]);
      break;
    }
  }
  return 0;
}

void operation(int valueX, int AC){
  int valid=1; // bool
  int opcode;
  // do equivelant
  for(;;) {
    printf("Type in opcode 2 to subtract, or 1 to add \n");
    scanf(" %d", &opcode);
    switch(opcode){
    case 0: // Load
      break;
    case 1: // Store
      break;
    case 2: // Subtract
      AC = AC - valueX;
      printf("AC value = %d \n", AC);  
      break;

    case 3: // Add
      AC = AC + valueX;
      printf("AC value = %d \n", AC);
      break;

    case 4: // Input
      break;
    case 5: // Output
      break;
    case 6: // Halt
      break;
    case 7: // Skipcond
      break;
    case -8: // Jump
      break;
    case -7: // Mult
      AC = AC * valueX;
      printf("AC value = %d \n", AC);
      break;
    case -6: // ROR
      break;
    case -5: // ROL
      break;
    default:
      printf("Not an opcode! \n");
      valid=0;
    }

    // This would be the while statement
    if (valid) break;
  }
}

void getMemFromFile(char *fileLocation) {
    FILE *fp; //file pointer
    int counter=0;
    char buffer[0xFF]; // 255 characters before buffer overload

    fp=fopen(fileLocation, "r");

    if (fp != NULL) { // checking if the file exists
        wipeMemory();
        while(fscanf(fp,"%20s",buffer) == 1) {
            memory[counter]=binToDec(buffer);
            counter++;
        }
    } else {
        printf("This file does not exist\n");
    }
    fclose(fp);
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

void wipeMemory() {
    int max= pow(2, BITS_NUM_WORDS-1);
    for (int i=0; i<max; i++) {
        memory[i]=0;
    }
}


/* Returns 2 if there are two valid arguements 
 * Returns 1 if there is one valid arguement
 * Returns 0 if there are no valid arguements
 */
int validArgue (char *argv[]) {
  switch (argv[1][1]) {
  case '-':
    if (argv[1][2]=='h' && argv[1][3]=='e' &&
        argv[1][4]=='l' && argv[1][5]=='p') {
      if (argv[1][6]=='\0') {
        return 1;
      }
    }
    break;
  case 'c':
    if (argv[1][2] == '\0') {
      return 1;
      }
    break;
  case 'd':
    if (argv[1][2] == '\0') {
      return 1;
    }
    break;
  case 'f':
    if (argv[1][2] == '\0') {      
      return 2;
    }
  }
  return 0;
}

void printHelp(){
  printf("You can run the commands:\n");
  printf("\t-c\t\t\tGo into user-input mode\n");
  printf("\t-d\t\t\tLoads default contents into memory\n");
  printf("\t-f <file location>\tLoads contents of a\
 file into memory\n");
  printf("\t--help\t\t\tGo into user-input mode\n");
}

