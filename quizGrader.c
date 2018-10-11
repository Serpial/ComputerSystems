#include <stdio.h>
#define NUMBER_STUDENTS 10
#define NUMBER_QUIZ 5

/*
  Structure to hold the information for an individual
  student
 */
struct Student {
  int quizScores[NUMBER_QUIZ];
  int totalScore;
  float avgScore;
};

/* Function Prototypes */
int findHigh(int quizScores[NUMBER_QUIZ]);
int findLow(int quizScores[NUMBER_QUIZ]);
void scanForQuizScores(struct Student *student, int studentIndex);
void printStatistics (struct Student students [NUMBER_STUDENTS], float quizAvg[NUMBER_QUIZ]);


int main(void) {
  int i, j; /* Index */
  struct Student students [NUMBER_STUDENTS];
  float quizAvg[NUMBER_QUIZ];
  int quizTotals[NUMBER_STUDENTS];
  
  
  /* Initialize quiz totals used to calculate average*/
  for (i = 0; i < NUMBER_QUIZ; i++) {
    quizTotals[i] = 0;
  }

  /* Get the scores from the user and calculate relevant statistics*/
  for (i = 0; i < NUMBER_STUDENTS; i++) {
    scanForQuizScores(&students[i], i);

    students[i].totalScore = 0;
    for (j = 0; j < NUMBER_QUIZ; j++) {
      students[i].totalScore += students[i].quizScores[j];
      quizTotals[j] += students[i].quizScores[j];
    }
    students[i].avgScore = students[i].totalScore/NUMBER_QUIZ;
    quizAvg[i] = quizTotals[i]/NUMBER_STUDENTS;
  }
  
  /* Then print the value */
 printStatistics(students, quizAvg);


  return 0;
}

void printStatistics (struct Student students[NUMBER_STUDENTS], float quizAvg[NUMBER_QUIZ]) {
  int listOfScoresForTest[NUMBER_STUDENTS];
  int i, j;

  printf("\n\n\nStudent\tTotal Score\tAverage\n");
  printf("---------------------------------\n");
  for (i = 0; i < NUMBER_STUDENTS; i++) {
    printf("%d\t%d\t\t%.2d\n", i+1, students[i].totalScore, students[i].totalScore/NUMBER_QUIZ);
  }
  printf("---------------------------------\n");
  printf("For each quiz:\n");
  printf("Quiz\tAverage Score\tHigh Score\tLow Score\n");
  printf("---------------------------------\n");  
  for (i = 0; i < NUMBER_QUIZ; i++) {
    for (j = 0; j < NUMBER_STUDENTS; j++) {
      listOfScoresForTest[j] = students[j].quizScores[i]; 
    }
    printf("%d\t%.2f\t\t", i+1, quizAvg[i]);
    printf("%d\t\t", findHigh(listOfScoresForTest));
    printf("%d\n", findLow(listOfScoresForTest));
  }
  printf("---------------------------------\n");    
}



void scanForQuizScores(struct Student *student, int studentIndex) {
  int i;
  for(i = 0; i < NUMBER_QUIZ; i++) {
    printf("Please enter Student %d's score for quiz %d : ", studentIndex+1, i+1);
    scanf(" %d", &student->quizScores[i]);
    if (student->quizScores[i] > 100 || student->quizScores[i] < 0) {
      printf("Please enter another value(less than 100 and greater than 0\n");
      i--;
      continue;
    }
  }
}

int findHigh(int quizScores[NUMBER_STUDENTS]) {
  int i, highestScore = quizScores[0];
  for (i = 1; i < NUMBER_QUIZ; i++) {
    if (quizScores[i] > highestScore) {
      highestScore = quizScores[i];
    }
  }
  return highestScore;
}

int findLow(int quizScores[NUMBER_STUDENTS]) {
  int i, lowestScore = quizScores[0];
  for (i = 0; i < NUMBER_QUIZ; i++) {
    if (quizScores[i] < lowestScore) {
      lowestScore = quizScores[i];
    }
  }
  return lowestScore;
}
