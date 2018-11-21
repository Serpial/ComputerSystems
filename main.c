#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "twoCompConv.h" // because it is a local file it is in double quotes instead of <>

#define INST_SIZE 16 // Size of an instruction
#define OPCODE_SIZE 4 // Number of bits an opcode takes up
#define BITS_NUM_WORDS 12+1 // 2^12=4096 plus 1 for twos comp

int16_t memory[4096];
// Registers
uint16_t registers[4];
uint16_t* AC, IR, MB, PC; 
int MAR; // Which has to be 12 bits long
const char mnemonic[9][8]={"LOAD","STORE","SUBT","ADD","INPUT","OUTPUT","HALT","SKIPCOND"};
const char negativeMnemonic[5][4]={"JUMP","MULT","ROR","ROL"};
// negativeMnemonic[getDecOpcodeFromDec(<a number where the opcode is load>)+7]; to get JUMP and so on

// function prototypes
void operation(int valueX, int AC);
void getMemFromFile(char *fileLocation);
void wipeMemory(); // resets memory
void displayMemBin(); // Displays memory in binary
int validArgue (char *argv[]);
void printHelp();

////////////////////////////////////////////
// Doesn't need to be kept, up to you Ismael
////////////////////////////////////////////
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
/////////////////////////////////////////////////
/////////////////////////////////////////////////

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
void operation(int instruction, int valueX){
  int valid=1; // bool
  int opcode = getDecOpcodeFromDec(instruction);
  
  switch(opcode){
  case 0: // Load
    AC = memory[valueX];
    break;
  case 1: // Store
    memory[valueX] = AC;
    break;
  case 2: // Subtract
    AC = AC - valueX;
    break;
  case 3: // Add
    AC = AC + valueX;
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
    break;
  case -6: // ROR
    break;
  case -5: // ROL
    break;
  default:
    printf("Not an opcode! \n");
    valid=0;
  }
}

/* Given a file location in a string format, 
 * search that location to get something to fill
 * the memory
 */
void getMemFromFile(char *fileLocation) {
    FILE *fp; //file pointer
    int counter=0;
    char buffer[0xFF]; // 255 characters before buffer overload
    char sub[0xFF];
    int temp, tempOpc;

    // Opens the file the user has entered
    fp=fopen(fileLocation, "r");

    if (fp != NULL) { // checking if the file exists
        wipeMemory(); // Clear memory
        while(fscanf(fp,"%20s",buffer) == 1) { // fscanf for making sure what comes is max 20 characters long
          for (int i=0; i<255;i++) {
            sub[i]=buffer[i+3];
          }


          for (int i=1; i<4;i++) {
            if (buffer[i]=='1') {
              tempOpc+=pow(2,4-i-1);
            }
          }
          temp = binToDec(sub);

          
          memory[counter]=        ; // place it in that location in memory
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
		strcpy(memLoc, decToBinStr(counter,BITS_NUM_WORDS));
		strcpy(instruc, decToBinStr(memory[counter], INST_SIZE));
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

