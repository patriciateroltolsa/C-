// Author: Patricia Terol

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define MAX_SIZE 5
using namespace std;

class matrix{
private:
	int** data;
	int rows, cols;

public:
	matrix();
	matrix(int rows, int cols);
	matrix operator+(matrix a);
	matrix operator-(matrix a);
	matrix operator-();
	matrix operator*(int c);
	matrix operator*(matrix a);
	friend ostream& operator<<(ostream& cout, matrix a);
	void fillMatrix(vector<string> input);
};


//Constructor to create the matrix information storage
matrix::matrix(){
	data = new int*[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++){
		data[i] = new int[MAX_SIZE];
	}
	rows = MAX_SIZE;
	cols = MAX_SIZE;
}

//Constructor to create the matrix information storage
matrix::matrix(int row, int col){
	rows = row;
	cols = col;
	data = new int*[rows];
	for (int i = 0; i < rows; i++){
		data[i] = new int[cols];
	}
}

//Function to add one matrix to another
inline matrix matrix::operator+(matrix a){
	matrix result(rows, cols);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			result.data[i][j] = data[i][j] + a.data[i][j];
		}
	}
	return result;
}

//Function to substract one matrix from another
inline matrix matrix::operator-(matrix a){
	matrix result(rows, cols);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			result.data[i][j] = data[i][j] - a.data[i][j];
		}
	}
	return result;
}

//Function to give the negative of a matrix
inline matrix matrix::operator-(){
	matrix result(rows, cols);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			result.data[i][j] = 0 - data[i][j];
		}
	}
	return result;
}

//Function to multiply a matrix by a constant value
inline matrix matrix::operator*(int c){
	matrix result(rows, cols);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			result.data[i][j] = data[i][j] * c;
		}
	}
	return result;
}

//Function to multiply two matrices together by using the dot product method
inline matrix matrix::operator*(matrix a){
	matrix result(rows, a.cols);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < a.cols; j++){
			int temp = 0;
			for (int z = 0; z < cols; z++){
				temp += (data[i][z] * a.data[z][j]);
			}
			result.data[i][j] = temp;
		}
	}
	return result;
}

//Function to print the matrix information on matrix format
inline ostream& operator<<(ostream& cout, matrix a){
	for (int i = 0; i < a.rows; i++){
		for (int j = 0; j < a.cols; j++){
			cout << a.data[i][j] << " ";
		}
		cout << endl;
	}
	return cout;
}

//Function to fill the matrix given some input information
inline void matrix::fillMatrix(vector<string> input){
	int found;
	int previous = 0;
	for (int i = 0; i < rows; i++){
		previous = 0;
		for (int j = 0; j < cols; j++){
			found = input[i].find(" ", previous);
			if (found == -1){
				found = input[i].size();
			}
			data[i][j] = atoi(input[i].substr(previous, found - previous).c_str());
			previous = found + 1;
		}
	}
}

//Method to check if the input is an operator
bool isOperator(string line){
	if (line == "+" || line == "-" || line == "*" || line == "<<"){
		return true;
	}
	return false;
}

//Method to get the amount of rows of the given input
int getRows(vector<string> input){
	return input.size();
}

//Method to get the amount of columns of the given input
int getCols(vector<string> input){
	int numbers = 1;
	for (unsigned int i = 0; i < input[0].size(); i++){
		if (input[0].substr(i, 1) == " "){
			numbers++;
		}
	}
	return numbers;
}

int main(int argc, char* argv[]){
	string line;
	bool first = true;
	bool second = false;
	string op;
	vector<string> firstInput;
	vector<string> secondInput;
	
	//Read from input file the matrix information and the operator
	ifstream input("matrix_input.txt");
	if (input.is_open()) {
		while (getline(input, line)) {
			if (isOperator(line)) {
				op = line;
				first = false;
			} else if(first){
				firstInput.push_back(line);
			} else {
				secondInput.push_back(line);
				second = true;
			}
		}

		input.close();
	}		
		
	//Create matrices based on the read information
	matrix firstMatrix(getRows(firstInput), getCols(firstInput));
	firstMatrix.fillMatrix(firstInput);
	int constant = -1;
	matrix secondMatrix(0,0);
	if (secondInput.size() == 0){

	} else if (getRows(secondInput) == 1 && getCols(secondInput) == 1){
		constant = atoi(secondInput[0].c_str());
	} else {
		secondMatrix = matrix(getRows(secondInput), getCols(secondInput));
		secondMatrix.fillMatrix(secondInput);
	}
	//Perform operation
	matrix result;
	if (op == "+"){
		result = firstMatrix + secondMatrix;
	} else if (op == "-"){
		if (second){
			result = firstMatrix - secondMatrix;
		} else {
			result =  - firstMatrix;
		}
	} else if (op == "*"){
		if (constant == -1){
			result = firstMatrix * secondMatrix;
		}
		else {
			result = firstMatrix * constant;
		}
	}
	//Print out the result
	cout << result;
}
