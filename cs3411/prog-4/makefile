# An even better makefile that uses varaibles to 
# eliminate repeated text in the rest of the file.

# Name of the compiler, gcc or g++ for C++ programs
CC = gcc
# Flags used in compiling
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g  
# Flags used in linking, e.g. -lm if you need the math library
LDFLAGS =
# Target excutable name
EXEC = s-tee
# All the object files that are need to build the executable
OBJECTS = s-tee.o errorhandler.o
# All the source files for building the tgz archive
SOURCES = makefile s-tee.c errorhandler.c errorhandler.h README

all: 
	$(MAKE) s-tee

# Rule to build the executable for s-tee
s-tee: ${OBJECTS} 
	${CC} ${LDFLAGS} -o s-tee ${OBJECTS} 

# Rule to build the object file for s-tee
s-tee.o: s-tee.c 
	${CC} ${CFLAGS} -c s-tee.c

# Rule to build the object file for the error handler
errorhandler.o: errorhandler.c errorhandler.h 
	${CC} ${CFLAGS} -c errorhandler.c errorhandler.h

prog4.tgz: ${SOURCES} 
	gtar -czvf prog4.tgz ${SOURCES}
 
.PHONY: all clean

# Blow away all the object files and executable file
# Typing "make clean" causes this to happen
clean: 
	rm -f ${EXEC} ${OBJECTS}




