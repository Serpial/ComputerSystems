#include <stdio.h>
#define MAX_VALID_LETTERS 10

// Function Prototypes 
char getMenuInput(char validLetters[MAX_VALID_LETTERS]) {
  char userInput[2];

  printf("Enter input : ");
  scanf(" %c", &userInput[0]);
  userInput[1] = '\0';
  for (int i = 0; i < MAX_VALID_LETTERS; i++) {
    if (userInput[0] == validLetters[i]) {
      return userInput[0];
    }
  }
  printf("Invalid Input. ");
  return getMenuInput(validLetters);
}

int main(void) {
  char menuInput;

  printf("Menu\n----\n1. Play Against A User\n");
  printf("2. Play against a Computer\n0. Exit\n");
  menuInput = getMenuInput("120");
}
