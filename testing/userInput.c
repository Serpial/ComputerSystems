#include <stdio.h>
#include <string.h>
#include <ctype.h> // for coverting the user's input to capitals

const char mnemonic[8][9]={"LOAD","STORE","SUBT","ADD","INPUT","OUTPUT","HALT","SKIPCOND"};
const char negativeMnemonic[4][5]={"JUMP","MULT","ROR","ROL"};

void userInput(int *memory) {
  const int ENTRY_SIZE=255;
  char entry[ENTRY_SIZE];
  int nulLoc=0, endOfOper=0;
  char operation[9];
  int validOper=0;
  
  printf("Enter \"stop\" to exit.\n");
  for(;;) {
    // make everything in the array a null character
    // cos for some reason there is random junk
    for (int i=0; i < ENTRY_SIZE; i++) { 
      entry[i]='\0';
    }

    printf("\t"); // formatting so there is a tab before every line of code
    fgets(entry, sizeof(entry), stdin);
    
    for (int i=0; i<ENTRY_SIZE; i++) {
      if (entry[i]=='\0') {
        nulLoc=i;
        break;
      }
    }

    if (strstr(entry, "stop")!=NULL) { // entry contain stop
      return;
    } else {
      printf("entry : %s\n", entry);
      // find index of first space
      for (int i=1; i < nulLoc; i++) {
        if (entry[i]==' ') {
          endOfOper=i;
          operation[i]='\0';
          break;
        } else {
          operation[i]=entry[i];
        }
      }

      // Capitalise the word
      for (int i=0; i<endOfOper; i++) {
        operation[i]=toupper(entry[i]);
      }
      
      // check if it is a valid instruction
      for (int i=0; i<12; i++) {
        if (i < 8) {
          printf("i<8 : %s:%s\n",operation, mnemonic[i]);
          if (strstr(operation, mnemonic[i])!=NULL) {
            validOper=1;
            break;
          }
        } else {
          printf("i>=8 : %s:%s\n",operation, negativeMnemonic[i-8]);
          if (strstr(operation, negativeMnemonic[i-8])!=NULL) {
            validOper=1;
            break;
          }
        }  
      }

      

    }

    printf("SYNTAX ERROR : Something you entered was not quite right\n");

    // prepare for the next instruction
    validOper=0;
  }
}
