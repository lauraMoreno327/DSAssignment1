#include <iostream>
using namespace std;
int main() {

	
	//hardcode matrix y 
	int array_y[5][8] = { {1,0,0,9,0,5,0,0},
						  {0,0,0,0,2,0,0,3},
						  {0,4,0,0,0,0,8,0},
						  {0,0,2,0,0,0,0,0},
						  {1,0,0,0,7,0,0,0}, };

	

	
	//variables I will use to read in and populate matrix x

	int row, column, value, task, nonZeroVals;
	
	cin >> task >> nonZeroVals;
	//cout << task << "\n";
	//cout << nonZeroVals<< "\n";
	
	
	int x[5][8] = { 0 };//setting all values to 0 at first
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 8; j++)
		{
			cin >> row;
			cin >> column;  //reading every 3 values
			cin >> value;
			x[row][column] = value;
			

		}
	}



	//counters I use in transposing and multiplication procedures respectively
	int k = 0;
	int u = 0;
	int size = 0;
	

	switch (task) {
	case 1:
		int z1[8][5];

		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 8; ++j) {
				z1[j][i] = x[i][j];
			}
		}
	
	
//converting sparse matrix to effective representation matrix
		int z1f[30][3];//I use a big constant for # of rows, since the array is static
		while (k < nonZeroVals) {//k functions as a counter to make sure i only transfer (nonZeroVals( number of values 
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 5; j++) {
					if (z1[i][j] != 0)
					{
						z1f[k][0] = i;
						z1f[k][1] = j;
						z1f[k][2] = z1[i][j];
						k++;
					}
				}
			}
		}
//printing out values
		for (int i = 0; i < nonZeroVals; i++) {
			for (int j = 0; j < 3; j++) {
				if ( i == nonZeroVals -1&&(j==2)) {
					cout << z1f[i][j];  //if condition to make sure last value does not print a blanck space after
				}
				else {
					cout << z1f[i][j] << " ";
				}

			}

		}


		break;

	case 2:

		//declaring a new 2d array with same dimensions
		int z2[5][8];
		//loop to sum the values that are in the same position
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 8; j++) {

				z2[i][j] = x[i][j] + array_y[i][j];

			}

		}

		//finding non-Zero values
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 8; j++) {

				if (z2[i][j] != 0) {
					size++;
				}

			}

		}

		//converting sparse matrix to effective representation matrix
		int z2f[30][3];//I use a big constant for # of rows, since the array is static
		while (k < size) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 8; j++) {
					if (z2[i][j] != 0)
					{
						z2f[k][0] = i;
						z2f[k][1] = j;
						z2f[k][2] = z2[i][j];
						k++;
					}
				}
			}
		}

		//printing out final values
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < 3; j++) {

				if (i == size - 1 && (j == 2)) {
					cout << z2f[i][j];  //if condition to make sure last value does not print a blanck space after
				}
				else {
					cout << z2f[i][j] << " ";
				}


			}

		}


		break;


	case 3:
		int z4[8][5];//z4 will be the transpose of x
		//transposing first using x
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 8; ++j) {
				z4[j][i] = x[i][j];
			}
		}

		int z3[8][8] = { 0 }; //initializing all values to 0


		//multiplying both matrices 
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				for (k = 0; k < 5; ++k)
				{
					z3[i][j] += z4[i][k] * array_y[k][j];//stroing the result in z3
				}
			}
		}

		//finding non-Zero values
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {

				if (z3[i][j] != 0) {
					size++;
				}

			}

		}
		
		//populating effective representation form
		int z3f[40][3];
		while (u < size) {//u has the same function as k, but I gave it a different nsme given that I wrote all my code within the same function main()
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (z3[i][j] != 0)
					{
						z3f[u][0] = i;
						z3f[u][1] = j;
						z3f[u][2] = z3[i][j];
						u++;
					}
				}
			}
		}
		//printing output
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < 3; j++) {

				if (i == size - 1 && (j == 2)) {
					cout << z3f[i][j];  //if condition to make sure last value does not print a blanck space after
				}
				else {
					cout << z3f[i][j] << " ";
				}


			}

		}



		break;


	}
	return 0;
}