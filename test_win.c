;; This buffer is for text that is not saved, and for Lisp evaluation.
;; To create a file, visit it with C-x C-f and enter text in its buffer.

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
