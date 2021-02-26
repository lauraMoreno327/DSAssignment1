

#include <iostream>;
#include <vector>;
using namespace std;
using std::cout;
using std::cin;



struct Val { // class that creates objects that have a key and a satellite data


public:
	
	string satelliteData;
	int key;
	
	Val(int key) { // constructor, sets key to key
	
		this->key = key;
	
	}
	//public functions (getters and setters) 
	int getKey() {
		return key;
	}
	string getSatelliteData() {
		return satelliteData;
	}
	
	void setSatelliteData(string sd) {
		satelliteData = sd;
	}
	

};

void directAddress(int max, vector<int> keys, vector<string>satelliteData, vector<int>searchKeys, int counter) { 
	int size = max + 1; // set size to max+1
	vector <string>directAddress(size,"/"); // creates vector called directAddress fo size max+1
	for (int i = 0; i <counter; ++i) {
		directAddress[keys.at(i)] = satelliteData.at(i); // stores satelliteData for respective key
	
	}
	

	for (int i = 0; i < searchKeys.size(); ++i) { // iterate through searchKeys

		if (searchKeys[i] > max) { // if searchKey is larger than max key, it does not exist
		
			cout << "*" << " "; // print astherisk
	}
		else if (directAddress[searchKeys.at(i)]=="/") { // if there is not a satelliteData associate to key, meaning directAddress(i) == "/"

			cout << "*" << " "; //print astherisk
		}

		else {
			cout << directAddress[searchKeys.at(i)] << " "; // else print satelliteData
		
		}

	}


}

int hashT(int key, int modulus) { // hash function

	return key% modulus; // returns modulus of respective input
}

bool isPrime(int n) // method to determine if a number is prime
{
	// Corner case 
	if (n <= 1)
		return false;

	// Check from 2 to n-1 
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return false;

	return true;
}

int main() {

	int task; //task
	vector<int>keys; // vector with keys used for direct address
	vector<string> satelliteData; // vector with satellite data used for direct adress
	vector<int>searchKeys; // vector with searchKeys
	vector<Val*> listObjects; // vector with objects used for hashing
	int key; // variable that will be use to read all keys inputs
	string var; // variable that will be use to read all sateliteData inputs
	int counter = 0; // counters used to iterate through list of objects and set the respective keys and satelliteData
	int counter1 = 0; //different iterators to complete reading process
	int max = 0; // varaible that will hold the max key in direct address method
	int searchKey; // variable to read in search keys
	int mod; // modulus
	int idx; 
	int idx2; // idx used in quadratic probing
	int size1;

	int printed = 0;
	bool isprime;

	

	while ((cin >> key)&& key >0) { // reads all keys ad stores them in a vector called keys 
	// while input is an integer and is bigger than  0
		keys.push_back(key);
	    Val* newVal = new Val(key); // creates a new objwct with every key and sets key to key
		listObjects.push_back(newVal);
		counter++; // increases counter
	}

	while ((cin >> var) && var !="*") { // reads all satellita Data and stores values in the vector called satellliteDAta
		satelliteData.push_back(var);
		listObjects[counter1]->setSatelliteData(var); // counter used to iterate through list of objects and set the satelliteData of each
		counter1++; // increase counter

	}
	cin >> task; // read task
	cin >> mod; // read modulus
	//size of hashTable with quadratic probe has to be greater than 2*size of input array
	int hashTable2size = (keys.size() * 2) + 1; 
	while (isPrime(hashTable2size) == false) { // loop to find next prime number 
		hashTable2size++;

	}




	while ((cin >> searchKey) && searchKey>0) { // reads all search keys and stores them in the vector call searchKeys
		searchKeys.push_back(searchKey);

	}
	vector<vector<Val*>> hashTable(mod); // 2D vector for separate chaining with size ==modulus
	vector <Val*> hashTable2(hashTable2size, NULL);// set's all slots to NULL
	vector<int> counters(mod, 0); // vector of counters for quadratic probing
	
	
	

	

	switch (task) {
	case 0://direct adress table
		//for loop to find the maxkey and therefore determine the size of the table 

		for (int i = 0; i < keys.size(); ++i) { // loop to find max keys to set the size of the direct address tab;e
			if (keys.at(i) > max) {
				max = keys.at(i);

			}
		}

		directAddress(max,keys,satelliteData,searchKeys,counter); // calls direct address method. Uses the vectors of keys, satelite data, searchKeys and max as input


		break;


	case 1: // separate chaining
		//using a 2D vector

		for (int i = 0; i < listObjects.size(); ++i) {// iterates through the list of objects 
			
			idx = hashT(listObjects[i]->getKey(), mod); // get's specific index through hash function
			hashTable[idx].push_back(listObjects[i]); // adds object to the vector in the specific index
		}
	

		for (int i = 0; i < searchKeys.size(); ++i) { // iterates through search keys
			printed = 0; // boolean that turns to one once a key is found
			
			idx = hashT(searchKeys[i], mod); // calculates new index
			size1 = hashTable[idx].size(); // get's size of the vector in that specific location
			if (size1 == 0) { // if vector is empty print, means the key does not exist
				cout << "*" << " "; // therefore print *
			}
			for (int j = 0; j < size1; ++j) { //else iterate throgu hthe horizontal vector
				if (hashTable[idx][j]->getKey() == searchKeys[i]) { // if found, print the satellite data
					cout << hashTable[idx][j]->getSatelliteData() << " ";
				
					printed = 1; // printed value becomes 1 
					
				}
				
			}
			//cout << printed;
			if (size1!=0 && printed == 0) { // if exits the for loop and printed is still 0, the search key does not exist and prints *
				cout << "*" << " ";
			}	
		
		}

		break;

	case 2:
		//insertion part with open addressing
		for (int i = 0; i < listObjects.size(); ++i) { // iterates through list of objects

			idx = hashT(listObjects[i]->getKey(), mod); // calculates new index
			if (hashTable2[idx] == NULL) { // if NULL, that specific slot in vector is empty. therfore add objec

				hashTable2[idx] = listObjects[i];
				counters[idx] ++; // increase counter
			}
			else {
				for (int xInsert = 1; xInsert < hashTable2.size(); xInsert++) {// while the slot if occupied
				
					idx2 = (idx + (xInsert * xInsert)) % hashTable2.size(); // update the index by quadratic probing , xInsert starts at one
					if (hashTable2[idx2] == NULL) { // if the slot at the new index is null

						hashTable2[idx2] = listObjects[i];// store value
						counters[idx]++;
						break; // break and continue with next object
					}
				
				
				}
			
			}
		
		}
	

		//search part
		for (int i = 0; i < searchKeys.size(); ++i) { // iterates through searchKeys
			printed = 0; // printed (found) starts at 0 for every key
		
		if (counters[hashT(searchKeys[i], mod)] == 0) { // if the counter of that specific position is zero, return astherisk because the key does not exist
			cout << "*" << " ";
			
		}
		
		else { //else
		
			for (int xSearch =0 ; xSearch < hashTable2.size(); xSearch++) {// updat index with quadratic probing method

				idx2 = (hashT(searchKeys[i], mod) + (xSearch * xSearch)) % hashTable2.size();// update the index by quadratic probing , xInsert starts at one
				
			if (hashTable2[idx2] == NULL) { // if it encounters a null, continue
				continue;
				}

				if (hashTable2[idx2]->getKey()==searchKeys[i]) { // if finds key, print it 
					cout << hashTable2[idx2]->getSatelliteData() << " ";
					printed = 1; // set printed to 1
					break;
					
				}	 
			}
			if (printed == 0 && counters[hashT(searchKeys[i], mod)] != 0) { //if exits for loop and printed is still 0, print astherisl 
			
				cout << "*" << " ";
			}
		}
		
		}
		break;


	}

		return 0;
}