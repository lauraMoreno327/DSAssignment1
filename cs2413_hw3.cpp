
#include <iostream>;
#include <vector>;
using namespace std;
using std::cout;
using std::cin;


struct currentValue {

	int val;
	struct currentValue* next;

	void setNext(currentValue* temp) {
		next = temp;
	}

};

class SinglyLinkedList {

private:

	int size;
	currentValue* head;
	currentValue* tail;

public:
	SinglyLinkedList()
	{
		this->size = 0;
		this->head = nullptr;
		this->tail = nullptr;
	
	}

	void setSize(int x) {
		size = x;
	}
	int getSize() {
		return size;
	}
	currentValue* getHead() {
		return head;
	}



void addAtEnd(int value){//method to insert new values to the list
	currentValue* temp = new currentValue;
	temp->val = value;
	temp->next = NULL;

	if (head != NULL) {// when list already contains some values
		tail->setNext(temp);
		tail = temp;
	
	}
	else {//for first element added == list is empty
		head = temp;
		tail = temp;
	
	}
	}

void swapNodes(currentValue* first, currentValue* second) {//mehod called by bubble sort
	int temp = first->val;
	first->val = second->val;
	second->val = temp;

}

void bubbleSort(currentValue* temp) { 
	for (int i = 0; i < size; i++) {//bubble sort has list.length number of iterations
		temp = head;//always go bck to head for to start a new iteration

		while (temp != NULL &&(temp->next!=NULL)) {
			
			if (temp->next->val > temp->val) {

				swapNodes(temp, temp->next);
			}

			temp = temp->next;

		}
	}
	//while loop to print out the list
	currentValue* x = head;
	while (x != NULL) {
		cout << x->val<<" ";
		x = x->next;
	
	}

}
};

void swap(int* first, int* second) {

	int temp = *first;
	*first = *second;
	*second = temp;


}

vector<int> selectionSort(vector<int> list) {//method called by merge
	int largest, maxIndex,temp = 0;
	for (int i = 0; i < list.size() ; ++i) {
		largest = list.at(i);
		maxIndex = i;
		for (int j = i; j < list.size(); ++j) {//finding largest value
			if (list.at(j) > largest) {
				largest = list.at(j);
				maxIndex = j;
			
			}
		
		}
		if (largest > list.at(i)) {//code to swap larger value with first element if needed
			temp = list.at(i);
			list.at(i) = list.at(maxIndex);
			list.at(maxIndex) = temp;
		}

	}

	return list;
}

void mergeSort(vector<int> list) {
	vector<int>subList1;
	vector<int>subList2;
	int largest;


	for (int i = 0; i < list.size(); ++i) {
		int size =  list.size() / 2;//find value in middle location
		if (i <= size - 1) {//assign all values before the middle location to the first list
			subList1.push_back(list.at(i));
		
		}
		else {//all those after the middle, are assigned to the second list
			subList2.push_back(list.at(i));
		}
	
	
	}

	subList1= selectionSort(subList1);//apply selection sort on both
	subList2=selectionSort(subList2);


	int firstLength = subList1.size();
	int secondLength = subList2.size();
	vector<int>finalList(firstLength + secondLength);//new list of size of sublist1 + subList2
	int x = 0;
	int y = 0;
	int z = 0;
	while (x < firstLength && y < secondLength)
	{
		if (subList1.at(x) > subList2.at(y)) {
			finalList.at(z) = subList1.at(x);
			x++;
			z++;


		}
		else {
			finalList.at(z) = subList2.at(y);
			y++;
			z++;
		}
	}

	while (x < subList1.size()) {
		finalList.at(z++) = subList1.at(x++);
	
	}

	while (y < subList2.size()) {
		finalList.at(z++) = subList2.at(y++);

	}
	//print final vector
	for (int i = 0; i < finalList.size(); ++i) {
		cout << finalList.at(i) << " ";
	}

}



int main(){

	int task;
	cin >> task;

	int capacity;//current value
	SinglyLinkedList* list = new SinglyLinkedList();
	vector<int> numbers;
	int length = 0;

	switch(task){
	
	case 0 ://uses single linked list for bubbly sort
	
		//read until you come across a non integer value
		while (cin >> capacity) {

			list->addAtEnd(capacity);//add item to t
			length += 1;//increase length
			list->setSize(length);//update size every time one element is added

		}
		list->bubbleSort(list->getHead());


		break;


	case 1://uses vectors for merge sort
		while (cin >> capacity) {

			numbers.push_back(capacity);

		}
		mergeSort(numbers);





		break;
	}
	


	return 0;
}
