#include <iostream>
using namespace std;
#define MAX 10

int arr[MAX * 3 + 1];
const int INF = 2e9;

int ub(int s, int e, int v) {
	while (s < e) {
		int m = (e + s) / 2;
		if (v >= arr[m]) s = m + 1;
		else e = m;
	}
	return e;
}

int main() {
	for (int i = 0; i < MAX; i++) {
		arr[i] = 4;
	}
	for (int i = MAX; i < MAX * 2; i++) {
		arr[i] = 5;
	}
	for (int i = MAX * 2; i < MAX * 3; i++) {
		arr[i] = 6;
	}
	arr[MAX * 3] = INF;

	for (int i = 0; i <= MAX * 3; i++) cout << arr[i] << ' ';
	cout << '\n';
	cout << ub(0, MAX * 3, 6) << '\n';
	return 0;
}