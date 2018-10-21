/**************************************************************************
 * Assessment Title:
 *
 * Number of Submitted C Files: 
 *
 * Date: October 2018
 *
 * 
 * Author: Paul James Hutchison, Reg no: 201741535
 *
 *
 * Personal Statement: I confirm that this submission is all my own work.
 *
 *          (Signed)_Paul___James___Hutchison____________(YOUR_FULL_NAME)
 *
 * 
 *
 **************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_NICKNAME_CHAR 50
#define MAX_INPUT_CHAR 2
#define SQUARE_CAP 3

// Function Prototypes 
//     Question 1 Function and helper functions
void prompt_user(char *message, char *answer);
//
void getValidPiece(char *playerPiece1, char *playerPiece2, char nickname1[MAX_NICKNAME_CHAR], char nickname2[MAX_NICKNAME_CHAR]);
void getNickname(int player, char *nickname);
void getGameDetails(int *gameType, char *playerPiece1, char *playerPiece2, char *nickname1, char *nickname2);
//     Question 2 Function
void clear_board(char gameBoard[SQUARE_CAP][SQUARE_CAP]);
//     Question 3 Function
void display_board(char gameBoard[SQUARE_CAP][SQUARE_CAP]);
//     Question 4 Function
void user_move(char gameBoard[SQUARE_CAP][SQUARE_CAP]) {

}
//     Question 5 Function
void computer_move(char gameBoard[SQUARE_CAP][SQUARE_CAP]) {
  
}
//     Question 6 Functions
int detect_win(char gameBoard[SQUARE_CAP][SQUARE_CAP]);
char testSet(char testArray[SQUARE_CAP]);


///////////////////////////////////////////////////////////////////
// Question 7 Function
///////////////////////////////////////////////////////////////////
int main(void) {
  int gameType;
  char playerPiece1, playerPiece2;
  char nickname1[MAX_NICKNAME_CHAR],nickname2[MAX_NICKNAME_CHAR];
  char gameBoard[SQUARE_CAP][SQUARE_CAP];
  
  for (;;) {
    clear_board(gameBoard);
    getGameDetails(&gameType, &playerPiece1, &playerPiece2, nickname1, nickname2);
    
    if (gameType == 0) {
      return 0;
    } else {
      display_board(gameBoard);
    }

    switch(int detect_win(gameBoard)) {
    case 0:
      printf("%s won\n", nickname1);
      break;
    case 1:
      printf("%s won\n", nickname2);
    default:
      printf("There was no winner");
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
  scanf(" %s", answer);
}

void getGameDetails(int *gameType, char *playerPiece1, char *playerPiece2, char *nickname1, char *nickname2) {
  char menuInput[MAX_INPUT_CHAR];

  // Question 1 part i
  printf("\nMenu\n----\n1. Play Against A User\n");
  printf("2. Play against a Computer\n0. Exit\n");
  prompt_user("Enter a number : ", menuInput);
  switch (menuInput[0]) {
  case '1':
    // Question 1 part iii
    getNickname(1, nickname1);
    getNickname(2, nickname2);
    
    // Question 1 part ii
    getValidPiece(playerPiece1, playerPiece2, nickname1, nickname2);
    *gameType = 1;
    break;
  case '2':
    // User wishes to play against the computer
    getValidPiece(playerPiece1, playerPiece2, nickname1, nickname2);
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
  printf("For the player number %d, ", player);
  prompt_user("please enter a nickname : ", nickname);
}

void getValidPiece(char *playerPiece1, char *playerPiece2, char nickname1[MAX_NICKNAME_CHAR], char nickname2[MAX_NICKNAME_CHAR]) {
  char tempString[MAX_INPUT_CHAR];
  printf("What would %s like to play as X or 0?\n", nickname1);
  for (;;) {
    prompt_user("Please enter X or O : ", tempString);
    tempString[0] = toupper(tempString[0]);
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
  printf("This means that %s is %c.\n", nickname2, *playerPiece2);
}

///////////////////////////////////////////////////////////////////
// QUESTION 2 Function
///////////////////////////////////////////////////////////////////

void clear_board(char gameBoard[SQUARE_CAP][SQUARE_CAP]){
  for (int i = 0; i < SQUARE_CAP; i++) {
    for (int j = 0; j < SQUARE_CAP; j++) {
      gameBoard[i][j] = 'n';
    }
  }
}

///////////////////////////////////////////////////////////////////
// QUESTION 3 Function
///////////////////////////////////////////////////////////////////

void display_board(char gameBoard[SQUARE_CAP][SQUARE_CAP]) {
  printf("\n\t");
  for (int i = 0; i < SQUARE_CAP; i++) {
    for (int j = 0; j < SQUARE_CAP; j++) {
      if (gameBoard[i][j] == 'X' || gameBoard[i][j] == 'O') {
        printf(" %c", gameBoard[i][j]);
      } else {
        printf("  ");
      }
      if (j < SQUARE_CAP-1) {
        printf(" |");
      } 
    }
    if (i < SQUARE_CAP-1) {
      printf("\n\t");
      for (int j = 0; j < SQUARE_CAP*3+2; j++) {
        printf("-");
      }
      printf("\n\t");
    }
  }
  printf("\n");
}

///////////////////////////////////////////////////////////////////
// QUESTION 4 Function
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// QUESTION 6 Functions
///////////////////////////////////////////////////////////////////

char testSet(char testArray[SQUARE_CAP]) {
  int counter = 1;
  if (testArray[0] != 'n') {
    for(;;) {      
      if (testArray[counter] != testArray[counter-1]){
        break;
      } else {
        if (counter+1 < SQUARE_CAP) {
          counter++;
        } else {
          return testArray[0];
        }
      }
    }
  }
  return 'n';
}

int detect_win(char gameBoard[SQUARE_CAP][SQUARE_CAP]) {
  char testArray[SQUARE_CAP], testChar = 'n';
  // Horizontals
  for (int i = 0; i < SQUARE_CAP; i++) {
    for (int j = 0; j < SQUARE_CAP; j++) {
      testArray[j] = gameBoard[i][j];
    }
    testChar = testSet(testArray);
    if (testChar != 'n') {
      break;
    }
  }

  // Vertical
  if (testChar != 'n') {
    for (int i = 0; i < SQUARE_CAP; i++) {
      for (int j = 0; j < SQUARE_CAP; j++) {
        testArray[j] = gameBoard[j][i];
      }
      testChar = testSet(testArray);
      if (testChar != 'n') {
        break;
      }
    } 
  }

  // Horizontals
  if (testChar != 'n') {
    // top left to bottom right
    for (int i = 0; i < SQUARE_CAP; i++) {
      testArray[i] = gameBoard[i][i];
    }
    testChar = testSet(testArray);
    if (testChar != 'n') {
      break;
    }
    // top right to bottom left
    for (int i = SQUARE_CAP; i > 0; i--) {
      testArray[i] = gameBoard[i][SQUARE_CAP-i];
    }
    testChar = testSet(testArray);
  }
  
  switch(testChar) {
  case 'X':
    return 1;
  case 'O':
    return 0;
  default:
    return -1;
  }
}
