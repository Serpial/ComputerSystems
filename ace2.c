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

// Include directives
#include <stdio.h>
#include <ctype.h> // To capitalise a character
#include <string.h>
#include <unistd.h> // Used for sleeping the program to emulate the computer thinking
// Used in getting random int
#include <time.h>
#include <stdlib.h>

// Define directives
#define MAX_INPUT_CHAR 50 // The maximum number of characters a nickname can be
#define SQUARE_CAP 3 // The number of elements in a row or column in tic-tac-toe
#define TRUE 1
#define FALSE 0

/*     Function Prototypes     */
/*-----------------------------*/
//     Question 1 Functions
void prompt_user(char *message, char *answer);
void getValidPiece(char *playerPiece1, char *playerPiece2, char nickname[2][MAX_INPUT_CHAR]);
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
int actionWin(char gameBoard[SQUARE_CAP][SQUARE_CAP], int *numberOfGames, int playerWins[2], char nickname[2][MAX_INPUT_CHAR], char *playerPiece1);
void printScores(int numberOfGames, int playerWins[2], char nickname[2][MAX_INPUT_CHAR]);

///////////////////////////////////////////////////////////////////
// Question 7 Function 
///////////////////////////////////////////////////////////////////

int main(void) {
  // These variables will be run throughout various functions of the program
  int gameType;
  char playerPiece1, playerPiece2;
  char nickname[2][MAX_INPUT_CHAR];
  char gameBoard[SQUARE_CAP][SQUARE_CAP];

  // These are local variables used exclusively for producing the game
  int numberOfGames = 0;
  int playerWins[2];
  int newGame = TRUE; // Boolean
  char replayGame[MAX_INPUT_CHAR];

  // Things needing done before the game begins
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
        if (actionWin(gameBoard,&numberOfGames,playerWins,nickname,&playerPiece1)) {
          break;
        } else if (isFull(gameBoard)) {
          printf("The game is a draw\n");
          printScores(numberOfGames,playerWins,nickname);
          break;
        }
        // Run Player 2's move
        runUserMove(gameBoard, nickname[1], playerPiece2);
        if (actionWin(gameBoard,&numberOfGames,playerWins,nickname,&playerPiece1)) {
          break;
        }
      } else if (gameType == 2) {
        // Run the user's move
        runUserMove(gameBoard, nickname[0], playerPiece1);
        if (actionWin(gameBoard,&numberOfGames,playerWins,nickname,&playerPiece1)) {
          break;
        }else if (isFull(gameBoard)) {
          printf("The game is a draw\n");
          printScores(numberOfGames,playerWins,nickname);
          break;
        }
        // Get the Computer's move
        computer_move(gameBoard);
        findAndReplaceTempMove(gameBoard, playerPiece2);
        display_board(gameBoard);
        if (actionWin(gameBoard,&numberOfGames,playerWins,nickname,&playerPiece1)) {
          break;
        }
      } else if (gameType == 0) {
        return 0;
      }
      
    } // end turn

    for (;;) {
      prompt_user("Would you like another game? (y/n) : ", replayGame);
      if (toupper(replayGame[0]) == 'Y') {
        newGame = TRUE;
        break;
      } else if (toupper(replayGame[0]) == 'N') {
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

/* findAndReplaceTempMove
 * Turns a temporary move into the user's player piece (X or O)
 */
void findAndReplaceTempMove(char gameBoard[SQUARE_CAP][SQUARE_CAP], char piece) {
  for (int i = 0; i < SQUARE_CAP; i++) {
    for (int j = 0; j < SQUARE_CAP;j++) {
      if (gameBoard[i][j] == 'T') {
        gameBoard[i][j] = piece;
      }
    }
  }
}

/* runUserMove
 * runs the basic set of function used by the user each turn
 */
void runUserMove(char gameBoard[SQUARE_CAP][SQUARE_CAP], char *nickname, char piece) {
  printf("%s, ", nickname);
  user_move(gameBoard);
  findAndReplaceTempMove(gameBoard, piece);
  display_board(gameBoard);
}

/* isFull
 * checks if the gameboard is full and returns a boolean value
 * of true if we do find that there are no empty elements
 * Returns : boolean isFull
 */
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

/* actionWin
 * this function adjusts the variables holding the win counter for
 * each player. it does this by checking if there is a win and does
 * actions based on this
 */
int actionWin(char gameBoard[SQUARE_CAP][SQUARE_CAP], int *numberOfGames, int playerWins[2], char nickname[2][MAX_INPUT_CHAR], char *playerPiece1){
  int winnerPiece = detect_win(gameBoard);
  int playerPiece1Int;

  playerPiece1Int = (*playerPiece1 == 'X'? 1 : 2);

  if (winnerPiece == playerPiece1Int){
    playerWins[0]++;
    printScores(*numberOfGames, playerWins, nickname);
  } else if (winnerPiece != 0) {
    playerWins[1]++;
    printScores(*numberOfGames, playerWins, nickname);
  }
  return winnerPiece == 1 || winnerPiece == 2;
}

/* printScores
 * Prints the scores of each player out of number of games
 */
void printScores(int numberOfGames, int playerWins[2], char nickname[2][MAX_INPUT_CHAR]) {
  printf("%s has won %d/%d games\n", nickname[0], playerWins[0], numberOfGames);
  printf("%s has won %d/%d games\n", nickname[1], playerWins[1], numberOfGames);
}

///////////////////////////////////////////////////////////////////
// Question 1 Functions
///////////////////////////////////////////////////////////////////

/* prompt_user
 * prompts the user for a string answer given an question
 */
void prompt_user(char *message, char *answer) {
  // Print message and get user input
  printf("%s", message);
  scanf(" %s", answer);
}

/* getGameDetails
 * gets the data from the user neccessary to play the game.
 * This includes their nickname, the piece they wish to play as
 * and whether or the game is PvP or PvE
 */
void getGameDetails(int *gameType, char *playerPiece1, char *playerPiece2, char nickname[2][MAX_INPUT_CHAR]) {
  char menuInput[MAX_INPUT_CHAR];

  // Question 1 part i
  printf("\nMenu\n----\n1. Play Against A User\n");
  printf("2. Play against a Computer\n0. Exit\n");
  prompt_user("Enter a number : ", menuInput);
  switch (menuInput[0]) {
  case '1':
    // Question 1 part iii
    printf("For player 1, ");
    prompt_user("please enter a nickname : ", nickname[0]);
    printf("For player 2, ");
    prompt_user("please enter a nickname : ", nickname[1]);
    
    // Question 1 part ii
    getValidPiece(playerPiece1, playerPiece2, nickname);
    *gameType = 1;
    break;
  case '2':
    // User wishes to play against the computer
    printf("For player 1, ");
    prompt_user("please enter a nickname : ", nickname[0]);
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

/* getValidPiece
 * get the piece that the user wishes to play as an set it.
 * the user can either play as X or O
 */
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

/* clear_board
 * clear the board of all of the value and replace them with my
 * null value 'n'
 */
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

/* display_board
 * simply displays the current state of the board for the user to
 * see
 */
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

/* user_move
 * attempts to get a user move until there is a valid user move.
 * Takes in put then checks to see if there is a space in the
 * designated spot to place the user input in the gameboard.
 */
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

/* getRowOrColumn
 * using a boolean input to decide whether or not we are
 * looking for a row or column for input then get the inpit
 * change the value and return
 */
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

/* canPlacePiece
 * checks if the user can place a piece in a given location
 */
int canPlacePiece (char gameBoard[SQUARE_CAP][SQUARE_CAP],int row,int column) {
  return gameBoard[row][column] == 'n';
}

///////////////////////////////////////////////////////////////////
// QUESTION 5 Function
///////////////////////////////////////////////////////////////////

/* computer_move
 * This executes the computers move. It tries to be random 3 times.
 * If there is something in the location all three times then the
 * computer will work its way backwards to check if there is something
 * in there eventually finding the empty space to put a value.
 */
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

/* testSet
 * This faction takes a set of 3 items and tests if they are all the same
 * It then returns the char that they are all set to
 */
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

/* detect_win
 * Tests the horizontals, verticals and diagonals for a win
 * returns that X won, Y won, or there is no winner yet
 */
int detect_win(char gameBoard[SQUARE_CAP][SQUARE_CAP]) {
  char testArray[SQUARE_CAP];
  char testChar = 'n';

  // Horizontal
  for (int i = 0; i < SQUARE_CAP; i++) {
    for (int j = 0; j < SQUARE_CAP; j++) {
      testArray[j] = gameBoard[i][j];
    }
    testChar = testSet(testArray);
    if (testChar != 'n') {break;}
  }

  // Vertical
  if (testChar == 'n') {
    for (int i = 0; i < SQUARE_CAP; i++) {
      for (int j = 0; j < SQUARE_CAP; j++) {
        testArray[j] = gameBoard[j][i];
      }
      testChar = testSet(testArray);
      if (testChar != 'n') {break;}
    }
  }

  // Diagonal
  if (testChar == 'n') {
    for (int i = 0; i < SQUARE_CAP; i++) {
      testArray[i] = gameBoard[i][i];
    }
    testChar = testSet(testArray);
  }
  if (testChar == 'n') {
    for (int i = 0; i < SQUARE_CAP; i++) {
      testArray[i] = gameBoard[i][SQUARE_CAP-i-1];
    }
    testChar = testSet(testArray);
  }

  switch(testChar) {
  case 'X':
    return 1;
  case 'O':
    return 2;
  case 'n':
    return 0;
  }
}
