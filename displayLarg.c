/* -std=c89 */
#include <stdio.h>

int main(void) {
  int userEntry, largestNum=0;
  for(;;) {
    printf("Please enter a positive number (or 0 for exit) : ");
    scanf("%d", &userEntry);

    if (userEntry < 0) {
      printf("Make sure that it is positive\n");
      continue;
    }
    if (userEntry > largestNum) {
      largestNum = userEntry;
    }

    if (userEntry == 0) {
      printf("The largest number entered was : %d\n", largestNum);
      break;
    }
  }
}
