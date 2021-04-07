CIS 4362 - Introduction to Cryptology
Ex02
Andrew Helms
9/28/20

This code was written in C++. To make and run the code, make and g++ must be installed on the Unix machine. To make all programs, type "make all" or "make" in the terminal in the directory that the files are located. To run the programs, type "./<programName> <args>" in the terminal in the directory that the file is located. There is only one bug, the input redirection adds a line break at the end of the input string in the unpad program, so the program will delete the last character if it is a line break. This can result in the program processing an input as valid if it invalid.
