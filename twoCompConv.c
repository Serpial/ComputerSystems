#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define INST_SIZE 16

/*
 * takes in a binary string and turns a 1 into a 0,
 * or vice versa, up to a set element in the string
 */
void invertUpTo(char *bin, int upToElem) {
  char* p = bin;
  
  for (int i=0 ; i<upToElem; i++) {
    if (*p=='1') {
      *p = '0';
    } else if (*p=='0'){
      *p = '1';
    } else if (*p=='\0') {
      break;
    }
    p++;
  }
}

/* Only converts back up to 16 bit 2s-compliment
 * To use simply put in a string of binary numbers
 * and it will turn it into a positive or negative 
 * number
 */

int binToDec(char *bin) {
  // Get length
  int bitSize=0, total=0;
  for (int i=0; i<INST_SIZE+1; i++) {
    if (bin[i]=='\0') {
      bitSize=i;
      break;
    }
  }

  // Add all the numbers together
  for (int i=0; i<bitSize;i++) {
    if (bin[i]=='1') {
      total+=pow(2,bitSize-i-1);
    }
  }

  return total;
}

char* decToBinStr(int dec, int bitSize) {
  // Turn a positive val into bin
  static char bin[INST_SIZE+1];

  if (bitSize!=INST_SIZE) {
    bin[bitSize]='\0';
  } else {
    bin[INST_SIZE]='\0';
  }
  
  // Make everything character the 0
  for (int i=0; i<bitSize; i++){;
    bin[i]='0';
  }

  for(int i=0; i<bitSize; i++) {
    if(dec>=pow(2, bitSize-i-1)){
      dec = dec - pow(2, bitSize-i-1);
      bin[i]='1';
    }
  }

  return bin;
}

int binToDec2s(char* bin) {
  int isNeg=0; // bool
  int bitSize=0, total=0;
  
  // find out how long the binary string is
  for (int i=0; i<INST_SIZE+1; i++) {
    if (bin[i]=='\0') {
      bitSize=i;
      break;
    }
  }
  
  // Invert and add 1 if the number is negative
  if (bin[0]=='1') {
    invertUpTo(bin, bitSize);

    isNeg=1;
    // Now we need to add 1
    for (int i=bitSize-1;i>0; i--) {
      if (bin[i]=='0') {
        bin[i]='1';
        for (++i; i<bitSize; i++) {
          bin[i]='0';
        }
        break;
      }
    }
  }

  

  // Add all the numbers together
  for (int i=1; i<bitSize;i++) {
    if (bin[i]=='1') {
      total+=pow(2,bitSize-i-1);
    }
  }

  // if the number is negative return the total
  // minus two times the total else return total  
  return isNeg? total-(total*2) : total;
}


/* arguements for this function are the decimal in
 * which you wish to turn into 2s-complement bin and
 * the number of bits you want to spread it across.
 * For example (-38, 16) will give you:
 * 1111111111011010
 * (Does also produce positive numbers as well)
 */
char *decToBinStr2s(int dec, const int bitSize) {  
  static char bin[INST_SIZE+1];
  int isNeg=0;
  int leastSigBit=bitSize;

  // HALT if we are using a bigger decimal than
  //    the bitsize can translate. For example,
  //    4 bits can only get between 7 and -7
  assert(dec<=pow(2,bitSize)-1);

  if (bitSize!=INST_SIZE) {
    bin[bitSize]='\0';
  } else {
    bin[INST_SIZE]='\0';
  }
  
  // Make everything character the 0
  for (int i=0; i<bitSize; i++){;
    bin[i]='0';
  }
  
  // Find out if the number is negative
  if (dec < 0) {
    isNeg=1;
    dec=fabs(dec); // Make the value positive
  }
  
  
  // Turn a positive val into bin
  for(int i=1; i<bitSize; i++) {
    if(dec>=pow(2, bitSize-i-1)){
      dec-=pow(2, bitSize-i-1);
      bin[i]='1';
    }
  }

  // Flip to neg representation
  if (isNeg==1) {
    // Now find the least significant bit
    for(int i=bitSize-1; i>0; i--) {
      if(bin[i]=='1') {
        leastSigBit=i;
        break;
      }
    }
    invertUpTo(bin, leastSigBit);
  }
  return bin;
}

/*
 * finds out what the decimnal value would be if
 * its binary value was in twos compliment
 */
int decTo2sDec(int dec) { 
  char temp[17];
  strcpy(temp,decToBinStr(dec,12));
  return binToDec2s(temp);
}

/*
 * finds out what a postive or negative number in binary
 * would be represented if it was unsigned.
 */
int dec2sToDec (int dec) {
  char temp[17];
  strcpy(temp,decToBinStr2s(dec,12));
  return binToDec(temp);
}



