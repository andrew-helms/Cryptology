/*
CIS 4362 - Introduction to Cryptology
Ex02
Andrew Helms
09/28/20
*/

#include <string.h>
#include <iostream>
#include <fstream>

std::string Tpose(std::string input, int* key, int size);

int main(int argc, char* argv[])
{
	//Checks if the keyfile name argument is there

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

	std::string tmp = "";
	std::string keyString = "";
	
	std::getline(file, tmp);

	for (int i = 0; i < tmp.length() ; i++)
		if (tmp[i] != ' ')
			keyString += tmp[i];

	//Checks if key is valid
	
	int* key = new int[keyString.length()];

	for (int i = 0; i < keyString.length(); i++)
	{
		try {
			std::string temp = "";
			temp += keyString[i];
			key[i] = std::stoi(temp, nullptr, 16);
		}
		catch (std::invalid_argument const &ex)
		{
			std::cerr << "Invalid key";			
			return 1;
		}
	}

	bool* validation = new bool[keyString.length()];

	for (int i = 0; i < keyString.length(); i++)
		validation[i] = false;

	for (int i = 0; i < keyString.length(); i++)
	{
		if (key[i] < keyString.length())
		{
			validation[key[i]] = !validation[key[i]];
		}
		else
		{
			std::cerr << "Invalid key";
			return 1;
		}
	}

	for (int i = 0; i < keyString.length(); i++)
	{
		if (!validation[i])
		{
			std::cerr << "Invalid key";
			return 1;
		}
	}

	//Gets user input from stdin

	std::string input = "";

	char inputChar;
	while ((inputChar = getchar()) != EOF)
		input += inputChar;

	std::cout << Tpose(input, key, keyString.length());
}

std::string Tpose(std::string input, int* key, int size)
{
	std::string output = "";
	std::string temp = "";

	for (int i = 0; i < input.length(); i++)
		if (input[i] != ' ' && input[i] != '\n' && input[i] != '\t')
			temp += input[i];

	if (temp.length() % size != 0)
	{
		std::cerr << "Invalid input length";
		return"";
	}

	for (int i = 0; i < temp.length() / size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				if (key[k] == j)
				{
					output += temp[i*size + k];
					break;
				}
			}
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
