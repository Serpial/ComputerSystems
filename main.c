#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "twoCompConv.h" // because it is a local file it is in double quotes instead of <>

typedef struct {
  unsigned int PC:12;
  unsigned int MAR:12;
  unsigned int IR:16;
  unsigned int MB:16;
  unsigned int AC:16;
} Registers;


#define INST_SIZE 16 // Size of an instruction
#define OPCODE_SIZE 4 // Number of bits an opcode takes up
#define BITS_NUM_WORDS 12+1 // 2^12=4096 plus 1 for twos comp

int memory[4096];
// To get the opcode from the int please use memory[i]>>12 (Using shifts)
// to get the operand, please you memory[i]&0xFFF (Using 'and' masking)


// Registers
Registers registers
const char mnemonic[12][9]={"LOAD","STORE","SUBT","ADD","INPUT",
                           "OUTPUT","HALT","SKIPCOND","JUMP",
                           "MULT","ROR","ROL"};

// function prototypes
// void operation(int valueX, int AC);  // edited once we have fetch execute down
void getMemFromFile(char *fileLocation);
void wipeMemory(); // resets memory
void displayMemBin(); // Displays memory in binary
int validArgue (char *argv[]);
void printHelp();


/* main that takes in arguments -c, -d, -f, or 
 * --help (used to get a list of commands)
 */
int main(int argc, char *argv[]) {
  int maxArg; // Either 0 (no right arguments), 1 (1 right argument), 2 (2 right arguments which can only mean '-f' right now)
  
  if (argc==1) {
    printf("Please run --help to find out commands\n");
    return 0;
  }

  maxArg=validArgue(argv);
  
  if (argc-1>maxArg) {
    printf("You have entered an invalid argument or\
 too many arguments\n");
    return 0;
  }
  
  switch (maxArg) {
  case 1:
    switch(argv[1][1]){
    case '-': // There is only one '--x' command right now -> --help
      if (argv[1][2]=='h' && argv[1][3]=='e' &&
                  argv[1][4]=='l' && argv[1][5]=='p') {
        printHelp();
      }
    case 'c':
      printf("This is what would happen in -c if we had written it yet\n");
      break;
    case 'd':
      printf("This is what would happen in -d if we had written it yet\n");
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

/* run the operation from memory
 */
int operation(){
  int valid=1; // bool
  int opcode = registers.IR >> 12;
  

  switch(opcode){
  case 0: // Load
    registers.AC = MB;
    break;
  case 1: // Store
    memory[MAR] = registers.AC;
    break;
  case 2: // Subtract
    registers.AC = registers.AC - MB;
    break;
  case 3: // Add
    registers.AC = registers.AC + MB;
    break;
  case 4: // Input
    printf("Enter input for AC: ");
    scanf("%d", registers.InREG);
    registers.AC = registers.InREG;
    break;
  case 5: // Output
    registers.OutREG = registers.AC;
    printf("AC is currently %d", registers.OutREG);
    break;
  case 6: // Halt
    return 0;
    break;
  case 7: // Skipcond
    // This is kind of what I was thinking: 
    registers.PC += 1;
    break;  
  case 8: // Jump
    registers.PC = MAR-1;
    break;
  case 9: // Mult
    registers.AC = registers.AC * MB;
    break;
  case 10: // ROR
    registers.AC = registers.AC >> MAR;
    break;
  case 11: // ROL
    registers.AC = registers.AC << MAR;
    break;
  default:
    printf("Not an opcode! \n");
    valid=0;
  }
  //registers.PC += 1; in fetch/execute 
}

/* Given a file location in a string format, 
 * search that location to get something to fill
 * the memory
 */
void getMemFromFile(char *fileLocation) {
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
          // bit of bitmasking magic to join the opcode and the operand together
          memory[counter]= opcode<<12 | binToDec2s(sub); 

          // reset opcode and move onto next instruction
          opcode=0;
          counter++;
        }
    } else {
        printf("This file does not exist\n");
    }
    fclose(fp);
}

/* This function displays everything in memory in a 
 * binary format such as:
 * <A memory Location> -> <an instruction from that location in memory>
 * 000000100001 -> 0001000000000001
 */
void displayMemBin () {
	int counter=0;
	printf("Memory Location\t->\tInstruction\n"); // Heading
	char memLoc[BITS_NUM_WORDS+1], instruc[INST_SIZE+1];

	while(memory[counter]!=0) {
		strcpy(memLoc, decToBinStr2s(counter,BITS_NUM_WORDS));
		strcpy(instruc, decToBinStr2s(memory[counter], INST_SIZE));
		printf("%s\t->\t%s\n", memLoc, instruc);
		counter++;
	}
}

/* Empties memory making every value 0
 */
void wipeMemory() {
    int max= pow(2, BITS_NUM_WORDS-1);
    for (int i=0; i<max; i++) {
        memory[i]=-1;
    }
}


/* Returns 2 if there are two valid arguments 
 * Returns 1 if there is one valid argument
 * Returns 0 if there are no valid arguments
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

