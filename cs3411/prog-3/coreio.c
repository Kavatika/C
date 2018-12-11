#include "coreio.h"
#include <stdbool.h>

extern char * const sys_errlist[];
extern int errno;

const uchar eof = 30u;
const uchar inf = 31u;
int hasNext = 1;
static int i = 7;

//helper functions that read/write n bits
static uchar read_bits(int n);
static void write_bits(uchar b, int n);

//helper functions that read/write a single bit
static uchar read_bit();
static void write_bit(uchar b, bool flush);

//helper function that actually read/writes a byte
static uchar read_char();
static void write_char(uchar b);

void flush()
{
// write(1, "flushing\n", 9);
 while(i >= 0) write_bit(0, true); 
}

uchar read_symbol()
{
 return read_bits(5);
}

void write_symbol(uchar b)
{
 write_bits(b, 5);
}

uchar read_byte()
{
 return read_bits(8);
}

void write_byte(uchar b)
{
 write_bits(b, 8);
}

static uchar read_bits(int n)
{
 uchar c = 0;
 for(int i = n - 1; i >= 0; i--)
 {
  c += (read_bit() << i);
 }
 return c;
}

static void write_bits(uchar c, int n)
{
 for(int i = n - 1; i >= 0; i--)
 {
  write_bit((c >> i) & 1, false);
 }
}

static uchar read_bit()
{
 static uchar c = 0;
 static int i = -1;
 if(i < 0) 
 {
  c = read_char();
  i = 7;
 }
char out = (c >> i) & 1;
 i--;
  return out;
}

/*
 * Assume b is of form 0000 000b
 */
static void write_bit(uchar b, bool flush)
{
 static uchar c = 0;
 c+=(b << i);
 i--;
 if(i < 0)
 {
  write_char(c);
  if(!flush)
  {
   c = 0;
   i = 7;
  }
 }
}

static uchar read_char()
{
 uchar c;
 int e = read(0, &c, 1);
 if(e == -1)
 {
  //return error
  char * err = strerror(errno);
  write(2, err, strlen(err));
  exit(errno);
 }
 hasNext = e;
 return c;
}

static void write_char(uchar c)
{
 int e = write(1, &c, 1);
 if(e == -1)
 {
  char * err = strerror(errno);
  write(2, err, strlen(err));
  exit(errno);
 }
}
