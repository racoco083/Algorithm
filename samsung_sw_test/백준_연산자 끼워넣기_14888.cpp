/*
 *  BOJ 연산자 끼워넣기. 148888
 *
 *  시간복잡도 : O(?)
 *
 *  연산자 우선순위가 없고 앞에서 부터 계산하면 된다.
 *  그래서 dfs로 현재까지 계산한 값 v, 다음 계산할 값의 인덱스 n
 *  매개변수로 넘겨준다. n이 N과 같을 때 모든 수를 다썻다는 것이므로
 *  v의 min값과 max값을 구하면 된다. 
 *
 *  첫 번째 실수 : max, min함수도 반환 값이 ll이어야 하는데
 *  다른 곳 다 잘 처리해 주고 여기 안해서 한 번 틀렸다.
 *
 *  두 번째 실수 : mxv값이 항상 양수가 아니다 음수일 수 있다.
 *  그런데 mxv의 값을 -INF로 두지 않고 0으로 두어 틀렸다.
 *  
 */

#include <iostream>
using namespace std;
#define MXN 11
typedef long long ll;

int N;
ll A[MXN + 1];
int ope[4];
ll mxv, miv;
const ll INF = 1e12;

ll max(ll a, ll b) {
	return a > b ? a : b;
}

ll min(ll a, ll b) {
	return a > b ? b : a;
}

ll operation(ll v, int i, int n) {
	ll ret = 0;
	if (i == 0) ret = v + A[n];
	else if (i == 1) ret = v - A[n];
	else if (i == 2) ret = v * A[n];
	else if (i == 3) ret = v / A[n];
	return ret;
}

void dfs(ll v, int n) {
	if (n == N) {
		mxv = max(mxv, v);
		miv = min(miv, v);
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (!ope[i]) continue;
		ope[i]--;
		dfs(operation(v, i, n), n + 1);
		ope[i]++;
	}
}

int main() {
	cin >> N;
	mxv = -INF;
	miv = INF;
	for (int i = 0; i < N; i++) cin >> A[i];
	for (int i = 0; i < 4; i++) cin >> ope[i];

	dfs(A[0], 1);
	cout << mxv << '\n';
	cout << miv << '\n';
	return 0;
}