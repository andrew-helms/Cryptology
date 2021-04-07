#CIS 4362 - Intro to Cryptology
#Ex01
#Andrew Helms
#09/16/20

CC=g++
CFLAGS=-I.

all: strip rot sub

strip: strip.o
	$(CC) strip.o -o strip

rot: rot.o
	$(CC) rot.o -o rot

sub: sub.o
	$(CC) sub.o -o sub

clean: 
	-rm *.o
