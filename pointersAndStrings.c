#include <stdio.h>
#define sizeOfA 8

/* function prototypes */
void quest4(int *a, int *p, int *q);
void quest5(int *p);

int main(void) {
  int a[] = {5,15,34,54,14,2,52,72};
  int *p = &a[1], *q = &a[5];

  quest4(a,p,q);
  quest5(p);
  
}

void quest4(int *a, int *p, int *q) {
  printf("Question 4:\n");
  printf("%d\n", *(p+3));
  printf("%d\n", *(q-3));
  printf("%d\n", p < q);
  printf("%d\n", *p < *q);  
}

void quest5 (int *p) {
  int i = 5;
  p = &i;
  
  printf("Question 5:\n");
  printf("*p  : %d\n", *p);
  printf("*&i : %d\n", *&i);
  printf("&p  : %d\n", &p);
  printf("&*p : %d\n", &*p);
  printf("&i  : %d\n", &i);
  printf("p   : %d\n", p);
}
