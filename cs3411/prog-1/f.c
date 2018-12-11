#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define  F_first        1   /* This is the first call to the function. */
#define  F_last         2   /* This is the last call to the function. Free the memory area. */
#define  F_data_int     3   /* Void * argument points to integer data. */
#define  F_data_char    4   /* Void * argument points to character string. */
#define  F_data_float   5   /* Void * argument points to a float data value. */
#define  F_print        6   /* Print the accumulated values. */

/**
 * The following macros are used to reduce code duplication.
 * 'ff' is the first two bytes of the initialized mem array, 
 * used to point to the end of written data. The first two macros
 * fetch and store ff, the third macro is used to unpack integers
 * from a char array. 
 */
#define ff_fetch(ptr) (ptr[0] << 8) | ptr[1]
#define ff_store(ptr, ff) {ptr[0] = ff >> 8; ptr[1] = ff & 0xff;}
#define unpack_int(ptr, i) (ptr[i] << 24) | (ptr[i+1] << 16) | (ptr[i+2] << 8) | ptr[i+3];

/**
 * Helper method that writes any given int/char/float
 * to the memory area created by this program. 
 */ 
void * f_data(int code, void * mem, void * data)
{
 unsigned char* ptr = mem; 
 //use an unsigned char to avoid interpreting each byte
 //of an int/float as signed values
 int ff = ff_fetch(ptr); 
 ptr[ff++] = code & 0xff;
 
 if(code == F_data_char) //write a string to mem
 {
  char* str = (char *) data; 
  char c = 1;
  for(int i = 0; c; i++)
  {
   c = str[i];
   ptr[ff++] = c;
   //when null terminator is reached, the loop will write
   //it to mem and stop executing
  }
 }
 //floats and ints are written in the same codeblock to avoid code duplication
 else if(code == F_data_int || code == F_data_float)
 {
  //no bitwise operations on floats, use a union to disguise them as an int
  union {int x; float y;} z;
  if(code == F_data_int) z.x = *((int*)data);
  else z.y = *((float *) data);
  ptr[ff++] = (z.x >> 24) & 0xff;
  ptr[ff++] = (z.x >> 16) & 0xff;
  ptr[ff++] = (z.x >> 8) & 0xff;
  ptr[ff++] = z.x & 0xff;
 }
 ff_store(ptr, ff);
 return mem;
}

/**
 * Helper method that prints all data written to the 
 * given memory area by this program. 
 */
void f_print(void * mem)
{
 unsigned char* ptr = mem;
 //use an unsigned char to avoid interpreting each byte
 //of an int/float as signed values
 int ff = ff_fetch(ptr);
 for(int i = 2; i < ff;)
 {
  char code = ptr[i++];
  
  if(code == F_data_char) //print a string
  {
   //when the zero terminator is reached, c is zero
   //thus, you can use c as your condition for the while loop 
   char c = 1;
   while(c)
   {
    c = ptr[i];
    i++;
    if(c != '\0') printf("%c", c); //print only when you haven't reached the null terminator
   }
  }
  else if(code == F_data_int || code == F_data_float) 
  {
   //since ints and floats are packed the same way, use a union to reduce code duplication
   union{int x; float y;}z;
   z.x = unpack_int(ptr, i); 
   i+=4; //increment i by 4 to account for 4 bytes of mem read
   if(code == F_data_int) printf("%d", z.x);
   else printf("%f", z.y);
  }
 } 
}

void * f (int code, void * mem, void * data)
{
 long long int z_data = (long long int)data;

 if((code == F_first && mem != NULL) 
    || (code != F_first && mem == NULL)
    || (code > F_print) ) return (void*)-1;

 switch(code)
 {
  case F_first:
   mem = malloc(z_data);
   ((char*)mem)[0] = 0 & 0xff;
   ((char*)mem)[1] = 2 & 0xff;
   break;
  case F_last:
   free(mem);
   break;
  case F_data_int:
  case F_data_char:
  case F_data_float:
   mem = f_data(code, mem, data); //writing data is handled in the same function
   break;
  case F_print:
   f_print(mem);
   break; 
 }

 printf("%d : %p %p %lld\n",code, mem, data, z_data);
 return mem;
}
