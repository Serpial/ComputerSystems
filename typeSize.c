/* -std=c89 */
#include <stdio.h>

int main(void) {
  printf("An int is %ld byte(s)\n",sizeof(int));
  printf("A short is %ld byte(s)\n",sizeof(short));
  printf("A long is %ld byte(s)\n",sizeof(long));
  printf("A char is %ld byte(s)\n",sizeof(char));
  printf("A float is %ld byte(s)\n",sizeof(float));
  printf("A double is %ld byte(s)\n",sizeof(double));  
}
