/* -std=c89 */
#include <stdio.h>

int main() {
  int lineNum = 0, i,j;
  for (i=0; i<3; i++) {
    for (j=lineNum-1; j < 6; j++ ) {
      printf(" ");
    }
    lineNum++;
    printf("*\n");
  }
  printf("*   *\n");
  printf(" * *\n");
  printf("  *\n");
}
