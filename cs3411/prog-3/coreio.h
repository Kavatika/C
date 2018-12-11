#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef unsigned char uchar;
extern const uchar eof;
extern const uchar inf;
extern int hasNext;

void flush();

uchar read_symbol();

void write_symbol(uchar b);

uchar read_byte();

void write_byte(uchar b);
