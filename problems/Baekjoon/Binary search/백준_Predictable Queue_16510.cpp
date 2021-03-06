/*
 *  BOJ 16510. Predictable Queue
 *
 *  시간복잡도 : O(MlogN)
 *  공간복잡도 : O(N)
 *  
 *  시간이 주어질 때 일의 처음부터 시작해서 최대 몇개의 일을 수행 할
 *  수 있는지 묻는 문제이다. 누적합 배열을 만들어 입력으로 받은
 *  시간을 누적합 배열에서 찾아서 ub를 구하고 이 구한 인덱스의
 *  -1 값이 주어진 시간에 최대의 일의 개수가 된다.
 *
 */

#include <iostream>
using namespace std;
#define MXN 200002

int N, M;
int arr[MXN];

int ub(int s, int e, int v) {
	while (s < e) {
		int m = (e + s) / 2;
		if (arr[m] <= v) s = m + 1;
		else e = m;
	}
	return e;
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
		arr[i] += arr[i - 1];
	}
	// ub를 사용했으므로 가장 마지막은 생길 수 없는 값으로 찾는 값이 
	// 없을 때는 마지막 값을 가리키도록 한다.
	arr[N + 1] = 2e9 + 50;

	int q;
	for (int i = 0; i < M; i++) {
		cin >> q;
		cout << ub(1, N + 1, q) - 1 << '\n';
	}
	return 0;
}