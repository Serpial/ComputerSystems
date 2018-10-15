#include <stdio.h>
#define sizeOfA 8

/* function prototypes */
void quest4(int *a, int *p, int *q);


int main(void) {
  int a[] = {5,15,34,54,14,2,52,72};
  int *p = &a[1], *q = &a[5];

  quest4(a,p,q);
  
}

void quest4(int *a, int *p, int *q) {
  printf("%d\n", *(p+3));
  printf("%d\n", *(q-3));
  printf("%d\n", p < q);
  printf("%d\n", *p < *q);  
}
