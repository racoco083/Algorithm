#include <iostream>
using namespace std;

int N;
int arr[100];
int tmp[100];

void merge(int s, int e) {
	if (e <= s) return;
	int m = (e + s) / 2;
	int l = s, r = m + 1, k = s;
	merge(s, m);
	merge(r, e);
	while (l <= m && r <= e) {
		// 안정성이 있으려면 <가 아닌 <=가 있어야 한다.
		tmp[k++] = (arr[l] <= arr[r]) ? arr[l++] : arr[r++];
	}
	while (l <= m) tmp[k++] = arr[l++];
	while (r <= e) tmp[k++] = arr[r++];
	for (int i = s; i <= e; i++) arr[i] = tmp[i];
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> arr[i];
	merge(0, N - 1);
	for (int i = 0; i < N + 5; i++)
		cout << arr[i] << ' ';
	return 0;
}
/*
5
5 4 3 2 1
*/