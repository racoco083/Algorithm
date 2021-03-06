#include <iostream>
using namespace std;
#define MXN 100

int arr[MXN + 1];
int N;

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void bubble_sort(int s, int e){
	for (int i = 0; i < e - s; i++) {
		for (int j = s + 1; j < e - i; j++) {
			if (arr[j - 1] > arr[j]) swap(arr[j - 1], arr[j]);
		}
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

	bubble_sort(0, N);
	print();
	return 0;
}

/*
20
5 15 7 20 1 4 10 2 8 11 9 6 13 18 3 16 12 14 17 19
*/

/*
5
5 4 3 2 1
*/