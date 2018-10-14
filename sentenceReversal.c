/*
 * Title       : Sentence Reversal
 * Author      : Paul Hutchison, 201741535
 * Description : This program covers questions 8
 *               This program takes in a sentence from the user
 *               and then flips every word in the sentece so
 *               that for a four word sentence, the first becomes
 *               the fourth and the second becomes the third
 *               and the third and fourth flip respectively.
 */

/* Include/Define Directives */
#include <stdio.h>
#include <string.h>
#define CHAR_SENTENCE_SIZE 250 /* maxumum number of characters a sentence can be */
#define CHAR_NUM_WORDS 20 /* maximum number of characters a word can be */
#define MAX_WORDS 10 /* maximum number of words the user can have in their sentence */

/* Function Prototypes */
int findIndexOfBreak (char sentence[CHAR_SENTENCE_SIZE]);
int getNumWordsAndFillWords (char sentence[CHAR_SENTENCE_SIZE],char words[MAX_WORDS][CHAR_NUM_WORDS], int spaceOfBreak);

/* Definition of Main */
int main(void) {
  char sentence[CHAR_SENTENCE_SIZE];
  char words [MAX_WORDS] [CHAR_NUM_WORDS];
  char terminatingChar = '.';
  int numWords, spaceOfBreak;
  int i; /* Index */
  
  printf("Please enter a sentence that ends in a period, question mark, or exclamation point\n");
  printf("Enter sentence here : ");
  fgets(sentence, sizeof(sentence), stdin);
  
  spaceOfBreak = findIndexOfBreak(sentence);
  if (spaceOfBreak == 0) {
    return 0;
  }

  /* words is also filled when this within this function as 
     the words are being found */
  numWords = getNumWordsAndFillWords(sentence, words, spaceOfBreak);
  
  terminatingChar = sentence[spaceOfBreak];
  
  /* print words backwards */
  printf("Your sentence backwards is : ");
  for (i = numWords; i >= 0; i--) {
    printf("%s ", words[i]);
  }
  printf("%c%c\n",'\b',terminatingChar);
  return 0;
}


/* getNumWordsAndFillWords
 * This function gets the number of words. it also gets
 * each word and puts it in an array. It uses the space 
 * of the break to decide where the end of the sentence
 * is. The variable goodChar is the index of a character
 * that isn't a space.
 */
int getNumWordsAndFillWords (char sentence[CHAR_SENTENCE_SIZE],char words[MAX_WORDS][CHAR_NUM_WORDS], int spaceOfBreak) {
  int i; /* Index */
  int goodChar = 0, numWords=0;
  
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
  return numWords;
}


/* findIndexOfBreak
 * this function finds the index of the break. It also
 * returns an error if the user hasn't entered a termi-
 * nating character at the end of their sentence. It
 * also stops after the first sentence.
 */
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

  if (!found) {
    printf("Please make sure to finish you sentence with a '.', '!', or '?'");
    return 0;
  } else {
    return i;
  }
}

