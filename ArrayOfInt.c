/* -std=c89  */
#include <stdio.h>
#define ARRAY_SIZE 5

/* Function Prototypes  */
void displayArrayAndSum(int theBigArray[ARRAY_SIZE][ARRAY_SIZE]);

int main(void) {
  /* Local Variables */
  int i;
  int theBigArray [ARRAY_SIZE][ARRAY_SIZE];


  /* Get each row from the user */
  for (i = 0; i < ARRAY_SIZE; i++) {
    printf("Please enter the values of row %d (seperate with spaces) : ", i);
    scanf(" %d %d %d %d %d", &theBigArray[i][0], &theBigArray[i][1], &theBigArray[i][2], &theBigArray[i][3], &theBigArray[i][4]);
  }
  
  displayArrayAndSum(theBigArray);
}

/* 
   This function gets the totals of the values as they are being
   displayed and then prints the totals out at the right-most side
   and the bottom line
 */
void displayArrayAndSum(int theBigArray[ARRAY_SIZE][ARRAY_SIZE]) {
  /* Local Variables */
  int i, j, sumHorzVals = 0, sumVertVals[ARRAY_SIZE];
  char *linebreak = "-----------------------------------------\n";
  
/* init the sumVertlines with it's starting value: 0 */
  for (i = 0; i < ARRAY_SIZE; i++) {
    sumVertVals[i] = 0;
  }


  /* Print Values and Horizontal totals */
  printf("%s|",linebreak);
  for (i = 0; i < ARRAY_SIZE; i++) {
    for (j = 0; j < ARRAY_SIZE; j++){
      printf("%d\t", theBigArray[i][j]);
      /* Add this value to the horizontal and vertical total */
      sumHorzVals += theBigArray[i][j];
      sumVertVals[j] += theBigArray[i][j];
    }
    printf("|\t%d\n", sumHorzVals);
    if (!(i == ARRAY_SIZE-1)) {
      printf("|");
    }
    sumHorzVals = 0;

  }
  

  /* Print Vertical Totals */
  printf("%s",linebreak);
  for (i = 0; i < ARRAY_SIZE; i++) {
    printf("%d\t",sumVertVals[i]);
  }
  printf("\n");
}
