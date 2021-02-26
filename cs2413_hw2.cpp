#include <iostream>;
using namespace std;
using std::cout;
using std::cin;



class Course {


private:
	int capacity;//private memeer
	Course* prev;
	Course* next;
public:
	Course() {//default constructor
		this->capacity = 0;
		Course* prev = nullptr;
		Course* next = nullptr;

	}
	Course(int x) {//constructor with capacity as parameter
		capacity = x;
		Course* prev = nullptr;
		Course* next = nullptr;

	}
	//public functions (getters and setters) to access private members
	int getCapacity() {
		return capacity;
	}
	Course* getPrev() {
		return prev;
	}
	Course* getNext() {
		return next;
	}
	void setPrev(Course* x) {
		prev = x;
	}
	void setNext(Course* x) {
		next = x;
	}


};

//class used to store Course objets and create the doubly linked list
class DoublyLinkedList {
private://private member
	int size;
	Course* head;// head and tail are pointers that will be used to traverse the list
	Course* tail;

public:
	DoublyLinkedList() {//default constructor
		this->size = 0;
		this->head = nullptr;
		this->tail = nullptr;
	}
	////public functions (getters and setters) to access private members
	void setSize(int x) {
		size = x;
	}
	int getSize() {
		return size;
	}

	Course* getHead() {
		return head;
	}
	Course* getTail() {
		return tail;
	}



	//method that is called everytime a new course object is created. Ever new eleemtn is added to the end of the list
	void addAtEnd(Course* newCourse) {
		if (tail != NULL) {
			tail->setNext(newCourse);
			newCourse->setPrev(tail);
			tail = newCourse;//tail is uupdated every time a new element is added
			tail->setNext(NULL);


		}
		else {
			newCourse->setPrev(NULL);// x will be the head, and so it's previous goes to null
			head = newCourse;//as there are no previous elements. Both, head andtail point to x. 
			tail = newCourse;

		}

	}
	Course* middleNode(Course* head, Course* tail) {
		//traversing the link from the front and from the back
		//idea is to return the spot that is being pointed at by head and by tail at the same time
		//

		while (head!=NULL && tail!=NULL) {
			if (head->getCapacity() == tail->getCapacity()) {
				return head;
			}
			head = head->getNext();
			if (head->getCapacity() == tail->getCapacity()) {
				return head;
			}

			tail = tail->getPrev();
		}
	
}



	int binarySearch(Course* head, Course* tail, int searchKey) { //binary search returns an int value. -1 when element is not found and value of element when it is
	//calls method to find middle position every time
		Course* currentMiddle = middleNode(head, tail);
	

		//condition to stop
		if ((head->getCapacity() == tail->getCapacity())&&(head->getCapacity()!=searchKey)) {
			return -1;
		}


		if (currentMiddle->getCapacity() == searchKey) {
			return currentMiddle->getCapacity();
		}
		else if (currentMiddle->getCapacity() > searchKey) {
			binarySearch(head, currentMiddle->getPrev(), searchKey);
		}
		else if (currentMiddle->getCapacity() < searchKey) {
			binarySearch(currentMiddle->getNext(), tail, searchKey);
		}
		else
		{
			return -1;
		}
	}

	void delete2(int position) {
		int counter = 0;
		Course* current = head;
		if (position == 0) {
			head = head->getNext();
			size--;

		}
		if (position == size - 1) {
			tail = tail->getPrev();
			size--;

		}
		// when position is not head nor tail, we use the current pointer to iterate through the list. Once counter equals the position, the pointers are shifted
		while (current != NULL) {

			if (counter == position) {
				current->getPrev()->setNext(current->getNext());
				current->getNext()->setPrev(current->getPrev());
				size--;
			}
			counter++;
			current = current->getNext();
		}

		//piece of code to display the resulting list
		Course* toDisplay = head;
		while (toDisplay != NULL) {

			cout << toDisplay->getCapacity() << " ";
			toDisplay = toDisplay->getNext();
		}
	}





	void addNode(int searchKey) {
		Course* newNode = new Course(searchKey);
		if (newNode->getCapacity() < head->getCapacity()) {//when new value is less than value of head, new value becomes new head
			head->setPrev(newNode);
			newNode->setNext(head);
			head = newNode;

		}
		if (newNode->getCapacity() > tail->getCapacity()) {//when new value is more than value of tail, new value becomes new tail
			newNode->setPrev(tail);
			tail->setNext(newNode);
			tail = newNode;

		}
		//else, a temp pointer is used to traverse the list. 
		else {
			Course* temp = head->getNext();
			while (temp != NULL) {

				if ((temp->getPrev()->getCapacity() < searchKey) && (temp->getCapacity() > searchKey)) {//if prev of temp<key and temp>key, we have to insert key bw prev of temp and temp
					newNode->setPrev(temp->getPrev());
					newNode->setNext(temp);
					temp->getPrev()->setNext(newNode);


				}

				temp = temp->getNext();
			}

		}

		//piece of code to display result list
		Course* current = head;
		while (current != NULL) {
			cout << current->getCapacity() << " ";
			current = current->getNext();
		}

	}


};


int main() {
	//declaration and creationg of list
	DoublyLinkedList* list = new DoublyLinkedList();
	//reading and assigning values to task and searchKey
	int task, searchKey;
	cin >> task;
	cin >> searchKey;
	int capacity;
	//length will be used to determine the size of the list
	int length = 0;
	//read until you come across a non integer value
	while (cin >> capacity) {
		//create a new course object with every value
		Course* newCourse = new Course(capacity);
		list->addAtEnd(newCourse);//add them to list
		length += 1;//increase length
		list->setSize(length);//update size every time one element is added

	}

	int position = 0;//used as a counter. Will be updated with every iteration of the while loop. Will be outputted when temp.getCapacity equals value of y
	int y = list->binarySearch(list->getHead(), list->getTail(), searchKey); // y hold either -1 or the value of searchKey
	Course* temp = list->getHead();//pointer to traverse the link 


	switch (task) {
	case 0:

		if (y < 0) {
			// y is -1 when element is not found in list
			cout << y;
		}

		else {

			while (position < list->getSize()) {//pointer p and the variable of position are used to traverse the list until temp.getCapacity() equals the return value of binary search, in this case y
				if (temp->getCapacity() == y) {
					cout << position;
				}

				temp = temp->getNext();
				position++;
			}
		}

		break;

	case 1:
		if (y < 0) {

			list->addNode(searchKey);// as y -1, we want to add the searchKey
		}
		else {

			while (position < list->getSize()) {
				if (temp->getCapacity() == y) {

					list->delete2(position);// position of the node with capacity that equalssearchKey
				}

				temp = temp->getNext();
				position++;
			}

		}

		break;

	}


		return 0;
}