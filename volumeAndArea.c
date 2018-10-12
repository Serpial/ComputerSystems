/*
 * Title       : Volume and Area
 * Author      : Paul Hutchison, 201741535
 * Description : This program covers questions 1 to 5
 *               This program takes the radius of a sphere from the user
 *               and, based on the user's input, outputs the volume,
 *               surface area, or both.
 */

/* Include directives */
#include <stdio.h>
#include <string.h>
/* Define directive */
#define PI_VALUE 3.141592654

/* Function Prototypes */
void menuOfFunctions(float radius);
float getRadiusFromUser ();
float toPow (float valueToSquare, int power);
float getVolume (float radius);
float getSurfaceArea (float radius);

/* Definition of main */
int main (void) {
  float  radius;

  radius = getRadiusFromUser();
  menuOfFunctions(radius);

  return 0;
}

/* menuOfFunctions
 * this is the menu that the user will receive 
 * when they enter a radius 
 */
void menuOfFunctions(float radius) {
  char userInput[2];

  /* Menu items */
  printf("Menu\n----\ns : Surface Area\nv : Volume\nb : Both\n");
  printf("Please enter an initial : ");

  /* Get user input stictly as one character */
  scanf(" %c", &userInput[0]);
  userInput[1] = '\0';
  printf("%s taken as input\n", userInput);

  /* 
   * Prints the relevant value based on the user input 
   * Also error checks to see if the user has entered an
   * invalid value
   */
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
}


/* getVolume
 * returns the calculation associated with calculating
 * the volume of a sphere
 */
float getVolume (float radius) {
  return 1.3333333333f * PI_VALUE * toPow(radius, 3);
}


/* getSurfaceArea
 * returns the calculation associated with calculating
 * the surface area of a sphere
 */
float getSurfaceArea (float radius) {
  return PI_VALUE * toPow(radius, 2);
}


/* getRadiusFromUser
 * This gives a prompt for an returns the radius that the 
 * user wants to work with. It uses an infinite for loop
 * to keep on asking until the user has entered a valid
 * input
 */
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


/* toPow
 * This is a simple function that calculate one 
 * value to the power of another
 */
float toPow (float valueToSquare, int power) {
  int i; /* index */
  
  for (i = 0; i < power; i++) {
    valueToSquare += valueToSquare;
  }
  return valueToSquare;
}
