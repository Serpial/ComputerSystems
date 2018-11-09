#include <stdio.h>
#include <string.h>

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

int strBinToDec(char* bin) {
  int count = getLength(bin);
  int total=0;
  int isNeg=0; // 0 if num is pos and 1 if num is neg
  int length=getLength(bin);


  

  
  if (length!=0) {
    if (bin[0]=='1') {
      isNeg = 1; 
    }
    
    for (int i=0; i<length; i++) {
      if (bin[i]=='0') bin[i]='1';
      if (bin[i]=='1') bin[i]='0';
    }
    
    
    for (int i=1; i<length; i++) {
      if (bin[i]=='1') {
        total+=power(2, count);
      }
    }
  }

  return total;
}

int main(void) {
  char something[INST_SIZE] = "0111";
  for (int i = 0; i < 10; i++){
      addOne(something, 4);
      printf("%s\n", something);
  }
}
