/*
 * Title       : Volume and Area
 * Author      : Paul Hutchison, 201741535
 * Description : This program covers questions 1 to 5
 *               This program takes the radius of a sphere from the user
 *               and, based on the user's input, outputs the volume,
 *               surface area, or both.
 */


#include <stdio.h>
#include <string.h>
#define CHAR_SENTENCE_SIZE 250 /* maxumum number of characters a sentence can be */
#define CHAR_NUM_WORDS 20 /* maximum number of characters a word can be */
#define MAX_WORDS 10 /* maximum number of words the user can have in their sentence */

/* Function Prototypes */
/* none */

int main(void) {
  char sentence[CHAR_SENTENCE_SIZE];
  char words [MAX_WORDS] [CHAR_NUM_WORDS];
  char terminatingChar= '.';
  int goodChar = 0, numWords = 0, spaceOfBreak = -1;
  int i,j;

  /* getInput(&sentence); */
  printf("Please enter a sentence that ends in a period, question mark, or exclamation point\n");
  printf("Enter sentence here : ");

  fgets(sentence, sizeof(sentence), stdin);

  for (i = 0; i < CHAR_SENTENCE_SIZE; i++) {
    switch (sentence[i]) {
    case '!': case '?': case '.':
      terminatingChar = sentence[i];
      spaceOfBreak = i;
    }
  }

  /* form a collection of words from the sentence */
  if (spaceOfBreak != -1){
    for (i = 0; i < spaceOfBreak; i++) {
      if (sentence[i] == ' ') {
        words[numWords++][goodChar] = '\0';
        /* On to the next word */
        if (sentence[i+1] != ' ' && spaceOfBreak != i+1) {
          words[numWords][0] = sentence[++i];
          goodChar = 1;
        }
      } else {
        words[numWords][goodChar++] = sentence[i];
      }
    }
    words[numWords][goodChar] = '\0';

    printf("Your sentence backwards is : \n");
    
    /* print words backwards */
    for (i = numWords; i >= 0; i--) {
      printf("%s ", words[i]);
    }
    printf("%c%c\n",'\b' ,terminatingChar);
  } else {
    printf("Please make sure you end your sentence with either a !, ?, or .\n");
  }
 
}

