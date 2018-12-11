CC=gcc
CFLAGS=-Wall -pedantic -std=c99

copy: copy.o
	$(CC) -o copy copy.o $(CFLAGS)

copy.o: copy.c
	$(CC) -c -o copy.o copy.c $(CFLAGS)

.PHONY: clean

clean:
	rm -f copy.o copy 
 
prog2.tgz: makefile copy.c stats.txt
	gtar -czvf prog2.tgz copy.c stats.txt makefile
