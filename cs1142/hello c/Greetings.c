/**
 * Name        : Evan Overweg
 * Username    : ejoverwe
 * Description : Greets the three given people using the given greeting.
 */

#include <stdio.h>

int main(int argc, char** argv)
{
  //Check to make sure the appropriate number 
  //of command line arguments were received
  if(argc < 5)
    {
      printf("Greetings <greeting> <name1> <name2> <name3>\n");
      return 0;
    }

  //assign each argument to variables and print them out
  char* greeting = argv[1];
  char* name1 = argv[2];
  char* name2 = argv[3];
  char* name3 = argv[4];
 
  printf("%s %s!\n", greeting, name1);
  printf("%s %s!\n", greeting, name2);
  printf("%s %s!\n", greeting, name3);
  return 0;
}
