#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Error, please input one positive integer N as argument" << endl;
		return 1;
	}
	int N = atoi(argv[1]);


	vector<int> vec(N);
	srand (time(NULL));

	for (int i = 0; i < N; i++) {
		int temp = rand() % 1000 + 1;
		vec[i] = temp;
	}

	unsigned long sum = 0;
	int largest = 0;

	for (int i = 0; i < N; i++) {
		sum += vec[i];
		if(vec[i] > largest) {
			largest = vec[i];
		}
	}
	
	cout << "Maximum: " << largest << "; Sum: " << sum << endl;
	return 0;
}
