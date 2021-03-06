#include <iostream>
using namespace std;
#define MXN 10

int N;
int arr[MXN + 1];
const int INF = 2e9;

int min(int a, int b) {
	return a > b ? b : a;
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void selection_sort() {
	for (int i = 0; i < N - 1; i++) {
		int midx = i;
		for (int j = i; j < N; j++) {
			if (arr[midx] > arr[j]) {
				midx = j;
			}
		}
		swap(arr[i], arr[midx]);
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

	selection_sort();
	print();
	return 0;
}

/*
5
9 6 7 3 5
*/