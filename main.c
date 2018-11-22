#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "twoCompConv.h" // because it is a local file it is in double quotes instead of <>

#define INST_SIZE 16 // Size of an instruction
#define OPCODE_SIZE 4 // Number of bits an opcode takes up
#define BITS_NUM_WORDS 12+1 // 2^12=4096 plus 1 for twos comp

typedef struct {
  unsigned int PC:12;
  unsigned int MAR:12;
  unsigned int IR:16;
  unsigned int MB:16;
  unsigned int AC:16;
  unsigned int InREG:16;
  unsigned int OutREG:16;
} Registers;




int memory[4096];
// To get the opcode from the int please use memory[i]>>12 (Using shifts)
// to get the operand, please you memory[i]&0xFFF (Using 'and' masking)


// Registers
Registers registers;
const char mnemonic[12][9]={"LOAD","STORE","SUBT","ADD","INPUT","OUTPUT",
                            "HALT","SKIPCOND","JUMP","MULT","ROR","ROL"};

// function prototypes
// void operation(int valueX, int AC);  // edited once we have fetch execute down
int getMemFromFile(char *fileLocation);
void wipeMemory(); // resets memory
void displayMemBin(); // Displays memory in binary
int displayMemAfterInput();
void userInput();
int operation();
int validArgue (char *argv[]);
void printHelp();
void machToAss();


/* main that takes in arguments -c, -d, -f, or 
 * --help (used to get a list of commands)
 */
int main(int argc, char *argv[]) {
  int maxArg;

  // init registers
  registers.PC=0;
  registers.MAR=0;
  registers.IR=0;
  registers.MB=0;
  registers.AC=0;
  registers.InREG=0;
  registers.OutREG=0;
  wipeMemory();
  
  
  
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
        return 0;
      }
      break;
    case 'c':
      userInput();
      break;
    case 'd':
      printf("This is what would happen in -d if we had written it yet\n");
      break;
    }
  case 2:    
    if (strcmp(argv[1], "-f")==0) {
      if (!getMemFromFile(argv[2])) {
        return 0; // if we are not able to find the file, close the program
      }
      break;
    }
  }

  // Check if the user would like to display memory
  displayMemAfterInput();






  machToAss();
  
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
    registers.AC = registers.AC - registers.MB;
    break;
  case 3: // Add
    registers.AC = registers.AC + registers.MB;
    break;
  case 4: // Input
    printf("Enter input for AC: ");
    int temp;
    scanf("%d", &temp); // needed because you cant & a bitfield
    registers.InREG=temp;
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
    if (ac>0) {
      registers.PC += 1;
    }
    break;  
  case 8: // Jump
    registers.PC = registers.MAR-1;
    break;
  case 9: // Mult
    registers.AC = registers.AC * registers.MB;
    break;
  case 10: // ROR
    registers.AC = registers.AC >> registers.MAR;
    break;
  case 11: // ROL
    registers.AC = registers.AC << registers.MAR;
    break;
  default:
    printf("Not an opcode! \n");
  }
  //registers.PC += 1; in fetch/execute 
}

void userInput() {
  char binaryInput[INST_SIZE+1];
  int validEntry=1; // bool | assumes valid
  int displayMemory=0; // bool | used when closing function
  char opcode[5], operand[13];
  int counter=0;

  wipeMemory();
  
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

int displayMemAfterInput() {
  char entry[255];
  printf("Would you like to print memory? (y or n) :");
  scanf(" %s", entry);

  if (strcmp(entry, "y")==0) {
    displayMemBin();
    return 1;
  } else if (strcmp(entry, "n")==0) {
    return 0;
  } else {
    return displayMemAfterInput();
  }
  
}

/* Given a file location in a string format, 
 * search that location to get something to fill
 * the memory
 * 
 * also returns whether or not the action was a success.
 */
int getMemFromFile(char *fileLocation) {
    FILE *fp=NULL; //file pointer
    int counter=0;
    char buffer[0xFF]; // 255 characters before buffer overload

    // Opens the file the user has entered
    fp=fopen(fileLocation, "r");
    
    if (fp != NULL) { // checking if the file exists
        wipeMemory(); // Clear memory
        while(fscanf(fp,"%20s",buffer) == 1) { // fscanf for making sure what comes is max 20 characters long

          memory[counter]= binToDec(buffer);
          
          counter++;
        }
        fclose(fp);
        return 1;
    } else {
        printf("This file does not exist\n");
        return 0;
    }
}

/* This function displays everything in memory in a 
 * binary format such as:
 * <A memory Location> -> <an instruction from that location in memory>
 * 000000100001 -> 0001000000000001
 */
void displayMemBin () {
  int counter=0;
  printf("Memory Location\t->\tInstruction\n"); // Heading
  while(memory[counter]!=0) {
    printf("%s\t->\t", decToBinStr(counter, 12));
    printf("%s\n", decToBinStr(memory[counter],16));
    counter++;
  }
}

/* Empties memory making every value 0
 */
void wipeMemory() {
    int max= pow(2, BITS_NUM_WORDS-1);
    for (int i=0; i<max; i++) {
        memory[i]=0;
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


void machToAss(){

  int operand_1;
  unsigned int opcode_2;
  
  for (int i=0; i < 4096; i++){
    
    opcode_2 = memory[i]>>12;
    operand_1 = memory[i]&0xFFF;

    if (opcode_2==0 && operand_1==0) {
      return;
    }
    
    printf("\t");
    printf("\t%s  ", mnemonic[opcode_2]);
    printf("%d\n", operand_1);
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

