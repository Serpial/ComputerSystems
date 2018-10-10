/* -std=c89 */
#include <stdio.h>
#include <string.h>
#define PI_VALUE 3.141592654

/* Function Prototypes */
void menuOfFunctions(float radius);
float getRadiusFromUser ();
float toPow (float valueToSquare, int power);
float getVolume (float radius);
float getSurfaceArea (float radius);

int main (void) {
  float  radius;

  radius = getRadiusFromUser();
  menuOfFunctions(radius);

  return 0;
}

void menuOfFunctions(float radius) {
  char userInput[2];
  
  printf("Menu\n----\ns : Surface Area\nv : Volume\nb : Both\n");
  printf("Please enter an initial : ");

  scanf(" %c", &userInput[0]);
  userInput[1] = '\0';
  printf("%s taken as input\n", userInput);

  if (strcmp(userInput,"s") == 0) {
    printf("The surface area of your sphere is %.2f\n",getSurfaceArea(radius));
  } else if (strcmp(userInput, "v") == 0) {
    printf("The volume of your sphere is %.2f\n",getVolume(radius));
  } else if (strcmp(userInput, "b") == 0) {
    printf("For your sphere:\nthe area is %.2f\nthe volume is %.2f\n",
           getSurfaceArea(radius), getVolume(radius));
  } else {
    printf("Character you have entered is not on the menu\n");
  }

  /* menuOfFunctions(radius); */
}

float getVolume (float radius) {
  return 1.3333333333f * PI_VALUE * toPow(radius, 3);
}


float getSurfaceArea (float radius) {
  return PI_VALUE * toPow(radius, 2);
}

float getRadiusFromUser () {
  float radius;
  printf("What is the radius of your circle : ");
  for(;;) {
    scanf("%f", &radius);
    if (radius <= 0) {
      printf("You can't get a negative circle\n");
      printf("Please try again : ");
      continue;
    } else {
      break;
    }
  }
  return radius;
}

float toPow (float valueToSquare, int power) {
  int i;
  for (i = 0; i < power; i++) {
    valueToSquare += valueToSquare;
  }
  return valueToSquare;
}
