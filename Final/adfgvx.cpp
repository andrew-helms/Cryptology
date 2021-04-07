#include <string.h>
#include <iostream>
#include <vector>
#include "adfgvx.h"

std::string adfgvxE(std::string pKey, std::string cKey, std::string input)
{
	const std::string reference = "abcdefghijklmnopqrstuvwxyz0123456789";
    const std::string outputReference = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    
    //Convert input to lowercase and remove invalid characters
    std::string temp = "";
    for (int i = 0; i < input.length(); i++)
    {
        if ((int)input[i] > 64 && (int)input[i] < 91) //convert to lowercase
                input[i] = input[i] + 32;
                
        int index = reference.find(input[i]);
                
        if (index > -1)
            temp += input[i];
    }
    
    input = temp;
    temp = "";
    
    //Remove duplicates from keys
    for (int i = 0; i < pKey.length(); i++)
    {
        if ((int)pKey[i] > 64 && (int)pKey[i] < 91) //convert to lowercase
                pKey[i] = pKey[i] + 32;
                
        int index = reference.find(pKey[i]);
                
        if (i == pKey.find(pKey[i]) && index > -1)
            temp += pKey[i];
    }
    
    pKey = temp;
    temp = "";
    
    for (int i = 0; i < cKey.length(); i++)
    {
        if ((int)cKey[i] > 64 && (int)cKey[i] < 91) //convert to lowercase
                cKey[i] = cKey[i] + 32;
                
        int index = reference.find(cKey[i]);
                
        if (i == cKey.find(cKey[i]) && index > -1)
            temp += cKey[i];
    }
    
    cKey = temp;
    temp = "";
    
    //Make key matrix;
    std::vector<std::vector<char>> keyMat;
    int offset = -1;
    
    for (int r = 0; r < 6; r++)
    {
        std::vector<char> row;
        
        for (int c = 0; c < 6; c++)
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
    const std::string matLabels = "adfgvx";
    
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
            if (c < colTranMat[r].size())
                output += outputReference[reference.find(colTranMat[r][orderedColIndex[c]])];
        }
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

std::string adfgvxD(std::string pKey, std::string cKey, std::string input)
{
	const std::string reference = "abcdefghijklmnopqrstuvwxyz0123456789";
    
    //Convert input to lowercase and remove invalid characters
    std::string temp = "";
    for (int i = 0; i < input.length(); i++)
    {
        if ((int)input[i] > 64 && (int)input[i] < 91) //convert to lowercase
                input[i] = input[i] + 32;
                
        int index = reference.find(input[i]);
                
        if (index > -1)
            temp += input[i];
    }
    
    input = temp;
    temp = "";
    
    //Remove duplicates from keys
    for (int i = 0; i < pKey.length(); i++)
    {
        if ((int)pKey[i] > 64 && (int)pKey[i] < 91) //convert to lowercase
                pKey[i] = pKey[i] + 32;
                
        int index = reference.find(pKey[i]);
                
        if (i == pKey.find(pKey[i]) && index > -1)
            temp += pKey[i];
    }
    
    pKey = temp;
    temp = "";
    
    for (int i = 0; i < cKey.length(); i++)
    {
        if ((int)cKey[i] > 64 && (int)cKey[i] < 91) //convert to lowercase
                cKey[i] = cKey[i] + 32;
                
        int index = reference.find(cKey[i]);
                
        if (i == cKey.find(cKey[i]) && index > -1)
            temp += cKey[i];
    }
    
    cKey = temp;
    temp = "";
    
    //Make key matrix;
    std::vector<std::vector<char>> keyMat;
    int offset = -1;
    
    for (int r = 0; r < 6; r++)
    {
        std::vector<char> row;
        
        for (int c = 0; c < 6; c++)
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
    
    std::vector<std::vector<char>> colTranMat(cKey.length(), std::vector<char>(input.length()/cKey.length() + 1, '?')); //Question mark shows that the cell should be empty
    
    for (int c = 0; c < orderedColIndex.size(); c++)
        for (int r = 0; r < colTranMat.size(); r++)
            colTranMat[r][orderedColIndex[c]] = input[orderedColIndex.size()*c + r];
            
    loopBreak: //label to break from inner loop
    
    for (int r = 0; r < colTranMat.size(); r++)
        for (int c = 0; c < colTranMat[0].size(); c++)
            if (colTranMat[r][c] != '?')
                temp += colTranMat[r][c];
                
    //Find the inverse of the Polybius square output   
    const std::string matLabels = "adfgvx";
    std::string output = "";
    
    std::cout<< temp.length() << std::endl;
    
    for (int i = 0; i < temp.length()-1; i+=2)
        output += keyMat[matLabels.find(temp[i])][matLabels.find(temp[i+1])];
        
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