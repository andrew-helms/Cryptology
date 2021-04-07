#CIS 4362 - Introduction to Cryptology
#Ex03
#Andrew Helms
#10/16/20

CC=g++
CFLAGS=-I.

all: invMod invMat hill

invMod: invMod.o
	$(CC) invMod.o -o invMod

invMat: invMat.o
	$(CC) invMat.o -o invMat

hill: hill.o
	$(CC) hill.o -o hill

clean: 
	-rm *.o
