/**************************************************************************
 * Assessment Title: Ace 2 : Tic-Tac-Toe
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
 *          (Signed)Paul James Hutchison
 *
 * 
 *
 **************************************************************************/

#include <stdio.h>
#include <ctype.h> // To capitalise a character
#include <string.h>
#include <unistd.h> // Used for sleeping the program to emulate the computer thinking
// Used in getting random int
#include <time.h>
#include <stdlib.h>


#define MAX_INPUT_CHAR 50 // The maximum number of characters a nickname can be
#define SQUARE_CAP 3 // The number of elements in a row or column in tic-tac-toe
#define TRUE 1
#define FALSE 0

/*     Function Prototypes     */
/*-----------------------------*/
//     Question 1 Functions
void prompt_user(char *message, char *answer);
void getValidPiece(char *playerPiece1, char *playerPiece2, char nickname[2][MAX_INPUT_CHAR]);
void getNickname(int player, char *nickname);
void getGameDetails(int *gameType, char *playerPiece1, char *playerPiece2, char nickname[2][MAX_INPUT_CHAR]);

//     Question 2 Function
void clear_board(char gameBoard[SQUARE_CAP][SQUARE_CAP]);

//     Question 3 Function
void display_board(char gameBoard[SQUARE_CAP][SQUARE_CAP]);

//     Question 4 Functions
void user_move(char gameBoard[SQUARE_CAP][SQUARE_CAP]);
void getRowOrColumn(int *rowOrColumn, int isRow);
int canPlacePiece (char gameBoard[SQUARE_CAP][SQUARE_CAP],int row,int column);
  
//     Question 5 Function
void computer_move(char gameBoard[SQUARE_CAP][SQUARE_CAP]);

//     Question 6 Functions
char testSet(char testArray[SQUARE_CAP]);
int detect_win(char gameBoard[SQUARE_CAP][SQUARE_CAP]);

//     Question 7 Functions
void findAndReplaceTempMove(char gameBoard[SQUARE_CAP][SQUARE_CAP], char piece);
void runUserMove(char gameBoard[SQUARE_CAP][SQUARE_CAP], char *nickname, char piece);
int isFull(char gameBoard[SQUARE_CAP][SQUARE_CAP]);
int actionWin(char gameBoard[SQUARE_CAP][SQUARE_CAP], int *numberOfGames, int playerWins[2], char nickname[2][MAX_INPUT_CHAR]);
void printScores(int numberOfGames, int playerWins[2], char nickname[2][MAX_INPUT_CHAR]);

///////////////////////////////////////////////////////////////////
// Question 7 Function 
///////////////////////////////////////////////////////////////////

int main(void) {
  int gameType;
  char playerPiece1, playerPiece2;
  char nickname[2][MAX_INPUT_CHAR];
  char gameBoard[SQUARE_CAP][SQUARE_CAP];
  
  int numberOfGames = 0;
  int playerWins[2];
  int newGame = TRUE; // Boolean
  char replayGame[MAX_INPUT_CHAR];

  getGameDetails(&gameType, &playerPiece1, &playerPiece2, nickname);
  playerWins[0] = 0;
  playerWins[1] = 0;
  srand(time(NULL));

  // New Game
  for (;;) {
    clear_board(gameBoard);
    numberOfGames++;

    // New turn
    for (;;){
      if (gameType == 1){
        // Run player 1's move
        runUserMove(gameBoard, nickname[0], playerPiece1);
        if (actionWin(gameBoard,&numberOfGames,playerWins,nickname)) {
          break;
        }
        // Run Player 2's move
        runUserMove(gameBoard, nickname[1], playerPiece2);
        if (actionWin(gameBoard,&numberOfGames,playerWins,nickname)) {
          break;
        }
      } else if (gameType == 2) {
        // Run the user's move
        runUserMove(gameBoard, nickname[0], playerPiece1);
        if (actionWin(gameBoard,&numberOfGames,playerWins,nickname)) {
          break;
        }
        // Get the Computer's move
        computer_move(gameBoard);
        findAndReplaceTempMove(gameBoard, playerPiece2);
        display_board(gameBoard);
        if (actionWin(gameBoard,&numberOfGames,playerWins,nickname)) {
          break;
        }
      } else if (gameType == 0) {
        return 0;
      }
      
    } // end turn

    for (;;) {
      prompt_user("Would you like another game? (y/n) : ", replayGame);
      printf("%c\n", replayGame[0]);
      if (replayGame[0] == 'y') {
        newGame = TRUE;
        break;
      } else if (replayGame[0] == 'n') {
        gameType = 0;
        newGame = FALSE;
        break;
      } else {
        printf("Invalid input\n");
      }
    }
    if (!newGame) {
      break;
    }
  }// end game
}

void findAndReplaceTempMove(char gameBoard[SQUARE_CAP][SQUARE_CAP], char piece) {
  for (int i = 0; i < SQUARE_CAP; i++) {
    for (int j = 0; j < SQUARE_CAP;j++) {
      if (gameBoard[i][j] == 'T') {
        gameBoard[i][j] = piece;
      }
    }
  }
}

void runUserMove(char gameBoard[SQUARE_CAP][SQUARE_CAP], char *nickname, char piece) {
  printf("%s, ", nickname);
  user_move(gameBoard);
  findAndReplaceTempMove(gameBoard, piece);
  display_board(gameBoard);
}

int isFull(char gameBoard[SQUARE_CAP][SQUARE_CAP]) {
  for (int i = 0; i < SQUARE_CAP; i++) {
    for (int j = 0; j < SQUARE_CAP; j++) {
      if (gameBoard[i][j] == 'n') {
        return FALSE;
      }
    }
  }

  return TRUE;
}

int actionWin(char gameBoard[SQUARE_CAP][SQUARE_CAP], int *numberOfGames, int playerWins[2], char nickname[2][MAX_INPUT_CHAR]){
  int winner = detect_win(gameBoard);
  if (winner == 1){
    playerWins[0]++;
    printScores(*numberOfGames, playerWins, nickname);
  } else if (winner == 2) {
    playerWins[1]++;
    printScores(*numberOfGames, playerWins, nickname);
  }
  return winner == 1 || winner == 2;
}

void printScores(int numberOfGames, int playerWins[2], char nickname[2][MAX_INPUT_CHAR]) {
  printf("%s has won %d/%d games\n", nickname[0], playerWins[0], numberOfGames);
  printf("%s has won %d/%d games\n", nickname[1], playerWins[1], numberOfGames);
}

///////////////////////////////////////////////////////////////////
// Question 1 Functions
///////////////////////////////////////////////////////////////////

void prompt_user(char *message, char *answer) {
  // Print message and get user input
  printf("%s", message);
  scanf(" %s", answer);
}

void getGameDetails(int *gameType, char *playerPiece1, char *playerPiece2, char nickname[2][MAX_INPUT_CHAR]) {
  char menuInput[MAX_INPUT_CHAR];

  // Question 1 part i
  printf("\nMenu\n----\n1. Play Against A User\n");
  printf("2. Play against a Computer\n0. Exit\n");
  prompt_user("Enter a number : ", menuInput);
  switch (menuInput[0]) {
  case '1':
    // Question 1 part iii
    getNickname(1, nickname[0]);
    getNickname(2, nickname[1]);
    
    // Question 1 part ii
    getValidPiece(playerPiece1, playerPiece2, nickname);
    *gameType = 1;
    break;
  case '2':
    // User wishes to play against the computer
    getNickname(1, nickname[0]);
    strcpy(nickname[1], "computer");
    getValidPiece(playerPiece1, playerPiece2, nickname);
    *gameType = 2;
    break;
  case '0':
    *gameType = 0;
    return;
  default:
    printf("What you entered was invalid\n");
    getGameDetails(gameType, playerPiece1, playerPiece2, nickname);
  }
}

void getNickname(int player, char *nickname) {
  printf("For player %d, ", player);
  prompt_user("please enter a nickname : ", nickname);
}

void getValidPiece(char *playerPiece1, char *playerPiece2, char nickname[2][MAX_INPUT_CHAR]) {
  char tempString[MAX_INPUT_CHAR];
  printf("What would %s like to play as X or 0?\n", nickname[0]);
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
  printf("This means that %s is %c.\n", nickname[1], *playerPiece2);
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
  printf("\n\n\t");
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
  printf("\n\n");
}

///////////////////////////////////////////////////////////////////
// QUESTION 4 Function
///////////////////////////////////////////////////////////////////
void user_move(char gameBoard[SQUARE_CAP][SQUARE_CAP]) {
  // So what we are going to do is enter a temp character in where the user wants to go
  int row, column;
  // For valid location
  for (;;) {
    // For Row
    getRowOrColumn(&row, TRUE);

    // For column
    getRowOrColumn(&column, FALSE);
    
    // Do a search in the game board to see if that space is filled
    if (canPlacePiece(gameBoard, row, column)) {
      gameBoard[row][column] = 'T'; // T for temp
      return;
    } else {
      printf("That position appears to have something in it\n");
      printf("Please find a new location\n");
      display_board(gameBoard);
    }
  }
}

void getRowOrColumn(int *rowOrColumn, int isRow) {
  char tempString[MAX_INPUT_CHAR];
  
  for (;;) {
    printf("what %s would you like? (", (isRow?"row":"column"));
    for (int i = 0; i < SQUARE_CAP-1; i++) {
      printf("%d", i+1);
      if (i < SQUARE_CAP-2) {
        printf(", ");
      } else {
        printf(", and %d", (i+1)+1);
      }
    }
    prompt_user(") : ", tempString);
    switch (tempString[0]) {
    case '1': *rowOrColumn = 0; return;
    case '2': *rowOrColumn = 1; return;
    case '3': *rowOrColumn = 2; return;
    default:  *rowOrColumn = -1;
    }
    printf("What you entered is not valid\n");
  }
}

int canPlacePiece (char gameBoard[SQUARE_CAP][SQUARE_CAP],int row,int column) {
  return gameBoard[row][column] == 'n';
}

///////////////////////////////////////////////////////////////////
// QUESTION 5 Function
///////////////////////////////////////////////////////////////////

void computer_move(char gameBoard[SQUARE_CAP][SQUARE_CAP]) {
  int row, column;

  printf("Computer is making a move...\n");
  sleep(1); // think for half a second
  // attempt using random 3 times
  for (int i = 0; i < 3; i++) {
    row = rand() % SQUARE_CAP;
    column = rand() % SQUARE_CAP;
    if (canPlacePiece(gameBoard, row, column)) {
      gameBoard[row][column] = 'T'; // T for temporary
      return;
    }
  }
  printf("Got to here\n");
  // if we didn't get it in the three random guesses then enter manually
  for (row = SQUARE_CAP-1; row >= 0; row--) {
    for (int column = SQUARE_CAP-1; column >= 0; column--) {
      if (canPlacePiece(gameBoard,row,column)) {
        gameBoard[row][column] = 'T';
        return;
      }
    }
  }
  
}

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
  char testArray[SQUARE_CAP] = {'O','X','O'};
  char testChar = 'n';

  testChar = testSet(testArray);
  
  switch(testChar) {
  case 'X':
    return 1;
  case 'O':
    return 2;
  case 'n':
    return 0;
  }
}
