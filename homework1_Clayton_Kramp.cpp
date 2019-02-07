#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#define BASE 100

using namespace std;

unsigned* vadd (int* arr, int n) {
	if (n <= BASE) {
		unsigned sum = 0;
		unsigned largest = 0;
		unsigned* vec = new unsigned[2];
		for (int i = 0; i < n; i++) {
			sum += arr[i];
			if(arr[i] > largest) largest = arr[i];
		}
		vec[0] = sum; vec[1] = largest;
		return vec;
	}
	else {
		unsigned* v1 = new unsigned[2];
		unsigned* v2 = new unsigned[2];
		v1 = cilk_spawn vadd(arr, n/2);
		v2 = cilk_spawn vadd (arr + n/2, n - n/2);
		cilk_sync;
		unsigned* returning = new unsigned[2];
		returning[0] = v1[0] + v2[0];
		if (v1[1] > v2[1]) returning[1] = v1[1];
		else returning[1] = v2[1];
		delete[] v1; delete[] v2;
		return returning;
	}
} 

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Error, please input one positive integer N as argument" << endl;
		return 1;
	}
	int N = atoi(argv[1]);
	clock_t tStart;
	tStart = clock();

	int* arr = new int[N];
	srand (time(NULL));

	for (int i = 0; i < N; i++) {
		int temp = rand() % 1000 + 1;
		arr[i] = temp;
	}

	unsigned* vec = new unsigned[2];
	vec = vadd(arr, N);
	
        delete[] arr;
//	cout << "Time Elapsed: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;

	cout << "Maximum: " << vec[1] << "; Sum: " << vec[0] << endl;
	delete[] vec;
	return 0;
}
