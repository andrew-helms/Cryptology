/*
CIS 4362 - Introduction to Cryptology
Ex04
Andrew Helms
11/13/20
*/

#include <string.h>
#include <iostream>
#include <vector>

std::string GenKeys(std::string input, int rounds);

int main(int argc, char* argv[])
{
	//Checks if the number of rounds argument is there
	if (argc < 2)
	{
		std::cerr << "Missing number of rounds\n";
		return 1;
	}

	int rounds = 0;

	//Checks if the number of rounds argument is valid
	try 
	{
		rounds = std::stoi(argv[1], nullptr);
	}
	catch (std::invalid_argument const &ex)
	{
		std::cerr << "Invalid number of rounds\n";
		return 1;
	}
    
    if (rounds < 2 || rounds > 10)
	{
		std::cerr << "Invalid number of rounds\n";
		return 1;
	}
	
	//Gets user input from stdin
	std::string input = "";

	char inputChar;
	while ((inputChar = getchar()) != EOF)
		input += inputChar;
    
    //Checks master key length
    if (input.length() < 9)
    {
        std::cerr << "Invalid master key\n";
        return 1;
    }

	//Processes user input and outputs through stdout
	std::cout << GenKeys(input, rounds);

	return 0;
}

std::string GenKeys(std::string input, int rounds)
{
	//Reference string for indexing
	const std::string reference = "abcdefghijklmnopqrstuvwxyz0123456789.";
    std::vector<std::vector<char>> roundKeys;

	//Process input to master key and validate
	for (int i = 0; i < 3; i++)
	{
        std::vector<char> column;
        
        for (int j = 0; j < 3; j++)
        {
            if ((int)input[i*3+j] > 64 && (int)input[i*3+j] < 91) //convert to lowercase
                input[i*3+j] = input[i*3+j] + 32;
		
            int index = reference.find(input[i*3+j]);
		
            //If the char is in the reference string, add the index to the master key
            if (index > -1)
                column.push_back(index);
            else
            {
                std::cerr << "Invalid master key\n";
                return "";
            }
        }
        
        roundKeys.push_back(column);
	}
    
    int roundConst = 0;
    for (int i = 0; i < rounds; i++)
    {
        std::vector<char> column = roundKeys[i*3+2];
        
        //rotate column up one
        char temp = column[0];
        column[0] = column[1];
        column[1] = column[2];
        column[2] = temp;
        
        //Substition and round constant addition
        for (int j = 0; j < 3; j++)
            column[j] = (column[j]*13+17+(roundConst++))%37;
        
        //Round key column generation
        for (int j = 0; j < 3; j++)
        {
            for (int c = 0; c < 3; c++)
                column[c] = (column[c] + roundKeys[i*3+j][c])%37;
            
            roundKeys.push_back(column);
        }
    }
    
    std::string output; //Output String
    
    for (int i = 0; i < roundKeys.size(); i++)
    {
        for (int j = 0; j < 3; j++)
            output += reference[roundKeys[i][j]];
        
        if (i % 3 == 2) //Last column in round key
            output += "\n";
    }

	return output;
}
