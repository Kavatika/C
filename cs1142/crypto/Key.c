/**
 * Name        : Evan Overweg
 * Username    : ejoverwe
 * Description : Contains function implementations for Key.h
 */

#include "Key.h"
#include "Stats.h" 
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//Reads the given file and builds the encryption data from it.
//Passed a pointer to a int to store the size of the encryption string in and the filename to read data from.
//Returns the encryption data, or NULL if an error occurred.  
char *readData(int* size, const char* filename)
{
  FILE* file = fopen(filename, "rb");
  if(file == NULL)
    {
      printf("Failed to load key file: %s\n", filename);
      return NULL;
    }
  char *data = malloc(sizeof(char));
  if(data == NULL)
    {
      printf("Memory allocation error: creating encryption data\n");
      fclose(file);
      file = NULL;
      return NULL;
    }
  *size = 0;
  int ch = '\0';
  while((ch = fgetc(file)) != EOF)
    {
      (*size)++;
      data = realloc(data, *size + 1);
      if(data == NULL)
	{
	  printf("Memory allocation error: resizing encryption data\n");
	  fclose(file);
	  file = NULL;
	  return NULL;
	}
      data[*size - 1] = (unsigned char) ch;
      data[*size] = '\0';
    }
  fclose(file);
  file = NULL;
  if(*size == 0)
    {
      printf("Failed to load key file: %s\n", filename);
      free(data);
      data = NULL;
      return NULL;
    }
  return data;
}

//Initializes a key structure.
//Passed a filename to get an encryption string from. 
//Returns a pointer to the newly initalized key, or NULL if an error occurred.
Key *initKey(const char* filename)
{
  int size;
  char* data = readData(&size, filename);
  if(data != NULL)
    {
      Key* key = malloc(sizeof(Key));
      if(key == NULL)
	{
	  printf("Memory allocation error: creating key\n");
	  free(data);
	  data = NULL;
	  return NULL;
	}
      key->data = data;
      key->size = size;
      key->pos = 0;
      return key;
    }
  else return NULL;
}

//Frees any memory used by the given key.
//Passed a pointer to a key. 
void freeKey(Key* key)
{
  free(key->data);
  key->data = NULL;
  free(key);
  key = NULL;
}

//Sets the given character to '~' if it is unprintable.
//Passed a pointer to a character.
void makePrintable(char* ch)
{
  *ch = (*ch >= 32 && *ch <= 126) ? *ch : '~';
}

//Prints the encryption process for debug mode. 
//Passed a source character, encryption character, and the resulting character.
void printDebug(char ch, char encrypt, char result)
{
  unsigned char a1 = ch, a2 = encrypt, a3 = result;
  makePrintable(&ch);
  makePrintable(&encrypt);
  makePrintable(&result);
  printf("%3u '%c' ^ %3u '%c' -> %3u '%c'\n", a1, ch, a2, encrypt, a3, result);
}

//Encrypts the given character using bitwise XOR and updates stats, prints debug info if desired.
//Passed a pointer to a key structure, stats structre, character to encrypt, and bool that enables/disables debug mode.
//Returns the character resulting from encryption. 
char applyKey(Key* key, Stats* stats, char ch, bool debug)
{
  char *data = key->data;
  char encrypt = data[key->pos];
  char result = ch ^ (data[key->pos]);
  if(debug) printDebug(ch, encrypt, result);
  key->pos = (key->pos + 1) % key->size;
  updateStats(stats, result);
  return result;
}
