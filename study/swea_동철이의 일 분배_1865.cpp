#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;

int arr[21];
int N, B;
int ans;

int min(int a, int b) {
	return a > b ? b : a;
}

// arr[d]번째 값을 넣어서 다음 dfs로 넣지 않고 다음 dfs로 가는 것을 반복해서
// 높이의 합 값 s가 B보다 크거나 같으면 ans의 값과 비교해 더 작은 값을 ans에 갱신
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