#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_NICKNAME_CHAR 50
#define MAX_INPUT_CHAR 2

// Function Prototypes 

  // Question 1 Function and helper functions
void prompt_user(char *message, char *answer); // char validLetters[MAX_VALID_LETTERS]);
void getValidPeice(char *playerPiece1, char *playerPiece2);
void getNickname(int player, char *nickname);
void getGameDetails(int *gameType, char *playerPiece1, char *playerPiece2, char *nickname1, char *nickname2);

int main(void) {
  int gameType;
  char playerPiece1, playerPiece2;
  char nickname1[MAX_NICKNAME_CHAR],nickname2[MAX_NICKNAME_CHAR];
  

  for (;;) {
    getGameDetails(&gameType, &playerPiece1, &playerPiece2, nickname1, nickname2);
    
    if (gameType == 0) {
      return 0;
    }
  }
}

///////////////////////////////////////////////////////////////////
// Question 1 Functions
///////////////////////////////////////////////////////////////////

void prompt_user(char *message, char *answer) { 
  char userInput[MAX_INPUT_CHAR];

  // Print message and get user input
  printf("%s", message);
  scanf(" %c", &userInput[0]);
  
  // clear input buffer for use of fgets later on
  while( getchar() != '\n' );

  // make answer from userInput
  userInput[0] = toupper(userInput[0]);
  userInput[1] = '\0';
  strcpy(answer, userInput);
}

void getGameDetails(int *gameType, char *playerPiece1, char *playerPiece2, char *nickname1, char *nickname2) {
  char menuInput[MAX_INPUT_CHAR];

  // Question 1 part i
  printf("\nMenu\n----\n1. Play Against A User\n");
  printf("2. Play against a Computer\n0. Exit\n");
  prompt_user("Enter a number : ", menuInput);
  switch (menuInput[0]) {
  case '1':
    // Question 1 part ii
    getValidPeice(playerPiece1, playerPiece2);
    // Question 1 part iii
    getNickname(1, nickname1);
    getNickname(2, nickname2);
    *gameType = 1;
    break;
  case '2':
    // User wishes to play against the computer
    getValidPeice(playerPiece1, playerPiece2);
    *gameType = 2;
    break;
  case '0':
    *gameType = 0;
    return;
  default:
    printf("What you entered was invalid\n");
    getGameDetails(gameType, playerPiece1, playerPiece2, nickname1, nickname2);
  }
}

void getNickname(int player, char *nickname) {
  int numOfInd;
  
  printf("Please enter nickname for player %d : ", player);
  fgets(nickname, sizeof(nickname), stdin);
  numOfInd = strlen(nickname)-1;
  if ( nickname[numOfInd] == '\n') {
    nickname[numOfInd] = '\0';
  }
}

void getValidPeice(char *playerPiece1, char *playerPiece2) {
  char tempString[MAX_INPUT_CHAR];
  printf("Would player 1 like to play as X or 0?\n");
  for (;;) {
    prompt_user("Please enter X or O : ", tempString);
    if (tempString[0] == 'X') {
      *playerPiece1 = 'X';
      *playerPiece2 = 'O';
      return;
    } else if (tempString[0] == 'O') {
      *playerPiece1 = 'O';
      *playerPiece2 = 'X';
      return;
    } else {
      printf("The input you entered was invalid\n");
    }
  }
}
///////////////////////////////////////////////////////////////////




