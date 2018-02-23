/**
 * Name        : Evan Overweg
 * Username    : ejoverwe
 * Description : Takes the centerpoints and radii of two circles and determines
 *               if they overlap. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv)
{
  //Ensure proper number of command line arguments
  if(argc < 7)
    {
      printf("TwoCircles <x1> <y1> <r1> <x2> <y2> <r2>\n");
      return 0;
    }
  //store each command line argument as a variable
  double x1 = atof(argv[1]);
  double y1 = atof(argv[2]);
  double r1 = atof(argv[3]);
  
  double x2 = atof(argv[4]);
  double y2 = atof(argv[5]);
  double r2 = atof(argv[6]);

  //calculate the distance and sum of the two radii
  double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
  double radiisum = r1 + r2;

  //print the information for each circle first
  printf("Circle 1: (%.2f, %.2f) r = %.2f\n", x1, y1, r1);
  printf("Circle 2: (%.2f, %.2f) r = %.2f\n", x2, y2, r2);
  printf("Distance between centers = %.4f\n", distance);
  
  //then print whether or not the two circles overlap
  if(distance < radiisum)
    {
      printf("%.4f < %.4f, circles intersect\n", distance, radiisum);
    }
  else
    {
      printf("%.4f >= %.4f, circles do not intersect\n", distance, radiisum);
    }

  return 0;
}
