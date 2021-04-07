/*
CIS 4362 - Introduction to Cryptology
Ex02
Andrew Helms
09/28/20
*/

#include <string.h>
#include <iostream>

std::string Unpad(std::string input);

int main(int argc, char* argv[])
{
	//Gets user input from stdin

	std::string input = "";

	char inputChar;
	while ((inputChar = getchar()) != EOF)
		input += inputChar;

	//Processes user input and outputs through stdout

	std::cout << Unpad(input);

	return 0;
}

std::string Unpad(std::string input)
{
	const std::string reference = "bcdefghijklmnopqrstuvwxyz0123456789.a";
	std::string output = "";

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] > 64 && input[i] < 91)
			input[i] = input[i] + 32;
	}

	if (input[input.length() - 1] == '\n')
		input.erase(input.length() - 1); //When doing input redirection, the last character is always a linebreak from my testing

	int paddingNum = reference.find(input[input.length() - 1]) + 1;

	if (paddingNum <= 0)
	{
		std::cerr << "Invalid padding";
		return "";
	}

	for (int i = 0; i < paddingNum; i++)
	{
		if (input[input.length() - 1 - i] != reference[paddingNum - 1])
		{
			std::cerr << "Invalid padding";
			return "";
		}

		input[input.length() - 1 - i] = '*'; //* since it won't be aded to output in the next step
	}

	for (int i = 0; i < input.length(); i++)
	{
		if 
		((int)input[i] == 46 || 
		((int)input[i] > 47 && (int)input[i] < 58) ||
		((int)input[i] > 96 && (int)input[i] < 123))
		{
			output += input[i];
		}	
	}

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
