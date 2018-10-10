/* -std=c89 */
#include <stdio.h>

int main(void) {
  int inputNumber;

  printf("Please enter a 2-digit positive integer : ");
  scanf("%d", &inputNumber);

  printf("The reversal of this number is : %d%d\n", inputNumber%10 , inputNumber/10);
  
}
