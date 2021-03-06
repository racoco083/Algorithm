/*
 *  BOJ 2636. 치즈
 * 
 *  시간복잡도 : O(TNM)
 *
 *  테두리는 항상 0이다. (0,0)에서 시작하여 qu를 사용해 bfs를 돌려 
 *  1을 만나면 이 좌표는 zero라는 queue에 담는다. 다음턴에서 이 좌표들이 
 *  시작하는 0값이 되기 때문이다. 이런식으로 치즈의 개수가 0이 될 때까지
 *  이번턴에 녹는 치즈의 개수를 bfs로 세면서 반복해 주면 된다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;
#define MXN 104
typedef pair<int, int> pi;

int N, M;
int visited[MXN + 1][MXN + 1];
int area[MXN + 1][MXN + 1];
int temp[MXN + 1][MXN + 1];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
queue<pi> zero;

int find_oone() {
	queue<pi> qu = zero;
	int cnt = 0;
	while (!zero.empty()) zero.pop();
	while (!qu.empty()) {
		int cy = qu.front().first;
		int cx = qu.front().second;
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny < 0 || ny >= N || nx < 0 || nx >= M || visited[ny][nx]) continue;
			visited[ny][nx] = true;
			if (area[ny][nx]) {
				cnt++;
				zero.push({ ny,nx });
				continue;
			}
			qu.push({ ny,nx });
		}
	}
	return cnt;
}

int main() {
	fastio();
	cin >> N >> M;
	int tcc = 0;// total_cheese_cnt
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> area[i][j];
			if (area[i][j]) tcc++;
		}
	}
	visited[0][0] = true;
	zero.push({ 0,0 });
	int T = 0;
	int ret;
	if (tcc == 0) {// 예외 처리
		cout << 0 << '\n' << 0 << '\n';
		return 0;
	}
	while (1) {
		T++;
		ret = find_oone();
		tcc -= ret;
		if (tcc == 0) break;
	}
	cout << T << '\n' << ret << '\n';
	return 0;
}