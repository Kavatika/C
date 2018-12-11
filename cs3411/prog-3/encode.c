#include "coreio.h"

extern int hasNext;
extern const uchar inf;
extern const uchar eof;

typedef struct {
 int exists; 
 int freq;
 uchar seq;
 unsigned int index : 5;
} Entry;

static uchar lowerRange;
static uchar upperRange;
static Entry entries[256];
static uchar dictionary[30];

int entryCompare(const void *p, const void *q)
{
 Entry a = *((Entry *) p);
 Entry b = *((Entry *) q);
 int ret = (a.freq < b.freq) ? 1 : 
            ((a.freq > b.freq) ? -1 : 0);
 if(ret == 0)
 {
  ret = (a.seq < b.seq) ? -1 : 1;
 }
 return ret;
}

static void create_dictionary()
{
 uchar c = read_byte();
 while(hasNext)
 { 
  Entry e = entries[c];
  e.freq++;
  e.seq = c;
  e.exists = 0;
  entries[c] = e;
  if(c < lowerRange) lowerRange = c;
  else if(c > upperRange) upperRange = c;
  c = read_byte();
 }
 Entry sorted[256];
 memcpy(sorted, entries, sizeof(Entry) * 256);
 qsort(sorted + lowerRange, upperRange - lowerRange, sizeof(Entry), entryCompare);

 int i = 0;
 for(int j = lowerRange; i < 30 && j <= upperRange; i++, j++)
 {
  uchar c = sorted[j].seq;
  dictionary[i] = c;
  entries[c].index = i;
  entries[c].exists = 1;
 }
 for(; i < 30; i++)
 {
  dictionary[i] = 0;
 }
}

static void output_dictionary()
{
 for(int i = 0; i < 30; i++)
 {
  write_byte(dictionary[i]);
 }
}

int main()
{
 create_dictionary();
 output_dictionary();
 //dictionary is made, now we need to encode the source file 
 int n = lseek(0, 0, SEEK_SET);
 hasNext = 1;
 if(n < 0)
 {
  //error
  char * err = strerror(errno);
  write(2, err, strlen(err));
  exit(errno);
 }
 uchar c = read_byte();
 while(hasNext)
 {
  if(entries[c].exists)
  {
   write_symbol(entries[c].index);
  }
  else
  {
   write_symbol(inf);
   write_byte(c);
  }
  c = read_byte();
 }
 write_symbol(eof);
 
 flush();
 return 0;
} 


