#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;

bool chk[10];// 0~9���� ���ڰ� ����� �� �ִ��� üũ�Ѵ�.
const int INF = 2e9;

int min(int a, int b) {
	return a > b ? b : a;
}

// ��� �ڸ��� ���ڰ� ����� �� �ִ� �������� üũ�Ѵ�.
// �ϳ��� ����� �� ������ false
bool can_make(int v) {
	while (v) {
		if (chk[v % 10] == 0) return false;
		v /= 10;
	}
	return true;
}

// �ڸ��� ������ �����Ѵ�.
int calc_len(int v) {
	int c = 0;
	while (v) {
		v /= 10;
		c++;
	}
	return c;
}

// v���� ������ �ָ鼭 ��� ���� �� ���� ���� �� �ִ��� ���Ѵ�.
int dfs(int v) {
	int ret = INF;
	// v�� ��� �ڸ����� ���ڰ� ����� �� �ִ� ���ڸ� �ڸ��� ������ ����
	if (can_make(v)) return calc_len(v);

	for (int i = 2; i*i <= v; i++) {
		// i�� ���� �� �ִ� ������ üũ�ϰ�, v�� i�� ������ ���������� üũ�ؾ� �Ѵ�.
		// 0���� ���� ���� �߰��� ���ذ��鼭 x���� ������� �ϸ� �������� ������� ����.
		// 1 + calc_len(i) + dfs(v / i) ���� 1�� ���ϱ⸦ ���Ƹ� ���� ���Ѵ�.
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