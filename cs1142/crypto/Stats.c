/**
 * Name        : Evan Overweg
 * Username    : ejoverwe
 * Description : Contains function implementations for Key.h
 */

#include "Stats.h"
#include <stdlib.h>
#include <stdio.h>

//Initalizes a stats structure. 
//Returns a pointer to the newly initalized stats structre, or NULL if an error occurred. 
Stats *initStats()
{
  Stats *stats = malloc(sizeof(Stats));
  if(stats == NULL)
    {
      printf("Memory allocation error: creating stats structure\n");
      return NULL;
    }
  stats->letters = 0;
  stats->spaces = 0;
  stats->numbers = 0;
  stats->other = 0;
  return stats;
}

//Determines the type of character that is given to it. 
//Passed a character to analyze. 
//Returns a type corresponding to the given character. 
Types getCharType(char ch)
{
  Types type;
  if(ch == ' ')
    type = SPACE;
  else if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    type = LETTER;
  else if(ch >= '0' && ch <= '9')
    type = NUMBER;
  else
    type = OTHER;
  return type;
}

//Updates stats based on the given character. 
//Passed a pointer to a stats structure and the newly added character. 
void updateStats(Stats* stats, char ch)
{
  switch(getCharType(ch))
    {
    case SPACE:
      stats->spaces++;
      return;
    case LETTER:
      stats->letters++;
      return;
    case NUMBER:
      stats->numbers++;
      return;
    case OTHER:
      stats->other++;
      return;
    }    
} 

//Calculates a percentage. 
//Passed an partial and total value. 
//Returns the percentage as a double. 
double percentage(int partial, int total)
{
  return (partial / (double) total) * 100;
}

//Prints the stats.
//Passed a pointer to a stats structure. 
void printStats(Stats* stats)
{
  int total = stats->letters + stats->spaces + stats->numbers + stats->other;
  printf("Output %d characters: %.2f%% letters, %.2f%% spaces, %.2f%% numbers, %.2f%% other\n", total, percentage(stats->letters, total), percentage(stats->spaces, total), percentage(stats->numbers, total), percentage(stats->other, total));
}
