#define _POSIX_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "errorhandler.h"

#define err(pfd) {close(pfd[0]); error_handler();}

int main(int argc, char * argv[])
{
 int e = 0;
 if(argc < 3) //not enough arguments to run
 {
  char * str = "Not enough arguments. Correct usage is: s-tee <file name> <program name> <arguments>";
  write(1, str, strlen(str));
  exit(1);
 }
 char * logfile = argv[1];
 char ** arguments = argv + 2;
 char * program = argv[2];
 
 //make sure logfile doesn't already exist
 int o = open(logfile, O_RDONLY);
 if(o >= 0)
 {
  //file already exists, print error and exit
  char * str = "Selected logfile already exists.\n";
  write(1, str, strlen(str));
  exit(1);
 }

 int pfd[2];
 e = pipe(pfd);
 if(e < 0) error_handler();
 if(fork() == 0) //child
 {
  //fd management
  e = close(pfd[1]);
  if(e < 0) err(pfd);
  int log = open(logfile, O_CREAT | O_WRONLY, S_IRWXU);
  if(log < 0) err(pfd);
 
  //buffer and output file
  char buf[1024];
  int r;
  while((r = read(pfd[0], buf, 1024)) != 0)
  {  
   if(e < 0) err(pfd);
   e = write(1, buf, r);
   if(e < 0) err(pfd);
   e = write(log, buf, r);
   if(e < 0) err(pfd);
  }
  //close all fd's
  close(pfd[0]);
  close(log);
  exit(0);
 }
 else //parent
 {
  //fd management
  close(pfd[0]);
  close(1);
  close(2);
  dup(pfd[1]); dup(pfd[1]);
  close(pfd[1]);
  
  //pipe all args verbatim to stdout + a new line char
  for(int i = 0; i < argc; i++)
  {
   write(1, argv[i], strlen(argv[i]));
   write(1, " ", 1);
  }
  write(1, "\n", 1);
  //execute the command
  execvp(program, arguments);
  error_handler();
 }
}
