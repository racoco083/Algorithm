/*
 *  BOJ 16988. Baduk2
 *
 *  시간복잡도 : O(N^6)
 *
 *  바둑을 놓을 수 있는 모든 빈칸을 보며 바둑을 놓고 dfs를 돌린다.
 *  바둑을 놓은 횟수 cnt가 2가 되면 bfs를 돌려 검은돌이 폐쇠되어있는 곳의
 *  최대 값을 구해서 리턴하여 이 값이 가장 큰 값을 구한다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
#define MXN 21
typedef pair<int, int> pi;

int N, M;
int area[MXN + 1][MXN + 1];
bool visited[MXN + 1][MXN + 1];
int ans;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int max(int a, int b) {
	return a > b ? a : b;
}

int bfs(int y, int x) {
	queue<pi> qu;
	qu.push({ y,x });
	visited[y][x] = true;
	bool closed = true;
	int cnt = 1;

	while (!qu.empty()) {
		int cy = qu.front().first;
		int cx = qu.front().second;
		qu.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny < 0 || ny >= N || nx < 0 || nx >= M
				|| visited[ny][nx] || area[ny][nx] == 1) continue;

			if (!area[ny][nx]) {
				closed = false;
				continue;
			}
			cnt++;
			visited[ny][nx] = true;
			qu.push({ ny, nx });
		}
	}
	if (closed) return cnt;
	return 0;
}

int calc() {
	// 초기화 안 시켜줬다.
	memset(visited, 0, sizeof(visited));
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			if (area[i][j] == 2 && !visited[i][j]) {
				// ret = max(ret, bfs(i,j))로 하여 돌 두개를 놓았을 때 먹을 수 있는
				// 영역이 2개 이상일 수 있는 데 그걸 간과했다.
				ret += bfs(i, j);
			}
		}
	}
	return ret;
}

void dfs(int y, int x, int cnt) {
	if (cnt == 2) {
		ans = max(calc(), ans);
		return;
	}

	for (int i = y; i < N; i++) {
		if (i != y) x = 0;
		for (int j = x; j < M; j++) {
			if (area[i][j]) continue;
			area[i][j] = 1;
			// i+1, j+1주는 실수를 하였다.
			dfs(i, j, cnt + 1);
			area[i][j] = 0;
		}
	}

}

int main() {
	fastio();
	cin >> N >> M;
	ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> area[i][j];
		}
	}
	dfs(0, 0, 0);
	cout << ans << '\n';
}