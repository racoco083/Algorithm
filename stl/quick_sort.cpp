#include <iostream>
using namespace std;
#define MXN 100

int N;
int arr[MXN + 1];

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void quick_sort(int s, int e) {
	if (s >= e) return;
	int low = s + 1;
	int high = e;
	int pivot = s;

	while (low<=high) {
		while (arr[low] < arr[pivot]) low++;
		while (arr[high] > arr[pivot]) high--;
		if (low > high) break;
		swap(arr[low], arr[high]);
	}
	
	swap(arr[pivot], arr[high]);
	quick_sort(s, high - 1);
	quick_sort(high + 1, e);
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

	quick_sort(0, N - 1);
	print();
	return 0;
}

/*
5
3 1 2 4 5
*/