/*
CIS 4362 - Intro to Cryptology
Ex01
Andrew Helms
09/16/20
*/

#include <string.h>
#include <iostream>
#include <fstream>

std::string Sub(std::string input, std::string key);

int main(int argc, char* argv[])
{
	//Checks if the keyfile was passed in

	if (argc < 2)
	{
		std::cerr << "Missing keyfile name";
		return 1;
	}

	std::string keyfile = argv[1];

	std::ifstream file;
	file.open(keyfile);
	
	//Checks if the keyfile was valid
	
	if (!file.is_open())
	{
		std::cerr << "Key file cannot be opened";
		return 1;
	}

	std::string key = "";

	std::getline(file, key);

	//Gets user input from stdin

	std::string input = "";
	
	char inputChar;
	while ((inputChar = getchar()) != EOF)
		input += inputChar;

	//Processes user input and outputs through stdout
	
	std::cout << Sub(input, key);

	return 0;
}

std::string Sub(std::string input, std::string key)
{
	//Reference string
	
	std::string inputChars = "abcdefghijklmnopqrstuvwxyz0123456789.";

	//Key validation
	
	for (int i = 0; i < key.length(); i++)
	{
		char curr = key[i];

		//converts uppercase to lowercase

		if (curr > 64 && curr < 91)
			curr += 32;
		
		//checks if the key length is right or if the current char is in the key

		if(inputChars.find(curr) == -1 || key.length() != 37)
		{
			std::cerr << "Invalid key";
			return "";
		}
	}

	//Processes chars individually

	for (int i = 0; i < input.length(); i++)
	{
		//Converts uppercase to lowercase

		if ((int)input[i] > 64 && (int)input[i] < 91)
			input[i] = input[i] + 32;
		
		int index = inputChars.find(input[i]);
		
		//Finds index of curr char in the reference string
		//Then swaps it with the char of the same index in the key

		if (index > -1)
			input[i] = key[index];
	}

	return input;
}
