/* -std=c89 */
#include <stdio.h>

int main(void) {
  int x, result;
  printf("Please enter a number : ");
  scanf("%d", &x);

  result = 2*x*x*x*x - 5*x*x*x - x*x + 7*x - 6;
  printf("%d\n", result);
}
