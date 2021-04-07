/*
CIS 4362 - Introduction to Cryptology
Ex03
Andrew Helms
10/16/20
*/

#include <string.h>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> InvMat(std::vector<std::vector<int>> matrix);

int main(int argc, char* argv[])
{
	//Gets user input from stdin
	std::string input = "";

	char inputChar;
	while ((inputChar = getchar()) != EOF)
		input += inputChar;
	
	std::vector<std::vector<int>> matrix(3, std::vector<int>(3,0)); //Matrix is represented by a vector of vectors of ints
	int index = 0;

	//Validates user input and converts to matrix
	for (int i = 0; i < input.length(); i++)
	{
		if (index > 8) //If there are more than 8 spaces, then there are more than nine numbers in the line. This is not allowed
		{
			std::cerr << "Invalid matrix";
			
			return 1;			
		}
		
		std::string numStr = "";
		
		while (input[i] != ' ' && i < input.length()) //Adds digits to the number string until a space is encountered
			numStr += input[i++];
		
		int num = 0;
		
		try 
		{
			num = std::stoi(numStr, nullptr); //Turns the number string to a number
		}
		catch (std::invalid_argument const &ex) //Line contains a non-number
		{
			std::cerr << "Invalid matrix";
			
			return 1;			
		}
		
		if (num > 36 || num < 0) //A number in the line isn't within the allowed range
		{
			std::cerr << "Invalid matrix";
			
			return 1;			
		}
		
		matrix[index/3][index%3] = num; //Adds the number to the matrix
		
		index++;
	}
	
	if (index != 9) //If index isn't nine, then there aren't enough numbers in the matrix
	{
		std::cerr << "Invalid matrix";
		
		return 1;			
	}
	
	std::vector<std::vector<int>> invMatrix = InvMat(matrix); //Find matrix inverse
	
	if (matrix == invMatrix) //If they are the same, then the matrix wasn't invertible
		return 1;
	
	for (int r = 0; r < 3; r++) //prints the matrix
	{
		for (int c = 0; c < 3; c++)
		{
			std::cout << invMatrix[r][c];
			
			if (r + c < 4)
				std::cout << " ";
		}
	}

	return 0;
}

std::vector<std::vector<int>> InvMat(std::vector<std::vector<int>> matrix)
{
	//Calculates the determinant
	int det = matrix[0][0]*(matrix[1][1]*matrix[2][2] - matrix[1][2]*matrix[2][1]);
	det += matrix[0][1]*(matrix[1][2]*matrix[2][0] - matrix[1][0]*matrix[2][2]);
	det += matrix[0][2]*(matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0]);
	
	det = det % 37; 
	
	if (det == 0) //Not invertible, return the input matrix to signal this
	{
		std::cerr << "Matrix is not invertible";
		
		return matrix;
	}
	
	//Extended Eulclidean Algorithm	
	int oldT = 0;
	int newT = 1;
	int oldR = 37;
	int newR = det;
	
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
		oldT += 37;
	
	det = oldT; //EEA of the determinant is the inverse of the determinant
	
	//Calculates the values for the output matrix
	std::vector<std::vector<int>> output(3, std::vector<int>(3,0));
	
	output[0][0] = ((matrix[1][1]*matrix[2][2] - matrix[1][2]*matrix[2][1])*det%37+37)%37;//(%37 + 37) % 37 so that the output will always be between 0 and 36
	output[0][1] = ((matrix[0][2]*matrix[2][1] - matrix[0][1]*matrix[2][2])*det%37+37)%37;
	output[0][2] = ((matrix[0][1]*matrix[1][2] - matrix[0][2]*matrix[1][1])*det%37+37)%37;
	output[1][0] = ((matrix[1][2]*matrix[2][0] - matrix[1][0]*matrix[2][2])*det%37+37)%37;
	output[1][1] = ((matrix[0][0]*matrix[2][2] - matrix[0][2]*matrix[2][0])*det%37+37)%37;
	output[1][2] = ((matrix[0][2]*matrix[1][0] - matrix[0][0]*matrix[1][2])*det%37+37)%37;
	output[2][0] = ((matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0])*det%37+37)%37;
	output[2][1] = ((matrix[0][1]*matrix[2][0] - matrix[0][0]*matrix[2][1])*det%37+37)%37;
	output[2][2] = ((matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0])*det%37+37)%37;
	
	return output;
}
