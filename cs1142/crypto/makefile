# An even better makefile that uses varaibles to 
# eliminate repeated text in the rest of the file.

# Name of the compiler, gcc or g++ for C++ programs
CC = gcc
# Flags used in compiling
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g  
# Flags used in linking, e.g. -lm if you need the math library
LDFLAGS =
# Target excutable name
EXEC = Crypto
# All the object files that are need to build the executable
OBJECTS = Crypto.o Key.o Stats.o

# Default rule, links the *.o files to create the executable
# Typing "make" causes this to happen
${EXEC}: ${OBJECTS}
	${CC} ${LDFLAGS} ${OBJECTS} -o ${EXEC}

# Rule to build the object file for the main program
Crypto.o: Crypto.c Key.h Stats.h
	${CC} ${CFLAGS} -c Crypto.c

# Rule to build the object file for Interval data type
Key.o: Key.c Key.h
	${CC} ${CFLAGS} -c Key.c

# Rule to build the object file for Location data type
Stats.o: Stats.c Stats.h
	${CC} ${CFLAGS} -c Stats.c

# Execute the test program
# Typing "make run" causes this to happen
run: Crypto
	./Crypto

# Blow away all the object files and executable file
# Typing "make clean" causes this to happen
clean: 
	rm -f ${EXEC} ${OBJECTS}




