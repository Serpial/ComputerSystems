#include <stdio.h>
#include <stdint.h>
#include "twoCompConv.h"


void getMemFromFile(char *fileLocation, int16_t *memory, int maxMem) {

  FILE *fp;
  int counter=0;
  char buffer[20];

  fp=fopen(fileLocation, "r");

  if (fp != NULL) {
    while(fscanf(fp,"%20s",buffer) == 1) {
        memory[counter]=binToDec(buffer);
        counter++;
    }
  } else {
    printf("This file does not exist\n");
  }
  fclose(fp);
}
