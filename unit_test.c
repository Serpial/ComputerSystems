#include <stdio.h>
#define SQUARE_CAP 3

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
    //    printf("%c %c %c\n", testArray[0], testArray[1], testArray[2]);
    testChar = testSet(testArray);
    //    printf("Test Char : %c\n", testChar);
    if (testChar != 'n') {
      break;
    }
  }


  // Vertical
  if (testChar == 'n') {
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

  // Diagonals
  if (testChar == 'n') {
    // top left to bottom right
    for (int i = 0; i < SQUARE_CAP; i++) {
      testArray[i] = gameBoard[i][i];
    }
    testChar = testSet(testArray);
  }
  if (testChar == 'n') {
    // top right to bottom left
    for (int i = SQUARE_CAP; i > 0; i--) {
      testArray[i] = gameBoard[i][SQUARE_CAP-i];
    }
    testChar = testSet(testArray);
  }

  switch(testChar) {
  case 'X':
    printf("here'X'\n");
    return 1;
  case 'O':
    printf("here'O'\n");
    return 2;
  case 'n':
    printf("here'n'\n");
    return 0;
  default:
    printf("here%c\n", testChar);
    return 0;
  }
}


int main(){
  char gameBoard[SQUARE_CAP][SQUARE_CAP] = {'n','X','n','O','n','n','n','n','n'};
  int something = detect_win(gameBoard);
  printf("Something : %d\n", something);

  for(int i = 0)
}

