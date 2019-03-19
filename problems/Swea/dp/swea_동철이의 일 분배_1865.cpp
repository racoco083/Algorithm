#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <string.h>
using namespace std;

int N;
double area[17][17];
double cache[1 << 16];

double max(double a, double b) {
	return a > b ? a : b;
}

// d��° ������ i��° ���� �����Ѵ�. ret�� �ڽ� ��忡�� ���� ���� ���� �ִ밪�� ������ 
// ���� ū ���� ret�� ���Ž�Ų��.
double dfs(int d, int m) {// ret, depth, mask
	if (d >= N) return 1.0;

	double &ret = cache[m];
	if (ret != 0.0) return ret;

	for (int i = 0; i < N; i++) {
		if (m & (1 << i)) continue;
		ret = max(ret, dfs(d + 1, m | (1 << i)) * area[d][i]);
	}
	return ret;
}

int main() {
	fastio();
	cout << fixed;
	cout.precision(6);
	int TC;
	cin >> TC;
	for (int T = 1; T <= TC; T++) {
		cin >> N;
		double a;
		// double�� memset���� -1�� �ʱ�ȭ ���� �ʴ´�.
		memset(cache, 0, sizeof(cache));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> a;
				area[i][j] = a / 100.0;
			}
		}
		cout << '#' << T << ' ' << dfs(0, 0) * 100.0 << '\n';
	}
	return 0;
}