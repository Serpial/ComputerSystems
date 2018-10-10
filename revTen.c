/* -std=c89 */
#include <stdio.h>

int main(void) {
  int line, collectedNumbers[10];

  for (line = 0; line < 10; line++) {
    printf("Please enter a number : ");
    scanf("%d", &collectedNumbers[line]);
  }
  
  for (line--; line >= 0; line--) {
    printf("%d\n", collectedNumbers[line]);
  }
}
