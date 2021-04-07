#CIS 4362 - Introduction to Cryptology
#Ex02
#Andrew Helms
#09/28/20

CC=g++
CFLAGS=-I.

all: pad unpad tpose

pad: pad.o
	$(CC) pad.o -o pad

unpad: unpad.o
	$(CC) unpad.o -o unpad

tpose: tpose.o
	$(CC) tpose.o -o tpose

clean: 
	-rm *.o
