/**************************************************************************
 * Assessment Title: Assessed Coursework Exercise 3
 *
 *
 * Number of Submitted C Files:  
 *
 * 
 * Date: 
 *
 * 
 * Authors: 
 *	1. Paul Hutchison, Reg no: 201741535
 *	2. Lucy Pennington, Reg no: 201707823
 *	3. Ismael Ahmed, Reg no: YOUR_REGISTRATION_NUMBER
 *	4. Christopher Reilly, Reg no: YOUR_REGISTRATION_NUMBER
 *	5. YOUR_FULL_NAME, Reg no: YOUR_REGISTRATION_NUMBER
 * 
 *
 *	Statement: We confirm that this submission is all our own work.
 *
 *      (Signed)_Paul_James_Hutchison_
 *	
 * 	(Signed)_____________________________________(YOUR_FULL_NAME)
 *	
 *	(Signed)_____________________________________(YOUR_FULL_NAME)
 *	
 *	(Signed)_____________________________________(YOUR_FULL_NAME)
 *
 *	(Signed)_____________________________________(YOUR_FULL_NAME)
 *
 **************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h> // used for 'pow()' | Make sure to use -lm when compiling

#include "twoCompConv.h" 

#define INST_SIZE 16 // Size of an instruction
#define INVALID_MEMORY_ITEM 12<<12 // There are opcodes 0 to 11. As soon as one uses 12 the whole istruction is invalid

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
int getMemFromFile(char *fileLocation);
void wipeMemory(); // resets memory
void displayMemBin(); // Displays memory in binary
int displayMemAfterInput();
void userInput();
int operation();
int validArgue (char *argv[]);
void printHelp();
void machToAss();
int fillMemory(int argc, char *argv[]);
void placeDefaultInMem();


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
  
  if (fillMemory(argc,argv)==0) {
    return 0;
  }
  
  
  // Check if the user would like to display memory
  if(displayMemAfterInput()){;
    printf("\t--------------------\n");
  }
  machToAss();
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
 * Gets user input from console making sure
 * to deal with some errors that the user may
 * accidently cause.
 */
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
 * A little recursive function that continues to ask
 * if the would like to print memory until they enter 
 * a syntatically correct answer.
 */
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
 * also returns whether or not the action was a success
 * and -1 if there is a syntax error
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

/* This function displays everything in memory in a 
 * binary format such as:
 * <A memory Location> -> <an instruction from that location in memory>
 * 000000100001 -> 0001000000000001
 */
void displayMemBin () {
  int counter=0;
  printf("Memory Location\t->\tInstruction\n"); // Heading
  while(memory[counter]!=INVALID_MEMORY_ITEM) {
    printf("%s\t->\t", decToBinStr(counter, 12));
    printf("%s\n", decToBinStr(memory[counter],16));
    counter++;
  }
}

void placeDefaultInMem() {
  wipeMemory();
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

/* The default should be 12<<12 as twelve is the first invalid
 * opcode and thus the decimal value in memory should always be 
 * smaller. It is logically shifted left to push it into the
 * location of the opcode
 */
void wipeMemory() {
  int max= pow(2, 12);
  for (int i=0; i<max; i++) {
    memory[i]=INVALID_MEMORY_ITEM;  
  }
}

/*
 * Returns 1 if we have successfully filled memory
 * Returns 0 if the arguements the user has entered were incorrect
 */
int fillMemory(int argc, char *argv[]){
  
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
      userInput();
      return 1;
    case 'd':
      placeDefaultInMem();
      return 1;
    case 'f':
      if (!getMemFromFile(argv[2])) {
        return 0; // if we are not able to find the file, close the program
      } else {
        return 1;
      }
      return 0;
    }
  }
  return 0;

}


/*
 * Simply prints the opcode translate into assembly along side
 * the operand of the instruction.
 */
void machToAss(){
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

