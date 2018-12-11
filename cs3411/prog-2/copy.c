#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> //only for sprintf and perror
#include <string.h>

#define DEFAULT_BUFFER 65536
//#define 

int calcChecksum(int cur, char * buf, int eob)
{
 int sum = cur;
 for(int i = 0; i < eob; i+=4)
 {
  int next = (buf[i] << 24) | (buf[i+1] << 16) | (buf[i+2] << 8) | buf[i+3];
  sum = sum ^ next;
 }
 return sum;
}

int copy(int fdin, int fdout, int blocksize)
{
 void * buf = malloc(sizeof(char) * blocksize);
 int checksum = 0;
 int bytes_read = 1;
 while(bytes_read)
 {
  bytes_read = read(fdin, buf, blocksize);
  if(bytes_read < 0) //indicates an error
  {
   write(1, "read error\n",12);
   perror("");
   exit(-1);   
  }
  //checksumming
  checksum = calcChecksum(checksum, buf, bytes_read);

  //writing
  int bytes_written = write(fdout, buf, bytes_read);
  if(bytes_written < 0) //indicates an error
  {
   write(1, "read error\n",12);
   perror("");
   exit(-1); 
  }
 }
 free(buf);
 return checksum; 
} 

int main(int argc, char* argv[])
{
 //step 1: extract args
 if(argc <= 2) //not enough arguments
 {
  char * str = "Invalid usage.\n Correct usage is: copy <infile> <outfile> [blocksize]\n";
  write(1, str, strlen(str));
  exit(1);
 }
 //char* infile = argv[1];
 int fdin = open(argv[1], O_RDONLY);
 //char* outfile = argv[2];
 int fdout = open(argv[2], O_RDWR | O_APPEND | O_CREAT, 0600);

 if(fdin < 0 || fdout < 0)
 {
  char str[50];
  sprintf(str, "A kernel error occured while trying to open the %s file.\n", (fdin < 0) ? "input" : "output");
  perror(str);
 }
 
 int blocksize = (argc >= 4) ? atoi(argv[3]) : DEFAULT_BUFFER; //use atoi
 if(blocksize % 4 != 0)
 {
  char * str = "The given blocksize must be a multiple of four. The blocksize has been incremeted to the nearest multiple of four.\n";
  write(1, str, strlen(str));
 }
 //file duplication here
 int checksum = copy(fdin, fdout, blocksize);

 char str[14];
 int size = sprintf(str, "%x\n", checksum);
 write(1,str,size); 

 close(fdin);
 close(fdout);
 return 0;
}
