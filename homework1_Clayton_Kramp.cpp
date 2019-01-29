#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <iostream>
#include <stdlib.h>
#define BASE 10

using namespace std;

void vadd (int* arr, int& sum, int& largest, int n) {
	if (n <= BASE) {
		for (int i = 0; i < n; i++) {
			sum += arr[i];
			if(arr[i] > largest) largest = arr[i];
		}
	}
	else {
		cilk_spawn vadd(arr, sum, largest, n/2);
		vadd (arr + n/2, sum, largest, n - n/2);
		cilk_sync;
	}
} 

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Error, please input one positive integer N as argument" << endl;
		return 1;
	}
	int N = atoi(argv[1]);


	int* arr = new int[N];
	srand (time(NULL));

	for (int i = 0; i < N; i++) {
		int temp = rand() % 1000 + 1;
		arr[i] = temp;
	}

	int sum = 0;
	int largest = 0;

	vadd(arr, sum, largest, N);
	
        delete[] arr;

	cout << "Maximum: " << largest << "; Sum: " << sum << endl;
	return 0;
}
