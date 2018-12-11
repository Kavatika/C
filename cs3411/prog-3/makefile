# An even better makefile that uses varaibles to 
# eliminate repeated text in the rest of the file.

# Name of the compiler, gcc or g++ for C++ programs
CC = gcc
# Flags used in compiling
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g  
# Flags used in linking, e.g. -lm if you need the math library
LDFLAGS =
# Target excutable name
EXEC = decode encode
# All the object files that are need to build the executable
OBJECTS = encode.o decode.o coreio.o
# All the source files for building the tgz archive
SOURCES = makefile coreio.h coreio.c decode.c encode.c TESTS README

all: 
	$(MAKE) decode
	$(MAKE) encode

# Rule to build the executable for encode
decode: decode.o coreio.o
	${CC} ${LDFLAGS} -o decode decode.o coreio.o

# Rule to build the executable for encode
encode: encode.o coreio.o
	${CC} ${LDFLAGS} -o encode encode.o coreio.o

# Rule to build the object file for encode
encode.o: encode.c coreio.h
	${CC} ${CFLAGS} -c encode.c
 
# Rule to build the object file for decode
decode.o: decode.c coreio.h
	${CC} ${CFLAGS} -c decode.c

# Rule to build the object file for io helper file
coreio.o: coreio.c coreio.h
	${CC} ${CFLAGS} -c coreio.c

prog3.tgz: ${SOURCES} 
	gtar -czvf prog3.tgz ${SOURCES}
 
.PHONY: all clean

# Blow away all the object files and executable file
# Typing "make clean" causes this to happen
clean: 
	rm -f ${EXEC} ${OBJECTS}




