#include <stdio.h>
#define NUMBER_STUDENTS 10
#define NUMBER_QUIZ 5

 void getQuizScores ();
int totalScoreInd (int studentScore[NUMBER_QUIZ]);

int main(void) {
  int i, j; /* Used for indexing */
  int quizes[NUMBER_STUDENTS][NUMBER_QUIZ];

  
  printf("Student\tTotal Score\tAverage\n");
  for (i = 0; i < NUMBER_STUDENTS; i++) {
    printf("%d\t%d\t%.2f\n", i+1, totalScoreInd(quizes[i]), totalScoreInd(quizes[i])/NUMBER_QUIZ);
  }
  printf("---------------------------------\n");


}

int totalScoreInd (int studentScore[NUMBER_QUIZ]){
  int i, total = 0;
  for (i = 0; i < NUMBER_QUIZ;i++) {
    total += studentScore[i];
  }
  return total;
}

void getQuizScores () {
  
}
