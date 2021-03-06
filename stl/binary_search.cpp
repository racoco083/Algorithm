#include<iostream>
using namespace std;
#define MAX 100

int arr[MAX + 1];

// v가 있으면 v값의 인덱스를 리턴한다.
int bs(int s, int e, int v) {
	while (s <= e) {
		int m = (s + e) / 2; //괄호 안 해주면 틀린다 주의!
		if (arr[m] == v) return m;
		else if (arr[m] > v) e = m - 1;
		else s = m + 1;
	}
	return -1; //찾는 값이 없으면 -1 return
}

int main() {
	for (int i = 0; i < MAX; i++) {
		arr[i] = i + 1;
	}
	cout << bs(0, MAX, 5) << '\n';
	cout << bs(0, MAX, 100) << '\n';
	cout << bs(0, MAX, 30) << '\n';
	cout << bs(0, MAX, 60) << '\n';
	cout << bs(0, MAX, 1) << '\n';
	cout << bs(0, MAX, 105) << '\n';
	return 0;
}