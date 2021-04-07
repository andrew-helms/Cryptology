/*
CIS 4362 - Introduction to Cryptology
Final Project
Andrew Helms
12/09/20
*/

#include "adfgvx.h"

std::string adfgvxE(std::string pKey, std::string cKey, std::string input)
{
	const std::string reference = "abcdefghijklmnopqrstuvwxyz0123456789"; //reference string for input character validation and indexing
    const std::string matLabels = "adfgvx"; //reference string for Polybius Square operation
    const std::string outputReference = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; //reference string for output characters
    
    //Convert input to lowercase and remove invalid characters
    std::string temp = "";
    for (int i = 0; i < input.length(); i++)
    {
        if ((int)input[i] > 64 && (int)input[i] < 91) //convert to lowercase
                input[i] = input[i] + 32;
                
        int index = reference.find(input[i]); //Checks if character is valid
                
        if (index > -1)
            temp += input[i];
    }
    
    input = temp; //Set input to the lowercase, validated form
    temp = "";

    if (input.length() == 0) //Throw an error if there were no valid characters
        return "Error: No valid input characters";
    
    //Remove duplicates from keys
    for (int i = 0; i < pKey.length(); i++)
    {
        if ((int)pKey[i] > 64 && (int)pKey[i] < 91) //convert to lowercase
                pKey[i] = pKey[i] + 32;
                
        int index = reference.find(pKey[i]); //Checks if character is valid
                
        if (i == pKey.find(pKey[i]) && index > -1)
            temp += pKey[i];
    }
    
    pKey = temp; //Set Polybius Square key to the lowercase, validated form
    temp = "";
    
    for (int i = 0; i < cKey.length(); i++)
    {
        if ((int)cKey[i] > 64 && (int)cKey[i] < 91) //convert to lowercase
                cKey[i] = cKey[i] + 32;
                
        int index = reference.find(cKey[i]); //Checks if character is valid
                
        if (i == cKey.find(cKey[i]) && index > -1)
            temp += cKey[i];
    }
    
    cKey = temp; //Set columnar transposition key to the lowercase, validated form
    temp = "";

    if (cKey.length() == 0) //Throw an error if there were no valid characters
        return "Error: Columnar transposition key has no valid characters";
    
    //Make key matrix;
    std::vector<std::vector<char>> keyMat;
    int offset = -1;
    
    for (int r = 0; r < 6; r++)
    {
        std::vector<char> row;
        
        for (int c = 0; c < 6; c++) //Add characters to the ketMatrix, one row at a time. Starting with the characters in the Polybius square key and then the rest of the alphabet
        {
            if (6*r + c < pKey.length())
                row.push_back(pKey[6*r + c]); 
            else
            {
                int index = 0;
                
                while (index > -1)
                    index = pKey.find(reference[++offset]);
                
                row.push_back(reference[offset]);
            }
        }
        
        keyMat.push_back(row);
    }
    
    //Calculate the output of the Polybius square part   
    
    for (int i = 0; i < input.length(); i++)
    {
        bool found = false;
        for (int r = 0; !found && r < 6; r++)
        {
            for (int c = 0; !found && c < 6; c++)
            {
               if (input[i] == keyMat[r][c])
               {
                   temp += matLabels[r];
                   temp += matLabels[c];
                   found = true;
               }
            }
        }
    }
    
    //Calculate the output of the keyed columnar transposition
    std::vector<std::vector<char>> colTranMat;
    
    for (int r = 0; true; r++)
    {
        std::vector<char> row;
        for (int c = 0; c < cKey.length(); c++)
        {
            if (cKey.length()*r + c < temp.length())
            {
                row.push_back(temp[cKey.length()*r + c]);
            }
            else
            {
                colTranMat.push_back(row);
                goto loopBreak; //break from inner loop
            }
        }
        colTranMat.push_back(row);
    }
    
    loopBreak: //label to break from inner loop
    
    std::string output = "";
    
    //find order of columns
    std::vector<int> orderedColIndex;
    for (int i = 0; i < reference.length(); i++)
    {
        for (int j = 0; j < cKey.length(); j++)
        {
            if (cKey[j] == reference[i])
            {
                orderedColIndex.push_back(j);
                break;
            }
        }
        
        if (orderedColIndex.size() == cKey.length())
            break;
    }
    
    for (int c = 0; c < orderedColIndex.size(); c++)
    {
        for (int r = 0; r < colTranMat.size(); r++)
        {
            if (orderedColIndex[c] < colTranMat[r].size())
                output += outputReference[reference.find(colTranMat[r][orderedColIndex[c]])]; //And the columns to the output string in the correct order
        }
    }
    
    //Format output

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
			output = output.insert(index++, "\r\n");

        index++;
	}
    
    return output;
}

std::string adfgvxD(std::string pKey, std::string cKey, std::string input)
{
	const std::string reference = "abcdefghijklmnopqrstuvwxyz0123456789"; //reference string for input character validation and indexing
    const std::string matLabels = "adfgvx"; //reference string for the Polybius Square
    
    //Convert input to lowercase and remove invalid characters
    std::string temp = "";
    for (int i = 0; i < input.length(); i++)
    {
        if ((int)input[i] > 64 && (int)input[i] < 91) //convert to lowercase
                input[i] = input[i] + 32;
                
        int index = matLabels.find(input[i]); //Checks if character is valid. Use matLabels since ciphertext should only contain those characters
                
        if (index > -1)
            temp += input[i];
    }
    
    input = temp; //Sets input to the lowercase, validated form
    temp = "";

    if (input.length() == 0) //Throws an error in there were no valid characters
        return "Error: No valid input characters";
    
    //Remove duplicates from keys
    for (int i = 0; i < pKey.length(); i++)
    {
        if ((int)pKey[i] > 64 && (int)pKey[i] < 91) //convert to lowercase
                pKey[i] = pKey[i] + 32;
                
        int index = reference.find(pKey[i]); //Checks if character is valid
                
        if (i == pKey.find(pKey[i]) && index > -1)
            temp += pKey[i];
    }
    
    pKey = temp; //Sets Polybius Square key to the lowercase, validated form
    temp = "";
    
    for (int i = 0; i < cKey.length(); i++)
    {
        if ((int)cKey[i] > 64 && (int)cKey[i] < 91) //convert to lowercase
                cKey[i] = cKey[i] + 32;
                
        int index = reference.find(cKey[i]); //Checks if character is valid
                
        if (i == cKey.find(cKey[i]) && index > -1)
            temp += cKey[i];
    }
    
    cKey = temp; //Sets columnar transposition key to the lowercase, validated form
    temp = "";

    if (cKey.length() == 0) //Throws an error is there were no valid characters
        return "Error: Columnar transposition key has no valid characters";
    
    //Make key matrix;
    std::vector<std::vector<char>> keyMat;
    int offset = -1;
    
    for (int r = 0; r < 6; r++)
    {
        std::vector<char> row;
        
        for (int c = 0; c < 6; c++) //Add characters to the key matrix, starting with the polybius square key and then the rest of the alphabet
        {
            if (6*r + c < pKey.length())
                row.push_back(pKey[6*r + c]);
            else
            {
                int index = 0;
                
                while (index > -1)
                    index = pKey.find(reference[++offset]);
                
                row.push_back(reference[offset]);
            }
        }
        
        keyMat.push_back(row);
    }
    
    //Find the inverse of the keyed columnar transpose output
    //find order of columns
    std::vector<int> orderedColIndex;
    for (int i = 0; i < reference.length(); i++)
    {
        for (int j = 0; j < cKey.length(); j++)
        {
            if (cKey[j] == reference[i])
            {
                orderedColIndex.push_back(j);
                break;
            }
        }
        
        if (orderedColIndex.size() == cKey.length())
            break;
    }
    
    std::vector<std::vector<char>> colTranMat(input.length() / cKey.length() + 1, std::vector<char>(cKey.length(), '?')); //'?' shows that the cell should be empty. All cells start with '?' and get filled in if they should be non empty

    int emptySpaces = colTranMat.size() * colTranMat[0].size() - input.length(); //The number of empty spaces in the last row
    int index = 0;
    
    //Add characters to the columnar transposition matrix by column in the inverted order
    for (int c = 0; c < orderedColIndex.size(); c++)
        for (int r = 0; r < colTranMat.size(); r++)
            if (index < input.length() && r < (colTranMat.size() - 1) || (r == (colTranMat.size() - 1) && orderedColIndex[c] < (cKey.length() - emptySpaces)))
                colTranMat[r][orderedColIndex[c]] = input[index++];
    
    //Read from the columnar transposition matrix by row, top to bottom
    for (int r = 0; r < colTranMat.size(); r++)
        for (int c = 0; c < colTranMat[0].size(); c++)
            if (colTranMat[r][c] != '?')
                temp += colTranMat[r][c];
                
    //Find the inverse of the Polybius square output 
    std::string output = "";
    
    for (int i = 0; i < temp.length()-1; i+=2)
        output += keyMat[matLabels.find(temp[i])][matLabels.find(temp[i+1])];
        
    //Output formatting

    index = 0;
    
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
			output = output.insert(index++, "\r\n");

        index++;
	}
                
    return output;
}