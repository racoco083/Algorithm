#include <iostream>
using namespace std;
#define MXN 10

int N;
int arr[MXN + 1];

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void insertion_sort() {
	for (int i = 1; i < N; i++) {
		int cur = arr[i];
		int j;
		for (j = i - 1; j >= 0 && cur < arr[j]; j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = cur;
	}
}

void print() {
	for (int i = 0; i < N; i++) {
		cout << arr[i] << ' ';
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	insertion_sort();
	print();
	return 0;
}

/*
5
8 5 6 2 4
*/