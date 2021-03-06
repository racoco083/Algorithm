/*
 *  swea 5656. 벽돌 깨기
 *
 *  시간복잡도 : O(W^N * W * H)
 *
 *  재귀적으로 반복하면서 N번을 위에서 쏘면 벽돌을 부순다
 *  맨위의 벽돌이 부서질 때 마다 bfs를 돌려 범위의 벽돌을 깨며 값을 0으로 만들어주고
 *  이 값이 1보다 크면 이 벽돌에 의해 다른 벽돌도 깨져야 하니 qu에 담는다.
 *  이렇게 qu에 담고 터트리는 걸 반복하는 것을 재귀적으로 반복하면 된다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
#define MXR 16

class Pos {
public:
	int y, x, c;
	Pos() {}
	Pos(int _y, int _x, int _c) : y(_y), x(_x), c(_c) {}
};

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int area[MXR + 1][MXR + 1];
int N, W, H;
int ans;
const int INF = 2e9;

int min(int a, int b) {
	return a > b ? b : a;
}

int calc() {
	int ret = 0;
	// i<N으로 해서 틀렸다. 습관 때문에..
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (area[i][j]) ret++;
		}
	}
	return ret;
}

void bfs(int y, int x) {
	queue<Pos> qu;
	qu.push(Pos(y, x, area[y][x]));
	area[y][x] = 0;

	while (!qu.empty()) {
		int cy = qu.front().y;
		int cx = qu.front().x;
		int cc = qu.front().c - 1;
		qu.pop();

		for (int i = 0; i < 4; i++) {
			int ty = cy;
			int tx = cx;
			for (int j = 0; j < cc; j++) {
				int ny = ty + dy[i];
				int nx = tx + dx[i];
				if (ny < 0 || ny >= H || nx < 0 || nx >= W) break;
				if (area[ny][nx] > 1) qu.push(Pos(ny, nx, area[ny][nx]));
				area[ny][nx] = 0;
				ty = ny;
				tx = nx;
			}
		}
	}

}

void block_down() {
	for (int i = 0; i < W; i++) {
		queue<int> qu;
		for (int j = H-1; j >= 0; j--) {
			if (area[j][i]) {
				qu.push(area[j][i]);
				area[j][i] = 0;
			}
		}
		int idx = H - 1;
		while (!qu.empty()) {
			area[idx--][i] = qu.front();
			qu.pop();
		}
	}
}

void dfs(int c) {
	if (c == N) {
		ans = min(ans, calc());
		return;
	}

	int tmp[MXR + 1][MXR + 1];
	memcpy(tmp, area, sizeof(tmp));

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			if (area[j][i]) {
				// bfs(i, j)로 주어 틀렸다.
				bfs(j, i);
				block_down();
				break;
			}
		}
		dfs(c + 1);
		memcpy(area, tmp, sizeof(tmp));
	}
}

int main() {
	fastio();
	int TC;
	cin >> TC;
	for (int T = 1; T <= TC; T++) {
		cin >> N >> W >> H;
		ans = INF;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> area[i][j];
			}
		}
		dfs(0);
		cout << '#' << T << ' ' << ans << '\n';
	}
	return 0;
}

/*
1
3 10 10
0 0 0 0 0 0 0 0 0 0
1 0 1 0 1 0 0 0 0 0
1 0 3 0 1 1 0 0 0 1
1 1 1 0 1 2 0 0 0 9
1 1 4 0 1 1 0 0 1 1
1 1 4 1 1 1 2 1 1 1
1 1 5 1 1 1 1 2 1 1
1 1 6 1 1 1 1 1 2 1
1 1 1 1 1 1 1 1 1 5
1 1 7 1 1 1 1 1 1 1
2 9 10
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0
1 1 0 0 1 0 0 0 0
1 1 0 1 1 1 0 1 0
1 1 0 1 1 1 0 1 0
1 1 1 1 1 1 1 1 0
1 1 3 1 6 1 1 1 1
1 1 1 1 1 1 1 1 1
*/