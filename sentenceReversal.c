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
int findIndexOfBreak (char sentence[CHAR_SENTENCE_SIZE]);

void getWordArray (char sentence[CHAR_SENTENCE_SIZE], int spaceOfBreak, int *numWords,)

int main(void) {
  char sentence[CHAR_SENTENCE_SIZE];
  char words [MAX_WORDS] [CHAR_NUM_WORDS];
  char terminatingChar= '.';
  int goodChar = 0, numWords = 0, spaceOfBreak;
  int i,j;
  
  printf("Please enter a sentence that ends in a period, question mark, or exclamation point\n");
  printf("Enter sentence here : ");
  fgets(sentence, sizeof(sentence), stdin);
  
  spaceOfBreak = findIndexOfBreak(sentence);
  if (spaceOfBreak == 0) {
    return 0;
  }
  
  terminatingChar = sentence[spaceOfBreak];

  /* form a collection of words from the sentence */
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

  printf("Your sentence backwards is : ");
  
  /* print words backwards */
  for (i = numWords; i >= 0; i--) {
    printf("%s ", words[i]);
  }
  printf("%c%c\n",'\b',terminatingChar);
    
 
  return 0;
}

int findIndexOfBreak (char sentence[CHAR_SENTENCE_SIZE]) {
  int i; /* Index */
  int found = 0; /* bool found = false; */
  
  for (i = 0; i < CHAR_SENTENCE_SIZE; i++) {
    switch (sentence[i]) {
    case '!': case '?': case '.':
      found++; /* sets found to true if found */
    }
    if (found) break;
  }

  if (!found || i == 168) {
    printf("Please make sure to finish you sentence with a '.', '!', or '?'");
    return 0;
  } else {
    return i;
  }
}

