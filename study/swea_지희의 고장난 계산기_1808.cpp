#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;

bool chk[10];// 0~9까지 숫자가 사용할 수 있는지 체크한다.
const int INF = 2e9;

int min(int a, int b) {
	return a > b ? b : a;
}

// 모든 자리의 숫자가 사용할 수 있는 숫자인지 체크한다.
// 하나라도 사용할 수 없으면 false
bool can_make(int v) {
	while (v) {
		if (chk[v % 10] == 0) return false;
		v /= 10;
	}
	return true;
}

// 자릿수 개수를 리턴한다.
int calc_len(int v) {
	int c = 0;
	while (v) {
		v /= 10;
		c++;
	}
	return c;
}

// v값을 나누어 주면서 몇번 만에 이 값을 만들 수 있는지 구한다.
int dfs(int v) {
	int ret = INF;
	// v의 모든 자릿수의 숫자가 사용할 수 있는 숫자면 자릿수 개수를 리턴
	if (can_make(v)) return calc_len(v);

	for (int i = 2; i*i <= v; i++) {
		// i가 만들 수 있는 수인지 체크하고, v가 i로 나누어 떨어지는지 체크해야 한다.
		// 0에서 부터 값을 추가해 곱해가면서 x값을 만들려고 하면 나머지는 생길수가 없다.
		// 1 + calc_len(i) + dfs(v / i) 앞의 1은 곱하기를 세아린 것을 뜻한다.
		if (can_make(i) && v%i == 0) ret = min(ret, 1 + calc_len(i) + dfs(v / i));
	}
	return ret;
}

int main() {
	fastio();
	int TC;
	int x;
	cin >> TC;
	for (int T = 1; T <= TC; T++) {
		for (int i = 0; i < 10; i++) {
			cin >> x;
			chk[i] = x;
		}
		cin >> x;
		int ans = dfs(x);
		cout << '#' << T << ' ';
		if (ans == INF) cout << -1;
		else cout << ans + 1;
		cout << '\n';
	}
	return 0;
}