/**
 * Name        : Evan Overweg
 * Username    : ejoverwe
 * Description : Header file for Stats.c Contains type definition for the Stats structure and Types enum, 
 * as well as function declarations. 
 */

#ifndef STATS_H
#define STATS_H

#include <stdbool.h>

typedef struct
{
  int letters; //count of letter characters in output file
  int spaces; //count of space characters in output file
  int numbers; //count of number characters in output file
  int other; //count of any other characters not a letter, space, or number
} Stats;

typedef enum {LETTER, SPACE, NUMBER, OTHER} Types;

Stats *initStats(); //Initialize a stats data structure
Types getCharType(char ch); //Returns the type associated with the character passed to it
void updateStats(Stats* stats, char ch); //Update stats based on ch output character
double percentage(int partial, int total);
void printStats(Stats* stats); //print out statistics about the characters processed

#endif
