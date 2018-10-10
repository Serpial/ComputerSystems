#include <stdio.h>
#define NUMBER_STUDENTS 10
#define NUMBER_QUIZ 5

/*
  Structure to hold the information for an individual
  student
 */
struct Student {
  int quizScores[NUMBER_QUIZ];
  int totalScore, highScore, lowScore;
  float avgScore;
};

/* Function Prototypes */
int findHigh(int quizScores[NUMBER_QUIZ]);
int findLow(int quizScores[NUMBER_QUIZ]);
void getQuizScores(struct Student *indivStudent, int studentNum);

int main(void) {
  int i, j; /* Index */
  struct Student students [NUMBER_STUDENTS];
  float quizAvg[NUMBER_QUIZ];
  int quizHigh[NUMBER_QUIZ], quizLow[NUMBER_QUIZ], quizTotals[NUMBER_QUIZ];

  /* Initialize quiz totals used to calculate average*/
  for (i = 0; i < NUMBER_QUIZ; i++) {
    quizTotals = 0;
  }

  for (i = 0; i < NUMBER_STUDENTS; i++) {
    students[i].totalScore = 0;
    getQuizScores(&students[i], i);
    for (j = 0; j < NUMBER_QUIZ; j++) {
      students[i].totalScore += students[i].quizScores[j];
      quizTotals[j] += students[i].quizScores[j];
    }

    /* Individual Totals */
    students[i].highScore = findHigh(students[i].quizScores);
    students[i].lowScore = findLow(students[i].quizScores);
    students[i].avgScore = students[i].totalScore/NUMBER_QUIZ;
  }

  /* Quiz Totals */
  for (i = 0; i < NUMBER_QUIZ; i++) {
    
    quizAvg[i] += ;
  }

  
}


/* For each student get their quiz scores
   and add it to the total*/
void getQuizScores(struct Student *indivStudent, int studentNum) {
  int i;
  for (i = 0; i < NUMBER_QUIZ; i++) {
    printf("For student: %d, enter score for quiz %d : ", studentNum+1, i+1);
    scanf("%d", &indivStudent->quizScores[i]);
    if (indivStudent->quizScores[i] < 0) {
      printf("A student can't get a negative score\n");
      i--;
      continue;
    } else if (indivStudent->quizScores[i] > 100) {
      printf("A student can't get a score greater than 100\n");
      i--;
      continue;
    }
  }
}

int findHigh(int quizScores[NUMBER_QUIZ]) {
  int i, highestScore = quizScores[0];
  for (i = 1; i < NUMBER_QUIZ; i++) {
    if (quizScores[i] > highestScore) {
      highestScore = quizScores[i];
    }
  }
  return highestScore;
}

int findLow(int quizScores[NUMBER_QUIZ]) {
  int i, lowestScore = quizScores[0];
  for (i = 0; i < NUMBER_QUIZ; i++) {
    if (quizScores[i] > lowestScore) {
      lowestScore = quizScores[i];
    }
  }
  return lowestScore;
}
