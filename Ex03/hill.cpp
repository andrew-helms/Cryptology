/*
CIS 4362 - Introduction to Cryptology
Ex03
Andrew Helms
10/16/20
*/

#include <string.h>
#include <iostream>
#include <vector>
#include <fstream>

std::string Hill(std::string input, std::vector<std::vector<int>> key);

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
	
	std::string keyString = "";
	
	std::getline(file, keyString);
	
	std::vector<std::vector<int>> key(3, std::vector<int>(3,0));
	int index = 0;

	//Validates key and converts to matrix
	for (int i = 0; i < keyString.length(); i++)
	{
		if (index > 8) //If there are more than 8 spaces, then there are more than nine numbers in the key. This is not allowed
		{
			std::cerr << "Invalid key";
			
			return 1;			
		}
		
		std::string numStr = "";
		
		while (keyString[i] != ' ' && i < keyString.length()) //Adds digits to the number string until a space is encountered
			numStr += keyString[i++];
		
		int num = 0;
		
		try 
		{
			num = std::stoi(numStr, nullptr); //Turns the number string to a number
		}
		catch (std::invalid_argument const &ex) //Key contains a non-number
		{
			std::cerr << "Invalid key";
			
			return 1;			
		}
		
		if (num > 36 || num < 0) //A number in the key isn't within the allowed range
		{
			std::cerr << "Invalid key";
			
			return 1;			
		}
		
		key[index/3][index%3] = num; //Adds the number to the matrix
		
		index++;
	}
	
	if (index != 9) //If index isn't nine, then there aren't enough numbers in the matrix
	{
		std::cerr << "Invalid key";
		
		return 1;			
	}

	//Gets user input from stdin

	std::string input = "";

	char inputChar;
	while ((inputChar = getchar()) != EOF)
		input += inputChar;

	//Processes user input and outputs through stdout
	std::cout << Hill(input, key);

	return 0;
}

std::string Hill(std::string input, std::vector<std::vector<int>> key)
{
	std::string output = "";
	
	//Reference strings to convert the letters to numbers and numbers to letters
	const std::string inputReference = "abcdefghijklmnopqrstuvwxyz0123456789.";
	const std::string outputReference = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.";
	
	std::vector<int> processing(3, 0); //The column vector being processed
	int cnt = 0; //Which element in the column vector is being added
	
	for (int i = 0; i < input.length(); i++)
	{
		//Converts uppercase to lowercase
		if ((int)input[i] > 64 && (int)input[i] < 91)
			input[i] = input[i] + 32;
		
		int index = inputReference.find(input[i]);
		
		if (index > -1) //If the character is in the input reference string, adds its index to the column vector
			processing[cnt++] = index;
		
		if (cnt == 3) //If the column vector is full
		{
			cnt = 0;
			
			//Matrix multiplcation
			for (int r = 0; r < 3; r++)
			{
				int outputChar = 0;
				for (int c = 0; c < 3; c++)
				{
					outputChar += processing[c]*key[r][c];
				}
				
				output += outputReference[outputChar % 37]; //Adds the charcter corresponding to the matrix multiplcation to the output string
			}
		}
	}
	
	if (cnt != 0) //Valid input characters weren't a multiple of 3
	{
		std::cerr << "Invalid input length";
		
		return "";
	}
	
	int index = 0;

	for (int l = 0; index < output.length(); l++) //Handles the rows of 10 groups
	{
		for (int i = 0; i < 10 && index < output.length(); i++) //Handles the groups of 5 characters
		{
			for (int j = 0; j < 5; j++)
				index++;

			if (index < output.length() && i < 9)
				output = output.insert(index++, " ");
		}

		if (index < output.length())
			output = output.insert(index++, "\n");
	}

	return output;
}
