/*
CIS 4362 - Introduction to Cryptology
Ex03
Andrew Helms
10/16/20
*/

#include <string.h>
#include <iostream>

std::string InvMod(std::string input, int modulus);

int main(int argc, char* argv[])
{
	//Checks if the modulus argument is there

	if (argc < 2)
	{
		std::cerr << "Missing or invalid modulus";
		return 1;
	}

	int modulus = 0;

	//Checks if the modulus argument is valid
	
	try 
	{
		modulus = std::stoi(argv[1], nullptr);
	}
	catch (std::invalid_argument const &ex)
	{
		std::cerr << "Missing or invalid modulus";
		return 1;
	}
	
	for (int i = 2; i < modulus / 2; i++) //modulus / 2 since nothing greater than that can be a factor of modulus
	{
		if (modulus % i == 0)
		{
			std::cerr << "Modulus not prime";
			return 1;
		}
	}

	//Gets user input from stdin

	std::string input = "";

	char inputChar;
	while ((inputChar = getchar()) != EOF)
		input += inputChar;

	//Processes user input and outputs through stdout

	std::cout << InvMod(input, modulus);

	return 0;
}

std::string InvMod(std::string input, int modulus)
{
	std::string output = "";
	const std::string reference = "0123456789"; //Reference string to tell if a character is a digit
	
	for (int i = 0; i < input.length(); i++)
	{
		std::string numStr = "";
		
		while (reference.find(input[i]) != -1 && i < input.length()) //Adds characters to the number string if they are digits. Stops at the first non-digit
		{
			numStr += input[i++];
		}
		
		int num = 0;
		
		if (numStr.length() == 0) //No digits at the start of the line, so it skips to the next line
		{
			std::cerr << "Input is not a decimal number";
			
			char temp = input[i];
			
			while (temp != '\n' && i < input.length() - 1)
				temp = input[++i];
			
			continue;
		}
		
		try 
		{
			num = std::stoi(numStr, nullptr); //Converts the number string to a number
		}
		catch (std::invalid_argument const &ex)
		{
			std::cerr << "Input is not a decimal number"; //Number string isn't a number, so it skips to the next line
			
			char temp = input[i];
			
			while (temp != '\n' && i < input.length() - 1)
				temp = input[++i];
			
			continue;			
		}
		
		//Extended Eulclidean Algorithm
		
		int oldT = 0;
		int newT = 1;
		int oldR = modulus; 
		int newR = num;
		
		while (newR != 0)
		{
			int q = oldR / newR;
			
			int temp = oldT;
			oldT = newT;
			newT = temp - q * newT;
			
			temp = oldR;
			oldR = newR;
			newR = temp - q * newR;
		}
		
		if (oldT < 0)
			oldT += modulus;
		
		output += std::to_string(oldT) + "\n"; //Adds the output of EEA to the output string
		
		char temp = input[i];
			
		while (temp != '\n' && i < input.length() - 1) //Skips any remaining digits in the line
		{
			temp = input[++i];
		}
	}

	return output;
}
