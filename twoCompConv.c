#include <stdio.h>
#include <string.h>
#include <math.h>

#define INST_SIZE 16+1

int power(int b, unsigned p) {
  if (p==0) return 1;
  int pow = power(b, p/2);
  if (p&1) return b*pow*pow;
  return pow*pow;
}

void addOne(char* bin, int length) {
  int i; // iterator
 
  for (i=length-1; i>=0; --i) {
    if (bin[i]=='0') {
      bin[i]='1';
      break;
    }
  }

  // work out why this logic is skipping 1st element.
  if (i==0 && bin[1]=='1') {
    for (++i;i<length; i++) {
      bin[i]='0';
    }
  }
}

// Works out the length of the string based on 1s and 0s
int getLength(char* bin) {
  int counter=0;
  for(;;) {
    if (bin[counter]!='1'&&bin[counter]!='0') {
      return counter;
    }
    counter++;
  }
}

void decToBinBinStr(int dec, char* strToReturn) {
  char bin[INST_SIZE];

  // Make everything character the null character
  for (int i=0; i<INST_SIZE; i++){
    strToReturn[i]='\0';
  }
  
  
  // Find out if the number is negative
  if (dec < 0) {
    bin[0]='1';
    fabs(dec); // Make the value positive
    dec++;
  }
  else bin[0]='0';
  for (int i=INST_SIZE-1; i>0 ; i--) {
    if(power(2, i) <= dec) {
        bin[i]='1';
        bin-power(2,i);
    } else {
      bin[i]='0';
    }
  }

  // Instead of returning a char*
  strcpy(strToReturn, bin);
}

// Just used for testing
int main(void) {
  char something[INST_SIZE];
  for (int i = 0; i < 10; i++){
    decToBinBinStr(i, something);
    printf("%s\n", something);
  }
}
