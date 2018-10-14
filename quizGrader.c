/*
 * Title       : Quiz Statistics
 * Author      : Paul Hutchison, 201741535
 * Description : This program covers questions 7
 *
 *               This program takes in the scores of 5 quizes
 *               form 10 students. It then produces statistics
 *               on the students individual score and their
 *               collective scores.
 */

/* Include/define directives */
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
void printStatistics (struct Student students [NUMBER_STUDENTS]);
float getTotalScoresForAQuiz (struct Student student [NUMBER_STUDENTS], int quizNum);

/* Definition of main */
int main(void) {
  int i, j; /* Index */
  /* structure holding the students individual data */
  struct Student students [NUMBER_STUDENTS];

  /* Get the scores from the user and calculate relevant statistics*/
  for (i = 0; i < NUMBER_STUDENTS; i++) {
    scanForQuizScores(&students[i], i);

    students[i].totalScore = 0;
    for (j = 0; j < NUMBER_QUIZ; j++) {
      students[i].totalScore += students[i].quizScores[j];
    }
    students[i].avgScore = students[i].totalScore/NUMBER_QUIZ;
  }

  
  /* Then print the value */
  printStatistics(students);
 
 return 0;
}


/* printStatistics
 * This function prints of all of the data collected
 */
void printStatistics (struct Student students[NUMBER_STUDENTS]) {
  int listOfScoresForTest[NUMBER_STUDENTS];
  int i, j;
  
  printf("\n\n\nStudent\tTotal Score\tAverage\n"); /* Heading */
  printf("---------------------------------\n");

  /* Print each of the students total score and average */
  for (i = 0; i < NUMBER_STUDENTS; i++) {
    printf("%d\t%d\t\t%.2d\n", i+1, students[i].totalScore, students[i].totalScore/NUMBER_QUIZ);
  }
  printf("---------------------------------\n");


  printf("For each quiz:\n");
  printf("Quiz\tAverage Score\tHigh Score\tLow Score\n"); /* Heading */
  printf("---------------------------------\n");
    /* Print all of the data for each of the test */
  for (i = 0; i < NUMBER_QUIZ; i++) {
    for (j = 0; j < NUMBER_STUDENTS; j++) {
      listOfScoresForTest[j] = students[j].quizScores[i]; 
    }
    printf("%d\t%.2f\t\t", i+1, getTotalScoresForAQuiz(students, i)/NUMBER_STUDENTS);
    printf("%d\t\t", findHigh(listOfScoresForTest));
    printf("%d\n", findLow(listOfScoresForTest));
  }
  printf("---------------------------------\n");    
}


/* scanForQuizScores
 * this function runs through all of the students asking for
 * their scores for each of the quizes within 0 and 100
 */
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


/* findHigh
 * finds the highest value out of a given 
 * list of test scores
 */
int findHigh(int quizScores[NUMBER_STUDENTS]) {
  int i, highestScore = quizScores[0];
  for (i = 1; i < NUMBER_STUDENTS; i++) {
    if (quizScores[i] > highestScore) {
      highestScore = quizScores[i];
    }
  }
  return highestScore;
}


/* findLow
 * finds the lowest value out of a given 
 * list of test scores
 */
int findLow(int quizScores[NUMBER_QUIZ]) {
  int i, lowestScore = quizScores[0];
  for (i = 0; i < NUMBER_QUIZ; i++) {
    if (quizScores[i] < lowestScore) {
      lowestScore = quizScores[i];
    }
  }
  return lowestScore;
}

/* getTotalScoresForAQuiz
 * returns the total for one particular quiz
 */
float getTotalScoresForAQuiz (struct Student student [NUMBER_STUDENTS], int quizNum) {
  int i; /* Index */
  float total = 0;
  
  for (i = 0; i < NUMBER_STUDENTS; i++){
    total += student[i].quizScores[quizNum];
  }
  return total;
}
