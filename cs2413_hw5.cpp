
#include <iostream>;
#include <vector>;
//#include <stack>;

using namespace std;
//using std::cout;
//using std::cin;
#define SIZE 1000



struct Node { // class that creates objects that have a key and a satellite data


public:

	int data ;
	Node* leftChild = nullptr; 
	Node* rightChild = nullptr;
	int isVisited = 0;


	Node(int data) { // constructor, sets key to key
		//sets children to null
		this->data = data;
		leftChild = nullptr;
	    rightChild = nullptr;
		isVisited = 0; 
		

	}
	//public functions (getters and setters) 
	int getData() {
		return data;
	}
	int getFlag() {
		return isVisited;
	}
	Node* getLeftChild() {
		return leftChild;
	}

	Node* getRightChild() {
		return rightChild;
	}
	
	void setFlag(int x) {
		isVisited = x;
	}

	void setLeftChild(Node* lc) {
		leftChild = lc;
	}
	void setRightChild(Node* rc) {
		rightChild = rc;
	}


};

class Stack
{
	int topElement = 0; // variaable to refer to the index of the stack

public:
	Node* myStack[SIZE] = {};

	
	Stack() { // constructor
		topElement = -1; //initialized topElemnt to -1, this way index (topElement) is dragged to the bottom of the stack and user is able to start adding on top of the previous elemnent
	}

	bool isEmpty(); // checks if stack is empty
	void push(Node* node); // adds new element to the stack
	Node* pop(); // will pop the top element in the stack
	Node* top(); // will return the top element in the stack

};

bool Stack::isEmpty() {

	return(topElement < 0); // if top Element remains -1, return true
}

void Stack::push(Node* node) {

	if (topElement >= (SIZE - 1)) { // if topElement exceeds size defined at the beginning
		cout << "Stack is full"; // warn user by prompting a message
		
	}
	else {
		myStack[++topElement] = node; // else add node to stack
	}
}
Node* Stack::pop() { // method that gets rid of top element in the stack

	if (isEmpty()) { 
		cout << "Stack is empty";
		//exit(EXIT_FAILURE);
		return 0;
	}
	else {
		return myStack[topElement--]; // 
	}

}

Node* Stack::top() { // method that returns the top element in the stack

	if(!isEmpty()){ // while stack is not empty
		return myStack[topElement]; // return top element in stack
	}

	else {
		//exit(EXIT_FAILURE);
		return 0;
	}
}



void enumerate(Node* root) { // uses two stacks
	
	if (root == NULL) {
		return;
	
	}
	Stack  stack1;
	Stack  stack2; // stack 2 will hold the elements in the correct order of enumeration
	//stack stack1;
	//stack stack2;

	stack1.push(root); // pishes head to stack 1 

	Node* temp;
	//cout << "reaches here";
	while (!stack1.isEmpty()) { // while stack 1 contains at least one element
		//cout << "reaches here";
		temp = stack1.top();
		stack1.pop();
		stack2.push(temp);
		if (temp->getLeftChild()!=nullptr) { // left child is stored before right child
			stack1.push(temp->getLeftChild()); // left child is stored in stack1
		}

		if (temp->getRightChild()!=nullptr) { // right child is stored in stack2
			stack1.push(temp->getRightChild());
		}
	}
	//cout << "reaches here";
	while (!stack2.isEmpty()) { // while stack 2 is not empty
		temp = stack2.top(); //cout data inside topElemnt
		cout << temp->getData() << " ";
		stack2.pop(); // pop Element that was recently displayed

	}
};

void insertInTree(Node* node, int key) { // method that builds the BST initially
	
	// all keys start comparissons with root and move down the tree accordingly

		if (key < node->getData()&&node->getLeftChild()==nullptr) { // if key is less than node, and left child of node is empty
			Node* temp = new Node(key); //set node of key as left child of node
			node->setLeftChild(temp);
		
		}

		else if (key > node->getData() && node->getRightChild() == nullptr) {// if key is larger than node and right child of node is empty
			Node* temp = new Node(key); // set node of key as right child of node
			node->setRightChild(temp);
			
		}
		else if (key < node->getData() && node->getLeftChild() != nullptr) {  // if key is less than node,  but left child of node is not empty

			insertInTree(node->getLeftChild(), key); // call method again with left child being main node

		}

		else if (key > node->getData() && node->getRightChild() != nullptr) {// if key is larger than node,  but right child of node is not empty
		
			insertInTree(node->getRightChild(), key); // call method again with right child being main node
		}
	
	
	}


void searchInTree(Node* root, int key, Node* head) {

	if (root->getData() == key) { // is key was found
	//	cout << "Supposed to enumerate";
		enumerate(head);// call enuerate method
		
	}
	if (root->getRightChild() == nullptr && root->getLeftChild() == nullptr && root->getData()!=key) { // if data is not equal to key and node is a leaf
	
		cout << -1; // return -1
	}

	else if (key > root->getData()) { // if key is more than node
	
		searchInTree(root->getRightChild(), key, head); // call method again with right child
	}
	else if (key < root->getData()) { //if opposite case

		searchInTree(root->getLeftChild(), key, head); // call method with left child
	}


}


void  insertion(Node* root, int key, Node* head) { // method to add a new node to the BST

	if (root->getData() == key) { // if node already exists

		cout << -1;// return -1
	}
	else if (key > root->getData() && root->getRightChild() == nullptr) { // if key is greater than node and node has no right child
		Node* temp = new Node(key); // set node of new  key as right child of node
		root->setRightChild(temp);
		enumerate(head); // call enumerate method
	
	}
	else if (key < root->getData() && root->getLeftChild() == nullptr) {// if key is less than node and node has no left child
		Node* temp = new Node(key); // set node of new  key as left child of node
		root->setLeftChild(temp);
		enumerate(head); // call enumerate method


	}
	else if (key > root->getData()) { // if key is greater than node and node has a right child

		insertion(root->getRightChild(), key, head); // call method again with right child
	}
	else if (key < root->getData()) {// if key is less than node and node has a left child

		insertion(root->getLeftChild(), key, head); // call method again with left child
	}

}



int main() {
	int key;
	vector <int> keys; // vector that stores all keys input
	vector <int> keys2; // used in deletion method
	Node* root = NULL; // iterator that starts at head
	Node* head = NULL; // node that stays constant and contains the adress of the root of the tree
	int task ; // task
	int searchKey ; // searchKey
	int isFound = 0; // used in deletion method
	Node* anotherNode; // used in deletion method


	while (cin >> key) {//reading in keys and storing them in a vector
		keys.push_back(key);
		if (root == NULL) {// if it is the first value to implement
			Node* currentNode = new Node(key);
			root = currentNode; // root becomes first input 
			head = currentNode; // head becomes and stays as first key input
			
		}

		else {
			insertInTree(root, key); // construct tree key by key
		}
			
		
	}

 cin.clear();
	cin.ignore(2, '\n');
	cin >> task; // read in task
	cin >> searchKey; // read in searchKey


	switch (task) {
	
	
	
	case 1:
		searchInTree(root,searchKey, head); // call method to search Key

		break;

	case 2:
	
		insertion(root, searchKey, head); // call method to insert Key

		break;


	case 3:
		for (int i = 0; i < keys.size(); ++i) { // iterate through vector of keys
			if (keys[i] == searchKey) { // if key to delete is found
				isFound = 1;// assign true to is Found
				continue; // skip that value
			}
			keys2.push_back(keys[i]); // copy elements of original vetor into new vector wirhout the key to delete
		}
	
		root = NULL; // set root to NULL
	//	cout << isFound;
		if (isFound == 1) { // is key was found and we want to delete it
			for (int i = 0; i < keys2.size(); ++i) { // iterate through updated vector of keys
				if (root == NULL) {// if it is the first value to implement
					anotherNode = new Node(keys2[i]);
					root = anotherNode; // assign first value to root
				}

				else {
					insertInTree(root, keys2[i]); // call method to construct updated BST
				}
			}
			enumerate(root);
			
		}
		else { // else if key to delete does not exist
			cout << -1; // print -1
		
		}

		break;
	
	}

	return 0;

}



