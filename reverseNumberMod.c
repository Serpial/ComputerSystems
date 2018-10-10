/* -std=c89 */
#include <stdio.h>

int main(void) {
  int inputNumber;

  for(;;) {
    printf("Please enter a 2-digit positive integer (or 0 to exit) : ");
    scanf("%d", &inputNumber);
    if (inputNumber > 9 && inputNumber < 100) {
      printf("The reversal of this number is : %d%d\n", inputNumber%10 , inputNumber/10);
    }
      
    if (inputNumber == 0) {
      printf("Goodbye...\n");
      break;
    }
  }
}
