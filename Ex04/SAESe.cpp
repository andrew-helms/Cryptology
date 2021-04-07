/*
CIS 4362 - Introduction to Cryptology
Ex04
Andrew Helms
11/13/20
*/

#include <string.h>
#include <iostream>
#include <vector>

std::string SAESe(std::string input, int rounds, std::vector<std::vector<char>> roundKeys);

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
    
    //Checks if the master key argument is there
	if (argc < 3)
	{
		std::cerr << "Missing master key\n";
		return 1;
	}
    
    std::string masterKey = argv[2];
    
    //Checks master key length
    if (masterKey.length() != 9)
    {
        std::cerr << "Invalid master key\n";
        return 1;
    }
	
    //Generate Sub Keys
    
    //Reference string for indexing
	const std::string reference = "abcdefghijklmnopqrstuvwxyz0123456789.";
    std::vector<std::vector<char>> roundKeys;

	//Process input to master key and validate
	for (int i = 0; i < 3; i++)
	{
        std::vector<char> column;
        
        for (int j = 0; j < 3; j++)
        {
            if ((int)masterKey[i*3+j] > 64 && (int)masterKey[i*3+j] < 91) //convert to lowercase
                masterKey[i*3+j] = masterKey[i*3+j] + 32;
		
            int index = reference.find(masterKey[i*3+j]);
		
            //If the char is in the reference string, add the index to the master key
            if (index > -1)
                column.push_back(index);
            else
            {
                std::cerr << "Invalid master key\n";
                return 1;
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
    
	//Gets user input from stdin
	std::string input = "";

	char inputChar;
	while ((inputChar = getchar()) != EOF)
		input += inputChar;

	//Processes user input and outputs through stdout
	std::cout << SAESe(input, rounds, roundKeys);

	return 0;
}

std::string SAESe(std::string input, int rounds, std::vector<std::vector<char>> roundKeys)
{
    //Reference strings for indexing
    const std::string inputReference = "abcdefghijklmnopqrstuvwxyz0123456789.";
	const std::string outputReference = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.";
    std::vector<std::vector<std::vector<char>>> inputAsBlocks;
    
    //Upper to lowercase and validates
    for (int i = 0; i < input.length(); )
    {
        std::vector<std::vector<char>> blockMatrix;
        
        for (int j = 0; j < 3; j++)
        {
            std::vector<char> column;
            
            for (int k = 0; k < 3;)
            {
                if ((int)input[i] > 64 && (int)input[i] < 91)
                    input[i] = input[i] + 32;
                
                int index = inputReference.find(input[i]);
            
                //If the char is in the reference string, add the index to the master key
                if (index > -1)
                {
                    column.push_back(index);
                    k++;
                }
                else
                {
                    if ((int)input[i] != 9 && (int)input[i] != 32 && (int)input[i] != 10 && (int)input[i] != 13)
                        std::cerr << "Invalid input character not encrypted\n";
                }
                
                if ((++i) == input.length())
                {
                    if (j+k != 5)
                    {
                        if (j+k != 0)
                            std::cerr << "Invalid input length\n";
                        goto breakOut;
                    }
                }
            }
            
            blockMatrix.push_back(column);
        }
        
        inputAsBlocks.push_back(blockMatrix);
    }
    
    breakOut: //to break out of main loop
    
    //Initial whitening
    for (int i = 0; i < inputAsBlocks.size(); i++)
        for (int c = 0; c < 3; c++)
            for (int r = 0; r < 3; r++)
                inputAsBlocks[i][c][r] = (inputAsBlocks[i][c][r] + roundKeys[c][r]) % 37;
            
    //Run through rounds
    for (int i = 0; i < rounds; i++)
    {
        //SubChars
        for (int j = 0; j < inputAsBlocks.size(); j++)
            for (int c = 0; c < 3; c++)
                for (int r = 0; r < 3; r++)
                    inputAsBlocks[j][c][r] = (inputAsBlocks[j][c][r]*13+17) % 37;
                    
        //ShiftRows
        for (int j = 0; j < inputAsBlocks.size(); j++)
        {
            char temp = inputAsBlocks[j][0][1];
            inputAsBlocks[j][0][1] = inputAsBlocks[j][1][1];
            inputAsBlocks[j][1][1] = inputAsBlocks[j][2][1];
            inputAsBlocks[j][2][1] = temp;
            
            temp = inputAsBlocks[j][0][2];
            inputAsBlocks[j][0][2] = inputAsBlocks[j][2][2];
            inputAsBlocks[j][2][2] = inputAsBlocks[j][1][2];
            inputAsBlocks[j][1][2] = temp;
        }
        
        //MixCols
        if (i != rounds - 1)
        {
            for (int k = 0; k < inputAsBlocks.size(); k++)
            {
                std::vector<std::vector<int>> key
                {
                    {1, 7, 17},
                    {3, 11, 19},
                    {5, 13, 23}
                };
                
                std::vector<std::vector<char>> blockMatrix = inputAsBlocks[k];
                
                for (int c = 0; c < 3; c++)
                {
                    for (int r = 0; r < 3; r++)
                    {
                        int sum = 0;
                        
                        for (int j = 0; j < 3; j++)
                        {
                            sum += key[j][r] * inputAsBlocks[k][c][j];
                        }
                        
                        blockMatrix[c][r] = sum % 37;
                    }
                }
                
                inputAsBlocks[k] = blockMatrix;
            }
        }
        
        //Whitening
        for (int j = 0; j < inputAsBlocks.size(); j++)
            for (int c = 0; c < 3; c++)
                for (int r = 0; r < 3; r++)
                    inputAsBlocks[j][c][r] = (inputAsBlocks[j][c][r] + roundKeys[i*3+c+3][r]) % 37;
    }
    
    std::string output = "";
    
    for (int i = 0; i < inputAsBlocks.size(); i++)
        for (int c = 0; c < 3; c++)
            for (int r = 0; r < 3; r++)
                output += outputReference[inputAsBlocks[i][c][r]];
    
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