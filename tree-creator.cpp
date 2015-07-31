//Author: Patricia Terol

#include <string>
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class tree{

protected:
	class node {
	public:
		node(T input);
		T data;
	protected:
		node* right;
		node* left;
		friend class tree<T>;
		friend class summaryTree;
	};

public:
	friend class summaryTree;
	node* root;
	int size;
	void a(T input);
	void p();
	bool s(T name);
	void tearDown(node *currentNode);
	void operator+(T input);
	friend ostream& operator<<(ostream& out, tree t);
	tree();
	~tree();
private:

	void a(T input, node *&currentNode);
	void p(node *currentNode);
	bool s(T input, node *currentNode);
	void p(ostream &out, node* currentNode);
};

// Constructor for the node.
template<typename T>
tree<T>::node::node(T input){
	data = input;
	right = NULL;
	left = NULL;
}

// Constructor for the tree.
template<typename T>
tree<T>::tree(){
	root = NULL;
}

// Call teardown which takes
// care of the tree's memory
// deallocation.
template<typename T>
tree<T>::~tree(){
	cout << "inside" << endl;
	tearDown(root);
}

// Deallocate the memory of each node
// in the tree.
template<typename T>
void tree<T>::tearDown(node *currentNode){
	if (currentNode == NULL) return;
	p(currentNode->left);
	p(currentNode->right);
	delete(currentNode);
}

// Overloading + operator.
template<typename T>
void tree<T>::operator+(T input){
	a(input);
}

// Overloading << operator.
template<typename T>
inline ostream& operator<<(std::ostream& out, tree<T> t){
	if (root == NULL){
		out << "Empty tree!" << endl;
	}
	else {
		p(out, root);
		cout << endl;
	}

	return out;
}

// Call the overloaded version of this
// function to add a node to the tree.
template<typename T>
void tree<T>::a(T input){
	a(input, root);
	size++;
}

// Add the node to the tree.
// If the tree contains the node already,
// it will not be added.
template<typename T>
void tree<T>::a(T input, node *&currentNode){
	if (currentNode == NULL){
		currentNode = new node(input);
		return;
	}
	if (currentNode->data == input){
		size--;
		return;
	}
	if (currentNode->data < input){
		a(input, currentNode->right);
	}
	else {
		a(input, currentNode->left);
	}
}

// If the tree is empty,
// let the user know. Otherwise
// call the overloaded version
// of this function to take care
// of printing.
template<typename T>
void tree<T>::p(){
	if (root == NULL){
		cout << "Empty tree!" << endl;
	}
	else {
		p(root);
		cout << endl;
	}
}

// Print all of the values in the tree.
template<typename T>
void tree<T>::p(node* currentNode){
	if (currentNode == NULL) return;
	p(currentNode->left);
	cout << currentNode->data << " ";
	p(currentNode->right);
}

// Used for the overloading of the << operator.
template<typename T>
void tree<T>::p(ostream &out, node* currentNode){
	if (currentNode == NULL) return;
	p(currentNode->left);
	out << currentNode->data << " ";
	p(currentNode->right);
}

// Will call the overloaded version of
// this function. A message will be printed
// to let the user if it was found or not.
template<typename T>
bool tree<T>::s(T input){
	if (s(input, root)){
		cout << "Found!" << endl;
		return true;
	}
	else {
		cout << "Not found!" << endl;
		return false;
	}
}

// Search through the tree for the data specified.
// If found return true, otherwise return false.
template<typename T>
bool tree<T>::s(T input, node *currentNode){
	if (currentNode == NULL){
		return false;
	}
	else if (currentNode->data == input) return true;
	if (currentNode->data < input){
		return s(input, currentNode->right);
	}
	else {
		return s(input, currentNode->left);
	}
}

class summaryTree : public tree<string> {
private:
	vector<string> t(tree<string>::node *currentNode, vector<string> &top5, int limit);
	vector<string> b(tree<string>::node *currentNode, vector<string> &bottom5, int limit);
public:
	void t();
	void b();

};


// Calls the overloaded version of
// this function. The values from that
// function will be printed out.
void summaryTree::t(){
	vector<string> top5;

	if (size == 0){
		cout << "Empty tree!" << endl;
		return;
	}

	if (size > 5){
		top5 = t(root, top5, 5);
		for (int i = 4; i >= 1; i--){
			cout << top5.at(i) << " ";
		}
		cout << top5.at(0) << endl;
	}
	else {
		top5 = t(root, top5, size);
		for (int i = size - 1; i >= 1; i--){
			cout << top5.at(i) << " ";
		}
		cout << top5.at(0) << endl;
	}
}

// Calls the overloaded version of
// this function. The values from that
// function will be printed out.
void summaryTree::b(){
	vector<string> bottom5;

	if (size == 0){
		cout << "Empty tree!" << endl;
		return;
	}

	if (size > 5){
		bottom5 = b(root, bottom5, 5);
		for (int i = 0; i < 4; i++){
			cout << bottom5.at(i) << " ";
		}
		cout << bottom5.at(4) << endl;
	}
	else {
		bottom5 = b(root, bottom5, size);
		for (int i = 0; i < size - 1; i++){
			cout << bottom5.at(i) << " ";
		}
		cout << bottom5.at(size - 1) << endl;
	}

}

// Finds the top five numbers of the tree.
vector<string> summaryTree::t(tree::node *currentNode, vector<string> &top5, int limit){
	if (currentNode == NULL) return top5;
	if (top5.size() == limit) return top5;
	t(currentNode->right, top5, limit);
	top5.push_back(currentNode->data);
	t(currentNode->left, top5, limit);
	return top5;
}

// Finds the bottom five numbers of the tree.
vector<string> summaryTree::b(tree::node *currentNode, vector<string> &bottom5, int limit){
	if (currentNode == NULL) return bottom5;
	if (bottom5.size() == limit) return bottom5;
	b(currentNode->left, bottom5, limit);
	bottom5.push_back(currentNode->data);
	b(currentNode->right, bottom5, limit);
	return bottom5;
}

// Removes spaces from the beginning and
// end of the string.
void trimString(string &input){
	while (true){
		if (input == ""){
			return;
		}

		if (input[0] == ' '){
			input = input.substr(1);
		}
		else{
			break;
		}
	}


	while (true){
		if (input == ""){
			return;
		}

		if (input[input.length() - 1] == ' '){
			input = input.substr(0, input.length() - 1);
		}
		else{
			break;
		}
	}
}

// Takes care of special cases where the
// user input is invalid.
bool isInvalidInput(string &command){
	trimString(command);

	if (command.length() < 3 && command[0] != 'p' && command[0] != 't' && command[0] != 'q' && command[0] != 'b'){
		return true;
	}

	if ((command[0] == 'p' || command[0] == 't' || command[0] == 'q' || command[0] == 'b') && command.length() > 1){
		return true;
	}

	return false;
}

int main(){
	cout << "Patricia Terol - CSE 2050 assignment 7" << endl;
	cout << "PREPARE FOR EXCITEMENT!" << endl;
	string command = "";
	summaryTree *myTree = new summaryTree();

	while (true){
		cout << "$Command: ";
		getline(cin, command);

		if (isInvalidInput(command)){
			cout << "Wrong input, please enter again. " << endl;
			continue;
		}

		if (command == "q"){
			break;
		}
		else if (command == "p"){
			myTree->p();
		}
		else if (command == "t"){
			myTree->t();
		}
		else if (command == "b"){
			myTree->b();
		}
		else if (command.at(0) == 'a'){
			myTree->a(command.substr(2));
		}
		else if (command.at(0) == 's'){
			myTree->s(command.substr(2));
		}
		else {
			cout << "Wrong input, please enter again. " << endl;
		}
	}
	cout << "Have a great day!" << endl;
}
