/*
CIS 4362 - Intro to Cryptology
Ex01
Andrew Helms
09/16/20
*/

#include <iostream>
#include <string>

std::string Parse(std::string input);

int main() 
{
	//Get user input from stdin

	std::string input = "";

	char inputChar;
	while ((inputChar = getchar()) != EOF)
		input += inputChar;

	//Process user input and output through stdout

	std::cout << Parse(input);

	return 0;
}

std::string Parse(std::string input)
{
	//convert all uppercase to lowercase

	for (int i = 0; i < input.length(); i++)
	{
		if ((int)input[i] > 64 && (int)input[i] < 91)
			input[i] = input[i] + 32;
	}

	std::string output = "";
	int index = 0;

	for (int l = 0; index < input.length(); l++) //Handles the rows of 10 groups
	{
		for (int i = 0; i < 10 && input.length(); i++) //Handles the groups of 5 characters
		{

			for (int j = 0; j < 5 && index < input.length(); index++) //Processes individual characters
			{
				if 
					((int)input[index] == 46 || 
					((int)input[index] > 47 && (int)input[index] < 58) ||
					((int)input[index] > 64 && (int)input[index] < 91) || 
					((int)input[index] > 96 && (int)input[index] < 123))
				{
					output += input[index];
					j++; //Only increment the count if we add the char to the output
				}
			}

			output += " ";
		}

		output += "\n";
	}

	return output;
}
