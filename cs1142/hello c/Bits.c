/**
 * Name        : Evan Overweg
 * Username    : ejoverwe
 * Description : A program that calculates the number of bits a given number takes up.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  //make sure a number is given in the command line
  if(argc < 2)
    {
      printf("Bits <integer N>\n");
      return 0;
    }

  //store the number as a variable and check that it is not negative
  int N = atoi(argv[1]);
  if(N < 0)
    {
      printf("Illegal input\n");
      return 0;
    }
  
  //count the number of bits
  int count = 0;
  while(N >= 1)
    {
      N /= 2;
      count++;
    }
  printf("%d\n", count);
  return 0;
}
