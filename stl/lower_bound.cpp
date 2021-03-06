#include <iostream>
using namespace std;
#define MAX 100

int arr[MAX * 2+1];
const int INF = 2e9;

// lower_bound는 찾는 값이 없으면 그것보다 바로 다음 큰 값의 인덱스를 리턴한다.
int lb(int s, int e, int v) {
	while (s < e) { //lb는 bs와 다르게 s와 e가 같은 값일 때도 처리해주면 무한반복한다. bs처럼 그 값을 찾았을 때 끝내는게 아니라 e에 m을 주입하고 찾는 과정을 계속하기 때문이다.
		int m = (s + e) / 2; //괄호 안 해주면 틀린다 주의!
		if (arr[m] >= v) e = m;
		else s = m + 1;
	}
	return e;
}

int main() {
	for (int i = 0; i < MAX; i++) {
		arr[i] = 4;
	}
	for (int i = MAX; i < MAX * 2; i++) {
		arr[i] = 6;
	}
	arr[MAX * 2] = INF;
	for (int i = 0; i <= MAX * 2; i++) cout << arr[i] << ' ';
	cout << '\n';
	cout << lb(0, MAX * 2, 5) << '\n';
	return 0;
}