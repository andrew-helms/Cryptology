/*
CIS 4362 - Intro to Cryptology
Ex01
Andrew Helms
09/16/20
*/

#include <string.h>
#include <iostream>

std::string Rot(std::string input, int key);

int main(int argc, char* argv[])
{
	//Checks if the rotation argument is there

	if (argc < 2)
	{
		std::cerr << "Missing or invalid rotation\n";
		return 1;
	}

	int key = 0;

	//Checks if the rotation argument is valid
	
	try 
	{
		key = std::stoi(argv[1], nullptr);
	}
	catch (std::invalid_argument const &ex)
	{
		std::cerr << "Missing or invalid rotation\n";
		return 1;
	}
	
	//Gets user input from stdin

	std::string input = "";

	char inputChar;
	while ((inputChar = getchar()) != EOF)
		input += inputChar;

	//Processes user input and outputs through stdout

	std::cout << Rot(input, key);

	return 0;
}

std::string Rot(std::string input, int key)
{
	//Reference strings for indexing
	
	std::string inputChars = "abcdefghijklmnopqrstuvwxyz0123456789.";
	std::string outputChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.";

	//Processing chars individually

	for (int i = 0; i < input.length(); i++)
	{
		//Converts uppercase to lowercase

		if ((int)input[i] > 64 && (int)input[i] < 91)
			input[i] = input[i] + 32;
		
		int index = inputChars.find(input[i]);
		
		//If the char is in the reference string, shift it by the key using the other reference string

		if (index > -1)
			input[i] = outputChars[(index + key + 37) % 37]; //Adds 37 because behavior wasn't right when index + key was negative
	}

	return input;
}
