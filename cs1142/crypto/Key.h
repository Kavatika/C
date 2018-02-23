/**
 * Name        : Evan Overweg
 * Username    : ejoverwe
 * Description : Header file for Key.c. Conatins the type definition for the key structure 
 * and function declarations for Key.c
 */
#ifndef KEY_H
#define KEY_H

#include <stdbool.h>
#include "Stats.h"

typedef struct
{
  char* data; //Stores actual data for this key
  int size; //How many bytes of memory this key can store
  int pos; //Current character to use next for encoding/decoding
} Key;

char *readData(int* size, const char* filename); //Load from the given filename, returns null if loading of key failed
Key *initKey(const char* filename); //Initialize and load from the given filename, returns null if loading of key failed
void freeKey(Key* key); //Deallocate any memory used by the key
void makePrintable(char* ch); //If the given character is unprintable (outside [32, 126]), sets the character equal to '~'
void printDebug(char ch, char encrypt, char result); //Prints debug info for the current encryption step. 
char applyKey(Key* key, Stats* stats, char ch, bool debug); //Process ch using the current posisiton in the key, advance key, update stats, optionally
//print debug line, returns output character

#endif
