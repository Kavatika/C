/**
 * Name        : Evan Overweg
 * Username    : ejoverwe
 * Description : The main file for the Crypto program. 
 */

#include "Key.h"
#include "Stats.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Encrypts the source file into the target file using the given key. 
//Passed a pointer to an input file, output file, key struct, stats struct, and a switch for debug mode
//Output file will be filled with encrypted text
void encrypt(FILE* input, FILE* output, Key* key, Stats* stats, bool debug)
{
  int byte;
  while((byte = fgetc(input)) != EOF)
    {
     char ch = applyKey(key, stats, (unsigned char) byte, debug);
     fprintf(output, "%c", ch);
    }
}

int main(int argc, char** argv)
{
  if(argc < 4)
    {
      printf("Crypto <input file> <output file> <key file> [debug]\n");
      return 0;
    }
  bool debug = false;
  if(argc == 5)
    {
      if(atoi(argv[4]))
	debug = true;
    }
  FILE *input = fopen(argv[1], "rb");
  if(input == NULL)
    {
      printf("Failed to open input file: %s\n", argv[1]);
      return 0;
    }
  FILE *output = fopen(argv[2], "wb");
  if(output == NULL)
    {
      printf("Failed to open output file: %s\n", argv[2]);
      fclose(input);
      input = NULL;
      return 0;
    }
  Key *key = initKey(argv[3]);
  if(key == NULL)
    {
      fclose(input);
      fclose(output);
      input = NULL;
      input = NULL;
      return 0;
    }
  Stats *stats = initStats();
  if(stats == NULL)
    {
      fclose(input);
      fclose(output);
      freeKey(key);
      input = NULL;
      output = NULL;
      return 0;
    }
  //if code reaches this point, all necessary files/structures have been created and loaded successfully
  
  //steps for encryption go here
  encrypt(input, output, key, stats, debug);
  printStats(stats);

  //close all files & free any used memory
  fclose(input);
  fclose(output);
  freeKey(key);
  free(stats);
  input = NULL;
  output = NULL;
  stats = NULL;
  return 1;
}
