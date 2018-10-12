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
  int goodChar = 0, numWords = 0, spaceOfBreak = -1;
  int i,j;

  /* getInput(&sentence); */
  printf("Please enter a sentence that ends in a period, question mark, or exclamation point\n");
  printf("Enter sentence here : ");

  fgets(sentence, sizeof(sentence), stdin);

  for (i = 0; i < CHAR_SENTENCE_SIZE; i++) {
    switch (sentence[i]) {
    case '!': case '?': case '.':
      spaceOfBreak = i;
    }
  }

  /* form a collection of words from the sentence */
  if (spaceOfBreak != -1){
    for (i = 0; i < spaceOfBreak; i++) {
      if (sentence[i] == ' ') {
        strcpy(words[numWords], words[numWords]+'\0');
        numWords++;
        if (sentence[i+1] != ' ') {
          strcpy(words[numWords], sentence[i+1]+"");
          printf("%c : %c\n", words[numWords][0], sentence[i+1]);
        }
      } else {
        strcpy(words[numWords], words[numWords]+ sentence[i]);
      }
    }
  } else {
    printf("Please make sure you end your sentence with either a !, ?, or .\n");
  }

  /* print words backwards */
  for (i = 0; i < numWords; i++) {
    printf("%s\n", words[i]);
  }

  
}

