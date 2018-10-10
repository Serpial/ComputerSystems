/* -std=c89 */
#include <stdio.h>

int main(void) {
  printf("An int is %ld bit(s)\n",sizeof(int)*8);
  printf("A short is %ld bit(s)\n",sizeof(short)*8);
  printf("A long is %ld bit(s)\n",sizeof(long)*8);
  printf("A char is %ld bit(s)\n",sizeof(char)*8);
  printf("A float is %ld bit(s)\n",sizeof(float)*8);
  printf("A double is %ld bit(s)\n",sizeof(double)*8);  
}
