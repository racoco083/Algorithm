#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;

int arr[21];
int N, B;
int ans;

int min(int a, int b) {
	return a > b ? b : a;
}

// arr[d]��° ���� �־ ���� dfs�� ���� �ʰ� ���� dfs�� ���� ���� �ݺ��ؼ�
// ������ �� �� s�� B���� ũ�ų� ������ ans�� ���� ���� �� ���� ���� ans�� ����
void dfs(int s, int d) { // sum, depth
	if (s >= B) {
		ans = min(ans, s);
		return;
	}
	if (d >= N) return;

	dfs(s + arr[d], d + 1);
	dfs(s, d + 1);
}

int main() {
	int TC;
	cin >> TC;
	for (int T = 1; T <= TC; T++) {
		ans = 2e9;
		cin >> N >> B;
		for (int i = 0; i < N; i++) {
			cin >> arr[i];
		}
		dfs(0, 0);
		cout << '#' << T << ' ' << ans - B << '\n';
	}
	return 0;
}