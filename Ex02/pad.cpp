/*
CIS 4362 - Introduction to Cryptology
Ex02
Andrew Helms
09/28/20
*/

#include <string.h>
#include <iostream>

std::string Pad(std::string input, int factor);

int main(int argc, char* argv[])
{
	//Checks if the factor argument is there

	if (argc < 2)
	{
		std::cerr << "Missing or invalid factor parameter";
		return 1;
	}

	int factor = 0;

	//Checks if the factor argument is valid
	
	try 
	{
		factor = std::stoi(argv[1], nullptr);
	}
	catch (std::invalid_argument const &ex)
	{
		std::cerr << "Missing or invalid factor parameter";
		return 1;
	}
	
	if (factor < 2 || factor > 37)
	{
		std::cerr << "Missing or invalid factor parameter";
		return 1;
	}

	//Gets user input from stdin

	std::string input = "";

	char inputChar;
	while ((inputChar = getchar()) != EOF)
		input += inputChar;

	//Processes user input and outputs through stdout

	std::cout << Pad(input, factor);

	return 0;
}

std::string Pad(std::string input, int factor)
{
	const std::string reference = "bcdefghijklmnopqrstuvwxyz0123456789.a";
	std::string output = "";

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] > 64 && input[i] < 91)
			output += input[i] + 32;

		if 
		((int)input[i] == 46 || 
		((int)input[i] > 47 && (int)input[i] < 58) ||
		((int)input[i] > 96 && (int)input[i] < 123))
		{
			output += input[i];
		}	
	}

	int paddingNum = factor - output.length() % factor;

	for (int i = 0; i < paddingNum; i++)
		output += reference[paddingNum - 1];

	int index = 0;

	for (int l = 0; index < output.length(); l++) //Handles the rows of 10 groups
	{
		for (int i = 0; i < 10 && index < output.length(); i++) //Handles the groups of 5 characters
		{
			for (int j = 0; j < 5; j++)
				index++;

			if (index < output.length())
				output = output.insert(index++, " ");
		}

		if (index < output.length())
			output = output.insert(index++, "\n");
	}

	return output;
}
