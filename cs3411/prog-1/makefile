CC=gcc
CFLAGS=-Wall -pedantic -std=c99

a.out: f.o main.o
	$(CC) -o a.out f.o main.o $(CFLAGS)

f.o: f.c
	$(CC) -c -o f.o f.c $(CFLAGS)

main.o: main.c
	$(CC) -c -o main.o main.c $(CFLAGS)

.PHONY: clean

clean:
	rm -f f.o main.o a.out
 
prog1.tgz: makefile f.c main.c
	gtar -czvf prog1.tgz f.c main.c makefile
