/*
 *  swea 1767. 프로세서 연결하기
 *
 *  시간복잡도 : O(4^N * N^2)
 *
 *  테두리에 붙은 프로세서 빼고 나머지 프로세서를 모두 core벡터에 담는다.
 *  이 코어들에 대해 순서대로 dfs를 하여 각 코어의 4방향을 다 보고 연결이 되면
 *  코어개수를 1증가시켜 다음 dfs를 실행시키면 된다. 하지만 연결이 되지 못 하는 상황이면
 *  전선을 아에 놓지 않고 다음 dfs를 실해시키는 것이 전선의 길이를 최소화 할 수 있다.
 *  그러므로 현재코어에서 전선을 놓으며 바깥과 연결이 되지 않을 때는 break를 해 주고
 *  4방향을 다 보기 전에 전선을 놓지 않고 다음 dfs를 코어개수를 그대로 하여
 *  실행시키면 된다.
 *
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define MXN 12
typedef pair<int, int> pi;

int N;
int area[MXN + 1][MXN + 1];
vector<pi> core;
int len_sum;
int core_cnt;
const int INF = 2e9;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int calc() {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (area[i][j] == 2) ret++;
		}
	}
	return ret;
}

int min(int a, int b) {
	return a > b ? b : a;
}

void dfs(int c, int cnt) {
	if (c == core.size()) {
		if (core_cnt < cnt) {
			core_cnt = cnt;
			len_sum = calc();
		}
		else if (cnt == core_cnt) {
			len_sum = min(len_sum, calc());
		}
		// stack overflow가 발생했다. 알고보니 밑에 return;을 해 주지 않았다.
		return;
	}

	int tmp[MXN + 1][MXN + 1];
	memcpy(tmp, area, sizeof(tmp));

	dfs(c + 1, cnt);

	for (int i = 0; i < 4; i++) {
		int cy = core[c].first;
		int cx = core[c].second;
		while (1) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny < 0 || ny >= N || nx < 0 || nx >= N) {
				dfs(c + 1, cnt + 1);
				break;
			}
			if (area[ny][nx]) {
				break;
			}
			area[ny][nx] = 2;
			cy = ny;
			cx = nx;
		}
		memcpy(area, tmp, sizeof(tmp));
	}

}

int main() {
	fastio();
	int TC;
	cin >> TC;
	for (int T = 1; T <= TC; T++) {
		cin >> N;
		core.clear();
		len_sum = INF;
		core_cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> area[i][j];
			}
		}

		for (int i = 1; i < N-1; i++) {
			for (int j = 1; j < N-1; j++) {
				if (area[i][j]) core.push_back({ i,j });
			}
		}

		dfs(0, 0);
		cout << '#' << T << ' ' << len_sum << '\n';
	}
	return 0;
}

/*
1
7
0 0 1 0 0 0 0
0 0 1 0 0 0 0
0 0 0 0 0 1 0
0 0 0 0 0 0 0
1 1 0 1 0 0 0
0 1 0 0 0 0 0
0 0 0 0 0 0 0
*/