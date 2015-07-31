// Author: Patricia Terol

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//Method to check if two strings are the same regardless of uppercase or lowercase
bool compareWords(string first, string second){
	if (first.size() != second.size()){
		return false;
	} 
	for (unsigned int i = 0; i < first.size(); i++){
		if (!(first.at(i) == second.at(i) || first.at(i) - 32 == second.at(i) || second.at(i) - 32 == first.at(i))){
			return false;
		}
	}
	return true;
}

//Method to delete the punctuation attached to words
vector<string> deletePunctuation(vector<string> input){
	for (unsigned int i = 0; i < input.size(); i++){
		while (true){
			int size = input.at(i).size();
			char* word = (char*)input.at(i).c_str();
			if (!((word[0] >= 'A' && word[0] <= 'Z') || (word[0] >= 'a' && word[0] <= 'z') || (word[0] >= '0' && word[0] <= '9'))){
				if (!((word[size - 1] >= 'A' && word[size - 1] <= 'Z') || (word[size - 1] >= 'a' && word[size - 1] <= 'z') || (word[size - 1] >= '0' && word[size - 1] <= '9'))){
					//Delete both punctuation at the beggining and end of the word
					input.at(i) = input.at(i).substr(1, size - 1);
				}
				else {
					//Delete punctuation only at the beggining of the word
					input.at(i) = input.at(i).substr(1, size);
				}
			}
			else {
				if (!((word[size - 1] >= 'A' && word[size - 1] <= 'Z') || (word[size - 1] >= 'a' && word[size - 1] <= 'z') || (word[size - 1] >= '0' && word[size - 1] <= '9'))){
					//Delete punctuation only at the end of a word
					input.at(i) = input.at(i).substr(0, size - 1);
				}
				else {
					break;
				}
			}
		}
	}
	return input;
}

//Method to define the sorting method
bool sortCompare(string one, string two){
	transform(one.begin(), one.end(), one.begin(), ::tolower);
	transform(two.begin(), two.end(), two.begin(), ::tolower);
	return one < two;
}

//Method to organize the input alphabetically
vector<string> organizeInput(vector<string> input){
	sort(input.begin(), input.end(), sortCompare);
	return input;
}

//Method to count the total amount of words in the input
int getTotalWords(vector<string> input){
	return input.size();
}

//Method to count the amount of unique words within the file(not counting repetitions)
int getUniqueWords(vector<string> input){
	if (input.size() == 0) return 0;
	int count = 1; 
	for (unsigned int i = 1; i < input.size()- 1; i++){
		if (!compareWords(input.at(i), input.at(i-1))){
			count++;
		}
	}
	if (!compareWords(input.at(input.size() - 1),input.at(input.size() - 2))){
		count++;
	}
	return count;
}

//Method to find the most frequent word used in the input
string getMostFrequent(vector<string> input){
	if (input.size() == 0) return "";
	//Initialize all values to the first word
	string frequentWord = input.at(0);
	string currentWord = input.at(0);
	int frequency = 1;
	int currentCount = 1;

	for (unsigned int i = 1; i < input.size(); i++){
		if (input.at(i) != input.at(i - 1)){
			//Check if the last group of words was more frequent the the top stored one
			//If so, change the most frequent to the new data
			if (currentCount > frequency){
				frequency = currentCount;
				frequentWord = currentWord;
			}
			//Start a new group of words
			currentWord = input.at(i);
			currentCount = 1;
		}
		else {
			//Add a new word to the current frequency
			currentCount++;
		}
	}
	//Check if the last group is bigger in frequency
	if (currentCount > frequency){
		frequency = currentCount;
		frequentWord = currentWord;
	}
	return frequentWord;
}

//Method to calculate the lexical density
double getLexicalDensity(int totalWords, int uniqueWords){
	return (double) (uniqueWords * 100.0) / totalWords;
}

//Method to print the list of words in the input alphabetically
void printAlphabeticalInput(vector<string> input){
	if (input.size() == 0){
		return;
	}
	for (unsigned int i = 0; i < input.size(); i++){
		cout << input.at(i) << " ";
	}
	return;
}

int main()
{
	vector<string> input;

	//Read the input and store it
	ifstream fileReader("assign09_input.txt");
	string currentWord;
	while (fileReader >> currentWord){
		input.push_back(currentWord);
	}

	//Delete the punctuation and sort it aphabetically
	input = deletePunctuation(input);
	input = organizeInput(input);

	//Print titles
	cout << "Patricia Terol - CSE 2050 assignment 9" << endl;
	cout << "WORDS R US" << endl;

	//Print results of stats for input
	cout << "Number of words: " << getTotalWords(input) << endl;
	cout << "Number of unique words: " << getUniqueWords(input) << endl;
	cout << "Most frequent word: " << getMostFrequent(input) << endl;
	cout << "Lexical density: " << getLexicalDensity(getTotalWords(input), getUniqueWords(input)) << endl;
	cout << "Input, alphabetically: ";
	printAlphabeticalInput(input);
	cout << endl;

	return 0;
}

