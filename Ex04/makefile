#CIS 4362 - Introduction to Cryptology
#Ex04
#Andrew Helms
#11/13/20

CC=g++
CFLAGS=-I.

all: genKeys SAESe SAESd

genKeys: genKeys.o
	$(CC) genKeys.o -o genKeys

SAESe: SAESe.o
	$(CC) SAESe.o -o SAESe

SAESd: SAESd.o
	$(CC) SAESd.o -o SAESd

clean: 
	-rm *.o
