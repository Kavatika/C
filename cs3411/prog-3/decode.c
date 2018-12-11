#include "coreio.h"

static uchar dictionary[30];

int main()
{
 for(int i = 0; i < 30; i++)
 {
  dictionary[i] = read_byte();
 }
 int b = 1;
 while(b)
 {
  uchar c = read_symbol();
  if(c == eof)
  {
   close(1);
   b = 0;
   return 0;
  }
  else if(c == inf) write_byte(read_byte());
  else write_byte(dictionary[c]);
 }

 return 0;
}
