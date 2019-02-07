#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Error, please input one positive integer N as argument" << endl;
		return 1;
	}
	int N = atoi(argv[1]);

	clock_t tstart;
	tstart = clock();

	int* arr = new int [N];
	srand (time(NULL));

	for (int i = 0; i < N; i++) {
		int temp = rand() % 1000 + 1;
		arr[i] = temp;
	}

	unsigned long sum = 0;
	int largest = 0;

	for (int i = 0; i < N; i++) {
		sum += arr[i];
		if(arr[i] > largest) {
			largest = arr[i];
		}
	}

	delete[] arr;
	
	cout << "Time Elapsed: " << (double)(clock() - tstart)/CLOCKS_PER_SEC << endl;
	cout << "Maximum: " << largest << "; Sum: " << sum << endl;
	return 0;
}
