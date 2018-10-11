#include <stdio.h>
#define BASE_SENTENCE_SIZE 250

/* Function Prototypes */
/* void getInput(char *sentence[BASE_SENTENCE_SIZE]); */


int main(void) {
  char sentence[BASE_SENTENCE_SIZE];

  /* getInput(&sentence); */
  printf("Please enter a sentence that ends in a period, question mark, or exclamation point\n");
  printf("Enter sentence here : ");

  fgets(sentence, sizeof(sentence), stdin);



  
}

void getInput(char *sentence[BASE_SENTENCE_SIZE]) {
  
}
