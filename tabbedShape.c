/* -std=c89 */
#include <stdio.h>

int main(void) {
  int i;
  for (i = 0; i<3; i++) {
    if (i%2 != 1) {
      printf("*\t*\t*\n");
    } else {
      printf(" \t*\t \n");
    }
  }
}
